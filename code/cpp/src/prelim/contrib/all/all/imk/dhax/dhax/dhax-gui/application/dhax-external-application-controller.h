
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef DHAX_EXTERNAL_APPLICATION_CONTROLLER__H
#define DHAX_EXTERNAL_APPLICATION_CONTROLLER__H


#include "accessors.h"

#include "global-types.h"

#include <QString>
#include <QMap>

class DHAX_Main_Window;
class DHAX_Display_Image_Data;
class Zoom_and_Navigate_Frame;
class DHAX_Image_Viewer;
class DHAX_Image_Scene_Item;
class DHAX_Main_Window_Receiver;
class DHAX_UDP_Controller;
class Page_and_Search_Frame;

class DHAX_Integration_Controller;
class DHAX_Main_Window_Controller;
class DHAX_Application_Receiver;
class DHAX_Application_Controller;


class WebGL_View_Dialog;
class DHAX_Video_Player_Dialog;

class DHAX_External_Application_Controller //: public QObject
{
 DHAX_Main_Window* application_main_window_;
 DHAX_Application_Controller* application_controller_;

 WebGL_View_Dialog* current_wgl_dialog_;

 QString save_area_folder_;


public:

 DHAX_External_Application_Controller();

 ACCESSORS(DHAX_Main_Window* ,application_main_window)
 ACCESSORS(DHAX_Application_Controller* ,application_controller)

 void view_3d();
 void view_360();
 void view_cad();
 void prepare_video_recorder();
 void test_ssr_datagram();

#ifdef USE_FORGE
 void run_forge_workflow();
#endif//def USE_FORGE


};


#endif //  DHAX_EXTERNAL_APPLICATION_CONTROLLER__H


