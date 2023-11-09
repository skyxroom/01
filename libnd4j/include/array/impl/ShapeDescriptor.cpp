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
//  @author raver119@gmail.com
//  @author AbdelRauf

#include <array/ShapeDescriptor.h>
#include <helpers/ShapeBuilders.h>
#include <helpers/shape.h>

#include "helpers/ShapeUtils.h"

namespace sd {

//////////////////////////////////////////////////////////////////////////
// equal to operator
bool ShapeDescriptor::operator==(const ShapeDescriptor &other) const {
  if (_extraProperties != other._extraProperties) return false;
  if (_rank != other._rank) return false;
  if (_order != other._order) return false;
  if (_dataType != other._dataType) return false;
  if (_ews != other._ews) return false;

  if (_shape_strides != other._shape_strides) return false;

  return true;
}

//////////////////////////////////////////////////////////////////////////
// less than operator
bool ShapeDescriptor::operator<(const ShapeDescriptor &other) const {
  return std::tie(_extraProperties, _rank, _dataType, _ews, _order, _shape_strides) <
         std::tie(other._extraProperties, other._rank, other._dataType, other._ews, other._order, other._shape_strides);
}

sd::LongType *ShapeDescriptor::toShapeInfo() const {
  // for empty array use original
  return ShapeBuilders::createShapeInfoFrom(const_cast<ShapeDescriptor *>(this));
}

ShapeDescriptor::ShapeDescriptor(const DataType type, const char order, const sd::LongType *shape, const LongType rank)
    : _dataType(type), _order(order), _rank(rank), _ews(1) {
  if(order != 'c' && order != 'f') {
    std::string errorMessage;
    errorMessage += "Invalid ordering from shape buffer";
    errorMessage += std::to_string(order);
    THROW_EXCEPTION(errorMessage.c_str());

  }
  if(!DataTypeUtils::validDataType(_dataType)) {
    THROW_EXCEPTION("Shape descriptor created with invalid data type");
  }
  int rank2 = rank < 1 ? 1 : rank;
  _shape_strides.resize(2 * rank2);
  auto _shape = _shape_strides.data();
  for (int i = 0; i < rank2; i++) {
    _shape[i] = shape[i];
  }

  _extraProperties = ArrayOptions::flagForDataType(type);

  fillStrides();


}

ShapeDescriptor::ShapeDescriptor(const DataType type, const char order, const sd::LongType *shape,
                                 const sd::LongType *strides, const LongType rank, sd::LongType extras = -1) {
  if(shape == nullptr)
    THROW_EXCEPTION("ShapeDescriptor constructor: Shape can not be null!");
  if(type  == DataType::UNKNOWN)
    THROW_EXCEPTION("Shape descriptor created with invalid data type");

  //note this used to operate directly on the vector buffer
  //it now does manual copies with more checks.
  //this is to handle the 0 length case.
  if(rank < 1) {
    _dataType = type;
    _order = order;
    _rank = rank;
    _extraProperties = extras;
  } else {
    _shape_strides.resize(2 * rank);
    _dataType = type;
    _order = order;
    _rank = rank;
    _extraProperties = extras;
    _ews = 1;
    auto _shape = _shape_strides.data();
    auto _strides = _shape_strides.data() + rank;
    for (int e = 0; e < rank; e++) {
      _shape[e] = shape[e];
      if(rank > 1 && shape[e] == 0 && !ArrayOptions::hasPropertyBitSet(_extraProperties, ARRAY_EMPTY)) {
        _extraProperties = ArrayOptions::setPropertyBitForFlagsValue(_extraProperties, ARRAY_EMPTY);
      }
      if(strides != nullptr)
        _strides[e] = strides[e];
    }

    if(strides == nullptr)
      fillStrides();
  }

  if(!DataTypeUtils::validDataType(_dataType)) {
    THROW_EXCEPTION("Shape descriptor created with invalid data type");
  }
}

//////////////////////////////////////////////////////////////////////////


ShapeDescriptor::ShapeDescriptor(const DataType type, const char order, const std::vector<sd::LongType> &shape)
    : _dataType(type), _order(order) {
  if(!DataTypeUtils::validDataType(_dataType)) {
    THROW_EXCEPTION("Shape descriptor created with invalid data type");
  }
  _rank = shape.size();
  _extraProperties = ArrayOptions::defaultFlag();
  _extraProperties = ArrayOptions::setDataTypeValue(_extraProperties, type);
  int rank2 = shape.size() < 1 ? 1 : shape.size();
  _ews = 1;
  _shape_strides.resize(2 * rank2);
  if(_rank > 0) {
    auto _shape = _shape_strides.data();
    for (int i = 0; i < _rank; i++) {
      _shape[i] = shape[i];
      if(shape[i] == 0 && !ArrayOptions::hasPropertyBitSet(_extraProperties, ARRAY_EMPTY)) {
        _extraProperties = ArrayOptions::setPropertyBitForFlagsValue(_extraProperties, ARRAY_EMPTY);
      }
    }
    fillStrides();
  }

  _order = order;
  if(_order != 'c' && _order != 'f') {
    std::string errorMessage;
    errorMessage += "Invalid ordering from shape buffer";
    errorMessage += std::to_string(_order);
    THROW_EXCEPTION(errorMessage.c_str());

  }
  if(!DataTypeUtils::validDataType(_dataType)) {
    THROW_EXCEPTION("Shape descriptor created with invalid data type");
  }
}



//////////////////////////////////////////////////////////////////////////
ShapeDescriptor::ShapeDescriptor(const DataType type, const char order, const std::vector<sd::LongType> &shape,
                                 const std::vector<sd::LongType> &strides, const sd::LongType ews)
    : ShapeDescriptor(type, order, shape, strides) {
  _ews = ews;
  if(!DataTypeUtils::validDataType(_dataType)) {
    THROW_EXCEPTION("Shape descriptor created with invalid data type");
  }
}

ShapeDescriptor::ShapeDescriptor(const DataType type, const sd::LongType length)
    : _dataType(type), _ews(1), _order('c'), _rank(1), _extraProperties(0) {
  _shape_strides = {length, 1};  //{shape, stride}
  if(!DataTypeUtils::validDataType(_dataType)) {
    THROW_EXCEPTION("Shape descriptor created with invalid data type");
  }
}

ShapeDescriptor::ShapeDescriptor(const sd::LongType *shapeInfo, bool validateDataType) {
  if(shapeInfo == nullptr) {
    THROW_EXCEPTION("ShapeDescriptor constructor: Shape info cannot be null!");
  }

  int rankVal = shape::rank(shapeInfo);

  if(rankVal < 0 || rankVal > SD_MAX_RANK) {
    std::string errorMessage;
    errorMessage += "Shape descriptor created with invalid rank: ";
    errorMessage += std::to_string(rankVal);
    errorMessage += ". Valid range is 0 to ";
    errorMessage += std::to_string(SD_MAX_RANK);
    THROW_EXCEPTION(errorMessage.c_str());
  }


  _order = shape::order(shapeInfo);
  if(_order != 'c' && _order != 'f') {
    std::string errorMessage;
    errorMessage += "Invalid ordering from shape buffer";
    errorMessage += std::to_string(_order);
    THROW_EXCEPTION(errorMessage.c_str());

  }
  _ews = shape::elementWiseStride(shapeInfo);
  _rank = rankVal;
  _extraProperties = shape::extra(shapeInfo);

  if(_rank > 0 && shape::isEmpty(shapeInfo)) {
    _shape_strides.resize(2 * _rank);
    auto _strides = _shape_strides.data() + _rank;
    auto shapePtr = shape::shapeOf(shapeInfo);
    auto stridePtr = shape::stride(shapeInfo);
    for (sd::LongType e = 0; e < _rank; e++) {
      _shape_strides[e] = shapePtr[e];
      _strides[e] = 0;
    }

  }

  else if (_rank > 0 && !shape::isEmpty(shapeInfo)) {
    _shape_strides.resize(2 * _rank);
    auto _strides = _shape_strides.data() + _rank;
    auto shapePtr = shape::shapeOf(shapeInfo);
    auto stridePtr = shape::stride(shapeInfo);
    for (sd::LongType e = 0; e < _rank; e++) {
      _shape_strides[e] = shapePtr[e];
      _shape_strides[e + _rank] = stridePtr[e];

    }
    //validate construction of the shape descriptor. This is to prevent flag regressions when modifying
    //_extraProperties.
    //ensure that we only validate this for array size > 1
    if(!ArrayOptions::hasPropertyBitSet(_extraProperties, ARRAY_EMPTY) && this->arrLength() > 1) {
      for(int i = 0; i < _rank; i++) {
        if(_strides[i] == 0 && shapePtr[i] != 1) {
          std::string errorMessage;
          errorMessage += "Shape descriptor:";
          errorMessage += toString();
          errorMessage += "Array set as  not empty but stride is not 0. Index is ";
          errorMessage += std::to_string(i);
          errorMessage += " Stride is ";
          errorMessage += std::to_string(_strides[i]);
          //append the full _shape_strides data
          errorMessage += " _shape_strides is ";
          for(int j = 0; j < _shape_strides.size(); j++) {
            errorMessage += std::to_string(_shape_strides[j]);
            if(j < _shape_strides.size() - 1) {
              errorMessage += ", ";
            }
          }

          THROW_EXCEPTION(errorMessage.c_str());
        }
      }
    } else if(this->arrLength() > 1) {
      for(int i = 0; i < _rank; i++) {
        if(_strides[i] != 0) {
          std::string errorMessage;
          errorMessage += "Array set as not empty but stride is 0. Index is";
          errorMessage += std::to_string(i);
          THROW_EXCEPTION(errorMessage.c_str());
        }
      }
    }

  } else if(!shape::isEmpty(shapeInfo)) {  // Handle scalar case
    _shape_strides.resize(2); // Since we're setting shape and stride
    _shape_strides[0] = 0;    // Shape for scalar
    _shape_strides[1] = 1;    // Stride for scalar
  } else {
    _shape_strides.resize(2);
    _shape_strides[0] = 0;
    _shape_strides[1] = 0;
  }
  _order = shape::order(shapeInfo);
  _dataType = ArrayOptions::dataType(shapeInfo);
  if(validateDataType && _dataType  == DataType::UNKNOWN) {
    std::string errorMessage;
    errorMessage += "Shape descriptor created with invalid data type ";
    errorMessage += DataTypeUtils::asString(_dataType);
    errorMessage += " extra properties for data type was ";
    errorMessage += DataTypeUtils::asString(ArrayOptions::dataTypeValue(_extraProperties));
    THROW_EXCEPTION(errorMessage.c_str());
  }

}



ShapeDescriptor::ShapeDescriptor(const sd::LongType *shapeInfo, const sd::DataType dtypeOverride)
    : ShapeDescriptor::ShapeDescriptor(shapeInfo, false) {
  if(dtypeOverride == DataType::UNKNOWN)
    THROW_EXCEPTION("Shape descriptor created with invalid data type");
  _dataType = dtypeOverride;
  if(!DataTypeUtils::validDataType(_dataType)) {
    THROW_EXCEPTION("Shape descriptor created with invalid data type");
  }
  //data type has already been set by another constructor. We need to update the _extraProperties
  //to reflect the new data type. This is effectively a cast.
  _extraProperties = ArrayOptions::propertyWithoutDataTypeValue(_extraProperties);
  _extraProperties = ArrayOptions::setDataTypeValue(_extraProperties, dtypeOverride);

  if(!DataTypeUtils::validDataType(_dataType)) {
    THROW_EXCEPTION("Shape descriptor created with invalid data type");
  }
}

ShapeDescriptor::ShapeDescriptor(const sd::LongType *shapeInfo, const sd::LongType *dtypeOverride)
    : ShapeDescriptor::ShapeDescriptor(shapeInfo, ArrayOptions::dataType(dtypeOverride)) {
  if(!DataTypeUtils::validDataType(_dataType)) {
    THROW_EXCEPTION("Shape descriptor created with invalid data type");
  }
}

ShapeDescriptor::ShapeDescriptor(const sd::LongType *shapeInfo, const sd::LongType *dtypeOverride,
                                 const sd::LongType *orderOverride)
    : ShapeDescriptor::ShapeDescriptor(shapeInfo, ArrayOptions::dataType(dtypeOverride)) {
  _order = shape::order(orderOverride);
  if(!DataTypeUtils::validDataType(_dataType)) {
    THROW_EXCEPTION("Shape descriptor created with invalid data type");
  }
}

int ShapeDescriptor::rank() const { return _rank; }

sd::LongType ShapeDescriptor::ews() const { return _ews; }

sd::LongType ShapeDescriptor::arrLength() const {
  if(_shape_strides.empty()) {
    return 0;
  }

  // when _ews == 1 allocation length is also array length
  sd::LongType len = 1;
  for (int i = 0; i < _rank; i++) len *= _shape_strides[i];

  return len;
}

void ShapeDescriptor::print() const {
  printf("ShapeDescriptor: [");
  for (int i = 0; i < _rank; i++) {
    printf("%lld", _shape_strides[i]);
    if (i < _rank - 1) printf(", ");
  }
  printf("], [");
  for (int i = _rank; i < 2 * _rank; i++) {
    printf("%lld", _shape_strides[i]);
    if (i < 2 * _rank - 1) printf(", ");
  }
  printf("], %c, %lld, %s, %lld\n", _order, _ews, DataTypeUtils::asString(_dataType).c_str(), _extraProperties);
}


sd::LongType ShapeDescriptor::allocLength() const {
  if (_paddedAllocSize > 0) return _paddedAllocSize;
  auto _shape = _shape_strides.data();
  auto _strides = _shape_strides.data() + _rank;
  int rank2 = _rank < 1 ? 1 : _rank;

  sd::LongType len = 1;
  if (_ews == 1 && _rank > 1) {
    // calculate using max stride
    int ind = _order == 'c' ? 0 : rank2 - 1;
    return _shape[ind] * _strides[ind];
  }
  for (int i = 0; i < rank2; i++) {
    len += (_shape[i] - 1) * _strides[i];
  }
  return len;
}

sd::LongType ShapeDescriptor::validate() const {
  auto status = SHAPE_DESC_OK;
  bool is_continous = true;
  //exclude scalars on purpose here
  if (_rank > 0 && _rank != _shape_strides.size() / 2 || _rank > SD_MAX_RANK) status |= SHAPE_DESC_INCORRECT_RANK;
  auto _shape = _shape_strides.data();
  auto _strides = _shape_strides.data() + _rank;
  if(_order != 'c' && _order != 'f') {
    THROW_EXCEPTION("Invalid ordering from shape buffer");
  }

  bool hasZero = false;
  for (int i = 0; i < _rank; i++) {
    if (_shape[i] == 0) {
      hasZero = true;
      break;
    }
  }
  //this check isn't correct for vectors
  if (_rank > 0 && !shape::isVector(_shape_strides.data(),2) && !hasZero) {
    if (_order == 'c') {
      for (int j = _rank - 2; j >= 0; j--) {
        sd::LongType currentStride = _strides[j];
        sd::LongType allowedStride = _strides[j + 1] * _shape[j + 1];
        if (currentStride < allowedStride) {
          status = status | SHAPE_DESC_INCORRECT_STRIDES;
          break;
        }
        is_continous = is_continous & (currentStride == allowedStride);
      }
    } else {
      for (int j = 1; j < _rank; j++) {
        sd::LongType currentStride = _strides[j];
        sd::LongType allowedStride = _strides[j - 1] * _shape[j - 1];
        if (currentStride < allowedStride) {
          status = status | SHAPE_DESC_INCORRECT_STRIDES;
          break;
        }
        is_continous = is_continous & (currentStride == allowedStride);
      }
    }

    int index = (_order == 'c') ? _rank - 1 : 0;
    auto correctEws = is_continous ? _strides[index] : 0;
    if (correctEws != _ews)  {
      status = status | SHAPE_DESC_INCORRECT_EWS;
    }
  }

  if(isEmpty()) {
    for(int i = 0; i < _rank; i++) {
      if(_strides[i] != 0) {
        std::string errorMessage;
        errorMessage += "Array set as empty but stride is not 0. Index is ";
        errorMessage += std::to_string(i);
        errorMessage += " Stride is ";
        errorMessage += std::to_string(_strides[i]);
        THROW_EXCEPTION(errorMessage.c_str());
        break;
      }
    }
  }

  if(!DataTypeUtils::validDataType(_dataType)) {
    THROW_EXCEPTION("Shape descriptor created with invalid data type");
  }

  return status;
}

char ShapeDescriptor::order() const { return _order; }

DataType ShapeDescriptor::dataType() const {
  if(!DataTypeUtils::validDataType(_dataType)) {
    std::string errorMessage;
    errorMessage += "Shape descriptor created with invalid data type";
    errorMessage += DataTypeUtils::asString(_dataType);
    THROW_EXCEPTION(errorMessage.c_str());
  }
  return _dataType;
}

bool ShapeDescriptor::isEmpty() const { return (_extraProperties & ARRAY_EMPTY) == ARRAY_EMPTY; }
bool ShapeDescriptor::isScalar() const { return !isEmpty() && rank() == 0 || rank() == 1 && arrLength() == 1; }

std::vector<sd::LongType> &ShapeDescriptor::shape_strides() { return _shape_strides; }

const sd::LongType *ShapeDescriptor::stridesPtr() const {
  return _shape_strides.size() == 2 * _rank ? _shape_strides.data() + _rank : nullptr;
}

ShapeDescriptor::ShapeDescriptor(const ShapeDescriptor &other) {
  _rank = other._rank;
  _ews = other._ews;
  _extraProperties = other._extraProperties;
  if(other._dataType == DataType::UNKNOWN)
    THROW_EXCEPTION("Shape descriptor created with invalid data type");
  _dataType = other._dataType;
  _order = other._order;
  _shape_strides = other._shape_strides;
  _paddedAllocSize = other._paddedAllocSize;
}

//////////////////////////////////////////////////////////////////////////
ShapeDescriptor::ShapeDescriptor(const DataType type, const char order, const std::vector<sd::LongType> &shape,
                                 const std::vector<sd::LongType> &strides)
    : _dataType(type), _order(order) {
  _rank = shape.size();
  int rank2 = _rank < 1 ? 1 : _rank;

  _shape_strides.resize(2 * rank2);
  auto _shape = _shape_strides.data();
  auto _strides = _shape_strides.data() + rank2;
  if (!shape.empty() && strides.size() != shape.size() ) {
    for (int i = 0; i < rank2; i++) {
      _shape[i] = shape[i];
    }
    fillStrides();
  } else {
    for (int i = 0; i < rank2; i++) {
      _shape[i] = shape[i];
      _strides[i] = strides[i];
    }
  }
}

ShapeDescriptor  * ShapeDescriptor::emptyDescriptor(const DataType type) {
  ShapeDescriptor *descriptor = new ShapeDescriptor();
  if(type == DataType::UNKNOWN)
    THROW_EXCEPTION("Shape descriptor created with invalid data type");
  descriptor->_dataType = type;
  descriptor->_extraProperties = ARRAY_EMPTY | ArrayOptions::flagForDataType(type);
  descriptor->_rank = 0;
  descriptor->_order = 'c';
  descriptor->_ews = 1;

  return descriptor;
}

ShapeDescriptor * ShapeDescriptor::scalarDescriptor(const DataType type) {
  ShapeDescriptor *descriptor = new ShapeDescriptor();
  if(type  == DataType::UNKNOWN)
    THROW_EXCEPTION("Shape descriptor created with invalid data type");
  descriptor->_dataType = type;
  descriptor->_extraProperties = ArrayOptions::flagForDataType(type);
  descriptor->_rank = 0;
  descriptor->_order = 'c';
  descriptor->_ews = 1;

  return descriptor;
}

ShapeDescriptor * ShapeDescriptor::vectorDescriptor(const sd::LongType length, const DataType type) {
  ShapeDescriptor *descriptor = new ShapeDescriptor();
  if(type  == DataType::UNKNOWN)
    THROW_EXCEPTION("Shape descriptor created with invalid data type");

  descriptor->_dataType = type;
  descriptor->_shape_strides = {length, 0};


  if (length > 0) {
    descriptor->_shape_strides[1] = 1;
    descriptor->_extraProperties = ArrayOptions::flagForDataType(type);
  }
  else {
    descriptor->_shape_strides[1] = 0;
    descriptor->_extraProperties = ARRAY_EMPTY;
    descriptor->_extraProperties = ArrayOptions::setDataTypeValue(descriptor->_extraProperties, type);
  }

  descriptor->_order = 'c';
  descriptor->_ews = 1;
  descriptor->_rank = 1;

  return descriptor;
}

ShapeDescriptor  * ShapeDescriptor::paddedBufferDescriptor(const DataType type, const char order,
                                                           const std::vector<sd::LongType> &shape,
                                                           const std::vector<sd::LongType> &paddings) {
  ShapeDescriptor *descriptor = new ShapeDescriptor();
  if(type  == DataType::UNKNOWN)
    THROW_EXCEPTION("Shape descriptor created with invalid data type");

  descriptor->_dataType = type;
  descriptor->_order = order;
  descriptor->_rank = shape.size();
  descriptor->_extraProperties = ArrayOptions::flagForDataType(type);
  if (descriptor->_rank < 1) {
    descriptor->_ews = 1;
    return descriptor;
  }

  int rank2 = descriptor->_rank < 1 ? 1 : descriptor->_rank;

  descriptor->_shape_strides.resize(rank2 * 2);
  auto _shape = descriptor->_shape_strides.data();
  auto _strides = descriptor->_shape_strides.data() + rank2;
  for (int i = 0; i < shape.size(); i++) {
    _shape[i] = shape[i];
  }
  // calculate strides with paddings
  int min_rank = descriptor->_rank > paddings.size() ? paddings.size() : rank2;
  bool is_continous = true;
  if (order == 'c') {
    _strides[rank2 - 1] = 1L;
    for (int j = descriptor->_rank - 2; j >= 0; j--) {
      sd::LongType pad = (j + 1 < min_rank) ? paddings[j + 1] : 0;
      _strides[j] = _strides[j + 1] * (_shape[j + 1] + pad);
      descriptor->_extraProperties = descriptor->_extraProperties | (_shape[j + 1] == 0);
      if (pad != 0) is_continous = false;
    }
    if (!is_continous && descriptor->_rank > 0) {
      sd::LongType size_pad = paddings.size() > 0 ? paddings[0] : 0;
      // alloc size should be supplied manually as we dont have place to store it
      descriptor->_paddedAllocSize = _strides[0] * (_shape[0] + size_pad);
    }
  } else {
    _strides[0] = 1L;
    for (int j = 1; j < rank2; j++) {
      sd::LongType pad = (j - 1 < min_rank) ? paddings[j - 1] : 0;
      _strides[j] = _strides[j - 1] * (_shape[j - 1] + pad);
      descriptor->_extraProperties = descriptor->_extraProperties | (_shape[j - 1] == 0);
      if (pad != 0) is_continous = false;
    }
    if (!is_continous && descriptor->_rank > 0) {
      sd::LongType size_pad = paddings.size() >= descriptor->_rank ? paddings[descriptor->_rank - 1] : 0;
      // alloc size should be supplied manually as we dont have place to store it
      descriptor->_paddedAllocSize = _strides[descriptor->_rank - 1] * (_shape[descriptor->_rank - 1] + size_pad);
    }
  }

  descriptor->_ews = is_continous ? 1 : 0;
  if (!is_continous) descriptor->_extraProperties |= ARRAY_HAS_PADDED_BUFFER;
  return descriptor;
}

}  // namespace sd

namespace std {
size_t hash<sd::ShapeDescriptor>::operator()(const sd::ShapeDescriptor &k) const {
  auto res = std::hash<char>()(k.order());
  res ^= std::hash<int>()((int)k.dataType()) + 0x9e3779b9 + (res << 6) + (res >> 2);
  auto shape_strides = const_cast<sd::ShapeDescriptor &>(k).shape_strides();
  auto ptr = shape_strides.data();
  //dont include strides if its' ews==1
  int stop = k.ews()==1? shape_strides.size()/2 : shape_strides.size() ;
  for (int j=0; j < stop; j++) {
    res ^= std::hash<sd::LongType>()(ptr[j]) + 0x9e3779b9 + (res << 6) + (res >> 2);
  }

  return res;
}
}  // namespace std
