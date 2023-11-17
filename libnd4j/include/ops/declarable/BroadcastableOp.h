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
// Created by raver on 6/6/2018.
//

#ifndef LIBND4J_BROADCASTABLEOP_H
#define LIBND4J_BROADCASTABLEOP_H

#include <ops/declarable/DeclarableCustomOp.h> 

namespace sd {
namespace ops {
class SD_LIB_EXPORT BroadcastableOp : public DeclarableCustomOp {
 protected:
  Status validateAndExecute(Context &block) override = 0;

 public:
  BroadcastableOp(const char *name, int numTArgs, int numIArgs);

  ShapeList *calculateOutputShape(ShapeList *inputShape, Context &block) override;
};
}  // namespace ops
}  // namespace sd

#endif  // LIBND4J_BROADCASTABLEOP_H
