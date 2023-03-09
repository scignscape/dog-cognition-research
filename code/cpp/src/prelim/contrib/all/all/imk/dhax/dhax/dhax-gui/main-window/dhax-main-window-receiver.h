
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef DHAX_MAIN_WINDOW_RECEIVER__H
#define DHAX_MAIN_WINDOW_RECEIVER__H

#include <QObject>

#include "accessors.h"

//#ifdef XCSD
#include "xcsd-2d/xcsd-sdi-structures.h"
//#endif

class DHAX_Main_Window;
class DHAX_Main_Window_Controller;
class DHAX_Annotation_Instance;

class DHAX_Main_Window_Receiver : public QObject
{
 Q_OBJECT

 DHAX_Main_Window* application_main_window_;
 DHAX_Main_Window_Controller* main_window_controller_;

public:

 DHAX_Main_Window_Receiver();

 ACCESSORS(DHAX_Main_Window* ,application_main_window)
 ACCESSORS(DHAX_Main_Window_Controller* ,main_window_controller)

public Q_SLOTS:

 void handle_take_screenshot(call_Stamp_u2, QString);

 void handle_load_image(call_Stamp_u2);
 void handle_load_bookmarked_image(call_Stamp_u2);

#ifdef XCSD
 void handle_show_xcsd_scene(call_Stamp_u2);

 void handle_calculate_local_color_histograms(call_Stamp_u2);
 void handle_save_local_color_histograms(call_Stamp_u2);

 void handle_show_fb_gradient_trimap(call_Stamp_u2, bool);
#endif

 void handle_load_pdf(call_Stamp_u2);
 void handle_complete_polygon(call_Stamp_u2);
 void handle_meshlab_import_info(call_Stamp_u2);
 void handle_freecad_import_info(call_Stamp_u2);

 void handle_draw_bezier(call_Stamp_u2);
 void handle_draw_cubic_path(call_Stamp_u2);
 void handle_draw_quad_path(call_Stamp_u2);

 void handle_get_annotation_comments(DHAX_Annotation_Instance* dai);

#ifdef USE_XCSD
 void handle_show_local_histogram(rc2);
#endif

};


#endif //  DHAX_MAIN_WINDOW_RECEIVER__H


