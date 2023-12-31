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

package org.datavec.api.records.reader.impl;

import org.datavec.api.records.reader.RecordReader;
import org.datavec.api.records.reader.impl.csv.CSVRecordReader;
import org.datavec.api.split.FileSplit;
import org.junit.jupiter.api.Tag;
import org.junit.jupiter.api.Test;
import org.nd4j.common.io.ClassPathResource;
import org.nd4j.common.tests.BaseND4JTest;
import org.nd4j.common.tests.tags.TagNames;

import static org.junit.jupiter.api.Assertions.assertEquals;
@Tag(TagNames.JAVA_ONLY)
@Tag(TagNames.FILE_IO)
public class TestConcatenatingRecordReader extends BaseND4JTest {

    @Test
    public void test() throws Exception {

        CSVRecordReader rr = new CSVRecordReader(0, ',');
        rr.initialize(new FileSplit(new ClassPathResource("datavec-api/iris.dat").getFile()));

        CSVRecordReader rr2 = new CSVRecordReader(0, ',');
        rr2.initialize(new FileSplit(new ClassPathResource("datavec-api/iris.dat").getFile()));

        RecordReader rrC = new ConcatenatingRecordReader(rr, rr2);

        int count = 0;
        while(rrC.hasNext()){
            rrC.next();
            count++;
        }

        assertEquals(300, count);
    }
}
