
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


 Context source_context = add_context("source-context");
 track_context({&source_context});

// Context group_context = add_context("group-context");
// track_context({&group_context});

// Context read_context = add_context("read-context",
//   {sample_context, group_context});

 activate(source_context);

 ChTR_Parse_Context& parse_context = graph_build.parse_context();



// add_rule(report_context,
//   "qj-enter",
//   "@at  .spaces. (?<line-number> \\d+ )  .spaces-optional. :  .spaces. "
////     "Qj \\( (?<context-name> .non-parens. ) \\) ",
//   ,[&]
// {
//  graph_build.enter_qj_context(p.matched("line-number").toUShort(), p.matched("context-name"));
// });

 add_rule(flags_all_(parse_context ,open_channel_body), source_context,
   "read-carrier-string",
   " [^)\\s]+ "          // (?<enum-type> \\w+) , (?<base-type> \\w+) )",
   ,[&]
  {
   graph_build.read_carrier_string(p.match_text());
  });


 add_rule(source_context,
   "statement-entry",
   "\\. (?!\\s)"
   ,[&]
 {
  graph_build.enter_statement_body();
 });



 add_rule(source_context,
   "channel-declaration",
   "\\[ (?<channel-string> [^\\]]+ )"
   ,[&]
 {
  graph_build.read_channel_string(p.matched("channel-string"));
 });


 add_rule(flags_all_(parse_context ,active_channel), source_context,
   "enter-channel-body",
   " \\( "          // (?<enum-type> \\w+) , (?<base-type> \\w+) )",
   ,[&]
  {
   graph_build.enter_channel_body();
  });


 add_rule(flags_all_(parse_context ,open_channel_body), source_context,
   "leave-channel-body",
   " \\) "          // (?<enum-type> \\w+) , (?<base-type> \\w+) )",
   ,[&]
  {
   graph_build.leave_channel_body();
  });


 add_rule(source_context,
   "skip",
   ".",
   [&]
 {
//  QString s = p.match_text();
//  qDebug() << "s = " << s;
 });



// add_rule(flags_all_(parse_context ,enum_def), report_context,
//   "enum-ops",
//   " ENUM_FLAGS_OP_MACROS \\( (?<enum-type> \\w+) , (?<base-type> \\w+) )",
//   [&]
// {

// });

}

