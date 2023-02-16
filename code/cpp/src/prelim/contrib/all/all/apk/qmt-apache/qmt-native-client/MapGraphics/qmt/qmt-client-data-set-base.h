
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)



#ifndef QMT_CLIENT_DATA_SET_BASE__H
#define QMT_CLIENT_DATA_SET_BASE__H

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


#include <typeinfo>

class MapGraphicsScene;
class MapGraphicsView;

class CircleObject;
class PolygonObject;
class QPolygonF;

class QMT_Client_Data_Set_Base
{
public:

 union _r8_or_ptr { r8 _r8; void* _ptr; };

 struct Match_Info
 {
  QVector<_r8_or_ptr> location_fields;
  QStringList text_fields;
 };

protected:

 typedef NTXH_Graph::hypernode_type hypernode_type;

 QString single_file_path_;
 QString folder_path_;

 QVector<Match_Info> current_matches_;

 QVector<CircleObject*>* current_bind_vector_;
 CircleObject* current_bind_object_;

 virtual void read_ntxh_hypernode(NTXH_Graph& g, hypernode_type* h) = 0;
 virtual void prepare_ntxh_document(NTXH_Document& doc, QString file_path) = 0;
 virtual void conclude_ntxh_document(NTXH_Document& doc, QString file_path) = 0;


public:


 QMT_Client_Data_Set_Base();

 virtual ~QMT_Client_Data_Set_Base() {}

 ACCESSORS(QString ,single_file_path)
 ACCESSORS(QString ,folder_path)

 ACCESSORS(QVector<CircleObject*>* ,current_bind_vector)

 ACCESSORS__RGET(QVector<Match_Info> ,current_matches)

 virtual QMT_Client_Data_Set_Base* make_new_unattached_child_data_set() = 0;
 virtual void add_markings() = 0;

 virtual void toggle_marking_outline_visibility(u4* count = nullptr) {}

 virtual u4 load_ok() = 0;

 virtual void bind_new_graphics_object(CircleObject* co)
 {
  if(current_bind_vector_)
    current_bind_vector_->push_back(co);
 }

 virtual void bind_to_spot_location(CircleObject* co)
 {
  current_bind_vector_ = new QVector<CircleObject*>;
  current_bind_object_ = co;
 }

 void load_ntxh_file(QString file_path);

 u4 match_locations_in_text_file(QString file_path, r8 query_latitude, r8 query_longitude,
   u4 number_of_results, u1 latitude_column,
   u1 longitude_column, u1 column_separator,
   s4 allow_duplicates = 0,
   u1 number_of_header_lines = 1, QVector<u1> other_location_columns = {});


};

// QMT_Client_Context_Menu_Handler

#endif //QMT_CLIENT_DATA_SET_BASE__H
