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

#ifndef SD_PLATFORMHELPER_H
#define SD_PLATFORMHELPER_H
#include <execution/Engine.h>
#include <graph/Context.h>
#include <helpers/ShapeUtils.h>
#include <system/RequirementsHelper.h>

#include <string>

namespace sd {
namespace ops {
namespace platforms {
/**
 * This abstract class defines methods used by platform-specific helpers implementations
 */
class SD_LIB_EXPORT PlatformHelper {
 protected:
  // target engine for this impl
  samediff::Engine _engine;

  // name of the operation this helper is built for
  std::string _name;

  // hash of the operation this helper is built for
  LongType _hash;

 public:
  PlatformHelper(const char *name, samediff::Engine engine);

  ~PlatformHelper() = default;

  std::string name();

  samediff::Engine engine();

  LongType hash();

  /**
   * This method checks, if given helper can be used with given input/output/configuration options
   *
   * @param context
   * @return
   */
  virtual bool isUsable(graph::Context &context) = 0;

  /**
   * This method invokes helper. Typically this method replaces actual op execution
   *
   * @param context
   * @return
   */
  virtual Status invokeHelper(graph::Context &context) = 0;

  /**
   * Helper method, needed for compatibility with DeclarableOp macros
   * @param ctx
   * @param inputId
   * @return
   */
  NDArray *getZ(graph::Context &ctx, int inputId);

  /**
   * Helper method, needed for compatibility with DeclarableOp macros
   * @param ctx
   * @param inputId
   * @return
   */
  NDArray *getNullifiedZ(graph::Context &ctx, int inputId);
};
}  // namespace platforms
}  // namespace ops
}  // namespace sd

#endif  // SD_PLATFORMHELPER_H
