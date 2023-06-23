
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "lanternfly-data-set.h"

#include "CircleObject.h"
#include "PolygonObject.h"

#include "lanternfly/lanternfly-frame.h"

#include "global-types.h"

#include <QMessageBox>

#include <QDebug>

#include <QFile>

#include <QVector2D>

#include "main-window.h"



Lanternfly_Data_Set::Lanternfly_Data_Set()
{

}

void Lanternfly_Data_Set::add_markings(Lanternfly_Main_Window& main_window,
  QVector<CircleObject*>& stash)
{
 u1 count = 0;
 for(const Sighting& s : sightings_)
 {
  CircleObject* circle = nullptr;

  void* ref = nullptr;

  switch (s.location_classification)
  {
   case Location_Classification::Parks_Recreation:
   {
    QPolygonF* qpf = new QPolygonF;
    (*qpf) << QPointF(-110, -110);
    (*qpf) << QPointF(-110, 110);
    (*qpf) << QPointF(110, -110);
    (*qpf) << QPointF(110, 110);

    //?QColor parks_clr = QColor(155, 0, 220, 220);
    static QColor parks_color = QColor(155, 0, 220, 220);

    circle = new CircleObject(main_window.lanternfly_frame()->view(), 125, false, parks_color);
    ref = qpf;
   }
   break;

  case Location_Classification::Transit:
   {
    QPolygonF* qpf = new QPolygonF;
    (*qpf) << QPointF(-80, 180);
    (*qpf) << QPointF(0, 150);
    (*qpf) << QPointF(80, 180);
    (*qpf) << QPointF(0, 0);

    static QColor transit_color = QColor(55, 90, 110, 255);

    circle = new CircleObject(main_window.lanternfly_frame()->view(), 125, false, transit_color);
    circle->sup.set_ref(qpf);
   }
   break;
  }

  if(circle)
  {
   circle->set_index_code(++count);
//?   circle->setFlags(MapGraphicsObject::ObjectIsSelectable);
   circle->setLatitude(s.latitude);
   circle->setLongitude(s.longitude);
   circle->sup.set_outline_code(s.presentation_code);
   main_window.lanternfly_frame()->scene()->addObject(circle);
   if(ref)
     circle->sup.set_ref(ref);
   stash.push_back(circle);
  }
 }

 main_window.lanternfly_frame()->update();
}

void Lanternfly_Data_Set::read_ntxh_hypernode(NTXH_Graph& g, hypernode_type* h)
{
 if(h->type_descriptor().first == "Sighting")
 {
  g.get_sfs(h, {1, 2, 3, 5}, [this](QVector<QPair<QString, void*>>& prs)
  {
   r8 latitude = prs[0].first.toDouble();
   r8 longitude = prs[1].first.toDouble();
   Location_Classification location_classification =
     parse_location_classification(prs[2].first);
   u2 presentation_code = prs[3].first.toUInt();

   Sighting s {latitude, longitude, location_classification, presentation_code};
   sightings_.push_back(s);

  });
 }

 //   u4 id = prs[0].first.toInt();
 //   QString j = prs[1].first;
 //   u4 s = prs[2].first.toInt();
 //   u4 e = prs[3].first.toInt();

}


