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
//  @author raver119@gmail.com
//

#ifndef DEV_TESTS_SCATTER_H
#define DEV_TESTS_SCATTER_H
#include <array/NDArray.h>

namespace sd {
namespace ops {
namespace helpers {
SD_LIB_HIDDEN void scatter(LaunchContext* context, pairwise::Ops op, const NDArray& indices, const NDArray& updates,
                           NDArray& output, const bool lock);

SD_LIB_HIDDEN void scatterND(LaunchContext* context, pairwise::Ops op, const NDArray& indices,
                             const NDArray& updates, NDArray& output, const bool lock);

SD_LIB_HIDDEN void scatterForLoss(LaunchContext* context, const NDArray& indices, NDArray& updates, NDArray& output,
                                  const bool calcGrad);

SD_LIB_HIDDEN LongType checkIndices(LaunchContext* context, const NDArray& indices, const NDArray& output,
                                        const int axis = -1);
}  // namespace helpers
}  // namespace ops
}  // namespace sd

#endif  // DEV_TESTS_SCATTER_H
