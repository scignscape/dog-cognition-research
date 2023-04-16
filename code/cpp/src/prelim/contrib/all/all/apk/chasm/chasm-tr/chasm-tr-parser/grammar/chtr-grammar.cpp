
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "chtr-grammar.h"

#include "chtr-parse-context.h"

#include "chtr-graph-build.h"

#include "chtr-parser.h"

#include "relae-graph/relae-parser.templates.h"

#include <QDebug>


USING_AQNS(Chasm_TR)

ChTR_Grammar::ChTR_Grammar()
{
}

void ChTR_Grammar::init(ChTR_Parser& p, ChTR_Graph& g, ChTR_Graph_Build& graph_build)
{
 // //  Check for package privates...?
 pre_rule( "script-word", "(?:[^{}()\\[\\]\\s`;,:]|(?:\\w::?\\w))+" );
 pre_rule( "ns-word", "(?: [^{}()\\[\\]\\s`;,:]+ )" );

// //  not used here ...
  //      pre_rule( "space-to-end-of-line", "[__\\t]* (?: ;- [^\\n]+ )? (?= \\n )" );
// //  not used here ...
  //      pre_rule( "end-of-line", "[__\\t\\S]* \\n" );

 pre_rule( "single-space", "[__\\t]" );
 pre_rule( "spaces", "[__\\t]+" );
 pre_rule( "spaces-optional", "[__\\t]*" );

 pre_rule( "non-parens", "[^)]*" );


 Context report_context = add_context("report-context");
 track_context({&report_context});

// Context group_context = add_context("group-context");
// track_context({&group_context});

// Context read_context = add_context("read-context",
//   {sample_context, group_context});

 activate(report_context);

 ChTR_Parse_Context& parse_context = graph_build.parse_context();

 add_rule(report_context,
   "qj-leave",
   "@lv .spaces. (?<line-number> \\d+ ) .spaces-optional. : .spaces."
     "Qj  .spaces-optional. \\( (?<context-name> .non-parens. ) \\) ",
   [&]
 {
  graph_build.leave_qj_context(p.matched("line-number").toUShort(), p.matched("context-name"));
 });


// add_rule(report_context,
//   "qj-enter",
//   "@at  .spaces. (?<line-number> \\d+ )  .spaces-optional. :  .spaces. "
////     "Qj \\( (?<context-name> .non-parens. ) \\) ",
//   ,[&]
// {
//  graph_build.enter_qj_context(p.matched("line-number").toUShort(), p.matched("context-name"));
// });

 add_rule(report_context,
   "qj-enter",
   "@at .spaces. (?<line-number> \\d+ ) .spaces-optional. : .spaces. "
     "Qj .spaces-optional. \\( (?<context-name> .non-parens. ) \\) ",
   [&]
 {
  graph_build.enter_qj_context(p.matched("line-number").toUShort(), p.matched("context-name"));
 });

 add_rule(flags_all_(parse_context ,enum_def), report_context,
   "enum-def",
   "enum_macro\\( (?<label> \\w+ ) , (?<value> .non-parens.) \\)",
   [&]
 {
  graph_build.note_enum_def(p.matched("label"), p.matched("value"));
 });

 add_rule(report_context,
   "line-number",
   "@ln .spaces. (?<line-number> \\d+ ) .spaces-optional. : .spaces. ",
   [&]
 {
  graph_build.hold_line_number(p.matched("line-number").toUShort());
 });

 add_rule(report_context,
   "skip",
   ".",
   [&]
 {
//  QString s = p.match_text();
//  qDebug() << "s = " << s;
 });



 add_rule(flags_all_(parse_context ,enum_def), report_context,
   "enum-ops",
   " ENUM_FLAGS_OP_MACROS \\( (?<enum-type> \\w+) , (?<base-type> \\w+) )",
   [&]
 {

 });

}

