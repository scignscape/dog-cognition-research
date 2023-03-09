
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


// //  this has to be included before
 //    the header because of _flags conflict
#include "stats/dhax-stat-assessment.h"


#include "dhax-image-scene-item.h"


#include <QMessageBox>
#include <QScrollBar>
#include <QGraphicsProxyWidget>
#include <QMenu>

#include "main-window/dhax-main-window.h"

#include "aforms/multistep-annotation-base.h"

#include "dhax-graphics-view.h"

#include "dhax-graphics-scene.h"

#include "dhax-mouse-interaction-data.h"


template<>
void DHAX_Image_Scene_Item::handle_mouse_event<
DHAX_Image_Scene_Item::Mouse_Event_Modes::Left_Edit>(QMouseEvent* mev, n8 mode_data_request)
{

}

template<>
void DHAX_Image_Scene_Item::handle_mouse_event<
DHAX_Image_Scene_Item::Mouse_Event_Modes::Left_Move>(QMouseEvent* mev, n8 mode_data_request)
{
 if(current_multistep_annotation_)
  current_multistep_annotation_->fulfill_left_move(mev, mode_data_request);
}

template<>
void DHAX_Image_Scene_Item::handle_mouse_event<
DHAX_Image_Scene_Item::Mouse_Event_Modes::Left_Resume>(QMouseEvent* mev, n8 mode_data_request)
{
 if(current_multistep_annotation_)
 {
  current_multistep_annotation_->fulfill_left_resume(mev, mode_data_request);
 }
}



void DHAX_Image_Scene_Item::_left_init(const QPoint& pos)
{
 if(data_->multi_draw)
 {
  data_->check_hold_drawn_shape();
 }
 else
 {
  data_->check_reset_drawn_shape();
  //  if(data_->check_reset_drawn_shape())
  //    update();
 }

 //?
 // if(!data_->drawingSquareEnabled_ && !data_->drawingEllipseEnabled_ && !data_->drawingPolygonEnabled_)
 //   QMessageBox::warning(this,"Warning!","Please select the shape's form");
 // else
 // {
 //  if(!data_->nameSelected_)
 //   data_->nameSelected_ = true;
 //  if(!data_->nameSelected_)
 //   QMessageBox::warning(this,"Warning!","Please select an instance name");
 //  else
 //  {
 //   data_->shapeID_.clear();

 DHAX_Drawn_Shape::Shape_Kinds sk = data_->current_enabled_shape_kind();

 switch(sk)
 {
 default: break;
 case DHAX_Drawn_Shape::Shape_Kinds::Ellipse:
 case DHAX_Drawn_Shape::Shape_Kinds::Rectangle:
 {
  // //  don't need to test for this here ...
  //if(data_->mStartPoint_.isNull())
  data_->mStartPoint_ = pos; //mev->pos();
  data_->mEndPoint_ = pos; //mev->pos();
  data_->isMoving_ = true;
  update();
 }
  break;
 case DHAX_Drawn_Shape::Shape_Kinds::Non_Regular_Polygon:
 {
  data_->point_pairs_.push_back({pos, pos}); //{mev->pos(), mev->pos()});
  data_->isMoving_ = true;
  update();
 }
  break;
 }
}

template<>
void DHAX_Image_Scene_Item::handle_mouse_event<
DHAX_Image_Scene_Item::Mouse_Event_Modes::Left_Init>(QMouseEvent* mev, n8 mode_data_request)
{
 if(current_multistep_annotation_)
  current_multistep_annotation_->fulfill_left_init(mev, mode_data_request);

 //? _left_init(mev->pos());


 //qDebug() << "Left_Init ...";

}

void DHAX_Image_Scene_Item::_left_move_release(const QPoint& pos)
{
 // current_multistep_annotation_->fulfill_left_init(mev, mode_data_request);


 DHAX_Drawn_Shape::Shape_Kinds sk = data_->current_enabled_shape_kind();

 DHAX_Drawn_Shape* dds = data_->check_current_drawn_shape(); //get_current_drawn_shape_

 switch(sk)
 {
 default: break;

 case DHAX_Drawn_Shape::Shape_Kinds::Non_Regular_Polygon:
 {
  data_->point_pairs_.last().second = pos;
  data_->isMoving_ = false;
 }
  break;

 case DHAX_Drawn_Shape::Shape_Kinds::Ellipse:
 case DHAX_Drawn_Shape::Shape_Kinds::Rectangle:
 {
  dds->points() << data_->mStartPoint_ << pos;
  data_->isMoving_ = false;
 }
  break;
 }
}

template<>
void DHAX_Image_Scene_Item::handle_mouse_event<
DHAX_Image_Scene_Item::Mouse_Event_Modes::Left_Move_Release>(QMouseEvent* mev, n8 mode_data_request)
{
 if(current_multistep_annotation_)
  current_multistep_annotation_->fulfill_left_move_release(mev, mode_data_request);
 //_left_move_release(mev->pos());
}

// //   right click temp release is like releasing the
//     left button and then immediately pressing it again ...
template<>
void DHAX_Image_Scene_Item::handle_mouse_event<
DHAX_Image_Scene_Item::Mouse_Event_Modes::Right_Click_Temp_Release>(QMouseEvent* mev, n8 mode_data_request)
{
 _left_move_release(mev->pos());
 _left_init(mev->pos());
}

// DHAX_Drawn_Shape::Shape_Kinds sk = data_->current_enabled_shape_kind();

// DHAX_Drawn_Shape* dds = data_->check_current_drawn_shape(); //get_current_drawn_shape_

// switch(sk)
// {
// default: break;

// case DHAX_Drawn_Shape::Shape_Kinds::Non_Regular_Polygon:
//  {
//   data_->point_pairs_.last().second = mev->pos();
//   data_->isMoving_ = false;
//  }
//  break;

// case DHAX_Drawn_Shape::Shape_Kinds::Ellipse:
// case DHAX_Drawn_Shape::Shape_Kinds::Rectangle:
//  {
//   dds->points() << data_->mStartPoint_ << mev->pos();
//   data_->isMoving_ = false;
//  }
//  break;
// }
//}


template<>
void DHAX_Image_Scene_Item::handle_mouse_event<
DHAX_Image_Scene_Item::Mouse_Event_Modes::Left_Edit_Release>(QMouseEvent* mev, n8 mode_data_request)
{

}

template<>
void DHAX_Image_Scene_Item::handle_mouse_event<
DHAX_Image_Scene_Item::Mouse_Event_Modes::Right_Edit>(QMouseEvent* mev, n8 mode_data_request)
{

}

template<>
void DHAX_Image_Scene_Item::handle_mouse_event<
DHAX_Image_Scene_Item::Mouse_Event_Modes::Right_Move>(QMouseEvent* mev, n8 mode_data_request)
{

}

template<>
void DHAX_Image_Scene_Item::handle_mouse_event<
DHAX_Image_Scene_Item::Mouse_Event_Modes::Right_Init>(QMouseEvent* mev, n8 mode_data_request)
{

}



template<>
void DHAX_Image_Scene_Item::handle_mouse_event<
DHAX_Image_Scene_Item::Mouse_Event_Modes::Right_Click_Iso>(QMouseEvent* mev,
                                                           n8 mode_data_request)
{
 QMenu* menu = new QMenu(nullptr);
 menu->setAttribute(Qt::WA_DeleteOnClose);

 QPoint pos = this_proxy_widget_->mapToScene(mev->pos()).toPoint();
 QPoint pos1 = containing_image_view_->mapFromScene(pos);
 QPoint pos2 = containing_image_view_->viewport()->mapToGlobal(pos1);

#ifdef USE_OpenCV
 if(current_transforms_map_)
 {
  QMenu* submenu = menu->addMenu("Sort Keypoints");

  QStringList keys = current_transforms_map_->keys();

  // //  temp for demo ..
  keys.prepend("AKAZE");
  keys.prepend("SIFT");
  keys.append("ORB");
  keys.append("SURF");
  keys.append("USURF");

    // make_0d_uxproc(SURF)"

  for(QString algorithm : keys) // current_transforms_map_->keys())
  {
   submenu->addAction(algorithm, [algorithm, this]()
   {
    std::shared_ptr<DHAX_Stat_Assessment> stat = current_transforms_map_->value(algorithm);

    // //  todo: this shouldn't be called from here directly
     //    better to emit a signal and call from a controller ...
    stat->run_classifier_transform();
   });
  }
 }
#else
 if(false) ;
#endif//def USE_OpenCV
 else
 {
  //if(current_mouse_interaction_data_->flags.)
  if(context_menu_prep_state_.flags.pending_annotation_confirm)
  {
   menu->addAction("Confirm Annotation", [this]
   {
   });

   menu->addAction("Cancel Annotation", [this]
   {
   });

   menu->addAction("Generate NTXH", [this]
   {
    generate_annotation_ntxh();
   });

   menu->addAction("Measurements ...", [this, &pos2]
   {
    show_annotation_measurements_dialog(pos2);
   });

  }

  DHAX_Drawn_Shape* ldds = data_->get_last_canceled_drawn_shape();

  if(ldds)
  {
   menu->addAction("Undo Cancel Notation", [this,ldds]
   {
    uncancel_notation(ldds);
   });
  }

  if(meshlab_import_count_ && *meshlab_import_count_)
  {
   menu->addAction("MeshLab Import Info", [this]
   {
    Q_EMIT meshlab_import_info_requested(NULL_CALL_STAMP);
   });

   menu->addAction("MeshLab Reset", [this]
   {
    Q_EMIT meshlab_reset_requested(NULL_CALL_STAMP);
   });
  }

  if(freecad_import_count_ && *freecad_import_count_)
  {
   menu->addAction("FreeCAD Import Info", [this]
   {
    Q_EMIT freecad_import_info_requested(NULL_CALL_STAMP);
   });

   menu->addAction("FreeCAD Reset", [this]
   {
    Q_EMIT freecad_reset_requested(NULL_CALL_STAMP);
   });
  }

  DHAX_Annotation_Instance* dai = get_annotation_comments();
  if(dai)
  {
   menu->addAction("Get Comments", [this, dai]
   {
    Q_EMIT get_annotation_comments_requested(dai);
   });
  }


  // //  point_pairs_ means a (presumptively non-regular) polygon
  if(!data_->point_pairs_.isEmpty())
  {
   menu->addAction("Complete Polygon", [this]
   {
    Q_EMIT complete_polygon_requested(NULL_CALL_STAMP);
   });

   menu->addAction("Save Notation", [this]
   {
    Q_EMIT polyline_save_notation_requested(false);
   });

   menu->addAction("Complete and Save", [this]
   {
    Q_EMIT polygon_complete_and_save_notation_requested(NULL_CALL_STAMP);
   });

   menu->addAction("Save Notation with Comment", [this]
   {
    Q_EMIT polyline_save_notation_requested(true);
   });

   menu->addAction("Complete and Save with Comment", [this]
   {
    Q_EMIT polygon_complete_and_save_notation_with_comment_requested(NULL_CALL_STAMP);
   });

   menu->addAction("Cancel Notation", [this]
   {
    cancel_notation();
    //   data_->check_clear_last_canceled_drawn_shapes();
    //   data_->cancel_current_drawn_shape();

    //   update();
   });

  }

  else if(data_->get_current_drawn_shape())
  {
   menu->addAction("Save Notation", [this]
   {
    //   qDebug() << "this = " << this;
    //   this->handle_save_notation_requested();
    Q_EMIT save_notation_requested(false);
    //   Q_EMIT onLineDraw({});
   });

   menu->addAction("Save Notation with Comment", [this]
   {
    Q_EMIT save_notation_requested(true);
   });

   menu->addAction("Convert Notation", [this]
   {
    Q_EMIT  convert_notation_requested(NULL_CALL_STAMP);
   });

   menu->addAction("Cancel Notation", [this]
   {
    cancel_notation();
    //   data_->check_clear_last_canceled_drawn_shapes();
    //   data_->cancel_current_drawn_shape();

    //   update();
   });
  }

  //??
  else
  {
   menu->addAction("Complete and Save", [this]
   {
    Q_EMIT polygon_complete_and_save_notation_requested(NULL_CALL_STAMP);
   });
  }

  if(data_->active_curve())
  {
   menu->addAction("Draw Bezier", [this]
   {
    Q_EMIT draw_bezier_requested(NULL_CALL_STAMP);
   });

   menu->addAction("Draw Cubic", [this]
   {
    Q_EMIT draw_cubic_path_requested(NULL_CALL_STAMP);
   });

   menu->addAction("Draw Quad", [this]
   {
    Q_EMIT draw_quad_path_requested(NULL_CALL_STAMP);
   });

   menu->addAction("Draw Arc", [this]
   {
    //Q_EMIT draw_quad_path_requested();
   });

   menu->addAction("Hide Diagonal", [this]
   {
    //Q_EMIT draw_quad_path_requested();
   });
  }

  menu->addAction("Edit Image ...", [this]
  {
   Q_EMIT edit_image_requested(NULL_CALL_STAMP);
  });

#ifdef HIDE
  QMenu* m1 = menu->addMenu("Manufacturer/Energy Info ...");

  m1->addAction("Windows");
  m1->addAction("Insulation");
  m1->addAction("Ventilation");
  m1->addAction("Walls/Panels");
  m1->addAction("Floors/Ceilings");
  m1->addAction("Lighting");

  menu->addAction("View IFC Graph");
  menu->addAction("View Blueprints (Floor/Room)");
#endif

 }

 menu->popup(pos2);

}



void DHAX_Image_Scene_Item::_handle_mouse_event(QMouseEvent* mev,
                                                Mouse_Event_Modes mem, n8 mode_data_request)
{
 switch(mem)
 {
#define TEMP_MACRO(x) case Mouse_Event_Modes::x: handle_mouse_event<Mouse_Event_Modes::x>(mev, mode_data_request); return;
 TEMP_MACRO(Left_Edit)
   TEMP_MACRO(Left_Move)
   TEMP_MACRO(Left_Init)
   TEMP_MACRO(Left_Resume)
   TEMP_MACRO(Right_Edit)
   TEMP_MACRO(Right_Move)
   TEMP_MACRO(Right_Init)
   TEMP_MACRO(Left_Move_Release)
   TEMP_MACRO(Left_Edit_Release)
   TEMP_MACRO(Right_Click_Iso)
   TEMP_MACRO(Right_Click_Temp_Release)
   default:break;
 }
}


