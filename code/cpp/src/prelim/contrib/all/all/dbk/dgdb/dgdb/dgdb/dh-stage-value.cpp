
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "dh-stage-value.h"

#include "types/stage/dh-stage-queue.h"

#include <QDebug>

#include <QDataStream>

extern "C" {
#include "whitedb/_whitedb.h"
}

//USING_KANS(DGDB)

DH_Stage_Value::DH_Stage_Value()
  :  data_(0), run({this})
{

}

DH_Stage_Value& DH_Stage_Value::set_ptr_data(void* ptr)
{
 data_ = (n8) ptr;
 return *this;
}

DH_Stage_Value::_run_result
DH_Stage_Value::_run_hold::_run::operator()(DH_Stage_Value::Callback_type cb)
{
 return _this->_run(cb, index, col);
}

DH_Stage_Value::_run_result
DH_Stage_Value::_run_hold::operator()(DH_Stage_Value::Callback_type cb)
{
 return _this->_run(cb);
}

DH_Stage_Value::_run_result
DH_Stage_Value::_run(Callback_type cb, u4 field_index, QString col)
{
 cb(field_index, col, this);
 return {info_, 0};
}

DH_Stage_Value::_run_result::operator u1() const
{
 u1 result = collapse_wg_encoding_type();
 result |= extra;
 return result;
}

u1 DH_Stage_Value::_run_result::collapse_wg_encoding_type() const
{
 u1 result = (u1) info.get_qtc_code();
 if(result > 2)
   result = 3;
 return (info.code() & 15) | (result << 4);
}

void DH_Stage_Value::enqueue_in(DH_Stage_Queue& sq)
{
 sq.enqueue_void((void*)this->data_);
}

DH_Stage_Value::~DH_Stage_Value()
{

}



DH_Stage_Value& DH_Stage_Value::new_qstring(const QString& qs, DH_Stage_Code::String_Kind sk)
{
 return note_qstring(sk).set_data(qs);
}

DH_Stage_Value& DH_Stage_Value::new_qstring_pair(const QString& qs, DH_Stage_Code::String_Kind sk)
{
 return note_qstring(sk).note_unspec_or_data_has_type().set_data(
   QPair<n8, QStringList*> {0, new QStringList {qs, {}}});
}

DH_Stage_Value& DH_Stage_Value::new_qstring_pair(const QString& qs1, const QString& qs2, DH_Stage_Code::String_Kind sk)
{
 return note_qstring(sk).note_unspec_or_data_has_type().set_data(
   QPair<n8, QStringList*> {0, new QStringList {qs1, qs2}});
}

DH_Stage_Value& DH_Stage_Value::new_qstring_xml_pair(const QString& qs1, const QString& qs2)
{
 return note_xml().note_unspec_or_data_has_type().set_data(
   QPair<n8, QStringList*> {0, new QStringList {qs1, qs2}});
}

DH_Stage_Value& DH_Stage_Value::new_qstring_uri_pair(const QString& qs1, const QString& qs2)
{
 return note_uri().note_unspec_or_data_has_type().set_data(
   QPair<n8, QStringList*> {0, new QStringList {qs1, qs2}});
}


u1 DH_Stage_Value::get_prelim_encoding_code() const
{
 u1 result = info_.code() >> 4;
 if(result < 3)
   return result;
 if(result == 15)
   return result;
 return 3;
}

u1 DH_Stage_Value::get_prelim_decoding_flag() const
{
 return info_.code() & 12; // 3rd,4th bits ...
}

u1 DH_Stage_Value::get_prelim_decoding_code() const
{
 u1 result = info_.code() >> 4;
 result &= 3;
 if(result == 0)
 {
  u1 add = info_.code() & 3;
  if(add == 0)
    return 0;
  return add + 15; 
 }
 return result;
}

u1 DH_Stage_Value::get_wg_encoding_type() const
{
 u1 enc = info_.code() >> 4;
 static const u1 u1s [] = {WG_NULLTYPE, WG_NULLTYPE, WG_NULLTYPE, // 0 - 2
   WG_NULLTYPE, // 3
   WG_RECORDTYPE, // 4
   WG_INTTYPE, // 5
   WG_DOUBLETYPE, // 6
   WG_STRTYPE, // 7
   WG_XMLLITERALTYPE, // 8
   WG_URITYPE, // 9
   WG_BLOBTYPE, // 10
   WG_CHARTYPE, // 11
   WG_FIXPOINTTYPE, // 12
   WG_DATETYPE, // 13
   WG_TIMETYPE, // 14,
   WG_NULLTYPE // 15
   };
 return u1s[enc];
}

u1 DH_Stage_Value::get_read_encoding_type() const
{
 u1 result = info_.code() >> 4;
 if(result == 0)
 {
  u1 add = info_.code() & 3;
  if(add == 0)
    return 0;
  return add + 15; 
 }
 return result;
}


DH_Stage_Value& DH_Stage_Value::note_unspec()
{
 info_.note_unspec(); // clear all but 4,8 bits ...
 return *this;
}

DH_Stage_Value& DH_Stage_Value::note_enum()
{
 info_.note_enum();
 return *this;
}

DH_Stage_Value& DH_Stage_Value::note_signed_enum()
{
 info_.note_signed_enum();
 return *this;
}

DH_Stage_Value& DH_Stage_Value::note_char_enum()
{
 info_.note_char_enum();
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

DH_Stage_Value& DH_Stage_Value::note_uint()
{
 info_.note_uint();
 return *this;
}

DH_Stage_Value& DH_Stage_Value::note_qstring(DH_Stage_Code::String_Kind sk)
{
 info_.note_qstring(sk);
 return *this;
}

DH_Stage_Value& DH_Stage_Value::note_null()
{
 info_.note_null();
 return *this;
}

DH_Stage_Value& DH_Stage_Value::note_rec()
{
 info_.note_rec();
 return *this;
}

DH_Stage_Value& DH_Stage_Value::note_int()
{
 info_.note_int();
 return *this;
}

DH_Stage_Value& DH_Stage_Value::note_dbl()
{
 info_.note_dbl();
 return *this;
}

DH_Stage_Value& DH_Stage_Value::note_str()
{
 info_.note_str();
 return *this;
}

DH_Stage_Value& DH_Stage_Value::note_xml()
{
 info_.note_xml();
 return *this;
}

DH_Stage_Value& DH_Stage_Value::note_uri()
{
 info_.note_uri();
 return *this;
}

DH_Stage_Value& DH_Stage_Value::note_blob()
{
 info_.note_blob();
 return *this;
}

DH_Stage_Value& DH_Stage_Value::note_char()
{
 info_.note_char();
 return *this;
}

DH_Stage_Value& DH_Stage_Value::note_fixp()
{
 info_.note_fixp();
 return *this;
}

DH_Stage_Value& DH_Stage_Value::note_date()
{
 info_.note_date();
 return *this;
}

DH_Stage_Value& DH_Stage_Value::note_time()
{
 info_.note_time();
 return *this;
}

DH_Stage_Value& DH_Stage_Value::note_tbd()
{
 info_.note_tbd();
 return *this;
}


DH_Stage_Value& DH_Stage_Value::note_unspec_or_data_has_type()
{
 info_.note_unspec_or_data_has_type();
 return *this;
}

DH_Stage_Value& DH_Stage_Value::clear_unspec_or_data_has_type()
{
 info_.clear_unspec_or_data_has_type();
 return *this;
}

void DH_Stage_Value::check_confirm_byte_length(u1 len, bool is_signed)
{
 if(len == 0)
   return;

 return info_.check_confirm_byte_length(len, is_signed);

}

void DH_Stage_Value::generic_null()
{
 info_.note_null().note_unspec_or_data_has_type();
}

void DH_Stage_Value::generic_int(n8 data)
{
 set_raw_data(data);
 info_.note_int().note_unspec_or_data_has_type();
}

u1 DH_Stage_Value::get_byte_length() const
{
 return info_.get_byte_length();
}

DH_Stage_Code::String_Kind DH_Stage_Value::get_string_kind() const
{
 return info_.get_string_kind();
}


DH_Stage_Value& DH_Stage_Value::note_byte_length(u1 len)
{
 info_.note_byte_length(len);
 return *this;
}

DH_Stage_Value& DH_Stage_Value::note_no_delete()
{
 info_.note_signed_or_no_delete();
 return *this;
}

DH_Stage_Value& DH_Stage_Value::clear_no_delete()
{
 info_.clear_signed_or_no_delete();
 return *this;
}


// //  maybe should template on qtc like with to_qba_ ...
void DH_Stage_Value::aborb_data(QDataStream& qds, DH_Stage_Code sc)
{
 DH_Stage_Code::Query_Typecode qtc = sc.get_qtc_code();

 switch (qtc)
 {

 case DH_Stage_Code::Query_Typecode::qtc_User_Data:
  {
  }
  break;

 case DH_Stage_Code::Query_Typecode::qtc_qvar:
  {
  }
  break;

 case DH_Stage_Code::Query_Typecode::qtc_Hypernode:
  {
  }
  break;

 case DH_Stage_Code::Query_Typecode::qtc_WG_NULLTYPE:
  {

  }
  break;

 case DH_Stage_Code::Query_Typecode::qtc_WG_INTTYPE:
  {
   u1 len = sc.get_byte_length();
   bool is_signed = sc.check_signed();
   if(is_signed)
   {
    switch(len)
    {
    case 1: { s1 s; qds >> s; set_s1_data(s); } break;
    case 2: { s2 s; qds >> s; set_s2_data(s); } break;
    case 4: { s4 s; qds >> s; set_s4_data(s); } break;
    default: break;
    }
   }
   else
   {
    switch(len)
    {
    case 1: { u1 u; qds >> u; set_u1_data(u); } break;
    case 2: { u2 u; qds >> u; set_u2_data(u); } break;
    case 4: { u4 u; qds >> u; set_u4_data(u); } break;
    case 8: { n8 n; qds >> n; set_n8_data(n); } break;
    default: break;
    }
   }
  }
  break;

 case DH_Stage_Code::Query_Typecode::qtc_WG_STRTYPE:
  {
   DH_Stage_Code::String_Kind sk = get_string_kind();

   QString value;
   qds >> value;
   set_str_data(value);
  }
  break;


 case DH_Stage_Code::Query_Typecode::qtc_WG_DOUBLETYPE:
  {
   r8 value;
   qds >> value;
   set_double_data(value);
  }
  break;

 case DH_Stage_Code::Query_Typecode::qtc_WG_DATETYPE:
  {
   QDate value;
   qds >> value;
   set_date_data(value);
  }
  break;

 case DH_Stage_Code::Query_Typecode::qtc_WG_TIMETYPE:
  {
   QTime value;
   qds >> value;
   set_time_data(value);
  }
  break;

 case DH_Stage_Code::Query_Typecode::qtc_QDateTime:
  {
   QDateTime value;
   qds >> value;
   set_n8_data(value.toMSecsSinceEpoch());
  }
  break;

 case DH_Stage_Code::Query_Typecode::qtc_WG_FIXPOINTTYPE:
  {

  }
  break;

 case DH_Stage_Code::Query_Typecode::qtc_WG_RECTYPE:
  {

  }
  break;

 case DH_Stage_Code::Query_Typecode::qtc_WG_CHARTYPE:
  {

  }
  break;

 case DH_Stage_Code::Query_Typecode::qtc_WG_BLOBTYPE:
  {

  }
  break;

 default:
  break;
 }



}


