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


#ifndef FLATBUFFERS_GENERATED_UIGRAPHEVENTS_SD_GRAPH_H_
#define FLATBUFFERS_GENERATED_UIGRAPHEVENTS_SD_GRAPH_H_

#include "flatbuffers/flatbuffers.h"

#include "array_generated.h"

namespace sd {
namespace graph {

struct UIEvent;
struct UIEventBuilder;

struct FrameIteration;
struct FrameIterationBuilder;

struct UIAddName;
struct UIAddNameBuilder;

struct FlatArrayList;
struct FlatArrayListBuilder;

struct UIHistogram;
struct UIHistogramBuilder;

struct UISummaryStatistics;
struct UISummaryStatisticsBuilder;

struct UIHardwareState;
struct UIHardwareStateBuilder;

enum UIEventType {
  UIEventType_ADD_NAME = 0,
  UIEventType_SCALAR = 1,
  UIEventType_ARRAY = 2,
  UIEventType_ARRAY_LIST = 3,
  UIEventType_HISTOGRAM = 4,
  UIEventType_IMAGE = 5,
  UIEventType_SUMMARY_STATISTICS = 6,
  UIEventType_OP_TIMING = 7,
  UIEventType_HARDWARE_STATE = 8,
  UIEventType_MIN = UIEventType_ADD_NAME,
  UIEventType_MAX = UIEventType_HARDWARE_STATE
};

inline const UIEventType (&EnumValuesUIEventType())[9] {
  static const UIEventType values[] = {
    UIEventType_ADD_NAME,
    UIEventType_SCALAR,
    UIEventType_ARRAY,
    UIEventType_ARRAY_LIST,
    UIEventType_HISTOGRAM,
    UIEventType_IMAGE,
    UIEventType_SUMMARY_STATISTICS,
    UIEventType_OP_TIMING,
    UIEventType_HARDWARE_STATE
  };
  return values;
}

inline const char * const *EnumNamesUIEventType() {
  static const char * const names[10] = {
    "ADD_NAME",
    "SCALAR",
    "ARRAY",
    "ARRAY_LIST",
    "HISTOGRAM",
    "IMAGE",
    "SUMMARY_STATISTICS",
    "OP_TIMING",
    "HARDWARE_STATE",
    nullptr
  };
  return names;
}

inline const char *EnumNameUIEventType(UIEventType e) {
  if (flatbuffers::IsOutRange(e, UIEventType_ADD_NAME, UIEventType_HARDWARE_STATE)) return "";
  const size_t index = static_cast<size_t>(e);
  return EnumNamesUIEventType()[index];
}

enum UIEventSubtype {
  UIEventSubtype_NONE = 0,
  UIEventSubtype_EVALUATION = 1,
  UIEventSubtype_LOSS = 2,
  UIEventSubtype_LEARNING_RATE = 3,
  UIEventSubtype_TUNING_METRIC = 4,
  UIEventSubtype_PERFORMANCE = 5,
  UIEventSubtype_PROFILING = 6,
  UIEventSubtype_FEATURE_LABEL = 7,
  UIEventSubtype_PREDICTION = 8,
  UIEventSubtype_USER_CUSTOM = 9,
  UIEventSubtype_MIN = UIEventSubtype_NONE,
  UIEventSubtype_MAX = UIEventSubtype_USER_CUSTOM
};

inline const UIEventSubtype (&EnumValuesUIEventSubtype())[10] {
  static const UIEventSubtype values[] = {
    UIEventSubtype_NONE,
    UIEventSubtype_EVALUATION,
    UIEventSubtype_LOSS,
    UIEventSubtype_LEARNING_RATE,
    UIEventSubtype_TUNING_METRIC,
    UIEventSubtype_PERFORMANCE,
    UIEventSubtype_PROFILING,
    UIEventSubtype_FEATURE_LABEL,
    UIEventSubtype_PREDICTION,
    UIEventSubtype_USER_CUSTOM
  };
  return values;
}

inline const char * const *EnumNamesUIEventSubtype() {
  static const char * const names[11] = {
    "NONE",
    "EVALUATION",
    "LOSS",
    "LEARNING_RATE",
    "TUNING_METRIC",
    "PERFORMANCE",
    "PROFILING",
    "FEATURE_LABEL",
    "PREDICTION",
    "USER_CUSTOM",
    nullptr
  };
  return names;
}

inline const char *EnumNameUIEventSubtype(UIEventSubtype e) {
  if (flatbuffers::IsOutRange(e, UIEventSubtype_NONE, UIEventSubtype_USER_CUSTOM)) return "";
  const size_t index = static_cast<size_t>(e);
  return EnumNamesUIEventSubtype()[index];
}

enum UIHistogramType {
  UIHistogramType_DISCRETE = 0,
  UIHistogramType_EQUAL_SPACING = 1,
  UIHistogramType_CUSTOM = 2,
  UIHistogramType_MIN = UIHistogramType_DISCRETE,
  UIHistogramType_MAX = UIHistogramType_CUSTOM
};

inline const UIHistogramType (&EnumValuesUIHistogramType())[3] {
  static const UIHistogramType values[] = {
    UIHistogramType_DISCRETE,
    UIHistogramType_EQUAL_SPACING,
    UIHistogramType_CUSTOM
  };
  return values;
}

inline const char * const *EnumNamesUIHistogramType() {
  static const char * const names[4] = {
    "DISCRETE",
    "EQUAL_SPACING",
    "CUSTOM",
    nullptr
  };
  return names;
}

inline const char *EnumNameUIHistogramType(UIHistogramType e) {
  if (flatbuffers::IsOutRange(e, UIHistogramType_DISCRETE, UIHistogramType_CUSTOM)) return "";
  const size_t index = static_cast<size_t>(e);
  return EnumNamesUIHistogramType()[index];
}

struct UIEvent FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  typedef UIEventBuilder Builder;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_EVENTTYPE = 4,
    VT_EVENTSUBTYPE = 6,
    VT_NAMEIDX = 8,
    VT_TIMESTAMP = 10,
    VT_ITERATION = 12,
    VT_EPOCH = 14,
    VT_VARIABLEID = 16,
    VT_FRAMEITER = 18,
    VT_PLUGIN = 20
  };
  UIEventType eventType() const { return static_cast<UIEventType>(GetField<int8_t>(VT_EVENTTYPE, 0)); }
  UIEventSubtype eventSubType() const {
    return static_cast<UIEventSubtype>(GetField<int8_t>(VT_EVENTSUBTYPE, 0));
  }
  int32_t nameIdx() const {
    return GetField<int32_t>(VT_NAMEIDX, 0);
  }
  int64_t timestamp() const {
    return GetField<int64_t>(VT_TIMESTAMP, 0);
  }
  int32_t iteration() const {
    return GetField<int32_t>(VT_ITERATION, 0);
  }
  int32_t epoch() const {
    return GetField<int32_t>(VT_EPOCH, 0);
  }
  int16_t variableId() const {
    return GetField<int16_t>(VT_VARIABLEID, 0);
  }
  const FrameIteration *frameIter() const {
    return GetPointer<const FrameIteration *>(VT_FRAMEITER);
  }
  uint16_t plugin() const {
    return GetField<uint16_t>(VT_PLUGIN, 0);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<int8_t>(verifier, VT_EVENTTYPE) &&
           VerifyField<int8_t>(verifier, VT_EVENTSUBTYPE) &&
           VerifyField<int32_t>(verifier, VT_NAMEIDX) &&
           VerifyField<int64_t>(verifier, VT_TIMESTAMP) &&
           VerifyField<int32_t>(verifier, VT_ITERATION) &&
           VerifyField<int32_t>(verifier, VT_EPOCH) &&
           VerifyField<int16_t>(verifier, VT_VARIABLEID) &&
           VerifyOffset(verifier, VT_FRAMEITER) &&
           verifier.VerifyTable(frameIter()) &&
           VerifyField<uint16_t>(verifier, VT_PLUGIN) &&
           verifier.EndTable();
  }
};

struct UIEventBuilder {
  typedef UIEvent Table;
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_eventType(UIEventType eventType) {
    fbb_.AddElement<int8_t>(UIEvent::VT_EVENTTYPE, static_cast<int8_t>(eventType), 0);
  }
  void add_eventSubType(UIEventSubtype eventSubType) {
    fbb_.AddElement<int8_t>(UIEvent::VT_EVENTSUBTYPE, static_cast<int8_t>(eventSubType), 0);
  }
  void add_nameIdx(int32_t nameIdx) {
    fbb_.AddElement<int32_t>(UIEvent::VT_NAMEIDX, nameIdx, 0);
  }
  void add_timestamp(int64_t timestamp) {
    fbb_.AddElement<int64_t>(UIEvent::VT_TIMESTAMP, timestamp, 0);
  }
  void add_iteration(int32_t iteration) {
    fbb_.AddElement<int32_t>(UIEvent::VT_ITERATION, iteration, 0);
  }
  void add_epoch(int32_t epoch) {
    fbb_.AddElement<int32_t>(UIEvent::VT_EPOCH, epoch, 0);
  }
  void add_variableId(int16_t variableId) {
    fbb_.AddElement<int16_t>(UIEvent::VT_VARIABLEID, variableId, 0);
  }
  void add_frameIter(flatbuffers::Offset<FrameIteration> frameIter) {
    fbb_.AddOffset(UIEvent::VT_FRAMEITER, frameIter);
  }
  void add_plugin(uint16_t plugin) {
    fbb_.AddElement<uint16_t>(UIEvent::VT_PLUGIN, plugin, 0);
  }
  explicit UIEventBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  UIEventBuilder &operator=(const UIEventBuilder &);
  flatbuffers::Offset<UIEvent> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<UIEvent>(end);
    return o;
  }
};

inline flatbuffers::Offset<UIEvent> CreateUIEvent(
    flatbuffers::FlatBufferBuilder &_fbb,
                                                  UIEventType eventType = UIEventType_ADD_NAME,
                                                  UIEventSubtype eventSubType = UIEventSubtype_NONE,
    int32_t nameIdx = 0,
    int64_t timestamp = 0,
    int32_t iteration = 0,
    int32_t epoch = 0,
    int16_t variableId = 0,
    flatbuffers::Offset<FrameIteration> frameIter = 0,
    uint16_t plugin = 0) {
  UIEventBuilder builder_(_fbb);
  builder_.add_timestamp(timestamp);
  builder_.add_frameIter(frameIter);
  builder_.add_epoch(epoch);
  builder_.add_iteration(iteration);
  builder_.add_nameIdx(nameIdx);
  builder_.add_plugin(plugin);
  builder_.add_variableId(variableId);
  builder_.add_eventSubType(eventSubType);
  builder_.add_eventType(eventType);
  return builder_.Finish();
}

struct FrameIteration FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  typedef FrameIterationBuilder Builder;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_FRAME = 4,
    VT_ITERATION = 6
  };
  const flatbuffers::String *frame() const {
    return GetPointer<const flatbuffers::String *>(VT_FRAME);
  }
  uint16_t iteration() const {
    return GetField<uint16_t>(VT_ITERATION, 0);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyOffset(verifier, VT_FRAME) &&
           verifier.VerifyString(frame()) &&
           VerifyField<uint16_t>(verifier, VT_ITERATION) &&
           verifier.EndTable();
  }
};

struct FrameIterationBuilder {
  typedef FrameIteration Table;
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_frame(flatbuffers::Offset<flatbuffers::String> frame) {
    fbb_.AddOffset(FrameIteration::VT_FRAME, frame);
  }
  void add_iteration(uint16_t iteration) {
    fbb_.AddElement<uint16_t>(FrameIteration::VT_ITERATION, iteration, 0);
  }
  explicit FrameIterationBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  FrameIterationBuilder &operator=(const FrameIterationBuilder &);
  flatbuffers::Offset<FrameIteration> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<FrameIteration>(end);
    return o;
  }
};

inline flatbuffers::Offset<FrameIteration> CreateFrameIteration(
    flatbuffers::FlatBufferBuilder &_fbb,
    flatbuffers::Offset<flatbuffers::String> frame = 0,
    uint16_t iteration = 0) {
  FrameIterationBuilder builder_(_fbb);
  builder_.add_frame(frame);
  builder_.add_iteration(iteration);
  return builder_.Finish();
}

inline flatbuffers::Offset<FrameIteration> CreateFrameIterationDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    const char *frame = nullptr,
    uint16_t iteration = 0) {
  auto frame__ = frame ? _fbb.CreateString(frame) : 0;
  return CreateFrameIteration(
      _fbb,
      frame__,
      iteration);
}

struct UIAddName FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  typedef UIAddNameBuilder Builder;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_NAMEIDX = 4,
    VT_NAME = 6
  };
  int32_t nameIdx() const {
    return GetField<int32_t>(VT_NAMEIDX, 0);
  }
  const flatbuffers::String *name() const {
    return GetPointer<const flatbuffers::String *>(VT_NAME);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<int32_t>(verifier, VT_NAMEIDX) &&
           VerifyOffset(verifier, VT_NAME) &&
           verifier.VerifyString(name()) &&
           verifier.EndTable();
  }
};

struct UIAddNameBuilder {
  typedef UIAddName Table;
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_nameIdx(int32_t nameIdx) {
    fbb_.AddElement<int32_t>(UIAddName::VT_NAMEIDX, nameIdx, 0);
  }
  void add_name(flatbuffers::Offset<flatbuffers::String> name) {
    fbb_.AddOffset(UIAddName::VT_NAME, name);
  }
  explicit UIAddNameBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  UIAddNameBuilder &operator=(const UIAddNameBuilder &);
  flatbuffers::Offset<UIAddName> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<UIAddName>(end);
    return o;
  }
};

inline flatbuffers::Offset<UIAddName> CreateUIAddName(
    flatbuffers::FlatBufferBuilder &_fbb,
    int32_t nameIdx = 0,
    flatbuffers::Offset<flatbuffers::String> name = 0) {
  UIAddNameBuilder builder_(_fbb);
  builder_.add_name(name);
  builder_.add_nameIdx(nameIdx);
  return builder_.Finish();
}

inline flatbuffers::Offset<UIAddName> CreateUIAddNameDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    int32_t nameIdx = 0,
    const char *name = nullptr) {
  auto name__ = name ? _fbb.CreateString(name) : 0;
  return CreateUIAddName(
      _fbb,
      nameIdx,
      name__);
}

struct FlatArrayList FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  typedef FlatArrayListBuilder Builder;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_LIST = 4
  };
  const flatbuffers::Vector<flatbuffers::Offset<FlatArray>> *list() const {
    return GetPointer<const flatbuffers::Vector<flatbuffers::Offset<FlatArray>> *>(VT_LIST);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyOffset(verifier, VT_LIST) &&
           verifier.VerifyVector(list()) &&
           verifier.VerifyVectorOfTables(list()) &&
           verifier.EndTable();
  }
};

struct FlatArrayListBuilder {
  typedef FlatArrayList Table;
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_list(flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<FlatArray>>> list) {
    fbb_.AddOffset(FlatArrayList::VT_LIST, list);
  }
  explicit FlatArrayListBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  FlatArrayListBuilder &operator=(const FlatArrayListBuilder &);
  flatbuffers::Offset<FlatArrayList> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<FlatArrayList>(end);
    return o;
  }
};

inline flatbuffers::Offset<FlatArrayList> CreateFlatArrayList(
    flatbuffers::FlatBufferBuilder &_fbb,
    flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<FlatArray>>> list = 0) {
  FlatArrayListBuilder builder_(_fbb);
  builder_.add_list(list);
  return builder_.Finish();
}

inline flatbuffers::Offset<FlatArrayList> CreateFlatArrayListDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    const std::vector<flatbuffers::Offset<FlatArray>> *list = nullptr) {
  auto list__ = list ? _fbb.CreateVector<flatbuffers::Offset<FlatArray>>(*list) : 0;
  return CreateFlatArrayList(
      _fbb,
      list__);
}

struct UIHistogram FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  typedef UIHistogramBuilder Builder;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_TYPE = 4,
    VT_NUMBINS = 6,
    VT_BINRANGES = 8,
    VT_Y = 10,
    VT_BINLABELS = 12
  };
  UIHistogramType type() const {
    return static_cast<UIHistogramType>(GetField<int8_t>(VT_TYPE, 0));
  }
  uint32_t numbins() const {
    return GetField<uint32_t>(VT_NUMBINS, 0);
  }
  const FlatArray *binranges() const {
    return GetPointer<const FlatArray *>(VT_BINRANGES);
  }
  const FlatArray *y() const {
    return GetPointer<const FlatArray *>(VT_Y);
  }
  const flatbuffers::Vector<flatbuffers::Offset<flatbuffers::String>> *binlabels() const {
    return GetPointer<const flatbuffers::Vector<flatbuffers::Offset<flatbuffers::String>> *>(VT_BINLABELS);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<int8_t>(verifier, VT_TYPE) &&
           VerifyField<uint32_t>(verifier, VT_NUMBINS) &&
           VerifyOffset(verifier, VT_BINRANGES) &&
           verifier.VerifyTable(binranges()) &&
           VerifyOffset(verifier, VT_Y) &&
           verifier.VerifyTable(y()) &&
           VerifyOffset(verifier, VT_BINLABELS) &&
           verifier.VerifyVector(binlabels()) &&
           verifier.VerifyVectorOfStrings(binlabels()) &&
           verifier.EndTable();
  }
};

struct UIHistogramBuilder {
  typedef UIHistogram Table;
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_type(UIHistogramType type) {
    fbb_.AddElement<int8_t>(UIHistogram::VT_TYPE, static_cast<int8_t>(type), 0);
  }
  void add_numbins(uint32_t numbins) {
    fbb_.AddElement<uint32_t>(UIHistogram::VT_NUMBINS, numbins, 0);
  }
  void add_binranges(flatbuffers::Offset<FlatArray> binranges) {
    fbb_.AddOffset(UIHistogram::VT_BINRANGES, binranges);
  }
  void add_y(flatbuffers::Offset<FlatArray> y) {
    fbb_.AddOffset(UIHistogram::VT_Y, y);
  }
  void add_binlabels(flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<flatbuffers::String>>> binlabels) {
    fbb_.AddOffset(UIHistogram::VT_BINLABELS, binlabels);
  }
  explicit UIHistogramBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  UIHistogramBuilder &operator=(const UIHistogramBuilder &);
  flatbuffers::Offset<UIHistogram> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<UIHistogram>(end);
    return o;
  }
};

inline flatbuffers::Offset<UIHistogram> CreateUIHistogram(
    flatbuffers::FlatBufferBuilder &_fbb, UIHistogramType type = UIHistogramType_DISCRETE,
    uint32_t numbins = 0,
    flatbuffers::Offset<FlatArray> binranges = 0,
    flatbuffers::Offset<FlatArray> y = 0,
    flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<flatbuffers::String>>> binlabels = 0) {
  UIHistogramBuilder builder_(_fbb);
  builder_.add_binlabels(binlabels);
  builder_.add_y(y);
  builder_.add_binranges(binranges);
  builder_.add_numbins(numbins);
  builder_.add_type(type);
  return builder_.Finish();
}

inline flatbuffers::Offset<UIHistogram> CreateUIHistogramDirect(
    flatbuffers::FlatBufferBuilder &_fbb, UIHistogramType type = UIHistogramType_DISCRETE,
    uint32_t numbins = 0,
    flatbuffers::Offset<FlatArray> binranges = 0,
    flatbuffers::Offset<FlatArray> y = 0,
    const std::vector<flatbuffers::Offset<flatbuffers::String>> *binlabels = nullptr) {
  auto binlabels__ = binlabels ? _fbb.CreateVector<flatbuffers::Offset<flatbuffers::String>>(*binlabels) : 0;
  return CreateUIHistogram(
      _fbb,
      type,
      numbins,
      binranges,
      y,
      binlabels__);
}

struct UISummaryStatistics FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  typedef UISummaryStatisticsBuilder Builder;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_BITMASK = 4,
    VT_MIN = 6,
    VT_MAX = 8,
    VT_MEAN = 10,
    VT_STDEV = 12,
    VT_COUNTZERO = 14,
    VT_COUNTPOSITIVE = 16,
    VT_COUNTNEGATIVE = 18,
    VT_COUNTNAN = 20,
    VT_COUNTINF = 22
  };
  uint32_t bitmask() const {
    return GetField<uint32_t>(VT_BITMASK, 0);
  }
  const FlatArray *min() const {
    return GetPointer<const FlatArray *>(VT_MIN);
  }
  const FlatArray *max() const {
    return GetPointer<const FlatArray *>(VT_MAX);
  }
  double mean() const {
    return GetField<double>(VT_MEAN, 0.0);
  }
  double stdev() const {
    return GetField<double>(VT_STDEV, 0.0);
  }
  int64_t countzero() const {
    return GetField<int64_t>(VT_COUNTZERO, 0);
  }
  int64_t countpositive() const {
    return GetField<int64_t>(VT_COUNTPOSITIVE, 0);
  }
  int64_t countnegative() const {
    return GetField<int64_t>(VT_COUNTNEGATIVE, 0);
  }
  int64_t countnan() const {
    return GetField<int64_t>(VT_COUNTNAN, 0);
  }
  int64_t countinf() const {
    return GetField<int64_t>(VT_COUNTINF, 0);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<uint32_t>(verifier, VT_BITMASK) &&
           VerifyOffset(verifier, VT_MIN) &&
           verifier.VerifyTable(min()) &&
           VerifyOffset(verifier, VT_MAX) &&
           verifier.VerifyTable(max()) &&
           VerifyField<double>(verifier, VT_MEAN) &&
           VerifyField<double>(verifier, VT_STDEV) &&
           VerifyField<int64_t>(verifier, VT_COUNTZERO) &&
           VerifyField<int64_t>(verifier, VT_COUNTPOSITIVE) &&
           VerifyField<int64_t>(verifier, VT_COUNTNEGATIVE) &&
           VerifyField<int64_t>(verifier, VT_COUNTNAN) &&
           VerifyField<int64_t>(verifier, VT_COUNTINF) &&
           verifier.EndTable();
  }
};

struct UISummaryStatisticsBuilder {
  typedef UISummaryStatistics Table;
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_bitmask(uint32_t bitmask) {
    fbb_.AddElement<uint32_t>(UISummaryStatistics::VT_BITMASK, bitmask, 0);
  }
  void add_min(flatbuffers::Offset<FlatArray> min) {
    fbb_.AddOffset(UISummaryStatistics::VT_MIN, min);
  }
  void add_max(flatbuffers::Offset<FlatArray> max) {
    fbb_.AddOffset(UISummaryStatistics::VT_MAX, max);
  }
  void add_mean(double mean) {
    fbb_.AddElement<double>(UISummaryStatistics::VT_MEAN, mean, 0.0);
  }
  void add_stdev(double stdev) {
    fbb_.AddElement<double>(UISummaryStatistics::VT_STDEV, stdev, 0.0);
  }
  void add_countzero(int64_t countzero) {
    fbb_.AddElement<int64_t>(UISummaryStatistics::VT_COUNTZERO, countzero, 0);
  }
  void add_countpositive(int64_t countpositive) {
    fbb_.AddElement<int64_t>(UISummaryStatistics::VT_COUNTPOSITIVE, countpositive, 0);
  }
  void add_countnegative(int64_t countnegative) {
    fbb_.AddElement<int64_t>(UISummaryStatistics::VT_COUNTNEGATIVE, countnegative, 0);
  }
  void add_countnan(int64_t countnan) {
    fbb_.AddElement<int64_t>(UISummaryStatistics::VT_COUNTNAN, countnan, 0);
  }
  void add_countinf(int64_t countinf) {
    fbb_.AddElement<int64_t>(UISummaryStatistics::VT_COUNTINF, countinf, 0);
  }
  explicit UISummaryStatisticsBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  UISummaryStatisticsBuilder &operator=(const UISummaryStatisticsBuilder &);
  flatbuffers::Offset<UISummaryStatistics> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<UISummaryStatistics>(end);
    return o;
  }
};

inline flatbuffers::Offset<UISummaryStatistics> CreateUISummaryStatistics(
    flatbuffers::FlatBufferBuilder &_fbb,
    uint32_t bitmask = 0,
    flatbuffers::Offset<FlatArray> min = 0,
    flatbuffers::Offset<FlatArray> max = 0,
    double mean = 0.0,
    double stdev = 0.0,
    int64_t countzero = 0,
    int64_t countpositive = 0,
    int64_t countnegative = 0,
    int64_t countnan = 0,
    int64_t countinf = 0) {
  UISummaryStatisticsBuilder builder_(_fbb);
  builder_.add_countinf(countinf);
  builder_.add_countnan(countnan);
  builder_.add_countnegative(countnegative);
  builder_.add_countpositive(countpositive);
  builder_.add_countzero(countzero);
  builder_.add_stdev(stdev);
  builder_.add_mean(mean);
  builder_.add_max(max);
  builder_.add_min(min);
  builder_.add_bitmask(bitmask);
  return builder_.Finish();
}

struct UIHardwareState FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  typedef UIHardwareStateBuilder Builder;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_GPUMEMORY = 4,
    VT_HOSTMEMORY = 6
  };
  const flatbuffers::Vector<int64_t> *gpuMemory() const {
    return GetPointer<const flatbuffers::Vector<int64_t> *>(VT_GPUMEMORY);
  }
  int64_t hostMemory() const {
    return GetField<int64_t>(VT_HOSTMEMORY, 0);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyOffset(verifier, VT_GPUMEMORY) &&
           verifier.VerifyVector(gpuMemory()) &&
           VerifyField<int64_t>(verifier, VT_HOSTMEMORY) &&
           verifier.EndTable();
  }
};

struct UIHardwareStateBuilder {
  typedef UIHardwareState Table;
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_gpuMemory(flatbuffers::Offset<flatbuffers::Vector<int64_t>> gpuMemory) {
    fbb_.AddOffset(UIHardwareState::VT_GPUMEMORY, gpuMemory);
  }
  void add_hostMemory(int64_t hostMemory) {
    fbb_.AddElement<int64_t>(UIHardwareState::VT_HOSTMEMORY, hostMemory, 0);
  }
  explicit UIHardwareStateBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  UIHardwareStateBuilder &operator=(const UIHardwareStateBuilder &);
  flatbuffers::Offset<UIHardwareState> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<UIHardwareState>(end);
    return o;
  }
};

inline flatbuffers::Offset<UIHardwareState> CreateUIHardwareState(
    flatbuffers::FlatBufferBuilder &_fbb,
    flatbuffers::Offset<flatbuffers::Vector<int64_t>> gpuMemory = 0,
    int64_t hostMemory = 0) {
  UIHardwareStateBuilder builder_(_fbb);
  builder_.add_hostMemory(hostMemory);
  builder_.add_gpuMemory(gpuMemory);
  return builder_.Finish();
}

inline flatbuffers::Offset<UIHardwareState> CreateUIHardwareStateDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    const std::vector<int64_t> *gpuMemory = nullptr,
    int64_t hostMemory = 0) {
  auto gpuMemory__ = gpuMemory ? _fbb.CreateVector<int64_t>(*gpuMemory) : 0;
  return CreateUIHardwareState(
      _fbb,
      gpuMemory__,
      hostMemory);
}

}  // namespace graph
}  // namespace sd

#endif  // FLATBUFFERS_GENERATED_UIGRAPHEVENTS_SD_GRAPH_H_
