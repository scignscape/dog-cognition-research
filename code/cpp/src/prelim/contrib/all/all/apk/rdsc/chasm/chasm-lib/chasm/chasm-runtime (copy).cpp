
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "chasm-runtime.h"

#include <QString>
#include <QVariant>
#include <QByteArray>

#include <QUrl>

#include <QPoint>

#define FULL_INCLUDE
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


//#include "kans.h"
//USING_KANS(GTagML)

#include <QDebug>

//#include "compilation-unit-object.h"
//#include "unified-runtime-object.h"
//#include "metatype-object.h"

#include "chasm-call-package.h"
#include "chasm-channel.h"

#include "chasm-type-object.h"


Chasm_Runtime::Chasm_Runtime()
 :  gen_trisym_line_index_(0), gen_trisym_file_index_(0),
    gen_trisym_col_index_(0), call_package_index_(0),
    current_no_file_session_(0)
{
 register_type_object("n8&", 0, 0, 0, -1);
 register_type_object("n8&!", 0, 0, 0, -1);
 //register_type_object("n8&!!", 0, 0, 0, -1);

 register_type_object("u1", 1, 10, 100, 1000);
 register_type_object("u2", 2, 20, 200, 2000);
 register_type_object("QString", 3, 30, 300, 3000);
 register_type_object("u4", 4, 40, 400, 4000);
 register_type_object("QByteArray", 5, 50, 500, 5000);
 register_type_object("r8", 6, 60, 600, 6000);
 register_type_object("QVariant", 7, 70, 700, 7000);
 register_type_object("n8", 8, 80, 800, 8000);
 register_type_object("void*", 9, 90, 900, 9000);
}

Chasm_Type_Object* Chasm_Runtime::get_type_object_by_name(QString name)
{
 return type_objects_.value(name);
}

Chasm_Type_Object* Chasm_Runtime::register_type_object(QString name, u2 pos1code, u2 pos2code,
  u2 pos3code, u2 pos4code)
{
 Chasm_Type_Object* result = new Chasm_Type_Object(name, pos1code, pos2code,
   pos3code, pos4code);

 type_objects_.insert(name, result);

 return result;
}


Chasm_Carrier Chasm_Runtime::gen_shared_ref_carrier(std::shared_ptr<n8>* ss)
{
 return gen_carrier(0).take_shared_ref_value(ss);
}

//Chasm_Carrier Chasm_Runtime::gen_shared_ref_carrier(n8 val)
//{
// std::shared_ptr<n8>* ss = new std::shared_ptr<n8>((n8*) val);
// return gen_carrier(0).take_twice_shared_ref_value(ss);
//}


template<>
Chasm_Carrier Chasm_Runtime::gen_carrier<n8&>()
{
 return gen_carrier(0);
}

template<>
Chasm_Carrier Chasm_Runtime::gen_carrier<u1>()
{
 return gen_carrier(1);
}

template<>
Chasm_Carrier Chasm_Runtime::gen_carrier<u2>()
{
 return gen_carrier(2);
}

template<>
Chasm_Carrier Chasm_Runtime::gen_carrier<QString>()
{
 return gen_carrier(3);
}

template<>
Chasm_Carrier Chasm_Runtime::gen_carrier<u4>()
{
 return gen_carrier(4);
}

template<>
Chasm_Carrier Chasm_Runtime::gen_carrier<QByteArray>()
{
 return gen_carrier(5);
}

template<>
Chasm_Carrier Chasm_Runtime::gen_carrier<r8>()
{
 return gen_carrier(6);
}

template<>
Chasm_Carrier Chasm_Runtime::gen_carrier<QVariant>()
{
 return gen_carrier(7);
}

template<>
Chasm_Carrier Chasm_Runtime::gen_carrier<n8>()
{
 return gen_carrier(8);
}

template<>
Chasm_Carrier Chasm_Runtime::gen_carrier<void*>()
{
 return gen_carrier(9);
}


template<>
Chasm_Carrier Chasm_Runtime::gen_carrier<n8&>(void* pv)
{
 return gen_carrier(0).take_value(pv);
}

template<>
Chasm_Carrier Chasm_Runtime::gen_carrier<u1>(void* pv)
{
 return gen_carrier(1).take_value(pv);
}

template<>
Chasm_Carrier Chasm_Runtime::gen_carrier<u2>(void* pv)
{
 return gen_carrier(2).take_value(pv);
}

template<>
Chasm_Carrier Chasm_Runtime::gen_carrier<QString>(void* pv)
{
 return gen_carrier(3).take_value(pv);
}

template<>
Chasm_Carrier Chasm_Runtime::gen_carrier<u4>(void* pv)
{
 return gen_carrier(4).take_value(pv);
}

template<>
Chasm_Carrier Chasm_Runtime::gen_carrier<QByteArray>(void* pv)
{
 return gen_carrier(5).take_value(pv);
}

template<>
Chasm_Carrier Chasm_Runtime::gen_carrier<r8>(void* pv)
{
 return gen_carrier(6).take_value(pv);
}

template<>
Chasm_Carrier Chasm_Runtime::gen_carrier<QVariant>(void* pv)
{
 return gen_carrier(7).take_value(pv);
}

template<>
Chasm_Carrier Chasm_Runtime::gen_carrier<n8>(void* pv)
{
 return gen_carrier(8).take_value(pv);
}

template<>
Chasm_Carrier Chasm_Runtime::gen_carrier<void*>(void* pv)
{
 return gen_carrier(9).take_value(pv);
}

Chasm_Carrier Chasm_Runtime::gen_carrier(Chasm_Typed_Value_Representation& tvr)
{
 Chasm_Type_Object* cto = tvr.type_object;

 // just until the full reg is set up ...

 if(cto->name() == "QString")
 {
  return gen_carrier<QString>(&tvr.rep);
 }

 if(cto->name() == "QVariant")
 {
  QString typ = tvr.rep.left(4);
  QString rep = tvr.rep.mid(4);
  QVariant r;
  if(typ == "url:")
    r = QUrl(tvr.rep);
  else if(typ == "int:")
    r = tvr.rep.toInt();
  else
    r = tvr.rep;
  return gen_carrier<QVariant>(&r);
 }

 if(cto->name() == "u1")
 {
  u1 arg = tvr.rep.toUInt();
  return gen_carrier<u1>(&arg);
 }

 if(cto->name() == "n8")
 {
  n8 arg = tvr.rep.toULongLong();
  return gen_carrier<n8>(&arg);
 }

 if(cto->name() == "void*")
 {
  void* arg = (void*) tvr.raw_value;
  return gen_carrier<void*>(&arg);
 }

// if(cto->name() == "n8&!")
// {
//  return gen_shared_ref_carrier(tvr.raw_value);
//  //return gen_shared_ref_carrier(*(std::shared_ptr<n8>*) tvr.raw_value);
// }

 if(cto->name() == "n8&!")
 {
  return gen_shared_ref_carrier((std::shared_ptr<n8>*) tvr.raw_value);
  //return gen_shared_ref_carrier(*(std::shared_ptr<n8>*) tvr.raw_value);
 }

 if(cto->name() == "n8&")
 {
  return gen_carrier<n8&>((n8*) tvr.raw_value);
 }

 return gen_carrier<void*>(&tvr.raw_value);
}


void Chasm_Runtime::release(Chasm_Call_Package* ccp)
{
 QMapIterator<QString, Chasm_Channel*> it(ccp->channels());
 while(it.hasNext())
 {
  it.next();
  Chasm_Channel* ch = it.value();

  for(Chasm_Carrier cc : ch->carriers())
  {
   if(cc.key().type_flag() == 14)
   {
    std::shared_ptr<n8>* ss = cc.raw_value_as<std::shared_ptr<n8>*>();
    delete ss;
   }
  }
 }

}



Chasm_Carrier Chasm_Runtime::gen_carrier(QString type_name)
{
 trisym tri;
 tri.set_fcode(current_no_file_session_);
 tri.set_lcode(-(++gen_trisym_line_index_));
 tri.set_ccode(1);
 Chasm_Carrier result;
 result.set_key(tri);
 return result;
}

Chasm_Carrier Chasm_Runtime::gen_carrier(u1 type_flag)
{
 Chasm_Carrier result = gen_carrier();
 result.set_type_flag(type_flag);
 return result;
}


void Chasm_Runtime::init_no_file_session()
{
 current_no_file_session_ = ++gen_trisym_file_index_;
}


Chasm_Call_Package* Chasm_Runtime::new_call_package()
{
 ++call_package_index_;

 Chasm_Call_Package* result = new Chasm_Call_Package(call_package_index_);
 current_call_packages_.push(result);
 return result;
}


void Chasm_Runtime::evaluate_3_re0(Chasm_Call_Package* ccp, u2 fncode, minimal_fn_s0_re0_type fn)
{
#include "./dev/consoles/fns/s0/a3/ch-eval-s0_3_re0.cpp"
}

void Chasm_Runtime::evaluate_3_re1(Chasm_Call_Package* ccp,
 u2 fncode, minimal_fn_s0_re1_type fn, Chasm_Carrier* rcar)
{
#include "./dev/consoles/fns/s0/a3/ch-eval-s0_3_re1.cpp"
}


void Chasm_Runtime::evaluate_3_re2(Chasm_Call_Package* ccp,
 u2 fncode, minimal_fn_s0_re2_type fn, Chasm_Carrier* rcar)
{
#include "./dev/consoles/fns/s0/a3/ch-eval-s0_3_re2.cpp"
}

void Chasm_Runtime::evaluate_3_re3(Chasm_Call_Package* ccp,
 u2 fncode, minimal_fn_s0_re3_type fn, Chasm_Carrier* rcar)
{
#include "./dev/consoles/fns/s0/a3/ch-eval-s0_3_re3.cpp"
}

void Chasm_Runtime::evaluate_3_re4(Chasm_Call_Package* ccp,
 u2 fncode, minimal_fn_s0_re4_type fn, Chasm_Carrier* rcar)
{
#include "./dev/consoles/fns/s0/a3/ch-eval-s0_3_re4.cpp"
}

void Chasm_Runtime::evaluate_3_re5(Chasm_Call_Package* ccp,
 u2 fncode, minimal_fn_s0_re5_type fn, Chasm_Carrier* rcar)
{
#include "./dev/consoles/fns/s0/a3/ch-eval-s0_3_re5.cpp"
}

void Chasm_Runtime::evaluate_3_re6(Chasm_Call_Package* ccp,
 u2 fncode, minimal_fn_s0_re6_type fn, Chasm_Carrier* rcar)
{
#include "./dev/consoles/fns/s0/a3/ch-eval-s0_3_re6.cpp"
}

void Chasm_Runtime::evaluate_3_re7(Chasm_Call_Package* ccp,
 u2 fncode, minimal_fn_s0_re7_type fn, Chasm_Carrier* rcar)
{
#include "./dev/consoles/fns/s0/a3/ch-eval-s0_3_re7.cpp"
}

void Chasm_Runtime::evaluate_3_re8(Chasm_Call_Package* ccp,
 u2 fncode, minimal_fn_s0_re8_type fn, Chasm_Carrier* rcar)
{
#include "./dev/consoles/fns/s0/a3/ch-eval-s0_3_re8.cpp"
}

void Chasm_Runtime::evaluate_3_re9(Chasm_Call_Package* ccp,
 u2 fncode, minimal_fn_s0_re9_type fn, Chasm_Carrier* rcar)
{
#include "./dev/consoles/fns/s0/a3/ch-eval-s0_3_re9.cpp"
}



void Chasm_Runtime::evaluate_2_re0(Chasm_Call_Package* ccp, u2 fncode, minimal_fn_s0_re0_type fn)
{
#include "./dev/consoles/fns/s0/a2/ch-eval-s0_2_re0.cpp"
}

void Chasm_Runtime::evaluate_2_re1(Chasm_Call_Package* ccp,
 u2 fncode, minimal_fn_s0_re1_type fn, Chasm_Carrier* rcar)
{
#include "./dev/consoles/fns/s0/a2/ch-eval-s0_2_re1.cpp"
}

void Chasm_Runtime::evaluate_2_re2(Chasm_Call_Package* ccp,
 u2 fncode, minimal_fn_s0_re2_type fn, Chasm_Carrier* rcar)
{
#include "./dev/consoles/fns/s0/a2/ch-eval-s0_2_re2.cpp"
}

void Chasm_Runtime::evaluate_2_re3(Chasm_Call_Package* ccp,
 u2 fncode, minimal_fn_s0_re3_type fn, Chasm_Carrier* rcar)
{
#include "./dev/consoles/fns/s0/a2/ch-eval-s0_2_re3.cpp"
}

void Chasm_Runtime::evaluate_2_re4(Chasm_Call_Package* ccp,
 u2 fncode, minimal_fn_s0_re4_type fn, Chasm_Carrier* rcar)
{
#include "./dev/consoles/fns/s0/a2/ch-eval-s0_2_re4.cpp"
}

void Chasm_Runtime::evaluate_2_re5(Chasm_Call_Package* ccp,
 u2 fncode, minimal_fn_s0_re5_type fn, Chasm_Carrier* rcar)
{
#include "./dev/consoles/fns/s0/a2/ch-eval-s0_2_re5.cpp"
}

void Chasm_Runtime::evaluate_2_re6(Chasm_Call_Package* ccp,
 u2 fncode, minimal_fn_s0_re6_type fn, Chasm_Carrier* rcar)
{
#include "./dev/consoles/fns/s0/a2/ch-eval-s0_2_re6.cpp"
}

void Chasm_Runtime::evaluate_2_re7(Chasm_Call_Package* ccp,
 u2 fncode, minimal_fn_s0_re7_type fn, Chasm_Carrier* rcar)
{
#include "./dev/consoles/fns/s0/a2/ch-eval-s0_2_re7.cpp"
}

void Chasm_Runtime::evaluate_2_re8(Chasm_Call_Package* ccp,
 u2 fncode, minimal_fn_s0_re8_type fn, Chasm_Carrier* rcar)
{
#include "./dev/consoles/fns/s0/a2/ch-eval-s0_2_re8.cpp"
}

void Chasm_Runtime::evaluate_2_re9(Chasm_Call_Package* ccp,
 u2 fncode, minimal_fn_s0_re9_type fn, Chasm_Carrier* rcar)
{
#include "./dev/consoles/fns/s0/a2/ch-eval-s0_2_re9.cpp"
}


void Chasm_Runtime::evaluate_1_re0(Chasm_Call_Package* ccp, u2 fncode, minimal_fn_s0_re0_type fn)
{
#include "./dev/consoles/fns/s0/a1/ch-eval-s0_1_re0.cpp"
}

void Chasm_Runtime::evaluate_1_re1(Chasm_Call_Package* ccp,
 u2 fncode, minimal_fn_s0_re1_type fn, Chasm_Carrier* rcar)
{
#include "./dev/consoles/fns/s0/a1/ch-eval-s0_1_re1.cpp"
}

void Chasm_Runtime::evaluate_1_re2(Chasm_Call_Package* ccp,
 u2 fncode, minimal_fn_s0_re2_type fn, Chasm_Carrier* rcar)
{
#include "./dev/consoles/fns/s0/a1/ch-eval-s0_1_re2.cpp"
}

void Chasm_Runtime::evaluate_1_re3(Chasm_Call_Package* ccp,
 u2 fncode, minimal_fn_s0_re3_type fn, Chasm_Carrier* rcar)
{
#include "./dev/consoles/fns/s0/a1/ch-eval-s0_1_re3.cpp"
}

void Chasm_Runtime::evaluate_1_re4(Chasm_Call_Package* ccp,
 u2 fncode, minimal_fn_s0_re4_type fn, Chasm_Carrier* rcar)
{
#include "./dev/consoles/fns/s0/a1/ch-eval-s0_1_re4.cpp"
}

void Chasm_Runtime::evaluate_1_re5(Chasm_Call_Package* ccp,
 u2 fncode, minimal_fn_s0_re5_type fn, Chasm_Carrier* rcar)
{
#include "./dev/consoles/fns/s0/a1/ch-eval-s0_1_re5.cpp"
}

void Chasm_Runtime::evaluate_1_re6(Chasm_Call_Package* ccp,
 u2 fncode, minimal_fn_s0_re6_type fn, Chasm_Carrier* rcar)
{
#include "./dev/consoles/fns/s0/a1/ch-eval-s0_1_re6.cpp"
}

void Chasm_Runtime::evaluate_1_re7(Chasm_Call_Package* ccp,
 u2 fncode, minimal_fn_s0_re7_type fn, Chasm_Carrier* rcar)
{
#include "./dev/consoles/fns/s0/a1/ch-eval-s0_1_re7.cpp"
}

void Chasm_Runtime::evaluate_1_re8(Chasm_Call_Package* ccp,
 u2 fncode, minimal_fn_s0_re8_type fn, Chasm_Carrier* rcar)
{
#include "./dev/consoles/fns/s0/a1/ch-eval-s0_1_re8.cpp"
}

void Chasm_Runtime::evaluate_1_re9(Chasm_Call_Package* ccp,
 u2 fncode, minimal_fn_s0_re9_type fn, Chasm_Carrier* rcar)
{
#include "./dev/consoles/fns/s0/a1/ch-eval-s0_1_re9.cpp"
}



void Chasm_Runtime::evaluate_0_re0(Chasm_Call_Package* ccp,
  u2 fncode, minimal_fn_s0_re0_type fn,
  minimal_fn_s1_re0_type sfn)
{
#include "./dev/consoles/fns/s0/a0/ch-eval-s0_0_re0.cpp"
}

void Chasm_Runtime::evaluate_0_re1(Chasm_Call_Package* ccp,
 u2 fncode, minimal_fn_s0_re1_type fn, Chasm_Carrier* rcar)
{
#include "./dev/consoles/fns/s0/a0/ch-eval-s0_0_re1.cpp"
}

void Chasm_Runtime::evaluate_0_re2(Chasm_Call_Package* ccp,
 u2 fncode, minimal_fn_s0_re2_type fn, Chasm_Carrier* rcar)
{
#include "./dev/consoles/fns/s0/a0/ch-eval-s0_0_re2.cpp"
}

void Chasm_Runtime::evaluate_0_re3(Chasm_Call_Package* ccp,
 u2 fncode, minimal_fn_s0_re3_type fn, Chasm_Carrier* rcar)
{
#include "./dev/consoles/fns/s0/a0/ch-eval-s0_0_re3.cpp"
}

void Chasm_Runtime::evaluate_0_re4(Chasm_Call_Package* ccp,
 u2 fncode, minimal_fn_s0_re4_type fn, Chasm_Carrier* rcar)
{
#include "./dev/consoles/fns/s0/a0/ch-eval-s0_0_re4.cpp"
}

void Chasm_Runtime::evaluate_0_re5(Chasm_Call_Package* ccp,
 u2 fncode, minimal_fn_s0_re5_type fn, Chasm_Carrier* rcar)
{
#include "./dev/consoles/fns/s0/a0/ch-eval-s0_0_re5.cpp"
}

void Chasm_Runtime::evaluate_0_re6(Chasm_Call_Package* ccp,
 u2 fncode, minimal_fn_s0_re6_type fn, Chasm_Carrier* rcar)
{
#include "./dev/consoles/fns/s0/a0/ch-eval-s0_0_re6.cpp"
}

void Chasm_Runtime::evaluate_0_re7(Chasm_Call_Package* ccp,
 u2 fncode, minimal_fn_s0_re7_type fn, Chasm_Carrier* rcar)
{
#include "./dev/consoles/fns/s0/a0/ch-eval-s0_0_re7.cpp"
}

void Chasm_Runtime::evaluate_0_re8(Chasm_Call_Package* ccp,
 u2 fncode, minimal_fn_s0_re8_type fn, Chasm_Carrier* rcar)
{
#include "./dev/consoles/fns/s0/a0/ch-eval-s0_0_re8.cpp"
}

void Chasm_Runtime::evaluate_0_re9(Chasm_Call_Package* ccp,
 u2 fncode, minimal_fn_s0_re9_type fn,
 minimal_fn_s1_re9_type sfn, Chasm_Carrier* rcar)
{
#include "./dev/consoles/fns/s0/a0/ch-eval-s0_0_re9.cpp"
}

