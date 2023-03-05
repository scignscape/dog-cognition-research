
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "qh-node-data.h"

USING_KANS(RdSC)

Qh_Node_Data::Qh_Node_Data()
{

}

u4 Qh_Node_Data::check_resize(u4 start, u4 amount)
{
 u4 end = start + amount;
 if(data_.size() < (s4) end)
   data_.resize(end);
 return end;
}


QPair<u4, u4> Qh_Node_Data::add_qba(const QByteArray& qba)
{
 u4 start = (u4) data_.size();
 u4 end = check_resize(start, qba.size());

 for(u4 uu = start, i = 0; uu < end; ++uu, ++i)
 {
  data_[uu] = qba[i];
 }

 return {start, end};
}

QPair<u4, u4> Qh_Node_Data::add_str(const QString& str)
{
 u4 start = (u4) data_.size();
 u4 end = check_resize(start, str.size() * 2);

 for(u4 uu = start, i = 0; uu < end; uu += 2, ++i)
 {
  QChar qc = str.at(i);
  u2 uni = qc.unicode();
  data_[uu] = uni >> 8;
  data_[uu + 1] = uni & 255;
 }

 return {start, end};
}


void Qh_Node_Data::add_array_proxy_value(u4 data_start, u4 data_end)
{

}


QPair<u4, u4> Qh_Node_Data::add_pointer(void* ptr)
{
 u4 start = (u4) data_.size();
 u4 end = check_resize(start, 8);
 n8 nn = (n8) ptr;
 data_[start] = (u1) (nn >> 56);
 data_[start + 1] = (u1) ((nn >> 48) & 255);
 data_[start + 2] = (u1) ((nn >> 40) & 255);
 data_[start + 3] = (u1) ((nn >> 32) & 255);
 data_[start + 4] = (u1) ((nn >> 24) & 255);
 data_[start + 5] = (u1) ((nn >> 16) & 255);
 data_[start + 6] = (u1) ((nn >> 8) & 255);
 data_[start + 7] = (u1) (nn & 255);
 return {start, end};
}


void* Qh_Node_Data::read_pointer(u4 start, u4 end)
{
 u1 len = end - start;

 n8 nn = 0;

 u1 adjust = len * 7;

 for(u4 uu = start; uu < end; ++uu, adjust -= 8)
 {
  nn |= (((n8) data_[uu]) << adjust);
 }

 return (void*) nn;
}


QByteArray Qh_Node_Data::read_qba(u4 start, u4 end)
{
 QByteArray result(end - start, 0);

 for(u4 uu = start, i = 0; uu < end; ++uu, ++i)
 {
  result[(s4)i] = data_[uu];
 }
 return result;

}


QString Qh_Node_Data::read_str(u4 start, u4 end)
{
 QString result((end - start) / 2, QChar{});

 for(u4 uu = start, i = 0; uu < end; uu += 2, ++i)
 {
  u2 uni = (((u2) data_[uu]) << 8) | data_[uu + 1];  // qc.unicode();
  result[(s4)i] = QChar(uni);
 }
 return result;
}
