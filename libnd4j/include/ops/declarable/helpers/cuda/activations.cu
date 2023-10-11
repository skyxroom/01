/* ******************************************************************************
 *
 *
 * This program and the accompanying materials are made available under the
 * terms of the Apache License, Version 2.0 which is available at
 * https://www.apache.org/licenses/LICENSE-2.0.
 *
 *  See the NOTICE file distributed with this work for additional
 *  information regarding copyright ownership.
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
 * License for the specific language governing permissions and limitations
 * under the License.
 *
 * SPDX-License-Identifier: Apache-2.0
 ******************************************************************************/

//
// @author Yurii Shyrma (iuriish@yahoo.com), created on 19.04.2018
// @author raver119@gmail.com
//
#include <helpers/ConstantTadHelper.h>
#include <helpers/PointersManager.h>
#include <helpers/ShapeUtils.h>
#include <ops/declarable/helpers/activations.h>
#include <system/op_boilerplate.h>

#include <numeric>

#include "execution/cuda/LaunchDims.h"

namespace sd {
namespace ops {
namespace helpers {

///////////////////////////////////////////////////////////////////
template <typename X, typename Y>
void SD_KERNEL preluCuda(const void *vx, const sd::LongType *xShapeInfo, const void *vy, const sd::LongType *yShapeInfo,
                         void *vz) {
  const auto x = reinterpret_cast<const X *>(vx);
  const auto y = reinterpret_cast<const Y *>(vy);
  auto z = reinterpret_cast<X *>(vz);

  __shared__ sd::LongType xzLen;
  __shared__ int xzRank, yRank;

  if (threadIdx.x == 0) {
    xzLen = shape::length(xShapeInfo);

    xzRank = shape::rank(xShapeInfo);
    yRank = shape::rank(yShapeInfo);
  }
  __syncthreads();

  const auto tid = blockIdx.x * blockDim.x + threadIdx.x;
  sd::LongType coords[SD_MAX_RANK];

  for (int i = tid; i < xzLen; i += blockDim.x * gridDim.x) {
    shape::index2coords(i, xShapeInfo, coords);

    const auto xzOffset = shape::getOffset(xShapeInfo, coords);
    const auto xVal = x[xzOffset];

    if (xVal < 0) {
      for (sd::LongType j = 0; j < yRank; ++j)
        if (yShapeInfo[j + 1] == 1) coords[j + 1] = 0;

      z[xzOffset] = xVal * y[shape::getOffset(yShapeInfo, coords + 1)];
    } else
      z[xzOffset] = xVal;
  }
}

///////////////////////////////////////////////////////////////////
template <typename X, typename Y>
void preluCudaLauncher(const int blocksPerGrid, const int threadsPerBlock, const int sharedMem,
                       const cudaStream_t *stream, const void *vx, const sd::LongType *xShapeInfo, const void *vy,
                       const sd::LongType *yShapeInfo, void *vz) {
  preluCuda<X, Y><<<blocksPerGrid, threadsPerBlock, sharedMem, *stream>>>(vx, xShapeInfo, vy, yShapeInfo, vz);
}

///////////////////////////////////////////////////////////////////
void prelu(sd::LaunchContext *context, const NDArray &input, const NDArray &alpha, NDArray &output) {
  PointersManager manager(context, "prelu");

  dim3 launchDims = getLaunchDims("prelu");

  const auto xType = input.dataType();
  const auto yType = alpha.dataType();

  NDArray::prepareSpecialUse({&output}, {&input, &alpha});
  BUILD_SINGLE_SELECTOR_TWICE(
      xType, preluCudaLauncher,
      (launchDims.x, launchDims.y, launchDims.z, context->getCudaStream(), input.specialBuffer(),
       input.specialShapeInfo(), alpha.specialBuffer(), alpha.specialShapeInfo(), output.specialBuffer()),
      SD_FLOAT_TYPES);
  NDArray::registerSpecialUse({&output}, {&input, &alpha});

  manager.synchronize();
}

///////////////////////////////////////////////////////////////////
template <typename X, typename Y>
void SD_KERNEL preluBPCuda(const void *vIn, const sd::LongType *inShapeInfo, const void *vAlpha,
                           const sd::LongType *alphaShapeInfo, const void *vdLdO, const sd::LongType *dLdOShapeInfo,
                           void *vdLdI, const sd::LongType *dLdIShapeInfo, void *vdLdA,
                           const sd::LongType *dLdAShapeInfo) {
  const auto in = reinterpret_cast<const X *>(vIn);
  const auto alpha = reinterpret_cast<const Y *>(vAlpha);
  const auto dLdO = reinterpret_cast<const Y *>(vdLdO);
  auto dLdI = reinterpret_cast<Y *>(vdLdI);
  auto dLdA = reinterpret_cast<Y *>(vdLdA);

  __shared__ sd::LongType inLen, totalThreads;
  __shared__ int inRank, alphaRank;

  if (threadIdx.x == 0) {
    inLen = shape::length(inShapeInfo);
    totalThreads = gridDim.x * blockDim.x;

    inRank = shape::rank(inShapeInfo);
    alphaRank = shape::rank(alphaShapeInfo);
  }
  __syncthreads();

  const auto tid = blockIdx.x * blockDim.x + threadIdx.x;
  sd::LongType coords[SD_MAX_RANK];

  for (int i = tid; i < inLen; i += totalThreads) {
    shape::index2coords(i, inShapeInfo, coords);

    const auto inOffset = shape::getOffset(inShapeInfo, coords);
    const auto dLdOOffset = shape::getOffset(dLdOShapeInfo, coords);
    const auto dLdIOffset = shape::getOffset(dLdIShapeInfo, coords);

    const auto xVal = in[inOffset];
    const auto grO = dLdO[dLdOOffset];

    if (xVal < 0) {
      for (sd::LongType j = 0; j < alphaRank; ++j)
        if (alphaShapeInfo[j + 1] == 1) coords[j + 1] = 0;

      const auto alphaOffset = shape::getOffset(alphaShapeInfo, coords + 1);
      const auto dLdAOffset = shape::getOffset(dLdAShapeInfo, coords + 1);

      dLdI[dLdIOffset] = grO * alpha[alphaOffset];

      sd::math::atomics::sd_atomicAdd<Y>(&dLdA[dLdAOffset], static_cast<Y>(grO * xVal));
    } else
      dLdI[dLdIOffset] = grO;
  }
}

//////////////////////////////////////////////////////////////////////////
template <typename X, typename Y>
void SD_HOST preluBPCudaLauncher(const int blocksPerGrid, const int threadsPerBlock, const int sharedMem,
                                 const cudaStream_t *stream, const void *vIn, const sd::LongType *inShapeInfo,
                                 const void *vAlpha, const sd::LongType *alphaShapeInfo, const void *vdLdO,
                                 const sd::LongType *dLdOShapeInfo, void *vdLdI, const sd::LongType *dLdIShapeInfo,
                                 void *vdLdA, const sd::LongType *dLdAShapeInfo) {
  preluBPCuda<X, Y><<<blocksPerGrid, threadsPerBlock, sharedMem, *stream>>>(
      vIn, inShapeInfo, vAlpha, alphaShapeInfo, vdLdO, dLdOShapeInfo, vdLdI, dLdIShapeInfo, vdLdA, dLdAShapeInfo);
}

//////////////////////////////////////////////////////////////////////////
void preluBP(sd::LaunchContext *context, const NDArray &input, const NDArray &alpha, const NDArray &dLdO, NDArray &dLdI,
             NDArray &dLdA) {
  dLdA.nullify();

  PointersManager manager(context, "preluBP");

  dim3 launchDims = getLaunchDims("prelu");

  const auto xType = input.dataType();
  const auto zType = alpha.dataType();

  NDArray::prepareSpecialUse({&dLdI, &dLdA}, {&input, &alpha, &dLdO});
  BUILD_SINGLE_SELECTOR_TWICE(
      xType, preluBPCudaLauncher,
      (launchDims.x, launchDims.y, launchDims.z, context->getCudaStream(), input.specialBuffer(),
       input.specialShapeInfo(), alpha.specialBuffer(), alpha.specialShapeInfo(), dLdO.specialBuffer(),
       dLdO.specialShapeInfo(), dLdI.specialBuffer(), dLdI.specialShapeInfo(), dLdA.specialBuffer(),
       dLdA.specialShapeInfo()),
      SD_FLOAT_TYPES);
  NDArray::registerSpecialUse({&dLdI, &dLdA}, {&input, &alpha, &dLdO});

  manager.synchronize();
}

///////////////////////////////////////////////////////////////////
template <typename T>
SD_DEVICE void softMaxForVectorCuda(const void *vx, const sd::LongType *xShapeInfo, void *vz,
                                    const sd::LongType *zShapeInfo) {
  // logic of this kernel is based on assumption gridDim = 1

  const auto x = reinterpret_cast<const T *>(vx);
  auto z = reinterpret_cast<T *>(vz);

  __shared__ sd::LongType len;
  __shared__ int numOfIters;
  __shared__ T shmem[SD_CUDA_BLOCK_SIZE];

  if (threadIdx.x == 0) {
    len = shape::length(xShapeInfo);
    numOfIters = (len + blockDim.x - 1) / blockDim.x;  // ceil (len / blockDim.x)
  }
  __syncthreads();

  T temp =
      -DataTypeUtils::max<T>();  // set start value to compare with at first iteration, FIXME: what if T is unsigned ??

  // ************ evaluate max element in input array x ************ //
  for (int i = 0; i < numOfIters; ++i) {
    const sd::LongType elemIdx = i * blockDim.x + threadIdx.x;
    if (elemIdx < len) {
      const sd::LongType xOffset = shape::getIndexOffset(elemIdx, xShapeInfo);
      shmem[threadIdx.x] =
          (threadIdx.x != 0)
              ? x[xOffset]
              : sd::math::sd_max<T>(
                    x[xOffset],
                    temp);  // take into account max element evaluated on previous iteration and stored in temp
    } else
      shmem[threadIdx.x] = -DataTypeUtils::max<T>();  // FIXME: what if T is unsigned ??

    __syncthreads();

    for (int s = blockDim.x / 2; s > 0; s /= 2) {
      if (threadIdx.x < s) shmem[threadIdx.x] = sd::math::sd_max<T>(shmem[threadIdx.x], shmem[threadIdx.x + s]);
      __syncthreads();
    }

    temp = shmem[0];  // save max value calculated at current iteration
  }

  const T max = temp;
  temp = 0;

  // ************ evaluate value of exp(x[offset] - max) per each element, store it to shared memory shmem ************
  // // at the same evaluate sum of exponents, sum will be stored in shmem[0]
  for (int i = 0; i < numOfIters; ++i) {
    const sd::LongType elemIdx = i * blockDim.x + threadIdx.x;
    if (elemIdx < len) {
      const sd::LongType xOffset = shape::getIndexOffset(elemIdx, xShapeInfo);
      const sd::LongType zOffset = shape::getIndexOffset(elemIdx, zShapeInfo);
      z[zOffset] = sd::math::sd_exp<T, T>(x[xOffset] - max);
      shmem[threadIdx.x] =
          (threadIdx.x != 0)
              ? z[zOffset]
              : (z[zOffset] +
                 temp);  // take into account sum element evaluated on previous iteration and stored in temp
    } else
      shmem[threadIdx.x] = 0;

    __syncthreads();

    for (int s = blockDim.x / 2; s > 0; s /= 2) {
      if (threadIdx.x < s) shmem[threadIdx.x] += shmem[threadIdx.x + s];
      __syncthreads();
    }

    temp = shmem[0];  // save sum calculated at current iteration
  }

  // ************ evaluate z[offset] / sum  ************ //
  for (int i = 0; i < numOfIters; ++i) {
    const sd::LongType elemIdx = i * blockDim.x + threadIdx.x;
    if (elemIdx >= len) continue;
    const sd::LongType zOffset = shape::getIndexOffset(elemIdx, zShapeInfo);
    z[zOffset] /= shmem[0];
  }
}

template <typename T>
void SD_KERNEL softMaxForVectorCudaGlobal(const void *vx, const sd::LongType *xShapeInfo, void *vz,
                                          const sd::LongType *zShapeInfo) {
  softMaxForVectorCuda<T>(vx, xShapeInfo, vz, zShapeInfo);
}

///////////////////////////////////////////////////////////////////
template <typename T>
void softMaxForVectorCudaLauncher(const cudaStream_t *stream, const void *vx, const sd::LongType *xShapeInfo, void *vz,
                                  const sd::LongType *zShapeInfo) {
  softMaxForVectorCudaGlobal<T><<<1, SD_CUDA_BLOCK_SIZE, 1024, *stream>>>(vx, xShapeInfo, vz, zShapeInfo);
}

///////////////////////////////////////////////////////////////////
template <typename T>
SD_KERNEL static void softMaxCuda(const void *vx, const sd::LongType *xTadShapeInfo, const sd::LongType *xOffsets,
                                  void *vz, const sd::LongType *zTadShapeInfo, const sd::LongType *zOffsets) {
  const auto x = reinterpret_cast<const T *>(vx);
  auto z = reinterpret_cast<T *>(vz);

  const auto *xTad = x + xOffsets[blockIdx.x];
  auto *zTad = z + zOffsets[blockIdx.x];

  softMaxForVectorCuda<T>(xTad, xTadShapeInfo, zTad, zTadShapeInfo);
}

///////////////////////////////////////////////////////////////////
template <typename T>
static void softMaxCudaLauncher(const int blocksPerGrid, const int threadsPerBlock, const int sharedMem,
                                const cudaStream_t *stream, const void *vx, const sd::LongType *xTadShapeInfo,
                                const sd::LongType *xOffsets, void *vz, const sd::LongType *zTadShapeInfo,
                                const sd::LongType *zOffsets) {
  softMaxCuda<T><<<blocksPerGrid, threadsPerBlock, sharedMem, *stream>>>(vx, xTadShapeInfo, xOffsets, vz, zTadShapeInfo,
                                                                         zOffsets);
}

//////////////////////////////////////////////////////////////////////////
void softmax(sd::LaunchContext *context, const NDArray &input, NDArray &output, const int dimension) {
  if (!input.isActualOnDeviceSide()) input.syncToDevice();
  const int rank = input.rankOf();

  PointersManager manager(context, "helpers::softmax");

  if (input.isVector()) {
    if (rank == 1 || input.sizeAt(dimension) != 1) {
      NDArray::prepareSpecialUse({&output}, {&input});
      BUILD_SINGLE_SELECTOR(input.dataType(), softMaxForVectorCudaLauncher,
                            (context->getCudaStream(), input.specialBuffer(), input.specialShapeInfo(),
                             output.specialBuffer(), output.specialShapeInfo()),
                            SD_FLOAT_TYPES);
      NDArray::registerSpecialUse({&output}, {&input});
    } else
      output = 1.;
  } else {
    auto packX = sd::ConstantTadHelper::getInstance().tadForDimensions(input.shapeInfo(), {dimension});
    auto packZ = sd::ConstantTadHelper::getInstance().tadForDimensions(output.shapeInfo(), {dimension});

    dim3 softmaxDims = getSoftmaxDims(packZ->numberOfTads());


    NDArray::prepareSpecialUse({&output}, {&input});
    BUILD_SINGLE_SELECTOR(input.dataType(), softMaxCudaLauncher,
                          (softmaxDims.x, softmaxDims.y, softmaxDims.z, context->getCudaStream(), input.specialBuffer(),
                           packX->specialShapeInfo(), packX->specialOffsets(), output.specialBuffer(),
                           packZ->specialShapeInfo(), packZ->specialOffsets()),
                          SD_FLOAT_TYPES);
    NDArray::registerSpecialUse({&output}, {&input});

  }

  manager.synchronize();

  output.tickWriteDevice();
}

///////////////////////////////////////////////////////////////////
template <typename T>
void SD_KERNEL logSoftMaxForVectorCuda(const void *vx, const sd::LongType *xzShapeInfo, void *vz) {
  // logic of this kernel is based on assumption gridDim = 1

  const auto x = reinterpret_cast<const T *>(vx);
  auto z = reinterpret_cast<T *>(vz);

  __shared__ sd::LongType len;
  __shared__ int numOfIters;
  __shared__ T shmem[SD_CUDA_BLOCK_SIZE];

  if (threadIdx.x == 0) {
    len = shape::length(xzShapeInfo);
    numOfIters = (len + blockDim.x - 1) / blockDim.x;  // ceil (len / blockDim.x)
  }
  __syncthreads();

  T temp =
      -DataTypeUtils::max<T>();  // set start value to compare with at first iteration, FIXME: what if T is unsigned ??

  // ************ evaluate max element in input array x ************ //
  for (int i = 0; i < numOfIters; ++i) {
    const sd::LongType elemIdx = i * blockDim.x + threadIdx.x;
    if (elemIdx < len) {
      const sd::LongType offset = shape::getIndexOffset(elemIdx, xzShapeInfo);
      shmem[threadIdx.x] =
          (threadIdx.x != 0)
              ? x[offset]
              : sd::math::sd_max<T>(
                    x[offset],
                    temp);  // take into account max element evaluated on previous iteration and stored in temp
    } else
      shmem[threadIdx.x] = -DataTypeUtils::max<T>();  // FIXME: what if T is unsigned ??

    __syncthreads();

    for (int s = blockDim.x / 2; s > 0; s /= 2) {
      if (threadIdx.x < s) shmem[threadIdx.x] = sd::math::sd_max<T>(shmem[threadIdx.x], shmem[threadIdx.x + s]);
      __syncthreads();
    }

    temp = shmem[0];  // save max value calculated at current iteration
  }

  const T max = temp;
  temp = 0;

  // ************ evaluate value of exp(x[offset] - max) per each element, store it to shared memory shmem ************
  // // at the same time evaluate sum of exponents, sum will be stored in shmem[0]
  for (int i = 0; i < numOfIters; ++i) {
    const sd::LongType elemIdx = i * blockDim.x + threadIdx.x;
    if (elemIdx < len) {
      const sd::LongType offset = shape::getIndexOffset(elemIdx, xzShapeInfo);
      z[offset] = sd::math::sd_exp<T, T>(x[offset] - max);
      shmem[threadIdx.x] =
          (threadIdx.x != 0)
              ? z[offset]
              : (z[offset] + temp);  // take into account sum element evaluated on previous iteration and stored in temp
    } else
      shmem[threadIdx.x] = 0;

    __syncthreads();

    for (int s = blockDim.x / 2; s > 0; s /= 2) {
      if (threadIdx.x < s) shmem[threadIdx.x] += shmem[threadIdx.x + s];
      __syncthreads();
    }

    temp = shmem[0];  // save sum calculated at current iteration
  }

  // ************ evaluate log(z[offset] / sum)  ************ //
  for (int i = 0; i < numOfIters; ++i) {
    const sd::LongType elemIdx = i * blockDim.x + threadIdx.x;
    if (elemIdx >= len) continue;
    const sd::LongType offset = shape::getIndexOffset(elemIdx, xzShapeInfo);
    z[offset] = sd::math::sd_log<T, T>(z[offset] / shmem[0]);
  }
}

///////////////////////////////////////////////////////////////////
template <typename T>
void logSoftMaxForVectorCudaLauncher(const cudaStream_t *stream, const void *vx, const sd::LongType *xzShapeInfo,
                                     void *vz) {
  logSoftMaxForVectorCuda<T><<<1, SD_CUDA_BLOCK_SIZE, 1024, *stream>>>(vx, xzShapeInfo, vz);
}

//////////////////////////////////////////////////////////////////////////
void logSoftmax(sd::LaunchContext *context, const NDArray &input, NDArray &output, const int dimension) {
  if (!input.isActualOnDeviceSide()) input.syncToDevice();
  const int rank = input.rankOf();

  if (input.isVector()) {
    if (rank == 1 || input.sizeAt(dimension) != 1) {
      BUILD_SINGLE_SELECTOR(
          input.dataType(), logSoftMaxForVectorCudaLauncher,
          (context->getCudaStream(), input.specialBuffer(), input.specialShapeInfo(), output.specialBuffer()),
          SD_FLOAT_TYPES);
      input.tickReadDevice();
    } else
      output = 0.;
  } else {
    std::vector<sd::LongType> dim = {static_cast<sd::LongType>(dimension)};
    auto maxAlongDim = const_cast<NDArray &>(input).reduceAlongDimension(reduce::Max, &dim, true);
    (input - maxAlongDim).applyTransform(transform::Exp, output);  // output contains exponents temporarily
    auto sumAlongDim = output.reduceAlongDimension(reduce::Sum, &dim, true);
    output /= sumAlongDim;
    output.applyTransform(transform::Log, output);
    input.tickReadDevice();
  }

  PointersManager manager(context, "helpers::logSoftmax");
  manager.synchronize();

  output.tickWriteDevice();
}

///////////////////////////////////////////////////////////////////
template <typename T>
void SD_KERNEL softMaxDerivForVectorCuda(const void *vx, const sd::LongType *xzShapeInfo, void *vz) {
  // logic of this kernel is based on assumption gridDim = 1

  const auto x = reinterpret_cast<const T *>(vx);
  auto z = reinterpret_cast<T *>(vz);

  __shared__ sd::LongType len;
  __shared__ int numOfIters;
  __shared__ T shmem[SD_CUDA_BLOCK_SIZE];

  if (threadIdx.x == 0) {
    len = shape::length(xzShapeInfo);
    numOfIters = (len + blockDim.x - 1) / blockDim.x;  // ceil (len / blockDim.x)
  }
  __syncthreads();

  T temp =
      -DataTypeUtils::max<T>();  // set start value to compare with at first iteration, FIXME: what if T is unsigned ??

  // ************ evaluate max element in input array x ************ //
  for (int i = 0; i < numOfIters; ++i) {
    const sd::LongType elemIdx = i * blockDim.x + threadIdx.x;
    if (elemIdx < len) {
      const sd::LongType offset = shape::getIndexOffset(elemIdx, xzShapeInfo);
      shmem[threadIdx.x] =
          (threadIdx.x != 0)
              ? x[offset]
              : sd::math::sd_max<T>(
                    x[offset],
                    temp);  // take into account max element evaluated on previous iteration and stored in temp
    } else
      shmem[threadIdx.x] = -DataTypeUtils::max<T>();  // FIXME: what if T is unsigned ??

    __syncthreads();

    for (int s = blockDim.x / 2; s > 0; s /= 2) {
      if (threadIdx.x < s) shmem[threadIdx.x] = sd::math::sd_max<T>(shmem[threadIdx.x], shmem[threadIdx.x + s]);
      __syncthreads();
    }

    temp = shmem[0];  // save max value calculated at current iteration
  }

  const T max = temp;
  temp = 0;

  // ************ evaluate value of exp(x[offset] - max) per each element, store it to shared memory shmem ************
  // // at the same evaluate sum of exponents, sum will be stored in shmem[0]
  for (int i = 0; i < numOfIters; ++i) {
    const sd::LongType elemIdx = i * blockDim.x + threadIdx.x;
    if (elemIdx < len) {
      const sd::LongType offset = shape::getIndexOffset(elemIdx, xzShapeInfo);
      z[offset] = sd::math::sd_exp<T, T>(x[offset] - max);
      shmem[threadIdx.x] =
          (threadIdx.x != 0)
              ? z[offset]
              : (z[offset] + temp);  // take into account sum element evaluated on previous iteration and stored in temp
    } else
      shmem[threadIdx.x] = 0;

    __syncthreads();

    for (int s = blockDim.x / 2; s > 0; s /= 2) {
      if (threadIdx.x < s) shmem[threadIdx.x] += shmem[threadIdx.x + s];
      __syncthreads();
    }

    temp = shmem[0];  // save sum calculated at current iteration
  }

  // ************ evaluate (z[offset] / sum) and derivative z[offset] = z[offset] * (1 - z[offset]) ************ //
  for (int i = 0; i < numOfIters; ++i) {
    const sd::LongType elemIdx = i * blockDim.x + threadIdx.x;
    if (elemIdx >= len) continue;
    const sd::LongType offset = shape::getIndexOffset(elemIdx, xzShapeInfo);
    z[offset] /= shmem[0];
    z[offset] *= (1.f - z[offset]);  // derivative
  }
}

///////////////////////////////////////////////////////////////////
template <typename T>
void softMaxDerivForVectorCudaLauncher(const cudaStream_t *stream, const void *vx, const sd::LongType *xzShapeInfo,
                                       void *vz) {
  softMaxDerivForVectorCuda<T><<<1, SD_CUDA_BLOCK_SIZE, 1024, *stream>>>(vx, xzShapeInfo, vz);
}

///////////////////////////////////////////////////////////////////
void softmaxDerivative(sd::LaunchContext *context, const NDArray &input, NDArray &output, const int dimension) {
  if (!input.isActualOnDeviceSide()) input.syncToDevice();
  const int rank = input.rankOf();
  sd::LongType temp;

  if (shape::isCommonVector(input.shapeInfo(), temp)) {
    BUILD_SINGLE_SELECTOR(
        input.dataType(), softMaxDerivForVectorCudaLauncher,
        (context->getCudaStream(), input.specialBuffer(), input.specialShapeInfo(), output.specialBuffer()),
        SD_FLOAT_TYPES);
    input.tickReadDevice();
  } else {
    std::vector<sd::LongType> dim = {static_cast<sd::LongType>(dimension)};
    auto maxAlongDim = const_cast<NDArray &>(input).reduceAlongDimension(reduce::Max, &dim, true);
    (input - maxAlongDim).applyTransform(transform::Exp, output);  // output contains exponents temporarily
    auto sumAlongDim = output.reduceAlongDimension(reduce::Sum, &dim, true);
    output /= sumAlongDim;
    output *= (1.f - output);  // derivative
    input.tickReadDevice();
  }

  PointersManager manager(context, "helpers::softmaxDerivative");
  manager.synchronize();

  output.tickWriteDevice();
}

template <typename T>
void thresholdRelu_(NDArray const &input, double threshold, NDArray &output) {
  auto routine = LAMBDA_T(_x, threshold) { return _x > (T)threshold ? _x : (T)0.f; };
  const_cast<NDArray &>(input).applyLambda(routine, output);
}

void thresholdRelu(sd::LaunchContext *context, NDArray const &input, double threshold, NDArray &output) {
  BUILD_SINGLE_SELECTOR(input.dataType(), thresholdRelu_, (input, threshold, output), SD_FLOAT_TYPES);
}

template <typename T>
void thresholdReluDerivative_(NDArray *input, double theta, NDArray *dLdO, NDArray *output) {
  auto derivative = LAMBDA_TT(_x, grO, theta) {
    if (_x > theta)
      return grO;
    else
      return static_cast<T>(0);
  };

  input->applyPairwiseLambda(*dLdO, derivative, *output);
}

void thresholdReluDerivative(sd::LaunchContext *context, NDArray *input, double threshold, NDArray *dLdO,
                             NDArray *output) {
  BUILD_SINGLE_SELECTOR(input->dataType(), thresholdReluDerivative_, (input, threshold, dLdO, output), SD_FLOAT_TYPES);
}

}  // namespace helpers
}  // namespace ops
}  // namespace sd
