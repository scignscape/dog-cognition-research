
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "dhax-application-receiver.h"

//#include "dhax-main-window.h"
//#include "dhax-main-window-controller.h"

#include "dhax-application-controller.h"
#include "dhax-external-application-controller.h"

#include <QMenuBar>

#include <QGuiApplication>
#include <QTimer>
#include <QDebug>
#include <QFile>
#include <QScreen>


DHAX_Application_Receiver::DHAX_Application_Receiver()
  :  application_main_window_(nullptr),
     application_controller_(nullptr)
{

}

void DHAX_Application_Receiver::handle_load_notes(call_Stamp_u2 callstamp)
{
 application_controller_->load_notes(/*callstamp*/);
}

void DHAX_Application_Receiver::handle_freecad_reset(call_Stamp_u2 callstamp)
{
 application_controller_->send_freecad_reset(/*callstamp*/);
}


void DHAX_Application_Receiver::handle_meshlab_reset(call_Stamp_u2 callstamp)
{
 application_controller_->send_meshlab_reset(/*callstamp*/);
}

void DHAX_Application_Receiver::handle_ssr_reset(QString msg, call_Stamp_u2 callstamp)
{
 application_controller_->send_ssr_reset(msg/*callstamp*/);
}



void DHAX_Application_Receiver::handle_convert_notation(call_Stamp_u2 callstamp)
{
 application_controller_->convert_notation_to_curve(/*callstamp*/);
}

#ifdef USE_IFC
void DHAX_Application_Receiver::handle_ifc_convert(call_Stamp_u2 callstamp)
{
 application_controller_->run_ifc_convert(/*callstamp*/);
}
#endif


void DHAX_Application_Receiver::handle_launch_edge_detection_dialog(call_Stamp_u2 callstamp)
{
 application_controller_->launch_edge_detection_dialog(/*callstamp*/);
}

#ifdef USE_XCSD

void DHAX_Application_Receiver::handle_calculate_fb_gaussian(call_Stamp_u2 callstamp)
{
 application_controller_->calculate_fb_gaussian(/*callstamp*/);
}


void DHAX_Application_Receiver::handle_show_pixel_local_aggregate_color_distance(call_Stamp_u2)
{
 application_controller_->show_pixel_local_aggregate_color_distance(/*callstamp*/);
}

void DHAX_Application_Receiver::handle_test_pixel_local_aggregate_color_distance(call_Stamp_u2)
{
 application_controller_->test_pixel_local_aggregate_color_distance(/*callstamp*/);
}

void DHAX_Application_Receiver::handle_toroid_run_stats(call_Stamp_u2)
{
 application_controller_->toroid_run_stats(/*callstamp*/);
}

void DHAX_Application_Receiver::handle_combined_test_stats(call_Stamp_u2, bool use_default_location)
{
 if(use_default_location)
   application_controller_->run_combined_test_stats(/*callstamp*/);

 else
   application_controller_->combined_test_stats(/*callstamp*/);
}

void DHAX_Application_Receiver::handle_register_test_image(call_Stamp_u2, bool then_run)
{
 application_controller_->register_test_image(/*callstamp*/then_run);
}
#endif//def USE_XCSD

void DHAX_Application_Receiver::handle_save_notation(bool with_comment)
{
 application_controller_->save_current_notation(with_comment);
}

void DHAX_Application_Receiver::handle_launch_color_mean_dialog(QString folder, QStringList qsl)
{
 application_controller_->launch_color_mean_dialog(folder, qsl);
}

void DHAX_Application_Receiver::handle_edit_image(call_Stamp_u2 callstamp)
{
#ifdef USE_Image_Editor
 application_controller_->handle_edit_image_requested(/*callstamp*/);
#endif
}

void DHAX_Application_Receiver::handle_polygon_complete_and_save_notation(call_Stamp_u2 callstamp)
{
 application_controller_->handle_complate_and_save_requested(false);
}

void DHAX_Application_Receiver::handle_polygon_complete_and_save_notation_with_comment(call_Stamp_u2 callstamp)
{
 application_controller_->handle_complate_and_save_requested(true);
}

void DHAX_Application_Receiver::handle_polyline_save_notation(bool with_comment)
{
 application_controller_->handle_polyline_save_requested(with_comment);
}


void DHAX_Application_Receiver::handle_view_contours(call_Stamp_u2 callstamp)
{
 application_controller_->view_contours(/*callstamp*/);
}

void DHAX_Application_Receiver::handle_view_3d(call_Stamp_u2 callstamp)
{
 external_application_controller_->view_3d(/*callstamp*/);
}

//void DHAX_Application_Receiver::handle_play_video(call_Stamp_u2 callstamp)
//{
// application_controller_->play_video(/*callstamp*/);
//}
//?
void DHAX_Application_Receiver::handle_play_video(call_Stamp_u2 callstamp, DHAX_Video_Player_Dialog::Annotation_Settings s)
{
 application_controller_->play_video(s/*callstamp*/);
}

void DHAX_Application_Receiver::handle_prepare_video_recorder(call_Stamp_u2 callstamp)
{
 external_application_controller_->prepare_video_recorder(/*callstamp*/);
}

void DHAX_Application_Receiver::handle_test_ssr_datagram(call_Stamp_u2 callstamp)
{
 external_application_controller_->test_ssr_datagram(/*callstamp*/);
}


void DHAX_Application_Receiver::handle_view_360(call_Stamp_u2 callstamp)
{
 external_application_controller_->view_360(/*callstamp*/);
}

void DHAX_Application_Receiver::handle_view_cad(call_Stamp_u2 callstamp)
{
 external_application_controller_->view_cad(/*callstamp*/);
}

#ifdef USE_FORGE
void DHAX_Application_Receiver::handle_run_forge_workflow(call_Stamp_u2 callstamp)
{
 external_application_controller_->run_forge_workflow(/*callstamp*/);
}
#endif//fdef USE_FORGE
