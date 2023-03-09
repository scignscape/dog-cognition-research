
#include "url-or-event-pattern.h"

URL_Or_Event_Pattern::URL_Or_Event_Pattern(QMap<QString, QString> args)
  :
     pattern_context_(parse_pattern_context_string(args.value("pattern-context"))),
     pattern_expression_(args.value("pattern-expression")),
     secondary_context_(args.value("secondary-context")),
     procedure_name_(args.value("procedure-name")),
     procedure_arguments_(args.value("procedure-arguments"))
{

}

URL_Or_Event_Pattern::URL_Or_Event_Pattern()
  :  pattern_context_(0)
{
}


QString URL_Or_Event_Pattern::pattern_context_to_string(u2 cue)
{
 static Pattern_Contexts all_contexts [8] {
   Pattern_Contexts::Link_Context_Menu_Formation, Pattern_Contexts::Link_Context_Menu_Option,
   Pattern_Contexts::Context_Menu_Formation, Pattern_Contexts::Context_Menu_Option,
   Pattern_Contexts::Navigation_Requested, Pattern_Contexts::Link_Hover,
   Pattern_Contexts::Link_Follow, Pattern_Contexts::Link_Typed
 };

 QString result;
 for(Pattern_Contexts pc : all_contexts)
 {
  if( (cue & (u2) pc) > 0 )
    result += pattern_context_to_string_code(pc);
 }

 return result;
}

u2 URL_Or_Event_Pattern::parse_pattern_context_string(QString cue)
{
 u2 result = 0;

 if(cue.contains("lC"))
 {
  cue.remove("lC");
  result += (u2) Pattern_Contexts::Link_Context_Menu_Formation;
 }

 if(cue.contains("lO"))
 {
  cue.remove("lO");
  result += (u2) Pattern_Contexts::Link_Context_Menu_Option;
 }

 if(cue.contains("C"))
   result += (u2) Pattern_Contexts::Context_Menu_Formation;

 if(cue.contains("O"))
   result += (u2) Pattern_Contexts::Context_Menu_Option;

 if(cue.contains("R"))
   result += (u2) Pattern_Contexts::Navigation_Requested;

 if(cue.contains("H"))
   result += (u2) Pattern_Contexts::Link_Hover;

 if(cue.contains("F"))
   result += (u2) Pattern_Contexts::Link_Follow;

 if(cue.contains("T"))
   result += (u2) Pattern_Contexts::Link_Typed;

 return result;
}


