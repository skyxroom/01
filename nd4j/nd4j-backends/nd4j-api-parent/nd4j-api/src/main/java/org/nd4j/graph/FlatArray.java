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
public final class FlatArray extends Table {
  public static FlatArray getRootAsFlatArray(ByteBuffer _bb) { return getRootAsFlatArray(_bb, new FlatArray()); }
  public static FlatArray getRootAsFlatArray(ByteBuffer _bb, FlatArray obj) { _bb.order(ByteOrder.LITTLE_ENDIAN); return (obj.__assign(_bb.getInt(_bb.position()) + _bb.position(), _bb)); }
  public void __init(int _i, ByteBuffer _bb) { bb_pos = _i; bb = _bb; vtable_start = bb_pos - bb.getInt(bb_pos); vtable_size = bb.getShort(vtable_start); }
  public FlatArray __assign(int _i, ByteBuffer _bb) { __init(_i, _bb); return this; }

  public long shape(int j) { int o = __offset(4); return o != 0 ? bb.getLong(__vector(o) + j * 8) : 0; }
  public int shapeLength() { int o = __offset(4); return o != 0 ? __vector_len(o) : 0; }
  public ByteBuffer shapeAsByteBuffer() { return __vector_as_bytebuffer(4, 8); }
  public ByteBuffer shapeInByteBuffer(ByteBuffer _bb) { return __vector_in_bytebuffer(_bb, 4, 8); }
  public byte buffer(int j) { int o = __offset(6); return o != 0 ? bb.get(__vector(o) + j * 1) : 0; }
  public int bufferLength() { int o = __offset(6); return o != 0 ? __vector_len(o) : 0; }
  public ByteBuffer bufferAsByteBuffer() { return __vector_as_bytebuffer(6, 1); }
  public ByteBuffer bufferInByteBuffer(ByteBuffer _bb) { return __vector_in_bytebuffer(_bb, 6, 1); }
  public byte dtype() { int o = __offset(8); return o != 0 ? bb.get(o + bb_pos) : 0; }
  public byte byteOrder() { int o = __offset(10); return o != 0 ? bb.get(o + bb_pos) : 0; }

  public static int createFlatArray(FlatBufferBuilder builder,
      int shapeOffset,
      int bufferOffset,
      byte dtype,
      byte byteOrder) {
    builder.startObject(4);
    FlatArray.addBuffer(builder, bufferOffset);
    FlatArray.addShape(builder, shapeOffset);
    FlatArray.addByteOrder(builder, byteOrder);
    FlatArray.addDtype(builder, dtype);
    return FlatArray.endFlatArray(builder);
  }

  public static void startFlatArray(FlatBufferBuilder builder) { builder.startObject(4); }
  public static void addShape(FlatBufferBuilder builder, int shapeOffset) { builder.addOffset(0, shapeOffset, 0); }
  public static int createShapeVector(FlatBufferBuilder builder, long[] data) { builder.startVector(8, data.length, 8); for (int i = data.length - 1; i >= 0; i--) builder.addLong(data[i]); return builder.endVector(); }
  public static void startShapeVector(FlatBufferBuilder builder, int numElems) { builder.startVector(8, numElems, 8); }
  public static void addBuffer(FlatBufferBuilder builder, int bufferOffset) { builder.addOffset(1, bufferOffset, 0); }
  public static int createBufferVector(FlatBufferBuilder builder, byte[] data) { builder.startVector(1, data.length, 1); for (int i = data.length - 1; i >= 0; i--) builder.addByte(data[i]); return builder.endVector(); }
  public static void startBufferVector(FlatBufferBuilder builder, int numElems) { builder.startVector(1, numElems, 1); }
  public static void addDtype(FlatBufferBuilder builder, byte dtype) { builder.addByte(2, dtype, 0); }
  public static void addByteOrder(FlatBufferBuilder builder, byte byteOrder) { builder.addByte(3, byteOrder, 0); }
  public static int endFlatArray(FlatBufferBuilder builder) {
    int o = builder.endObject();
    return o;
  }
  public static void finishFlatArrayBuffer(FlatBufferBuilder builder, int offset) { builder.finish(offset); }
  public static void finishSizePrefixedFlatArrayBuffer(FlatBufferBuilder builder, int offset) { builder.finishSizePrefixed(offset); }
}

