
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)



#ifndef QMT_CLIENT_CONTEXT_MENU_HANDLER_BASE__H
#define QMT_CLIENT_CONTEXT_MENU_HANDLER_BASE__H

//#include "qmt-accessors.h"

#include "global-types.h"

#include <QString>
#include <QList>

#include <QPoint>

#include <QMap>

#include <functional>

#include <QVariant>

//class QMT_Server_Response;

#include <QObject>

class QGraphicsSceneContextMenuEvent;
class MapGraphicsObject;

class MapGraphicsView;

class QMT_Client_Context_Menu_Handler_Base : public QObject
{
 Q_OBJECT

protected:
 MapGraphicsView* view_;

public:

 QMT_Client_Context_Menu_Handler_Base(MapGraphicsView* view);

 virtual void handle_context_menu_on_mgo(QGraphicsSceneContextMenuEvent* event, MapGraphicsObject*);

};



#endif // QMT_CLIENT_CONTEXT_MENU_HANDLER_BASE__H
