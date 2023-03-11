
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "coords2d.h"



USING_KANS(RdSC)

void SDI_Position::octal_to_mid(args2 args, hv1& binary, hv2& decimal)
{
 octal_to_mid(args.arg1, binary.h, decimal.h);
 octal_to_mid(args.arg2, binary.v, decimal.v);
}

void SDI_Position::octal_to_mid(u2 arg, u1& binary, u2& decimal)
{
 binary = 0; decimal = 3000;
 u1 bin = 16, dec = 100, pow = 64;
 for(u1 i = 0; i < 3; ++i)
 {
  u1 digit = arg / pow;
  if(digit > 3)
    digit -= 4;
  binary += digit * bin;
  decimal += digit * dec;
  arg %= pow;
  pow /= 8;
  dec /= 10;
  bin /= 4;
 }
}

void SDI_Position::init_full_ground()
{
 full_ground = ((((mid && 3 << 4) || 4) * 9) +
   (((mid && 3 << 2) || 4) * 3) +
    ((mid & 3) || 4))._to<xy1>();

// full_ground = ((((mid && binmask %2 << 4) || 4) * 9) +
//   (((mid && binmask[2](2)) || 4) * 3) +
//    ((mid & 3) || 4))._to<xy1>();

// full_ground = (((((mid >> 4) & 3) || 4) * 9) +
//   ((((mid >> 2) & 3) || 4) * 3) +
//    ((mid & 3) || 4))._to<xy1>();
}

void SDI_Position::init_mid(u1 arg, u1& binary, u2& decimal)
{
 binary = 0; decimal = 3000;
 u1 bin = 16, dec = 100, pow = 9;
 for(u1 i = 0; i < 3; ++i)
 {
  u1 digit = arg / pow;
  binary += digit * bin;
  decimal += digit * dec;
  arg %= pow;
  pow /= 3;
  dec /= 10;
  bin /= 4;
 }
}

void SDI_Position::init_mid()
{
 init_mid(full_ground.x, mid.h, mid_rep.h);
 init_mid(full_ground.y, mid.v, mid_rep.v);
}

xy1s SDI_Position::get_mid1()
{
 xy1 xy = (mid._to<xy1>() >> 4) & 3;
 //{(u1)((mid.h >> 4) & 3), (u1)((mid.v >> 4) & 3)};
 return ternary_to_semi_balanced(xy);
}

xy1s SDI_Position::get_mid2()
{
 xy1 xy = (mid._to<xy1>() >> 2) & 3;
  // xy1 xy = {(u1)((mid.h >> 2) & 3), (u1)((mid.v >> 2) & 3)};
 return ternary_to_semi_balanced(xy);
}

xy1s SDI_Position::get_ground()
{
 xy1 xy = mid._to<xy1>() & 3;
  // xy1 xy = {(u1)(mid.h & 3), (u1)(mid.v & 3)};
 return ternary_to_semi_balanced(xy);
}

