
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)



#ifndef MAIN_WINDOW_CONTROLLER__H
#define MAIN_WINDOW_CONTROLLER__H

//#include "qmt-accessors.h"
//

#include "global-types.h"

#include "qmt-gis-utils.h"

#include "accessors.h"

#include "qmt-client-data-set-base.h"

#include <QString>
#include <QList>

#include <QPoint>
#include <QStack>

//class QMT_Server_Response;

class MapGraphicsView;
class QMT_Client_Layer_Base;

class Main_Window_Controller
{
 QStringList map_styles_by_name_;

 MapGraphicsView* view_;
 QMT_Client_Layer_Base* qmt_client_layer_base_;

 QStack<QMT_Client_Data_Set_Base*> active_data_sets_;

 QMT_GIS_Utils gis_utils_;

 // //  TODO: as in DHAX this could be part of a separate "app data" class
  //    for now leave it here but I'll make it a pointer so it can move easily
 QMap<QString, QString>* info_files_;

 int current_map_style_index_;

 CircleObject* current_location_spot_;

// QString request_path_;
// QString actual_path_;

// u4 size_;

 void _activate_local_tile_server(const QString* local_socket_flag);

public:

 Main_Window_Controller(MapGraphicsView* view);

 ACCESSORS(QMT_Client_Layer_Base* ,qmt_client_layer_base)

 void push_data_set(QMT_Client_Data_Set_Base* ds)
 {
  active_data_sets_.push(ds);
 }

 void reset_map_style(QPoint qp);
 void reset_data_layer();
 void show_coordinate_marking();


 void show_llcoords(QPoint qp);
 void llcoords_to_street_address(QPoint qp);

 void load_bus_data();
 void find_bus_stops(r8 latitude, r8 longitude, CircleObject* spot = nullptr);

 void check_clear_data_layers(CircleObject* _spot);
 void check_clear_data_layers()
 {
  check_clear_data_layers(current_location_spot_);
 }

 CircleObject* add_spot_location_marking(r8 latitude, r8 longitude);


 void load_incident_reports();
 void track_incidents(r8 latitude, r8 longitude, s4 allow_duplicates);

 void load_web_engine_view(QPoint pos, QUrl url);


 void load_single_file_data_set();

 void activate_local_tile_server(QString local_socket_flag)
 {
  _activate_local_tile_server(&local_socket_flag);
 }
 void activate_local_tile_server()
 {
  static QString no_local_socket;
  _activate_local_tile_server(&no_local_socket);
 }
 void activate_local_tile_server(QString* local_socket_flag)
 {
  if(local_socket_flag)
    _activate_local_tile_server(local_socket_flag);
  else
  {
   static QString default_local_socket_flag = "-l";
   activate_local_tile_server(&default_local_socket_flag);
  }
 }

 void deactivate_local_tile_server();

 void toggle_marking_outline_visibility();

 void set_info_file(QString key, QString value)
 {
  (*info_files_)[key] = value;
 }

 QString get_info_file(QString key)
 {
  return info_files_->value(key);
 }

// static u4 match_locations_in_text_file(QString file_path, r8 query_latitude, r8 query_longitude,
//   u4 number_of_results, u1 latitude_column,
//   u1 longitude_column, u1 column_separator,
//   QVector<QPair<QVector<r8>, QStringList>>& results,
//   s4 allow_duplicates = 0,
//   u1 number_of_header_lines = 1, QVector<u1> other_location_columns = {});

 template<typename... ARGS>
 u4 match_locations_in_info_file(QString key, QMT_Client_Data_Set_Base* data_set,
   ARGS&&... args)
 {
  QString file_path = get_info_file(key);
  if(file_path.isEmpty())
    return 0;
  return data_set->match_locations_in_text_file(file_path,
    std::forward<ARGS>(args)...);
 }

// ACCESSORS(QString ,request_path)
// ACCESSORS(QString ,actual_path)
// ACCESSORS(u4 ,size)

};



#endif // MAIN_WINDOW_CONTROLLER__H
