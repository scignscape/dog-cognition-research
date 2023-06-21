
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "qmt-client-layer-base.h"

//#include "MapGraphicsView.h"

#include "global-types.h"

#include <QMessageBox>

#include <QGeoServiceProvider>
#include <QGeoCodingManager>
#include <QGeoCoordinate>

#include <QGeoCodeReply>

#include <QDebug>

#include "CircleObject.h"
#include "PolygonObject.h"

#include "MapGraphicsScene.h"


QMT_Client_Layer_Base::QMT_Client_Layer_Base(MapGraphicsScene* scene, MapGraphicsView* view)
  :  scene_(scene), view_(view), current_style_(nullptr)
{
}


//PolygonObject* QMT_Client_Layer_Base::add_polygon_object(r8 latitude,
//  r8 longitude, u2 radius, QColor color)
//{
// PolygonObject* result = new PolygonObject(radius, false, color);
// result->setLatitude(latitude);
// result->setLongitude(longitude);
// scene_->addObject(result);
// return result;

//}

CircleObject* QMT_Client_Layer_Base::add_polygon_object(r8 latitude,
  r8 longitude, QPolygonF* polygon, QColor color, r4 select_margin)
{
 CircleObject* co = add_circle_object(latitude, longitude, select_margin, color);
// PolygonObject* result = new PolygonObject(*polygon, color);
 co->sup.set_ref(polygon);
 return co;
// return add_object(latitude, longitude, result);
}


CircleObject* QMT_Client_Layer_Base::add_circle_object(r8 latitude,
  r8 longitude, u2 radius, QColor color)
{
 CircleObject* result = new CircleObject(view_, radius, false, color);
 return add_object(latitude, longitude, result);

// result->setLatitude(latitude);
// result->setLongitude(longitude);

// scene_->addObject(result);
// return result;
}

void* QMT_Client_Layer_Base::adopt_style(QString name)
{
 auto it = style_names_.find(name);
 if(it == style_names_.end())
   return nullptr;
 current_style_ = *it;
 return current_style_;
}

void* QMT_Client_Layer_Base::define_and_adopt_style(QString name, QString context_menu_handler, const std::type_info& model,
 QVector<QColor> colors, QMap<QString, QVariant> params, u1 complexity)
{
 current_style_ = define_style(name, context_menu_handler, model, colors, params, complexity);
 return current_style_;
}

void* QMT_Client_Layer_Base::define_and_adopt_style(QString name, QString context_menu_handler,
   QVector<QColor> colors, QPolygonF polygon, QMap<QString, QVariant> params)
{
 current_style_ = define_style(name, context_menu_handler, colors, polygon, params);
 return current_style_;
}

void QMT_Client_Layer_Base::add_d0_marks(QMT_Client_Data_Set_Base* data_set)
  //const QVector<QPair<QVector<r8>, QStringList>>& coords_and_texts)
{
 for(auto& match : data_set->current_matches())
 {
  CircleObject* co = add_d0_mark(match);
  data_set->bind_new_graphics_object(co);
 }
}
