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

#include <system/op_boilerplate.h>
#if NOT_EXCLUDED(OP_broadcastgradientargs)

#include <ops/declarable/CustomOperations.h>

namespace sd {
namespace ops {
/**
 * PLEASE NOTE: This op is disabled atm, and reserved for future releases.
 */
OP_IMPL(broadcastgradientargs, 2, 2, true) {
  sd_printf("BroadcastGradientArgs: Not implemented yet\n", "");

  return Status::KERNEL_FAILURE;
}
DECLARE_SYN(BroadcastGradientArgs, broadcastgradientargs);

DECLARE_TYPES(broadcastgradientargs) { getOpDescriptor()->setAllowedInputTypes(ANY); }
}  // namespace ops
}  // namespace sd

#endif
