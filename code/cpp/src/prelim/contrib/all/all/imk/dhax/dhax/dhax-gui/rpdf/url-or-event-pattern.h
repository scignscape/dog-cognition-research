
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef URL_OR_EVENT_PATTERN__H
#define URL_OR_EVENT_PATTERN__H

#include "global-types.h"

#include "accessors.h"

class Context_Menu_Provider;

class URL_Or_Event_Pattern
{
 u2 pattern_context_;
 QString pattern_expression_;
 QString secondary_context_;
 QString procedure_name_;
 QString procedure_arguments_;

public:

 enum class Pattern_Contexts {
   N_A = 0,
   Link_Context_Menu_Formation = 1, Link_Context_Menu_Option = 2,
   Context_Menu_Formation = 4, Context_Menu_Option = 8,
   Navigation_Requested = 16, Link_Hover = 32, Link_Follow = 64,
   Link_Typed = 128
 };

 static QString pattern_context_to_string(u2 cue);
 static QString pattern_context_to_string_code(Pattern_Contexts pc)
 {
  switch(pc)
  {
  case Pattern_Contexts::N_A: return {};
  case Pattern_Contexts::Link_Context_Menu_Formation: return "lC";
  case Pattern_Contexts::Link_Context_Menu_Option: return "lO";
  case Pattern_Contexts::Context_Menu_Formation: return "C";
  case Pattern_Contexts::Context_Menu_Option: return "O";
  case Pattern_Contexts::Navigation_Requested: return "R";
  case Pattern_Contexts::Link_Hover: return "H";
  case Pattern_Contexts::Link_Follow: return "F";
  case Pattern_Contexts::Link_Typed: return "T";
  }
 }

 static u2 parse_pattern_context_string(QString cue);

 URL_Or_Event_Pattern(QMap<QString, QString> args);
 URL_Or_Event_Pattern();

 ACCESSORS(QString ,pattern_expression)
 ACCESSORS(QString ,secondary_context)
 ACCESSORS(QString ,procedure_name)
 ACCESSORS(QString ,procedure_arguments)
 ACCESSORS(u2 ,pattern_context)

 void set_pattern_context_string(QString cue)
 {
  pattern_context_ = parse_pattern_context_string(cue);
 }

};

#endif // URL_OR_EVENT_PATTERN__H
