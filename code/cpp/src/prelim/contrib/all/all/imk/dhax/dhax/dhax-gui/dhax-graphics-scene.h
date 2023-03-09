
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef DHAX_GRAPHICS_SCENE__H
#define DHAX_GRAPHICS_SCENE__H

#include <QGraphicsScene>

#include <QDebug>

#include <QGraphicsProxyWidget>
#include <QGraphicsSceneMouseEvent>

#include "global-types.h"

#include "xcsd-2d/xcsd-sdi-structures.h"

#include "xcsd-2d/xcsd-image.h"

#include "self-connect.h"


class XCSD_Tierbox_Scene_Item;

//class XCSD_Outer_Ring_Info;

class XCSD_Outer_Ring_Scene_Item;

class DHAX_Graphics_Frame;


class _Proxy_Widget : public QGraphicsProxyWidget
{
public:

 void mousePressEvent(QGraphicsSceneMouseEvent* mev) Q_DECL_OVERRIDE
 {
  qDebug() << "smev = " << mev;
  this->QGraphicsProxyWidget::mousePressEvent(mev);
 }

 void mouseMoveEvent(QGraphicsSceneMouseEvent* mev) Q_DECL_OVERRIDE
 {
  qDebug() << "mmev = " << mev;
  this->QGraphicsProxyWidget::mouseMoveEvent(mev);
 }

 void mouseReleaseEvent(QGraphicsSceneMouseEvent* mev) Q_DECL_OVERRIDE
 {
  qDebug() << "rmev = " << mev;
  this->QGraphicsProxyWidget::mouseReleaseEvent(mev);
 }

};


class DHAX_Graphics_Scene : public QGraphicsScene
{
 Q_OBJECT

 QGraphicsRectItem* hover_rect_;
 DHAX_Graphics_Frame* containing_graphics_frame_;

public:

 DHAX_Graphics_Scene();

 USE_SELF_CONNECT(normal)
 USE_SELF_CONNECT(lambda)

 ACCESSORS(DHAX_Graphics_Frame* ,containing_graphics_frame)

 _Proxy_Widget* add_proxy_widget(QWidget* w)
 {
  return (_Proxy_Widget*) addWidget(w);
 }

 void set_background_color(QColor c);

 void add_tierbox_pixmap(QString path, rc2 rc, u2 x_corner, u2 y_corner);
 void add_outer_pixmap(const XCSD_Outer_Ring_Info& xori, const QPoint& pos);

 void handle_tierbox_context_menu_action(XCSD_Tierbox_Scene_Item* xtsi,
   u1 code);

 void handle_tierbox_hover_enter(XCSD_Tierbox_Scene_Item* xtsi);

 // void set_foreground_color(QColor c);

Q_SIGNALS:

 void show_tierbox_local_color_histogram_requested(rc2);

};

#endif //  DHAX_GRAPHICS_SCENE__H






