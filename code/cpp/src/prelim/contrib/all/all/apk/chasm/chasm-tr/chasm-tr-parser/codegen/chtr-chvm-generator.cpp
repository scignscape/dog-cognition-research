
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "chtr-chvm-generator.h"

//#include "


#include <QMap>

#include "global-types.h"

#include "chtr-chvm-line.h"


USING_AQNS(Chasm_TR)


ChTR_CHVM_Generator::ChTR_CHVM_Generator()
  :  acc_stream_(&acc_)
{
 current_subroutine_name_ = "--sf--";
 check_register_current_subroutine_name();
}

void ChTR_CHVM_Generator::chvm_code(QString& result)
{
 for(QString sn : known_subroutine_names_)
 {
  result += "\n\n";
  for(auto ccl : acc_lines_[sn])
  {
   result += ccl->get_text() + "\n";
  }
 }
}

void ChTR_CHVM_Generator::check_register_current_subroutine_name()
{
 auto& lines = acc_lines_[current_subroutine_name_];

 if(lines.isEmpty())
 {
//  ChTR_CHVM_Line* ccl = new ChTR_CHVM_Line(0, "@fn %1 ;."_qt.arg(current_subroutine_name_));
//  lines.push_back(ccl);

  dissolve({"@fn %1"_qt.arg(current_subroutine_name_)});

  known_subroutine_names_.push_back(current_subroutine_name_);
 }
}

ChTR_CHVM_Generator& ChTR_CHVM_Generator::dissolve(QVector<QString> new_lines)
{
 for (QString line : new_lines)
 {
  acc_stream_ << line; cut();
//  acc_stream_ << statement_line(line); cut();
 }
 return *this;
}

ChTR_CHVM_Generator& ChTR_CHVM_Generator::blank()
{
 preamble("\n");
 return *this;
}

ChTR_CHVM_Generator& ChTR_CHVM_Generator::cut()
{
//?acc << " ;.";
 statement_line();

 auto& acc_lines = acc_lines_[current_subroutine_name_];

 u4 ln = acc_lines.size() + 1;

 ChTR_CHVM_Line* ccl = new ChTR_CHVM_Line(ln, acc_);

 if(!held_preambles_.isEmpty())
 {
  ccl->pre(held_preambles_);
  held_preambles_.clear();
 }

 acc_.clear();

 acc_lines.push_back(ccl);

 return *this;
}

void ChTR_CHVM_Generator::statement_line()
{
 statement_line(&acc_);
}


void ChTR_CHVM_Generator::statement_line(QString* ln)
{
 *ln += " ;.";
}

QString ChTR_CHVM_Generator::statement_line(QString ln)
{
 return ln + " ;.";
}


