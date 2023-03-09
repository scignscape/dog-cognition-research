
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef GH_TAG_COMMAND_NODE__H
#define GH_TAG_COMMAND_NODE__H


#include "gh-prenode-sequence-list.h"

#include <QList>

class GH_Prenode_Sequence;

class GH_Tag_Command_Node
{
 GH_Prenode_Sequence_List prenodes_;

public:

 GH_Tag_Command_Node();

 void add_prenode_sequence(QString key, GH_Prenode_Sequence* seq);
 void add_prenode_sequence(GH_Prenode_Sequence* seq);

 GH_Prenode_Sequence* enter_attribute_sequence(QString key);
 GH_Prenode_Sequence* enter_mandatory_sequence();
 GH_Prenode_Sequence* enter_optional_sequence();
 GH_Prenode_Sequence* enter_main_text_sequence();



};


#endif // GH_TAG_COMMAND_NODE__H


