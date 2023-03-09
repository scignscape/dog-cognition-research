
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "gtagml-tag-command-callback.h"

#include "kans.h"

USING_KANS(GTagML)

GTagML_Tag_Command_Callback::GTagML_Tag_Command_Callback(QString command_name, QString tag)
 : Flags(0), command_name_trigger_(command_name), rename_tag_(tag)
{
 flags.has_rename = true;

 //?
 flags.pre_fallthrough = true;
 flags.post_fallthrough = true;
}


GTagML_Tag_Command_Callback::GTagML_Tag_Command_Callback(QString command_name,
 QString tag, QString style_class)
 : Flags(0), command_name_trigger_(command_name),
   rename_tag_(tag), rename_style_class_(style_class)
{
 flags.has_rename = true;
 flags.has_rename_style_class = true;

 flags.pre_fallthrough = true;
 flags.post_fallthrough = true;

}


GTagML_Tag_Command_Callback::GTagML_Tag_Command_Callback(QString command_name,
  QMap<QString, std::function<void(QTextStream&, caon_ptr<GTagML_Node>,
  caon_ptr<GTagML_Node>, caon_ptr<GTagML_Node>,
  u4, caon_ptr<GTagML_Tag_Command_Callback>)> > callbacks)
 : Flags(0), command_name_trigger_(command_name)
{
 absorb(callbacks);
}

GTagML_Tag_Command_Callback::GTagML_Tag_Command_Callback(QString command_name)
 : Flags(0), command_name_trigger_(command_name)
{
}

void GTagML_Tag_Command_Callback::pre_callback(QTextStream& qts, caon_ptr<GTagML_Node> node,
  caon_ptr<GTagML_Node> prior_node, caon_ptr<GTagML_Node> parent_of_siblings,
  u4 index, caon_ptr<GTagML_Tag_Command_Callback> cb) const
{
 pre_callback_(qts, node, prior_node, parent_of_siblings, index, cb);
}

void GTagML_Tag_Command_Callback::post_callback(QTextStream& qts, caon_ptr<GTagML_Node> node,
  caon_ptr<GTagML_Node> prior_node, caon_ptr<GTagML_Node> parent_of_siblings,
  u4 index, caon_ptr<GTagML_Tag_Command_Callback> cb) const
{
 post_callback_(qts, node, prior_node, parent_of_siblings, index, cb);
}

void GTagML_Tag_Command_Callback::around_callback(QTextStream& qts, caon_ptr<GTagML_Node> node,
  caon_ptr<GTagML_Node> prior_node, caon_ptr<GTagML_Node> parent_of_siblings,
  u4 index, caon_ptr<GTagML_Tag_Command_Callback> cb) const
{
 around_callback_(qts, node, prior_node, parent_of_siblings, index, cb);
}


void GTagML_Tag_Command_Callback::absorb(Callback_Map_type callbacks)
{
 if(callbacks.contains("pre"))
 {
  flags.has_pre_callback = true;
  pre_callback_ = callbacks["pre"];
 }

 if(callbacks.contains("post"))
 {
  flags.has_post_callback = true;
  post_callback_ = callbacks["post"];
 }

 if(callbacks.contains("around"))
 {
  flags.has_around_callback = true;
  around_callback_ = callbacks["around"];
 }
}

