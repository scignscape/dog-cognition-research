
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "qmt-gis-utils.h"

//#include "MapGraphicsView.h"

#include "global-types.h"

#include <QMessageBox>

#include <QGeoServiceProvider>
#include <QGeoCodingManager>
#include <QGeoCoordinate>

#include <QGeoCodeReply>

#include <QDebug>


QMT_GIS_Utils::QMT_GIS_Utils()
  :  geo_service_provider_(nullptr)
{
 // //  use osm for default
 reset_service_provider("osm");
}

void QMT_GIS_Utils::get_street_address_from_ll(QPointF ll,
  const Result_Callbacks& cbs)
{
 QGeoCodeReply* gcr
   = geo_coding_manager_->reverseGeocode(QGeoCoordinate(ll.y(), ll.x()));

 QObject::connect(gcr, &QGeoCodeReply::finished,
   [gcr, cbs]
 {
  if(gcr->error() == QGeoCodeReply::NoError)
  {
   QList<QGeoLocation> reply_locations = gcr->locations();
   QVariant qvar;
   qvar.setValue(reply_locations);
   cbs.success(qvar);
  }
  else
  {
   cbs.failure(QVariant((int)gcr->error()), gcr->errorString());
  }
 });

}


void QMT_GIS_Utils::reset_service_provider(QString name)
{
 auto it = geo_service_provider_map_.find(name);

 if(it == geo_service_provider_map_.end())
 {
  geo_service_provider_ = new QGeoServiceProvider(name);
  geo_service_provider_map_[name] = geo_service_provider_;
  init_service_provider();
 }
 else
   geo_service_provider_ = it.value();
}

void QMT_GIS_Utils::init_service_provider()
{
 geo_coding_manager_ = geo_service_provider_->geocodingManager();
}

