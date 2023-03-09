

//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "gh-block-writer.h"

#include "gh-block-standard-8bit.h"

#define NO_BOUNDARY_WHITE_SPACE {}

GH_Block_Writer::GH_Block_Writer()
 :  current_main_text_block_(nullptr),
    current_tag_command_name_block_(nullptr),
    current_mandatory_argument_block_(nullptr),
    current_optional_argument_block_(nullptr)
{

}

GH_Block_Base* GH_Block_Writer::write_mandatory_argument(QString text, QPair<u4, u4>& result)
{
 current_mandatory_argument_block_->write(text, NO_BOUNDARY_WHITE_SPACE, result);
 return current_mandatory_argument_block_;
}

GH_Block_Base* GH_Block_Writer::write_optional_argument(QString text, QPair<u4, u4>& result)
{
 current_optional_argument_block_->write(text, NO_BOUNDARY_WHITE_SPACE, result);
 return current_optional_argument_block_;
}


GH_Block_Base* GH_Block_Writer::write_tag_command_name_as_main_text(QString name, QPair<u4, u4>& result)
{
 current_main_text_block_->write(name, NO_BOUNDARY_WHITE_SPACE, result);
 return current_main_text_block_;
}


GH_Block_Base* GH_Block_Writer::write_tag_command_name(QString name, QPair<u4, u4>& result)
{
 current_tag_command_name_block_->check_cached(name, result);
 if(result == QPair<u4, u4>{0, 0})
 {
  current_tag_command_name_block_->write(name, NO_BOUNDARY_WHITE_SPACE, result);
 }
 return current_tag_command_name_block_;
}


u4 GH_Block_Writer::push_optional()
{
 //?
// if(held_blocks_.isEmpty())
//   held_blocks_.push(current_optional_argument_block_);
// else if(held_blocks_.top() != current_optional_argument_block_)

 held_blocks_.push(current_optional_argument_block_);

 return held_blocks_.top()->layer_code();

}

u4 GH_Block_Writer::pop_optional()
{
 if(held_blocks_.isEmpty())
   return current_main_text_block_->layer_code();

 if(held_blocks_.top() == current_optional_argument_block_)
   held_blocks_.pop();

 if(held_blocks_.isEmpty())
   return current_main_text_block_->layer_code();

 return held_blocks_.top()->layer_code();
}

u4 GH_Block_Writer::push_mandatory()
{
 //?
// if(held_blocks_.isEmpty())
//   held_blocks_.push(current_mandatory_argument_block_);

// else if(held_blocks_.top() != current_mandatory_argument_block_)
   held_blocks_.push(current_mandatory_argument_block_);

 return current_mandatory_argument_block_->layer_code();
}

u4 GH_Block_Writer::pop_mandatory()
{
 if(held_blocks_.isEmpty())
   return current_main_text_block_->layer_code();

 if(held_blocks_.top() == current_mandatory_argument_block_)
   held_blocks_.pop();

 if(held_blocks_.isEmpty())
   return current_main_text_block_->layer_code();

 return held_blocks_.top()->layer_code();

}


u4 GH_Block_Writer::push_main()
{
 //?
// if(held_blocks_.isEmpty())
//   return current_main_text_block_->layer_code();

// if(held_blocks_.top() != current_main_text_block_)

 held_blocks_.push(current_main_text_block_);

 return current_main_text_block_->layer_code();
}

u4 GH_Block_Writer::pop_main()
{
 if(held_blocks_.isEmpty())
   return current_main_text_block_->layer_code();

 if(held_blocks_.top() == current_main_text_block_)
    held_blocks_.pop();

 if(held_blocks_.isEmpty())
   return current_main_text_block_->layer_code();

 return held_blocks_.top()->layer_code();
}

void GH_Block_Writer::write_to_main(QString text)
{
 QPair<u4, u4> pr;
 current_main_text_block_->write(text, NO_BOUNDARY_WHITE_SPACE, pr);
}

void GH_Block_Writer::write_boundary_whitespace(QString bws)
{
 if(held_blocks_.isEmpty())
 {
  current_main_text_block_->write_boundary_whitespace(bws);
 }
}


GH_Block_Base* GH_Block_Writer::write_tile(QString text,
  QString bws, QPair<u4, u4>& result, QVector<u4>* special_flag_marks)
{
 if(held_blocks_.isEmpty())
 {
  current_main_text_block_->write(text, bws, result, special_flag_marks);
  return current_main_text_block_;
 }
 held_blocks_.top()->write(text, bws, result, special_flag_marks);
 return held_blocks_.top();
}


void GH_Block_Writer::init_standard_8bit()
{
 current_tag_command_name_block_ = new GH_Block_Standard_8bit;
 current_tag_command_name_block_->activate_cache();
 current_blocks_[Block_Roles::Tag_Command_Name] = current_tag_command_name_block_;

 current_mandatory_argument_block_ = new GH_Block_Standard_8bit;
 current_optional_argument_block_ = new GH_Block_Standard_8bit;

 current_blocks_[Block_Roles::Mandatory]= current_mandatory_argument_block_;
 current_blocks_[Block_Roles::Optional] = current_optional_argument_block_;

 current_main_text_block_ = new GH_Block_Standard_8bit;
 current_main_text_block_->activate_inserts();
 current_blocks_[Block_Roles::Main_Text] = current_main_text_block_;

 current_main_text_block_->set_layer_summary("(1:main)");
 current_main_text_block_->set_layer_code(1);

 current_optional_argument_block_->set_layer_summary("(2:oarg)");
 current_optional_argument_block_->set_layer_code(2);

 current_mandatory_argument_block_->set_layer_summary("(3:marg)");
 current_mandatory_argument_block_->set_layer_code(3);

 current_tag_command_name_block_->set_layer_summary("(5:tcmd)");
 current_tag_command_name_block_->set_layer_code(5);
}

