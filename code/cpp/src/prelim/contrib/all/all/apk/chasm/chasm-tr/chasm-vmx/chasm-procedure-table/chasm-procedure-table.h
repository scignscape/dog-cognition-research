
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef CHASM_PROCEDURE_TABLE__H
#define CHASM_PROCEDURE_TABLE__H

#include <QString>

#include <QStack>
#include <QVariant>
#include <QQueue>
#include <deque>

#include <QDebug>

#include "chasm/chasm-carrier.h"

#include "accessors.h"
#include "flags.h"

#include "global-types.h"
#include "kans.h"

#include "chasm/chasm-runtime.h"

#include "chasm/chasm-value-expression.h"

#define register_s0(proc ,code) register_procedure_s0(#proc, (void(*)()) &proc, #code)
#define register_s1(proc ,code) register_procedure_s1(#proc, (void(_min_::*)()) &proc, #code)



class Chasm_Call_Package;
class Chasm_Type_Object;
class CSM_Ghost_Scope;

typedef void(*_minimal_fn_s0_type)();
typedef void(_min_::*_minimal_fn_s1_type)();
union _minimal_fn_type { _minimal_fn_s0_type s0; _minimal_fn_s1_type s1; };

typedef QPair<Chasm_Function_Code, Chasm_Function_Code> CFC_Pair;

class Chasm_Procedure_Table
{
 Chasm_Type_Object* type_object_ref_;
 Chasm_Type_Object* type_object_u1_;
 Chasm_Type_Object* type_object_u2_;
 Chasm_Type_Object* type_object_QString_;
 Chasm_Type_Object* type_object_u4_;
 Chasm_Type_Object* type_object_QByteArray_;
 Chasm_Type_Object* type_object_r8_;
 Chasm_Type_Object* type_object_QVariant_;
 Chasm_Type_Object* type_object_n8_;
 Chasm_Type_Object* type_object_ptr_;
 Chasm_Type_Object* type_object_qsl_;

 QMap<QString, QString> procedure_name_resolutions_;
 QMap<QString, QPair<CFC_Pair, _minimal_fn_type>> registered_procedures_;

public:

 Chasm_Procedure_Table(Chasm_Runtime* csr);

 ACCESSORS__RGET(MACRO_PASTE(QMap<QString, QString>) ,procedure_name_resolutions)
 ACCESSORS__RGET(MACRO_PASTE(QMap<QString, QPair<CFC_Pair, _minimal_fn_type>>) ,registered_procedures)


 ACCESSORS__GET(Chasm_Type_Object* ,type_object_ref)
 ACCESSORS__GET(Chasm_Type_Object* ,type_object_u1)
 ACCESSORS__GET(Chasm_Type_Object* ,type_object_u2)
 ACCESSORS__GET(Chasm_Type_Object* ,type_object_QString)
 ACCESSORS__GET(Chasm_Type_Object* ,type_object_u4)
 ACCESSORS__GET(Chasm_Type_Object* ,type_object_QByteArray)
 ACCESSORS__GET(Chasm_Type_Object* ,type_object_r8)
 ACCESSORS__GET(Chasm_Type_Object* ,type_object_QVariant)
 ACCESSORS__GET(Chasm_Type_Object* ,type_object_n8)
 ACCESSORS__GET(Chasm_Type_Object* ,type_object_ptr)
 ACCESSORS__GET(Chasm_Type_Object* ,type_object_qsl)

// void register_procedure_s0(QString name,
//   _minimal_fn_s0_type fn, u4 proc);

 void register_procedure_s0(QString name,
   _minimal_fn_s0_type fn, QString code);

 void register_procedure_s1(QString name,
   _minimal_fn_s1_type sfn, QString code);

 CFC_Pair find_procedure(QString name,
   _minimal_fn_s0_type& s0, _minimal_fn_s1_type& s1);

 QVector<Chasm_Value_Expression> parse_expressions(QString reps);

 Chasm_Value_Expression read_value_expression(QString rep);
 Chasm_Value_Expression read_value_expression(QString type_string, QString rep);


};

// _KANS(GTagML)

#endif // CHASM_PROCEDURE_TABLE__H
