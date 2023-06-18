
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)



#ifndef LANTERNFLY_DATA_SET__H
#define LANTERNFLY_DATA_SET__H

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

//#include "ntxh-parser/ntxh-document.h"

#include "qmt-data-set-content-base.h"

#include <typeinfo>

class MapGraphicsScene;
class MapGraphicsView;

class CircleObject;
class PolygonObject;
class QPolygonF;


class Lanternfly_Data_Set : public QMT_Data_Set_Content_Base
{
 // //  cf. location_classification in the filter dialog
  //   "Private House", "Apartment Building", "Parks/Recreation Area",
  //   "Transit Stop/Center",
  //   "Port/Airport/Railroad Track", "Commercial/Retail", "Factory/Warehouse",
  //   "School/Religious Institution", "Farm/Agricultural Site", "Other"

 enum class Location_Classification {
   N_A,
     Private_House, Apartment_Building, Parks_Recreation,
     Transit, Port_Airport_Railroad, Commercial_Retail,
     Factory_Warehouse, School_Religious, Farm_Agricultural, Other
 };

 Location_Classification parse_location_classification(QString key)
 {
  if(key == "park")
    return Location_Classification::Parks_Recreation;
  if(key == "transit")
    return Location_Classification::Transit;

  // //  todo: skipping the parse-map for now

  return Location_Classification::N_A;
 }

 struct Sighting {

  r8 latitude;
  r8 longitude;
  Location_Classification location_classification;
  u2 presentation_code;

 };

 QVector<Sighting> sightings_;

public:


 Lanternfly_Data_Set();

 void read_ntxh_hypernode(NTXH_Graph& g, hypernode_type* h) Q_DECL_OVERRIDE;
 void add_markings(Lanternfly_Main_Window& main_window,
   QVector<CircleObject*>& stash) Q_DECL_OVERRIDE;

 u4 get_item_count() Q_DECL_OVERRIDE
 {
  return sightings_.size();
 }

// virtual QMT_Client_Data_Set_Base* make_new_unattached_child_data_set() Q_DECL_OVERRIDE;

};

#endif // LANTERNFLY_DATA_SET__H
