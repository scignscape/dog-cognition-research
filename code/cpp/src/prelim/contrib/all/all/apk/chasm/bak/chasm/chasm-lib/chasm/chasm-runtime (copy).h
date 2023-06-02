
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef CHASM_RUNTIME__H
#define CHASM_RUNTIME__H

#include <QString>

#include <QStack>
#include <QVariant>

#include "accessors.h"
#include "flags.h"

#include "global-types.h"

#include <functional>

#include <QString>
#include <QVariant>
#include <QByteArray>

#include "kans.h"

#include "chasm-carrier.h"

struct _min_{};

#include "./dev/consoles/fns/s0/a3/run-s0_3_re0.cpp"
#include "./dev/consoles/fns/s0/a3/run-s0_3_re1.cpp"
#include "./dev/consoles/fns/s0/a3/run-s0_3_re2.cpp"
#include "./dev/consoles/fns/s0/a3/run-s0_3_re3.cpp"
#include "./dev/consoles/fns/s0/a3/run-s0_3_re4.cpp"
#include "./dev/consoles/fns/s0/a3/run-s0_3_re5.cpp"
#include "./dev/consoles/fns/s0/a3/run-s0_3_re6.cpp"
#include "./dev/consoles/fns/s0/a3/run-s0_3_re7.cpp"
#include "./dev/consoles/fns/s0/a3/run-s0_3_re8.cpp"
#include "./dev/consoles/fns/s0/a3/run-s0_3_re9.cpp"

#include "./dev/consoles/fns/s0/a2/run-s0_2_re0.cpp"
#include "./dev/consoles/fns/s0/a2/run-s0_2_re1.cpp"
#include "./dev/consoles/fns/s0/a2/run-s0_2_re2.cpp"
#include "./dev/consoles/fns/s0/a2/run-s0_2_re3.cpp"
#include "./dev/consoles/fns/s0/a2/run-s0_2_re4.cpp"
#include "./dev/consoles/fns/s0/a2/run-s0_2_re5.cpp"
#include "./dev/consoles/fns/s0/a2/run-s0_2_re6.cpp"
#include "./dev/consoles/fns/s0/a2/run-s0_2_re7.cpp"
#include "./dev/consoles/fns/s0/a2/run-s0_2_re8.cpp"
#include "./dev/consoles/fns/s0/a2/run-s0_2_re9.cpp"

#include "./dev/consoles/fns/s0/a1/run-s0_1_re0.cpp"
#include "./dev/consoles/fns/s0/a1/run-s0_1_re1.cpp"
#include "./dev/consoles/fns/s0/a1/run-s0_1_re2.cpp"
#include "./dev/consoles/fns/s0/a1/run-s0_1_re3.cpp"
#include "./dev/consoles/fns/s0/a1/run-s0_1_re4.cpp"
#include "./dev/consoles/fns/s0/a1/run-s0_1_re5.cpp"
#include "./dev/consoles/fns/s0/a1/run-s0_1_re6.cpp"
#include "./dev/consoles/fns/s0/a1/run-s0_1_re7.cpp"
#include "./dev/consoles/fns/s0/a1/run-s0_1_re8.cpp"
#include "./dev/consoles/fns/s0/a1/run-s0_1_re9.cpp"

#include "./dev/consoles/fns/s0/a0/run-s0_0_re0.cpp"
#include "./dev/consoles/fns/s0/a0/run-s0_0_re1.cpp"
#include "./dev/consoles/fns/s0/a0/run-s0_0_re2.cpp"
#include "./dev/consoles/fns/s0/a0/run-s0_0_re3.cpp"
#include "./dev/consoles/fns/s0/a0/run-s0_0_re4.cpp"
#include "./dev/consoles/fns/s0/a0/run-s0_0_re5.cpp"
#include "./dev/consoles/fns/s0/a0/run-s0_0_re6.cpp"
#include "./dev/consoles/fns/s0/a0/run-s0_0_re7.cpp"
#include "./dev/consoles/fns/s0/a0/run-s0_0_re8.cpp"
#include "./dev/consoles/fns/s0/a0/run-s0_0_re9.cpp"


//struct _min_{};

class Chasm_Call_Package;
class Chasm_Type_Object;

struct Chasm_Typed_Value_Representation
{
 Chasm_Type_Object* type_object;
 n8 raw_value;
 QString rep;
};

//KANS_(GTagML)

class Chasm_Runtime
{
 //QString text_;

 struct _Result
 {
  n8* _ref;
  u1* _u1;
  u2* _u2;
  QString* _QString;
  u4* _u4;
  QByteArray* _QByteArray;
  r8* _r8;
  QVariant* _QVariant;
  n8* _n8;
  void** _ptr;

  _Result() : _ref(new n8(0)), _u1(new u1(0)), _u2(new u2(0)),
    _QString(new QString), _u4(new u4(0)), _QByteArray(new QByteArray),
    _r8(new r8(0)), _QVariant(new QVariant),
    _n8(new n8(0)),  _ptr(new void*(nullptr))
    {}
 };

 u4 gen_trisym_line_index_;
 u4 gen_trisym_file_index_;
 u4 gen_trisym_col_index_;

 u4 call_package_index_;

 QStack<Chasm_Call_Package*> current_call_packages_;

 u4 current_no_file_session_;

 QMap<QString, Chasm_Type_Object*> type_objects_;

public:

 Chasm_Runtime();

 _Result Result;

 Chasm_Type_Object* register_type_object(QString name, u2 pos1code, u2 pos2code,
   u2 pos3code, u2 pos4code);

 Chasm_Type_Object* get_type_object_by_name(QString name);

 Chasm_Call_Package* new_call_package();

 Chasm_Carrier gen_carrier(Chasm_Typed_Value_Representation& tvr);
 Chasm_Carrier gen_carrier(QString type_name = {});
 Chasm_Carrier gen_carrier(u1 type_flag);

 Chasm_Carrier gen_shared_ref_carrier(std::shared_ptr<n8>* ss);
 //Chasm_Carrier gen_shared_ref_carrier(n8 val);

 template<typename CARRIER_Type>
 inline Chasm_Carrier gen_carrier();

 template<typename CARRIER_Type>
 inline Chasm_Carrier gen_carrier(void* value);

 void init_no_file_session();

 void release(Chasm_Call_Package* ccp);

 template<typename FN_Type>
 void evaluate_3(Chasm_Call_Package* ccp, u4 fncode, FN_Type fn, Chasm_Carrier* rcar = nullptr)
 {
  u1 sl = fncode / 10000;

  u1 rr = (fncode % 10000) / 1000;

  fncode %= 1000;

  switch(rr)
  {
  case 0:
   evaluate_3_re0(ccp, fncode, (minimal_fn_s0_re0_type) fn);
   break;

  case 1:
   evaluate_3_re1(ccp, fncode, (minimal_fn_s0_re1_type) fn, rcar);
   break;

  case 2:
   evaluate_3_re2(ccp, fncode, (minimal_fn_s0_re2_type) fn, rcar);
   break;

  case 3:
   evaluate_3_re3(ccp, fncode, (minimal_fn_s0_re3_type) fn, rcar);
   break;

  case 4:
   evaluate_3_re4(ccp, fncode, (minimal_fn_s0_re4_type) fn, rcar);
   break;

  case 5:
   evaluate_3_re5(ccp, fncode, (minimal_fn_s0_re5_type) fn, rcar);
   break;

  case 6:
   evaluate_3_re6(ccp, fncode, (minimal_fn_s0_re6_type) fn, rcar);
   break;

  case 7:
   evaluate_3_re7(ccp, fncode, (minimal_fn_s0_re7_type) fn, rcar);
   break;

  case 8:
   evaluate_3_re8(ccp, fncode, (minimal_fn_s0_re8_type) fn, rcar);
   break;

  case 9:
   evaluate_3_re9(ccp, fncode, (minimal_fn_s0_re9_type) fn, rcar);
   break;
  }
 }


 template<typename FN_Type>
 void evaluate_2(Chasm_Call_Package* ccp, u4 fncode, FN_Type fn, Chasm_Carrier* rcar = nullptr)
 {
  u1 sl = fncode / 1000;

  u1 rr = (fncode % 1000) / 100;

  fncode %= 100;

  switch(rr)
  {
  case 0:
   evaluate_2_re0(ccp, fncode, (minimal_fn_s0_re0_type) fn);
   break;

  case 1:
   evaluate_2_re1(ccp, fncode, (minimal_fn_s0_re1_type) fn, rcar);
   break;

  case 2:
   evaluate_2_re2(ccp, fncode, (minimal_fn_s0_re2_type) fn, rcar);
   break;

  case 3:
   evaluate_2_re3(ccp, fncode, (minimal_fn_s0_re3_type) fn, rcar);
   break;

  case 4:
   evaluate_2_re4(ccp, fncode, (minimal_fn_s0_re4_type) fn, rcar);
   break;

  case 5:
   evaluate_2_re5(ccp, fncode, (minimal_fn_s0_re5_type) fn, rcar);
   break;

  case 6:
   evaluate_2_re6(ccp, fncode, (minimal_fn_s0_re6_type) fn, rcar);
   break;

  case 7:
   evaluate_2_re7(ccp, fncode, (minimal_fn_s0_re7_type) fn, rcar);
   break;

  case 8:
   evaluate_2_re8(ccp, fncode, (minimal_fn_s0_re8_type) fn, rcar);
   break;

  case 9:
   evaluate_2_re9(ccp, fncode, (minimal_fn_s0_re9_type) fn, rcar);
   break;
  }
 }


 template<typename FN_Type>
 void evaluate_1(Chasm_Call_Package* ccp, u4 fncode, FN_Type fn, Chasm_Carrier* rcar = nullptr)
 {
  u1 sl = fncode / 100;

  u1 rr = (fncode % 100) / 10;

  fncode %= 100;

  switch(rr)
  {
  case 0:
   evaluate_1_re0(ccp, fncode, (minimal_fn_s0_re0_type) fn);
   break;

  case 1:
   evaluate_1_re1(ccp, fncode, (minimal_fn_s0_re1_type) fn, rcar);
   break;

  case 2:
   evaluate_1_re2(ccp, fncode, (minimal_fn_s0_re2_type) fn, rcar);
   break;

  case 3:
   evaluate_1_re3(ccp, fncode, (minimal_fn_s0_re3_type) fn, rcar);
   break;

  case 4:
   evaluate_1_re4(ccp, fncode, (minimal_fn_s0_re4_type) fn, rcar);
   break;

  case 5:
   evaluate_1_re5(ccp, fncode, (minimal_fn_s0_re5_type) fn, rcar);
   break;

  case 6:
   evaluate_1_re6(ccp, fncode, (minimal_fn_s0_re6_type) fn, rcar);
   break;

  case 7:
   evaluate_1_re7(ccp, fncode, (minimal_fn_s0_re7_type) fn, rcar);
   break;

  case 8:
   evaluate_1_re8(ccp, fncode, (minimal_fn_s0_re8_type) fn, rcar);
   break;

  case 9:
   evaluate_1_re9(ccp, fncode, (minimal_fn_s0_re9_type) fn, rcar);
   break;
  }

 }

 struct _True_ {};
 struct _False_ {};

 template<typename T> struct _Is_Member_Function {};

 template<typename RETURN_Type, typename CLASS_Type>
 struct _Is_Member_Function<RETURN_Type (CLASS_Type::*)>
 {
  using type = _True_;
 };

 template<typename RETURN_Type>
 struct _Is_Member_Function<RETURN_Type (*)>
 {
  using type = _True_;
 };

 template< typename T>
 using Is_Member_Function = typename _Is_Member_Function<T>::type;



 template<typename SFN_Type> //, typename ISM = Is_Member_Function<SFN_Type> >
 void evaluate_s1_0(Chasm_Call_Package* ccp, u4 fncode,
  SFN_Type sfn,  Chasm_Carrier* rcar = nullptr)//;

// template<typename SFN_Type>
// void evaluate_s1_0<SFN_Type, _True_>
//   (Chasm_Call_Package* ccp, u4 fncode,
//  SFN_Type sfn,  Chasm_Carrier* rcar = nullptr)
 {
  u1 sl = fncode / 10;

  u1 rr = (fncode % 10);

  fncode %= 10;

  switch(rr)
  {
  case 0:
   evaluate_0_re0(ccp, fncode, nullptr,
     (minimal_fn_s1_re0_type) sfn);
   break;

  case 9:
   evaluate_0_re9(ccp, fncode, nullptr,
     (minimal_fn_s1_re9_type) sfn, rcar);
   break;

  }
 }

 template<typename FN_Type>
 void evaluate_s0_0(Chasm_Call_Package* ccp, u4 fncode,
  FN_Type fn, Chasm_Carrier* rcar = nullptr)
 {
  u1 sl = fncode / 10;

  u1 rr = (fncode % 10);

  fncode %= 10;

  switch(rr)
  {
  case 0:
   evaluate_0_re0(ccp, fncode, (minimal_fn_s0_re0_type) fn, nullptr);
   break;

  case 9:
   evaluate_0_re9(ccp, fncode, (minimal_fn_s0_re9_type) fn, nullptr, rcar);
   break;

  }
 }



// template<typename FN_Type>
// void evaluate_s0_0(Chasm_Call_Package* ccp, u4 fncode, FN_Type fn, Chasm_Carrier* rcar = nullptr)
// {
//  u1 sl = fncode / 10;

////  if(sl == 8)
////  {
////   evaluate_s1_0(ccp, fncode, fn);
////   return;
////  }

//  u1 rr = (fncode % 10);

//  fncode %= 10;

//  switch(rr)
//  {
//  case 0:
//   evaluate_0_re0(ccp, fncode, (minimal_fn_s0_re0_type) fn, nullptr);
//   break;

//  case 1:
//   evaluate_0_re1(ccp, fncode, (minimal_fn_s0_re1_type) fn, rcar);
//   break;

//  case 2:
//   evaluate_0_re2(ccp, fncode, (minimal_fn_s0_re2_type) fn, rcar);
//   break;

//  case 3:
//   evaluate_0_re3(ccp, fncode, (minimal_fn_s0_re3_type) fn, rcar);
//   break;

//  case 4:
//   evaluate_0_re4(ccp, fncode, (minimal_fn_s0_re4_type) fn, rcar);
//   break;

//  case 5:
//   evaluate_0_re5(ccp, fncode, (minimal_fn_s0_re5_type) fn, rcar);
//   break;

//  case 6:
//   evaluate_0_re6(ccp, fncode, (minimal_fn_s0_re6_type) fn, rcar);
//   break;

//  case 7:
//   evaluate_0_re7(ccp, fncode, (minimal_fn_s0_re7_type) fn, rcar);
//   break;

//  case 8:
//   evaluate_0_re8(ccp, fncode, (minimal_fn_s0_re8_type) fn, rcar);
//   break;

//  case 9:
//   evaluate_0_re9(ccp, fncode, (minimal_fn_s0_re9_type) fn, nullptr, rcar);
//   break;
//  }
// }


 template<typename SFN_Type>
 void evaluate_s1(Chasm_Call_Package* ccp, u4 fncode, SFN_Type fn, Chasm_Carrier* rcar = nullptr)
 {
  if(fncode >= 10000)
    ;//evaluate_3(ccp, fncode, fn, rcar);

  else if(fncode >= 1000)
    ;//evaluate_2(ccp, fncode, fn, rcar);

  else if(fncode >= 100)
    ;//evaluate_1(ccp, fncode, fn, rcar);

  else
    evaluate_s1_0(ccp, fncode, fn, rcar);
 }

 template<typename RETURN_Type, typename CLASS_Type> //  typename T, typename FN_Type, typename CT = Is_Member_Function<FN_Type> >
 void evaluate_0(Chasm_Call_Package* ccp, u4 fncode,
   RETURN_Type (CLASS_Type::*fn), Chasm_Carrier* rcar = nullptr)
 {
  u1 sl = fncode / 10;

  if(sl == 8)
  {
   evaluate_s1_0(ccp, fncode, fn);
   return;
  }
 }

// template<typename RETURN_Type>//, typename ISM = Is_Member_Function<FN_Type> >
// void evaluate_0(Chasm_Call_Package* ccp, u4 fncode,
//   RETURN_Type(*fn), Chasm_Carrier* rcar = nullptr)

 template<typename FN_Type>//, typename ISM = Is_Member_Function<FN_Type> >
 void evaluate_0(Chasm_Call_Package* ccp, u4 fncode,
   FN_Type fn, Chasm_Carrier* rcar = nullptr)
 {
  u1 sl = fncode / 10;

  if(sl == 7)
  {
   evaluate_s0_0(ccp, fncode, fn);
   return;
  }
 }

// template<typename SFN_Type>
// void evaluate_s01_0(Chasm_Call_Package* ccp, u4 fncode,
//  SFN_Type sfn, Chasm_Carrier* rcar = nullptr)
// {
//  u1 sl = fncode / 10;

//  if(sl == 8)
//    evaluate_s1_0(ccp, fncode, sfn, rcar);

//  else
//    evaluate_0(ccp, fncode, sfn, rcar);
// }

 template<typename SFN_Type>
 void evaluate_s01(Chasm_Call_Package* ccp, u4 fncode, SFN_Type fn, Chasm_Carrier* rcar = nullptr)
 {
  if(fncode >= 10000)
    ;//evaluate_3(ccp, fncode, fn, rcar);

  else if(fncode >= 1000)
    ;//evaluate_2(ccp, fncode, fn, rcar);

  else if(fncode >= 100)
    ;//evaluate_1(ccp, fncode, fn, rcar);

  else
    ;//evaluate_s01_0(ccp, fncode, fn, rcar);
 }



 template<typename FN_Type>
 void evaluate(Chasm_Call_Package* ccp, u4 fncode, FN_Type fn, Chasm_Carrier* rcar = nullptr)
 {
  if(fncode >= 10000)
    evaluate_3(ccp, fncode, fn, rcar);

  else if(fncode >= 1000)
    evaluate_2(ccp, fncode, fn, rcar);

  else if(fncode >= 100)
    evaluate_1(ccp, fncode, fn, rcar);

  else
    ; //evaluate_0(ccp, fncode, fn, rcar);
//?    evaluate_0(ccp, fncode, fn, rcar);
 }


// template<typename FN_Type, typename CT = Is_Member_Function<FN_Type> >
// void _evaluate_(Chasm_Call_Package* ccp, u4 fncode, FN_Type fn, Chasm_Carrier* rcar = nullptr)
// {
////  if(fncode >= 10000)
////    evaluate_3(ccp, fncode, fn, rcar);

////  else if(fncode >= 1000)
////    evaluate_2(ccp, fncode, fn, rcar);

////  else if(fncode >= 100)
////    evaluate_1(ccp, fncode, fn, rcar);

////  else
//   evaluate_0(ccp, fncode, fn, rcar);
////?    evaluate_0(ccp, fncode, fn, rcar);
// }

 template<typename FN_Type>
 void _evaluate_(Chasm_Call_Package* ccp, u4 fncode, FN_Type fn, Chasm_Carrier* rcar = nullptr)
 {
//  if(fncode >= 10000)
//    evaluate_3(ccp, fncode, fn, rcar);

//  else if(fncode >= 1000)
//    evaluate_2(ccp, fncode, fn, rcar);

//  else if(fncode >= 100)
//    evaluate_1(ccp, fncode, fn, rcar);

//  else
   evaluate_0(ccp, fncode, fn, rcar);
//?    evaluate_0(ccp, fncode, fn, rcar);
 }





 void evaluate_3_re0(Chasm_Call_Package* ccp, u2 fncode, minimal_fn_s0_re0_type fn);
 void evaluate_3_re1(Chasm_Call_Package* ccp, u2 fncode, minimal_fn_s0_re1_type fn, Chasm_Carrier* rcar = nullptr);
 void evaluate_3_re2(Chasm_Call_Package* ccp, u2 fncode, minimal_fn_s0_re2_type fn, Chasm_Carrier* rcar = nullptr);
 void evaluate_3_re3(Chasm_Call_Package* ccp, u2 fncode, minimal_fn_s0_re3_type fn, Chasm_Carrier* rcar = nullptr);
 void evaluate_3_re4(Chasm_Call_Package* ccp, u2 fncode, minimal_fn_s0_re4_type fn, Chasm_Carrier* rcar = nullptr);
 void evaluate_3_re5(Chasm_Call_Package* ccp, u2 fncode, minimal_fn_s0_re5_type fn, Chasm_Carrier* rcar = nullptr);
 void evaluate_3_re6(Chasm_Call_Package* ccp, u2 fncode, minimal_fn_s0_re6_type fn, Chasm_Carrier* rcar = nullptr);
 void evaluate_3_re7(Chasm_Call_Package* ccp, u2 fncode, minimal_fn_s0_re7_type fn, Chasm_Carrier* rcar = nullptr);
 void evaluate_3_re8(Chasm_Call_Package* ccp, u2 fncode, minimal_fn_s0_re8_type fn, Chasm_Carrier* rcar = nullptr);
 void evaluate_3_re9(Chasm_Call_Package* ccp, u2 fncode, minimal_fn_s0_re9_type fn, Chasm_Carrier* rcar = nullptr);


 void evaluate_2_re0(Chasm_Call_Package* ccp, u2 fncode, minimal_fn_s0_re0_type fn);
 void evaluate_2_re1(Chasm_Call_Package* ccp, u2 fncode, minimal_fn_s0_re1_type fn, Chasm_Carrier* rcar = nullptr);
 void evaluate_2_re2(Chasm_Call_Package* ccp, u2 fncode, minimal_fn_s0_re2_type fn, Chasm_Carrier* rcar = nullptr);
 void evaluate_2_re3(Chasm_Call_Package* ccp, u2 fncode, minimal_fn_s0_re3_type fn, Chasm_Carrier* rcar = nullptr);
 void evaluate_2_re4(Chasm_Call_Package* ccp, u2 fncode, minimal_fn_s0_re4_type fn, Chasm_Carrier* rcar = nullptr);
 void evaluate_2_re5(Chasm_Call_Package* ccp, u2 fncode, minimal_fn_s0_re5_type fn, Chasm_Carrier* rcar = nullptr);
 void evaluate_2_re6(Chasm_Call_Package* ccp, u2 fncode, minimal_fn_s0_re6_type fn, Chasm_Carrier* rcar = nullptr);
 void evaluate_2_re7(Chasm_Call_Package* ccp, u2 fncode, minimal_fn_s0_re7_type fn, Chasm_Carrier* rcar = nullptr);
 void evaluate_2_re8(Chasm_Call_Package* ccp, u2 fncode, minimal_fn_s0_re8_type fn, Chasm_Carrier* rcar = nullptr);
 void evaluate_2_re9(Chasm_Call_Package* ccp, u2 fncode, minimal_fn_s0_re9_type fn, Chasm_Carrier* rcar = nullptr);


 void evaluate_1_re0(Chasm_Call_Package* ccp, u2 fncode, minimal_fn_s0_re0_type fn);
 void evaluate_1_re1(Chasm_Call_Package* ccp, u2 fncode, minimal_fn_s0_re1_type fn, Chasm_Carrier* rcar = nullptr);
 void evaluate_1_re2(Chasm_Call_Package* ccp, u2 fncode, minimal_fn_s0_re2_type fn, Chasm_Carrier* rcar = nullptr);
 void evaluate_1_re3(Chasm_Call_Package* ccp, u2 fncode, minimal_fn_s0_re3_type fn, Chasm_Carrier* rcar = nullptr);
 void evaluate_1_re4(Chasm_Call_Package* ccp, u2 fncode, minimal_fn_s0_re4_type fn, Chasm_Carrier* rcar = nullptr);
 void evaluate_1_re5(Chasm_Call_Package* ccp, u2 fncode, minimal_fn_s0_re5_type fn, Chasm_Carrier* rcar = nullptr);
 void evaluate_1_re6(Chasm_Call_Package* ccp, u2 fncode, minimal_fn_s0_re6_type fn, Chasm_Carrier* rcar = nullptr);
 void evaluate_1_re7(Chasm_Call_Package* ccp, u2 fncode, minimal_fn_s0_re7_type fn, Chasm_Carrier* rcar = nullptr);
 void evaluate_1_re8(Chasm_Call_Package* ccp, u2 fncode, minimal_fn_s0_re8_type fn, Chasm_Carrier* rcar = nullptr);
 void evaluate_1_re9(Chasm_Call_Package* ccp, u2 fncode, minimal_fn_s0_re9_type fn, Chasm_Carrier* rcar = nullptr);


 void evaluate_0_re0(Chasm_Call_Package* ccp, u2 fncode,
   minimal_fn_s0_re0_type fn,
   minimal_fn_s1_re0_type sfn);

 void evaluate_0_re1(Chasm_Call_Package* ccp, u2 fncode, minimal_fn_s0_re1_type fn, Chasm_Carrier* rcar = nullptr);
 void evaluate_0_re2(Chasm_Call_Package* ccp, u2 fncode, minimal_fn_s0_re2_type fn, Chasm_Carrier* rcar = nullptr);
 void evaluate_0_re3(Chasm_Call_Package* ccp, u2 fncode, minimal_fn_s0_re3_type fn, Chasm_Carrier* rcar = nullptr);
 void evaluate_0_re4(Chasm_Call_Package* ccp, u2 fncode, minimal_fn_s0_re4_type fn, Chasm_Carrier* rcar = nullptr);
 void evaluate_0_re5(Chasm_Call_Package* ccp, u2 fncode, minimal_fn_s0_re5_type fn, Chasm_Carrier* rcar = nullptr);
 void evaluate_0_re6(Chasm_Call_Package* ccp, u2 fncode, minimal_fn_s0_re6_type fn, Chasm_Carrier* rcar = nullptr);
 void evaluate_0_re7(Chasm_Call_Package* ccp, u2 fncode, minimal_fn_s0_re7_type fn, Chasm_Carrier* rcar = nullptr);
 void evaluate_0_re8(Chasm_Call_Package* ccp, u2 fncode, minimal_fn_s0_re8_type fn, Chasm_Carrier* rcar = nullptr);

 void evaluate_0_re9(Chasm_Call_Package* ccp, u2 fncode,
   minimal_fn_s0_re9_type fn, minimal_fn_s1_re9_type sfn, Chasm_Carrier* rcar = nullptr);

//.. ACCESSORS(QString ,text)

// void test_cuo();

// void test_method(QString path, u4 val1, u4 val2);


};

// _KANS(GTagML)

#endif // CHASM_RUNTIME__H

