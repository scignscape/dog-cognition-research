
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)



#ifndef QMT_CLIENT_LAYER__H
#define QMT_CLIENT_LAYER__H

//#include "qmt-accessors.h"

#include "global-types.h"

#include <QString>
#include <QList>

#include <QPoint>

#include <QMap>

#include <functional>

#include <QVariant>

//class QMT_Server_Response;

#include "qmt/qmt-client-layer-base.h"

#include <typeindex>

#include <QGraphicsEllipseItem>
#include <QGraphicsRectItem>
#include <QGraphicsPolygonItem>

#include <QPolygonF>


class QMT_Client_Layer : public QMT_Client_Layer_Base
{
 enum class Known_Style_Models {
   N_A, QGraphicsEllipse, QGraphicsEllipse_Circle,
   QGraphicsRect, QGraphicsRect_Square,
   QGraphicsPolygon, QGraphicsPolygon_Regular,
 };

 struct Style_Params {
  r4 x_radius {};
  r4 y_radius {};
  r4 pen_width {};
  r4 rotation {};
  r4 arc_end {};
  QColor brush_color;
  QColor pen_color;
  Known_Style_Models model = Known_Style_Models::N_A;
  QPolygonF* polygon {};
  r4 select_margin { std::numeric_limits<float>::quiet_NaN() };
  QString context_menu_handler;
  QString name;
 };

 Known_Style_Models parse_style_model(const std::type_info& ti)
 {
  static QMap<std::type_index, Known_Style_Models> static_map {
   {typeid(QGraphicsEllipseItem), Known_Style_Models::QGraphicsEllipse},
   {typeid(QGraphicsRectItem), Known_Style_Models::QGraphicsRect},
   {typeid(QGraphicsPolygonItem), Known_Style_Models::QGraphicsPolygon}
  };

  return static_map.value(ti, Known_Style_Models::N_A);
 }

 void set_params(Style_Params* sp, QMap<QString, QVariant> params);

public:

 CircleObject* add_d0_mark(r8 latitude, r8 longitude, QStringList text = {}) Q_DECL_OVERRIDE;

 CircleObject* add_d0_mark(QMT_Client_Data_Set_Base::Match_Info& match_info) Q_DECL_OVERRIDE;

 void* define_style(QString name, QString context_menu_handler, const std::type_info& model,
   QVector<QColor> colors, QMap<QString, QVariant> params = {}, u1 complexity = 0) Q_DECL_OVERRIDE;

 void* define_style(QString name, QString context_menu_handler,
   QVector<QColor> colors, QPolygonF, QMap<QString, QVariant> params = {}) Q_DECL_OVERRIDE;

 QMT_Client_Layer(MapGraphicsScene* scene, MapGraphicsView* view);

 static QString get_context_menu_handler_name(MapGraphicsObject* mgo);
 static QString get_style_params_name(MapGraphicsObject* mgo);


};



#endif // QMT_GIS_UTILS__H
