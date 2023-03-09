
#ifndef DHAX_SIGNAL_GENERATOR__H
#define DHAX_SIGNAL_GENERATOR__H

#include <QObject>

#include <QVariant>

#include "accessors.h"
#include "global-types.h"
#include "self-connect.h"

#include "dhax-video/dhax-video-player-dialog.h"


class DHAX_Signal_Generator : public QObject
{
 Q_OBJECT

 //QObject* held_object_;

public:

 DHAX_Signal_Generator();


 USE_SELF_CONNECT(normal)
 USE_SELF_CONNECT(lambda)


 //void hold(QObject* obj);
 void emit_take_screenshot_requested();

 void emit_load_image_requested();
 void emit_load_bookmarked_image_requested();

 void emit_load_pdf_requested();
 void emit_load_notes_requested();
 void emit_received_datagram(QByteArray qba);

 void emit_show_xcsd_scene_requested();
 void emit_calculate_local_color_histograms_requested();
 void emit_save_local_color_histograms_requested();
 void emit_show_fb_gradient_trimap_requested(bool autoset);
 void emit_calculate_fb_gaussian_requested();
 void emit_launch_edge_detection_dialog_requested();

 void emit_prepare_video_recorder_requested();
 void emit_test_ssr_datagram_requested();

//?
 void emit_play_video_requested(DHAX_Video_Player_Dialog::Annotation_Settings s);
//? void emit_play_video_requested(); //DHAX_Video_Player_Dialog::Annotation_Settings s);

 void emit_test_pixel_local_aggregate_color_distance_requested();
 void emit_show_pixel_local_aggregate_color_distance_requested();
 void emit_toroid_run_stats_requested();
 void emit_combined_test_stats_requested(bool use_default_location);
 void emit_register_test_image_requested(bool then_run);


 void emit_view_contours_requested();
 void emit_view_3d_requested();
 void emit_view_360_requested();
 void emit_view_cad_requested();
 void emit_run_forge_workflow_requested();
 void emit_quit_requested();

#ifdef USE_IFC
 void emit_ifc_convert_requested();
#endif

Q_SIGNALS:

 void take_screenshot_requested(call_Stamp_u2, QString);
 void load_pdf_requested(call_Stamp_u2);

 void load_image_requested(call_Stamp_u2);
 void load_bookmarked_image_requested(call_Stamp_u2);


 void load_notes_requested(call_Stamp_u2);
 void received_datagram(QByteArray qba);

 void view_contours_requested(call_Stamp_u2);
 void view_3d_requested(call_Stamp_u2);
 void view_360_requested(call_Stamp_u2);

// void play_video_requested(call_Stamp_u2);//, DHAX_Video_Player_Dialog::Annotation_Settings);
 void play_video_requested(call_Stamp_u2, DHAX_Video_Player_Dialog::Annotation_Settings);

 void prepare_video_recorder_requested(call_Stamp_u2);
 void test_ssr_datagram_requested(call_Stamp_u2);

 void view_cad_requested(call_Stamp_u2);
 void run_forge_workflow_requested(call_Stamp_u2);
 void quit_requested(call_Stamp_u2);

 void show_xcsd_scene_requested(call_Stamp_u2);

 void calculate_local_color_histograms_requested(call_Stamp_u2);
 void save_local_color_histograms_requested(call_Stamp_u2);
 void show_fb_gradient_trimap_requested(call_Stamp_u2, bool);

 void calculate_fb_gaussian_requested(call_Stamp_u2);
 void launch_edge_detection_dialog_requested(call_Stamp_u2);

 void test_pixel_local_aggregate_color_distance_requested(call_Stamp_u2);
 void show_pixel_local_aggregate_color_distance_requested(call_Stamp_u2);
 void toroid_run_stats_requested(call_Stamp_u2);
 void combined_test_stats_requested(call_Stamp_u2, bool use_default_location);

 void register_test_image_requested(call_Stamp_u2, bool then_run);



#ifdef USE_IFC
 void ifc_convert_requested(call_Stamp_u2);
#endif


};

#endif // DHAX_SIGNAL_GENERATOR__H
