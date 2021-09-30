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

package org.nd4j.graph;
import java.nio.ByteOrder;
import java.nio.*;
import java.lang.*;
import java.util.*;
import com.google.flatbuffers.*;

@SuppressWarnings("unused")
public final class UIEvent extends Table {
  public static UIEvent getRootAsUIEvent(ByteBuffer _bb) { return getRootAsUIEvent(_bb, new UIEvent()); }
  public static UIEvent getRootAsUIEvent(ByteBuffer _bb, UIEvent obj) { _bb.order(ByteOrder.LITTLE_ENDIAN); return (obj.__assign(_bb.getInt(_bb.position()) + _bb.position(), _bb)); }
  public void __init(int _i, ByteBuffer _bb) { bb_pos = _i; bb = _bb; vtable_start = bb_pos - bb.getInt(bb_pos); vtable_size = bb.getShort(vtable_start); }
  public UIEvent __assign(int _i, ByteBuffer _bb) { __init(_i, _bb); return this; }

  public byte eventType() { int o = __offset(4); return o != 0 ? bb.get(o + bb_pos) : 0; }
  public byte eventSubType() { int o = __offset(6); return o != 0 ? bb.get(o + bb_pos) : 0; }
  public int nameIdx() { int o = __offset(8); return o != 0 ? bb.getInt(o + bb_pos) : 0; }
  public long timestamp() { int o = __offset(10); return o != 0 ? bb.getLong(o + bb_pos) : 0L; }
  public int iteration() { int o = __offset(12); return o != 0 ? bb.getInt(o + bb_pos) : 0; }
  public int epoch() { int o = __offset(14); return o != 0 ? bb.getInt(o + bb_pos) : 0; }
  public short variableId() { int o = __offset(16); return o != 0 ? bb.getShort(o + bb_pos) : 0; }
  public FrameIteration frameIter() { return frameIter(new FrameIteration()); }
  public FrameIteration frameIter(FrameIteration obj) { int o = __offset(18); return o != 0 ? obj.__assign(__indirect(o + bb_pos), bb) : null; }
  public int plugin() { int o = __offset(20); return o != 0 ? bb.getShort(o + bb_pos) & 0xFFFF : 0; }

  public static int createUIEvent(FlatBufferBuilder builder,
      byte eventType,
      byte eventSubType,
      int nameIdx,
      long timestamp,
      int iteration,
      int epoch,
      short variableId,
      int frameIterOffset,
      int plugin) {
    builder.startObject(9);
    UIEvent.addTimestamp(builder, timestamp);
    UIEvent.addFrameIter(builder, frameIterOffset);
    UIEvent.addEpoch(builder, epoch);
    UIEvent.addIteration(builder, iteration);
    UIEvent.addNameIdx(builder, nameIdx);
    UIEvent.addPlugin(builder, plugin);
    UIEvent.addVariableId(builder, variableId);
    UIEvent.addEventSubType(builder, eventSubType);
    UIEvent.addEventType(builder, eventType);
    return UIEvent.endUIEvent(builder);
  }

  public static void startUIEvent(FlatBufferBuilder builder) { builder.startObject(9); }
  public static void addEventType(FlatBufferBuilder builder, byte eventType) { builder.addByte(0, eventType, 0); }
  public static void addEventSubType(FlatBufferBuilder builder, byte eventSubType) { builder.addByte(1, eventSubType, 0); }
  public static void addNameIdx(FlatBufferBuilder builder, int nameIdx) { builder.addInt(2, nameIdx, 0); }
  public static void addTimestamp(FlatBufferBuilder builder, long timestamp) { builder.addLong(3, timestamp, 0L); }
  public static void addIteration(FlatBufferBuilder builder, int iteration) { builder.addInt(4, iteration, 0); }
  public static void addEpoch(FlatBufferBuilder builder, int epoch) { builder.addInt(5, epoch, 0); }
  public static void addVariableId(FlatBufferBuilder builder, short variableId) { builder.addShort(6, variableId, 0); }
  public static void addFrameIter(FlatBufferBuilder builder, int frameIterOffset) { builder.addOffset(7, frameIterOffset, 0); }
  public static void addPlugin(FlatBufferBuilder builder, int plugin) { builder.addShort(8, (short)plugin, (short)0); }
  public static int endUIEvent(FlatBufferBuilder builder) {
    int o = builder.endObject();
    return o;
  }
}

