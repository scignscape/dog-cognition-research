
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef CHVM_LEXICAL_SCOPE__H
#define CHVM_LEXICAL_SCOPE__H

#include <QString>

#include <QStack>
#include <QVariant>

#include <QDebug>

#include "chasm-lib/chasm/chasm-carrier.h"


#include "accessors.h"
#include "flags.h"

#include "global-types.h"
#include "kans.h"


class Chasm_Runtime;

class Chasm_Runtime_Bridge;

class Chasm_Type_Object;

class CHVM_Lexical_Scope
{
//? QVector<Chasm_Carrier> carriers_;

 CHVM_Lexical_Scope* parent_scope_;

 QMap<QString, Chasm_Type_Object*> type_objects_;

 QMap<QString, n8> values_;
 QStringList string_values_;

public:

 CHVM_Lexical_Scope(CHVM_Lexical_Scope* parent_scope = nullptr);

// void add_carrier(const Chasm_Carrier& cc);
// void clear_carrier(Chasm_Carrier& cc);
// void clear_all();

 void register_symbol(QString symbol, Chasm_Type_Object* cto);

 Chasm_Type_Object* type_object_for_symbol(QString symbol);

 void register_value(QString symbol, n8 value);
 n8 retrieve_value(QString symbol);

 void register_string_value(QString symbol, QString value);
 QString retrieve_string_value(QString symbol);

 template<typename V_Type>
 V_Type retrieve(QString symbol)
 {
  return (V_Type)(values_[symbol]);
 }

// ACCESSORS__GET(QString ,last_source_proc_name)


};

// _KANS(GTagML)

#endif // CHVM_LEXICAL_SCOPE__H
