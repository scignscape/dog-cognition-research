
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "ngml-sdi-mark-base.h"

//#include "ntxh-parser/ntxh-document.h"

#include "global-types.h"

//typedef NTXH_Graph::hypernode_type hypernode_type;

NGML_SDI_Mark_Base::NGML_SDI_Mark_Base()
  :  start_index_(0), end_index_(0),
     start_x_(0), start_y_(0),
     end_x_(0), end_y_(0), file_id_(0)
{
}

QString NGML_SDI_Mark_Base::get_kind_string()
{
 return kind_str_;
}


