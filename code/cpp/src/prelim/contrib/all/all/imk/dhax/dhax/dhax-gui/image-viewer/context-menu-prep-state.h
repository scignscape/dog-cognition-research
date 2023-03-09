
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef CONTEXT_MENU_PREP_STATE__H
#define CONTEXT_MENU_PREP_STATE__H

#include <QFrame>
#include <QBoxLayout>
#include <QStack>

#include "accessors.h"

#include "global-types.h"

#include "flags.h"

//#include "dhax-data/ann/dhax-annotation-instance.h"


class Context_Menu_Prep_State
{
public:

 flags_(1)
   bool no_loaded_image:1;
   bool pending_annotation_confirm:1;
   bool has_confirmed_annotations:1;
 _flags


public:

 Context_Menu_Prep_State();


};

#endif //  CONTEXT_MENU_PREP_STATE__H




