
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "dw-stage-value.h"

#include "stage/dw-stage-queue.h"

#include <QDebug>

extern "C" {
#include "whitedb/_whitedb.h"
}

USING_KANS(DGDB)

DW_Stage_Value::DW_Stage_Value()
  :  info_(0), data_(0), run({this})
{

}

DW_Stage_Value& DW_Stage_Value::set_ptr_data(void* ptr)
{
 data_ = (n8) ptr;
 return *this;
}

DW_Stage_Value::_run_result 
DW_Stage_Value::_run_hold::_run::operator()(DW_Stage_Value::Callback_type cb)
{
 return _this->_run(cb, index, col);
}

DW_Stage_Value::_run_result 
DW_Stage_Value::_run_hold::operator()(DW_Stage_Value::Callback_type cb)
{
 return _this->_run(cb);
}

DW_Stage_Value::_run_result 
DW_Stage_Value::_run(Callback_type cb, u4 field_index, QString col)
{
 cb(field_index, col, this);
 return {info_, 0};
}

DW_Stage_Value::_run_result::operator u1() const
{
 u1 result = collapse_dw_encoding_type();
 result |= extra;
 return result;
}

u1 DW_Stage_Value::_run_result::collapse_dw_encoding_type() const
{
 u1 result = info >> 4; 
 if(result > 2)
   result = 3;
 return (info & 15) | (result << 4);
}

void DW_Stage_Value::enqueue_in(DW_Stage_Queue& sw)
{
 sw.enqueue_void((void*)this->data_);
}

DW_Stage_Value::~DW_Stage_Value()
{

}

DW_Stage_Value& DW_Stage_Value::new_qstring(const QString& qs)
{
 return note_qstring().set_data(qs);
}

DW_Stage_Value& DW_Stage_Value::new_qstring_pair(const QString& qs)
{
 return note_qstring().note_data_has_type().set_data(
   QPair<n8, QStringList*> {0, new QStringList {qs, {}}});
}

DW_Stage_Value& DW_Stage_Value::new_qstring_pair(const QString& qs1, const QString& qs2)
{
 return note_qstring().note_data_has_type().set_data(
   QPair<n8, QStringList*> {0, new QStringList {qs1, qs2}});
}

DW_Stage_Value& DW_Stage_Value::new_qstring_xml_pair(const QString& qs1, const QString& qs2)
{
 return note_xml().note_data_has_type().set_data(
   QPair<n8, QStringList*> {0, new QStringList {qs1, qs2}});
}

DW_Stage_Value& DW_Stage_Value::new_qstring_uri_pair(const QString& qs1, const QString& qs2)
{
 return note_uri().note_data_has_type().set_data(
   QPair<n8, QStringList*> {0, new QStringList {qs1, qs2}});
}


u1 DW_Stage_Value::get_prelim_encoding_code() const
{
 u1 result = info_ >> 4;
 if(result < 3)
   return result;
 if(result == 15)
   return result;
 return 3;
}

u1 DW_Stage_Value::get_prelim_decoding_flag() const
{
 return info_ & 192; // high two bits ...
}

u1 DW_Stage_Value::get_prelim_decoding_code() const
{
 u1 result = info_ >> 4;
 result &= 3;
 if(result == 0)
 {
  u1 add = info_ & 3;
  if(add == 0)
    return 0;
  return add + 15; 
 }
 return result;
}

u1 DW_Stage_Value::get_dw_encoding_type() const
{
 u1 enc = info_ >> 4;
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

u1 DW_Stage_Value::get_read_encoding_type() const
{
 u1 result = info_ >> 4;
 if(result == 0)
 {
  u1 add = info_ & 3;
  if(add == 0)
    return 0;
  return add + 15; 
 }
 return result;
}

DW_Stage_Value& DW_Stage_Value::note_unspec()
{
 info_ &= 12; // clear all but 4,8 bits ...
 return *this;
}

DW_Stage_Value& DW_Stage_Value::note_enum()
{
 info_ &= 12; 
 info_ |= 1;
 return *this;
}

DW_Stage_Value& DW_Stage_Value::note_signed_enum()
{
 info_ &= 12; 
 info_ |= 2;
 return *this;
}

DW_Stage_Value& DW_Stage_Value::note_char_enum()
{
 info_ &= 12; 
 info_ |= 3;
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

DW_Stage_Value& DW_Stage_Value::note_uint()
{
 info_ &= 15;
 info_ |= (1 << 4);

 return *this;
}

DW_Stage_Value& DW_Stage_Value::note_qstring()
{
 info_ &= 15;
 info_ |= (2 << 4);
 return *this;
}

DW_Stage_Value& DW_Stage_Value::note_null()
{
 info_ &= 15;
 info_ |= (3 << 4);
 return *this;
}

DW_Stage_Value& DW_Stage_Value::note_rec()
{
 info_ &= 15;
 info_ |= (4 << 4);
 return *this;
}

DW_Stage_Value& DW_Stage_Value::note_int()
{
 info_ &= 15;
 info_ |= (5 << 4);
 return *this;
}

DW_Stage_Value& DW_Stage_Value::note_dbl()
{
 info_ &= 15;
 info_ |= (6 << 4);
 return *this;
}

DW_Stage_Value& DW_Stage_Value::note_str()
{
 info_ &= 15;
 info_ |= (7 << 4);
 return *this;
}

DW_Stage_Value& DW_Stage_Value::note_xml()
{
 info_ &= 15;
 info_ |= (8 << 4);
 return *this;
}

DW_Stage_Value& DW_Stage_Value::note_uri()
{
 info_ &= 15;
 info_ |= (9 << 4);
 return *this;
}

DW_Stage_Value& DW_Stage_Value::note_blob()
{
 info_ &= 15;
 info_ |= (10 << 4);
 return *this;
}

DW_Stage_Value& DW_Stage_Value::note_char()
{
 info_ &= 15;
 info_ |= (11 << 4);
 return *this;
}

DW_Stage_Value& DW_Stage_Value::note_fixp()
{
 info_ &= 15;
 info_ |= (12 << 4);
 return *this;
}

DW_Stage_Value& DW_Stage_Value::note_date()
{
 info_ &= 15;
 info_ |= (13 << 4);
 return *this;
}

DW_Stage_Value& DW_Stage_Value::note_time()
{
 info_ &= 15;
 info_ |= (14 << 4);
 return *this;
}

DW_Stage_Value& DW_Stage_Value::note_tbd()
{
 info_ &= 15;
 info_ |= (15 << 4);
 return *this;
}


DW_Stage_Value& DW_Stage_Value::note_data_has_type()
{
 info_ |= 8;
 return *this;
}

DW_Stage_Value& DW_Stage_Value::clear_data_has_type()
{
 info_ &= (255 - 8);
 return *this;
}

u1 DW_Stage_Value::get_byte_length() const
{
 switch(info_ & 3)
 {
 case 0: return 8;
 case 1: return 4;
 case 2: return 2;
 case 3: return 1;
 }
}

DW_Stage_Value& DW_Stage_Value::note_byte_length(u1 len)
{
 switch(len)
 {
 case 1: info_  |= 3; break;
 case 2: info_ &= (255 - 1); info_  |= 2; break;
 case 4: info_ &= (255 - 2); info_  |= 1; break;
 default:
 case 8: info_ &= (255 - 3); break;
 }
 return *this;
}

DW_Stage_Value& DW_Stage_Value::note_no_delete()
{
 info_ |= 4;
 return *this;
}

DW_Stage_Value& DW_Stage_Value::clear_no_delete()
{
 info_ &= (255 - 4);
 return *this;
}


