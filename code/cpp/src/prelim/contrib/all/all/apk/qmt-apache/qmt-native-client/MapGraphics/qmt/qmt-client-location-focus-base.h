
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)



#ifndef QMT_CLIENT_LOCATION_FOCUS_BASE__H
#define QMT_CLIENT_LOCATION_FOCUS_BASE__H


#include "accessors.h"

#include "global-types.h"

#include <QString>
#include <QList>

#include <QPoint>

#include <QMap>

#include <functional>

#include <QVariant>

//class QMT_Server_Response;

#include <QObject>


class QMT_Client_Location_Focus_Base //: public QObject
{
protected:

 r8 current_central_latitude_;
 r8 current_central_longitude_;

 QString current_location_name_;
 //Q_OBJECT

 void reset(QString location_name, r8 central_latitude,
   r8 central_longitude);

public:

 QMT_Client_Location_Focus_Base();


 ACCESSORS(r8 ,current_central_latitude)
 ACCESSORS(r8 ,current_central_longitude)
 ACCESSORS(QString ,current_location_name)


 virtual QStringList get_short_choice_list() = 0;
 virtual QString adopt_location(QString name) = 0;


};



#endif // QMT_CLIENT_LOCATION_FOCUS_BASE__H
