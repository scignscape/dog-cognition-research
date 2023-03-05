
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef QH_TYPE__H
#define QH_TYPE__H

#include <QMap>
#include <QString>

#include "global-types.h"

#include "accessors.h"

#include "../qh-pack-code.h"

#include "kans.h"

KANS_(RdSC)

class Qh_Class_Object;
class Qh_Pack_Code;
class Qh_Pack_Builder;
class Qh_Type_System;

class Qh_Type
{
 QString name_;
 QString cname_;

 u1 byte_length_code_;

 void* meta_object_;

 Qh_Class_Object* qh_class_object_;

 Qh_Type_System* type_system_;

 void* local_;


 std::function<void(void*, Qh_Pack_Builder&)> static_pack_encoder_1_;

 std::function<void(void*, void*, Qh_Pack_Builder&)> static_pack_encoder_2_;
 std::function<void(void*, QString, void*, Qh_Pack_Builder&)> static_pack_encoder_3_;

 template<typename T> struct _Class_Of_Member_Function {};

 template<typename RETURN_Type, typename CLASS_Type>
 struct _Class_Of_Member_Function<RETURN_Type (CLASS_Type::*)>
 {
  using type = CLASS_Type;
 };

 template< typename T>
 using Class_Of_Member_Function = typename _Class_Of_Member_Function<T>::type;

 template <class R, class O, class... ARGS>
 struct count_args {
     static constexpr size_t n_args = sizeof...(ARGS);
 };

 template <class R, class O, class... ARGS>
 count_args<R, O, ARGS ...> constexpr make_count_args(R (O::*) (ARGS...) ) {
   return count_args<R, O, ARGS...>();
 }

public:

 Qh_Type(Qh_Type_System* ts);

 ACCESSORS(QString ,name)
 ACCESSORS(QString ,cname)

 ACCESSORS(Qh_Class_Object* ,qh_class_object)
 ACCESSORS(Qh_Type_System* ,type_system)


 ACCESSORS(MACRO_PASTE(std::function<void(void*, Qh_Pack_Builder&)>) ,static_pack_encoder_1)
 ACCESSORS(MACRO_PASTE(std::function<void(void*, void*, Qh_Pack_Builder&)>) ,static_pack_encoder_2)
 ACCESSORS(MACRO_PASTE(std::function<void(void*, QString, void*, Qh_Pack_Builder&)>) ,static_pack_encoder_3)


 Qh_Type_System* operator->()
 {
  return type_system_;
 }

 Qh_Class_Object& qh_class();
 void init_qh_class(Qh_Pack_Code& qpc);


 template<typename Local>
 Qh_Type& qh_local(Local* lcl)
 {
  local_ = lcl;
  return *this;
 }


 Qh_Type& defpack(void(*fn)(Qh_Pack_Code&));

 Qh_Pack_Builder* serialize(void* obj);
 void serialize(Qh_Pack_Builder& qpb, void* obj);


 template<typename PROV_Type>
 Qh_Type& defpack(void(PROV_Type::*fn)(Qh_Pack_Code&))
 {
  Qh_Pack_Code qpc;
  (((PROV_Type*) local_)->*fn)(qpc);
  init_qh_class(qpc);
  return *this;
 }

 template<typename PROV_Type>
 Qh_Type& defpack(void(PROV_Type::*fn)(QString tn, Qh_Pack_Code&))
 {
  Qh_Pack_Code qpc;
  (((PROV_Type*) local_)->*fn)(name_, qpc);
  init_qh_class(qpc);
  return *this;
 }



 template<typename T>
 static std::function<void(void*, Qh_Pack_Builder&)> default_pack_encoder(void (T::*fn)(Qh_Pack_Builder&))
 {
  return [fn](void* v, Qh_Pack_Builder& qpb)
  {
   (((T*) v)->*fn)(qpb);
  };
 }

 template<typename T>
 static std::function<void(void*, QString, void*, Qh_Pack_Builder&)>
   default_pack_encoder_loc(void (T::*fn)(QString, void*, Qh_Pack_Builder&))
 {
  return [fn](void* v, QString tn, void* obj, Qh_Pack_Builder& qpb)
  {
   (((T*) v)->*fn)(tn, obj, qpb);
  };
 }


 template<typename PROV_Type, typename OBJ_Type>
 using proc_t = void (PROV_Type::*)(OBJ_Type&, Qh_Pack_Builder&);

 template<typename PROV_Type, typename OBJ_Type>
 static std::function<void(void*, void*, Qh_Pack_Builder&)> default_pack_encoder_prov(
   proc_t<PROV_Type, OBJ_Type> fn)
 {
  return [fn](void* prov, void* obj, Qh_Pack_Builder& qpb)
  {
   (((PROV_Type*) prov)->*fn)( *(OBJ_Type*) obj, qpb);
  };
 }

// template<typename PROV_Type, typename OBJ_Type>
// static std::function<void(void*, void*, Qh_Pack_Builder&)> default_pack_encoder_prov(void (PROV_Type::*fn)
//   (OBJ_Type&, Qh_Pack_Builder&))
// {
//  return [fn](void* prov, void* obj, Qh_Pack_Builder& qpb)
//  {
//   // (((PROV_Type*) prov)->*fn)(obj, qpb);
//  };
// }



 template<typename VALUE_Type, typename PROC_Type>
 Qh_Type& _set_pack_encoder(PROC_Type pt)
 {
  set_static_pack_encoder_1(default_pack_encoder
    <VALUE_Type>(pt) );
  return *this;
 }

 template<typename PROV_Type, typename PROC_Type>
 Qh_Type& _set_pack_encoder_loc(PROC_Type pt)
 {
  set_static_pack_encoder_3(default_pack_encoder_loc
    <PROV_Type>(pt) );
  return *this;
 }



 template<typename PROV_Type, typename OBJ_Type> //,  typename PROC_Type>
 Qh_Type& set_pack_encoder(proc_t<PROV_Type, OBJ_Type> fn)    //(PROC_Type pt)
 {
  set_static_pack_encoder_2(default_pack_encoder_prov
    <PROV_Type, OBJ_Type>(fn) );
  return *this;
 }



 template<typename PROC_Type>
 Qh_Type& set_pack_encoder_loc(PROC_Type pt)
 {
   constexpr size_t count_args = decltype(make_count_args(pt))::n_args;

  return _set_pack_encoder_loc<
    Class_Of_Member_Function<PROC_Type>, PROC_Type>(pt);
 }

 template<int ARG_Count>
 struct _set_pack_encoder_
 {

 };


 template<typename PROC_Type>
 Qh_Type& set_pack_encoder(PROC_Type pt)
 {
  constexpr size_t count_args = decltype(make_count_args(pt))::n_args;

  return _set_pack_encoder_<count_args>::proceed(*this, pt);
//  return _set_pack_encoder<
//    Class_Of_Member_Function<PROC_Type>, PROC_Type>(pt);

//  return _set_pack_encoder_loc<
//    Class_Of_Member_Function<PROC_Type>, PROC_Type>(pt);

 }



// template<typename PROC_Type>
// Qh_Type& set_pack_encoder_prov(PROC_Type pt)
// {
//  return _set_pack_encoder_prov<
//    Class_Of_Member_Function<PROC_Type>, PROC_Type>(pt);
// }




};

template<>
struct Qh_Type::_set_pack_encoder_<1>
{
 template<typename PROC_Type>
 static Qh_Type& proceed(Qh_Type& _this, PROC_Type pt)
 {
  return _this._set_pack_encoder<
    Class_Of_Member_Function<PROC_Type>, PROC_Type>(pt);
 }
};

template<>
struct Qh_Type::_set_pack_encoder_<3>
{
 template<typename PROC_Type>
 static Qh_Type& proceed(Qh_Type& _this, PROC_Type pt)
 {
  return _this._set_pack_encoder_loc<
    Class_Of_Member_Function<PROC_Type>, PROC_Type>(pt);
 }
};

_KANS(RdSC)

#endif // QH_TYPE__H


