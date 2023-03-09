
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef GTAGML_TAG_COMMAND_CALLBACK__H
#define GTAGML_TAG_COMMAND_CALLBACK__H

#include "accessors.h"
#include "flags.h"

#include "relae-graph/relae-caon-ptr.h"

#include "global-types.h"

#include <QString>
#include <QMap>

#include <QTextStream>

#include <functional>

#include "kans.h"
KANS_(GTagML)


class GTagML_Node;

class GTagML_Tag_Command_Callback
{
public:
 flags_(1)
  bool has_pre_callback:1;
  bool has_post_callback:1;
  bool has_around_callback:1;
  bool pre_fallthrough:1;
  bool post_fallthrough:1;
  bool has_rename:1;
  bool has_rename_style_class:1;
 _flags

//? enum class Connection_Contexts { N_A, Parent, Sibling, Child, Unrelated };

private:

 QString command_name_trigger_;

 std::function<void(QTextStream&, caon_ptr<GTagML_Node> node, caon_ptr<GTagML_Node> prior_node,
   caon_ptr<GTagML_Node> parent_of_siblings, u4 index, caon_ptr<GTagML_Tag_Command_Callback> cb)> pre_callback_;

 std::function<void(QTextStream&, caon_ptr<GTagML_Node> node, caon_ptr<GTagML_Node> prior_node,
   caon_ptr<GTagML_Node> parent_of_siblings, u4 index, caon_ptr<GTagML_Tag_Command_Callback> cb)> post_callback_;

 std::function<void(QTextStream&, caon_ptr<GTagML_Node> node, caon_ptr<GTagML_Node> prior_node,
   caon_ptr<GTagML_Node> parent_of_siblings, u4 index, caon_ptr<GTagML_Tag_Command_Callback> cb)> around_callback_;

 QString rename_tag_;
 QString rename_style_class_;

public:

 ACCESSORS(QString ,rename_tag)
 ACCESSORS(QString ,rename_style_class)

 void rename_style_class(QString sc)
 {
  rename_style_class_ = sc;
  flags.has_rename_style_class = true;
 }

 typedef QMap<QString, std::function<void(QTextStream&, caon_ptr<GTagML_Node>,
   caon_ptr<GTagML_Node>, caon_ptr<GTagML_Node>, u4,
   caon_ptr<GTagML_Tag_Command_Callback>)> >
   Callback_Map_type;

 GTagML_Tag_Command_Callback(QString command_name);

 GTagML_Tag_Command_Callback(QString command_name,
  Callback_Map_type callbacks);

 void absorb(Callback_Map_type callbacks);

 GTagML_Tag_Command_Callback(QString command_name, QString tag);
 GTagML_Tag_Command_Callback(QString command_name, QString tag, QString style_class);

 void pre_callback(QTextStream& qts, caon_ptr<GTagML_Node> node,
   caon_ptr<GTagML_Node> prior_node, caon_ptr<GTagML_Node> parent_of_siblings,
   u4 index, caon_ptr<GTagML_Tag_Command_Callback> cb) const;

 void post_callback(QTextStream& qts, caon_ptr<GTagML_Node> node,
   caon_ptr<GTagML_Node> prior_node, caon_ptr<GTagML_Node> parent_of_siblings,
   u4 index, caon_ptr<GTagML_Tag_Command_Callback> cb) const;

 void around_callback(QTextStream& qts, caon_ptr<GTagML_Node> node,
   caon_ptr<GTagML_Node> prior_node, caon_ptr<GTagML_Node> parent_of_siblings,
   u4 index, caon_ptr<GTagML_Tag_Command_Callback> cb) const;


};

_KANS(GTagML)

#endif
