
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef DHAX_APPLICATION_CONTROLLER__H
#define DHAX_APPLICATION_CONTROLLER__H


#include "accessors.h"

#include "global-types.h"

#include "dhax-video/dhax-video-player-dialog.h"

#ifdef USE_XCSD
#include "xcsd-2d/xcsd-image.h"
#endif//def USE_XCSD

#ifdef USE_OpenCV
#include <opencv2/core/types.hpp>
#endif//def USE_OpenCV

#include <QString>
#include <QMap>
#include <QDir>

#include <QSize>

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

class DHAX_Graphics_Frame;


#ifdef USE_FORGE
class DHAX_Forge_Controller;
#endif

class DHAX_Application_State;

class DHAX_Stat_Assessment;

class DHAX_Video_Player_Dialog;

class  Feature_Classifier_Transform;


#ifdef USE_Image_Editor
class Main_Window_Dialog;
typedef Main_Window_Dialog Image_Editor_Dialog_Window;
#endif


class DHAX_Menu_System;

class DHAX_Application_Controller
{
 DHAX_Application_State* application_state_;

 DHAX_Menu_System* menu_system_;

 DHAX_Main_Window* application_main_window_;

#ifdef USE_Image_Editor
 Image_Editor_Dialog_Window* current_image_editor_dialog_window_;
#endif

 DHAX_Main_Window_Controller* main_window_controller_;
 DHAX_Main_Window_Receiver* main_window_receiver_;
 DHAX_Application_Receiver* application_receiver_;

#ifdef USE_FORGE
 DHAX_Forge_Controller* forge_controller_;
#endif

// QString current_image_file_path_;
// DHAX_Display_Image_Data* display_image_data_;
// Zoom_and_Navigate_Frame* zoom_frame_;
// DHAX_Image_Viewer* image_viewer_;
// DHAX_Image_Scene_Item* image_scene_item_;
// DHAX_Main_Window_Receiver* main_window_receiver_;
 DHAX_UDP_Controller* udp_controller_;

 QMap<QString, DHAX_Integration_Controller*> integration_controllers_;

 DHAX_Graphics_Frame* graphics_frame_;

 u4 autogen_index_;

 QSize old_main_window_size_;

 QString bookmarked_image_path_;

 //?
// QString mesh_position_;
// QString mesh_file_path_;
 QString txt_filename_path_;

#ifdef USE_Image_Editor
 Image_Editor_Dialog_Window* open_image_editor_dialog_window();
#endif

 QString proc_class_temp_folder_;

 DHAX_Video_Player_Dialog* current_video_player_dialog_;

 void check_reset_proc_class_temp_folder();

 QDir get_proc_class_temp_dir();

public:

 DHAX_Application_Controller();

 ACCESSORS(DHAX_Main_Window* ,application_main_window)
// ACCESSORS(Zoom_and_Navigate_Frame* ,zoom_frame)
// ACCESSORS(DHAX_Display_Image_Data* ,display_image_data)
// ACCESSORS(DHAX_Image_Viewer* ,image_viewer)
// ACCESSORS(DHAX_Main_Window_Receiver* ,main_window_receiver)
 ACCESSORS(DHAX_UDP_Controller* ,udp_controller)
 ACCESSORS(DHAX_Main_Window_Controller* ,main_window_controller)
 ACCESSORS(DHAX_Application_Receiver* ,application_receiver)
 ACCESSORS(DHAX_Application_State* ,application_state)

 ACCESSORS(DHAX_Menu_System* ,menu_system)

#ifdef USE_FORGE
 ACCESSORS(DHAX_Forge_Controller* ,forge_controller)
#endif

 ACCESSORS(DHAX_Graphics_Frame* ,graphics_frame)

 ACCESSORS(DHAX_Video_Player_Dialog* ,current_video_player_dialog)

 ACCESSORS__GET(QString ,bookmarked_image_path)
 ACCESSORS__SDECLARE(QString ,bookmarked_image_path)

// void take_screenshot();
// void load_image();
// void load_image(QString file_path);
// void init_image_scene_item(DHAX_Image_Scene_Item* si);

 //CLASS_NAME_FOLDER_FN(DHAX_Application_Controller)

 CLASS_NAME_FN (classname ,DHAX_Application_Controller)

#ifdef USE_OpenCV
 void show_keypoints(std::shared_ptr<QMap<QString, std::shared_ptr<DHAX_Stat_Assessment>>> transforms_map,
   QString file_path, std::vector<cv::KeyPoint>& keypoints);
#endif

// QString class_name_folder(QString pre)
// {
//  return pre + "/_DHAX_Application_Controller";
// }

 void handle_newly_downloaded_video(QString file_path);

 static void r8_vector_to_qba(const QVector<r8>& data, QByteArray& qba);

#ifdef USE_FORGE
 DHAX_Forge_Controller* check_init_forge_controller();
#endif//def USE_FORGE


#ifdef USE_XCSD
 void pixel_local_aggregate_color_distance(QString file_path, QString subfolder, XCSD_Image* xcsd = nullptr);

 void test_pixel_local_aggregate_color_distance();
 void show_pixel_local_aggregate_color_distance();
 void toroid_run_stats();

 QString get_test_file_from_folder(QString folder);

 void test_pixel_local_aggregate_color_distance(QString folder);
 void test_pixel_local_aggregate_color_distance(QString file_path, QString subfolder,
   XCSD_Image** xcsd = nullptr);

 void toroid_run_stats(QString folder, QString file_name,
   QString extension, XCSD_Image* xcsd = nullptr);
#endif//def USE_XCSD



 void change_image_margins(QVector<u1> margins, u1 cim);

 void init_udp_controller();
 void dispatch_datagram(QByteArray qba);
 void init_integration_controllers();

 void load_image(QString file_path);
 void load_notes();

#ifdef USE_Image_Editor
 void handle_edit_image_requested();
#endif

 void init_image_scene_item(DHAX_Image_Scene_Item *si);

 void send_ssr_reset(QRect window);
 void send_ssr_reset(QString message);

 void send_freecad_reset();
 void send_meshlab_reset();

 void view_contours();

 void view_trimap(QString path);

 void offer_to_play_video(QString text, QString file_path);

 void play_video(DHAX_Video_Player_Dialog::Annotation_Settings s);
 void play_video(DHAX_Video_Player_Dialog::Annotation_Settings s, QString file_path, QString annotations_file_path = {});
// void play_video();
// void play_video(QString file_path, QString annotations_file_path = {});

#ifdef USE_XCSD
 void calculate_fb_gaussian();

 void combined_test_stats();
 void register_test_image(bool then_run);

 void run_combined_test_stats();
 void run_combined_test_stats(QString folder);
 void run_combined_test_stats(QString folder, QString file_path);
#endif//def USE_XCSD

 void launch_edge_detection_dialog();

 QString get_current_image_folder();
 QString get_current_image_complete_base_name();
 QString get_current_image_suffix();
 QDir get_current_image_dir();
 QString get_current_image_file_path();
 QString get_current_image_q3x3_file_path();

 static void q3x3(const QImage& src, QString path);


 QColor handle_change_color(QString application_role);

 void handle_image_path_show_folder();
 void handle_change_image_border_color();
 void handle_change_scene_background_color();
 void handle_change_scene_margins_color();
 void handle_change_image_margins(QVector<u1> values, u1 context);

 void handle_set_border_visible();
 void handle_unset_border_visible();

 void handle_set_image_pen_visible();
 void handle_unset_image_pen_visible();

#ifdef USE_Image_Edit
 void handle_set_edit_transform_open_automatically();
 void handle_unset_edit_transform_open_automatically();
#endif//def USE_Image_Edit

 void handle_expand_window();
 void handle_unexpand_window();

 void handle_view_contour_info(QString path);
 void save_current_notation(bool with_comment);
 void handle_save_requested();
 void convert_notation_to_curve();



 void handle_complate_and_save_requested(bool with_comment);
 void handle_polyline_save_requested(bool with_comment);

 void launch_color_mean_dialog(QString folder, QStringList qsl);

#ifdef USE_IFC
 void run_ifc_convert();
#endif


};


#endif //  DHAX_APPLICATION_CONTROLLER__H


