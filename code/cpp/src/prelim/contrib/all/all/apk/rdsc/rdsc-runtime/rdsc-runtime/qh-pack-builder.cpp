
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "qh-pack-builder.h"

#include "qh-pack-code.h"

#include "graphs/qh-node-data.h"

#include "graphs/qh-hypernode.h"

USING_KANS(RdSC)


Qh_Pack_Builder::Qh_Pack_Builder(Qh_Pack_Code& pack_code)
  :  pack_code_(pack_code), current_bit_index_(0),
     current_byte_index_(0), current_array_value_index_(0),
     current_structure_value_index_(0),
     declared_structure_value_boundary_(0),
     current_structure_value_boundary_(0),
     node_data_(nullptr),
     current_node_data_byte_index_(0),
     current_node_data_field_index_(0),
     current_proxy_data_byte_index_(0),
     current_proxy_data_field_index_(0)
{

}


Qh_Hypernode* Qh_Pack_Builder::as_hypernode()
{
 Qh_Hypernode* result = new Qh_Hypernode(data_, node_data_);
 return result;
}


void Qh_Pack_Builder::check_resize(u2 bytes_req)
{
 u4 end = current_byte_index_ + bytes_req;
 if(data_.size() < (s4) end)
   data_.resize(end);
}


void Qh_Pack_Builder::add_structure_or_array_value(QVariant qvar, u1 bytes_req, Qh_Pack_Code::Type_Hints th)
{
 check_resize(bytes_req);

 n8 nn = 0;


 if(th == Qh_Pack_Code::Type_Hints::Unsigned)
 {
  if(bytes_req == 8)
    nn = qvar.toULongLong();
  else
    nn = qvar.toUInt();
 }
 else if(th == Qh_Pack_Code::Type_Hints::Unsigned)
 {
  if(bytes_req == 8)
    nn = qvar.toLongLong();
  else
    nn = qvar.toInt();
 }
 else if(th == Qh_Pack_Code::Type_Hints::Real)
 {
  if(bytes_req == 8)
    nn = qvar.toDouble();
  else
    // // this version of the method should not be called
     //   with 1-2 byte reals ...
    nn = qvar.toFloat();
 }

 switch (bytes_req)
 {
 case 1: data_[current_byte_index_] = (u1) nn; break;
 case 2:
  data_[current_byte_index_] = (u1) (nn >> 8);
  data_[current_byte_index_ + 1] = (u1) (nn & 255);
  break;
 case 4:
  data_[current_byte_index_] = (u1) (nn >> 24);
  data_[current_byte_index_ + 1] = (u1) ((nn >> 16) & 255);
  data_[current_byte_index_ + 2] = (u1) ((nn >> 8) & 255);
  data_[current_byte_index_ + 3] = (u1) (nn & 255);
  break;
 case 8:
  data_[current_byte_index_] = (u1) (nn >> 56);
  data_[current_byte_index_ + 1] = (u1) ((nn >> 48) & 255);
  data_[current_byte_index_ + 2] = (u1) ((nn >> 40) & 255);
  data_[current_byte_index_ + 3] = (u1) ((nn >> 32) & 255);
  data_[current_byte_index_ + 4] = (u1) ((nn >> 24) & 255);
  data_[current_byte_index_ + 5] = (u1) ((nn >> 16) & 255);
  data_[current_byte_index_ + 6] = (u1) ((nn >> 8) & 255);
  data_[current_byte_index_ + 7] = (u1) (nn & 255);
  break;
 default: break;
 }

 current_byte_index_ += bytes_req;
}

void Qh_Pack_Builder::init_node_data()
{
 node_data_ = new Qh_Node_Data;
}

void Qh_Pack_Builder::init_proxy_data()
{
 proxy_data_ = new Qh_Node_Data;
}

void Qh_Pack_Builder::add_structure_or_array_value_str(QString str, u1 bytes_req)
{
 if(bytes_req == 0)
 {
  check_resize(8);

  QPair<u4, u4> pr = node_data_->add_str(str);
  data_[current_byte_index_] = (u1) (pr.first >> 24);
  data_[current_byte_index_ + 1] = (u1) ((pr.first >> 16) & 255);
  data_[current_byte_index_ + 2] = (u1) ((pr.first >> 8) & 255);
  data_[current_byte_index_ + 3] = (u1) (pr.first & 255);

  data_[current_byte_index_ + 4] = (u1) (pr.second >> 24);
  data_[current_byte_index_ + 5] = (u1) ((pr.second >> 16) & 255);
  data_[current_byte_index_ + 6] = (u1) ((pr.second >> 8) & 255);
  data_[current_byte_index_ + 7] = (u1) (pr.second & 255);

  current_byte_index_ += 8;
 }
}

void Qh_Pack_Builder::add_structure_or_array_value_qba(QByteArray& qba, u1 bytes_req)
{
 if(bytes_req == 0)
 {
  check_resize(8);

  QPair<u4, u4> pr = node_data_->add_qba(qba);
  data_[current_byte_index_] = (u1) (pr.first >> 24);
  data_[current_byte_index_ + 1] = (u1) ((pr.first >> 16) & 255);
  data_[current_byte_index_ + 2] = (u1) ((pr.first >> 8) & 255);
  data_[current_byte_index_ + 3] = (u1) (pr.first & 255);

  data_[current_byte_index_ + 4] = (u1) (pr.second >> 24);
  data_[current_byte_index_ + 5] = (u1) ((pr.second >> 16) & 255);
  data_[current_byte_index_ + 6] = (u1) ((pr.second >> 8) & 255);
  data_[current_byte_index_ + 7] = (u1) (pr.second & 255);

  current_byte_index_ += 8;
 }
}


void Qh_Pack_Builder::add_structure_or_array_value(QVariant qvar,
  QPair<u1, Qh_Pack_Code::Type_Hints> pr)
{
 switch (pr.second)
 {
 case Qh_Pack_Code::Type_Hints::Opaque:
  {
   QByteArray qba = qvar.toByteArray();
   add_structure_or_array_value_qba(qba, pr.first);
  }
  break;

 case Qh_Pack_Code::Type_Hints::Chars_QString:
  add_structure_or_array_value_str(qvar.toString(), pr.first);
  break;

 case Qh_Pack_Code::Type_Hints::Signed:
 case Qh_Pack_Code::Type_Hints::Unsigned:
  add_structure_or_array_value(qvar, pr.first, pr.second);
  break;
 }
}

Qh_Pack_Builder& Qh_Pack_Builder::add_array_proxy_value(Qh_Hypernode* qhn)
{
 if(current_array_value_index_ == 0)
   current_structure_value_boundary_ = current_byte_index_;

 ++current_array_value_index_;
 add_structure_or_array_proxy_value(qhn, 0);
 return *this; //current_array_value_index_;
}

Qh_Pack_Builder& Qh_Pack_Builder::add_structure_proxy_value(Qh_Hypernode* qhn)
{
 ++current_structure_value_index_;
 add_structure_or_array_proxy_value(qhn, current_structure_value_index_);
 return *this; //current_structure_value_index_;
}

void Qh_Pack_Builder::add_structure_or_array_proxy_value(Qh_Hypernode* qhn, u2 index)
{
 QPair<u1, Qh_Pack_Code::Type_Hints> pr = pack_code_.get_requirements(index);
 //add_structure_or_array_value(qvar, pr);
 u1 precue = pr.first;
 u1 cue = 0;
 if(precue > 20)
 {
  if(precue < 30)
    cue = precue - 20;
 }
 switch(cue)
 {
 case 4:
   // store in proxy_data_ as just a pointer
  {
   QPair<u4, u4> se = proxy_data_->add_pointer(qhn);
   add_structure_or_array_value(QVariant::fromValue(se.first), 4);
   current_proxy_data_byte_index_ += 4;
   ++current_proxy_data_field_index_;
  }
 }
}

Qh_Pack_Builder& Qh_Pack_Builder::add_structure_value(QVariant qvar)
{
 ++current_structure_value_index_;
 QPair<u1, Qh_Pack_Code::Type_Hints> pr = pack_code_.get_requirements(current_structure_value_index_);
 add_structure_or_array_value(qvar, pr);
 return *this; //current_structure_value_index_;
}


Qh_Pack_Builder& Qh_Pack_Builder::add_array_value(QVariant qvar)
{
 if(current_array_value_index_ == 0)
   current_structure_value_boundary_ = current_byte_index_;
 ++current_array_value_index_;
 QPair<u1, Qh_Pack_Code::Type_Hints> pr = pack_code_.get_requirements(0);
 add_structure_or_array_value(qvar, pr);
 return *this; //current_array_value_index_;
}

