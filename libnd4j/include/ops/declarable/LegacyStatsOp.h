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
// Created by raver119 on 17.10.2017.
//

#ifndef LIBND4J_LEGACYSTATSOP_H
#define LIBND4J_LEGACYSTATSOP_H
#include <ops/declarable/LegacyOp.h>

namespace sd {
namespace ops {
/**
 *   This class provides wrapper for SummaryStats operations: Variance and Standard Deviation
 */
class SD_LIB_EXPORT LegacyStatsOp : public LegacyOp {
 protected:
  Status validateAndExecute(sd::graph::Context& block) override;

 public:
  LegacyStatsOp();
  LegacyStatsOp(int opNum);

  ShapeList* calculateOutputShape(ShapeList* inputShape, Context& block) override;
  LegacyOp* clone() override;
};
}  // namespace ops
}  // namespace sd

#endif  // LIBND4J_LEGACYSTATSOP_H
