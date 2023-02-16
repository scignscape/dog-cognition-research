
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)



#ifndef QMT_CLIENT_LAYER_BASE__H
#define QMT_CLIENT_LAYER_BASE__H

//#include "qmt-accessors.h"

#include "global-types.h"

#include <QString>
#include <QList>

#include <QPoint>

#include <QMap>

#include <functional>

#include <QVariant>

#include <QPolygonF>

#include "accessors.h"

#include "typeindex"

#include "MapGraphicsScene.h"

#include "qmt-client-data-set-base.h"

#include <typeinfo>

class MapGraphicsScene;
class MapGraphicsView;

class CircleObject;
class PolygonObject;
class QPolygonF;

class QMT_Data_Set_Base;

class QMT_Client_Layer_Base
{
protected:
 MapGraphicsScene* scene_;
 MapGraphicsView* view_;

 QMap<QString, void*> style_names_;

 void* current_style_;

public:

 virtual CircleObject* add_d0_mark(r8 latitude, r8 longitude, QStringList text = {}) = 0;
 virtual CircleObject* add_d0_mark(QMT_Client_Data_Set_Base::Match_Info& match_info) = 0;
 virtual void add_d0_marks(QMT_Client_Data_Set_Base* data_set);

// virtual void* define_style(QString name, std::type_index model,
//   QVector<QColor> colors, QVector<r8> params, u1 complexity = 0) = 0;

// virtual void* define_style(QString name, std::type_info& model,
//   QVector<QColor> colors, QVector<r8> params, u1 complexity = 0)
// {
//  return define_style(name, std::type_index(model), colors, params, complexity);
// }

  virtual void* define_style(QString name, QString context_menu_handler, const std::type_info& model,
    QVector<QColor> colors, QMap<QString, QVariant> params = {}, u1 complexity = 0) = 0;

 virtual void* define_style(QString name, QString context_menu_handler,
   QVector<QColor> colors, QPolygonF polygon, QMap<QString, QVariant> params = {}) = 0;

 virtual void* adopt_style(QString name);
 virtual void* define_and_adopt_style(QString name, QString context_menu_handler, const std::type_info& model,
   QVector<QColor> colors, QMap<QString, QVariant> params = {}, u1 complexity = 0);

 virtual void* define_and_adopt_style(QString name, QString context_menu_handler,
   QVector<QColor> colors, QPolygonF polygon, QMap<QString, QVariant> params = {});


// virtual void* define_and_adopt_style(QString name, std::type_index model,
//  QVector<QColor> colors, QVector<r8> params, u1 complexity = 0);

// virtual void* define_and_adopt_style(QString name, std::type_info& model,
//  QVector<QColor> colors, QVector<r8> params, u1 complexity = 0)
// {
//  return define_and_adopt_style(name, std::type_index(model), colors, params, complexity);
// }


 QMT_Client_Layer_Base(MapGraphicsScene* scene, MapGraphicsView* view);

 CircleObject* add_circle_object(r8 latitude, r8 longitude, u2 radius, QColor color);

 // //  currently we add polygons by adding a (maybe invisible) circle which,
  //    if it is visible at all, can add detail to the icon.  The circle
  //    object then takes responsibility for drawing the polygon
 CircleObject* add_polygon_object(r8 latitude, r8 longitude,
   QPolygonF* polygon, QColor color, r4 select_margin = 0);

 template<typename OBJECT_Type>
 OBJECT_Type* add_object(OBJECT_Type* obj)
 {
  scene_->addObject(obj);
  return obj;
 }

 template<typename OBJECT_Type>
 OBJECT_Type* add_object(r8 latitude, r8 longitude, OBJECT_Type* obj)
 {
  obj->setLatitude(latitude);
  obj->setLongitude(longitude);
  return add_object(obj);
 }


 ACCESSORS(MapGraphicsScene* ,scene)

};

// QMT_Client_Context_Menu_Handler

#endif //QMT_CLIENT_LAYER_BASE__H
