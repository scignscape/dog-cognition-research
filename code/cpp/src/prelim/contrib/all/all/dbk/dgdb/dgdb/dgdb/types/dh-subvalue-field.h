
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef DH_SUBVALUE_FIELD__H
#define DH_SUBVALUE_FIELD__H

#include <functional>

#include <QDomElement>
#include <QVariant>

#include "global-types.h"

//#include "_whitedb/_whitedb.h"

#include "accessors.h"

#include "kans.h"

#include "stage/dh-stage-code.h"

KANS_(DGDB)

class DH_Type;


class DH_Subvalue_Field
{
 QString field_name_;

public:


 inline DH_Stage_Code::Query_Typecode get_qtc_code()
 {
  return stage_code_.get_qtc_code();
 }


 enum class Stage_Profiles {
   Signed_Number, QString_Latin1,
   QString_Local, QString_Unicode
 };

 enum Write_Mode {
  In_Block,
  Redirect_In_Block,
  Redirect_In_Record,
  Redirect_External,
 };

 enum Block_Segment_Info_Flags {
   Extension_Flags = 1, Has_Offset_Split = 2, Has_Type_Code = 4,
   Has_Segment_Length = 8, Has_Record_Pointer = 16, Has_Field_Index = 32,
   Has_White_Path = 64, Has_Value = 128
 };

 enum Block_Segment_Extension_Info_Flags {
   Has_Active_Segment_End = 1, Has_Active_Segment_Start = 2,
   Has_Edit_Timestamp = 4, Has_Edit_Info = 8,
   Has_User_Data = 16
 };


private:

 Write_Mode write_mode_;
 u2 index_;
 u2 record_column_index_;

 u4 block_offset_start_;
 u4 block_offset_end_;

 QString query_path_;
 QString checked_query_path_;

 DH_Stage_Code stage_code_;
 Stage_Profiles stage_profile_;

 u2 query_column_;

 DH_Subvalue_Field* query_partner_;

 // //  note: this is the max of sf's which have
  //    *this* as a partner, not this's own partner.
  //    Probably max_partner_query_column_ should = 0
  //    when query_partner_ doesn't, and vice-versa
  //    (could an sf have a partner and also be a partner?)
 u2 max_partner_query_column_;

 // //  may become part of a bitmask sometime ...
 //s1 target_byte_length_;

public:


 DH_Subvalue_Field(QString field_name = {});

 ACCESSORS(Write_Mode ,write_mode)

 ACCESSORS(QString ,field_name)

 ACCESSORS(Stage_Profiles ,stage_profile)

 ACCESSORS(u4 ,block_offset_start)
 ACCESSORS(u4 ,block_offset_end)

 ACCESSORS(u2 ,index)
 ACCESSORS(u2 ,record_column_index)

 ACCESSORS(u2 ,max_partner_query_column)

 ACCESSORS(QString ,query_path)
 ACCESSORS(DH_Stage_Code ,stage_code)
 ACCESSORS(u2 ,query_column)
 ACCESSORS(QString ,checked_query_path)
 ACCESSORS(DH_Subvalue_Field* ,query_partner)

 u2 block_offset_record_column_split();
 void check_write_mode();
 void note_target_byte_length(s1 len);
 QPair<u1, bool> get_target_byte_length();

 u4 get_block_segment_byte_length();

 void inline check_adjust_from_default_length(u1& len)
 {
  if(len == 8) // default -- this could be changed if/when there's some
               // other flag that the len was not explicitly set ...
  {
   u4 olen = block_offset_end_ - block_offset_start_ + 1;
   if(olen == 1)
     len = 1;
   else if(olen < 4)
     len = 2;
   else if(olen < 8)
     len = 4;
  }
 }

 void note_query_info(QString path, DH_Stage_Code::Query_Typecode qtc)
 {
  set_query_path(path);
  check_write_mode();
  stage_code_.note_qtc_code(qtc);
 }

 void note_query_info(DH_Stage_Code::Query_Typecode qtc)
 {
  stage_code_.note_qtc_code(qtc);
 }

};

struct DH
{
 static QPair<u2, u1> block_offset_record_column_unsplit(u2 combined)
 {
  return {combined >> 6, (u1) combined & 0b00111111};
 }

 template<typename T>
 struct Redirect_In_Record_intermediary
 {
  operator QPair<DH_Subvalue_Field::Write_Mode, DH_Stage_Code::Query_Typecode>() const
  {
   return {DH_Subvalue_Field::Redirect_In_Record, DH_Stage_Code::get_qtc_code<T>()};
  }

  QPair<QPair<DH_Subvalue_Field::Write_Mode, DH_Stage_Code::Query_Typecode>, u2>
    operator()(u1 column_index) const
  {
   return {{DH_Subvalue_Field::Redirect_In_Record, DH_Stage_Code::get_qtc_code<T>()}, column_index - 1};
  }

  QPair<QPair<DH_Subvalue_Field::Write_Mode, DH_Stage_Code::Query_Typecode>, u2>
    operator[](u1 column_index) const
  {
   return {{DH_Subvalue_Field::Redirect_In_Record, DH_Stage_Code::get_qtc_code<T>()},
     column_index | 0b0010'0000};
  }

 };

 // column_index

 template<typename T>
 static constexpr Redirect_In_Record_intermediary<T> Redirect_In_Record = {};

};

_KANS(DGDB)

#endif // DH_SUBVALUE_FIELD__H


