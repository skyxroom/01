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

package org.nd4j.linalg.api.ops.random.impl;

import org.nd4j.autodiff.samediff.SDVariable;
import org.nd4j.autodiff.samediff.SameDiff;
import org.nd4j.linalg.api.ndarray.INDArray;
import org.nd4j.linalg.api.ops.DynamicCustomOp;
import org.nd4j.linalg.api.ops.OpContext;
import org.nd4j.linalg.api.shape.LongShapeDescriptor;

import java.util.Arrays;
import java.util.List;

public class CustomDropOut extends DynamicCustomOp {

    private boolean inverted;
    private long seed;
    private double probabilityValue;

    public CustomDropOut() {
    }

    public CustomDropOut(INDArray[] inputs, boolean inverted, long seed, double probabilityValue) {
        super(inputs, null);
        this.inverted = inverted;
        this.seed = seed;
        this.probabilityValue = probabilityValue;
        addArgs();
    }

    public CustomDropOut(SameDiff sameDiff, SDVariable[] args, boolean inverted, long seed, double probabilityValue) {
        super(sameDiff, args);
        this.inverted = inverted;
        this.seed = seed;
        this.probabilityValue = probabilityValue;
    }

    public CustomDropOut(SameDiff sd, SDVariable input, boolean inverted, int seed, double probabilityValue) {
        this(sd,new SDVariable[]{input},inverted,seed,probabilityValue);
    }

    public CustomDropOut(INDArray input, boolean inverted, int seed, double probabilityValue) {
        this(new INDArray[]{input},inverted,seed,probabilityValue);
    }

    private void addArgs() {
        addBArgument(inverted);
        addTArgument(probabilityValue);
        addIArgument(seed);
    }


    @Override
    public String opName() {
        return "dropout";
    }


    @Override
    public List<LongShapeDescriptor> calculateOutputShape(OpContext oc) {
        INDArray input = oc.getInputArray(0);
        return Arrays.asList(input.shapeDescriptor());
    }

    @Override
    public List<SDVariable> doDiff(List<SDVariable> f1) {
        return Arrays.asList(new CustomDropOut(sameDiff, new SDVariable[]{arg(0), f1.get(0)}, inverted, seed, probabilityValue).outputVariables());
    }
}
