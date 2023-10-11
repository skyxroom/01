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

package org.eclipse.deeplearning4j.frameworkimport.tensorflow;

import lombok.extern.slf4j.Slf4j;
import lombok.val;
import org.eclipse.deeplearning4j.tests.extensions.DeallocationExtension;
import org.junit.jupiter.api.*;

import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.Arguments;
import org.junit.jupiter.params.provider.MethodSource;
import org.nd4j.common.tests.tags.TagNames;
import org.nd4j.linalg.api.ndarray.INDArray;
import org.nd4j.linalg.factory.Nd4j;
import org.nd4j.common.primitives.Pair;

import java.io.File;
import java.io.IOException;
import java.util.*;
import java.util.stream.Stream;

import static org.junit.jupiter.api.Assumptions.assumeFalse;

@Slf4j
@Tag(TagNames.TENSORFLOW)
public class TestTFGraphAllSameDiff {   //Note: Can't extend BaseNd4jTest here as we need no-arg constructor for parameterized tests

    private static final TFGraphTestAllHelper.ExecuteWith EXECUTE_WITH = TFGraphTestAllHelper.ExecuteWith.SAMEDIFF;
    private static final String BASE_DIR = "tf_graphs/examples";
    private static final String MODEL_FILENAME = "frozen_model.pb";

    /**
     * NOTE: If this is empty or the tests names are wrong,
     * all tests will trigger an assumeFalse(..) that indicates
     * the status of the test failing. No tests will run.
     */
    public final static List<String> EXECUTE_ONLY_MODELS = Arrays.asList(
           //TODO: unsorted segment sum is the problem op here
            "g_09"
            /*,
            ,
            ,
           ,

            "fused_batch_norm/float32_nhcw",
            "g_12",
            "g_05",
            "is_strictly_increasing/emptyArrayTest/rank1_float32",
            "fused_batch_norm/float32_nhwc",
            "is_strictly_increasing/emptyArrayTest/rank2_float32",
            "linear_solve/float32_rank2",
            "extractImagePatches/sz1-6-6-2_float32_k3_s1_r1_SAME",
            "linear_solve/float64_rank3",
            "lrn/dr3_b05_a05_b02",
            "in_top_k/test_4,5_k1",
            "linear_solve/float64_rank2",
          */
    );


    public static final String[] IGNORE_REGEXES = new String[] {
            //crashes JVM
            //expects 2 outputs we only output 1
            "non_max_suppression_v4/float16_with_thresholds",
            "non_max_suppression_v4/float32_with_thresholds",
            "non_max_suppression_v4/float32_with_thresholds_pad_to_max_output_size",
            "non_max_suppression_v5/.*",
            "resize_bicubic/float64",
            "resize_bicubic/int32",

            "multinomial/.*",


            //Failing 2019/09/11 - https://github.com/eclipse/deeplearning4j/issues/7965
            // Still failing 2020/04/27 java.lang.IllegalStateException: Requested output variable Bincount does not exist in SameDiff instance
            //Invalid test cases. Verified by running graph against actual TF.

            "reductions/scatter_update_vector",
            "reductions/scatter_update_scalar",
            "emptyArrayTests/scatter_update/rank1_emptyIndices_emptyUpdates",
            "bincount/rank2_weights",
            "slogdet/.*",
            "fused_batch_norm/float16_nhwc",
            "emptyArrayTests/scatter_update/rank2_emptyIndices_emptyUpdates",
            //Don't bother to test RNG. We can test subsets of ops with dropout to make sure they are consistent
            //These tests have random uniform and other RNG in them that don't need to be perfectly compatible to be acceptable.
            //We need different test cases here.
            "layers_dropout/.*",
            //TODO floormod and truncatemod behave differently - i.e., "c" vs. "python" semantics. Need to check implementations too
            // Still failing 2020/04/27 java.lang.IllegalStateException: Could not find class for TF Ops: TruncateMod
            "truncatemod/.*",

            //2019/09/11 - No tensorflow op found for SparseTensorDenseAdd
            // 2020/04/27 java.lang.IllegalStateException: Could not find class for TF Ops: SparseTensorDenseAdd
            "confusion/.*",

            //2019/09/11 - Couple of tests failing (InferenceSession issues)
            // Still failing 2020/04/27 Requested output variable concat does not exist in SameDiff instance


            //2019/05/21 - Failing on windows-x86_64-cuda-9.2 only -
            "conv_4",



            //2019/11/04 AB - disabled, pending libnd4j deconv3d_tf implementation
            // Still failing 2020/04/27 java.lang.IllegalStateException: Could not find descriptor for op: deconv3d_tf - class: org.nd4j.linalg.api.ops.impl.layers.convolution.DeConv3DTF
            "conv3d_transpose.*",

            //2019/11/15 - mapping is not present yet https://github.com/eclipse/deeplearning4j/issues/8397
            // Still failing 2020/04/27 java.lang.AssertionError: Predictions do not match on ragged/reduce_mean/2d_a1, node RaggedReduceMean/truediv
            "ragged/reduce_mean/.*",


            //08.05.2020 - https://github.com/eclipse/deeplearning4j/issues/8927
            "random_gamma/.*",

            //08.05.2020 - https://github.cMatchCondom/eclipse/deeplearning4j/issues/8928
            "Conv3DBackpropInputV2/.*",





            // 18.05.2020 - :wq:wq

            "random_uniform_int/.*",
            "random_uniform/.*",
            "random_poisson_v2/.*"
    };

    /* As per TFGraphTestList.printArraysDebugging - this field defines a set of regexes for test cases that should have
       all arrays printed during execution.
       If a test name matches any regex here, an ExecPrintListener will be added to the listeners, and all output
       arrays will be printed during execution
     */
    private final List<String> debugModeRegexes = Arrays.asList();



    public static Stream<Arguments> data() throws IOException {
        String localPath = System.getenv(TFGraphTestAllHelper.resourceFolderVar);
        // if this variable isn't set - we're using dl4j-tests-resources
        if (localPath == null) {
            File baseDir = new File(System.getProperty("java.io.tmpdir"), UUID.randomUUID().toString());
            List<Object[]> params = TFGraphTestAllHelper.fetchTestParams(BASE_DIR, MODEL_FILENAME, EXECUTE_WITH, baseDir);
            return params.stream().map(input -> Arguments.of(input));
        } else {
            File baseDir = new File(localPath);
            return TFGraphTestAllHelper.fetchTestParams(BASE_DIR, MODEL_FILENAME, EXECUTE_WITH, baseDir).stream().map(input -> Arguments.of(input));
        }
    }

    @ParameterizedTest(name = "{2}")
    @MethodSource("data")
    public void testOutputOnly(Map<String, INDArray> inputs, Map<String, INDArray> predictions, String modelName, File localTestDir) throws Exception {
        if(EXECUTE_ONLY_MODELS.isEmpty()) {
            for(String s : IGNORE_REGEXES)  {
                if(modelName.matches(s)) {
                    log.info("\n\tIGNORE MODEL ON REGEX: {} - regex {}", modelName, s);
                    assumeFalse(true);
                }
            }
        } else if(!EXECUTE_ONLY_MODELS.contains(modelName)) {
            log.info("Not executing " + modelName);
            assumeFalse(true);
        }



        System.out.println("Testing with test name " + System.getProperty(DeallocationExtension.CURRENT_TEST_DISPLAY_NAME));
        Pair<Double,Double> precisionOverride = TFGraphTestAllHelper.testPrecisionOverride(modelName);
        Double maxRE = (precisionOverride == null ? null : precisionOverride.getFirst());
        Double minAbs = (precisionOverride == null ? null : precisionOverride.getSecond());

        boolean verboseDebugMode = true;
        if(debugModeRegexes != null) {
            for(String regex : debugModeRegexes) {
                if(modelName.matches(regex)){
                    verboseDebugMode = true;
                    break;
                }
            }
        }

        try {

            Nd4j.getEnvironment().setDeletePrimary(false);
            Nd4j.getEnvironment().setDeleteSpecial(false);
            Nd4j.getExecutioner().enableDebugMode(true);
            Nd4j.getExecutioner().enableVerboseMode(true);
            // TFGraphTestAllHelper.checkIntermediate(inputs, modelName, BASE_DIR, MODEL_FILENAME, EXECUTE_WITH,localTestDir,verboseDebugMode);
            TFGraphTestAllHelper.checkOnlyOutput(inputs, predictions, modelName, BASE_DIR, MODEL_FILENAME, EXECUTE_WITH, new TFGraphTestAllHelper.DefaultGraphLoader(inputs), maxRE, minAbs, verboseDebugMode);
        } catch (Throwable t){
            log.error("ERROR Executing test: {} - input keys {}", modelName, (inputs == null ? null : inputs.keySet()), t);
            throw t;
        }
    }



}
