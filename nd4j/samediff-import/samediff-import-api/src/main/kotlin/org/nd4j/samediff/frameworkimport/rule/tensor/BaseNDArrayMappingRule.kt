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
package org.nd4j.samediff.frameworkimport.rule.tensor

import org.nd4j.common.primitives.Counter
import org.nd4j.ir.MapperNamespace
import org.nd4j.ir.OpNamespace
import org.nd4j.ir.TensorNamespace
import org.nd4j.samediff.frameworkimport.ArgDescriptor
import org.nd4j.samediff.frameworkimport.context.MappingContext
import org.nd4j.samediff.frameworkimport.findOp
import org.nd4j.samediff.frameworkimport.lookupIndexForArgDescriptor
import org.nd4j.samediff.frameworkimport.opdefs.OpDescriptorLoaderHolder
import org.nd4j.samediff.frameworkimport.process.MappingProcess
import org.nd4j.shade.protobuf.GeneratedMessageV3
import org.nd4j.shade.protobuf.ProtocolMessageEnum
import java.lang.IllegalArgumentException

abstract class BaseNDArrayMappingRule<
        GRAPH_DEF : GeneratedMessageV3,
        OP_DEF_TYPE : GeneratedMessageV3, NODE_DEF_TYPE : GeneratedMessageV3, ATTR_DEF : GeneratedMessageV3,
        ATTR_VALUE_TYPE : GeneratedMessageV3, TENSOR_TYPE : GeneratedMessageV3,
        DATA_TYPE>(
    mappingNamesToPerform: MutableMap<String, String> = mutableMapOf(),
    transformerArgs: Map<String, List<OpNamespace.ArgDescriptor>> = emptyMap()
) :
    TensorMappingRule<GRAPH_DEF, OP_DEF_TYPE, NODE_DEF_TYPE, ATTR_DEF, ATTR_VALUE_TYPE, TENSOR_TYPE, DATA_TYPE>
        where DATA_TYPE : ProtocolMessageEnum {

    protected var opDescriptor: OpNamespace.OpDescriptor? = null
    protected val mappingNamesToPerform = mappingNamesToPerform
    protected val transformerArgs = transformerArgs
    protected var mappingProcess: MappingProcess<GRAPH_DEF, OP_DEF_TYPE, NODE_DEF_TYPE, TENSOR_TYPE, ATTR_DEF, ATTR_VALUE_TYPE, DATA_TYPE>? =
        null
    protected var inputFrameworkOpName: String? = null

    override fun inputFrameworkOpName(): String {
        return inputFrameworkOpName!!
    }

    override fun modifyInputFrameworkOpName(inputFrameworkOpName: String) {
        this.inputFrameworkOpName = inputFrameworkOpName
    }

    override fun initWithMappingProcess(mappingProcess: MappingProcess<GRAPH_DEF, OP_DEF_TYPE, NODE_DEF_TYPE, TENSOR_TYPE, ATTR_DEF, ATTR_VALUE_TYPE, DATA_TYPE>) {
        val opDescriptorList = OpDescriptorLoaderHolder.nd4jOpDescriptor
        if (!opDescriptorList.opListList.map {  it.name }.contains(mappingProcess.opName())) {
            throw java.lang.IllegalArgumentException("Op name ${mappingProcess.opName()} not found!")
        }
        opDescriptor = opDescriptorList.opListList.first { input ->
            input.name == mappingProcess.opName()
        } ?: error("")
        this.mappingProcess = mappingProcess
        this.inputFrameworkOpName = mappingProcess.inputFrameworkOpName()
    }


    operator fun set(outputAttribute: String, inputAttribute: String) {
        mappingNamesToPerform[outputAttribute] = inputAttribute
    }

    override fun name(): String {
        return "ndarraymapping"
    }


    override fun mappingNamesToPerform(): Map<String, String> {
        return mappingNamesToPerform
    }


    override fun convertInput(mappingContext: MappingContext<GRAPH_DEF, NODE_DEF_TYPE, OP_DEF_TYPE, TENSOR_TYPE, ATTR_DEF, ATTR_VALUE_TYPE, DATA_TYPE>): List<OpNamespace.ArgDescriptor> {
        val ret = ArrayList<OpNamespace.ArgDescriptor>()
        val mappingsToPerform = inputArgumentMappings()
        val nameUsageCounts = Counter<String>()
        mappingsToPerform.forEach { (k, v) ->
          //only allow inputs that exist on the node, this accounts for default optional inputs on the node associated with the context
            if(mappingContext.hasInput(v)) {
              ret.add(ArgDescriptor {
                  name = mappingContext.nodeInputNameForOpDefInputName(v)
                  argType = OpNamespace.ArgDescriptor.ArgType.INPUT_TENSOR
                  inputValue = mappingContext.tensorInputFor(v).toArgTensor()
                  argIndex = lookupIndexForArgDescriptor(
                      argDescriptorName = k,
                      opDescriptorName = mappingContext.nd4jOpName(),
                      argDescriptorType = OpNamespace.ArgDescriptor.ArgType.INPUT_TENSOR
                  )
              })

              nameUsageCounts.incrementCount(v,1.0)
          } else {
              println("Skipping input $v on node ${mappingContext.irNode().nodeName()}")
            }

        }


        return ret
    }

    abstract fun createTensorProto(input: TENSOR_TYPE): TensorNamespace.TensorProto


    override fun convertInputsReverse(toReverse: List<OpNamespace.ArgDescriptor>): List<TENSOR_TYPE> {
        for (argument in toReverse) {
            require(argument.argType == OpNamespace.ArgDescriptor.ArgType.INPUT_TENSOR) { "Type to reverse must be an input tensor." }
        }
        TODO("Not yet implemented")
    }

    override fun inputArgumentMappings(): Map<String, String> {
        return mappingNamesToPerform
    }

    override fun serialize(): MapperNamespace.MappingRule {
        val builder = MapperNamespace.MappingRule.newBuilder()
        builder.ruleName = name()
        builder.functionName = name()
        builder.ruleType = "tensor"
        builder.inputFrameworkOpName = inputFrameworkOpName()
        for ((k, v) in transformerArgs) {
            val descriptor = opDescriptor!!.argDescriptorList.filter { input -> input.name == k }[0]
            when (descriptor.argType) {
                OpNamespace.ArgDescriptor.ArgType.BOOL -> builder.addOutputBooleanName(k)
                OpNamespace.ArgDescriptor.ArgType.INT64 -> builder.addOutputIntName(k)
                OpNamespace.ArgDescriptor.ArgType.FLOAT -> builder.addOutputFloatName(k)
                OpNamespace.ArgDescriptor.ArgType.DOUBLE -> builder.addOutputDoubleName(k)
                OpNamespace.ArgDescriptor.ArgType.INT64 -> builder.addOutputIntName(k)
                OpNamespace.ArgDescriptor.ArgType.INPUT_TENSOR -> builder.addInputTensorName(k)
                OpNamespace.ArgDescriptor.ArgType.OUTPUT_TENSOR -> builder.addOutputTensorName(k)
                OpNamespace.ArgDescriptor.ArgType.INT32 -> builder.addOutputIntName(k)
                OpNamespace.ArgDescriptor.ArgType.DATA_TYPE -> builder.addOutputDataTypeName(k)
                OpNamespace.ArgDescriptor.ArgType.STRING -> builder.addOutputStringAttrName(k)
                OpNamespace.ArgDescriptor.ArgType.UNRECOGNIZED -> throw IllegalArgumentException("Illegal type ${descriptor.argType}")
            }

            for (associatedInput in v) {
                when (associatedInput.argType) {
                    OpNamespace.ArgDescriptor.ArgType.STRING -> builder.addInputStringAttrName(associatedInput.name)
                    OpNamespace.ArgDescriptor.ArgType.BOOL -> builder.addInputBooleanName(associatedInput.name)
                    OpNamespace.ArgDescriptor.ArgType.DOUBLE, OpNamespace.ArgDescriptor.ArgType.FLOAT -> builder.addInputFloatName(associatedInput.name)
                    OpNamespace.ArgDescriptor.ArgType.INT32, OpNamespace.ArgDescriptor.ArgType.INT64 -> builder.addInputIntName(associatedInput.name)
                    OpNamespace.ArgDescriptor.ArgType.INPUT_TENSOR -> builder.addInputTensorName(associatedInput.name)
                    OpNamespace.ArgDescriptor.ArgType.DATA_TYPE ->builder.addOutputDataTypeName(associatedInput.name)
                    OpNamespace.ArgDescriptor.ArgType.OUTPUT_TENSOR -> builder.addOutputTensorName(associatedInput.name)
                    OpNamespace.ArgDescriptor.ArgType.UNRECOGNIZED -> throw IllegalArgumentException("Illegal type ${descriptor.argType}")
                }
            }


        }

        mappingNamesToPerform.forEach { outputName, inputName ->
            builder.addInputTensorName(inputName)
            builder.addOutputTensorName(outputName)
            builder.putInputToOutput(outputName,inputName)
        }


        return builder.build()
    }

    override fun toString(): String {
        return "BaseNDArrayMappingRule(mappingNamesToPerform=$mappingNamesToPerform, transformerArgs=$transformerArgs"
    }

    override fun equals(other: Any?): Boolean {
        if (this === other) return true
        if (other !is BaseNDArrayMappingRule<*, *, *, *, *, *, *>) return false

        if (mappingNamesToPerform != other.mappingNamesToPerform) return false
        if (transformerArgs != other.transformerArgs) return false

        return true
    }

    override fun hashCode(): Int {
        var result = opDescriptor?.hashCode() ?: 0
        result = 31 * result + mappingNamesToPerform.hashCode()
        result = 31 * result + transformerArgs.hashCode()
        return result
    }

}