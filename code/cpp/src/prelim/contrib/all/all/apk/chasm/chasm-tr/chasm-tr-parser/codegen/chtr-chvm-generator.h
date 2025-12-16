
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef ChTR_CHVM_GENERATOR__H
#define ChTR_CHVM_GENERATOR__H



#include "flags.h"

#include "accessors.h"

#include "global-types.h"

#include "grammar/chtr-parse-context.h"

#include "kernel/graph/chtr-graph.h"

#include "types/chtr-type-system.h"

#include <QStack>


#include "aqns.h"
AQNS_(Chasm_TR)

class ChTR_Graph;
class ChTR_Node;
class ChTR_Node_Factory;


class ChTR_Document;
class ChTR_Parser;
class ChTR_Graph;
class ChTR_Relae_Frame;
class ChTR_Relae_Query;


class ChTR_Source_Type;
class ChTR_Source_File;

class ChTR_Channel_Package;
class ChTR_Channel_Object;
class ChTR_Code_Statement;

class ChTR_CHVM_Line;

class ChTR_CHVM_Generator
{

 QString acc_;

 QTextStream acc_stream_;

 QStringList held_preambles_;

 QString current_subroutine_name_;

 QStringList known_subroutine_names_;


 QMap<QString, QVector<ChTR_CHVM_Line*>> acc_lines_;

 void check_register_current_subroutine_name();

public:

 ChTR_CHVM_Generator();

 ACCESSORS(QMap<QString, QVector<ChTR_CHVM_Line*>> ,acc_lines)

 void chvm_code(QString& result);

 ChTR_CHVM_Generator& preamble(QString p)
 {
  held_preambles_.push_back(p);
  return *this;
 }

 ChTR_CHVM_Generator& preamble_comment(QString p)
 {
  return preamble(" .; "_qt + p + " ;.\n");
 }

 void statement_line();
 void statement_line(QString* ln);
 QString statement_line(QString ln);

 ChTR_CHVM_Generator& cut();
 ChTR_CHVM_Generator& blank();

 ChTR_CHVM_Generator& dissolve(QVector<QString> new_lines);

 template<typename TEXT_Type>
 friend ChTR_CHVM_Generator& operator << (ChTR_CHVM_Generator& lhs, TEXT_Type rhs)
 {
  lhs.acc_stream_ << rhs;
  return lhs;
 }



};

_AQNS(Chasm_TR)

#endif //  ChTR_CHVM_GENERATOR

