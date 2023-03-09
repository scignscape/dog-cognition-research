
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef GT_MODULE_IR__H
#define GT_MODULE_IR__H

#include <QString>
#include <QMap>
#include <QMultiMap>
#include <QStack>

#include <functional>

#include "accessors.h"
#include "global-types.h"

#include "kans.h"


KANS_(DGH)

class DGH_Module_Interpreter;
class GTagML_DGH_Module;

class GT_Module_IR
{
 typedef void(DGH_Module_Interpreter::*fn0_t)();
 typedef void(DGH_Module_Interpreter::*fn1_t)(QString);

 typedef union {fn0_t fn0; fn1_t fn1;} fn_u;

 struct line_op_info
 {
  void* module;
  QString* cmd;
  fn_u fn;
 };

 QMap<QString, QList<line_op_info>> line_ops_;

 GTagML_DGH_Module* gtagml_module_;

 QString current_proc_name_;

 std::function<void(QString&)> line_translate_fn_;
 std::function<void(QString&)> cmd_translate_fn_;

public:

 GT_Module_IR();

 ACCESSORS(std::function<void(QString&)> ,line_translate_fn)
 ACCESSORS(std::function<void(QString&)> ,cmd_translate_fn)

 static QString first_non_flag_arg(const QStringList& qsl, QVector<QChar>& firsts,
   QMap<QString, u1>* flagset = nullptr, QMap<QString, QString>* flagpairs = nullptr);
 static QString first_non_flag_arg(const QStringList& qsl, QString firsts,
   QMap<QString, u1>* flagset = nullptr, QMap<QString, QString>* flagpairs = nullptr);
 static QString first_non_flag_arg(const QStringList& qsl,
   QMap<QString, u1>* flagset = nullptr, QMap<QString, QString>* flagpairs = nullptr);


 void read_line(QString inst);
 void read_line(QString inst, QString arg);
 void parse_fn_line(QString line);

 void read_lines(QString lines);

 void run_lines(QString proc_name = {});

 void check_translate_line(QString& l);
 void check_translate_cmd(QString& c);


};

_KANS(DGH)

#endif // GT_MODULE_IR__H
