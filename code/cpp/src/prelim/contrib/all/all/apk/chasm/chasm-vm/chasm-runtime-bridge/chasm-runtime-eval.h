
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef CHASM_RUNTIME_EVAL__H
#define CHASM_RUNTIME_EVAL__H

#include <QString>

#include <QStack>
#include <QVariant>
#include <QQueue>
#include <deque>

#include <QDebug>

#include "chasm-lib/chasm/chasm-carrier.h"

#include "accessors.h"
#include "flags.h"

#include "global-types.h"
#include "kans.h"

#include "chasm-lib/chasm/chasm-runtime.h"

//#define register_s0(proc ,code) register_procedure_s0(#proc, (void(*)()) &proc, #code)
//#define register_s1(proc ,code) register_procedure_s1(#proc, (void(_min_::*)()) &proc, #code)

#include "chasm-procedure-table/chasm-procedure-table.h"
#include "chasm-lib/chasm/chasm-value-expression.h"

class Chasm_Call_Package;
class Chasm_Type_Object;
class CSM_Ghost_Scope;


//typedef void(*_minimal_fn_s0_type)();
//typedef void(_min_::*_minimal_fn_s1_type)();
//union _minimal_fn_type { _minimal_fn_s0_type s0; _minimal_fn_s1_type s1; };

class Chasm_Runtime_Eval
{
 Chasm_Runtime* csr_;

// Chasm_Type_Object* type_object_ref_;
// Chasm_Type_Object* type_object_u1_;
// Chasm_Type_Object* type_object_u2_;
// Chasm_Type_Object* type_object_QString_;
// Chasm_Type_Object* type_object_u4_;
// Chasm_Type_Object* type_object_QByteArray_;
// Chasm_Type_Object* type_object_r8_;
// Chasm_Type_Object* type_object_QVariant_;
// Chasm_Type_Object* type_object_n8_;
// Chasm_Type_Object* type_object_ptr_;

 Chasm_Procedure_Table* proctable_;

 struct call_s0_package
 {
  Chasm_Runtime_Eval* _this;
  QString arg;
  operator Chasm_Carrier()
  {
   return _this->_call_s0(arg);
  }
  Chasm_Carrier operator()(QString name, QString args = {})
  {
   //return _this->_call_s0(name, arg, args);
  }
  Chasm_Carrier operator()(QString name, QVector<Chasm_Value_Expression> args)
  {
   return _this->_call_s01(name, arg, args);
  }

  template<typename... Args>
  Chasm_Carrier operator()(QString name, Args... args)
  {
   return _this->_call_s0(name, arg, {args...});
  }
 };

 void init_carrier(Chasm_Carrier& cc, Chasm_Value_Expression cvx);


public:

 ACCESSORS(Chasm_Procedure_Table* ,proctable)

 Chasm_Runtime_Eval(Chasm_Runtime* csr);

 Chasm_Carrier call_s1(void* obj, QString name);

 call_s0_package call_s0(QString ret_channel_name)
 {
  return {this, ret_channel_name};
 }

 Chasm_Carrier call_s0(QString name, QString args_rep);

 template<typename... Args>
 Chasm_Carrier call_s0(QString name, Args... args)
 {
  return _call_s0(name, {args...});
 }


 Chasm_Carrier _call_s01(QString name, QString ret_channel_name, QVector<Chasm_Value_Expression> args);

 Chasm_Carrier _call_s0(QString name);

 Chasm_Carrier _call_s0(QString name, QVector<void*> args)
 {
  return _call_s0(name, "retvalue", args);
 }

 Chasm_Carrier _call_s0(QString name, QString ret_channel_name, QVector<void*> args);

// Chasm_Carrier call_s0(QString name, QString ret_channel_name, );

};

//template<>
//inline Chasm_Carrier Chasm_Runtime_Eval::call_s0_package::operator()(QString name, void* args ...)
//{
// return _this->_call_s0(name, {args});
//}


// _KANS(GTagML)

#endif // CHASM_RUNTIME_EVAL__H
