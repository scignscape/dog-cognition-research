

//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef DH_STAGE_CODE__H
#define DH_STAGE_CODE__H

#include <QVector>
#include <QQueue>

#include <QDateTime>
#include <QDate>

#include <QDomElement>
#include <QVariant>


#include <QDebug>

#include <functional>

#include "accessors.h"

#include "global-types.h"

#include "kans.h"


#define _TYPECODE_QUERY_MACROS(x) \
 x(User_Data ,char*) \
 x(Hypernode ,DgDb_Hypernode*) \
 x(qvar ,QVariant) \
 x(WG_NULLTYPE ,nullptr_t) \
 x(WG_RECTYPE ,void*) \
 x(WG_INTTYPE ,int) \
 x(WG_DOUBLETYPE ,double) \
 x(WG_STRTYPE ,QString) \
 x(WG_XMLLITERALTYPE ,QDomEntity) \
 x(WG_URITYPE ,QUrl) \
 x(WG_BLOBTYPE ,QByteArray) \
 x(WG_CHARTYPE ,char) \
 x(WG_FIXPOINTTYPE ,float) \
 x(WG_DATETYPE ,QDate) \
 x(WG_TIMETYPE ,QTime) \
 x(QDateTime ,QDateTime) \


KANS_(DGDB)

class DgDb_Hypernode;


class DH_Stage_Code
{
 u1 code_;


public:


 enum class Query_Typecode {
#define TEMP_MACRO(x ,y) \
  qtc_##x,
  _TYPECODE_QUERY_MACROS(TEMP_MACRO)
#undef TEMP_MACRO
 };

 enum class String_Kind { ql1, ql8, q16, Other };

 DH_Stage_Code() : code_(0) { }

 ACCESSORS(u1 ,code)

 u1& ref()
 {
  return code_;
 }

 template<typename T>
 static inline DH_Stage_Code::Query_Typecode get_qtc_code()
 {
  return DH_Stage_Code::Query_Typecode::qtc_User_Data;
 }

 template<typename T>
 static inline DH_Stage_Code get_prelim_for_type()
 {
  return DH_Stage_Code();
 }

 DH_Stage_Code::Query_Typecode get_qtc_code() const
 {
  u1 result = code_ >> 4;

  // //  currently only 14 options ...
//  if(result == 15)
//    result = 0;

  return (Query_Typecode) result;
 }

 void note_qtc_code(Query_Typecode qtc)
 {
  code_ &= 0b0000'1111;
  code_ |= ( (u1) qtc << 4 );
 }

 enum Str_Option {
  Latin1 = 0, Local8 = 1, Unicode = 2, Other = 3, N_A = 255
 };

 enum Null_Option {
  Default_Null = 0, Index_Null = 1, Cond_Null = 2, Other_Null = 3, Null_N_A = 255
 };

 u1 get_option_code() const
 {
  return code_ & 3;
 }

 DH_Stage_Code& set_option_code(u1 code)
 {
  // //  code should be <= 3
  code &= 3;

  code_ &= 0b1111'1100;

  code_ |= code;
  return *this;
 }

 DH_Stage_Code& note_signed_or_no_delete()
 {
  code_ |= 4;
  return *this;
 }

 DH_Stage_Code& clear_signed_or_no_delete()
 {
  code_ &= 0b1111'1011;
  return *this;
 }

 bool check_no_delete() const
 {
  return code_ & 4;
 }

 bool check_signed() const
 {
  return code_ & 4;
 }

 bool check_unspec_or_data_has_type()
 {
  return code_ & 8;
 }

 static u1 qtc_to_wg_field_type(Query_Typecode qtc);

 void check_confirm_byte_length(u1 len, bool is_signed);

// u1 get_query_typecode() const;
 u1 get_byte_length() const;

 String_Kind get_string_kind() const;
 DH_Stage_Code& note_string_kind(String_Kind sk);


// u1 get_prelim_encoding_code() const;
// u1 get_read_encoding_type() const;

// u1 get_prelim_decoding_code() const;
// u1 get_prelim_decoding_flag() const;

// bool is_uninit() const
// {
//  return code_ == 0;
// }


 DH_Stage_Code& note_unspec();
 DH_Stage_Code& note_enum();
 DH_Stage_Code& note_signed_enum();
 DH_Stage_Code& note_char_enum();
 DH_Stage_Code& note_qstring(String_Kind sk);
 DH_Stage_Code& note_uint();
 DH_Stage_Code& note_null();
 DH_Stage_Code& note_rec();
 DH_Stage_Code& note_int();
 DH_Stage_Code& note_dbl();
 DH_Stage_Code& note_str();
 DH_Stage_Code& note_xml();
 DH_Stage_Code& note_uri();
 DH_Stage_Code& note_blob();
 DH_Stage_Code& note_char();
 DH_Stage_Code& note_fixp();
 DH_Stage_Code& note_date();
 DH_Stage_Code& note_time();
 DH_Stage_Code& note_tbd();

 DH_Stage_Code& note_byte_length(u1 len);

 DH_Stage_Code& note_unspec_or_data_has_type();
 DH_Stage_Code& clear_unspec_or_data_has_type();
//? bool check_unspec_or_data_has_type() { return code_ & 8; }

// DH_Stage_Code& note_signed_or_no_delete();
// DH_Stage_Code& clear_signed_or_no_delete();

//? bool check_signed_or_no_delete() { return code_ & 16; }

 DH_Stage_Code& new_qstring(const QString& qs);
 DH_Stage_Code& new_qstring_pair(const QString& qs);
 DH_Stage_Code& new_qstring_pair(const QString& qs1, const QString& qs2);

 DH_Stage_Code& new_qstring_xml_pair(const QString& qs1, const QString& qs2);
 DH_Stage_Code& new_qstring_uri_pair(const QString& qs1, const QString& qs2);


};

_KANS(DGDB)

USING_KANS(DGDB)


#define TEMP_MACRO(x ,y) \
template<> \
inline DH_Stage_Code::Query_Typecode DH_Stage_Code::get_qtc_code<y>() \
{ \
 return Query_Typecode::qtc_##x; \
} \

_TYPECODE_QUERY_MACROS(TEMP_MACRO)
#undef TEMP_MACRO


template<>
inline DH_Stage_Code DH_Stage_Code::get_prelim_for_type<s1>()
{
 return DH_Stage_Code().note_int().note_byte_length(1).note_signed_or_no_delete();
}

template<>
inline DH_Stage_Code DH_Stage_Code::get_prelim_for_type<u1>()
{
 return DH_Stage_Code().note_int().note_byte_length(1);
}


template<>
inline DH_Stage_Code DH_Stage_Code::get_prelim_for_type<s2>()
{
 return DH_Stage_Code().note_int().note_byte_length(2).note_signed_or_no_delete();
}

template<>
inline DH_Stage_Code DH_Stage_Code::get_prelim_for_type<u2>()
{
 return DH_Stage_Code().note_int().note_byte_length(2);
}


template<>
inline DH_Stage_Code DH_Stage_Code::get_prelim_for_type<s4>()
{
 return DH_Stage_Code().note_int().note_byte_length(4).note_signed_or_no_delete();
}

template<>
inline DH_Stage_Code DH_Stage_Code::get_prelim_for_type<u4>()
{
 return DH_Stage_Code().note_int().note_byte_length(4);
}



#endif // DH_Stage_Code__H


