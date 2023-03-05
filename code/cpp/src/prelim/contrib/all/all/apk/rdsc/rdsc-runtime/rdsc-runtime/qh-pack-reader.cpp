
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "qh-pack-reader.h"

#include "graphs/qh-node-data.h"

#include "graphs/qh-hypernode.h"

USING_KANS(RdSC)

Qh_Pack_Reader::Qh_Pack_Reader(Qh_Pack_Code& pack_code, const QVector<u1>& data,
  Qh_Node_Data* node_data)
  :  pack_code_(pack_code), node_data_(node_data), data_(data),
     current_index_(0), current_byte_index_(0)
{

}

Qh_Pack_Reader::Qh_Pack_Reader(Qh_Pack_Code& pack_code, const Qh_Hypernode& qhn)
  :  Qh_Pack_Reader(pack_code, qhn.data(), qhn.node_data())
{

}



u1 Qh_Pack_Reader::read_data_1(u4 index)
{
 return data_[index];
}

u2 Qh_Pack_Reader::read_data_2(u4 index)
{
 return (((u2) data_[index]) << 8) |
   (data_[index + 1]);

}

u4 Qh_Pack_Reader::read_data_4(u4 index)
{
 return (((u4) data_[index]) << 24) |
   (((u4) data_[index + 1]) << 16) |
   (((u4) data_[index + 2]) << 8) |
   (data_[index + 3]);
}

n8 Qh_Pack_Reader::read_data_8(u4 index)
{
 return (((n8) data_[index]) << 56) |
   (((n8) data_[index + 1]) << 48) |
   (((n8) data_[index + 2]) << 40) |
   (((n8) data_[index + 3]) << 32) |
   (((n8) data_[index + 4]) << 24) |
   (((n8) data_[index + 5]) << 16) |
   (((n8) data_[index + 6]) << 8) |
   (data_[index + 7]);
}


QVariant Qh_Pack_Reader::read_value()
{
 ++current_index_;
 u2 ci = pack_code_.check_index_to_array(current_index_);

 QPair<u1, Qh_Pack_Code::Type_Hints> pr = pack_code_.get_requirements(ci);

 u4 cbi = current_byte_index_;

 u1 cue = pr.first;

 if(cue > 20)
 {
  if(cue < 30)
  {
   current_byte_index_ += 4;
   u4 start = read_data_4(cbi);
   u4 end = start + 8;
   return QVariant::fromValue(proxy_data_->read_pointer(start, end));
  }
 }

 switch (pr.second)
 {
 case Qh_Pack_Code::Type_Hints::Unsigned:
  {
   current_byte_index_ += pr.first;
   switch(cue)
   {
   case 1: return QVariant::fromValue( read_data_1(cbi) );
   case 2: return QVariant::fromValue( read_data_2(cbi) );
   case 4: return QVariant::fromValue( read_data_4(cbi) );
   case 8: return QVariant::fromValue( read_data_8(cbi) );
   }
  }
  break;

 case Qh_Pack_Code::Type_Hints::Opaque:
  {
   switch(pr.first)
   {
   case 0:
    current_byte_index_ += 8;
    u4 start = read_data_4(cbi);
    u4 end = read_data_4(cbi + 4);
    return node_data_->read_qba(start, end);
   }
  }
  break;


 case Qh_Pack_Code::Type_Hints::Chars_QString:
  {
   switch(pr.first)
   {
   case 0:
    current_byte_index_ += 8;
    u4 start = read_data_4(cbi);
    u4 end = read_data_4(cbi + 4);
    return node_data_->read_str(start, end);
   }
  }
  break;

 }


}


