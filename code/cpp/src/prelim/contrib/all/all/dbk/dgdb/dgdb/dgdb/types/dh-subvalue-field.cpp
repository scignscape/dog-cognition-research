
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "dh-subvalue-field.h"

#include "stage/dh-stage-code.h"


DH_Subvalue_Field::DH_Subvalue_Field(QString field_name)
  :  field_name_(field_name), write_mode_(In_Block), block_offset_start_(0),
     block_offset_end_(0), record_column_index_(0), index_(0), query_column_(0),
     max_partner_query_column_(0)
{

}

void DH_Subvalue_Field::check_write_mode()
{
 if(write_mode_ != Write_Mode::In_Block)
  return;

 if(query_path_.isEmpty())
  return;

 write_mode_ = Write_Mode::Redirect_External;
}

u4 DH_Subvalue_Field::get_block_segment_byte_length()
{
 DH_Stage_Code::Query_Typecode qtc = get_qtc_code();


 switch (qtc)
 {
 case DH_Stage_Code::Query_Typecode::qtc_WG_INTTYPE:
  {
   auto [result, is_signed] = get_target_byte_length();
   // len is not always declared
   check_adjust_from_default_length(result);
   return result;
  }

 case DH_Stage_Code::Query_Typecode::qtc_WG_FIXPOINTTYPE:
 case DH_Stage_Code::Query_Typecode::qtc_WG_DOUBLETYPE:
  // // anything special here?
  return block_offset_end_ - block_offset_start_ + 1;

 default:
  return block_offset_end_ - block_offset_start_ + 1;
 }
}


void DH_Subvalue_Field::note_target_byte_length(s1 len)
{
 if(len < 0)
 {
  stage_code_.note_byte_length(-len).note_signed_or_no_delete();
 }
 else
 {
  stage_code_.note_byte_length(len);
 }
}

QPair<u1, bool> DH_Subvalue_Field::get_target_byte_length()
{
 return {stage_code_.get_byte_length(), stage_code_.check_signed()};
}


u2 DH_Subvalue_Field::block_offset_record_column_split()
{
 u2 result = (u2) block_offset_start_ << 6;
 result |= ( (u1)record_column_index_ & 0b00111111 );
 return result;
}

//u1 DH_Subvalue_Field::construct_stage_code()
//{
// DH_Stage_Code result;
//}

