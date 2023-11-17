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
// @author raver119@gmail.com
//
#include <ops/specials_cuda.h>

//////////////////////////////////////////////////////////////////////////
template <typename X, typename Y>
SD_KERNEL void execOesTadKernelKey(void *vx, sd::LongType const *xShapeInfo, void *vy, sd::LongType const *yShapeInfo,
                                   long long int *dimension, long long int dimensionLength, sd::LongType const *tadShapeInfo,
                                   sd::LongType const *tadOffsets, bool descending) {
  auto x = static_cast<X *>(vx);
  auto y = static_cast<Y *>(vy);

  __shared__ int xLength;
  __shared__ int xTadLength;
  __shared__ int numTads;
  if (threadIdx.x == 0) {
    xLength = shape::length(xShapeInfo);
    xTadLength = shape::length(tadShapeInfo);
    numTads = xLength / xTadLength;
  }
  __syncthreads();

  for (int r = blockIdx.x; r < numTads; r += gridDim.x) {
    auto dx = x + tadOffsets[r];
    auto dy = y + tadOffsets[r];

    // this is general loop, we go uncached
    int iterations = xTadLength;

    for (int i = 0; i < iterations; i++) {
      if (i % 2 == 0) {
        for (int tid = threadIdx.x; tid < xTadLength; tid += blockDim.x) {
          auto top = 2 * tid + 1;
          if (top < xTadLength) {
            auto t0 = shape::getIndexOffset(top - 1, tadShapeInfo);
            auto t1 = shape::getIndexOffset(top, tadShapeInfo);

            if (!descending == (dx[t0] > dx[t1])) {
              X dt0 = dx[t0];
              dx[t0] = dx[t1];
              dx[t1] = dt0;

              Y dy0 = dy[t0];
              dy[t0] = dy[t1];
              dy[t1] = dy0;
            }
          }
        }
      } else {
        for (int tid = threadIdx.x; tid < xTadLength; tid += blockDim.x) {
          auto top = 2 * tid + 2;
          if (top < xTadLength) {
            auto t0 = shape::getIndexOffset(top - 1, tadShapeInfo);
            auto t1 = shape::getIndexOffset(top, tadShapeInfo);

            if (!descending == (dx[t0] > dx[t1])) {
              X dt0 = dx[t0];
              dx[t0] = dx[t1];
              dx[t1] = dt0;

              Y dy0 = dy[t0];
              dy[t0] = dy[t1];
              dy[t1] = dy0;
            }
          }
        }
      }
      __syncthreads();
    }
  }
}

//////////////////////////////////////////////////////////////////////////
template <typename T>
SD_KERNEL void execOesTadKernel(void *vx, sd::LongType const *xShapeInfo,sd::LongType *dimension,
                                sd::LongType dimensionLength,
                                sd::LongType const *tadShapeInfo, sd::LongType const *tadOffsets, bool descending) {
  auto x = static_cast<T *>(vx);
  const int sharedSize = 32768;

  __shared__ int xLength;
  __shared__ int xTadLength;
  __shared__ int numTads;
  __shared__ T *shmem;
  __shared__ bool cached;
  if (threadIdx.x == 0) {
    xLength = shape::length(xShapeInfo);
    xTadLength = shape::length(tadShapeInfo);
    numTads = xLength / xTadLength;

    extern __shared__ unsigned char shrd[];
    shmem = (T *)shrd;

    cached = xTadLength <= (sharedSize / sizeof(T));
  }
  __syncthreads();

  for (int r = blockIdx.x; r < numTads; r += gridDim.x) {
    auto dx = x + tadOffsets[r];

    // this is general loop, we go uncached
    int iterations = xTadLength;
    if (cached) {
      for (int tid = threadIdx.x; tid < xTadLength; tid += blockDim.x) {
        auto t0 = shape::getIndexOffset(tid, tadShapeInfo);
        shmem[tid] = dx[t0];
      }

      __syncthreads();
      dx = shmem;
    }

    for (int i = 0; i < iterations; i++) {
      if (i % 2 == 0) {
        for (int tid = threadIdx.x; tid < xTadLength; tid += blockDim.x) {
          auto top = 2 * tid + 1;
          if (top < xTadLength) {
            auto t0 = cached ? top - 1 : shape::getIndexOffset(top - 1, tadShapeInfo);
            auto t1 = cached ? top : shape::getIndexOffset(top, tadShapeInfo);

            if (!descending == (dx[t0] > dx[t1])) {
              T dt0 = dx[t0];
              dx[t0] = dx[t1];
              dx[t1] = dt0;
            }
          }
        }
      } else {
        for (int tid = threadIdx.x; tid < xTadLength; tid += blockDim.x) {
          auto top = 2 * tid + 2;
          if (top < xTadLength) {
            auto t0 = cached ? top - 1 : shape::getIndexOffset(top - 1, tadShapeInfo);
            auto t1 = cached ? top : shape::getIndexOffset(top, tadShapeInfo);

            if (!descending == (dx[t0] > dx[t1])) {
              T dt0 = dx[t0];
              dx[t0] = dx[t1];
              dx[t1] = dt0;
            }
          }
        }
      }
      __syncthreads();
    }

    if (cached) {
      dx = x + tadOffsets[r];
      for (int tid = threadIdx.x; tid < xTadLength; tid += blockDim.x) {
        auto t0 = shape::getIndexOffset(tid, tadShapeInfo);
        dx[t0] = shmem[tid];
      }
    }
  }
}

//////////////////////////////////////////////////////////////////////////
template <typename T>
SD_HOST void oesTadGeneric(dim3 &launchDims, cudaStream_t *stream, void *vx, sd::LongType const *xShapeInfo,
                           sd::LongType *dimension, sd::LongType dimensionLength, sd::LongType const *tadShapeInfo,
                           sd::LongType const *tadOffsets, bool descending) {
  execOesTadKernel<T><<<launchDims.y, launchDims.x, launchDims.z, *stream>>>(vx, xShapeInfo, dimension, dimensionLength,
                                                                             tadShapeInfo, tadOffsets, descending);

  sd::DebugHelper::checkErrorCode(stream, "execOesTadKernel  failed");

}

template <typename X, typename Y>
SD_HOST void oesTadGenericKey(dim3 &launchDims, cudaStream_t *stream, void *vx, sd::LongType const *xShapeInfo,
                              void *vy, sd::LongType const *yShapeInfo, sd::LongType *dimension,
                              sd::LongType dimensionLength,
                              sd::LongType const *tadShapeInfo, sd::LongType const *tadOffsets, bool descending) {
  execOesTadKernelKey<X, Y><<<launchDims.y, launchDims.x, launchDims.z, *stream>>>(
      vx, xShapeInfo, vy, yShapeInfo, dimension, dimensionLength, tadShapeInfo, tadOffsets, descending);
  sd::DebugHelper::checkErrorCode(stream, "execOesTadKernelKey  failed");

}

BUILD_SINGLE_TEMPLATE(template void oesTadGeneric,
                      (dim3 & launchDims, cudaStream_t *stream, void *vx, sd::LongType const *xShapeInfo,
                       sd::LongType *dimension, sd::LongType dimensionLength, sd::LongType const *tadShapeInfo,
                       sd::LongType const *tadOffsets, bool descending),
                      SD_COMMON_TYPES);
BUILD_DOUBLE_TEMPLATE(template void oesTadGenericKey,
                      (dim3 & launchDims, cudaStream_t *stream, void *vx, sd::LongType const *xShapeInfo, void *vy,
                       sd::LongType const *yShapeInfo, sd::LongType *dimension, sd::LongType dimensionLength,
                       sd::LongType const *tadShapeInfo, sd::LongType const *tadOffsets, bool descending),
                      SD_COMMON_TYPES, SD_COMMON_TYPES);
