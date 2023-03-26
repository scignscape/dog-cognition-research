/*
 * Copyright 2017 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */
#ifndef SkStubHeifDecoderAPI_DEFINED
#  define SkStubHeifDecoderAPI_DEFINED
// This stub implementation of HeifDecoderAPI.h lets us compile SkHeifCodec.cpp
// even when libheif is not available.  It, of course, does nothing and fails to decode.
#  include <memory>
#  include <stddef.h>
#  include <stdint.h>
enum HeifColorFormat {
    kHeifColorFormat_RGB565,
    kHeifColorFormat_RGBA_8888,
    kHeifColorFormat_BGRA_8888,
};
struct HeifStream
{
  virtual ~HeifStream()
  {
  }
  virtual size_t read(void*, size_t) = 0;
  virtual bool rewind() = 0;
  virtual bool seek(size_t) = 0;
  virtual bool hasLength() const = 0;
  virtual size_t getLength() const = 0;
};
struct HeifFrameInfo
{
  uint32_t mWidth;
  uint32_t mHeight;
  int32_t mRotationAngle;
  uint32_t mBytesPerPixel;
  int64_t mDurationUs;
  std::vector<uint8_t> mIccData;
};
struct HeifDecoder
{
  bool init(HeifStream* stream, HeifFrameInfo*)
  {
    delete stream;
    return false;
  }
  bool getSequenceInfo(HeifFrameInfo* frameInfo, size_t* frameCount)
  {
    return false;
  }
  bool decode(HeifFrameInfo*)
  {
    return false;
  }
  bool decodeSequence(int frameIndex, HeifFrameInfo* frameInfo)
  {
    return false;
  }
  bool setOutputColor(HeifColorFormat)
  {
    return false;
  }
  bool getScanline(uint8_t*)
  {
    return false;
  }
  int skipScanlines(int)
  {
    return 0;
  }
};
static HeifDecoder* createHeifDecoder()
{
  return new HeifDecoder;
}
#endif
