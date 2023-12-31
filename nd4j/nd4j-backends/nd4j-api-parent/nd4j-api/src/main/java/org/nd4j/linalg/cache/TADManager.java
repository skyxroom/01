/*
 *  ******************************************************************************
 *  *
 *  *
 *  * This program and the accompanying materials are made available under the
 *  * terms of the Apache License, Version 2.0 which is available at
 *  * https://www.apache.org/licenses/LICENSE-2.0.
 *  *
 *  *  See the NOTICE file distributed with this work for additional
 *  *  information regarding copyright ownership.
 *  * Unless required by applicable law or agreed to in writing, software
 *  * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 *  * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
 *  * License for the specific language governing permissions and limitations
 *  * under the License.
 *  *
 *  * SPDX-License-Identifier: Apache-2.0
 *  *****************************************************************************
 */

package org.nd4j.linalg.cache;

import org.nd4j.common.primitives.Pair;
import org.nd4j.linalg.api.buffer.DataBuffer;
import org.nd4j.linalg.api.ndarray.INDArray;

public interface TADManager {

    /**
     * This method returns TAD shapeInfo and all offsets
     * for specified tensor and dimensions.
     *
     * @param array Tensor for TAD precalculation
     * @param dimension
     * @return
     */
    Pair<DataBuffer, DataBuffer> getTADOnlyShapeInfo(INDArray array, long... dimension);

    /**
     * This method removes all cached shape buffers
     */
    void purgeBuffers();

    /**
     * This method returns memory used for cache, in bytes
     * 
     * @return
     */
    long getCachedBytes();
}
