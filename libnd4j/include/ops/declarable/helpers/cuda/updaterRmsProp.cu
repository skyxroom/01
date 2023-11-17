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
// @author Oleh Semeniv (oleg.semeniv@gmail.com)
//
#include <helpers/PointersManager.h>
#include <math/platformmath.h>
#include <math/templatemath.h>
#include <ops/declarable/helpers/updatersHelpers.h>
#include <system/op_boilerplate.h>

#include "execution/cuda/LaunchDims.h"
#include "helpers/DebugHelper.h"

namespace sd {
namespace ops {
namespace helpers {

///////////////////////////////////////////////////////////////////
template <typename T>
SD_KERNEL void rmsPropUpdaterCuda(const void *vx, const LongType *xShapeInfo, const void *vin,
                                  const LongType *inShapeInfo, void *vz, const LongType *zShapeInfo, void *vst,
                                  const LongType *stShapeInfo, const T lr, const T rmsDecay, const T epsilon) {
  const auto x = reinterpret_cast<const T *>(vx);
  const auto init = reinterpret_cast<const T *>(vin);

  auto up = reinterpret_cast<T *>(vz);
  auto st = reinterpret_cast<T *>(vst);

  __shared__ LongType xLen;
  __shared__ bool bEWS, bOrdering, bXZsame, bXInSame, bXStSame;

  if (threadIdx.x == 0) {
    xLen = shape::length(xShapeInfo);

    bEWS = 1 == shape::elementWiseStride(xShapeInfo) && 1 == shape::elementWiseStride(zShapeInfo) &&
           1 == shape::elementWiseStride(stShapeInfo) && 1 == shape::elementWiseStride(inShapeInfo);

    bOrdering = shape::order(zShapeInfo) == shape::order(xShapeInfo) &&
                shape::order(xShapeInfo) == shape::order(stShapeInfo) &&
                shape::order(xShapeInfo) == shape::order(inShapeInfo);
    bXZsame = shape::haveSameShapeAndStrides(xShapeInfo, zShapeInfo);
    bXInSame = shape::haveSameShapeAndStrides(xShapeInfo, inShapeInfo);
    bXStSame = shape::haveSameShapeAndStrides(xShapeInfo, stShapeInfo);
  }
  __syncthreads();

  LongType coords[SD_MAX_RANK];

  for (LongType i = blockIdx.x * blockDim.x + threadIdx.x; i < xLen; i += gridDim.x * blockDim.x) {
    LongType xOffset = i, zOffset = i, initOffset = i, stOffset = i;

    if (!bEWS || !bOrdering) {
      shape::index2coords(i, xShapeInfo, coords);
      xOffset = shape::getOffset(xShapeInfo, coords);
      zOffset = bXZsame ? xOffset : shape::getOffset(zShapeInfo, coords);
      initOffset = bXInSame ? xOffset : shape::getOffset(inShapeInfo, coords);
      stOffset = bXStSame ? xOffset : shape::getOffset(stShapeInfo, coords);
    }

    st[stOffset] = init[initOffset] * rmsDecay + x[xOffset] * x[xOffset] * (1 - rmsDecay);
    up[zOffset] = (lr * x[xOffset]) / (math::sd_sqrt<T, T>(st[stOffset]) + epsilon);
  }
}

///////////////////////////////////////////////////////////////////
template <typename T>
void rmsPropUpdaterCudaLauncher(const int blocksPerGrid, const int threadsPerBlock, const int sharedMemory,
                                const cudaStream_t *stream, const void *vx, const LongType *xShapeInfo,
                                const void *vin, const LongType *inShapeInfo, void *vz,
                                const LongType *zShapeInfo, void *vst, const LongType *stShapeInfo,
                                const double dLr, const double dRmsDecay, const double dEpsilon) {
  const T lr = static_cast<T>(dLr);
  const T rmsDecay = static_cast<T>(dRmsDecay);
  T epsilon = static_cast<T>(dEpsilon);
  //fp16 to prevent underflow
  if(epsilon == 0.0) {
    epsilon = static_cast<T>(1e-7);
  }
  rmsPropUpdaterCuda<T><<<blocksPerGrid, threadsPerBlock, sharedMemory, *stream>>>(
      vx, xShapeInfo, vin, inShapeInfo, vz, zShapeInfo, vst, stShapeInfo, lr, rmsDecay, epsilon);
  sd::DebugHelper::checkErrorCode(const_cast<cudaStream_t *>(stream), "rmsPropUpdaterCudaLauncher failed");

}

///////////////////////////////////////////////////////////////////
void updaterRmsProp(LaunchContext *context, const NDArray &gradient, const NDArray &initState, NDArray &update,
                    NDArray &stateG, const double dLr, const double dRmsDecay, const double dEpsilon) {
  PointersManager manager(context, "rmsPropUpdater");

  dim3 launchDims = updaterDims(gradient.lengthOf());
  NDArray::prepareSpecialUse({&update, &stateG}, {&gradient, &initState});

  BUILD_SINGLE_SELECTOR(
      gradient.dataType(), rmsPropUpdaterCudaLauncher,
      (launchDims.y, launchDims.x,launchDims.z, context->getCudaStream(), gradient.specialBuffer(), gradient.specialShapeInfo(),
       initState.specialBuffer(), initState.specialShapeInfo(), update.specialBuffer(), update.specialShapeInfo(),
       stateG.specialBuffer(), stateG.specialShapeInfo(), dLr, dRmsDecay, dEpsilon),
      SD_FLOAT_TYPES);

  NDArray::registerSpecialUse({&update, &stateG}, {&gradient, &initState});

  manager.synchronize();
}

}  // namespace helpers
}  // namespace ops
}  // namespace sd
