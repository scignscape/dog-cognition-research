
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "gtagml-tag-command.h"

#include "gh/gh-prenode.h"

#include "kans.h"
USING_KANS(GTagML)

bool needs_sdi_mark_check_nothing(QString)
{
 return false;
}

std::function<bool(QString)> GTagML_Tag_Command::needs_sdi_mark_check_ = &needs_sdi_mark_check_nothing;

void GTagML_Tag_Command::set_needs_sdi_mark_check(std::function<bool(QString)> fn)
{
 GTagML_Tag_Command::needs_sdi_mark_check_ = fn;
}

GTagML_Tag_Command::GTagML_Tag_Command(QString name, 
  QString argument, QString parent_tag_type)
 : Flags(0), name_(name), argument_(argument),
   parent_tag_type_(parent_tag_type),
   ref_position_(0), ref_order_(0),
   ref_enter_(0), ref_leave_(0),
   gh_node_(nullptr), arg_gh_node_(nullptr),
   name_prenode_(nullptr), last_tile_prenode_(nullptr)
{
 //if(name_.contains('-'))
 //  flags.needs_sdi_mark = true;
 if(needs_sdi_mark_check_(name))
   flags.needs_sdi_mark = true;
}


void GTagML_Tag_Command::set_opt_argument(QString arg)
{
 opt_argument_ = arg;
 flags.force_opt_split = true;
}


void GTagML_Tag_Command::each_arg_prenode(std::function<void(GH_Prenode*)> fn)
{
 for(GH_Prenode* ghp : arg_prenodes_)
   fn(ghp);
}

void GTagML_Tag_Command::add_arg_prenode(GH_Block_Base* block, const QPair<u4, u4>& pr)
{
 GH_Prenode* prenode = new GH_Prenode(block, pr.first, pr.second);
 arg_prenodes_.push_back(prenode);
}

void GTagML_Tag_Command::add_arg_prenode(GH_Block_Base* block, u4 enter, u4 leave)
{
 GH_Prenode* prenode = new GH_Prenode(block, enter, leave);
 arg_prenodes_.push_back(prenode);
}

void GTagML_Tag_Command::init_name_prenode(GH_Block_Base* block, const QPair<u4, u4>& pr)
{
 name_prenode_ = new GH_Prenode(block, pr.first, pr.second);
}

void GTagML_Tag_Command::init_name_prenode(GH_Block_Base* block, u4 enter, u4 leave)
{
 name_prenode_ = new GH_Prenode(block, enter, leave);
}



void GTagML_Tag_Command::each_arg_gh_node(std::function<void(GTagML_HTXN_Node*)> fn)
{
 for(GTagML_HTXN_Node* nhn : arg_gh_nodes_)
   fn(nhn);
}

void GTagML_Tag_Command::add_arg_gh_node(GTagML_HTXN_Node* nhn)
{
 arg_gh_nodes_.append(nhn);
}

u2 GTagML_Tag_Command::get_whitespace_code()
{
 if(flags.nonstandard_space)
   return 9999;
 u2 result = 0;
 if(flags.left_line_double_gap)
   result += 2000;
 if(flags.left_line_gap)
   result += 1000;
 if(flags.left_space_gap)
   result += 100;
 if(flags.right_space_gap)
   result += 1;
 if(flags.right_line_double_gap)
   result += 20;
 if(flags.right_line_gap)
   result += 10;
 return result;
}


void GTagML_Tag_Command::normalize_whitespace()
{
 u1 counts [4];
 ws().get_counts(counts);
 get_whitespace_counts_as_inherited(counts);
 for(int i = 0; i < 4; ++i)
   if(counts[i] == 255)
   {
    flags.nonstandard_space = true;
    return;
   }

 if(counts[0] > 1)
   flags.right_line_double_gap = true;
 else if(counts[0] == 1)
   flags.right_line_gap = true;
 if(counts[1] >= 1)
   flags.right_space_gap = true;

 if(counts[2] > 1)
   flags.left_line_double_gap = true;
 else if(counts[2] == 1)
   flags.left_line_gap = true;
 if(counts[3] >= 1)
   flags.left_space_gap = true;
}

QString GTagML_Tag_Command::latex_name(const QString& name)
{
 QString result = name;
 result.remove('-');
 return result;
}

QString GTagML_Tag_Command::latex_name()
{
 return latex_name(name_);
}

