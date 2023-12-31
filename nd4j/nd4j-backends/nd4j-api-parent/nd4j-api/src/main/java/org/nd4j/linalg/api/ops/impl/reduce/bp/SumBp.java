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

package org.nd4j.linalg.api.ops.impl.reduce.bp;

import org.nd4j.autodiff.samediff.SDVariable;
import org.nd4j.autodiff.samediff.SameDiff;
import org.nd4j.linalg.api.ndarray.INDArray;


public class SumBp extends BaseReductionBp {

    public SumBp(SameDiff sameDiff, SDVariable origInput, SDVariable gradAtOutput, boolean keepDims, long... dimensions) {
        super(sameDiff, origInput, gradAtOutput, keepDims, dimensions);
        addArgs();
    }

    public SumBp(INDArray origInput, INDArray gradAtOutput, INDArray output, boolean keepDims, INDArray dimensions){
        super(origInput, gradAtOutput, output, keepDims, dimensions);
        addArgs();
    }


    public SumBp(SameDiff sameDiff, SDVariable origInput, SDVariable gradAtOutput, boolean keepDims, SDVariable dimensions) {
        super(sameDiff, origInput, gradAtOutput, keepDims, dimensions);
        addArgs();
    }


    public SumBp(){}

    public SumBp(INDArray preReduceInput, INDArray dLdOut, INDArray dLdIn, boolean keepDims) {
        super(preReduceInput,dLdOut,dLdIn,keepDims);
        addArgs();
    }


    @Override
    public String opName() {
        return "reduce_sum_bp";
    }
}
