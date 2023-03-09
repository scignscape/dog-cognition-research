
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef XCSD_LOCAL_HISTOGRAM_DIALOG__H
#define XCSD_LOCAL_HISTOGRAM_DIALOG__H



#include "xcsd-2d/xcsd-sdi-structures.h"

#include <QImage>

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QVBoxLayout>

#include <QDialog>



#include "accessors.h"

//XCNS_(XCSD)

//class XCSD_XPixel;

#include "xcsd-2d/xcsd-sdi-structures.h"

#include "xcsd-2d/local-histogram-data.h"

#include <QGraphicsRectItem>

#include "self-connect.h"



class XCSD_Local_Histogram_Dialog : public QDialog
{
 Q_OBJECT

 struct Window_Rect_Item : QGraphicsRectItem {
   XCSD_Local_Histogram_Dialog* parent_dialog;
   Window_Rect_Item(XCSD_Local_Histogram_Dialog* dlg)
    : QGraphicsRectItem(), parent_dialog(dlg)
   {

   }

 };


 struct Rect_Item : QGraphicsRectItem {
   u2 color_code;
   //u2 hue;
   Rect_Item(Window_Rect_Item* parent, const QRect& rect, u2 cc, QColor color);

   XCSD_Local_Histogram_Dialog* get_parent_dialog()
   {
    return ((Window_Rect_Item*)(this->parentItem()))->parent_dialog;
   }

   void hoverEnterEvent(QGraphicsSceneHoverEvent* event) Q_DECL_OVERRIDE;
   void hoverLeaveEvent(QGraphicsSceneHoverEvent* event) Q_DECL_OVERRIDE;
   void contextMenuEvent(QGraphicsSceneContextMenuEvent* event) Q_DECL_OVERRIDE;


 };

 QMap<s2, Histogram_Group_Summary>* data_;

 u2 image_height_; // = 520;
 u2 max_bin_height_; //  = 200;
 u2 min_bin_height_; //  = 10;
 u2 bin_base_; //  = 260;
 u2 bin_width_; //  = 9;

 u2 max_group_height_; //  = 200;
 u2 min_group_height_; //  = 10;

 QVBoxLayout* main_layout_;
 QGraphicsScene* graphics_scene_;
 QGraphicsView* graphics_view_;

 Window_Rect_Item* parent_rect_item_;

 void context_menu(Rect_Item* ri, QGraphicsSceneContextMenuEvent* event);

public:

 XCSD_Local_Histogram_Dialog(QWidget* parent,
   pr2 totals, QColor ref_color, //largest_group_total,
   QMap<s2, Histogram_Group_Summary>* data);

 USE_SELF_CONNECT(normal)
 USE_SELF_CONNECT(lambda)


Q_SIGNALS:

 void mark_global_foreground_pole_requested(u2);
 void mark_global_background_pole_requested(u2);
 void mark_local_foreground_pole_requested(u2);
 void mark_local_background_pole_requested(u2);

};


//_XCNS(XCSD)

#endif // XCSD_LOCAL_HISTOGRAM_DIALOG__H
