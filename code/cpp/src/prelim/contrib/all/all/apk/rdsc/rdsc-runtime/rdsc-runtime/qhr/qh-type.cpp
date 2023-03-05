
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "qh-type.h"

#include "qh-pack-code.h"

#include "qh-class-object.h"
#include "qh-pack-builder.h"

USING_KANS(RdSC)

Qh_Type::Qh_Type(Qh_Type_System* ts)
  :  byte_length_code_(0),
     meta_object_(nullptr),
     qh_class_object_(nullptr),
     type_system_(ts)
{

}


Qh_Pack_Builder* Qh_Type::serialize(void* obj)
{
 Qh_Pack_Code& qpc = qh_class_object_->pack_code();
 Qh_Pack_Builder* result = new Qh_Pack_Builder(qpc);
 serialize(*result, obj);
 return result;
}


void Qh_Type::serialize(Qh_Pack_Builder& qpb, void *obj)
{

 if(static_pack_encoder_1_)
   static_pack_encoder_1_(obj, qpb);

 else if(static_pack_encoder_3_)
   static_pack_encoder_3_(local_, name_, obj, qpb);

 else
   static_pack_encoder_2_(local_, obj, qpb);
}


Qh_Class_Object& Qh_Type::qh_class()
{
 if(!qh_class_object_)
 {
  qh_class_object_ = new Qh_Class_Object(this);
  qh_class_object_->qh_local(local_);
 }
 return *qh_class_object_;
}


void Qh_Type::init_qh_class(Qh_Pack_Code& qpc)
{
 qh_class_object_ = new Qh_Class_Object(this, name_);
 qh_class_object_->pack_code() = qpc;

 qh_class_object_->qh_local(local_);

}


Qh_Type& Qh_Type::defpack(void(*fn)(Qh_Pack_Code&))
{
 Qh_Pack_Code qpc;
 fn(qpc);
 init_qh_class(qpc);
 return *this;
}

//template<typename PROV_Type>
//Qh_Type& Qh_Type::defpack(void(PROV_Type::*fn)(Qh_Pack_Code&))
//{
// Qh_Pack_Code qpc;
// (((PROV_Type*) local_)->*fn)(qpc);
// init_qh_class(qpc);
// return *this;
//}
