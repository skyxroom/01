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
package org.nd4j.autodiff.samediff.internal.memory;

import java.util.HashSet;
import java.util.Set;

import org.nd4j.autodiff.samediff.config.SDValue;
import org.nd4j.autodiff.samediff.internal.AbstractDependencyTracker;
import org.nd4j.autodiff.samediff.internal.IDependencyMap;

public class HashDependencyTracker<T extends SDValue, D> extends AbstractDependencyTracker<T, D> {

    @Override
    protected IDependencyMap<T, D> newTMap() {
        return new DependencyMap<T, D>();
    }

    @Override
    protected Set<T> newTSet() {
        return (Set<T>) new HashSet<T>();
    }

    @Override
    protected String toStringT(SDValue t) {
        return " - " + t.toString();
    }

    @Override
    protected String toStringD(D d) {
        return d.toString();
    }
}
