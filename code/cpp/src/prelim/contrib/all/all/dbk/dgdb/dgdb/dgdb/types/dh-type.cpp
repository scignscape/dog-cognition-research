
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "dh-type.h"

//USING_KANS(DgDb)

DH_Type::DH_Type()
  :  byte_length_(0),
     byte_length_code_(0), stash_id_(0),
     subvalue_fields_serialization_vector_(nullptr),
     meta_object_(nullptr), shm_block_size_(0),
     shm_block_column_(2), shm_message_column_(-2)
     //subvalue_fields_qtc_vector_(nullptr)
  //   stage_encoder_(nullptr)
{
 default_query_column_ = 5;
 default_query_path_ = "&/q/$type";
}


void DH_Type::get_subvalue_fields_as_vector(QVector<DH_Subvalue_Field*>& sfs)
{
 if(subvalue_fields_serialization_vector_)
 {
  // //  this vector is non-null when someone has declared a
   //    particular serialization order, which may differ
   //    from the order of how the fields are declared ...
  if(subvalue_fields_serialization_vector_->isEmpty())
  {
   subvalue_fields_serialization_vector_->resize(field_name_serialization_order_.size());
   std::transform(field_name_serialization_order_.begin(),
     field_name_serialization_order_.end(),
     subvalue_fields_serialization_vector_->begin(),
     [this](QString fn) { return get_subvalue_field_by_field_name(fn);});
  }

  sfs = *subvalue_fields_serialization_vector_;
  return;
 }

 if(subvalue_fields_.isEmpty())
   return;

 // //  assume QMaps are sorted by keys, so the
  //    largest is the last one before .end() ...
 u2 max = (subvalue_fields_.end() - 1).key();

 sfs.resize(max);

 QMapIterator<u2, DH_Subvalue_Field*> it(subvalue_fields_);
 while(it.hasNext())
 {
  it.next();
  sfs[it.key() - 1] = it.value();
 }
}

DH_Subvalue_Field* DH_Type::get_subvalue_field_by_index(u2 ix)
{
 return subvalue_fields_.value(ix);
}

DH_Subvalue_Field* DH_Type::get_subvalue_field_by_field_name(QString field_name)
{
 u2 ix = subvalue_fields_index_map_.value(field_name).first;
 if(ix == 0)
  return nullptr;
 return subvalue_fields_.value(ix);
}

void DH_Type::note_field_query_partner(DH_Subvalue_Field* sf,
  QString partner, QMap<DH_Subvalue_Field*, QVector<QPair<DH_Subvalue_Field*, u2>>>& query_partners)
{
 DH_Subvalue_Field* psf = get_subvalue_field_by_field_name(partner);
 sf->set_query_partner(psf);
 u2 qc = sf->query_column() + 1;
 if(query_partners.isEmpty())
 {
  sf->set_query_column(qc);
  query_partners[psf] = {{sf, qc}};
  psf->set_max_partner_query_column(qc);
 }
 else
 {
  QSet<u2> already_declared_qcs;
  // //  the idea here is that explicitly setting the
   //    column for partner sf's will make them 0 in
   //    this vector; otherwise count all
   //    the sf's which had automatically assigned columns ...

  for(QPair<DH_Subvalue_Field*, u2>& pr : query_partners[psf])
  {
   if(pr.second == 0)
     already_declared_qcs.insert(pr.first->query_column());
   else
   {
    ++qc;
    // // users should be careful when mixing
     //   declared and automatically assigned
     //   qc's so they don't conflict.  But
     //   we'll try to double check just in case.
    while(already_declared_qcs.contains(qc))
    {
     // // can't use that column; try the next one
     ++qc;
    }
   }
  }
  sf->set_query_column(qc);
  if(qc > psf->max_partner_query_column())
    psf->set_max_partner_query_column(qc);
  query_partners[psf].push_back({sf, qc});
 }
}


u2 DH_Type::get_max_declared_field_column()
{
 std::vector<u1> fixed;
 std::transform(subvalue_fields_.cbegin(), subvalue_fields_.cend(), std::back_inserter(fixed),
    [](DH_Subvalue_Field* sf) -> u1
 {
  return ((sf->write_mode() == DH_Subvalue_Field::Redirect_In_Record) &&
    (sf->record_column_index() & 0b0010'0000))?
    (sf->record_column_index() & 0b0001'1111):0;
 });
 return *std::max_element(fixed.begin(), fixed.end());
}

u2 DH_Type::get_internal_field_column_requirements()
{
 return std::count_if(subvalue_fields_.cbegin(), subvalue_fields_.cend(), [](DH_Subvalue_Field* sf)
 {
  return sf->write_mode() == DH_Subvalue_Field::Redirect_In_Record;
 });
}

void DH_Type::note_field_qtc(DH_Subvalue_Field* sf, DH_Stage_Code::Query_Typecode qtc)
{
 sf->note_query_info(qtc);
}

void DH_Type::note_field_signed(DH_Subvalue_Field* sf)
{
 sf->set_stage_profile(DH_Subvalue_Field::Stage_Profiles::Signed_Number);
}

void DH_Type::note_write_mode(DH_Subvalue_Field* sf, DH_Subvalue_Field::Write_Mode wm)
{
 sf->set_write_mode(wm);
}

void DH_Type::note_record_column_index(DH_Subvalue_Field* sf, u2 rci)
{
 sf->set_record_column_index(rci);
}

DH_Subvalue_Field* DH_Type::note_write_mode(QString field_name, DH_Subvalue_Field::Write_Mode wm)
{
 if(DH_Subvalue_Field* sf = get_subvalue_field_by_field_name(field_name))
 {
  note_write_mode(sf, wm);
  return sf;
 }
 return nullptr;
}

DH_Subvalue_Field::Write_Mode DH_Type::get_write_mode(QString field_name)
{
 if(DH_Subvalue_Field* sf = get_subvalue_field_by_field_name(field_name))
   return sf->write_mode();
 return DH_Subvalue_Field::In_Block;
}


DH_Type& DH_Type::default_object_layout()
{
 set_byte_length(QT_POINTER_SIZE);
 set_byte_length_code(QT_POINTER_SIZE);
 return *this;
}

void DH_Type::note_field_block_offset(DH_Subvalue_Field* sf, u4 start, u4 end)
{
 sf->set_block_offset_start(start);
 sf->set_block_offset_end(end);
}

void DH_Type::note_field_index(DH_Subvalue_Field* sf, u2 index)
{
 sf->set_index(index);
}


void DH_Type::note_field_target_byte_length(DH_Subvalue_Field* sf, u1 len)
{
 sf->note_target_byte_length(len);
}

void DH_Type::note_field_query_path(DH_Subvalue_Field* sf, QString path, DH_Stage_Code::Query_Typecode qtc)
{
 sf->note_query_info(path, qtc);
}

void DH_Type::note_field_query_column(DH_Subvalue_Field* sf, u2 qyc)
{
 sf->set_query_column(qyc);
}

void DH_Type::note_record_column_index(DH_Subvalue_Field* sf,
  DH_Stage_Code::Query_Typecode qtc, u2 rci)
{
 sf->note_query_info(qtc);
 sf->set_record_column_index(rci);
}

DH_Subvalue_Field* DH_Type::note_field_block_offset(QString field_name, u4 start, u4 end)
{
 if(DH_Subvalue_Field* sf = get_subvalue_field_by_field_name(field_name))
 {
  note_field_block_offset(sf, start, end);
  return sf;
 }
 return nullptr;
}


//DH_Subvalue_Field* DH_Type::check_note_field_name(QString field_name)
//{

//}


DH_Subvalue_Field* DH_Type::note_field_query_path(QString field_name, QString path,
  DH_Stage_Code::Query_Typecode qtc)
{
 if(DH_Subvalue_Field* sf = get_subvalue_field_by_field_name(field_name))
 {
  note_field_query_path(sf, path, qtc);
  return sf;
 }
 return nullptr;
}


//DH_Subvalue_Field* DH_Type::note_field_column_in_record(QString field_name,
//  DH_Stage_Code::Query_Typecode qtc, u2 column)
//{
// if(DH_Subvalue_Field* sf = get_subvalue_field_by_field_name(field_name))
// {
//  note_field_column_in_record(sf, qtc, column);
//  return sf;
// }
// return nullptr;
//}


DH_Subvalue_Field* DH_Type::note_field_index(QString field_name, u2 index)
{
 if(DH_Subvalue_Field* sf = get_subvalue_field_by_field_name(field_name))
 {
  note_field_index(sf, index);
  return sf;
 }

 DH_Subvalue_Field* result = new DH_Subvalue_Field(field_name);

 result->set_query_column(default_query_column_);
 result->set_query_path(default_query_path_);

 note_field_index(result, index);

 // //  see if a qtc has already been entered ...
 auto it = subvalue_fields_index_map_.find(field_name);
 if(it == subvalue_fields_index_map_.end())
 {
  // //   todo: maybe a non-0 DH_Stage_Code uninit value ...
  subvalue_fields_index_map_[field_name] = {index, DH_Stage_Code()};
 }
 else
   it->first = index;

 //subvalue_fields_index_map_[field_name] = index;

 subvalue_fields_[index] = result;
 return result;
}


QPair<u4, u4> DH_Type::get_field_block_offset(QString field_name)
{
 if(DH_Subvalue_Field* sf = get_subvalue_field_by_field_name(field_name))
 {
  return {sf->block_offset_start(), sf->block_offset_end()};
 }
 return {0,0};
 //return field_block_offsets_.value(field_name);
}

