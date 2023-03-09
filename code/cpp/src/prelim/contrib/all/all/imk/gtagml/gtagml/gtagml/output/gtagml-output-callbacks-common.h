
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


//?#define QSTRING_STRIP_HYPHEN(x) QString(x).remove('-')

//?#define QSTRING_STRIP_HYPHEN(x) QString(x)

#define RENAME_(name, tag, style_class) \
 callbacks_[#name] = caon_ptr<GTagML_Tag_Command_Callback>( new GTagML_Tag_Command_Callback(#name, #tag, #style_class) ); \


#define RENAME_TAG(name, tag) \
 callbacks_[#name] = caon_ptr<GTagML_Tag_Command_Callback>( new GTagML_Tag_Command_Callback(#name, #tag) ); \


#define GTAGML_CALLBACK_(name) \
 callbacks_[#name] = caon_ptr<GTagML_Tag_Command_Callback>( new GTagML_Tag_Command_Callback(#name, \
  GTagML_Tag_Command_Callback::Callback_Map_type{{ \


// //  Should b be captured, or an argument?

#define WHEN_(kind) \
  {#kind, [this](QTextStream& qts, caon_ptr<tNode> node, \
  caon_ptr<tNode> prior_node, \
  caon_ptr<GTagML_Node> parent_of_siblings, \
  u4 index, caon_ptr<GTagML_Tag_Command_Callback> cb)

#define _WHEN },

#define _WHEN_(kind) _WHEN WHEN_(kind)

#define _GTagML_CALLBACK }}) );

#define GTAGML_CALLBACK_SUPPRESS(name) \
 GTAGML_CALLBACK_(name) \
 WHEN_(pre) \
 { \
  suppress_node_ = node; \
 } \
 _WHEN_(post) \
 { \
  suppress_node_ = nullptr; \
 } \
 _WHEN \
_GTagML_CALLBACK \

#define GTAGML_CALLBACK_NOACTION(name) \
 GTAGML_CALLBACK_(name) \
  WHEN_(around) \
  { \
  } \
  _WHEN \
_GTagML_CALLBACK \


