
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef DHAX_MOUSE_INTERACTION_DATA__H
#define DHAX_MOUSE_INTERACTION_DATA__H

#include <QFrame>
#include <QBoxLayout>
#include <QStack>

#include "accessors.h"

#include "global-types.h"

#include "flags.h"

//#include "dhax-data/ann/dhax-annotation-instance.h"

class DHAX_Graphics_Scene;
class DHAX_Graphics_View;

class DHAX_Image_Scene_Item;
class DHAX_Display_Image_Data;
class DHAX_Main_Window;
class DHAX_Annotation_Instance;

class DHAX_Application_State;


class DHAX_Mouse_Interaction_Data
{
 friend class DHAX_Image_Scene_Item;

 DHAX_Application_State* application_state_;

public:

 flags_(2)
   bool mouse_moving:1;
   bool needs_resume:1;
   bool ui_needs_update:1;
   bool has_resumed:1;
   bool pan_mode:1;
   bool pull_mode:1;
   bool multi_draw:1;
   bool is_pressed:1;
   bool is_double_pressed:1;
   bool shape_moving:1;
   bool checked:1;
   bool editing:1;
 _flags

 inline bool pan_or_pull_mode()
 {
  return flags.pan_mode || flags.pull_mode;
 }


public:

 DHAX_Mouse_Interaction_Data();

 ACCESSORS(DHAX_Application_State* ,application_state)


};

#endif //  DHAX_MOUSE_INTERACTION_DATA__H




