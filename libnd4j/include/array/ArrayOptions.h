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

#ifndef ND4J_ARRAY_OPTIONS_H
#define ND4J_ARRAY_OPTIONS_H

#pragma once

#include <system/common.h>
#include <system/op_boilerplate.h>
#include <array/ArrayType.h>
#include <array/DataType.h>
#include <array/SpaceType.h>
#include <array/SparseType.h>

#include <initializer_list>
#include <vector>
#define ARRAY_SPARSE 2
#define ARRAY_COMPRESSED 4
#define ARRAY_EMPTY 8
#define ARRAY_RAGGED 16

#define ARRAY_CSR 32
#define ARRAY_CSC 64
#define ARRAY_COO 128

// complex values
#define ARRAY_COMPLEX 512

// quantized values
#define ARRAY_QUANTIZED 1024

//  16 bit float FP16
#define ARRAY_HALF 4096

//  16 bit bfloat16
#define ARRAY_BHALF 2048

// regular 32 bit float
#define ARRAY_FLOAT 8192

// regular 64 bit float
#define ARRAY_DOUBLE 16384

// 8 bit integer
#define ARRAY_CHAR 32768

// 16 bit integer
#define ARRAY_SHORT 65536

// 32 bit integer
#define ARRAY_INT 131072

// 64 bit integer
#define ARRAY_LONG 262144

// boolean values
#define ARRAY_BOOL 524288

// UTF values
#define ARRAY_UTF8 1048576
#define ARRAY_UTF16 4194304
#define ARRAY_UTF32 16777216

// flag for extras
#define ARRAY_EXTRAS 2097152

// flag for signed/unsigned integers
#define ARRAY_UNSIGNED 8388608

// flag for arrays with padded buffer
#define ARRAY_HAS_PADDED_BUFFER (1 << 25)

#define DEFAULT_FLAG 0




namespace sd {
class SD_LIB_EXPORT ArrayOptions {
 public:
  static SD_HOST LongType extra(const LongType *shapeInfo);
  static SD_HOST void setExtra(sd::LongType *shapeInfo, sd::LongType value);
  static SD_HOST bool isNewFormat(const sd::LongType *shapeInfo);
  static SD_HOST bool hasPropertyBitSet(const sd::LongType *shapeInfo, LongType property);
  static SD_HOST bool togglePropertyBit(sd::LongType *shapeInfo, LongType property);
  static SD_HOST void unsetPropertyBit(sd::LongType *shapeInfo, LongType property);
  static SD_HOST void validateSingleDataType(sd::LongType property);
  static SD_HOST void setPropertyBit(sd::LongType *shapeInfo, LongType property);
  static SD_HOST void setPropertyBits(sd::LongType *shapeInfo, std::initializer_list<LongType> properties);

  static SD_HOST bool isSparseArray(sd::LongType *shapeInfo);
  static SD_HOST bool isUnsigned(sd::LongType *shapeInfo);

  static SD_HOST_DEVICE sd::DataType dataType(const sd::LongType *shapeInfo);

  static SD_HOST SpaceType spaceType(sd::LongType *shapeInfo);
  static SD_HOST_DEVICE SpaceType spaceType(const sd::LongType *shapeInfo);

  static SD_HOST_DEVICE ArrayType arrayType(sd::LongType *shapeInfo);
  static SD_HOST_DEVICE ArrayType arrayType(const sd::LongType *shapeInfo);

  static SD_HOST_DEVICE SparseType sparseType(sd::LongType *shapeInfo);
  static SD_HOST SparseType sparseType(const sd::LongType *shapeInfo);

  static SD_HOST_DEVICE bool hasExtraProperties(sd::LongType *shapeInfo);

  static SD_HOST bool hasPaddedBuffer(const sd::LongType *shapeInfo);
  static SD_HOST void flagAsPaddedBuffer(sd::LongType *shapeInfo);

  static SD_HOST void resetDataType(sd::LongType *shapeInfo);
  static SD_HOST sd::LongType propertyWithoutDataType(const sd::LongType *shapeInfo);
  static SD_HOST void setDataType(sd::LongType *shapeInfo, const sd::DataType dataType);
  static SD_HOST sd::LongType setDataTypeValue(sd::LongType extraStorage, const sd::DataType dataType);
  static SD_HOST LongType flagForDataType(const sd::DataType dataType);
  static SD_HOST void copyDataType(sd::LongType *to, const sd::LongType *from);
  static SD_HOST const char *enumerateSetFlags(const LongType *shapeInfo);
  static SD_HOST void unsetAllFlags(LongType *shapeInfo);
  static SD_HOST int enumerateSetFlags(const LongType *shapeInfo, const char **setFlagsOutput, int maxFlags);
  static SD_HOST const char *findFlagString(int flag);
  static SD_HOST sd::LongType extraIndex(const sd::LongType *shapeInfo);
  static SD_HOST sd::LongType extraIndex(sd::LongType *shapeInfo);
  static SD_HOST void unsetAllFlags(LongType &flagStorage);
  static SD_HOST const char *enumerateSetFlagsForFlags(const LongType flagStorage);
  static SD_HOST SpaceType spaceTypeForFlags(const LongType &flagStorage);
  static SD_HOST ArrayType arrayTypeForFlags(const LongType &flagStorage);
  static SD_HOST bool togglePropertyBitForFlags(LongType &flagStorage, LongType property);
  static SD_HOST sd::LongType unsetPropertyBitForFlags(LongType &flagStorage, LongType property);
  static SD_HOST SparseType sparseTypeForFlags(const LongType &flagStorage);
  static sd::LongType setPropertyBitForFlagsValue(LongType extraStorage, LongType property);
  static SD_HOST bool hasPropertyBitSet(const LongType extra, LongType property);
  static SD_HOST void resetFlags(LongType *to);
  static SD_HOST sd::LongType defaultFlag();

  static SD_HOST  LongType propertyWithoutDataTypeValue(LongType extra);
  static SD_HOST DataType dataTypeValue(LongType property);
};

}
#endif  // ND4J_ARRAY_OPTIONS_H :)
