
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)



#ifndef QMT_CLIENT_LOCATION_FOCUS__H
#define QMT_CLIENT_LOCATION_FOCUS__H


#include "qmt/qmt-client-location-focus-base.h"

#include "global-types.h"

#include <QString>
#include <QList>

#include <QPoint>

#include <QMap>

#include <functional>

#include <QVariant>

//class QMT_Server_Response;

#include <QObject>

class Lanternfly_Frame;

class QMT_Client_Location_Focus : public QMT_Client_Location_Focus_Base
{
 QMap<QString, QPair<r8, r8>> known_locations_;

 Lanternfly_Frame* map_display_frame_;

public:

 QMT_Client_Location_Focus(Lanternfly_Frame* map_display_frame);

 virtual QStringList get_short_choice_list() Q_DECL_OVERRIDE;
 virtual QString adopt_location(QString name) Q_DECL_OVERRIDE;


};



#endif // QMT_CLIENT_LOCATION_FOCUS__H
