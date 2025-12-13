
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef CHASM_VM__H
#define CHASM_VM__H

#include <QString>

#include <QStack>
#include <QVariant>

#include <QDebug>



#include "accessors.h"
#include "flags.h"

#include "global-types.h"
#include "kans.h"


class Chasm_Runtime;

class Chasm_Runtime_Bridge;


class Chasm_VM
{
 Chasm_Runtime_Bridge* crb_;
 u4 gen_source_proc_name_count_;
 QString current_source_proc_name_;
 QString last_source_proc_name_;

 typedef union {void(Chasm_Runtime_Bridge::*fn0)(); void(Chasm_Runtime_Bridge::*fn1)(QString);} fn_u ;

 QMap<QString, QVector<QPair<QString*, fn_u>>> line_ops_;


public:

 Chasm_VM(Chasm_Runtime_Bridge* crb);

 ACCESSORS__GET(QString ,last_source_proc_name)

 void load_program(QString path);

 void read_line(QString inst);
 void read_line(QString inst, QString arg);

 void reread_substitute(QString& key);
 void parse_fn_line(QString line);



 QString gen_source_proc_name();
 QString _gen_source_proc_name();
 void run_lines(QString source_proc_name);
 void read_local_program(QString lines);

 void run_current_source_proc_name();


};

// _KANS(GTagML)

#endif // CHASM_VM__H
