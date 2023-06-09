

//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)



#include "chvm-code-statement-generator.h"

#include "kernel/graph/chtr-node.h"
#include "kernel/graph/chtr-graph.h"
#include "kernel/query/chtr-query.h"

#include "chtr-code-statement.h"

#include "chtr-channel-package.h"

#include "chtr-channel-object.h"

#include <QDebug>


USING_AQNS(Chasm_TR)


void ChVM_Code_Statement_Generator::statement_line(QString* ln)
{
 *ln += " ;.\n";
}

QString ChVM_Code_Statement_Generator::statement_line(QString ln)
{
 return ln + " ;.\n";
}


QString ChVM_Code_Statement_Generator::load_symbol(QString symbol_string)
{
 static QString line = "load_symbol $ %1";
 return line.arg(symbol_string);
}

QString ChVM_Code_Statement_Generator::enter_channel(QString channel_kind)
{
 static QString line = "add_new_channel $ %1";
 return line.arg(channel_kind);
}

QString ChVM_Code_Statement_Generator::enter_carrier()
{
 static QString line = "gen_carrier_tvr";
 return line;
}
