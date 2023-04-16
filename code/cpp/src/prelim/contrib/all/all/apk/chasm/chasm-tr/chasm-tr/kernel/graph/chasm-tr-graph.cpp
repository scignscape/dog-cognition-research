
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "chasm-tr-graph.h"

#include "aqns.h"

USING_AQNS(ChasmTR)


Chasm_TR_Graph::Chasm_TR_Graph(Chasm_TR_Node* root_node)
  :  root_node_(root_node)
{
 set_user_data(&hypernodes_);
 set_node_add_function([](phaong<pg_t>& _pg, phaong<pg_t>::Hypernode* hn)
 {
  QVector<hypernode_type*>* hh = _pg.user_data_as<QVector<hypernode_type*>>();
  hh->push_back(hn);
 });
}

// // here offset dfaults to -1 ...
void Chasm_TR_Graph::add_structure_type(QString name, unsigned int l,
  signed int offset)
{
 types_[name] = {l, {offset, -1}};
}

void Chasm_TR_Graph::add_array_type(QString name, unsigned int l,
  unsigned int csize, signed int offset)
{
 types_[name] = {-l, {offset, csize}};
}

// // here offset defaults to 0 ...
void Chasm_TR_Graph::add_fixed_array_type(QString name, unsigned int l,
  signed int offset)
{
 types_[name] = {l, {offset, -1}};
}

void Chasm_TR_Graph::update_current_field_index(QString type_name,
  QString field_name, int& upd)
{
 auto it = field_indices_.find({type_name, field_name});

 if(it != field_indices_.end())
 {
  upd = *it;
 }
}


void Chasm_TR_Graph::add_read_token(hypernode_type* hn, QString type_name,
  QString field_name, QPair<QString, void*> val)
{
 auto it = field_indices_.find({type_name, field_name});

 if(it != field_indices_.end())
 {
  add_read_token(hn, type_name, *it, val, field_name);
 }
}

void Chasm_TR_Graph::array_append(hypernode_type* hn, hypernode_type* nhn)
{
 append_af(hn, {"", nhn}, {"proxy", nullptr});
}


void Chasm_TR_Graph::add_read_token(hypernode_type* hn, QString type_name,
  int field_index, QPair<QString, void*> val, QString field_name)
{
 auto it = types_.find(type_name);

 if(it != types_.end())
 {
  signed int sz = it->first;
  signed int offs = it->second.first;
  if( (offs >= 0) && !field_name.isEmpty() )
  {
   set_sf(hn, field_index, (hyponode_value_type) val);
  }
  else if( (offs >= 0) || (sz < 0) )
  {
   set_af(hn, field_index, (hyponode_value_type) val);
  }
  else
  {
   set_sf(hn, field_index, (hyponode_value_type) val);
  }
 }
}

void Chasm_TR_Graph::add_type_field_index(QString type_name, QString field_name, int code)
{
 field_indices_.insert({type_name, field_name}, code);
}

Chasm_TR_Graph::hypernode_type* Chasm_TR_Graph::new_hypernode_by_type_name(QString ty)
{
 auto it = types_.find(ty);
 if(it == types_.end())
   return nullptr;

 hypernode_type* result = this->new_hypernode(it.value().first,
   {ty, nullptr}, it.value().second.first, it.value().second.second);

 return result;
}

