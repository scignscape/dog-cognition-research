
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "dhax-main-window-receiver.h"

#include "dhax-main-window.h"
#include "dhax-main-window-controller.h"

#include <QMenuBar>

#include <QGuiApplication>
#include <QTimer>
#include <QDebug>
#include <QFile>
#include <QScreen>


DHAX_Main_Window_Receiver::DHAX_Main_Window_Receiver()
  :  application_main_window_(nullptr),
     main_window_controller_(nullptr)
{

}


void DHAX_Main_Window_Receiver::handle_draw_bezier(call_Stamp_u2 callstamp)
{
 main_window_controller_->draw_demo_bezier(/*callstamp*/);
}


void DHAX_Main_Window_Receiver::handle_draw_cubic_path(call_Stamp_u2 callstamp)
{
 main_window_controller_->draw_demo_cubic(/*callstamp*/);
}


void DHAX_Main_Window_Receiver::handle_draw_quad_path(call_Stamp_u2 callstamp)
{
 main_window_controller_->draw_demo_quad(/*callstamp*/);
}


void DHAX_Main_Window_Receiver::handle_get_annotation_comments(DHAX_Annotation_Instance* dai)
{
 main_window_controller_->show_annotation_comments(dai);
}

void DHAX_Main_Window_Receiver::handle_complete_polygon(call_Stamp_u2 callstamp)
{
 main_window_controller_->complete_polygon(/*callstamp*/);
}


void DHAX_Main_Window_Receiver::handle_meshlab_import_info(call_Stamp_u2 callstamp)
{
 application_main_window_->show_meshlab_import_info(/*callstamp*/);
}


void DHAX_Main_Window_Receiver::handle_freecad_import_info(call_Stamp_u2 callstamp)
{
 application_main_window_->show_freecad_import_info(/*callstamp*/);
}


void DHAX_Main_Window_Receiver::handle_take_screenshot(call_Stamp_u2 callstamp, QString folder)
{
 main_window_controller_->take_screenshot(/*callstamp*/);
}

void DHAX_Main_Window_Receiver::handle_load_image(call_Stamp_u2 callstamp)
{
 main_window_controller_->load_image(/*callstamp*/);
}

void DHAX_Main_Window_Receiver::handle_load_bookmarked_image(call_Stamp_u2 callstamp)
{
 main_window_controller_->load_bookmarked_image(/*callstamp*/);
}

#ifdef XCSD
void DHAX_Main_Window_Receiver::handle_show_xcsd_scene(call_Stamp_u2 callstamp)
{
 main_window_controller_->show_xcsd_scene(/*callstamp*/);
}

void DHAX_Main_Window_Receiver::handle_show_local_histogram(rc2 rc)
{
 main_window_controller_->show_local_color_histogram(rc);
}


void DHAX_Main_Window_Receiver::handle_calculate_local_color_histograms(call_Stamp_u2 callstamp)
{
 main_window_controller_->calculate_local_color_histograms(/*callstamp*/);
}

void DHAX_Main_Window_Receiver::handle_save_local_color_histograms(call_Stamp_u2 callstamp)
{
 main_window_controller_->save_local_color_histograms(/*callstamp*/);
}

void DHAX_Main_Window_Receiver::handle_show_fb_gradient_trimap(call_Stamp_u2 callstamp, bool autoset)
{
 main_window_controller_->show_fb_gradient_trimap(/*callstamp*/ autoset);
}
#endif//def XCSD



void DHAX_Main_Window_Receiver::handle_load_pdf(call_Stamp_u2 callstamp)
{
 main_window_controller_->load_pdf(/*callstamp*/);
}
