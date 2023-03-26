/*
 * Copyright 2013 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */
#ifndef SkPDFResourceDict_DEFINED
#  define SkPDFResourceDict_DEFINED
#  include "src/pdf/SkPDFFont.h"
#  include <vector>
class SkPDFDict;
class SkPDFObject;
class SkWStream;
enum class SkPDFResourceType {
    kExtGState = 0,
    kPattern = 1,
    kXObject = 2,
    kFont = 3,
    // These additional types are defined by the spec, but not
    // currently used by Skia: ColorSpace, Shading, Properties
};
/** Create a PDF resource dictionary.
 *  The full set of ProcSet entries is automatically created for backwards
 *  compatibility, as recommended by the PDF spec.
 *
 *  Any arguments can be nullptr.
 */
std::unique_ptr<SkPDFDict> SkPDFMakeResourceDict(const std::vector<SkPDFIndirectReference>& graphicStateResources, const std::vector<SkPDFIndirectReference>& shaderResources, const std::vector<SkPDFIndirectReference>& xObjectResources, const std::vector<SkPDFIndirectReference>& fontResources);
/**
 * Writes the name for the resource that will be generated by the resource
 * dict.
 *
 *  @param type  The type of resource being entered
 *  @param key   The resource key, should be unique within its type.
 */
void SkPDFWriteResourceName(SkWStream*, SkPDFResourceType type, int key);
#endif
