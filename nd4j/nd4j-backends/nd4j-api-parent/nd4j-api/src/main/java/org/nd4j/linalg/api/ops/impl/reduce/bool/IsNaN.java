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

package org.nd4j.linalg.api.ops.impl.reduce.bool;

import org.nd4j.autodiff.samediff.SDVariable;
import org.nd4j.autodiff.samediff.SameDiff;
import org.nd4j.linalg.api.ndarray.INDArray;
import org.nd4j.linalg.api.ops.BaseReduceBoolOp;

import java.util.Collections;
import java.util.List;

public class IsNaN extends BaseReduceBoolOp {
    public IsNaN(SameDiff sameDiff, SDVariable i_v, long[] dims) {
        super(sameDiff, i_v, dims);
    }

    public IsNaN(INDArray x, INDArray z, boolean keepDims, long[] dimensions) {
        super(x, z, keepDims, dimensions);
    }

    public IsNaN(INDArray x, long... dimensions) {
        super(x, dimensions);
    }

    public IsNaN(INDArray x, boolean keepDims, long... dimensions) {
        super(x, keepDims, dimensions);
    }

    public IsNaN(INDArray x, INDArray z, long... dimensions) {
        super(x, z, dimensions);
    }

    public IsNaN(INDArray x, INDArray y, INDArray z, long... dimensions) {
        super(x, y, z, dimensions);
    }

    public IsNaN(SameDiff sameDiff) {
        super(sameDiff);
    }

    public IsNaN(SameDiff sameDiff, SDVariable i_v, SDVariable i_v2, SDVariable dimensions) {
        super(sameDiff, i_v, i_v2, dimensions);
    }

    public IsNaN(SameDiff sameDiff, SDVariable i_v, long[] dims, boolean keepDims) {
        super(sameDiff, i_v, dims, keepDims);
    }

    public IsNaN(SameDiff sameDiff, SDVariable i_v, SDVariable i_v2, long[] dimensions, boolean keepDims) {
        super(sameDiff, i_v, i_v2, dimensions, keepDims);
    }

    public IsNaN(SameDiff sameDiff, SDVariable i_v) {
        super(sameDiff, i_v);
    }


    public IsNaN() {}

    public IsNaN(INDArray x, INDArray y, INDArray z, boolean keepDims, long[] dimensions) {
        super(x, y, z, keepDims, dimensions);
    }

    public IsNaN(INDArray x, INDArray z) {
        super(x, z, false, null);
    }

    public IsNaN(INDArray x) {
        super(x);
    }

    public IsNaN(SameDiff sameDiff, SDVariable i_v, SDVariable i_v2, long[] dimensions) {
        super(sameDiff, i_v, i_v2, dimensions);
    }

    public IsNaN(SameDiff sameDiff, SDVariable i_v, boolean keepDims) {
        super(sameDiff, i_v, keepDims);
    }

    public IsNaN(SameDiff sameDiff, SDVariable i_v, SDVariable dimensions, boolean keepDims) {
        super(sameDiff, i_v, dimensions, keepDims);
    }

    public IsNaN(SameDiff sameDiff, SDVariable i_v, SDVariable i_v2) {
        super(sameDiff, i_v, i_v2);
    }

    @Override
    public int opNum() {
        return 4;
    }

    @Override
    public String opName() {
        return "hasnan";
    }

    @Override
    public String onnxName() {
        return "hasNaNs";
    }


    @Override
    public List<SDVariable> doDiff(List<SDVariable> i_v) {
        return Collections.singletonList(sameDiff.zerosLike(arg()));
    }

    @Override
    public boolean emptyValue() {
        return false;
    }
}
