

//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)



#ifndef GH_BLOCK_WRITER__H
#define GH_BLOCK_WRITER__H

#include "global-types.h"

#include "accessors.h"

#include <QPair>
#include <QString>
#include <QStack>

class GH_Block_Base;


class GH_Block_Writer
{
 enum class Block_Roles { Tag_Command_Name, Mandatory, Optional, Main_Text, Custom };


 QMap<QString, QPair<Block_Roles, GH_Block_Base*>> current_named_blocks_;
 QMap<Block_Roles, GH_Block_Base*> current_blocks_;

 GH_Block_Base* current_main_text_block_;
 GH_Block_Base* current_tag_command_name_block_;

 GH_Block_Base* current_mandatory_argument_block_;
 GH_Block_Base* current_optional_argument_block_;

 QStack<GH_Block_Base*> held_blocks_;


public:

 GH_Block_Writer();

 ACCESSORS(GH_Block_Base* ,current_main_text_block)
 ACCESSORS(GH_Block_Base* ,current_tag_command_name_block)
 ACCESSORS(GH_Block_Base* ,current_mandatory_argument_block)
 ACCESSORS(GH_Block_Base* ,current_optional_argument_block)


 void init_standard_8bit();

 u4 push_optional();
 u4 pop_optional();

 u4 push_mandatory();
 u4 pop_mandatory();

 u4 push_main();
 u4 pop_main();

 void write_boundary_whitespace(QString bws);

 void write_to_main(QString text);

 GH_Block_Base* write_tag_command_name(QString name, QPair<u4, u4>& result);
 GH_Block_Base* write_tile(QString name, QString bws, QPair<u4, u4>& result,
   QVector<u4>* special_flag_marks = nullptr);
 GH_Block_Base* write_mandatory_argument(QString name, QPair<u4, u4>& result);
 GH_Block_Base* write_optional_argument(QString name, QPair<u4, u4>& result);

 GH_Block_Base* write_tag_command_name_as_main_text(QString name, QPair<u4, u4>& result);



};


#endif // GH_BLOCK_WRITER__H


