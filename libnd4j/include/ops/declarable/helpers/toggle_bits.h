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
#include <ops/declarable/helpers/helpers.h>

#ifndef DEV_TESTS_TOGGLE_BITS_H
#define DEV_TESTS_TOGGLE_BITS_H

namespace sd {
namespace ops {
namespace helpers {
template <typename T>
static void toggle_bits__(LaunchContext* context, NDArray& in, NDArray& out);

SD_LIB_HIDDEN void __toggle_bits(LaunchContext* context, NDArray& in, NDArray& out);
}  // namespace helpers
}  // namespace ops
}  // namespace sd

#endif  // DEV_TESTS_TOGGLE_BITS_H
