
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)



#ifndef QMT_DATA_SET_CONTENT_BASE__H
#define QMT_DATA_SET_CONTENT_BASE__H

//#include "qmt-accessors.h"

#include "global-types.h"

#include <QString>
#include <QList>

#include <QPoint>

#include <QMap>

#include <functional>

#include <QVariant>

#include <QPolygonF>

#include "accessors.h"

#include "typeindex"

#include "MapGraphicsScene.h"


#include "ntxh-parser/ntxh-document.h"

#include "qmt/qmt-client-data-set-base.h"

#include <typeinfo>

class MapGraphicsScene;
class MapGraphicsView;

class CircleObject;
class PolygonObject;
class QPolygonF;

class Lanternfly_Main_Window;



class QMT_Data_Set_Content_Base
{
protected: 
 typedef NTXH_Graph::hypernode_type hypernode_type;

public:


 QMT_Data_Set_Content_Base();

 virtual void read_ntxh_hypernode(NTXH_Graph& g, hypernode_type* h) = 0;
 virtual void add_markings(Lanternfly_Main_Window& main_window,
   QVector<CircleObject*>& stash) = 0;

 virtual u4 get_item_count() = 0;


// virtual QMT_Client_Data_Set_Base* make_new_unattached_child_data_set() Q_DECL_OVERRIDE;

};

// QMT_Client_Context_Menu_Handler

#endif //DATA_SET_CONTENT_BASE__H
