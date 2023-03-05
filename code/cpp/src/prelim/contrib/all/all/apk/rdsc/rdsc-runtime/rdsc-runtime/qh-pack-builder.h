
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef QH_PACK_BUILDER__H
#define QH_PACK_BUILDER__H

#include <QByteArray>

#include <QVariant>

#include <functional>

#include "global-types.h"

#include "accessors.h"

//class Qh_Bundle_Code;

#include "qh-pack-code.h"

KANS_(RdSC)

class Qh_Node_Data;
class Qh_Hypernode;


class Qh_Pack_Builder
{
 Qh_Pack_Code& pack_code_;

 u1 current_bit_index_;
 u4 current_byte_index_;
 u4 current_array_value_index_;
 u2 current_structure_value_index_;
 u2 declared_structure_value_boundary_;
 u2 current_structure_value_boundary_;

 QVector<u1> data_;

 Qh_Node_Data* node_data_;
 u4 current_node_data_byte_index_;
 u4 current_node_data_field_index_;

 Qh_Node_Data* proxy_data_;
 u4 current_proxy_data_byte_index_;
 u4 current_proxy_data_field_index_;


public:

 Qh_Pack_Builder(Qh_Pack_Code& pack_code);

 ACCESSORS__CONST_RGET(QVector<u1> ,data)
 ACCESSORS(Qh_Node_Data* ,node_data)
 ACCESSORS(Qh_Node_Data* ,proxy_data)
 ACCESSORS__RGET(Qh_Pack_Code ,pack_code)


 Qh_Hypernode* as_hypernode();

 Qh_Pack_Builder& add_structure_proxy_value(Qh_Hypernode* qhn);
 Qh_Pack_Builder& add_array_proxy_value(Qh_Hypernode* qhn);

 Qh_Pack_Builder& add_sv_proxy(Qh_Hypernode* qhn)
 {
  return add_structure_proxy_value(qhn);
 }
 Qh_Pack_Builder& add_av_proxy(Qh_Hypernode* qhn)
 {
  return add_array_proxy_value(qhn);
 }

 void add_structure_or_array_proxy_value(Qh_Hypernode* qhn, u2 index);

 Qh_Pack_Builder& add_structure_value(QVariant qvar);
 Qh_Pack_Builder& add_array_value(QVariant qvar);

 template<typename VARIANT_Type>
 Qh_Pack_Builder& add_sv(const VARIANT_Type& var)
 {
  return add_structure_value(QVariant::fromValue(var));
 }

 template<typename VARIANT_Type>
 Qh_Pack_Builder& add_av(const VARIANT_Type& var)
 {
  return add_array_value(QVariant::fromValue(var));
 }


 void add_structure_or_array_value(QVariant qvar,
   QPair<u1, Qh_Pack_Code::Type_Hints> pr);


 void add_structure_or_array_value(QVariant qvar, u1 bytes_req,
   Qh_Pack_Code::Type_Hints th = Qh_Pack_Code::Type_Hints::N_A);

 void add_structure_or_array_value_str(QString str, u1 bytes_req);
 void add_structure_or_array_value_qba(QByteArray& qba, u1 bytes_req);


 void init_node_data();
 void init_proxy_data();

 void check_resize(u2 bytes_req);

};

_KANS(RdSC)


#endif // QH_PACK_BUILDER__H


