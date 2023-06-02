
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef CHASM_RUNTIME__H
#define CHASM_RUNTIME__H

#include <QString>

#include <QStack>
#include <QVariant>

#include <QDebug>

#define  UNEXPECTED_PRETYPE_PATTERN \
 qDebug() << "Unexpected pretype pattern; evaluation impossible";

#define UNEXPECTED_CONVENTION_CODE \
 qDebug()  << "Unexpected convention code; evaluation impossible";


#include "accessors.h"
#include "flags.h"

#include "global-types.h"

#include <functional>

#include <QString>
#include <QVariant>
#include <QByteArray>

#include "kans.h"

#include "chasm-carrier.h"

#include "types/chasm-type-system.h"


struct _min_{};

class Chasm_Call_Package;
class Chasm_Type_Object;

struct Chasm_Typed_Value_Representation
{
 Chasm_Type_Object* type_object;
 n8 raw_value;
 QString rep;
};

struct Chasm_Function_Code
{
 u1 arg_count;
 u1 convention;
 u1 return_code;
 u2 distinct_pretype_pattern;
 s2 pretype_pattern;
 u1 pretype_pattern_binary;

 u2 invalid()
 {
  if((distinct_pretype_pattern % 100) == 0)
    return distinct_pretype_pattern;
  return 0;
 }
 static Chasm_Function_Code _invalid()
 {
  return {0,0,0,100,0,0};
 }
 static QPair<Chasm_Function_Code, Chasm_Function_Code> _invalid_pair()
 {
  return {_invalid(), _invalid()};
 }

 n8 collapsed(n8 cue);
};

QPair<Chasm_Function_Code, Chasm_Function_Code> operator""_cfc(n8 cue);

inline QPair<Chasm_Function_Code, Chasm_Function_Code> _cfc(n8 cue)
{
 return operator""_cfc(cue);
}

//Chasm_Function_Code operator""_cfc(n8 cue);
//inline Chasm_Function_Code _cfc(n8 cue)
//{
// return operator""_cfc(cue);
//}

extern void _evaluate_s01_3of3(Chasm_Call_Package* ccp, Chasm_Function_Code fncode,
  void(*fn)(), void(_min_::*sfn)(), Chasm_Carrier* rcar);

extern void _evaluate_s01_4of3(Chasm_Call_Package* ccp, Chasm_Function_Code fncode,
  void(*fn)(), void(_min_::*sfn)(), Chasm_Carrier* rcar);

extern void _evaluate_s01_Xof1(Chasm_Call_Package* ccp, Chasm_Function_Code fncode,
  void(*fn)(), void(_min_::*sfn)(), Chasm_Carrier* rcar);

extern void _evaluate_s01_Xof2(Chasm_Call_Package* ccp, Chasm_Function_Code fncode,
  void(*fn)(), void(_min_::*sfn)(), Chasm_Carrier* rcar);

void _evaluate_s01_0_rX(Chasm_Call_Package* ccp, Chasm_Function_Code fncode,
  void(*fn)(), void(_min_::*sfn)(), Chasm_Carrier* rcar);


class Chasm_Runtime
{
 //QString text_;

 struct _Retvalue
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

  _Retvalue() : _ref(new n8(0)), _u1(new u1(0)), _u2(new u2(0)),
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

 Chasm_Type_System type_system_;

public:

 Chasm_Runtime();

 ACCESSORS__RGET(Chasm_Type_System ,type_system)

 QVector<Chasm_Type_Object*>* pretype_type_objects()
 {
  return type_system_.pretype_type_objects();
 }

 _Retvalue Retvalue;

 Chasm_Type_Object* register_type_object(QString name, u2 pos1code, u2 pos2code,
   u2 pos3code, u2 pos4code);

 Chasm_Type_Object* get_type_object_by_name(QString name);

 Chasm_Call_Package* new_call_package();

 Chasm_Carrier gen_carrier(Chasm_Typed_Value_Representation& tvr);
 Chasm_Carrier gen_carrier(QString type_name = {});
 Chasm_Carrier gen_carrier(u1 type_flag);
 Chasm_Carrier gen_carrier(u1 type_flag, QString rep);

 Chasm_Carrier gen_shared_ref_carrier(std::shared_ptr<n8>* ss);

 template<typename CARRIER_Type>
 inline Chasm_Carrier gen_carrier();

 template<typename CARRIER_Type>
 inline Chasm_Carrier gen_carrier(void* value);

 Chasm_Carrier gen_carrier_by_type_object(Chasm_Type_Object* cto);
 Chasm_Carrier gen_carrier_by_type_object(Chasm_Type_Object* cto, void* pv);


 void init_no_file_session();

 void release(Chasm_Call_Package* ccp);


 template<typename RETURN_Type, typename CLASS_Type>
 void evaluate(Chasm_Call_Package* ccp, QPair<Chasm_Function_Code, Chasm_Function_Code> fncodes,
   RETURN_Type (CLASS_Type::*sfn), Chasm_Carrier* rcar = nullptr)
 {
  //
  Chasm_Function_Code  fncode = fncodes.second;
  //Chasm_Function_Code fncode = fncodes.first;

  if(fncode.convention != 1)
    UNEXPECTED_CONVENTION_CODE

  if(fncode.distinct_pretype_pattern < 10)
  {
   if(fncode.arg_count == 0)
     _evaluate_s01_0_rX(ccp, fncode, nullptr, (void(_min_::*)()) sfn, rcar);
   else
     _evaluate_s01_Xof1(ccp, fncode, nullptr, (void(_min_::*)()) sfn, rcar);
  }
  else if(fncode.distinct_pretype_pattern < 100)
    UNEXPECTED_PRETYPE_PATTERN
  else if(fncode.distinct_pretype_pattern < 1000)
    _evaluate_s01_Xof2(ccp, fncode, nullptr, (void(_min_::*)()) sfn, rcar);
  else if(fncode.arg_count == 3)
    _evaluate_s01_3of3(ccp, fncode, nullptr, (void(_min_::*)()) sfn, rcar);
  else if(fncode.arg_count == 4)
    _evaluate_s01_4of3(ccp, fncode, nullptr, (void(_min_::*)()) sfn, rcar);
 }


 template<typename FN_Type>
 void evaluate(Chasm_Call_Package* ccp, QPair<Chasm_Function_Code, Chasm_Function_Code> fncodes,
   FN_Type fn, Chasm_Carrier* rcar = nullptr)
 {
  //
  Chasm_Function_Code fncode = fncodes.second;
  //Chasm_Function_Code fncode = fncodes.first;

  if(fncode.convention != 0)
    UNEXPECTED_CONVENTION_CODE
  else if(fncode.distinct_pretype_pattern < 10)
  {
   if(fncode.arg_count == 0)
     _evaluate_s01_0_rX(ccp, fncode, (void(*)()) fn, nullptr, rcar);
   else
     _evaluate_s01_Xof1(ccp, fncode, (void(*)()) fn, nullptr, rcar);
  }
  else if(fncode.distinct_pretype_pattern < 100)
    UNEXPECTED_PRETYPE_PATTERN
  else if(fncode.distinct_pretype_pattern < 1000)
    _evaluate_s01_Xof2(ccp, fncode, (void(*)()) fn, nullptr, rcar);
  else if(fncode.arg_count == 3)
   // // 3 args ...
    _evaluate_s01_3of3(ccp, fncode, (void(*)()) fn, nullptr, rcar);
  else if(fncode.arg_count == 4)
   // // 4 args ...
    _evaluate_s01_4of3(ccp, fncode, (void(*)()) fn, nullptr, rcar);
 }
};

// _KANS(GTagML)

#endif // CHASM_RUNTIME__H
