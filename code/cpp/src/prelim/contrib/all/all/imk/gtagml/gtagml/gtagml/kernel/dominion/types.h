
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


// //  This is a list of relevant types.
//    The DOMINION_TYPE has different
//    definitions depending on where
//    this file is included.


#undef DOMINION_OUTER_NAMESPACE
#undef DOMINION_INNER_NAMESPACE

#define DOMINION_NODE_TYPE GTagML_Node

#include "relae-graph/dominion-macros.h"
DOMINION_TYPE(string, QString, String)

#define DOMINION_OUTER_NAMESPACE KA
#define DOMINION_INNER_NAMESPACE GTagML
#include "relae-graph/dominion-macros.h"

DOMINION_TYPE(GTagML_root, GTagML_Root, GTagML_Root)
DOMINION_TYPE(gh_prenode, GH_Prenode, GH_Prenode)
DOMINION_TYPE(GTagML_token, GTagML_Token, GTagML_Token)
DOMINION_TYPE(GTagML_tile, GTagML_Tile, GTagML_Tile)
DOMINION_TYPE(GTagML_annotation_tile, GTagML_Annotation_Tile, GTagML_Annotation_Tile)
DOMINION_TYPE(GTagML_tag_command, GTagML_Tag_Command, GTagML_Tag_Command)
DOMINION_TYPE(GTagML_attribute_tile, GTagML_Attribute_Tile, GTagML_Attribute_Tile)
DOMINION_TYPE(GTagML_paralex_tile, GTagML_Paralex_Tile, GTagML_Paralex_Tile)
DOMINION_TYPE(GTagML_raw_tile, GTagML_Raw_Tile, GTagML_Raw_Tile)
