
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef RELAE_PARSE_CONTEXT__H
#define RELAE_PARSE_CONTEXT__H

#include "flags.h"
#include "rz-typedefs.h"

// //  Shouldn't this be in RZ?
struct RZ_Parse_Context
{
 typedef RZ_Script_Galaxy::tNode tNode;

 flags_(2)
  flag_(1, multiline_comment);
  flag_(2, awaiting_run_entry);
  flag_(3, awaiting_run_sequence);
  flag_(4, inline_cmd);
  flag_(5, inside_command_arguments);
  flag_(6, parse_as_escaped_pdm);
  flag_(7, parse_as_latex);
  flag_(8, parse_as_data_page);
  flag_(9, awaiting_command_argument);
 _flags_

 typedef RZ_Script_Galaxy::tCon tCon;

 tNode* current_open_print_node;

 tStack<tCon*> stacked_connectors;

 tMid stacked_connectors_count;

 template<typename CONNECTOR_Type>
 void stack_connector(CONNECTOR_Type&& c)
 {
  size_t st = sizeof(c);

  stacked_connectors.push( &c );
  ++stacked_connectors_count;
 }

 template<typename CONNECTOR_Type>
 void stack_connector(CONNECTOR_Type* c)
 {
  stacked_connectors.push( c );
  ++stacked_connectors_count;

 };


 tCon* pop_connector()
 {
  if(stacked_connectors_count > 0)
  {
   --stacked_connectors_count;
   tCon* result = stacked_connectors.top();
   stacked_connectors.pop();
   return result;
  }
  return 0;
 }


 RZ_Parse_Context(): Flags(), current_open_print_node(0), stacked_connectors_count(0) {}

};

#endif //RELAE_PARSE_CONTEXT__H
