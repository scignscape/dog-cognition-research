
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "chvm-lexical-scope.h"

#include "chasm-lib/chasm/types/chasm-type-object.h"

#include "textio.h"
USING_KANS(TextIO)

#include <QString>
#include <QVariant>
#include <QByteArray>

#include <QUrl>

#include <QPoint>


CHVM_Lexical_Scope::CHVM_Lexical_Scope(CHVM_Lexical_Scope* parent_scope)
  :  parent_scope_(parent_scope)
{

}

void CHVM_Lexical_Scope::register_symbol(QString symbol, Chasm_Type_Object* cto)
{
 type_objects_[symbol] = cto;
}


n8 CHVM_Lexical_Scope::retrieve_value(QString symbol)
{
 auto it = values_.find(symbol);
 if(it == values_.end())
   return parent_scope_->retrieve_value(symbol);
 return *it;
}

void CHVM_Lexical_Scope::register_value(QString symbol, n8 value)
{
 values_[symbol] = value;
}

void CHVM_Lexical_Scope::register_string_value(QString symbol, QString value)
{
 register_value(symbol, string_values_.size());
 string_values_.push_back(value);
}

QString CHVM_Lexical_Scope::retrieve_string_value(QString symbol)
{
 s4 v = retrieve<s4>(symbol);
 return string_values_[v];
}

Chasm_Type_Object* CHVM_Lexical_Scope::type_object_for_symbol(QString symbol)
{
 auto it = type_objects_.find(symbol);
 if(it == type_objects_.end())
   return parent_scope_->type_object_for_symbol(symbol);
 return *it;
}

//void CHVM_Lexical_Scope::add_carrier(const Chasm_Carrier& cc)
//{
// carriers_.push_back(cc);
//}

//void CHVM_Lexical_Scope::clear_carrier(Chasm_Carrier& cc)
//{
// u1 tf = cc.key().type_flag();
// switch(tf)
// {
// case 3: delete (QString*) cc.raw_value(); break;
// case 5: delete (QByteArray*) cc.raw_value(); break;
// case 7: delete (QVariant*) cc.raw_value(); break;

// default: break;
// }
//}

//void CHVM_Lexical_Scope::clear_all()
//{
// for(Chasm_Carrier& cc : carriers_)
// {
//  clear_carrier(cc);
// }
//}
