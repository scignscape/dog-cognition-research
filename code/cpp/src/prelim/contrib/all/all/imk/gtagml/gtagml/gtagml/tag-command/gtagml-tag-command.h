
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef GTAGML_TAG_COMMAND__H
#define GTAGML_TAG_COMMAND__H

#include <QString>

#include <functional>

#include "accessors.h"
#include "flags.h"

#include "whitespace/gtagml-whitespace-holder.h"

#include "global-types.h"

#include "kans.h"

class GH_Block_Base;

KANS_(GTagML)

class GTagML_HTXN_Node;

class GH_Prenode;

class GTagML_Tag_Command : public GTagML_Whitespace_Holder
{
public:

 flags_(7)

  bool is_region:1;
  bool is_closed:1;
  bool is_html:1;
  bool is_self_closed:1;
  bool is_tag_assertion:1;
  bool is_tag_query:1;
  bool is_understood_auto_closed:1;
  bool has_main_tile:1;
  bool has_entry:1;
  bool has_attribute_tile:1;
  
  bool is_multi_parent:1;
  bool is_multi_optional:1;
  bool is_multi_mandatory:1;

  bool is_layer_optional:1;
  bool is_layer_mandatory:1;
  bool is_layer_main_optional:1;
  bool is_layer_main_mandatory:1;

  //bool is_multi_parent_semis:1;
  bool anticipate_semis:1;

  bool is_multi_parent_inherited:1;
//?  bool is_multi_parent_semis_inherited:1;
  bool anticipate_semis_inherited:1;


  bool multi_arg_layer:1;
  bool multi_main_layer:1;

  bool multi_arg_layer_inherited:1;
  bool multi_main_layer_inherited:1;

  bool autogen_multi_name:1;

  bool left_space_gap:1;
  bool right_space_gap:1;
  bool left_line_gap:1;
  bool right_line_gap:1;
  bool left_line_double_gap:1;
  bool right_line_double_gap:1;

  bool nonstandard_space:1;

  bool has_non_wrapped_space:1;
  bool is_non_wrapped:1;
  bool is_left_wrapped:1;

  bool is_main_layer:1;
  bool is_provisional_multi_parent:1;

  bool is_fiat:1;
  bool tile_is_quasi_fiat:1;

  bool marked_main:1;

  bool needs_sdi_mark:1;

  bool force_opt_split:1;

  bool has_boundary_white_whitespace:1;

  bool command_name_written_to_main:1;
//?  bool is_provisional_multi_parent_semis:1;

 _flags

private:

 QString name_;
 QString argument_; 

 QString parent_tag_type_;

 u4 ref_position_;
 u4 ref_order_;

 u4 ref_enter_;
 u4 ref_leave_;

 GTagML_HTXN_Node* gh_node_;

 GTagML_HTXN_Node* arg_gh_node_;

 QList<GTagML_HTXN_Node*> arg_gh_nodes_;

 QList<GH_Prenode*> arg_prenodes_;
 GH_Prenode* name_prenode_;

 GH_Prenode* last_tile_prenode_;

 QString opt_argument_;

 static std::function<bool(QString)> needs_sdi_mark_check_;

public:

 ACCESSORS(QString ,name)
 ACCESSORS(QString ,parent_tag_type)
 ACCESSORS(QString ,argument)

 ACCESSORS__GET(QString ,opt_argument)
 ACCESSORS__SDECLARE(QString ,opt_argument)

 ACCESSORS(u4 ,ref_position)
 ACCESSORS(u4 ,ref_order)

 ACCESSORS(u4 ,ref_enter)
 ACCESSORS(u4 ,ref_leave)


 ACCESSORS(GTagML_HTXN_Node* ,gh_node)
 ACCESSORS(GTagML_HTXN_Node* ,arg_gh_node)

 ACCESSORS(GH_Prenode* ,name_prenode)

 ACCESSORS(GH_Prenode* ,last_tile_prenode)


 static void set_needs_sdi_mark_check(std::function<bool(QString)> fn);

 void add_arg_prenode(GH_Block_Base* block, u4 enter, u4 leave);
 void init_name_prenode(GH_Block_Base* block, u4 enter, u4 leave);

 void add_arg_prenode(GH_Block_Base* block, const QPair<u4, u4>& pr);
 void init_name_prenode(GH_Block_Base* block, const QPair<u4, u4>& pr);

 GTagML_Tag_Command(QString name, QString argument,
   QString parent_tag_type = QString());

 QString latex_name();

 static QString latex_name(const QString& name);

 void add_arg_gh_node(GTagML_HTXN_Node* nhn);

 void each_arg_gh_node(std::function<void(GTagML_HTXN_Node*)> fn);

 void each_arg_prenode(std::function<void(GH_Prenode*)> fn);

 void normalize_whitespace();

 u2 get_whitespace_code();

};

_KANS(GTagML)

#endif
