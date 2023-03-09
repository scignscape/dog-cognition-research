
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef DHAX_APPLICATION_RECEIVER__H
#define DHAX_APPLICATION_RECEIVER__H

#include <QObject>

#include "accessors.h"

#include "global-types.h"

#include "dhax-video/dhax-video-player-dialog.h"

class DHAX_Main_Window;
class DHAX_Application_Controller;
class DHAX_External_Application_Controller;

class DHAX_Application_Receiver : public QObject
{
 Q_OBJECT

 DHAX_Main_Window* application_main_window_;
 DHAX_Application_Controller* application_controller_;
 DHAX_External_Application_Controller* external_application_controller_;

public:

 DHAX_Application_Receiver();

 ACCESSORS(DHAX_Main_Window* ,application_main_window)
 ACCESSORS(DHAX_Application_Controller* ,application_controller)
 ACCESSORS(DHAX_External_Application_Controller* ,external_application_controller)

public Q_SLOTS:

 void handle_save_notation(bool with_comment);
 void handle_polyline_save_notation(bool with_comment);
 //void handle_polyline_save_notation_with_comment();
 void handle_freecad_reset(call_Stamp_u2);

 void handle_load_notes(call_Stamp_u2);
 void handle_meshlab_reset(call_Stamp_u2);
 void handle_ssr_reset(QString msg, call_Stamp_u2);

 void handle_convert_notation(call_Stamp_u2);
 void handle_polygon_complete_and_save_notation(call_Stamp_u2);
 void handle_polygon_complete_and_save_notation_with_comment(call_Stamp_u2);

 void handle_edit_image(call_Stamp_u2);

 void handle_launch_edge_detection_dialog(call_Stamp_u2);

#ifdef USE_XCSD
 void handle_calculate_fb_gaussian(call_Stamp_u2);
 void handle_show_pixel_local_aggregate_color_distance(call_Stamp_u2);
 void handle_test_pixel_local_aggregate_color_distance(call_Stamp_u2);
 void handle_toroid_run_stats(call_Stamp_u2);
 void handle_combined_test_stats(call_Stamp_u2, bool use_default_location);
 void handle_register_test_image(call_Stamp_u2, bool then_run);
#endif//def USE_XCSD

//?
 void handle_play_video(call_Stamp_u2, DHAX_Video_Player_Dialog::Annotation_Settings);
//? void handle_play_video(call_Stamp_u2);

 void handle_view_contours(call_Stamp_u2);
 void handle_view_3d(call_Stamp_u2);
 void handle_view_360(call_Stamp_u2);
 void handle_prepare_video_recorder(call_Stamp_u2);
 void handle_test_ssr_datagram(call_Stamp_u2);
 void handle_view_cad(call_Stamp_u2);

#ifdef USE_FORGE
 void handle_run_forge_workflow(call_Stamp_u2);
#endif//def USE_FORGE


 void handle_launch_color_mean_dialog(QString folder, QStringList);


#ifdef USE_IFC
 void handle_ifc_convert(call_Stamp_u2);
#endif

// void handle_take_screenshot();
// void handle_load_image();

};


#endif //  DHAX_APPLICATION_RECEIVER__H


