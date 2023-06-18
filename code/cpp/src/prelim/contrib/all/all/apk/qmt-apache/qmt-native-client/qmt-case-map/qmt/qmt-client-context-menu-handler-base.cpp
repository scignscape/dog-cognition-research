
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "qmt-client-context-menu-handler-base.h"

//#include "MapGraphicsView.h"

#include "global-types.h"

#include <QMessageBox>

#include <QGeoServiceProvider>
#include <QGeoCodingManager>
#include <QGeoCoordinate>

#include <QGeoCodeReply>

#include <QDebug>

#include "CircleObject.h"


QMT_Client_Context_Menu_Handler_Base::QMT_Client_Context_Menu_Handler_Base(MapGraphicsView* view)
  :  view_(view)
{

}


void QMT_Client_Context_Menu_Handler_Base::handle_context_menu_on_mgo
  (QGraphicsSceneContextMenuEvent* event, MapGraphicsObject*)
{
 event->ignore();
}
