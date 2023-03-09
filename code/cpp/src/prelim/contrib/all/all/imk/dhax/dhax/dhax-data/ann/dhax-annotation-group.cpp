
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "dhax-annotation-group.h"

#include "dhax-annotation-instance.h"


DHAX_Annotation_Group::DHAX_Annotation_Group(DHAX_Annotation_Group* parent_group)
  :  parent_group_(parent_group)
{

}

void DHAX_Annotation_Group::add_annotation(DHAX_Annotation_Instance* dai)
{
 annotations_.push_back(dai);
}


DHAX_Annotation_Instance* DHAX_Annotation_Group::add_annotation()
{
 DHAX_Annotation_Instance* result = new DHAX_Annotation_Instance;
 result->set_group(this);
 annotations_.push_back(result);
 return result;
}
