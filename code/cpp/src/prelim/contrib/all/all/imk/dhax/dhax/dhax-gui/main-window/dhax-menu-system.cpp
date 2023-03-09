
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "dhax-menu-system.h"

#include "dhax-main-window-menus.h"
#include "dhax-main-window.h"
#include "dhax-signal-generator.h"


#include <QMenuBar>

extern void instagram_temp();

DHAX_Menu_System::DHAX_Menu_System()
{
// tools_menu:
//  take screenshot

//// file menu
//   load image
//   load annotations
//   quit

//   save annotation
//   convert aim ...




// help menu
}


DHAX_Menu* DHAX_Menu_System::menu(QString label)
{
 return menus_->menu(label);
}

QAction* DHAX_Menu_System::add_deferred_action_ref(QString ref, DHAX_Menu& menu, QString key)
{
 QAction* result = add_action_ref(ref, menu, key);
 if(result)
 {
  result->setEnabled(false);
  deferred_actions_[{&menu, ref}] = result;
 }
 return result;
}

QAction* DHAX_Menu_System::add_action_ref(QString ref, DHAX_Menu& menu, QString key)
{
 for(QAction* a : menu.actions())
 {
  if(a->text() == key)
  {
   action_ref_map_[{&menu, ref}] = a;
   return a;
  }
 }
 return nullptr;
}

//void DHAX_Menu::add_deferred_action(QString key, QAction* a)
//{
// deferred_actions_.insert(key, a);
//}

//void DHAX_Menu::add_deferred_action_ref(QString ref, QString key)
//{
// action_ref_map_[ref] = deferred_actions_[key];
//}

QAction* DHAX_Menu_System::get_action_by_ref_name(QString ref, DHAX_Menu& menu)
{
 return action_ref_map_.value({&menu, ref});
}


void DHAX_Menu_System::init_menus()
{
 menus_ = new DHAX_Main_Window_Menus;
 menus_->set_parent(main_window_);

 menus_->init_menu("File");
 menus_->init_menu("Histograms");
 menus_->init_menu("Trimap");
 menus_->init_menu("Matrix");
 menus_->init_menu("Toroid");
 menus_->init_menu("Help");
 menus_->init_menu("Tools");

 DHAX_Signal_Generator* sg = main_window_->signal_generator();

 DHAX_Menu& file_menu = *menus_->menu("File");
 file_menu.add_action("Load PDF") << [sg]
 {
  sg->emit_load_pdf_requested();
 };

 file_menu.add_action("Load Image") << [sg]
 {
  sg->emit_load_image_requested();
 };

 file_menu.add_action("Load Bookmarked Image") << [sg]
 {
  sg->emit_load_bookmarked_image_requested();
 };

 //file_menu.
 add_deferred_action_ref("bookmark", file_menu, "Load Bookmarked Image");

 //file_menu.act

 file_menu.add_action("Load or Show Image as XCSD Scene") << [sg]
 {
  sg->emit_show_xcsd_scene_requested();
 };


 file_menu.addSeparator();
 file_menu.add_action("Load Notes") << [sg]
 {
  sg->emit_load_notes_requested();
 };

 //file_menu.addAction(action_load_annotations);

 file_menu.add_action("View Contours (Open CV)") << [sg]
 {
  sg->emit_view_contours_requested();
 };

 DHAX_Menu* launch_3D_menu = file_menu.add_nested_menu("Launch 3D");

// launch_3D_menu->addAction("View 3D (MeshLab)");
// launch_3D_menu->addAction("View 360 (Matterport)");
// launch_3D_menu->addAction("View CAD (FreeCAD)");

 launch_3D_menu->add_action("View 3D (MeshLab)") << [sg]
 {
  sg->emit_view_3d_requested();
 };

 launch_3D_menu->add_action("View 360 (Matterport)") << [sg]
 {
  sg->emit_view_360_requested();
 };

 launch_3D_menu->add_action("View CAD (FreeCAD)") << [sg]
 {
  sg->emit_view_cad_requested();
 };

 file_menu.add_action("Instagram Download") << []
 {
  instagram_temp();
 };


 DHAX_Menu* video_menu = file_menu.add_nested_menu("Play Video");
 video_menu->add_action("No Annotations") << [sg]
 {
  sg->emit_play_video_requested(DHAX_Video_Player_Dialog::No_Annotations);
 };
 video_menu->add_action("Load Annotatios") << [sg]
 {
  sg->emit_play_video_requested(DHAX_Video_Player_Dialog::Load_Annotations);
 };
 video_menu->add_action("Load Annotatios With Pause") << [sg]
 {
  sg->emit_play_video_requested(DHAX_Video_Player_Dialog::Load_Annotations_With_Pause);
 };
 video_menu->add_action("Load Annotatios Manually") << [sg]
 {
  sg->emit_play_video_requested(DHAX_Video_Player_Dialog::Load_Annotations_Manually);
 };
 video_menu->add_action("Play Video Series") << [sg]
 {
  sg->emit_play_video_requested(DHAX_Video_Player_Dialog::Video_Series);
 };

//?
// file_menu.add_action("Play Video") << [sg]
// {
//  sg->emit_play_video_requested();
// };

 file_menu.addSeparator();

 DHAX_Menu* ssr_menu = file_menu.add_nested_menu("Video Recorder (SimpleScreen)");

 ssr_menu->add_action("Prepare Recorder (opens external window)") << [sg]
 {
  sg->emit_prepare_video_recorder_requested();
 };

 ssr_menu->add_action("Test datagram") << [sg]
 {
  sg->emit_test_ssr_datagram_requested();
 };

 file_menu.addSeparator();

 file_menu.add_action("Run Forge Workflow (Forge API)") << [sg]
 {
  sg->emit_run_forge_workflow_requested();
 };

 file_menu.addSeparator();
 file_menu.add_action("Quit") << [sg]
 {
  sg->emit_quit_requested();
 };


 DHAX_Menu& hm = *menus_->menu("Histograms");

 hm.add_action("Calculate Local Color Histograms") << [sg]
 {
  sg->emit_calculate_local_color_histograms_requested();
 };

 hm.add_action("Save Local Color Histograms (diagrams)") << [sg]
 {
  sg->emit_save_local_color_histograms_requested();
 };


 DHAX_Menu& tm = *menus_->menu("Trimap");

 tm.add_action("Show fb-Gradient Trimap") << [sg]
 {
  sg->emit_show_fb_gradient_trimap_requested(false);
 };

 tm.add_action("Show fb-Gradient Trimap (autoset poles)") << [sg]
 {
  sg->emit_show_fb_gradient_trimap_requested(true);
 };

 DHAX_Menu& mm = *menus_->menu("Matrix");

 mm.add_action("Launch Edge-Detection Dialog") << [sg]
 {
  sg->emit_launch_edge_detection_dialog_requested();
 };

 mm.add_action("Calculate fb-Gaussian Matrix Space") << [sg]
 {
  sg->emit_calculate_fb_gaussian_requested();
 };


 DHAX_Menu& toroid_menu = *menus_->menu("Toroid");

 toroid_menu.add_action("Run stats")
   << [sg]
 {
  sg->emit_toroid_run_stats_requested();
 };

 toroid_menu.add_action("Show pixel-local aggregate color distance")
   << [sg]
 {
  sg->emit_show_pixel_local_aggregate_color_distance_requested();
 };

 toroid_menu.add_action("Test pixel-local aggregate color distance")
   << [sg]
 {
  sg->emit_test_pixel_local_aggregate_color_distance_requested();
 };

 DHAX_Menu* combined_menu = toroid_menu.add_nested_menu("Combined tests (fb/boundary)");

 combined_menu->add_action("Default location ")
   << [sg]
 {
  sg->emit_combined_test_stats_requested(true);
 };

 combined_menu->add_action("Choose location ")
   << [sg]
 {
  sg->emit_combined_test_stats_requested(false);
 };

 combined_menu->add_action("Register test image")
   << [sg]
 {
  sg->emit_register_test_image_requested(false);
 };

 combined_menu->add_action("Register, then run")
   << [sg]
 {
  sg->emit_register_test_image_requested(true);
 };


 DHAX_Menu& tools = *menus_->menu("Tools");

#ifdef USE_IFC
 tools.add_action("IFC Convert ...") << [sg]
 {
  //QApplication* qapp = qApp;
  sg->emit_ifc_convert_requested();
  //ifc_convert_run_main(qapp);
 };
#endif

 tools.add_action("Take Screenshot") << [sg]
 {
  sg->emit_take_screenshot_requested();
 };

}
