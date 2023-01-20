
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "dw-type.h"

USING_KANS(DGDB)

DW_Type::DW_Type()
  :  byte_length_(0),
     byte_length_code_(0), stash_id_(0),
     meta_object_(nullptr),
     stage_encoder_(nullptr)
{

}

DW_Type& DW_Type::default_object_layout()
{
 set_byte_length(QT_POINTER_SIZE);
 set_byte_length_code(QT_POINTER_SIZE);
 return *this;
}


