
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "dw-type-builder.h"

#include "dw-type.h"
//#include "graph/dgdb-node.h"

USING_KANS(DGDB)

DW_Type_Builder::DW_Type_Builder()
{

}

template<typename NUM_Type, u4 BYTE_Length>
void* default_raw_binary_encoder(DW_Node* node, 
  std::function<void*(n8)> cb)
{
 void* mem = cb(BYTE_Length);
 NUM_Type* val = new (mem) NUM_Type;
 //?*val = *(NUM_Type*) node->vertex();
}

template<typename NUM_Type>
std::function<void*(DW_Node*, 
  std::function<void*(u4)> )> get_default_raw_binary_encoder(u4 byte_length)
{
 switch(byte_length)
 {
 case 1: return &default_raw_binary_encoder<NUM_Type, 1>;
 case 2: return &default_raw_binary_encoder<NUM_Type, 2>;
 case 4: return &default_raw_binary_encoder<NUM_Type, 4>;
 case 8: return &default_raw_binary_encoder<NUM_Type, 8>;
 default: return nullptr; 
 }
}

void DW_Type_Builder::build(QMap<QString, DW_Type*>* type_map, 
   std::function<void(QString, DW_Type*)> cb)
{
 DW_Type* ty_u1 = new DW_Type;
 ty_u1->RTTI_READ(u1);
 ty_u1->set_raw_binary_encoder(get_default_raw_binary_encoder<u1>(ty_u1->byte_length()));
 if(cb) cb(ty_u1->name(), ty_u1);
 if(type_map) (*type_map)[ty_u1->name()] = ty_u1;
   
 DW_Type* ty_u2 = new DW_Type;
 ty_u2->RTTI_READ(u2);
 ty_u2->set_raw_binary_encoder(get_default_raw_binary_encoder<u2>(ty_u2->byte_length()));
 if(cb) cb(ty_u2->name(), ty_u2);
 if(type_map) (*type_map)[ty_u2->name()] = ty_u2;

 DW_Type* ty_u4 = new DW_Type;
 ty_u4->RTTI_READ(u4);
 ty_u4->set_raw_binary_encoder(get_default_raw_binary_encoder<u4>(ty_u4->byte_length()));
 if(cb) cb(ty_u4->name(), ty_u4);
 if(type_map) (*type_map)[ty_u4->name()] = ty_u4;

 DW_Type* ty_n8 = new DW_Type;
 ty_n8->RTTI_READ(n8);
 ty_n8->set_raw_binary_encoder(get_default_raw_binary_encoder<n8>(ty_n8->byte_length()));
 if(cb) cb(ty_n8->name(), ty_n8);
 if(type_map) (*type_map)[ty_n8->name()] = ty_n8;

}


