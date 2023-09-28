/*
 *  ******************************************************************************
 *  *
 *  *
 *  * This program and the accompanying materials are made available under the
 *  * terms of the Apache License, Version 2.0 which is available at
 *  * https://www.apache.org/licenses/LICENSE-2.0.
 *  *
 *  * See the NOTICE file distributed with this work for additional
 *  * information regarding copyright ownership.
 *  * Unless required by applicable law or agreed to in writing, software
 *  * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 *  * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
 *  * License for the specific language governing permissions and limitations
 *  * under the License.
 *  *
 *  * SPDX-License-Identifier: Apache-2.0
 *  *****************************************************************************
 */

//
//  @author GS <sgazeos@gmail.com>
//
#include <array/NDArray.h>
#include <execution/Threads.h>
#include <helpers/ConstantTadHelper.h>
#include <system/op_boilerplate.h>

#include "../triangular_solve.h"
#include "execution/cuda/LaunchDims.h"

namespace sd {
namespace ops {
namespace helpers {



/*
 * lower triangular process for system of linear equations
 * x_1 = b_1/a_1,1
 * x_2 = (b_2 - a_2,1 * x_1) / a_2,2
 * x_3 = (b_3 - a_3,1 * x_1 - a_3,2 * x_2) / a_3,3
 * ...
 * x_M = (b_M - a_M,1 * x_1 - ... a_M,M-1 * x_M-1)/ a_M,M
 *
 * output == x
 * a == leftInput
 * b == rightInput
 *
 * */
template <typename T>
static void lowerTriangularSolve(sd::LaunchContext* context, NDArray const* leftInput, NDArray const* rightInput,
                                 bool const unitsOnDiag, NDArray* output) {
  auto rows = leftInput->rows();
  auto cols = rightInput->columns();
  for (sd::LongType r = 0; r < rows; r++) {
    for (sd::LongType j = 0; j < cols; j++) {
      auto sum = rightInput->t<T>(r, j);
      for (sd::LongType c = 0; c < r; c++) {
        sum -= leftInput->t<T>(r, c) * output->t<T>(c, j);
      }
      output->r<T>(r, j) = unitsOnDiag ? sum : sum / leftInput->t<T>(r, r);
    }
  }
}

/*
 * upper triangular process for system of linear equations
 * x_M = b_M/a_M,M
 * x_M-1 = (b_M-1 - a_M-1,M-2 * x_M) / a_M-1,M-1
 * x_M-2 = (b_M-2 - a_M-2,M-3 * x_M-2 - a_M-2,M-1 * x_M) / a_3,3
 * ...
 * x_1 = (b_1 - a_1,2 * x_2 - ... a_1,M * x_M)/ a_1,1
 *
 * output == x
 * a == leftInput
 * b == rightInput
 *
 * */

template <typename T>
static void upperTriangularSolve(sd::LaunchContext* context, NDArray const* leftInput, NDArray const* rightInput,
                                 bool const unitsOnDiag, NDArray* output) {
  auto rows = leftInput->rows();
  auto cols = rightInput->columns();
  for (sd::LongType r = rows; r >= 0; r--) {
    for (sd::LongType j = 0; j < cols; j++) {
      auto sum = rightInput->t<T>(r - 1, j);
      for (sd::LongType c = r; c < rows; c++) {
        sum -= leftInput->t<T>(r - 1, c) * output->t<T>(c, j);
      }
      output->p(r - 1, j, unitsOnDiag ? sum : sum / leftInput->t<T>(r - 1, r - 1));
    }
  }
}

template <typename T>
static sd::Status triangularSolveFunctor_(sd::LaunchContext* context, NDArray* leftInput, NDArray* rightInput,
                                          bool lower, bool adjoint, NDArray* output) {


  auto leftPart = leftInput->allTensorsAlongDimension({-2, -1});
  auto rightPart = rightInput->allTensorsAlongDimension({-2, -1});
  auto outputPart = output->allTensorsAlongDimension({-2, -1});
  auto batchLoop = PRAGMA_THREADS_FOR {
    for (auto i = start; i < stop; i++) {
      if(i >= rightPart.size() || i > outputPart.size())
        break;
      if (lower) {
        lowerTriangularSolve<T>(context, leftPart[i], rightPart[i], false, outputPart[i]);
      } else {
        upperTriangularSolve<T>(context, leftPart[i], rightPart[i], false, outputPart[i]);
      }
    }
  };

  samediff::Threads::parallel_tad(batchLoop, 0, leftPart.size(), 1);

  return sd::Status::OK;
}
template <typename T>
static void adjointTriangularMatrix_(sd::LaunchContext* context, NDArray const* input, bool const lower,
                                     NDArray* output) {
  auto inputPart = input->allTensorsAlongDimension({-2, -1});
  auto outputPart = output->allTensorsAlongDimension({-2, -1});
  auto cols = input->sizeAt(-1);
  auto rows = input->sizeAt(-2);

  auto batchLoop = PRAGMA_THREADS_FOR {
    for (auto batch = start; batch < stop; batch++) {
      if (!lower) {
        for (sd::LongType r = 0; r < rows; r++) {
          for (sd::LongType c = 0; c <= r; c++) {
            outputPart[batch]->r<T>(r, c) = inputPart[batch]->t<T>(c, r);
          }
        }
      } else {
        for (sd::LongType r = 0; r < rows; r++) {
          for (sd::LongType c = r; c < cols; c++) {
            outputPart[batch]->r<T>(r, c) = inputPart[batch]->t<T>(c, r);
          }
        }
      }
    }
  };
  samediff::Threads::parallel_tad(batchLoop, 0, inputPart.size(), 1);
}

///  triangularSolve2D - 2D implementation of triangularSolveFunctor
/// \tparam T - type of NDArray output
/// \param context - launch context pointer
/// \param leftInput  - T matrix of equation Tx = b
/// \param rightInput  - b vector of equation Tx = b
/// \param lower - lower or upper triangular matrix
/// \param unitsOnDiag - solve for case when only units (1.0) on diagonal is assumed
/// \param output - output vector (x on equation Tx = b)
///
template <typename T>
void triangularSolve2D(sd::LaunchContext* context, const NDArray& leftInput, const NDArray& rightInput,
                       bool const lower, bool const unitsOnDiag, NDArray& output) {
  triangularSolveFunctor_<T>(context, const_cast<NDArray*>(&leftInput), const_cast<NDArray*>(&rightInput), lower,
                             unitsOnDiag, &output);


}
BUILD_SINGLE_TEMPLATE(template void triangularSolve2D,
                      (sd::LaunchContext * context, NDArray const& leftInput, NDArray const& rightInput,
                          bool const lower, bool const unitsOnDiag, NDArray& output),
                      SD_FLOAT_TYPES);

sd::Status triangularSolveFunctor(sd::LaunchContext* context, NDArray* leftInput, NDArray* rightInput, bool lower,
                                  bool unitsOnDiag, NDArray* output) {
  BUILD_SINGLE_SELECTOR(leftInput->dataType(), return triangularSolveFunctor_,
                        (context, leftInput, rightInput, lower, unitsOnDiag, output), SD_FLOAT_NATIVE);
}

template <typename T>
static SD_KERNEL void upperAdjointKernel(T const* input, T* output, sd::LongType batchSize, sd::LongType rows,
                                         sd::LongType columns, sd::LongType const* inputTads,
                                         sd::LongType const* inputOffsets, sd::LongType const* outputTads,
                                         sd::LongType const* outputOffsets) {
  for (auto b = blockIdx.x; b < batchSize; b += gridDim.x) {
    auto inputPart = input + inputOffsets[b];
    auto outputPart = output + outputOffsets[b];
    for (auto r = threadIdx.x; r < rows; r += blockDim.x) {
      for (auto c = threadIdx.y; c <= r; c += blockDim.y) {
        sd::LongType zPos[] = {r, c};
        sd::LongType xPos[] = {c, r};
        auto zIndex = shape::getOffset(outputTads, zPos);
        auto xIndex = shape::getOffset(inputTads, xPos);
        outputPart[zIndex] = inputPart[xIndex];
      }
    }
  }
}

template <typename T>
static SD_KERNEL void lowerAdjointKernel(T const* input, T* output, sd::LongType batchSize, sd::LongType rows,
                                         sd::LongType columns, sd::LongType const* inputTads,
                                         sd::LongType const* inputOffsets, sd::LongType const* outputTads,
                                         sd::LongType const* outputOffsets) {
  for (auto b = blockIdx.x; b < batchSize; b += gridDim.x) {
    auto inputPart = input + inputOffsets[b];
    auto outputPart = output + outputOffsets[b];
    for (auto r = threadIdx.x; r < rows; r += blockDim.x) {
      for (auto c = r + threadIdx.y; c < columns; c += blockDim.y) {
        sd::LongType zPos[] = {r, c};
        sd::LongType xPos[] = {c, r};
        auto zIndex = shape::getOffset(outputTads, zPos);
        auto xIndex = shape::getOffset(inputTads, xPos);
        outputPart[zIndex] = inputPart[xIndex];
      }
    }
  }
}



void adjointMatrix(sd::LaunchContext* context, NDArray const* input, bool const lower, NDArray* output) {
  BUILD_SINGLE_SELECTOR(input->dataType(), adjointTriangularMatrix_, (context, input, lower, output), SD_FLOAT_NATIVE);
}


}  // namespace helpers
}  // namespace ops
}  // namespace sd
