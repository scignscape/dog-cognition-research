
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef DHAX_IMAGE_SCENE_ITEM__H
#define DHAX_IMAGE_SCENE_ITEM__H

#include <QFrame>
#include <QBoxLayout>
#include <QGraphicsRectItem>
#include <QDebug>

#include "accessors.h"

#include "global-types.h"

#include "dhax-display-image-data.h"

#include "context-menu-prep-state.h"

#include "self-connect.h"

class DHAX_Graphics_Scene;
class DHAX_Graphics_View;

class DHAX_Display_Image_Data;
class DHAX_Main_Window;

class DHAX_Annotation_Instance;

class MultiStep_Annotation_Base;

class DHAX_Mouse_Interaction_Data;

class DHAX_Stat_Assessment;

class DHAX_Drawn_Shape;

class _Proxy_Widget;

class DHAX_Image_Scene_Item : public QWidget
{
 Q_OBJECT

private:


// QPixmap* scrolled_image_pixmap_;

//// QPixmap* original_scrolled_image_pixmap_;
//// QMap<int, QPixmap*> pixmaps_by_contrast_measure_;


// //QGraphicsScene *scene
// QGraphicsView* scrolled_image_view_;
// QGraphicsScene* scrolled_image_scene_;
// QGraphicsPixmapItem* scrolled_image_pixmap_item_;

// QGraphicsRectItem* background_rectangle_;

// int background_rectangle_center_x_;
// int background_rectangle_center_y_;

// QVBoxLayout* main_layout_;

// void recenter_image();

 DHAX_Display_Image_Data* data_;

// QGraphicsProxyWidget* this_proxy_widget_;
 _Proxy_Widget* this_proxy_widget_;

 QGraphicsItem* background_item_;

 DHAX_Graphics_View* containing_image_view_;

 QPointF original_position_;

 u4* meshlab_import_count_;
 u4* freecad_import_count_;

 QVector<QPair<DHAX_Annotation_Instance*, r8>> saved_dhax_annotations_;

 MultiStep_Annotation_Base* current_multistep_annotation_;
 MultiStep_Annotation_Base* current_completed_multistep_annotation_;


 QPointF active_right_mouse_drag_origin_;
 QPointF active_left_mouse_drag_origin_;

 DHAX_Mouse_Interaction_Data* current_mouse_interaction_data_;

 Context_Menu_Prep_State context_menu_prep_state_;

 QString image_file_path_;

 std::shared_ptr<QMap<QString, std::shared_ptr<DHAX_Stat_Assessment>>>
   current_transforms_map_;



// QGraphics

 enum class Mouse_Event_Modes { N_A, Left_Edit, Left_Move,
   Left_Init, Left_Resume, Right_Edit, Right_Move, Right_Init,
   Left_Move_Release, Left_Edit_Release,
   Right_Click_Iso, Right_Click_Temp_Release   };

 template<Mouse_Event_Modes mem>
 void handle_mouse_event(QMouseEvent* mev, n8 mode_data_request);

 void _handle_mouse_event(QMouseEvent* mev, Mouse_Event_Modes mem, n8 mode_data_request);

 void paintEvent_draw_point_pairs(QVector<QPair<QPoint, QPoint>>& pairs, QPainter& painter,
   QPen& pen, QPen& shape_pen, QPen& back_pen);

 void paintEvent_draw_drawn_shape(DHAX_Drawn_Shape* dds, QString text,
   QPainter& painter, QPen& pen, QPen& shape_pen);

 void paintEvent_draw_drawn_shape(DHAX_Drawn_Shape* dds,
   QPainter& painter, QPen& pen, QPen& shape_pen)
 {
  paintEvent_draw_drawn_shape(dds, {}, painter, pen, shape_pen);
 }

 void paintEvent_draw_annotation(DHAX_Annotation_Instance& axa, QPainter& painter,
   QPen& pen, QPen& shape_pen, r8 resize_factor);

 void paintEvent_draw_vertex_handles(const QVector<const QPoint*>& points, QPainter& painter);

 void _left_init(const QPoint& pos);
 void _left_move_release(const QPoint& pos);

 void _check_ui_update();

 void show_context_menu(const QPoint& pos);

 void show_annotation_measurements_dialog(const QPoint& pos);

 void generate_annotation_ntxh();

public:

 DHAX_Image_Scene_Item(QWidget *parent = 0);

 USE_SELF_CONNECT(normal)
 USE_SELF_CONNECT(lambda)

 ACCESSORS(DHAX_Display_Image_Data* ,data)

 ACCESSORS(_Proxy_Widget* ,this_proxy_widget)
 //ACCESSORS(QGraphicsProxyWidget* ,this_proxy_widget)


 ACCESSORS(QPointF ,original_position)
 ACCESSORS(QGraphicsItem* ,background_item)
 ACCESSORS(DHAX_Graphics_View* ,containing_image_view)
 ACCESSORS(u4* ,meshlab_import_count)
 ACCESSORS(u4* ,freecad_import_count)

 ACCESSORS(QString ,image_file_path)

 ACCESSORS(MACRO_PASTE(std::shared_ptr<QMap<QString, std::shared_ptr<DHAX_Stat_Assessment>>>)
            ,current_transforms_map)

 QWidget* temp;


 enum shapes{ square, ellipse, polygon };

 void cancel_notation();
 void uncancel_notation(DHAX_Drawn_Shape* dds);

 void reset_background_to_original_position();

 void add_dhax_annotation(DHAX_Annotation_Instance* dai, r8 resize_factor)
 {
  saved_dhax_annotations_.push_back({dai, resize_factor});
 }

 void draw_control_square(const QPoint& center, QPainter& painter, u1 wind);

 DHAX_Annotation_Instance* get_annotation_comments();

 ACCESSORS(MACRO_PASTE(QVector<QPair<DHAX_Annotation_Instance*, r8>>) ,saved_dhax_annotations)


 void hide_for_xcsd();


Q_SIGNALS:

 //?
 void onLineDraw(QList<DHAX_Display_Image_Data::shape>);
 void setTuple(QString);

 void save_notation_requested(bool);
 void polygon_complete_and_save_notation_requested(call_Stamp_u2);
 void polygon_complete_and_save_notation_with_comment_requested(call_Stamp_u2);

 void polyline_save_notation_requested(bool);

 void get_annotation_comments_requested(DHAX_Annotation_Instance*);

 void complete_polygon_requested(call_Stamp_u2);
 void edit_image_requested(call_Stamp_u2);

//? void uncancel_requested(DHAX_Drawn_Shape*);

 void meshlab_import_info_requested(call_Stamp_u2);
 void meshlab_reset_requested(call_Stamp_u2);
 void freecad_import_info_requested(call_Stamp_u2);
 void freecad_reset_requested(call_Stamp_u2);

 void draw_bezier_requested(call_Stamp_u2);
 void draw_cubic_path_requested(call_Stamp_u2);
 void draw_quad_path_requested(call_Stamp_u2);

 void convert_notation_requested(call_Stamp_u2);

 void color_mean_dialog_requested(QString, QStringList);

protected:
 void paintEvent(QPaintEvent *);
 void mousePressEvent(QMouseEvent* mouseEvent);
 void mouseReleaseEvent(QMouseEvent *mouseEvent);
 void mouseMoveEvent(QMouseEvent *mouseEvent);
 void mouseDoubleClickEvent(QMouseEvent *mouseEvent);


};

#endif //  DHAX_IMAGE_SCENE_ITEM__H




