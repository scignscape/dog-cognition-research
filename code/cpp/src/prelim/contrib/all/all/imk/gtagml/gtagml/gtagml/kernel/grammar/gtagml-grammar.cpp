
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "gtagml-grammar.h"

#include "kernel/grammar/gtagml-parse-context.h"

#include "kernel/grammar/gtagml-graph-build.h"

#include "kernel/grammar/gtagml-parser.h"

#include "relae-graph/relae-parser.templates.h"

USING_KANS(GTagML)

GTagML_Grammar::GTagML_Grammar()
{
}

void GTagML_Grammar::init(GTagML_Parser& p, GTagML_Graph& g, GTagML_Graph_Build& graph_build)
{
 pre_rule( "script-word", "(?:[^{}()\\[\\]\\s`;,:]|(?:\\w::?\\w))+" );
 pre_rule( "valid-tag-command-name", "[\\w@](?:[^{}()\\[\\]<>/\\s`;,.:]|(?:\\w+::?\\w))*" );
 pre_rule( "space-to-end-of-line", "[__\\t]* \\n" );
 pre_rule( "end-of-line", "[__\\t\\S]* \\n" );
 pre_rule( "single-space", "[__\\t]" );

 pre_rule( "tag-command-wrap-mode-indicator", ": :? \\.?" );

 Context gtagml_context = add_context("gtaml-context");
 //Context* raw_context = new Context( add_context("raw-context") );
 Context raw_context = add_context("raw-context");
 Context html_context = add_context("html-context");

 Context comment_context = add_context("comment-context");

 Context gtagml_or_html_context = add_context("gtaml-or-html",
   {gtagml_context, html_context});


 track_context({&gtagml_context, &raw_context,
   &gtagml_or_html_context, &html_context, &comment_context});

 switch(graph_build.current_parsing_mode())
 {
 case GTagML_Parsing_Modes::HTML:
  activate(gtagml_or_html_context);
  break;

 case GTagML_Parsing_Modes::Raw:
  activate(raw_context);
  break;

 case GTagML_Parsing_Modes::GTagML:
  activate(gtagml_context);
  break;
 }


 GTagML_Parse_Context& parse_context = graph_build.parse_context();

// size_t test;

 add_rule( gtagml_context, "enter-multi-line-comment",
   " ; ;+ (?<tail> [~-]{2,}) "
   ,[comment_context, this, &p] //raw_context, &graph_build, this, &p]
 {
  QString tail = p.matched("tail");
  activate_with_depth_mark(comment_context, tail.length());
 });

 add_rule( gtagml_context, "single-line-comment",
   " ;{2,} [~=-] [^\\n]* \\n "
   ,[] //raw_context, &graph_build, this, &p]
 {
 });


 add_rule( comment_context, "leave-multi-line-comment",
   " (?<tail> [~-]{2,}) ; ;+  "
   ,[gtagml_context, comment_context, this, &p] //raw_context, &graph_build, this, &p]
 {
  QString tail = p.matched("tail");
  check_activate_with_depth_mark(gtagml_context, comment_context, tail.length());
 });


 add_rule( gtagml_context, "enter-special-parse-mode",
   " \\{  "
   " (?<spm> .valid-tag-command-name. ) "
   " >> "
   ,[raw_context, &graph_build, this, &p]
 {
  QString spm = p.matched("spm");
  graph_build.enter_special_parse_mode(spm);
  if(graph_build.current_parsing_mode() == GTagML_Parsing_Modes::Raw)
    activate(raw_context);
 });

 add_rule( raw_context, "leave-special-parse-mode",
   " << (?<spm> .valid-tag-command-name. )? \\}  "
   ,[gtagml_context, &graph_build, this, &p]
 {
  QString spm = p.matched("spm");
  if(spm.isEmpty())
    spm = "raw";
  graph_build.leave_special_parse_mode(spm);
  if(graph_build.current_parsing_mode() == GTagML_Parsing_Modes::GTagML)
    activate(gtagml_context);
 });

 add_rule( raw_context, "spm-long-acc",
   " [^<]+  "
   ,[&]
 {
  graph_build.special_parse_mode_acc(p.match_text());
 });

 add_rule( raw_context, "spm-short-acc",
   " < "
   ,[&]
 {
  graph_build.special_parse_mode_acc(p.match_text());
 });


 add_rule( gtagml_context, "gtag-command-entry-inline",
   " \\[  "
   " (?<tag-command> .valid-tag-command-name. ) "
   " (?<tag-body-follow> [,>;.] ) "
   ,[&]
 {
  QString tag_command = p.matched("tag-command");
  QString tag_body_follow = p.matched("tag-body-follow");
 // QString argument = p.matched("argument");
  graph_build.gtag_command_entry_inline(tag_command, tag_body_follow);
  //graph_build.tag_body_leave();
 });

 add_rule( gtagml_context, "block-gtag-command-leave",
  " < (?<tag-command> .valid-tag-command-name. ) \\]  "
           ,[&]
 {
  graph_build.inline_tag_command_leave();
 });

 add_rule( flags_all_(parse_context ,inside_attribute_sequence),
   gtagml_context, "attribute-sequence-leave",
   " \\s+ => \\s+ "
   //" [/-]? "
   //" > "
   //" [,;.]? "
   ,[&]
 {
  //QString m = p.match_text();
  graph_build.attribute_sequence_leave();
 });

 add_rule( flags_all_(parse_context ,inside_attribute_sequence),
   gtagml_context, "mark-attribute-tile",
   " \\s+ @ \\s+ "
   ,[&]
 {
  graph_build.mark_attribute_tile();
 });



 // //  these should be for graph_build the equivalent
  //    of ->> (etc.) then `::some_cmd;
 add_rule( flags_all_(parse_context ,inside_multi_generic),
   gtagml_context,
   "cmd-multi-arg-transition",
   " \\s+ (?<fiat-or-wmi> (?: (?: :: ) | [.] | = ) ) (?<main> -{1,2}>{1,2}) "
   " \\s+ (?<cmd> .valid-tag-command-name. ) "
    ,[&]
 {
  QString cmd = p.matched("cmd");

  QString m = p.matched("main");
  QString fiat_or_wmi = p.matched("fiat-or-wmi");

  if(fiat_or_wmi == ".")
  {
   graph_build.multi_arg_transition({}, fiat_or_wmi, {}, "->");
   graph_build.tile_acc(cmd);
  }
  else
  {
   graph_build.multi_arg_transition({}, {}, {}, m);

   if(fiat_or_wmi == "=")
     graph_build.tag_command_entry_inline("::", {}, "==", cmd, ";", {});
   else
     graph_build.tag_command_entry_inline(fiat_or_wmi, {}, {}, cmd, ";", {});
  }
 });


 add_rule( flags_all_(parse_context ,inside_multi_generic),
   gtagml_context,
   "multi-arg-transition-to-main-tile",
   " \\s+ => \\s+ "
   ,[&]
 {
  graph_build.multi_arg_transition_to_main_tile();
 });

 add_rule( flags_all_(parse_context ,inside_multi_generic),
   gtagml_context,
   "multi-arg-transition",
   " \\s+ (?<wmi> .tag-command-wrap-mode-indicator.? ) "
   " (?<fiat> [=,]?)  "
   " (?<main> -{1,2}>{1,2} ) \\s+ "
   ,[&]
 {
  QString wmi = p.matched("wmi");
  QString fiat = p.matched("fiat");
  QString m = p.matched("main");
  graph_build.multi_arg_transition(wmi, {}, fiat, m);
 });

 add_rule( flags_all_(parse_context ,inside_multi_parent_semis),
   gtagml_context, "tag-command-leave-multi",
   "  \\s+ ;[.]*; "
   ,[&]
 {
  graph_build.tag_command_leave_multi({});
 //?  parse_context.flags.inside_multi_parent_semis = false;
 //? parse_context.flags.inside_multi_parent = false;
 });



 add_rule( flags_all_(parse_context ,inside_multi_parent),
   gtagml_context, "tag-command-leave-multi",
   "  ` (?<tag-command> .valid-tag-command-name.? ) ` "
   ,[&]
 {
  QString tag_command = p.matched("tag-command");
  graph_build.tag_command_leave_multi(tag_command);
//?  parse_context.flags.inside_multi_parent = false;
 });


 add_rule( gtagml_context, "cmd-tag-command-entry-multi",
   " ` (?<wmi> .tag-command-wrap-mode-indicator.? ) "
   " (?<tag-command> .valid-tag-command-name. ) "
   " (?<tag-body-follow> [,.]?) "
   " \\s+ (?<fiat-or-wmi> (?: (?: :: ) | [.] | = ) ) "
   " (?<first-arg-marker> -{1,2} >{1,2} ) \\s+ (?<cmd> .valid-tag-command-name. )"
   ,[&]
 {
  QString wmi = p.matched("wmi");

  QString tag_command = p.matched("tag-command");
  QString tag_body_follow = p.matched("tag-body-follow");

  QString fiat_or_wmi = p.matched("fiat-or-wmi");
  QString first_arg_marker = p.matched("first-arg-marker");

  QString cmd = p.matched("cmd");

  if(fiat_or_wmi == ".")
  {
   graph_build.tag_command_entry_multi(wmi, fiat_or_wmi, tag_command,
     tag_body_follow, {}, {}, first_arg_marker);
   graph_build.tile_acc(cmd);
  }
  else
  {
   graph_build.tag_command_entry_multi(wmi, {}, tag_command,
     tag_body_follow, {}, {}, first_arg_marker);

   if(fiat_or_wmi == "=")
     graph_build.tag_command_entry_inline("::",  {}, fiat_or_wmi, cmd, ";", {});
   else
     graph_build.tag_command_entry_inline(fiat_or_wmi, {}, {}, cmd, ";", {});
  }
 });


 add_rule( gtagml_context, "tag-command-entry-multi",
  " ` (?<wmi> .tag-command-wrap-mode-indicator.? ) " 
  " (?<tag-command> .valid-tag-command-name. ) "
  " (?<tag-body-follow> [,.]?) \\s+  "
  " (?<fwmi> .tag-command-wrap-mode-indicator.? ) "
  " (?<first-arg-marker> @ | (?: -{1,2} >{1,2} ) ) \\s+ "
           ,[&]
 {
  QString wmi = p.matched("wmi");
  QString fwmi = p.matched("fwmi");
  QString tag_command = p.matched("tag-command");
  QString tag_body_follow = p.matched("tag-body-follow");
  QString first_arg_marker = p.matched("first-arg-marker");
  graph_build.tag_command_entry_multi(wmi, {}, tag_command,
    tag_body_follow, {}, fwmi, first_arg_marker);
    //graph_build.tag_body_leave();
 });



 add_rule( gtagml_context, "tag-command-entry-with-layer",
   " ` " //?(?<wmi> .tag-command-wrap-mode-indicator.? ) "
   " (?<tag-command> .valid-tag-command-name. ) / "
   " (?: .single-space.+ )  (?<layer-marker> -{1,2} >{1,2} ) "
   ,[&]
 {
  QString tag_command = p.matched("tag-command");
  QString layer_marker = p.matched("layer-marker");
  graph_build.tag_command_entry_with_layer(tag_command, layer_marker);
  //graph_build.tag_body_leave();
 });


 add_rule( gtagml_context, "tag-command-entry-inline",
   " ` (?<wmi> .tag-command-wrap-mode-indicator.? ) "
   " (?<tag-command> .valid-tag-command-name. ) "
   " (?: < (?<argument> [^>]+ ) >)?  (?<tag-body-follow> [,;.] ) "
   ,[&]
 {
  QString wmi = p.matched("wmi");
  QString tag_command = p.matched("tag-command");
  QString tag_body_follow = p.matched("tag-body-follow");
  QString argument = p.matched("argument");
  graph_build.tag_command_entry_inline(wmi,  {}, {}, tag_command, tag_body_follow, argument);
  //graph_build.tag_body_leave();
 });

 add_rule( gtagml_context, "alt-tag-command-entry-inline",
   " ` (?<wmi> .tag-command-wrap-mode-indicator.? ) "
   " (?<tag-command> .valid-tag-command-name. ) "
   " <> (?<argument> [^;]* ) ;"
   ,[&]
 {
  QString wmi = p.matched("wmi");
  QString tag_command = p.matched("tag-command");
  QString argument = p.matched("argument");

  argument.replace('{', "! ");
  argument.replace('[', "? ");
  argument.replace('}', " ");
  argument.replace(']', " ");

  graph_build.tag_command_entry_inline(wmi, {}, {}, tag_command, ";", argument);
  //graph_build.tag_body_leave();
 });


#ifdef HIDE
 add_rule( html_context, "html-tag-command-leave",
  " </ (?<tag-command> .valid-tag-command-name. ) "
  " > "
  ,[&]
 {
  QString tag_command = p.matched("tag-command");
  graph_build.check_html_tag_command_leave(tag_command, p.match_text());
 });

 add_rule( gtagml_context, "tag-command-leave",
  " < (?<load-connector> .valid-tag-command-name. )? "
  "  < (?<tag-command> .valid-tag-command-name. ) "
  " /? "  // this really needs to be set to check for matching env's
  " > "
           ,[&]
 {
  QString load_connector = p.matched("load-connector");
  QString tag_command = p.matched("tag-command");
  if(load_connector.isEmpty())
   graph_build.check_tag_command_leave(tag_command, p.match_text());
  else
   graph_build.tag_command_leave(load_connector, tag_command);
 });
#endif //def HIDE

 add_rule( gtagml_context, "tag-block-command-leave",
  "  ` (?<tag-command> .valid-tag-command-name. ) ` "
  ,[&]
 {
  QString tag_command = p.matched("tag-command");
  graph_build.check_tag_command_leave(tag_command, p.match_text());
 });

 add_rule( gtagml_context, "inline-tag-command-leave",
  " ` (?: / | (?= \\s))  "
           ,[&]
 {
  graph_build.inline_tag_command_leave();
 });


#ifdef HIDE
 add_rule( gtagml_context, "generic-tag-command-leave",
  " </>  "
           ,[&]
 {
  graph_build.tag_command_leave();
 });
#endif //def HIDE

//?
// add_rule( gtagml_context, "special-character-sequence",
//  " (?: %-- ) | (?: %[<>$'] ) | (&-\\S>\\w) | (&#\\w+;) | (&:\\w+;) "
//           ,[&]
// {
//  QString m = p.match_text();
//  graph_build.special_character_sequence(m);
// });

  add_rule( gtagml_context, "semantic-mark",
   " (?: ` (?<pre> [`']?) (?: "
   "  \\( (?<sem1> [^)]+ ) \\) ) "
   "  | (?: ` { (?<sem2> [^}]+ ) } ) "
   "  | (?: ` \\[ (?<sem3> [^]]+ ) \\] ) "
   "  | (?: ` < (?<sem4> [^>]+ ) \\> ) "
   " ) " ,[&]
  {
   int which = 1;
   QString sem = p.matched("sem1");
   if(sem.isEmpty())
   {
    sem = p.matched("sem2");
    ++which;
   }
   if(sem.isEmpty())
   {
    sem = p.matched("sem3");
    ++which;
   }
   if(sem.isEmpty())
   {
    sem = p.matched("sem4");
    ++which;
   }
   if(sem.isEmpty())
   {
    which = 0;
   }

   QString m = p.match_text();

   graph_build.semantic_mark(m, sem, which);


  });

  add_rule( gtagml_context, "deleted-visual-line",
    "\\n* \\s* \\|[.]\\| \\s* ",
    [&]
  {
   QString m = p.match_text();
   graph_build.tile_acc("\n");
  });

  add_rule( gtagml_context, "deleted-visual-line-then-sentence-start",
    "\\n* \\s* \\|-\\| \\s* ",
    [&]
  {
   QString m = p.match_text();
   graph_build.tile_acc("\n`\(@)");
  });


  add_rule( gtagml_context, "declare-sentence-end-special-character-sequence",
    " (?<se> [,;:-]) (?<sp> \\s*) \\| (?<cue> [=]) \\|",
    [&]
  {

   QString se = p.matched("se");
   QString cue = p.matched("cue");

   QString esc1 = cue;
   QString m1 = QString("`\\[%1]").arg(cue);

   u1 which = 3;

//   if(se == ",")
//   {
//    QString sp = p.matched("sp");

//    QString m = "`\\<~>";
//    QString esc = "~";
//    u1 which0 = 4;
//    graph_build.tile_acc(se);
//    graph_build.special_character_sequence(m, esc, which0);
//    //?graph_build.tile_acc(sp);
//    graph_build.special_character_sequence(m1, esc1, which);
//    return;
//   }

   QString m = QString("`\\[%1]").arg(se);
   QString esc = se;


   graph_build.special_character_sequence(m, esc, which);
   graph_build.special_character_sequence(m1, esc1, which);

  });

  add_rule( gtagml_context, "declare-sentence-end",
    " (?<se> [,?!:-] | [.]) (?<mid> [\\])]*)"
    " \\s* \\|(?<end>[+*])\\| \\s* ",
    [&]
  {
   QString se = p.matched("se");
   QString mid = p.matched("mid");
   QString end = p.matched("end");
   QString m, m1, esc, esc1;
   u1 which = 3; // = "`\\[.]" QString esc = "." u1 which = 3

   if(end == "+")
   {
    m1 = "`\\[;]";
    esc1 = ";";
   }
   else
   {
    m1 = QString("`\\[%1]").arg(end);
    esc1 = end;
   }


   if( (se == ":") || (se == ",") )
   {
    m = QString("`\\[%1]").arg(se);
    esc = se;
   }
//   else if(se == ",")
//   {
//    m = "`\\[,]";
//    m1 = "`\\[;]";
//    esc = ",";
//    esc1 = ";";
//   }

//   else
//   {
//    m1 = "`\\[;]";
//    esc1 = ";";
//   }

//   else if(se == ".")
//   {
////    m = "`\\[.]";
//    m1 = "`\\[;]";
////    esc = ".";
//    esc1 = ";";
//   }
//   else if(se == "?")
//   {
//    m = "`\\[?]";
//    m1 = "`\\[;]";
//    esc = "?";
//    esc1 = ";";
//   }
//   else if(se == "!")
//   {
//    m = "`\\[!]";
//    m1 = "`\\[;]";
//    esc = "?";
//    esc1 = ";";
//   }

//   else
//     return;
//   // else others?

   if(m.isEmpty())
     graph_build.tile_acc(se);
   else
     graph_build.special_character_sequence(m, esc, which);

   if(!mid.isEmpty())
     graph_build.tile_acc(mid);

   graph_build.special_character_sequence(m1, esc1, which);

  });

  add_rule( gtagml_context, "special-special-character-sequence",
    " \\s* \\| (?<cue> [=_@]) \\| \\s* ",
    [&]
  {
   QString cue = p.matched("cue");
   QString esc = cue;
   QString m = QString("`\\[%1]").arg(cue);
   u1 which = 3;
   graph_build.special_character_sequence(m, esc, which);
  });

  add_rule( gtagml_context, "special-character-sequence",
   " (?: %-- ) | (?: %_) | (?: ->- ) | (?: %\\.,{2,3} ) "
   "  | (?: ` \\\\ \\( (?<bq-esc1> [^)]+ ) \\) ) "
   "  | (?: ` \\\\ { (?<bq-esc2> [^}]+ ) } ) "
   "  | (?: ` \\\\ \\[ (?<bq-esc3> [^]]+ ) \\] ) "
   "  | (?: ` \\\\ < (?<bq-esc4> [^>]+ ) \\> ) "
   "  | (?: \\| (?<pipe-esc> [^|]+) \\| )"
 
          //? "| (?: %[<>$'] ) | (&-\\S>\\w) | (&#\\w+;) | (&:\\w+;) "
            ,[&]
  {
   u1 which = 1;
   QString esc = p.matched("bq-esc1");
   if(esc.isEmpty())
   {
    esc = p.matched("bq-esc2");
    ++which;
   }
   if(esc.isEmpty())
   {
    esc = p.matched("bq-esc3");
    ++which;
   }
   if(esc.isEmpty())
   {
    esc = p.matched("bq-esc4");
    ++which;
   }
   if(esc.isEmpty())
   {
    esc = p.matched("pipe-esc");
    ++which;
   }
   if(esc.isEmpty())
   {
    which = 0;
   }

   QString m = p.match_text();

   graph_build.special_character_sequence(m, esc, which);
  });


 // // do we always want this?
 add_rule( gtagml_context, "tile-acc-newline",
  " .single-space.+ \\n "
           ,[&]
 {
  graph_build.tile_acc("\n");
 });

 add_rule( gtagml_context, "tile-acc",
  " . "
           ,[&]
 {
  graph_build.tile_acc(p.match_text());
 });


}
