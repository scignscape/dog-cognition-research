
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef NGML_SDI_MARK_BASE__H
#define NGML_SDI_MARK_BASE__H

#include "global-types.h"


#include <QDebug>

#include <QTextStream>

//#include "ntxh-parser/ntxh-document.h"

#include "kans.h"

#include "accessors.h"

//KANS_CLASS_DECLARE(HGDMCore ,NTXH_Graph)
//USING_KANS(HGDMCore)

#include "rzns.h"

//class hypernode_type;


class NGML_SDI_Mark_Base
{
 u4 id_;

// u1 job_id_;

 u4 start_index_;
 u4 end_index_;

 QString kind_str_;

 u4 file_id_;

 u4 start_x_;
 u4 start_y_;
 u4 end_x_;
 u4 end_y_;

public:
 
 NGML_SDI_Mark_Base();

 ACCESSORS(u4 ,id)
 ACCESSORS(u4 ,file_id)

// ACCESSORS(u1 ,job_id)

 ACCESSORS(u4 ,start_index)
 ACCESSORS(u4 ,end_index)

 ACCESSORS(u4 ,start_x)
 ACCESSORS(u4 ,start_y)
 ACCESSORS(u4 ,end_x)
 ACCESSORS(u4 ,end_y)

 virtual QString get_kind_string();


// virtual u8 get_base_line_skip()
// {
//  return 0;
// }
};


#endif // NGML_SDI_SENTENCE__H
