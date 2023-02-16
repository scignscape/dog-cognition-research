
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)



#ifndef QMT_CLIENT_CONTEXT_MENU_HANDLER__H
#define QMT_CLIENT_CONTEXT_MENU_HANDLER__H


#include "qmt/qmt-client-context-menu-handler-base.h"

#include "global-types.h"

#include <QString>
#include <QList>

#include <QPoint>

#include <QMap>

#include <functional>

#include <QVariant>

//class QMT_Server_Response;

#include <QObject>




class QMT_Client_Context_Menu_Handler  :  public QMT_Client_Context_Menu_Handler_Base
{
 Q_OBJECT

 QPoint map_event_pos_to_global(QGraphicsSceneContextMenuEvent* event, MapGraphicsObject* mgo);


public:

 QMT_Client_Context_Menu_Handler(MapGraphicsView* view);

 virtual void handle_context_menu_on_mgo
   (QGraphicsSceneContextMenuEvent* event, MapGraphicsObject* mgo) Q_DECL_OVERRIDE;

public Q_SLOTS:

 void handle_bus_stop_context_menu(QGraphicsSceneContextMenuEvent* event,
   MapGraphicsObject* mgo);

 void handle_incident_context_menu(QGraphicsSceneContextMenuEvent* event,
   MapGraphicsObject* mgo);

};


#endif // QMT_CLIENT_CONTEXT_MENU_HANDLER__H
