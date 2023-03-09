
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "hive-structure.h"

#include "global-types.h"

#include <QVector>
#include <QString>
#include <QMap>

#include <QDebug>

USING_XCNS(XCSD)


XCNS_(XCSD)

bool get_permutation_numbers(u1 code, u1& first, u1& second, u1& third, u1& fourth)
{
 static u1 result [96] {
  1, 2, 3, 4,  //  4
  1, 2, 4, 3,  //  8
  1, 3, 2, 4,  //  12
  1, 3, 4, 2,  //  16
  1, 4, 2, 3,  //  20
  1, 4, 3, 2,  //  24
  2, 1, 3, 4,  //  28
  2, 1, 4, 3,  //  32
  2, 3, 1, 4,  //  36
  2, 3, 4, 1,  //  40
  2, 4, 1, 3,  //  44
  2, 4, 3, 1,  //  48
  3, 1, 2, 4,  //  52
  3, 1, 4, 2,  //  56
  3, 2, 1, 4,  //  60
  3, 2, 4, 1,  //  64
  3, 4, 1, 2,  //  68
  3, 4, 2, 1,  //  72
  4, 1, 2, 3,  //  76
  4, 1, 3, 2,  //  80
  4, 2, 1, 3,  //  84
  4, 2, 3, 1,  //  88
  4, 3, 1, 2,  //  92
  4, 3, 2, 1,  //  96
 };

 u1 index = code * 4;

 if(index >= 96)
   return false;

 first = result[index];
 second = result[++index];
 third = result[++index];
 fourth = result[++index];

 return true;
}

bool get_permutation_numbers(u1 code, u1& first, u1& second, u1& third)
{
 static u1 result [18] {
  1, 2, 3,  //  3
  1, 3, 2,  //  6
  2, 1, 3,  //  9
  2, 3, 1,  //  12
  3, 1, 2,  //  15
  3, 2, 1,  //  18
 };

 u1 index = code * 3;

 if(index >= 18)
   return false;

 first = result[index];
 second = result[++index];
 third = result[++index];

 return true;
}

s1 get_permutation_code(u1& mask, Out_of_Bounds_Resolution_Flags first,
  Out_of_Bounds_Resolution_Flags second)
{
 mask = (u1) (first | second);

 if(first < second)
   return 30;
 return 31;
}

s1 get_permutation_code(u1& mask, Out_of_Bounds_Resolution_Flags first, Out_of_Bounds_Resolution_Flags second,
   Out_of_Bounds_Resolution_Flags third, Out_of_Bounds_Resolution_Flags fourth)
{
 mask = (u1) (first | second | third | fourth);

 u1 c1 = 1, _c1 = (u1) first >> 4;
 u1 c2 = 1, _c2 = (u1) second >> 4;
 u1 c3 = 1, _c3 = (u1) third >> 4;
 u1 c4 = 1, _c4 = (u1) fourth >> 4;

 while(_c1 >>= 1) ++c1;
 while(_c2 >>= 1) ++c2;
 while(_c3 >>= 1) ++c3;
 while(_c4 >>= 1) ++c4;

 u2 switch_code = c4 + c3 * 8 + c2 * 64 + c1 * 512;

 switch (switch_code)
 {
  case 01234: return 0;
  case 01243: return 1;
  case 01324: return 2;
  case 01342: return 3;
  case 01423: return 4;
  case 01432: return 5;
  case 02134: return 6;
  case 02143: return 7;
  case 02314: return 8;
  case 02341: return 9;
  case 02413: return 10;
  case 02431: return 11;
  case 03124: return 12;
  case 03142: return 13;
  case 03214: return 14;
  case 03241: return 15;
  case 03412: return 16;
  case 03421: return 17;
  case 04123: return 18;
  case 04132: return 19;
  case 04213: return 20;
  case 04231: return 21;
  case 04312: return 22;
  case 04321: return 23;
   break;

  default:
   return -1;
 }
}



s1 get_permutation_code(u1& mask, Out_of_Bounds_Resolution_Flags first, Out_of_Bounds_Resolution_Flags second,
   Out_of_Bounds_Resolution_Flags third)
{
 mask = (u1) (first | second | third);

 u1 c1 = 1, c2 = 1, c3 = 1;

 if(first > second)
   ++c1;
 else
   ++c2;
 if(first > third)
   ++c1;
 else
   ++c3;
 if(second > third)
   ++c2;
 else
   ++c3;


 u1 switch_code = c3 + c2 * 8 + c1 * 64;

 u1 offset = 24;

 switch (switch_code)
 {
  case 0123: return offset + 0;
  case 0132: return offset + 1;
  case 0213: return offset + 2;
  case 0231: return offset + 3;
  case 0312: return offset + 4;
  case 0321: return offset + 5;
   break;

  default:
   return -1;
 }
}

void parse_permutation_code(u1 code, u1 mask, Out_of_Bounds_Resolution_Flags& first, Out_of_Bounds_Resolution_Flags& second,
  Out_of_Bounds_Resolution_Flags& third, Out_of_Bounds_Resolution_Flags& fourth)
{
 u2 preshift = (u2) (1 << (monotone_offset - 1)); //Out_of_Bounds_Resolution_Flags::Highest_Value_Before_Actions;

 u1 mshifted = mask >> 4;
 first = second = third = fourth = Out_of_Bounds_Resolution_Flags::N_A;
 if(mshifted == 0)
   return;
 if(code > 31)
   return;
 if(code > 29)
 {
  u1 low, high;
  switch(mshifted)
  {
  case 3: // 12
   low = 1; high = 2; break;
  case 5: // 14
   low = 1; high = 4; break;
  case 9: // 18
   low = 1; high = 8; break;
  case 6: // 24
   low = 2; high = 4; break;
  case 10: // 28
   low = 2; high = 8; break;
  case 12: // 48
   low = 4; high = 8; break;
  default: return;
  }
  if(code == 30)
  {
   first = (Out_of_Bounds_Resolution_Flags) (low << 4);
   second = (Out_of_Bounds_Resolution_Flags) (high << 4);
   return;
  }
  first = (Out_of_Bounds_Resolution_Flags) (high << 4);
  second = (Out_of_Bounds_Resolution_Flags) (low << 4);
  return;
 }

 if(code > 23)
 {
//  Out_of_Bounds_Resolution_Flags *low, *mid, *high;
  u1 low, mid, high;
//  get_permutation_numbers(code - 24, low, mid, high);

  switch(mshifted)
  {
  case 7: // 124
   low = 1; mid = 2; high = 3; break;
  case 11: // 128
   low = 1; mid = 2; high = 4; break;
  case 13: // 148
   low = 1; mid = 3; high = 4; break;
  case 14: // 248
   low = 2; mid = 3; high = 4; break;
  default: return;
  }

  u1 p1, p2, p3;
  bool ok = get_permutation_numbers(code - 24, p1, p2, p3);
  if(!ok)
    return;
  first = (p1 == 1)?(Out_of_Bounds_Resolution_Flags) (preshift << low)
        : (p1 == 2)?(Out_of_Bounds_Resolution_Flags) (preshift << mid)
        : (Out_of_Bounds_Resolution_Flags) (preshift << high);
  second = (p2 == 1)?(Out_of_Bounds_Resolution_Flags) (preshift << low)
         : (p2 == 2)?(Out_of_Bounds_Resolution_Flags) (preshift << mid)
         : (Out_of_Bounds_Resolution_Flags) (preshift << high);
  third = (p3 == 1)?(Out_of_Bounds_Resolution_Flags) (preshift << low)
         : (p3 == 2)?(Out_of_Bounds_Resolution_Flags) (preshift << mid)
         : (Out_of_Bounds_Resolution_Flags) (preshift << high);
  return;
 }

 if(mshifted < 15)
 {
  switch (mshifted)
  {
  case 1: case 2: case 4: case 8: first = (Out_of_Bounds_Resolution_Flags) mask;
   return;
  default: return;;
  }
 }

 u1 p1, p2, p3, p4;
 bool ok = get_permutation_numbers(code, p1, p2, p3, p4);
 if(!ok)
   return;

 first = (Out_of_Bounds_Resolution_Flags) (preshift << p1);
 second = (Out_of_Bounds_Resolution_Flags) (preshift << p2);
 third = (Out_of_Bounds_Resolution_Flags) (preshift << p3);
 fourth = (Out_of_Bounds_Resolution_Flags) (preshift << p4);
}

u2 encode_double_mitigation_flags(Out_of_Bounds_Resolution_Flags index,
  Out_of_Bounds_Resolution_Flags alt)
{

}

u2 encode_double_mitigation_flags(s1 split, Out_of_Bounds_Resolution_Flags f1)
{
 switch(split)
 {
 case 0: return encode_double_mitigation_flags_1_0(f1);
 case -1: return encode_double_mitigation_flags_0_1(f1);
 default: return 0;
 }
}

u2 encode_double_mitigation_flags(s1 split, Out_of_Bounds_Resolution_Flags f1,
  Out_of_Bounds_Resolution_Flags f2)
{
 switch(split)
 {
 case 0: return encode_double_mitigation_flags_2_0(f1, f2);
 case 1: return encode_double_mitigation_flags_1_1(f1, f2);
 case -1: return encode_double_mitigation_flags_0_2(f1, f2);
 default: return 0;
 }
}

u2 encode_double_mitigation_flags(s1 split, Out_of_Bounds_Resolution_Flags f1,
  Out_of_Bounds_Resolution_Flags f2,
  Out_of_Bounds_Resolution_Flags f3)
{
 switch(split)
 {
 case 0: return encode_double_mitigation_flags_3_0(f1, f2, f3);
 case 1: return encode_double_mitigation_flags_1_2(f1, f2, f3);
 case 2: return encode_double_mitigation_flags_2_1(f1, f2, f3);
 case -1: return encode_double_mitigation_flags_0_3(f1, f2, f3);
 default: return 0;
 }
}

u2 encode_double_mitigation_flags(s1 split, Out_of_Bounds_Resolution_Flags f1,
  Out_of_Bounds_Resolution_Flags f2,
  Out_of_Bounds_Resolution_Flags f3,
  Out_of_Bounds_Resolution_Flags f4)
{
 switch(split)
 {
 case 0: return encode_double_mitigation_flags_4_0(f1, f2, f3, f4);
 case 1: return encode_double_mitigation_flags_1_3(f1, f2, f3, f4);
 case 2: return encode_double_mitigation_flags_2_2(f1, f2, f3, f4);
 case 3: return encode_double_mitigation_flags_3_1(f1, f2, f3, f4);
 case -1: return encode_double_mitigation_flags_0_4(f1, f2, f3, f4);
 default: return 0;
 }
}

u2 encode_double_mitigation_flags(s1 split, Out_of_Bounds_Resolution_Flags f1,
  Out_of_Bounds_Resolution_Flags f2,
  Out_of_Bounds_Resolution_Flags f3,
  Out_of_Bounds_Resolution_Flags f4,
  Out_of_Bounds_Resolution_Flags f5)
{
 switch(split)
 {
 case 1: return encode_double_mitigation_flags_1_4(f1, f2, f3, f4, f5);
 case 2: return encode_double_mitigation_flags_2_3(f1, f2, f3, f4, f5);
 case 3: return encode_double_mitigation_flags_3_2(f1, f2, f3, f4, f5);
 case 4: return encode_double_mitigation_flags_4_1(f1, f2, f3, f4, f5);
 default: return 0;
 }
}

u2 encode_double_mitigation_flags(s1 split, Out_of_Bounds_Resolution_Flags f1,
  Out_of_Bounds_Resolution_Flags f2,
  Out_of_Bounds_Resolution_Flags f3,
  Out_of_Bounds_Resolution_Flags f4,
  Out_of_Bounds_Resolution_Flags f5,
  Out_of_Bounds_Resolution_Flags f6)
{
 switch(split)
 {
 case 2: return encode_double_mitigation_flags_2_4(f1, f2, f3, f4, f5, f6);
 case 3: return encode_double_mitigation_flags_3_3(f1, f2, f3, f4, f5, f6);
 case 4: return encode_double_mitigation_flags_4_2(f1, f2, f3, f4, f5, f6);
 default: return 0;
 }
}

u2 encode_double_mitigation_flags(s1 split, Out_of_Bounds_Resolution_Flags f1,
  Out_of_Bounds_Resolution_Flags f2,
  Out_of_Bounds_Resolution_Flags f3,
  Out_of_Bounds_Resolution_Flags f4,
  Out_of_Bounds_Resolution_Flags f5,
  Out_of_Bounds_Resolution_Flags f6,
  Out_of_Bounds_Resolution_Flags f7)
{
 switch(split)
 {
 case 3: return encode_double_mitigation_flags_4_3(f1, f2, f3, f4, f5, f6, f7);
 case 4: return encode_double_mitigation_flags_3_4(f1, f2, f3, f4, f5, f6, f7);
 default: return 0;
 }
}


u1 _decode_mitigation_flags_alt_0to9(u1 encoding,
  Out_of_Bounds_Resolution_Flags& f1,
  Out_of_Bounds_Resolution_Flags& f2,
  Out_of_Bounds_Resolution_Flags& f3,
  Out_of_Bounds_Resolution_Flags& f4)
{
 u1 m1 = 0, m2 = 0;
 bool odd = (encoding & 1);
 switch (encoding / 2)
 {
 case 0: m1 = 1; m2 = 3; break;  // 13
 case 1: m1 = 1; m2 = 4; break;  // 14
 case 2: m1 = 2; m2 = 3; break;  // 23
 case 3: m1 = 2; m2 = 4; break;  // 24
 case 4: m1 = 3; m2 = 4; break;  // 34
 }

 if(odd)
   std::swap(m1, m2);

 f1 = (Out_of_Bounds_Resolution_Flags) demonotone(m1);
 f2 = (Out_of_Bounds_Resolution_Flags) demonotone(m2);

 return 2; // 2 non-N_A's
}

u1 _decode_mitigation_flags_alt_10to27(u1 encoding,
  Out_of_Bounds_Resolution_Flags& f1,
  Out_of_Bounds_Resolution_Flags& f2,
  Out_of_Bounds_Resolution_Flags& f3,
  Out_of_Bounds_Resolution_Flags& f4)
{
 encoding -= 10;
 u1 excluded = encoding / 6;
 excluded = 1 << excluded;
 encoding %= 6;
 encoding += 24;

 u1 mask = 15 - excluded; // clear the bit of the excluded one
 mask <<= 4;

 parse_permutation_code(encoding, mask, f1, f2, f3, f4);

 return 3; // 3 non-N_A's
}


u1 _decode_mitigation_flags_alt(u1 encoding,
  Out_of_Bounds_Resolution_Flags& f1,
  Out_of_Bounds_Resolution_Flags& f2,
  Out_of_Bounds_Resolution_Flags& f3,
  Out_of_Bounds_Resolution_Flags& f4)
{
 if(encoding < 10)
   return _decode_mitigation_flags_alt_0to9(encoding, f1, f2, f3, f4);

 if(encoding < 28)
   return _decode_mitigation_flags_alt_10to27(encoding, f1, f2, f3, f4);

 u1 mask = encoding - 27;
 f1 = demonotone(mask);

 return 1;


}

//std::pair<u1, u1> decode_double_mitigation_flags(u2 encoding,15
//  Out_of_Bounds_Resolution_Flags& f11,
//  Out_of_Bounds_Resolution_Flags& f12,
//  Out_of_Bounds_Resolution_Flags& f13,
//  Out_of_Bounds_Resolution_Flags& f14,
//  Out_of_Bounds_Resolution_Flags& f21,
//  Out_of_Bounds_Resolution_Flags& f22,
//  Out_of_Bounds_Resolution_Flags& f23,
//  Out_of_Bounds_Resolution_Flags& f24)

std::pair<u1, u1> parse_double_mitigation_flags_encoding(u2 encoding)
{
 u2 supp = encoding & 0b111'11100'0000'0000;
 u1 enc = encoding & 63; // 0b0011'1111
 encoding &= ~supp;
 u1 fallback_enc = encoding >> 6; // 0b0011'1111
 return {enc, fallback_enc};
}

std::pair<u1, u1> decode_double_mitigation_flags(u2 encoding,
  Out_of_Bounds_Resolution_Flags& supplement,
  Out_of_Bounds_Resolution_Flags& f11,
  Out_of_Bounds_Resolution_Flags& f12,
  Out_of_Bounds_Resolution_Flags& f13,
  Out_of_Bounds_Resolution_Flags& f14,
  Out_of_Bounds_Resolution_Flags& f21,
  Out_of_Bounds_Resolution_Flags& f22,
  Out_of_Bounds_Resolution_Flags& f23,
  Out_of_Bounds_Resolution_Flags& f24)
{
 u2 supp = encoding & 0b111'11100'0000'0000;
 u1 enc = encoding & 63; // 0b0011'1111
 supplement = (Out_of_Bounds_Resolution_Flags) (supp >> 10);
 encoding &= ~supp;
 u1 fallback_enc = encoding >> 6; // 0b0011'1111

 // //  check for the no-action signal ...
  // // maybe fallback_enc == 15 as another test ..
 if((enc == 0) && (supplement & Out_of_Bounds_Resolution_Flags::Delay_Mitigation_on_Fallback))
 {
  u2 mask = ~(u2)Out_of_Bounds_Resolution_Flags::Delay_Mitigation_on_Fallback;
  supplement = (Out_of_Bounds_Resolution_Flags) ((u2) supplement & mask);
  u1 result_first = 0;
  f11 = f12 = f13 = f14 = Out_of_Bounds_Resolution_Flags::N_A;
  u1 result_second = decode_fallback_mitigation_flags(fallback_enc, f21, f22, f23, f24);
  return std::make_pair(result_first, result_second);
 }
 else
 {
  u1 result_first = decode_mitigation_flags(enc, f11, f12, f13, f14);
  u1 result_second = decode_fallback_mitigation_flags(fallback_enc, f21, f22, f23, f24);
  return std::make_pair(result_first, result_second);
 }
}

u1 decode_mitigation_flags(u1 encoding,
  Out_of_Bounds_Resolution_Flags& f1,
  Out_of_Bounds_Resolution_Flags& f2,
  Out_of_Bounds_Resolution_Flags& f3,
  Out_of_Bounds_Resolution_Flags& f4)
{
 f1 = f2 = f3 = f4 = Out_of_Bounds_Resolution_Flags::N_A;

 if(encoding & 0b0010'0000)
   return _decode_mitigation_flags_alt(encoding & 0b0001'1111, f1, f2, f3, f4);

 if(encoding == 30)
 {
  f1 = demonotone(1); f2 = demonotone(2); return 2;
 }
 if(encoding == 31)
 {
  f1 = demonotone(2); f2 = demonotone(1); return 2;
 }
 if(encoding < 24)
 {
  u1 mask = 15 << 4;
  parse_permutation_code(encoding, mask, f1, f2, f3, f4);
  return 4; // 4 non-N_A's
 }

 u1 mask = 7 << 4; //?(u1)demonotone(1) | (u1)demonotone(2) | (u1)demonotone(3);
 parse_permutation_code(encoding, mask, f1, f2, f3, f4);
 return 3; // 3 non-N_A's
}

u1 decode_fallback_mitigation_flags(u1 encoding,
  Out_of_Bounds_Resolution_Flags& f1,
  Out_of_Bounds_Resolution_Flags& f2,
  Out_of_Bounds_Resolution_Flags& f3,
  Out_of_Bounds_Resolution_Flags& f4)
{
 f1 = f2 = f3 = f4 = Out_of_Bounds_Resolution_Flags::N_A;

 if(encoding == 15)
   return 0;
 if(encoding < 6)
 {
  u1 mask = 7 << 4; //?(u1)demonotone(1) | (u1)demonotone(2) | (u1)demonotone(3);
  parse_permutation_code(encoding + 24, mask, f1, f2, f3, f4);
  return 3; // 3 non-N_A's
 }
 if(encoding < 12)
 {
  u1 m1, m2;
  bool odd = encoding & 1;
  switch (encoding / 2)
  {
  case 3: m1 = 1; m2 = 2; break;
  case 4: m1 = 1; m2 = 3; break;
  case 5: m1 = 2; m2 = 3; break;
  default: return 0;
  }
  if(odd)
    std::swap(m1, m2);

  f1 = (Out_of_Bounds_Resolution_Flags) demonotone(m1);
  f2 = (Out_of_Bounds_Resolution_Flags) demonotone(m2);

  return 2; // 3 non-N_A's
 }
 encoding -= 11;
 f1 = demonotone(encoding);
 return 1;
}



u1 encode_mitigation_flags(Out_of_Bounds_Resolution_Flags f1)
{
 u1 m = monotone(f1);
 u1 result = 0b0010'0000; // set alt permutation interpretation
 m += 27;
 result += m;
 return result;
}

u1 encode_mitigation_flags(Out_of_Bounds_Resolution_Flags f1,
  Out_of_Bounds_Resolution_Flags f2)
{
 u1 m1 = monotone(f1);
 u1 m2 = monotone(f2);

 u2 oct = octal(m1, m2);

 u1 alt_index = 0;
 switch (oct)
 {
 case 012: return 30; // normal permutation interpretation
 case 021: return 31; // normal permutation interpretation
 case 013: alt_index = 0; break; // alt permutation interpretation
 case 031: alt_index = 1; break; // alt permutation interpretation
 case 014: alt_index = 2; break; // alt permutation interpretation
 case 041: alt_index = 3; break; // alt permutation interpretation
 case 023: alt_index = 4; break; // alt permutation interpretation
 case 032: alt_index = 5; break; // alt permutation interpretation
 case 024: alt_index = 6; break; // alt permutation interpretation
 case 042: alt_index = 7; break; // alt permutation interpretation
 case 034: alt_index = 8; break; // alt permutation interpretation
 case 043: alt_index = 9; break; // alt permutation interpretation
 default: return 0;
 }

 u1 result = 0b0010'0000; // set alt perutation interpretation
 result += alt_index;
 return result;
}

u1 encode_fallback_mitigation_flags(Out_of_Bounds_Resolution_Flags f1)
{
 u1 m1 = monotone(f1);
 return m1 + 11;
}

u1 encode_fallback_mitigation_flags(Out_of_Bounds_Resolution_Flags f1,
  Out_of_Bounds_Resolution_Flags f2)
{
 u1 m1 = monotone(f1);
 u1 m2 = monotone(f2);

 u2 oct = octal(m1, m2);

 switch (oct)
 {
 case 012: return 6; // normal permutation interpretation
 case 021: return 7; // normal permutation interpretation
 case 013: return 8; // alt permutation interpretation
 case 031: return 9; // alt permutation interpretation
 case 023: return 10; // alt permutation interpretation
 case 032: return 11; // alt permutation interpretation
 default: return 0;
 }

}


u1 encode_fallback_mitigation_flags(Out_of_Bounds_Resolution_Flags f1,
  Out_of_Bounds_Resolution_Flags f2,
  Out_of_Bounds_Resolution_Flags f3)
{
 u1 mask = 0;
 s1 enc = get_permutation_code(mask, f1, f2, f3);
 if(enc == -1)
   return 0;
 return enc - 24;
}


u1 encode_mitigation_flags(Out_of_Bounds_Resolution_Flags f1,
  Out_of_Bounds_Resolution_Flags f2,
  Out_of_Bounds_Resolution_Flags f3)
{
 u1 mask = 0;
 s1 enc = get_permutation_code(mask, f1, f2, f3);

 if(enc == -1)
   return 0;

 mask >>= 4;

 u1 alt;
 // //  which option is excluded?
 switch(mask)
 {
 case 7: // 124
   // //  no need for alt ...
   return enc;
 case 11: // 128
   alt = 4; break;
 case 13: // 148
   alt = 2; break;
 case 14: // 248
   alt = 1; break;
 default: return 0;
 }

 enc -= 23;

 enc += (alt / 2) * 6 + 10;

 return enc | 32;  // 0b0010'0000 = alt flag

// u1 m1 = monotone(f1);
// u1 m2 = monotone(f2);
// u1 m3 = monotone(f3);
// u2 oct = octal(m1, m2, m3);

}

u1 encode_mitigation_flags(Out_of_Bounds_Resolution_Flags f1,
  Out_of_Bounds_Resolution_Flags f2,
  Out_of_Bounds_Resolution_Flags f3,
  Out_of_Bounds_Resolution_Flags f4)
{

 u1 mask = 0;
 s1 enc = get_permutation_code(mask, f1, f2, f3, f4);

 if(enc == -1)
   return 0;

// mask >>= 4;
 // //  mask should now be 15 ...
// if(mask != 15)
//   return 0;

 return enc;

}

u2 encode_double_mitigation_flags_0_0()
{
 return (15 << 6);
}

u2 encode_double_mitigation_flags_0_1(Out_of_Bounds_Resolution_Flags f21)
{
 return encode_fallback_mitigation_flags(f21) << 6;
}


//u2 encode_double_mitigation_flags_0_1(Out_of_Bounds_Resolution_Flags f21) {}

u2 encode_double_mitigation_flags_0_2(Out_of_Bounds_Resolution_Flags f21,
  Out_of_Bounds_Resolution_Flags f22)
{
 return encode_fallback_mitigation_flags(f21, f22) << 6;
}

u2 encode_double_mitigation_flags_0_3(Out_of_Bounds_Resolution_Flags f21,
  Out_of_Bounds_Resolution_Flags f22,
  Out_of_Bounds_Resolution_Flags f23)
{
 return encode_fallback_mitigation_flags(f21, f22, f23) << 6;
}

u2 encode_double_mitigation_flags_0_4(Out_of_Bounds_Resolution_Flags f21,
  Out_of_Bounds_Resolution_Flags f22,
  Out_of_Bounds_Resolution_Flags f23,
  Out_of_Bounds_Resolution_Flags f24)
{
 return encode_fallback_mitigation_flags(f21, f22, f23) << 6;
}


u2 encode_double_mitigation_flags_1_0(Out_of_Bounds_Resolution_Flags f11)
{
 u2 result = encode_mitigation_flags(f11) +
   (15 << 6);

 return result;
}

u2 encode_double_mitigation_flags_1_1(Out_of_Bounds_Resolution_Flags f11,
  Out_of_Bounds_Resolution_Flags f21)
{
 u2 result = encode_mitigation_flags(f11) +
   (encode_fallback_mitigation_flags(f21) << 6);

 return result;
}

u2 encode_double_mitigation_flags_1_2(Out_of_Bounds_Resolution_Flags f11,
  Out_of_Bounds_Resolution_Flags f21,
  Out_of_Bounds_Resolution_Flags f22)
{
// u1 enc = encode_mitigation_flags(f11);
// u1 fallback_enc = encode_fallback_mitigation_flags(f21, f22);

 u2 result = encode_mitigation_flags(f11) +
   (encode_fallback_mitigation_flags(f21, f22) << 6);

 return result;
}

u2 encode_double_mitigation_flags_1_3(Out_of_Bounds_Resolution_Flags f11,
  Out_of_Bounds_Resolution_Flags f21,
  Out_of_Bounds_Resolution_Flags f22,
  Out_of_Bounds_Resolution_Flags f23)
{
 u2 result = encode_mitigation_flags(f11) +
   (encode_fallback_mitigation_flags(f21, f22, f23) << 6);

 return result;
}

u2 encode_double_mitigation_flags_1_4(Out_of_Bounds_Resolution_Flags f11,
  Out_of_Bounds_Resolution_Flags f21,
  Out_of_Bounds_Resolution_Flags f22,
  Out_of_Bounds_Resolution_Flags f23,
  Out_of_Bounds_Resolution_Flags f24)
{
 u2 result = encode_mitigation_flags(f11) +
   (encode_fallback_mitigation_flags(f21, f22, f23) << 6);

 // // handle flag on f 24 ...
 return result;
}

u2 encode_double_mitigation_flags_2_0(Out_of_Bounds_Resolution_Flags f11,
  Out_of_Bounds_Resolution_Flags f12)
{
 u2 result = encode_mitigation_flags(f11, f12) +
   (15 << 6);

 return result;
}

u2 encode_double_mitigation_flags_2_1(Out_of_Bounds_Resolution_Flags f11,
  Out_of_Bounds_Resolution_Flags f12,
  Out_of_Bounds_Resolution_Flags f21)
{
 u2 result = encode_mitigation_flags(f11, f12) +
   (encode_fallback_mitigation_flags(f21) << 6);

 return result;
}

u2 encode_double_mitigation_flags_2_2(Out_of_Bounds_Resolution_Flags f11,
  Out_of_Bounds_Resolution_Flags f12,
  Out_of_Bounds_Resolution_Flags f21,
  Out_of_Bounds_Resolution_Flags f22)
{
 u2 result = encode_mitigation_flags(f11, f12) +
   (encode_fallback_mitigation_flags(f21, f22) << 6);

 return result;
}

u2 encode_double_mitigation_flags_2_3(Out_of_Bounds_Resolution_Flags f11,
  Out_of_Bounds_Resolution_Flags f12,
  Out_of_Bounds_Resolution_Flags f21,
  Out_of_Bounds_Resolution_Flags f22,
  Out_of_Bounds_Resolution_Flags f23)
{
 u2 result = encode_mitigation_flags(f11, f12) +
   (encode_fallback_mitigation_flags(f21, f22, f23) << 6);

 return result;
}

u2 encode_double_mitigation_flags_2_4(Out_of_Bounds_Resolution_Flags f11,
  Out_of_Bounds_Resolution_Flags f12,
  Out_of_Bounds_Resolution_Flags f21,
  Out_of_Bounds_Resolution_Flags f22,
  Out_of_Bounds_Resolution_Flags f23,
  Out_of_Bounds_Resolution_Flags f24)
{
 u2 result = encode_mitigation_flags(f11, f12) +
   (encode_fallback_mitigation_flags(f21, f22, f23) << 6);

 // // handle flag on f 24 ...
 return result;
}

u2 encode_double_mitigation_flags_3_0(Out_of_Bounds_Resolution_Flags f11,
  Out_of_Bounds_Resolution_Flags f12,
  Out_of_Bounds_Resolution_Flags f13)
{
 u2 result = encode_mitigation_flags(f11, f12, f13) +
   (15 << 6);

 return result;
}

u2 encode_double_mitigation_flags_3_1(Out_of_Bounds_Resolution_Flags f11,
  Out_of_Bounds_Resolution_Flags f12,
  Out_of_Bounds_Resolution_Flags f13,
  Out_of_Bounds_Resolution_Flags f21)
{
 u2 result = encode_mitigation_flags(f11, f12, f13) +
   (encode_fallback_mitigation_flags(f21) << 6);

 return result;
}

u2 encode_double_mitigation_flags_3_2(Out_of_Bounds_Resolution_Flags f11,
  Out_of_Bounds_Resolution_Flags f12,
  Out_of_Bounds_Resolution_Flags f13,
  Out_of_Bounds_Resolution_Flags f21,
  Out_of_Bounds_Resolution_Flags f22)
{
 u2 result = encode_mitigation_flags(f11, f12, f13) +
   (encode_fallback_mitigation_flags(f21, f22) << 6);

 return result;
}

u2 encode_double_mitigation_flags_3_3(Out_of_Bounds_Resolution_Flags f11,
  Out_of_Bounds_Resolution_Flags f12,
  Out_of_Bounds_Resolution_Flags f13,
  Out_of_Bounds_Resolution_Flags f21,
  Out_of_Bounds_Resolution_Flags f22,
  Out_of_Bounds_Resolution_Flags f23)
{
 u2 result = encode_mitigation_flags(f11, f12, f13) +
   (encode_fallback_mitigation_flags(f21, f22, f23) << 6);

 return result;
}

u2 encode_double_mitigation_flags_3_4(Out_of_Bounds_Resolution_Flags f11,
  Out_of_Bounds_Resolution_Flags f12,
  Out_of_Bounds_Resolution_Flags f13,
  Out_of_Bounds_Resolution_Flags f21,
  Out_of_Bounds_Resolution_Flags f22,
  Out_of_Bounds_Resolution_Flags f23,
  Out_of_Bounds_Resolution_Flags f24)
{
 u2 result = encode_mitigation_flags(f11, f12, f13) +
   (encode_fallback_mitigation_flags(f21, f22, f23) << 6);

 // // handle flag on f 24 ...
 return result;
}

u2 encode_double_mitigation_flags_4_0(Out_of_Bounds_Resolution_Flags f11,
  Out_of_Bounds_Resolution_Flags f12,
  Out_of_Bounds_Resolution_Flags f13,
  Out_of_Bounds_Resolution_Flags f14)
{
 u2 result = encode_mitigation_flags(f11, f12, f13, f14) +
   (15 << 6);

 return result;
}

u2 encode_double_mitigation_flags_4_1(Out_of_Bounds_Resolution_Flags f11,
  Out_of_Bounds_Resolution_Flags f12,
  Out_of_Bounds_Resolution_Flags f13,
  Out_of_Bounds_Resolution_Flags f14,
  Out_of_Bounds_Resolution_Flags f21)
{
 u2 result = encode_mitigation_flags(f11, f12, f13, f14) +
   (encode_fallback_mitigation_flags(f21) << 6);

 return result;
}

u2 encode_double_mitigation_flags_4_2(Out_of_Bounds_Resolution_Flags f11,
  Out_of_Bounds_Resolution_Flags f12,
  Out_of_Bounds_Resolution_Flags f13,
  Out_of_Bounds_Resolution_Flags f14,
  Out_of_Bounds_Resolution_Flags f21,
  Out_of_Bounds_Resolution_Flags f22)
{
 u2 result = encode_mitigation_flags(f11, f12, f13, f14) +
   (encode_fallback_mitigation_flags(f21, f22) << 6);

 return result;
}

u2 encode_double_mitigation_flags_4_3(Out_of_Bounds_Resolution_Flags f11,
  Out_of_Bounds_Resolution_Flags f12,
  Out_of_Bounds_Resolution_Flags f13,
  Out_of_Bounds_Resolution_Flags f14,
  Out_of_Bounds_Resolution_Flags f21,
  Out_of_Bounds_Resolution_Flags f22,
  Out_of_Bounds_Resolution_Flags f23)
{
 u2 result = encode_mitigation_flags(f11, f12, f13, f14) +
   (encode_fallback_mitigation_flags(f21, f22, f23) << 6);

 return result;
}

u2 encode_double_mitigation_flags_4_4(Out_of_Bounds_Resolution_Flags f11,
  Out_of_Bounds_Resolution_Flags f12,
  Out_of_Bounds_Resolution_Flags f13,
  Out_of_Bounds_Resolution_Flags f14,
  Out_of_Bounds_Resolution_Flags f21,
  Out_of_Bounds_Resolution_Flags f22,
  Out_of_Bounds_Resolution_Flags f23,
  Out_of_Bounds_Resolution_Flags f24)
{
 u2 result = encode_mitigation_flags(f11, f12, f13, f14) +
   (encode_fallback_mitigation_flags(f21, f22, f23) << 6);

 // // handle flag on f 24 ...
 return result;
}




_XCNS(XCSD)


//template<typename GALAXY_Type>
//typename GALAXY_Type::element_type&
//Hive_Structure<GALAXY_Type>::get_element(Hive_Structure::numeric_index_type ind)
//{
// int layer_index = ind % layer_size();

// int layer_order = fixed_size()? 0 :
//   ind / layer_size();

// Hive_Layer* hl = nullptr;

// if(fixed_size())
//   hl = layer_ptr();
// else
// {
//  Hive_Layer_Block* hlb = block_package_->first_block_;
//  numeric_index_type lcount = block_package_->block_size_;
//  int block_index = layer_order % lcount;
//  int block_order = layer_order / lcount;
//  int order = 0;
//  while(order < block_order)
//  {
//   if(!hlb->next)
//   {
//    Hive_Layer* new_hl = new Hive_Layer[lcount];
//    for(int i = 0; i < lcount; ++i)
//      new_hl[i] = {nullptr};
//    Hive_Layer_Block* new_hb = new Hive_Layer_Block{new_hl, nullptr};
//    hlb->next = new_hb;
//   }
//   hlb = hlb->next;
//   ++order;
//  }
//  hl = &(hlb->layers)[block_index];
//  if(hl->elements == nullptr)
//  {
//   hl->elements = new element_type[layer_size()];
//  }
// }
// return &(hl->elements)[layer_index];
//}


#ifdef HIDE
Hive_Structure::Hive_Structure()
 :  block_size_(0), total_size_(0),
   value_size_(0), first_block_(nullptr)
{

}

Hive_Block* Hive_Structure::check_init_blocks(u4 max)
{
 Hive_Block** current_block = 1_block_;
 Hive_Block* result = nullptr;
 for(int i = 0; i <= max; ++i)
 {
  if(*current_block)
  {
   result = *current_block;
   current_block = &(*current_block)->next_block;
   continue;
  }
  void* mem = malloc(block_size_ * value_size_);

  (*current_block) = new Hive_Block{mem, nullptr};
  result = *current_block;
  current_block = &(result->next_block);
 }
 return result;
}


void* Hive_Structure::get_indexed_location(u4 index)
{
 if(index >= total_size_)
   return nullptr;
 u4 blkn = index / block_size_;
 u2 blki = index % block_size_;
 return get_indexed_location(blkn, blki);
}

void* Hive_Structure::get_indexed_location_unchecked(u4 index)
{
 u4 blkn = index / block_size_;
 u2 blki = index % block_size_;
 return get_indexed_location(blkn, blki);
}


void* Hive_Structure::get_indexed_location(u4 blkn, u2 blki)
{
 Hive_Block* hb = check_init_blocks(blkn);

 return (unsigned char*)(hb->values)
   + (blki * value_size_);

}

void* Hive_Structure::get_back_location()
{
 if(total_size_ == 0)
   return nullptr;
 return get_indexed_location(total_size_ - 1);
}

void Hive_Structure::push_first_block()
{
 void* mem = malloc(block_size_ * value_size_);
 first_block_ = new Hive_Block{mem, first_block_};
 total_size_ += block_size_;
}

void Hive_Structure::pop_first_block()
{
 if(first_block_)
 {
  if(first_block_->next_block)
  {
   Hive_Block* hb = first_block_;
   first_block_ = first_block_->next_block;
   delete hb;
  }
  else
  {
   delete first_block_;
   first_block_ = nullptr;
  }
 }
}

void Hive_Structure::pop_back()
{
 if(total_size_ == 0)
   return;
 --total_size_;

 u2 blki = (total_size_ % block_size_);

 if(blki == 0)
 {
  u4 blkn = total_size_ / block_size_;
  Hive_Block* hb = check_init_blocks(blkn);
  if(hb)
  {
   if(hb->next_block)
   {
    delete hb->next_block;
    hb->next_block = nullptr;
   }
  }
 }


}

void* Hive_Structure::get_push_back_location()
{
 return get_indexed_location_unchecked(total_size_);
}

void* Hive_Structure::get_iterator_location(iterator& hit)
{
 return get_indexed_location(hit.block_index, hit.inner_index);
}

void Hive_Structure::increment_total_size()
{
 ++total_size_;
}

void Hive_Structure::check_start_iterator(iterator& hit)
{
 if(total_size_ == 0)
 {
  hit.total_index = -1;
  return;
 }
}

void Hive_Structure::reverse_iterator(iterator& hit)
{
 if(total_size_ == 0)
 {
  hit.total_index = -1;
  return;
 }
 hit.total_index = total_size_ - 1;
 hit.block_index = hit.total_index / block_size_;
 hit.inner_index = hit.total_index % block_size_;
}

void Hive_Structure::position_iterator(iterator& hit, u4 ix)
{
 if(ix >= total_size_)
 {
  hit.total_index = -1;
  return;
 }
 hit.total_index = ix;
 hit.block_index = ix / block_size_;
 hit.inner_index = ix % block_size_;
}

void Hive_Structure::increment_iterator(iterator& hit)
{
 if(++hit.total_index == total_size_)
   hit.total_index = -1;
 if(++hit.inner_index == block_size_)
 {
  hit.inner_index = 0;
  ++hit.block_index;
 }
}


void Hive_Structure::decrement_iterator(iterator& hit)
{
 if(hit.total_index == 0)
 {
  hit.total_index = -1;
  return;
 }
 --hit.total_index;
 if(hit.inner_index == 0)
 {
  hit.inner_index = block_size_ - 1;
  --hit.block_index;
 }
 else
   --hit.inner_index;
}

#endif // HIDE
