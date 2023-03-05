
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "qh-pack-code.h"


Qh_Pack_Code::Qh_Pack_Code()
  :  field_codes_({0})
{

}

// bytes 1-2 = 1, 2, 4, or 8 bytes
// byte 3 = proxy
// byte 4 = flag // interpert as enum (2, 4, 5 or 6 bits)
// byte 5-7 = signed/unsigned/blob/text etc.
// byte 8 = special return/coproxy flag

Qh_Pack_Code::Type_Hints Qh_Pack_Code::get_type_hint(u2 index)
{
 return parse_type_hint(field_codes_[index]);
}

Qh_Pack_Code::Type_Hints Qh_Pack_Code::parse_type_hint(u1 cue)
{
 u1 code = (cue & 0b01110000) >> 4;
 static Type_Hints static_key [8] {
  Type_Hints::N_A, Type_Hints::Signed, Type_Hints::Real, Type_Hints::Chars_QString,
  Type_Hints::Chars_Encoded, Type_Hints::Blob, Type_Hints::Opaque, Type_Hints::Enum
 };

 return static_key[code];
}

QPair<u1, Qh_Pack_Code::Type_Hints> Qh_Pack_Code::get_requirements(u2 index)
{
 Type_Hints th = get_type_hint(index);

 u1 addon = 0;

 u1 fc = field_codes_[index];

 u1 special = fc & 12;

 if(special & 4)
 {
  if(fc == 4)
  {
   addon = 20;
   // // defauts to 4 bytes
   fc |= 2;
  }
 }
//  if(fc == 4)
//  {
//   return {20, Type_Hints::N_A};
//  }
// }

 if( (th == Type_Hints::N_A) && (special == 0) )
   th = Type_Hints::Unsigned;

 switch (th)
 {
 case Type_Hints::Opaque:
 case Type_Hints::Chars_QString:
  return {addon + (fc & 3), th};
 case Type_Hints::N_A:
 case Type_Hints::Unsigned:
 default:
  break;
 }

 return {addon + (1 << (fc & 3)), th};
}



u1 Qh_Pack_Code::get_type_hint_code(Type_Hints th)
{
 switch (th)
 {
 case Type_Hints::Unsigned: return 0;
 case Type_Hints::Signed: return 1;
 case Type_Hints::Real: return 2;
 case Type_Hints::Chars_QString: return 3;
 case Type_Hints::Chars_Encoded: return 4;
 case Type_Hints::Blob: return 5;
 case Type_Hints::Opaque: return 6;
 case Type_Hints::Enum: return 7;
 case Type_Hints::N_A:
 default: return 0;
 }
}

QString Qh_Pack_Code::get_type_hint_string(Type_Hints th)
{
 switch (th)
 {
 case Type_Hints::Signed: return "signed";
 case Type_Hints::Real: return "real";
 case Type_Hints::Chars_QString: return "chars QString";
 case Type_Hints::Chars_Encoded: return "chars encoded";
 case Type_Hints::Blob: return "blob";
 case Type_Hints::Opaque: return "opaque";
 case Type_Hints::N_A:
 default: return  "unsigned/N_A";
 }
}


u1 Qh_Pack_Code::with_type_hint(u1 cue, Type_Hints th)
{
 return cue | (get_type_hint_code(th) << 4);
}

u1 Qh_Pack_Code::with_proxy_hint(u1 cue)
{
 return cue | 4;
}


QByteArray Qh_Pack_Code::as_qba()
{
 return QByteArray::fromRawData(
    reinterpret_cast<const char*>(field_codes_.data()), field_codes_.size());
}


Qh_Pack_Code& Qh_Pack_Code::add_u1(u2 array)
{
 u1 code = with_type_hint(0, Type_Hints::Unsigned);

 if(array)
   field_codes_[0] = code;
 else
   field_codes_.push_back(code);

 return *this;
}

Qh_Pack_Code& Qh_Pack_Code::add_u2(u2 array)
{
 u1 code = with_type_hint(1, Type_Hints::Unsigned);

 if(array)
   field_codes_[0] = code;
 else
   field_codes_.push_back(code);

 return *this;
}

Qh_Pack_Code& Qh_Pack_Code::add_u4(u2 array)
{
 u1 code = with_type_hint(2, Type_Hints::Unsigned);

 if(array)
   field_codes_[0] = code;
 else
   field_codes_.push_back(code);

 return *this;
}

Qh_Pack_Code& Qh_Pack_Code::add_n8(u2 array)
{
 u1 code = with_type_hint(3, Type_Hints::Unsigned);

 if(array)
   field_codes_[0] = code;
 else
   field_codes_.push_back(code);

 return *this;
}


Qh_Pack_Code& Qh_Pack_Code::add_s1(u2 array)
{
 u1 code = with_type_hint(0, Type_Hints::Signed);

 if(array)
   field_codes_[0] = code;
 else
   field_codes_.push_back(code);

 return *this;
}

Qh_Pack_Code& Qh_Pack_Code::add_s2(u2 array)
{
 u1 code = with_type_hint(1, Type_Hints::Signed);

 if(array)
   field_codes_[0] = code;
 else
   field_codes_.push_back(code);

 return *this;
}

Qh_Pack_Code& Qh_Pack_Code::add_s4(u2 array)
{
 u1 code = with_type_hint(2, Type_Hints::Signed);

 if(array)
   field_codes_[0] = code;
 else
   field_codes_.push_back(code);

 return *this;
}

Qh_Pack_Code& Qh_Pack_Code::add_s8(u2 array)
{
 u1 code = with_type_hint(3, Type_Hints::Signed);

 if(array)
   field_codes_[0] = code;
 else
   field_codes_.push_back(code);

 return *this;
}


Qh_Pack_Code& Qh_Pack_Code::add_ratio(u2 array)
{
 u1 code = with_type_hint(0, Type_Hints::Real);

 if(array)
   field_codes_[0] = code;
 else
   field_codes_.push_back(code);

 return *this;
}

Qh_Pack_Code& Qh_Pack_Code::add_posit(u2 array)
{
 u1 code = with_type_hint(1, Type_Hints::Real);

 if(array)
   field_codes_[0] = code;
 else
   field_codes_.push_back(code);

 return *this;
}

Qh_Pack_Code& Qh_Pack_Code::add_r4(u2 array)
{
 u1 code = with_type_hint(2, Type_Hints::Real);

 if(array)
   field_codes_[0] = code;
 else
   field_codes_.push_back(code);

 return *this;
}

Qh_Pack_Code& Qh_Pack_Code::add_r8(u2 array)
{
 u1 code = with_type_hint(3, Type_Hints::Real);

 if(array)
   field_codes_[0] = code;
 else
   field_codes_.push_back(code);

 return *this;
}


Qh_Pack_Code& Qh_Pack_Code::add_proxy(u2 array)
{
 u1 code = with_proxy_hint(0);

 if(array)
   field_codes_[0] = code;
 else
   field_codes_.push_back(code);

 return *this;
}

Qh_Pack_Code& Qh_Pack_Code::add_str(u2 array)
{
 u1 code = with_type_hint(0, Type_Hints::Chars_QString);

 if(array)
   field_codes_[0] = code;
 else
   field_codes_.push_back(code);

 return *this;
}

Qh_Pack_Code& Qh_Pack_Code::add_txn(u2 array)
{
 u1 code = with_type_hint(0, Type_Hints::Chars_Encoded);

 if(array)
   field_codes_[0] = code;
 else
   field_codes_.push_back(code);

 return *this;
}

Qh_Pack_Code& Qh_Pack_Code::add_opaque(u2 array)
{
 u1 code = with_type_hint(0, Type_Hints::Opaque);

 if(array)
   field_codes_[0] = code;
 else
   field_codes_.push_back(code);

 return *this;
}





void Qh_Pack_Code::each(std::function<u2(u1, u2)> fn)
{
 u2 sz = field_codes_.size();
 u2 _continue = 0;
 for(u2 u = 0; u < sz; ++u)
 {
  _continue = fn(field_codes_[u], u + 1);
  if(!_continue)
    break;
 }
}

void Qh_Pack_Code::each(std::function<u2(u1, Type_Hints, u2)> fn)
{
 u2 sz = field_codes_.size();
 u2 _continue = 0;
 for(u2 u = 0; u < sz; ++u)
 {
  u1 cue = field_codes_[u];
  Type_Hints th = parse_type_hint(cue);
  cue &= 3;

  _continue = fn(cue, th, u + 1);
  if(!_continue)
    break;
 }
}


