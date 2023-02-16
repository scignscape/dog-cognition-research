
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)



#ifndef QMT_GIS_UTILS__H
#define QMT_GIS_UTILS__H

//#include "qmt-accessors.h"
//#include "qmt-global-types.h"

#include <QString>
#include <QList>

#include <QPoint>

#include <QMap>

#include <functional>

#include <QVariant>

//class QMT_Server_Response;

class MapGraphicsView;
class QGeoCodingManager;
class QGeoServiceProvider;

class QMT_GIS_Utils
{

 QGeoServiceProvider* geo_service_provider_; //("osm");
 QGeoCodingManager* geo_coding_manager_;// gcm = gsp.geocodingManager();

 QMap<QString, QGeoServiceProvider*> geo_service_provider_map_;

 void init_service_provider();

// QGeoServiceProvider gsp("esri");
// QGeoCodingManager* gcm = gsp.geocodingManager();


// QStringList map_styles_by_name_;
// MapGraphicsView* view_;

// QString request_path_;
// QString actual_path_;

// u4 size_;

public:

 struct Result_Callbacks {
   std::function<void(QVariant)> success;
   std::function<void(QVariant, QString)> failure;
 };

 QMT_GIS_Utils();

 void reset_service_provider(QString name);

 void get_street_address_from_ll(QPointF ll,
   const Result_Callbacks& cbs);

// void reset_map_style(QPoint qp);
// void show_llcoords(QPoint qp);
// void llcoords_to_street_address(QPoint qp);

// ACCESSORS(QString ,request_path)
// ACCESSORS(QString ,actual_path)
// ACCESSORS(u4 ,size)

};



#endif // QMT_GIS_UTILS__H
