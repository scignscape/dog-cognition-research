
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef DW_TYPE__H
#define DW_TYPE__H

#include <functional>

#include <QMap>

#include "global-types.h"

#include "dw-stage-value.h"
#include "stage/dw-stage-queue.h"

// #include "_whitedb/_whitedb.h"

#include "accessors.h"

#ifndef RTTI_READ
#define RTTI_READ(tn) \
rtti_read<tn>(#tn)
#endif

#ifndef RTTI_READ_2_1
#define RTTI_READ_2_1(ho_tname ,tn) \
rtti_read<ho_tname<tn>>("(" #ho_tname \
  " " #tn ")")
#endif

#include "kans.h"

KANS_(DGDB)

//class DgDb_Node;

class DW_Node;

class DW_Stage_Value;
struct DW_Stage_Queue;


class DW_Type
{
 QString name_;
 QString cname_;

 u4 byte_length_;
 u1 byte_length_code_;

 s2 stash_id_;

 void* meta_object_;

 std::function<void(void*, QByteArray& qba, 
   DW_Stage_Value::Callback_type cb)> stage_encoder_;

 std::function<void(const QByteArray& qba, 
  QMap<u4, DW_Stage_Value>& qm, DW_Stage_Queue& sq)> stage_queue_initializer_;


 std::function<void(void*, QByteArray& qba)> opaque_encoder_;
 std::function<void(void*, const QByteArray& qba)> opaque_decoder_;


 std::function<void*(DW_Node*, 
   std::function<void*(u4)> )> raw_binary_encoder_;

 std::function<void(void*, QByteArray& qba)> binary_encoder_;
 std::function<void(void*, const QByteArray& qba)> binary_decoder_;

 std::function<void*(DW_Node*, 
   std::function<void*(n8)> )> dw_record_encoder_;

 //std::function<void(QQueue<void*>& vals)> stage_queue_reader_;

 std::function<void(QQueue<void*>& vals)> stage_queue_reader_;

 template<typename T> struct _Class_Of_Member_Function {};

 template<typename RETURN_Type, typename CLASS_Type>
 struct _Class_Of_Member_Function<RETURN_Type (CLASS_Type::*)>
 {  
  using type = CLASS_Type;    
 };

 template< typename T> 
 using Class_Of_Member_Function = typename _Class_Of_Member_Function<T>::type;


public:

 ACCESSORS(MACRO_PASTE(std::function<void*(DW_Node*, 
   std::function<void*(u4)> )>) ,raw_binary_encoder)

 ACCESSORS__GET(std::function<void(void*, QByteArray&)> ,binary_encoder)
 ACCESSORS__GET(std::function<void(void*, const QByteArray&)> ,binary_decoder)

 ACCESSORS__GET(std::function<void(void*, QByteArray&)> ,opaque_encoder)
 ACCESSORS__GET(std::function<void(void*, const QByteArray&)> ,opaque_decoder)


 ACCESSORS__GET(MACRO_PASTE(std::function<void(void*, QByteArray& qba, 
   DW_Stage_Value::Callback_type cb)>) ,stage_encoder)

 ACCESSORS__GET(std::function<void(QQueue<void*>& vals)> ,stage_queue_reader)

 ACCESSORS__GET(MACRO_PASTE(std::function<void(const QByteArray& qba, 
  QMap<u4, DW_Stage_Value>& qm, DW_Stage_Queue& sq)>) ,stage_queue_initializer)

 ACCESSORS(MACRO_PASTE(std::function<void*(DW_Node*, 
   std::function<void*(n8)> )>) ,dw_record_encoder)

 ACCESSORS(u4 ,byte_length)
 ACCESSORS(u1 ,byte_length_code)

 ACCESSORS(s2 ,stash_id)

 ACCESSORS(QString ,name)
 ACCESSORS(QString ,cname)


 template<typename T>
 static std::function<void(void*, QByteArray&)> default_binary_encoder(void (T::*fn)(QByteArray&))
 {
  return [fn](void* v, QByteArray& qba)
  {
   (((T*) v)->*fn)(qba);
  };
 }


 template<typename T>
 static std::function<void(void*, const QByteArray&)> 
   default_binary_decoder(void (T::*fn)(const QByteArray&))
 {
  return [fn](void* v, const QByteArray& qba)
  {
   (((T*) v)->*fn)(qba);
  };
 }

 template<typename PROC_Type>
 DW_Type& set_stage_encoder(PROC_Type pt)
 {
  stage_encoder_ = (void(*)(void*, QByteArray& qba,
    DW_Stage_Value::Callback_type cb)) pt;
  return *this;
 }  

 template<typename PROC_Type>
 DW_Type& set_stage_queue_initializer(PROC_Type pt)
 {
  stage_queue_initializer_ = (void(*)(const QByteArray& qba, 
  QMap<u4, DW_Stage_Value>& qm, DW_Stage_Queue& sq)) pt;
  return *this;
 }  

 template<typename PROC_Type>
 DW_Type& set_stage_queue_reader(PROC_Type pt)
 {
  stage_queue_reader_ = (std::function<void(QQueue<void*>&)>) pt;
  return *this;
 }  

 template<typename VALUE_Type, typename PROC_Type>
 DW_Type& _set_default_stage_queue_reader(PROC_Type pt)
 {
  return set_stage_queue_reader(default_stage_queue_reader
     <VALUE_Type>(pt) );
 }  

 template<typename PROC_Type>
 DW_Type& set_default_stage_queue_reader(PROC_Type pt)
 {
  return _set_default_stage_queue_reader<
    Class_Of_Member_Function<PROC_Type>, PROC_Type>(pt);
 }  

 template<typename PROC_Type>
 DW_Type& set_binary_encoder(PROC_Type pt)
 {
  binary_encoder_ = pt;
  return *this;
 }  

 template<typename VALUE_Type, typename PROC_Type>
 DW_Type& _set_default_binary_encoder(PROC_Type pt)
 {
  return set_binary_encoder(default_binary_encoder
     <VALUE_Type>(pt) );
  return *this;
 }  

 template<typename PROC_Type>
 DW_Type& set_default_binary_encoder(PROC_Type pt)
 {
  return _set_default_binary_encoder<
    Class_Of_Member_Function<PROC_Type>, PROC_Type>(pt);
 }  


 template<typename PROC_Type>
 DW_Type& _set_static_opaque_encoder(PROC_Type pt)
 {
  opaque_encoder_ = pt;
  return *this;
 }

 template<typename PROC_Type>
 DW_Type& set_static_opaque_encoder(PROC_Type pt)
 {
  static s2 stash_id = 0;
  --stash_id;
  opaque_encoder_ = pt;
  stash_id_ = stash_id;
  return *this;
 }

 template<typename VALUE_Type, typename PROC_Type>
 DW_Type& _set_opaque_encoder(PROC_Type pt)
 {
  return set_static_opaque_encoder(default_binary_encoder
     <VALUE_Type>(pt) );
  //return *this;
 }


 template<typename PROC_Type>
 DW_Type& set_opaque_encoder(PROC_Type pt)
 {
  return _set_opaque_encoder<
    Class_Of_Member_Function<PROC_Type>, PROC_Type>(pt);
 }



 template<typename PROC_Type>
 DW_Type& set_binary_decoder(PROC_Type pt)
 {
  binary_decoder_ = pt;
  return *this;
 }  

 template<typename VALUE_Type, typename PROC_Type>
 DW_Type& _set_default_binary_decoder(PROC_Type pt)
 {
  return set_binary_decoder(default_binary_decoder
     <VALUE_Type>(pt) );
  return *this;
 }  

 template<typename PROC_Type>
 DW_Type& set_default_binary_decoder(PROC_Type pt)
 {
  return _set_default_binary_decoder<
    Class_Of_Member_Function<PROC_Type>, PROC_Type>(pt);
 }  


 template<typename PROC_Type>
 DW_Type& set_static_opaque_decoder(PROC_Type pt)
 {
  opaque_decoder_ = pt;
  return *this;
 }

 template<typename VALUE_Type, typename PROC_Type>
 DW_Type& _set_opaque_decoder(PROC_Type pt)
 {
  return set_static_opaque_decoder(default_binary_decoder
     <VALUE_Type>(pt) );
  return *this;
 }

 template<typename PROC_Type>
 DW_Type& set_opaque_decoder(PROC_Type pt)
 {
  return _set_opaque_decoder<
    Class_Of_Member_Function<PROC_Type>, PROC_Type>(pt);
 }


 template<typename CType>
 void rtti_read(QString name)
 {
  name_ = name;
  cname_ = QString::fromStdString(typeid(CType).name());
  byte_length_ = sizeof(CType);
  if( (byte_length_ == 1) || (byte_length_ == 2)
    || (byte_length_ == 4) || (byte_length_ == 8) )
    byte_length_code_ = byte_length_; 
 } 


 DW_Type();

 DW_Type& default_object_layout();
 

};


_KANS(DGDB)

#endif // DW_TYPE__H


