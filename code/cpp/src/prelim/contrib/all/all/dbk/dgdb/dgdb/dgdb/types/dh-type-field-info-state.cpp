
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "dh-type-field-info-state.h"

#include "dh-type.h"

#ifndef UNEXPECTED_INPUT_PATTERN
#define UNEXPECTED_INPUT_PATTERN \
  qDebug() << "Unexpected input pattern in field info (line " << __LINE__ << " )";
#endif


void DH_Type_Field_Info_State::note_field_block_offset(u4 start, u4 end, u1 qtc)
{
 if(field_)
   _this.note_field_block_offset(field_, start, end);
 else
   field_ = _this.note_field_block_offset(field_name_, start, end);

 if(qtc != 255)
   _this.note_field_qtc(field_, (DH_Stage_Code::Query_Typecode) qtc);
}


DH_Type_Field_Info_State&
DH_Type_Field_Info_State::operator()(u4 start, u4 end)
{
 switch (wide_)
 {
 case Wide_Input_State::Field_Name:
  note_field_block_offset(start, end, (u1)DH_Stage_Code::get_qtc_code<int>());
  narrow_ = Narrow_Input_State::Declared_Block_Indexes;
  break;
 default:
  break;
 }
}

DH_Type_Field_Info_State&
DH_Type_Field_Info_State::operator()(u1 byte_len)
{
 switch (wide_)
 {
 case Wide_Input_State::Field_Name:
  //  just the number of bytes ...
  // todo ... note_field_block_offset(start, end, (u1)DH_Stage_Code::get_qtc_code<int>());
  break;

 case Wide_Input_State::Query:
  _this.note_field_target_byte_length(field_, byte_len);
  narrow_ = Narrow_Input_State::Declared_Byte_Length;

 default:
  break;
 }

 return *this;
}


void DH_Type_Field_Info_State::note_write_mode(DH_Subvalue_Field::Write_Mode wm)
{
 if(field_)
   _this.note_write_mode(field_, wm);
 else
   field_ = _this.note_write_mode(field_name_, wm);
}


DH_Type_Field_Info_State&
DH_Type_Field_Info_State::operator()(QString another_field_name)
{
// if(wide_ != Wide_Input_State::Query)
// {
//  UNEXPECTED_INPUT_PATTERN
//  return *this;
// }

 field_ = nullptr;
 wide_ = Wide_Input_State::Field_Name;
 narrow_ = Narrow_Input_State::N_A;
 if(held_start_ != (u4) -1)
 {
  // //  todo ...
 }
 field_name_ = another_field_name;
 return *this;
}

DH_Type_Field_Info_State& DH_Type_Field_Info_State::operator()(QPair<
  QPair<DH_Subvalue_Field::Write_Mode, DH_Stage_Code::Query_Typecode>, u2> pr)
{
 if(wide_ != Wide_Input_State::Field_Name)
 {
  UNEXPECTED_INPUT_PATTERN
  return *this;
 }

 auto [pr1, column_index] = pr;
 auto [wm, qtc] = pr1;

 note_write_mode(wm);

 _this.note_record_column_index(field_, qtc, column_index);
 return *this;
}


DH_Type_Field_Info_State& DH_Type_Field_Info_State::operator[](QString partner)
{
 switch (wide_)
 {
 default:
  // //  anything other than Query here ?
  break;

 case Wide_Input_State::Query:
  _this.note_field_query_partner(field_, partner, query_partners_);
  narrow_ = Narrow_Input_State::Query_Partner;
  break;
 }
}


DH_Type_Field_Info_State& DH_Type_Field_Info_State::operator[](u2 index)
{
 switch (wide_)
 {
 default:
 case Wide_Input_State::Field_Name:
  if(field_)
    _this.note_field_index(field_, index);
  else
    field_ = _this.note_field_index(field_name_, index);
  narrow_ = Narrow_Input_State::Declared_Field_Index;
  break;

 case Wide_Input_State::Record:
  // //  using square brackets indicates that the number
   //    refers to a fixed column, not offset from
   //    largest fixed column; hence the 6th-bit flag ...
  _this.note_record_column_index(field_, index | 0b0010'0000);

  //?  narrow_ = Narrow_Input_State:: ...;
  break;

 case Wide_Input_State::Query:
  _this.note_field_query_column(field_, index);
  if(DH_Subvalue_Field* psf = field_->query_partner())
  {
   // // we need to 0 out the qc in the query partners map
    //   since now the qc is being set explicitly ...
   auto it = std::find_if(query_partners_[psf].begin(),
                query_partners_[psf].end(), [this](auto pr)
   {
    return pr.first == field_;
   });
   // //  we found field_ ...
   if(it != query_partners_[psf].end())
     (*it).second = 0;

   // //  now reset the max
   u2 max = std::max_element(query_partners_[psf].begin(),
     query_partners_[psf].end(), [](auto pr1, auto pr2)
   {
    return pr1.second < pr2.second;
   })->second;

   psf->set_max_partner_query_column(qMax(max, index));
  }
  narrow_ = Narrow_Input_State::Query_Column;
  break;
 }

 return *this;
}


DH_Type_Field_Info_State& DH_Type_Field_Info_State::operator()(DH_Subvalue_Field::Write_Mode wm)
{
 if(wide_ != Wide_Input_State::Field_Name)
 {
  UNEXPECTED_INPUT_PATTERN
  return *this;
 }

// if(field_)
//   _this.note_write_mode(field_, wm);
// else
//   field_ = _this.note_write_mode(field_name_, wm);

 note_write_mode(wm);
 return *this;
}


DH_Type_Field_Info_State&
DH_Type_Field_Info_State::operator()(QPair<DH_Subvalue_Field::Write_Mode, DH_Stage_Code::Query_Typecode> pr)
{
 if(wide_ != Wide_Input_State::Field_Name)
 {
  UNEXPECTED_INPUT_PATTERN
  return *this;
 }

 auto [wm, qtc] = pr;
 note_write_mode(wm);

 _this.note_field_qtc(field_, qtc);
 return *this;
}


DH_Type_Field_Info_State& DH_Type_Field_Info_State::operator()(QPair<DH_Subvalue_Field::Write_Mode, u2> pr)
{
 if(wide_ != Wide_Input_State::Field_Name)
 {
  UNEXPECTED_INPUT_PATTERN
  return *this;
 }

 auto [wm, column_index] = pr;
 note_write_mode(wm);

 _this.note_record_column_index(field_, column_index);
 return *this;
}

DH_Type_Field_Info_State& DH_Type_Field_Info_State::_signed_(u4 start, u4 end)
{
 note_field_block_offset(start, end, (u1)DH_Stage_Code::get_qtc_code<int>());
 _this.note_field_signed(field_);
 narrow_ = Narrow_Input_State::Declared_Block_Indexes;
 return *this;
}

DH_Type_Field_Info_State& DH_Type_Field_Info_State::_date_(u4 start, u4 end)
{
 note_field_block_offset(start, end, (u1)DH_Stage_Code::get_qtc_code<QDate>());
 narrow_ = Narrow_Input_State::Declared_Block_Indexes;
 return *this;
}

DH_Type_Field_Info_State& DH_Type_Field_Info_State::_time_(u4 start, u4 end)
{
 note_field_block_offset(start, end, (u1)DH_Stage_Code::get_qtc_code<QTime>());
 narrow_ = Narrow_Input_State::Declared_Block_Indexes;
 return *this;
}

DH_Type_Field_Info_State& DH_Type_Field_Info_State::_datetime_(u4 start, u4 end)
{
 note_field_block_offset(start, end, (u1)DH_Stage_Code::get_qtc_code<QDateTime>());
 narrow_ = Narrow_Input_State::Declared_Block_Indexes;
 return *this;
}



