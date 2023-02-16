
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "qmt-client-location-focus-base.h"

//#include "MapGraphicsView.h"

#include "global-types.h"

#include <QMessageBox>

#include <QGeoServiceProvider>
#include <QGeoCodingManager>
#include <QGeoCoordinate>

#include <QGeoCodeReply>

#include <QDebug>

#include "CircleObject.h"


QMT_Client_Location_Focus_Base::QMT_Client_Location_Focus_Base()
  :  current_central_latitude_(0), current_central_longitude_(0)
{

}


void QMT_Client_Location_Focus_Base::reset(QString location_name, r8 central_latitude,
  r8 central_longitude)
{
 current_location_name_ = location_name;
 current_central_latitude_ = central_latitude;
 current_central_longitude_ = central_longitude;
}


