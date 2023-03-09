
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "dhax-main-window-controller.h"

#include "dhax-main-window.h"

#include "image-viewer/dhax-display-image-data.h"

#include "image-viewer/image-document-controller.h"

#include "pleneviews/zoom-and-navigate-frame.h"
#include "pleneviews/page-and-search-frame.h"
#include "pleneviews/shape-select-frame.h"

#include "image-viewer/dhax-image-viewer.h"

#include "image-viewer/dhax-image-scene-item.h"

#include "main-window/dhax-main-window-receiver.h"
#include "main-window/dhax-main-window-data.h"

#include "integration/meshlab/dhax-meshlab-integration-data.h"
#include "integration/freecad/dhax-freecad-integration-data.h"

#include "application/dhax-application-controller.h"

#include "dhax-graphics-scene.h"

#include "pdf-viewer/pdf-document-controller.h"

#ifdef USE_XCSD
#include "xcsd-2d/mat2d.h"
#include "xcsd-2d/mat2d.templates.h"
#include "xcsd-1d/vec1d.h"
#include "xcsd-2d/xcsd-image.h"
#include "xcsd-2d/xcsd-tierbox.h"
#include "dialogs/xcsd-local-histogram-dialog.h"
#endif//def USE_XCSD

#include "dhax-graphics-frame.h"

#include "self-connect.h"

#include "styles.h"

#include "styled-messages.h"


#include <QMenuBar>

#include <QGuiApplication>
#include <QTimer>
#include <QDebug>
#include <QFile>
#include <QScreen>

#include <QFileDialog>

#include <QGraphicsProxyWidget>

#include <QGraphicsPixmapItem>

DHAX_Main_Window_Controller::DHAX_Main_Window_Controller()
  :  display_image_data_(nullptr),
     zoom_frame_(nullptr),
     shape_select_frame_(nullptr),
     page_and_search_frame_(nullptr),
     image_scene_item_(nullptr),
     main_window_receiver_(nullptr),
     application_controller_(nullptr),
     pdf_document_controller_(nullptr),
     image_document_controller_(nullptr)
#ifdef SHOW_XCSD
     ,xcsd_image_(nullptr)
#endif
{

}


void DHAX_Main_Window_Controller::show_video(QString file_path)
{
//? application_controller_->play_video(file_path);
 application_controller_->play_video(DHAX_Video_Player_Dialog::No_Annotations, file_path);
}


void DHAX_Main_Window_Controller::show_annotation_comments(DHAX_Annotation_Instance* dai)
{
 QString text = dai->comment(); //application_main_window_, ?
 QMessageBox_exec_information(dai->scoped_identifiers_to_string(),
   dai->comment());
}


void DHAX_Main_Window_Controller::init_image_scene_item(DHAX_Image_Scene_Item* si)
{
 image_scene_item_ = si;

 application_controller_->init_image_scene_item(si);

 si->set_meshlab_import_count(application_main_window_->
   main_window_data()->meshlab_integration()->meshlab_import_count());

 si->set_freecad_import_count(application_main_window_->
   main_window_data()->freecad_integration()->freecad_import_count());

// application_controller_

//?
// si->set_freecad_import_count(application_main_window_->
//   main_window_data()->freecad_integration()->freecad_import_count());


//?
// image_scene_item_->setGeometry(0,0,0,0);
// image_scene_item_->setObjectName(QString::fromUtf8("ImageDisplayWidget"));
// // //


 //image_scene_item_->self_connect()

// image_scene_item_->connect(image_scene_item_,SIGNAL(save_notation_requested(bool)),
//   main_window_receiver_, SLOT(handle_save_notation_requested(bool)));

// image_scene_item_->connect(image_scene_item_,SIGNAL(convert_notation_requested()),
//   main_window_receiver_, SLOT(handle_convert_notation_requested()));

// image_scene_item_->connect(image_scene_item_,SIGNAL(polygon_save_notation_requested()),
//   main_window_receiver_, SLOT(handle_polygon_save_notation_requested()));
// image_scene_item_->connect(image_scene_item_,SIGNAL(polygon_complete_and_save_notation_requested()),
//   main_window_receiver_, SLOT(handle_polygon_complete_and_save_notation_requested()));

// image_scene_item_->self_connect(SIGNAL(complete_polygon_requested(call_Stamp_u2)),
//   main_window_receiver_, SLOT(handle_complete_polygon(call_Stamp_u2)));

 _self_connect_(image_scene_item_ ,complete_polygon_requested)
   _to_bind_0 (with_callstamp) (main_window_receiver_ ,handle_complete_polygon);

// image_scene_item_->self_connect(SIGNAL(get_annotation_comments_requested(DHAX_Annotation_Instance*)),
//   main_window_receiver_, SLOT(handle_get_annotation_comments(DHAX_Annotation_Instance*)));

 _self_connect_(image_scene_item_ ,get_annotation_comments_requested)
   _to_bind_0 (with_callstamp) (main_window_receiver_ ,handle_get_annotation_comments);


// image_scene_item_->self_connect(SIGNAL(meshlab_import_info_requested(call_Stamp_u2)),
//   main_window_receiver_, SLOT(handle_meshlab_import_info(call_Stamp_u2)));
   //show_meshlab_import_info

 _self_connect_(image_scene_item_ ,meshlab_import_info_requested)
   _to_bind_0 (with_callstamp) (main_window_receiver_ ,handle_meshlab_import_info);



// image_scene_item_->self_connect(SIGNAL(freecad_import_info_requested(call_Stamp_u2)),
//   main_window_receiver_, SLOT(handle_freecad_import_info(call_Stamp_u2)));

 _self_connect_(image_scene_item_ ,freecad_import_info_requested)
   _to_bind_0 (with_callstamp) (main_window_receiver_ ,handle_freecad_import_info);


// image_scene_item_->self_connect(SIGNAL(draw_bezier_requested(call_Stamp_u2)),
//   main_window_receiver_,
//   SLOT(handle_draw_bezier(call_Stamp_u2)));


 _self_connect_(image_scene_item_ ,draw_bezier_requested)
   _to_bind_0 (with_callstamp) (main_window_receiver_ ,handle_draw_bezier);



// image_scene_item_->self_connect(SIGNAL(draw_cubic_path_requested(call_Stamp_u2)),
//   main_window_receiver_,
//   SLOT(handle_draw_cubic_path(call_Stamp_u2)));

 _self_connect_(image_scene_item_ ,draw_cubic_path_requested)
   _to_bind_0 (with_callstamp) (main_window_receiver_ ,handle_draw_cubic_path);



// image_scene_item_->self_connect(SIGNAL(draw_quad_path_requested(call_Stamp_u2)),
//   main_window_receiver_,
//   SLOT(handle_draw_quad_path(call_Stamp_u2)));


 _self_connect_(image_scene_item_ ,draw_quad_path_requested)
   _to_bind_0 (with_callstamp) (main_window_receiver_ ,handle_draw_quad_path);


// image_scene_item_->self_connect(SIGNAL(meshlab_reset_requested()),
//   main_window_receiver_,
//   SLOT(send_meshlab_reset()));

// image_scene_item_->self_connect(SIGNAL(freecad_import_info_requested()),
//   main_window_receiver_,
//   SLOT(show_freecad_import_info()));


}



void DHAX_Main_Window_Controller::init_polyline()
{
 display_image_data_->init_polyline();
}


void DHAX_Main_Window_Controller::complete_polygon()
{
 display_image_data_->complete_polygon();
 image_scene_item_->update();

// DHAX_Drawn_Shape* dds = display_image_data_->current_drawn_shape();
// if(!dds)
//   return;
// dds->points().push_back(dds->points().first());

}


#include "libspline/aaCurve.h"
#include "libspline/spline.h"

void DHAX_Main_Window_Controller::draw_demo_bezier()
{
 DHAX_Drawn_Shape* cdds = display_image_data_->active_curve();
 if(!cdds)
   return;

 QPoint _p1 = cdds->points()[0];
 QPoint _p2 = cdds->points()[1];
 QPoint _mid = cdds->extra_points()[0];


 QPoint p1 = image_viewer_->control_center(1).toPoint();
 QPoint mid = image_viewer_->control_center(2).toPoint();
 QPoint p2 = image_viewer_->control_center(3).toPoint();

 qDebug() << "_p1 = " << _p1;
 qDebug() << "_p2 = " << _p2;
 qDebug() << "_mid = " << _mid;

 qDebug() << "p1 = " << p1;
 qDebug() << "p2 = " << p2;
 qDebug() << "mid = " << mid;

 std::vector<aaAaa::aaSpline> splines;

 aaAaa::aaSpline spline;
 spline.addKnots(aaAaa::aaPoint(p1.x(), p1.y()));
 spline.addKnots(aaAaa::aaPoint(mid.x(), mid.y()));
 spline.addKnots(aaAaa::aaPoint(p2.x(), p2.y()));

 aaAaa::aaCurvePtr pspline = aaAaa::aaCurveFactory::createCurve(spline);

 aaAaa::aaSpline::KnotsList::iterator beg = spline.knots.begin();
 aaAaa::aaSpline::KnotsList::reverse_iterator rbeg = spline.knots.rbegin();

 static const int Y_FACTOR = 1;
 double m_deltaT = 0.1;

 double t = (*beg).t;
 double v = (*beg).y;
 //glVertex3f(t, v * Y_FACTOR, Z_VALUE);
 t += m_deltaT;

 while(t < (*rbeg).t - m_deltaT){
     pspline->getValue(t, v);
     if(spline.bLimited){
//         if(v > m_spline_data.limit_top)
//             v = m_spline_data.limit_top;
//         else if(v < m_spline_data.limit_bottom)
//             v = m_spline_data.limit_bottom;
     }

//     qDebug() << "t = " << t;
//     qDebug() << "v = " << v;

     QPoint ptv(t, v);
     image_viewer_->draw_circle(ptv, 2, Qt::cyan, Qt::transparent, 0);

//     glVertex3f(t, v * Y_FACTOR, Z_VALUE);
     t += m_deltaT;
 }

 t = (*rbeg).t;
 v = (*rbeg).y;


 {
  aaAaa::aaSpline spline;
  spline.addKnots(aaAaa::aaPoint(_p1.x(), _p1.y()));
  spline.addKnots(aaAaa::aaPoint(_mid.x(), _mid.y()));
  spline.addKnots(aaAaa::aaPoint(_p2.x(), _p2.y()));

  aaAaa::aaCurvePtr pspline = aaAaa::aaCurveFactory::createCurve(spline);

  aaAaa::aaSpline::KnotsList::iterator beg = spline.knots.begin();
  aaAaa::aaSpline::KnotsList::reverse_iterator rbeg = spline.knots.rbegin();

  static const int Y_FACTOR = 1;
  double m_deltaT = 0.1;

  double t = (*beg).t;
  double v = (*beg).y;
  //glVertex3f(t, v * Y_FACTOR, Z_VALUE);
  t += m_deltaT;

  static u1 color_min = 100;
  static u1 color_max = 210;
  static u1 color_inc = color_max - color_min;

  double c = 100;

  double max = (*rbeg).t - m_deltaT;
  double color_change = max - t;
  double increments = color_change / m_deltaT;
  double increment = color_inc / increments;

  qDebug() << "inc = " << increment;

  while(t < (*rbeg).t - m_deltaT){
      pspline->getValue(t, v);
      if(spline.bLimited){
 //         if(v > m_spline_data.limit_top)
 //             v = m_spline_data.limit_top;
 //         else if(v < m_spline_data.limit_bottom)
 //             v = m_spline_data.limit_bottom;
      }

 //     qDebug() << "t = " << t;
 //     qDebug() << "v = " << v;


      QPoint ptv(t, v);
      image_viewer_->draw_circle(ptv, 2, QColor(c, c + 40, 200, 140), Qt::transparent, 0);

      c += increment;

 //     glVertex3f(t, v * Y_FACTOR, Z_VALUE);
      t += m_deltaT;
  }

  t = (*rbeg).t;
  v = (*rbeg).y;
 }
}


void DHAX_Main_Window_Controller::draw_demo_cubic()
{
 DHAX_Drawn_Shape* cdds = display_image_data_->active_curve();
 if(!cdds)
   return;

 QPoint _p1 = cdds->points()[0];
 QPoint _p2 = cdds->points()[1];
 QPoint _mid = cdds->extra_points()[0];

 QPoint p1 = image_viewer_->control_center(1).toPoint();
 QPoint mid = image_viewer_->control_center(2).toPoint();
 QPoint p2 = image_viewer_->control_center(3).toPoint();

 image_viewer_->draw_circle(p1, 2, Qt::cyan, Qt::transparent, 0);
 image_viewer_->draw_circle(mid, 2, Qt::cyan, Qt::transparent, 0);
 image_viewer_->draw_circle(p2, 2, Qt::cyan, Qt::transparent, 0);

 QPainterPath path;

// display_image_->scrolled_image_pixmap_item()->mapToScene()

 path.moveTo(p1);
 path.cubicTo(mid, mid, p2);

 QGraphicsPathItem* ppi = image_viewer_->scrolled_image_scene()->addPath(path,
   QPen(QColor(25, 79, 106), 1, Qt::SolidLine,
   Qt::FlatCap, Qt::MiterJoin), QBrush(QColor(5, 122, 163, 100)));

 ppi->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
 ppi->setParentItem(image_viewer_->scrolled_image_pixmap_item()); //image_scene_item_->this_proxy_widget()->graphicsItem());

    //image_viewer_->scrolled_image_pixmap_item());

}


void DHAX_Main_Window_Controller::draw_demo_quad()
{
 DHAX_Drawn_Shape* cdds = display_image_data_->active_curve();
 if(!cdds)
   return;

//?
// QPoint _p1 = cdds->points()[0];
// QPoint _p2 = cdds->points()[1];
// QPoint _mid = cdds->extra_points()[0];

 QPoint p1 = image_viewer_->control_center(1).toPoint();
 QPoint mid = image_viewer_->control_center(2).toPoint();
 QPoint p2 = image_viewer_->control_center(3).toPoint();

 image_viewer_->draw_circle(p1, 2, Qt::cyan, Qt::transparent, 0);
 image_viewer_->draw_circle(mid, 2, Qt::cyan, Qt::transparent, 0);
 image_viewer_->draw_circle(p2, 2, Qt::cyan, Qt::transparent, 0);

 QPainterPath path;

// display_image_->scrolled_image_pixmap_item()->mapToScene()

 path.moveTo(p1);
 path.quadTo(mid, p2);

 QGraphicsPathItem* ppi = image_viewer_->scrolled_image_scene()->addPath(path,
   QPen(QColor(79, 106, 25), 1, Qt::SolidLine,
   Qt::FlatCap, Qt::MiterJoin), QBrush(QColor(39, 122, 163, 100)));

 ppi->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
 ppi->setParentItem(image_viewer_->scrolled_image_pixmap_item());

}

void DHAX_Main_Window_Controller::check_init_image_document_controller()
{
 if(!image_document_controller_)
 {
  image_document_controller_ = new Image_Document_Controller;
 }
}

void DHAX_Main_Window_Controller::check_init_pdf_document_controller()
{
 if(!pdf_document_controller_)
 {
  pdf_document_controller_ = new PDF_Document_Controller;
  pdf_document_controller_->set_page_and_search_frame(page_and_search_frame_);

  _self_connect_(page_and_search_frame_ ,page_select_requested)
    to_lambda[this](u4 page)
  {
   pdf_document_controller_->switch_to_page(page);
   reinit_pdf_page_view(page);
  // display_image_data_->unset_multi_draw();
  };

 }
}

void DHAX_Main_Window_Controller::delayed_image_viewer_recenter_scroll_top_left()
{
 QTimer::singleShot(0, [this]
 {
  image_viewer_->recenter_scroll_top_left();
 });
}

void DHAX_Main_Window_Controller::reinit_pdf_page_view(u4 page)
{
 init_pdf_page_view();
}

void DHAX_Main_Window_Controller::init_pdf_page_view()
{
 image_viewer_->load_pdf_pixmap(pdf_document_controller_); //->pixmap());
 delayed_image_viewer_recenter_scroll_top_left();
}

void DHAX_Main_Window_Controller::load_pdf()
{
 QString ws =  ROOT_FOLDER "/../pdf";

 QString filters = "PDF Files (*.pdf)";

 QString file_path = QFileDialog::getOpenFileName(application_main_window_, "Open PDF", ws, filters);

 if(file_path.isEmpty())
   return;

 check_init_pdf_document_controller();

 pdf_document_controller_->load_document(file_path);

 QPair dpis {image_viewer_->physicalDpiX(), image_viewer_->physicalDpiY()};
 pdf_document_controller_->load_page(dpis);

 init_pdf_page_view();

 application_controller_->application_state()->flags.pdf_mode = true;
}


#ifdef XCSD
void DHAX_Main_Window_Controller::show_fb_gradient_trimap(bool autoset)
{
 if(!image_scene_item_)
 {
//

//  QMessageBox msg;

//  sigma(&msg)->init_information("XCSD Scene Needed",
//                               "Please load an image as an XCSD scene first.");

////  QMessageBox_init_information(msg, "XCSD Scene Needed",
////    "Please load an image as an XCSD scene first.");

//  msg.exec();

    QMessageBox_exec_information("XCSD Scene Needed",
      "Please load an image as an XCSD scene first.");


//  QMessageBox msg(QMessageBox::Question, "Background and/or Foreground Poles Have Not Been Set",
//    "Foreground/Background functionality requires the two poles to be set from an XCSD Image.",
//    QMessageBox::Ok);
//  msg.button(QMessageBox::Ok)->setObjectName("Ok");
//  msg.setStyleSheet(qmessagebox_button_style_sheet());

//  msg.exec();


//  QMessageBox::information(application_main_window_, "XCSD Scene Needed",
//    "Please load an image as an XCSD scene first");
//  return;

//  QMessageBox msg(QMessageBox::Question, "No image loaded",
//    "Load an image before invoking foreground/background functionality.",
//    QMessageBox::Ok);

//  msg.button(QMessageBox::Ok)->setObjectName("Ok");

//  msg.setStyleSheet(qmessagebox_button_style_sheet());

//  msg.exec();

  return;
 }

 if(!xcsd_image_)
 {
//  QMessageBox msg;
//  QMessageBox_init_question(msg, "Load XCSD Scene",
//    "Histogram data requires an XCSD image format.  Proceed to load the current image as an XCSD scene?");

  //  QMessageBox msg(QMessageBox::Question, "Load XCSD Scene",
//    "Histogram data requires an XCSD image format.  Proceed to load the current image as an XCSD scene?",
//    QMessageBox::Yes | QMessageBox::No);

//  msg.button(QMessageBox::Yes)->setObjectName("Yes");
//  msg.button(QMessageBox::No)->setObjectName("No");

//  msg.setStyleSheet(qmessagebox_button_style_sheet());

  int response = QMessageBox_exec_question("Load XCSD Scene",
                                             "Histogram data requires an XCSD image format.  Proceed to load the current image as an XCSD scene?");


  // QMessageBox::question(application_main_window_, "Missing histogram data",
  // "Histogram data needs to be calculated first.  Proceed with the calculation?")

  if(response == QMessageBox::Yes)
  {
   show_xcsd_scene();
   //calculate_local_color_histograms();
  }
  else
    return;

  //xcsd_image_

 }

 if(autoset)
   xcsd_image_->autoset_fb_poles();

 else if( (image_document_controller_->marked_background_pole() == (u2) -1)
    || (image_document_controller_->marked_foreground_pole() == (u2) -1) )
 {
  //QMessageBox msg;
  QMessageBox_exec_information("Background and/or Foreground Poles Have Not Been Set",
    "Foreground/Background functionality requires the two poles to be set from an XCSD Image.");

//  QMessageBox msg(QMessageBox::Question, "Background and/or Foreground Poles Have Not Been Set",
//    "Foreground/Background functionality requires the two poles to be set from an XCSD Image.",
//    QMessageBox::Ok);
//  msg.button(QMessageBox::Ok)->setObjectName("Ok");
//  msg.setStyleSheet(qmessagebox_button_style_sheet());

//  msg.exec();

  return;
 }

 //qDebug() << "show_fb_gradient_trimap";

// QFileInfo qfi(current_image_file_path_);

 QDir qdir(base_temp_folder_ + class_name_folder("/_proc") + "/trimap");

 qdir.mkpath(".");
 QString path = qdir.absolutePath() + "/fg-%1.png";
 qdir.mkdir("test");
 QString fpath = qdir.absoluteFilePath("test");

 if(autoset)
   xcsd_image_->save_fb_gradient_trimap(path, fpath);

// xcsd->check_set_fb_gradient_trimap_to_channels();

// qDebug() << "Autoset background pole: " << xcsd->background_pole() <<
//             " and foreground pole: " << xcsd->foreground_pole();

 else
   xcsd_image_->save_fb_gradient_trimap({image_document_controller_->marked_background_pole(),
     image_document_controller_->marked_foreground_pole()}, path, fpath);

 application_controller_->view_trimap(path);

}
#endif//def XCSD

void DHAX_Main_Window_Controller::check_reset_base_temp_folder()
{
 base_temp_folder_ = DEFAULT_DHAX_TEMP_FOLDER;
 if(base_temp_folder_.isEmpty())
 {
  QFileInfo qfi(current_image_file_path_);
  base_temp_folder_ = qfi.absolutePath();
 }
}

#ifdef USE_XCSD
void DHAX_Main_Window_Controller::save_local_color_histograms()
{
 qDebug() << "save local histograms ...";

 //QFileInfo qfi(current_image_file_path_);
 QDir qdir(base_temp_folder_ + class_name_folder("/_info"));
 qdir.mkdir("histpgra,s");
 QString path = qdir.absoluteFilePath("hist") + "/%1-%2.png";
 // //?
}

void DHAX_Main_Window_Controller::calculate_local_color_histograms()
{
 qDebug() << "local histograms ...";

 //xcsd_image_->f

 if(!image_scene_item_)
 {
//  QMessageBox::information(application_main_window_, "XCSD Scene Needed",
//    "Please load an image as an XCSD scene first");
//  return;

  //QMessageBox msg;
  QMessageBox_exec_information("No image loaded", "Load an image before invoking histogram functionality.");

//  (QMessageBox::Question, "No image loaded",
//    "Load an image before invoking histogram functionality.",
//    QMessageBox::Ok);

//  msg.button(QMessageBox::Ok)->setObjectName("Ok");

//  msg.setStyleSheet(qmessagebox_button_style_sheet());

//  msg.exec();

  return;
 }

 bool newly_loaded = false;

 if(!xcsd_image_)
 {
//  QMessageBox msg;
  int response = QMessageBox_exec_question("Load XCSD Scene",
    "Histogram data requires an XCSD image format.  Proceed to load the current image as an XCSD scene?");

//  QMessageBox msg(QMessageBox::Question, "Load XCSD Scene",
//    "Histogram data requires an XCSD image format.  Proceed to load the current image as an XCSD scene?",
//    QMessageBox::Yes | QMessageBox::No);

//  msg.button(QMessageBox::Yes)->setObjectName("Yes");
//  msg.button(QMessageBox::No)->setObjectName("No");

//  msg.setStyleSheet(qmessagebox_button_style_sheet());

//  int response = msg.exec();

  // QMessageBox::question(application_main_window_, "Missing histogram data",
  // "Histogram data needs to be calculated first.  Proceed with the calculation?")

  if(response == QMessageBox::Yes)
  {
   show_xcsd_scene();
   //calculate_local_color_histograms();
  }
  else
    return;

  newly_loaded = true;

  //xcsd_image_

 }


 QVector<Local_Histogram_Data>* data = xcsd_image_->calculate_local_histograms(); //path);
 image_document_controller_->set_local_histogram_data(data);

// xcsd_image_->save_local_histogram_vector_to_folder(*histogram_data, path);
// u2 fti = (u2) xcsd_image_->tierbox_index_to_full_tier_index({0, 21});
// const Local_Histogram_Data& lhd = histogram_data->at(fti);
// XCSD_Local_Histogram_Dialog* dlg = new XCSD_Local_Histogram_Dialog(application_main_window_,
//   {lhd.largest_group_total(), lhd.largest_bin()}, &lhd.combined_map());

// dlg->setModal(false);
// dlg->show();

 if(newly_loaded)
 {
  //QMessageBox msg;
  QMessageBox_exec_information("Action Completed", "All XCSD and histogram data has been calculated.");
  //msg.exec();
 }

}

void DHAX_Main_Window_Controller::show_local_color_histogram(rc2 rc)
{
 if(!xcsd_image_)
 {
//  QMessageBox::information(application_main_window_, "XCSD Scene Needed",
//    "Please load an image as an XCSD scene first");
//  return;

//  QMessageBox msg;

  QMessageBox_exec_information("Missing XCSD Scene",
    "The XCSD Scene was not found; try reloading.");

//  msg.button(QMessageBox::Ok)->setObjectName("Ok");

//  msg.setStyleSheet(qmessagebox_button_style_sheet());

 // msg.exec();

  return;
 }

 if(!image_document_controller_->local_histogram_data())
 {
//  QMessageBox msg;
  int response = QMessageBox_exec_question("Missing histogram data",
    "Histogram data needs to be calculated first.  Proceed with the calculation?");

//  QMessageBox msg(QMessageBox::Question, "Missing histogram data",
//    "Histogram data needs to be calculated first.  Proceed with the calculation?",
//    QMessageBox::Yes | QMessageBox::No);

//  msg.button(QMessageBox::Yes)->setObjectName("Yes");
//  msg.button(QMessageBox::No)->setObjectName("No");

//  msg.setStyleSheet(qmessagebox_button_style_sheet());

//  int response = msg.exec();

  // QMessageBox::question(application_main_window_, "Missing histogram data",
  // "Histogram data needs to be calculated first.  Proceed with the calculation?")

  if(response == QMessageBox::Yes)
  {
   calculate_local_color_histograms();
  }
  else
    return;


  //xcsd_image_

 }

 u2 fti = (u2) xcsd_image_->tierbox_index_to_full_tier_index(rc);
 const Local_Histogram_Data& lhd =
   image_document_controller_->local_histogram_data()->at(fti);
 XCSD_Local_Histogram_Dialog* dlg = new XCSD_Local_Histogram_Dialog(application_main_window_,
   {lhd.largest_group_total(), lhd.largest_bin()}, lhd.get_ref_color(), &lhd.combined_map());

 _self_connect_(dlg ,mark_global_foreground_pole_requested)
  to_lambda[this] (u2 code)
  {
   image_document_controller_->set_marked_foreground_pole(code);
  };

 _self_connect_(dlg ,mark_global_background_pole_requested)
  to_lambda[this] (u2 code)
  {
   image_document_controller_->set_marked_background_pole(code);
  };

 dlg->setModal(false);
 dlg->show();

}

void DHAX_Main_Window_Controller::check_init_xcsd_image()
{
 if(xcsd_image_)
   return;

 xcsd_image_ = new XCSD_Image;

 //QFileInfo qfi(current_image_file_path_);
 QDir qdir(base_temp_folder_ + class_name_folder("/_proc") + "/xcsd");

 QString px = qdir.filePath("px");
 QString px0 = qdir.filePath("px/0");
 QString px1 = qdir.filePath("px/1");
 QString px2 = qdir.filePath("px/2");

 qdir.mkpath("px");
 qdir.mkpath("px/0");
 qdir.mkpath("px/1");
 qdir.mkpath("px/2");

 //xcsd.load_image(ROOT_FOLDER "/../pics/angle.jpg");
 xcsd_image_->load_image(current_image_file_path_);

// qDebug() << xcsd.

 xcsd_image_->init_geometry();
 XCSD_Image_Geometry& xcsg = xcsd_image_->geometry();

 xcsg.init_tier_counts(XCSD_Image_Geometry::TierGrid_Preferances::Minimize_Outer_Tiers);

// xcsg.draw_tier_summary(QString(ROOT_FOLDER "/../test/t%1x%2.png")
//     .arg(xcsg.total_size().width).arg(xcsg.total_size().height),
//   QString(ROOT_FOLDER "/../test/t%1x%2-seq.png")
//     .arg(xcsg.total_size().width).arg(xcsg.total_size().height),
//                        3.3, 8);

 xcsg.init_outer_ring_positions();

 xcsd_image_->init_pixel_data(px); //ROOT_FOLDER "/../test/ukraine");

 xcsd_image_->init_tierboxes();


 xcsd_image_->draw_tierboxes_to_folder(px1, &xcsd_paths_);

 xcsd_image_->init_outer_ring_info();

 xcsd_image_->save_full_tier_image(px1 + "/t1.png",
   XCSD_Image::Save_QRgb, px2);



}


void DHAX_Main_Window_Controller::show_xcsd_scene()
{
 if(current_image_file_path_.isEmpty())
 {
  load_image();

  if(current_image_file_path_.isEmpty())
    return;
 }

 check_reset_base_temp_folder();

 check_init_xcsd_image();

 XCSD_Image_Geometry& xcsg = xcsd_image_->geometry();

 qDebug() << current_image_file_path_;

 image_viewer_->get_graphics_frame()->show_info(QString("Loaded image (as XCSD scene): %1")
   .arg(current_image_file_path_));


 //XCSD_Image xcsd;

 image_scene_item_->hide_for_xcsd(); //setVisible(false);

 u1 lft = xcsg.horizontal_outer_sizes().left + image_scene_item_->pos().x();
 u1 top = xcsg.vertical_outer_sizes().top + image_scene_item_->pos().y();


 for(u2 r = 0; r < xcsd_paths_.n_rows(); ++r)
  for(u2 c = 0; c < xcsd_paths_.n_cols(); ++c)
  {
   QString qs = xcsd_paths_[r + 1][c + 1];
   image_viewer_->scrolled_image_scene()->add_tierbox_pixmap(qs, {r, c},
     lft + c * 27, top + r * 27);
  }


 QVector<XCSD_Outer_Ring_Info>& outer_ring_info = *xcsd_image_->outer_ring_info();

// int i = 0;

 for(const XCSD_Outer_Ring_Info& xori : outer_ring_info)
 {
  image_viewer_->scrolled_image_scene()->add_outer_pixmap(xori, image_scene_item_->pos());

//  ++i;

//  if(i == 1)
//    break;




 }

 //QVector<QImage> images;

 //Mat2d<QString>
}
#endif//def USE_XCSD


void DHAX_Main_Window_Controller::load_bookmarked_image()
{
 QString path = application_controller_->bookmarked_image_path();
 if(!path.isEmpty())
   load_image(path);
}

void DHAX_Main_Window_Controller::load_image()
{
 //
 //QString ws =  ROOT_FOLDER "/../pics";
 // //  temporary ...
 //QString ws =  ROOT_FOLDER "/../pics/ukraine";

  QString ws =  ROOT_FOLDER "/../dev/dhax-stats/test-combined";

 QString filters = "Images (*.jpg *.jpeg *.png *.bmp *.webp)";

// QFileDialog qdialog;
// QString file_path = qdialog.getOpenFileName(application_main_window_, "Open Image", ws, filters);

 QString file_path = QFileDialog::getOpenFileName(application_main_window_, "Open Image", ws, filters);

 if(!file_path.isNull())
 {
  load_image(file_path);
 }

}

void DHAX_Main_Window_Controller::load_image(QString file_path)
{
 current_image_file_path_ = file_path;
 display_image_data_->setNameSelected(true);

 shape_select_frame_->update_image_path(file_path);

 zoom_frame_->reset_with_image_data(&current_image_file_path_);

 check_init_image_document_controller();

 image_document_controller_->set_current_file_path(current_image_file_path_);

 image_viewer_->load_image(current_image_file_path_, image_document_controller_);

// display_->update();
// display_->repaint();

 init_image_scene_item(image_viewer_->image_scene_item());


 application_controller_->application_state()->flags.image_mode = true;

 delayed_image_viewer_recenter_scroll_top_left();

 image_viewer_->get_graphics_frame()->show_info(QString("Loaded image: %1")
   .arg(file_path));


 // //  400 limit for initial height expansion ...
 wh2 dimensions = image_viewer_->dimensions_maxed(400);

 application_main_window_->resize(application_main_window_->width(),
   dimensions.height + page_and_search_frame_->height());


}


void DHAX_Main_Window_Controller::take_screenshot()
{
 QScreen* screen = QGuiApplication::primaryScreen();
 if (!screen)
   return;

 QTimer::singleShot(10000, [=]
 {
  QPixmap pixmap = screen->grabWindow(application_main_window_->winId());
  QString path = SCREENSHOTS_FOLDER "/dhax.png";
  qDebug() << "Saving to path: " << path;

  QFile file(path);
  if(file.open(QIODevice::WriteOnly))
  {
   pixmap.save(&file, "PNG");
  }
 });

}

