
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "qmt-client-location-focus.h"

//#include "MapGraphicsView.h"

#include "global-types.h"

#include <QMessageBox>

#include <QGeoServiceProvider>
#include <QGeoCodingManager>
#include <QGeoCoordinate>

#include <QGeoCodeReply>

#include <QDebug>

#include "CircleObject.h"

#include "lanternfly/lanternfly-frame.h"


QMT_Client_Location_Focus::QMT_Client_Location_Focus(Lanternfly_Frame* map_display_frame)
  :  QMT_Client_Location_Focus_Base(), map_display_frame_(map_display_frame)
{
 known_locations_["Bergen$County"] = {-74.0435, 40.8859};
 known_locations_["Kherson"] = {32.6169, 46.6354};
}


QStringList QMT_Client_Location_Focus::get_short_choice_list()
{
 QStringList result = known_locations_.keys();
 result.sort();
 return result;
}


QString QMT_Client_Location_Focus::adopt_location(QString name)
{
 qDebug() << name;
 auto it = known_locations_.find(name);
 if(it == known_locations_.end())
 {
  // // message box?
  return {};
 }

 reset(name, it->second, it->first);

 map_display_frame_->center_on(it->first, it->second);

 return name;
}
