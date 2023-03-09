

//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "gh-tag-command-node.h"

#include "gh-prenode-sequence.h"

GH_Tag_Command_Node::GH_Tag_Command_Node()
{

}

void GH_Tag_Command_Node::add_prenode_sequence(GH_Prenode_Sequence* seq)
{
 add_prenode_sequence("!", seq);
}

void GH_Tag_Command_Node::add_prenode_sequence(QString key, GH_Prenode_Sequence* seq)
{
 prenodes_.push_back({key, seq});
}

GH_Prenode_Sequence* GH_Tag_Command_Node::enter_attribute_sequence(QString key)
{
 GH_Prenode_Sequence* result = new GH_Prenode_Sequence;
 add_prenode_sequence(key, result);
 return result;
}

GH_Prenode_Sequence* GH_Tag_Command_Node::enter_mandatory_sequence()
{
 GH_Prenode_Sequence* result = new GH_Prenode_Sequence;
 add_prenode_sequence("!", result);
 return result;
}

GH_Prenode_Sequence* GH_Tag_Command_Node::enter_optional_sequence()
{
 GH_Prenode_Sequence* result = new GH_Prenode_Sequence;
 add_prenode_sequence("?", result);
 return result;
}

GH_Prenode_Sequence* GH_Tag_Command_Node::enter_main_text_sequence()
{
 GH_Prenode_Sequence* result = new GH_Prenode_Sequence;
 add_prenode_sequence("\\", result);
 return result;
}

