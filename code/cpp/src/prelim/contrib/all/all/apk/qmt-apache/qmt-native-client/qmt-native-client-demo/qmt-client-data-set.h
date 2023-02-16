
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)



#ifndef QMT_CLIENT_DATA_SET__H
#define QMT_CLIENT_DATA_SET__H

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

#include "qmt/qmt-client-data-set-base.h"

#include <typeinfo>

class MapGraphicsScene;
class MapGraphicsView;

class CircleObject;
class PolygonObject;
class QPolygonF;

class QMT_Data_Set_Content_Base;
class Lanternfly_Main_Window;


class QMT_Client_Data_Set : public QMT_Client_Data_Set_Base
{
 QMT_Data_Set_Content_Base* current_content_base_;
 Lanternfly_Main_Window* main_window_;

 QMap<QMT_Data_Set_Content_Base*, QVector<CircleObject*>> all_markings_;

 u4 last_load_status_;

protected:

 virtual void read_ntxh_hypernode(NTXH_Graph& g, hypernode_type* h) Q_DECL_OVERRIDE;
 virtual void prepare_ntxh_document(NTXH_Document& doc, QString file_path) Q_DECL_OVERRIDE;
 virtual void conclude_ntxh_document(NTXH_Document& doc, QString file_path) Q_DECL_OVERRIDE;


public:


 QMT_Client_Data_Set(Lanternfly_Main_Window* main_window);


 ACCESSORS(QString ,single_file_path)
 ACCESSORS(QString ,folder_path)

 ACCESSORS__RGET(QVector<Match_Info> ,current_matches)

 virtual QMT_Client_Data_Set_Base* make_new_unattached_child_data_set() Q_DECL_OVERRIDE;

 virtual void add_markings() Q_DECL_OVERRIDE;
 virtual void toggle_marking_outline_visibility(u4* count = nullptr) Q_DECL_OVERRIDE;
 virtual u4 load_ok() Q_DECL_OVERRIDE;

};

// QMT_Client_Context_Menu_Handler

#endif //QMT_CLIENT_DATA_SET__H
