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
package org.nd4j.samediff.frameworkimport.rule.attribute

import org.nd4j.ir.OpNamespace
import org.nd4j.linalg.factory.Nd4j
import org.nd4j.samediff.frameworkimport.context.MappingContext
import org.nd4j.samediff.frameworkimport.lookupIndexForArgDescriptor
import org.nd4j.samediff.frameworkimport.nameSpaceTensorFromNDarray
import org.nd4j.shade.protobuf.GeneratedMessageV3
import org.nd4j.shade.protobuf.ProtocolMessageEnum

abstract class StringContainsAdapterRule<
        GRAPH_DEF: GeneratedMessageV3,
        OP_DEF_TYPE: GeneratedMessageV3,
        NODE_TYPE: GeneratedMessageV3,ATTR_DEF : GeneratedMessageV3,
        ATTR_VALUE_TYPE : GeneratedMessageV3,
        TENSOR_TYPE : GeneratedMessageV3, DATA_TYPE>(
    mappingNamesToPerform: Map<String, String> = emptyMap(),
    transformerArgs: Map<String, List<OpNamespace.ArgDescriptor>> = emptyMap()):
    BaseAttributeExtractionRule<GRAPH_DEF, OP_DEF_TYPE, NODE_TYPE, ATTR_DEF, ATTR_VALUE_TYPE, TENSOR_TYPE, DATA_TYPE>
        (name = "stringcontains",
        mappingNamesToPerform =  mappingNamesToPerform,
        transformerArgs = transformerArgs)
        where DATA_TYPE: ProtocolMessageEnum {
    override fun acceptsInputType(argDescriptorType: AttributeValueType): Boolean {
        return argDescriptorType == AttributeValueType.STRING
    }

    override fun outputsType(argDescriptorType: List<OpNamespace.ArgDescriptor.ArgType>): Boolean {
        return argDescriptorType.contains(OpNamespace.ArgDescriptor.ArgType.BOOL) || argDescriptorType.contains(
            OpNamespace.ArgDescriptor.ArgType.INT64
        )
    }

    override fun convertAttributes(mappingCtx: MappingContext<GRAPH_DEF, NODE_TYPE, OP_DEF_TYPE, TENSOR_TYPE, ATTR_DEF, ATTR_VALUE_TYPE, DATA_TYPE>): List<OpNamespace.ArgDescriptor> {
        val ret = ArrayList<OpNamespace.ArgDescriptor>()

        for((k, v) in mappingNamesToPerform()) {
            val argDescriptorTypeList =  mappingCtx.argDescriptorTypeForName(k)
            val descriptorForName = transformerArgs[k]
            val compString = descriptorForName!![0].stringValue
            val testValue = mappingCtx.irAttributeValueForNode(v).stringValue()
            argDescriptorTypeList.forEach { argDescriptorType ->
                val descriptorBuilder = OpNamespace.ArgDescriptor.newBuilder()
                descriptorBuilder.name = k
                descriptorBuilder.argType =  argDescriptorType
                descriptorBuilder.argIndex = lookupIndexForArgDescriptor(
                    argDescriptorName = k,
                    opDescriptorName = mappingCtx.nd4jOpName(),
                    argDescriptorType = argDescriptorType
                )

                when(argDescriptorType) {
                    OpNamespace.ArgDescriptor.ArgType.BOOL -> {
                        descriptorBuilder.boolValue = testValue.isNotEmpty() && compString.contains(testValue)
                    }

                    OpNamespace.ArgDescriptor.ArgType.INT64 -> {
                        descriptorBuilder.int64Value = if (testValue.isNotEmpty() && compString.contains(testValue)) 1 else 0

                    }

                    OpNamespace.ArgDescriptor.ArgType.FLOAT ->    descriptorBuilder.floatValue = if (testValue.isNotEmpty() && compString.contains(testValue)) 1.0f else 0.0f

                    OpNamespace.ArgDescriptor.ArgType.DOUBLE ->   descriptorBuilder.doubleValue = if (testValue.isNotEmpty() && compString.contains(testValue)) 1.0 else 0.0
                    OpNamespace.ArgDescriptor.ArgType.INT32 ->   descriptorBuilder.int32Value = if (testValue.isNotEmpty() && compString.contains(testValue)) 1 else 0
                    OpNamespace.ArgDescriptor.ArgType.INPUT_TENSOR ->  {
                        descriptorBuilder.inputValue = if (testValue.isNotEmpty() && compString.contains(testValue)) nameSpaceTensorFromNDarray(
                            Nd4j.scalar(true)) else nameSpaceTensorFromNDarray(Nd4j.scalar(false))
                    }
                    OpNamespace.ArgDescriptor.ArgType.OUTPUT_TENSOR ->  {
                        descriptorBuilder.outputValue = if (testValue.isNotEmpty() && compString.contains(testValue)) nameSpaceTensorFromNDarray(
                            Nd4j.scalar(true)) else nameSpaceTensorFromNDarray(Nd4j.scalar(false))
                    }
                    OpNamespace.ArgDescriptor.ArgType.STRING ->   descriptorBuilder.stringValue = if (testValue.isNotEmpty() && compString.contains(testValue)) "true" else "false"
                    else -> throw IllegalArgumentException("Invalid type ${argDescriptorType}")
                }
                ret.add(descriptorBuilder.build())
            }


        }
        return ret
    }
}