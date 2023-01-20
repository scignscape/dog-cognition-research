
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "dh-stage-code.h"


// //  1-4   byte length 8,4,2,1  for int
// //  1-4   qstrl1 qstrl8  qstruni  qstrenc  for str


// // #define WG_NULLTYPE 1
// // #define WG_RECORDTYPE 2
// // #define WG_INTTYPE 3
// // #define WG_DOUBLETYPE 4
// // #define WG_STRTYPE 5
// // #define WG_XMLLITERALTYPE 6
// // #define WG_URITYPE 7
// // #define WG_BLOBTYPE 8
// // #define WG_CHARTYPE 9
// // #define WG_FIXPOINTTYPE 10
// // #define WG_DATETYPE 11
// // #define WG_TIMETYPE 12

// //  qstring l1
// //  qstring l8
// //  qstring uni

//u1 DH_Stage_Code::get_wg_encoding_type() const
//{
// u1 enc = code_ >> 4;
// static const u1 u1s [] = {WG_NULLTYPE, WG_NULLTYPE, WG_NULLTYPE, // 0 - 2
//   WG_NULLTYPE, // 3
//   WG_RECORDTYPE, // 4
//   WG_INTTYPE, // 5
//   WG_DOUBLETYPE, // 6
//   WG_STRTYPE, // 7
//   WG_XMLLITERALTYPE, // 8
//   WG_URITYPE, // 9
//   WG_BLOBTYPE, // 10
//   WG_CHARTYPE, // 11
//   WG_FIXPOINTTYPE, // 12
//   WG_DATETYPE, // 13
//   WG_TIMETYPE, // 14,
//   WG_NULLTYPE // 15
//   };
// return u1s[enc];
//}



//DH_Stage_Code& DH_Stage_Code::note_int()
//{

//}

void DH_Stage_Code::check_confirm_byte_length(u1 len, bool is_signed)
{
 Query_Typecode qtc = get_qtc_code();
 if(qtc == Query_Typecode::qtc_WG_INTTYPE)
 {
  if(check_unspec_or_data_has_type())
  {
   note_byte_length(len);
   if(is_signed)
     note_signed_or_no_delete();
   clear_unspec_or_data_has_type();
  }
 }
}

u1 DH_Stage_Code::qtc_to_wg_field_type(Query_Typecode qtc)
{
 u1 result = (u1) qtc;
 if(result == 15)
   return 0;
 if(result < 2)
   return 0;
 return result - 2;
}

u1 DH_Stage_Code::get_byte_length() const
{
 Query_Typecode qtc = get_qtc_code();
 switch(qtc)
 {
 case Query_Typecode::qtc_WG_INTTYPE:
 case Query_Typecode::qtc_WG_DOUBLETYPE:
 case Query_Typecode::qtc_WG_TIMETYPE:
   return 1 << (3 - get_option_code());
 default:
   return 0;
 }
}

DH_Stage_Code::String_Kind DH_Stage_Code::get_string_kind() const
{
 return (String_Kind) get_option_code();
}

DH_Stage_Code& DH_Stage_Code::note_string_kind(String_Kind sk)
{
 u1 _sk = (u1) sk & 3;
 code_ &= 0b1111'1100;
 code_ |= _sk;
 return *this;
}

DH_Stage_Code& DH_Stage_Code::note_unspec()
{
 code_ &= 12; // clear all but 4,8 bits ...
 return *this;
}

DH_Stage_Code& DH_Stage_Code::note_enum()
{
 code_ &= 12;
 code_ |= 1;
 return *this;
}

DH_Stage_Code& DH_Stage_Code::note_signed_enum()
{
 code_ &= 12;
 code_ |= 2;
 return *this;
}

DH_Stage_Code& DH_Stage_Code::note_char_enum()
{
 code_ &= 12;
 code_ |= 3;
 return *this;
}

// //  these are offset by 2
 //
// // #define WG_NULLTYPE 1
// // #define WG_RECORDTYPE 2
// // #define WG_INTTYPE 3
// // #define WG_DOUBLETYPE 4
// // #define WG_STRTYPE 5
// // #define WG_XMLLITERALTYPE 6
// // #define WG_URITYPE 7
// // #define WG_BLOBTYPE 8
// // #define WG_CHARTYPE 9
// // #define WG_FIXPOINTTYPE 10
// // #define WG_DATETYPE 11
// // #define WG_TIMETYPE 12

DH_Stage_Code& DH_Stage_Code::note_uint()
{
// code_ &= 15;
// code_ |= (1 << 4);

 code_ &= 15;
 code_ |= (5 << 4);

 //note_signed_or_no_delete();
 return *this;
}

DH_Stage_Code& DH_Stage_Code::note_qstring(String_Kind sk)
{
 note_str();
 note_string_kind(sk);
// code_ &= 15;
// code_ |= (1 << 4);
 return *this;
}

DH_Stage_Code& DH_Stage_Code::note_null()
{
 code_ &= 15;
 code_ |= (3 << 4);
 return *this;
}

DH_Stage_Code& DH_Stage_Code::note_rec()
{
 code_ &= 15;
 code_ |= (4 << 4);
 return *this;
}

DH_Stage_Code& DH_Stage_Code::note_int()
{
 code_ &= 15;
 code_ |= (5 << 4);

 note_signed_or_no_delete();
 return *this;
}

DH_Stage_Code& DH_Stage_Code::note_dbl()
{
 code_ &= 15;
 code_ |= (6 << 4);
 return *this;
}

DH_Stage_Code& DH_Stage_Code::note_str()
{
 code_ &= 15;
 code_ |= (7 << 4);
 return *this;
}

DH_Stage_Code& DH_Stage_Code::note_xml()
{
 code_ &= 15;
 code_ |= (8 << 4);
 return *this;
}

DH_Stage_Code& DH_Stage_Code::note_uri()
{
 code_ &= 15;
 code_ |= (9 << 4);
 return *this;
}

DH_Stage_Code& DH_Stage_Code::note_blob()
{
 code_ &= 15;
 code_ |= (10 << 4);
 return *this;
}

DH_Stage_Code& DH_Stage_Code::note_char()
{
 code_ &= 15;
 code_ |= (11 << 4);
 return *this;
}

DH_Stage_Code& DH_Stage_Code::note_fixp()
{
 code_ &= 15;
 code_ |= (12 << 4);
 return *this;
}

DH_Stage_Code& DH_Stage_Code::note_date()
{
 code_ &= 15;
 code_ |= (13 << 4);
 return *this;
}

DH_Stage_Code& DH_Stage_Code::note_time()
{
 code_ &= 15;
 code_ |= (14 << 4);
 return *this;
}

DH_Stage_Code& DH_Stage_Code::note_tbd()
{
 code_ &= 15;
 code_ |= (15 << 4);
 return *this;
}


DH_Stage_Code& DH_Stage_Code::note_unspec_or_data_has_type()
{
 code_ |= 8;
 return *this;
}

DH_Stage_Code& DH_Stage_Code::clear_unspec_or_data_has_type()
{
 code_ &= 0b1111'0111; //(255 - 8);
 return *this;
}


DH_Stage_Code& DH_Stage_Code::note_byte_length(u1 len)
{
 switch(len)
 {
 case 1: code_  |= 3; break;
 case 2: code_ &= (255 - 1); code_  |= 2; break;
 case 4: code_ &= (255 - 2); code_  |= 1; break;
 default:
 case 8: code_ &= (255 - 3); break;
 }
 return *this;
}



