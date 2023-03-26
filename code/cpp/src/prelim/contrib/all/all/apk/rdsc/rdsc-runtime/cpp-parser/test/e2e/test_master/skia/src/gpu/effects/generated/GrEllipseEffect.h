/*
 * Copyright 2017 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

/**************************************************************************************************
 *** This file was autogenerated from GrEllipseEffect.fp; do not modify.
 **************************************************************************************************/
#ifndef GrEllipseEffect_DEFINED
#  define GrEllipseEffect_DEFINED
#  include "include/core/SkTypes.h"
#  include "src/gpu/GrShaderCaps.h"
#  include "src/gpu/GrCoordTransform.h"
#  include "src/gpu/GrFragmentProcessor.h"
class GrEllipseEffect : public GrFragmentProcessor
{
public:
  static std::unique_ptr<GrFragmentProcessor> Make(GrClipEdgeType edgeType, SkPoint center, SkPoint radii, const GrShaderCaps& caps)
  {
        // Small radii produce bad results on devices without full float.
    if (!caps.floatIs32Bits() && (radii.fX < 0.5f || radii.fY < 0.5f))
    {
      return nullptr;
    }
        // Very narrow ellipses produce bad results on devices without full float
    if (!caps.floatIs32Bits() && (radii.fX > 255 * radii.fY || radii.fY > 255 * radii.fX))
    {
      return nullptr;
    }
        // Very large ellipses produce bad results on devices without full float
    if (!caps.floatIs32Bits() && (radii.fX > 16384 || radii.fY > 16384))
    {
      return nullptr;
    }
    return std::unique_ptr<GrFragmentProcessor>(new GrEllipseEffect(edgeType, center, radii));
  }
  GrEllipseEffect(const GrEllipseEffect& src);
  std::unique_ptr<GrFragmentProcessor> clone() const override;
  const char* name() const override
  {
    return "EllipseEffect";
  }
  GrClipEdgeType edgeType;
  SkPoint center;
  SkPoint radii;
private:
  GrEllipseEffect(GrClipEdgeType edgeType, SkPoint center, SkPoint radii)
    : INHERITED(kGrEllipseEffect_ClassID, (OptimizationFlags) kCompatibleWithCoverageAsAlpha_OptimizationFlag)
    , edgeType(edgeType)
    , center(center)
    , radii(radii)
  {
  }
  GrGLSLFragmentProcessor* onCreateGLSLInstance() const override;
  void onGetGLSLProcessorKey(const GrShaderCaps&, GrProcessorKeyBuilder*) const override;
  bool onIsEqual(const GrFragmentProcessor&) const override;
  GR_DECLARE_FRAGMENT_PROCESSOR_TEST
  typedef GrFragmentProcessor INHERITED;
};
#endif
