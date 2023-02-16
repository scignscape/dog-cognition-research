
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "main-window.h"
//#include "ui_MainWindow.h"

#include "MapGraphicsView.h"
#include "MapGraphicsScene.h"
#include "tileSources/GridTileSource.h"
#include "tileSources/OSMTileSource.h"
#include "tileSources/CompositeTileSource.h"
#include "guts/CompositeTileSourceConfigurationWidget.h"
#include "CircleObject.h"
#include "PolygonObject.h"

#include "lanternfly/lanternfly-frame.h"


#include <QSharedPointer>
#include <QtDebug>
#include <QThread>
#include <QImage>

#include "lanternfly/lanternfly-sighting-dialog.h"
#include "lanternfly/lanternfly-configuration-dialog.h"
#include "lanternfly/lanternfly-sighting-filter-dialog.h"

Lanternfly_Main_Window::Lanternfly_Main_Window(QWidget* parent) :
  QMainWindow(parent)
//    ui(new Ui::MainWindow)
{
 setWindowTitle("Lanternfly Sighting Map");

 //    ui->setupUi(this);

 //Setup the MapGraphics scene and view
 //    MapGraphicsScene* scene = new MapGraphicsScene(this);
 //    MapGraphicsView* view = new MapGraphicsView(scene,this);

 lanternfly_frame_ = new Lanternfly_Frame(this);

 setCentralWidget(lanternfly_frame_);

 //Setup some tile sources
 QSharedPointer<OSMTileSource> osmTiles(new OSMTileSource(OSMTileSource::OSMTiles), &QObject::deleteLater);
 QSharedPointer<GridTileSource> gridTiles(new GridTileSource(), &QObject::deleteLater);
 QSharedPointer<CompositeTileSource> composite(new CompositeTileSource(), &QObject::deleteLater);
 composite->addSourceBottom(osmTiles);
 composite->addSourceTop(gridTiles);

 lanternfly_frame_->set_tile_source(composite);

 composite->set_current_host("https://b.tile.openstreetmap.fr/hot/");
//? composite->set_current_host("https://b.tile.openstreetmap.org/");
 composite->set_current_url("%1/%2/%3.png");
 composite->update_hosts();
 composite->update_host_cache();

 lanternfly_frame_->set_view_zoom_level(12);
 //view->setZoomLevel(12);
 //view->centerOn(-74.0435, 40.8859);
//? lanternfly_frame_->center_on(-74.0435, 40.8859);

//?

 // //  New Jersey
 // lanternfly_frame_->center_on(-74.0435, 40.8859);


 // //  Ukraine - kherson
 //?
// lanternfly_frame_->center_on(32.6169, 46.6354);


 lanternfly_frame_->adopt_location("Bergen$County");
#ifdef HIDE
 QPolygonF* qpf1 = new QPolygonF;
 (*qpf1) << QPointF(-20, 110);
 (*qpf1) << QPointF(20, 110);
 (*qpf1) << QPointF(110, 20);
 (*qpf1) << QPointF(110, -20);
 (*qpf1) << QPointF(20, -110);
 (*qpf1) << QPointF(-20, -110);
 (*qpf1) << QPointF(-110, -20);
 (*qpf1) << QPointF(-110, 20);

 QColor spot_clr = QColor(80, 105, 155,  220);

 // QColor(201, 159, 34)

 CircleObject* spotcircle = new CircleObject(lanternfly_frame_->view(), 125, false, spot_clr);
 spotcircle->setLatitude(40.86695);
 spotcircle->setLongitude(-74.01307);
 lanternfly_frame_->scene()->addObject(spotcircle);
 spotcircle->ref = qpf1;

 QVector<QPair<qreal, qreal>> locs {
  {-74.03678, 40.88516}, //Forchini
  {-74.03460, 40.88043}, //Oscar E. Olson  Bogota

  {-74.03705, 40.89313}, //Johnson

  {-74.04184, 40.89233}, //Anderson
  {-74.05000, 40.89079}, //Carver
  {-74.05314, 40.90588}, //Borg's Woods
  {-74.04735, 40.91236}, //Staib
  {-74.05299, 40.91114}, //Fireman's Memorial

  {-74.02756, 40.89605}, //Phelp's    Teaneck
  {-74.01814, 40.89134}, //Sagamore    Teaneck
  {-74.00995, 40.896964}, //Milton A. Votee    Teaneck

  {-74.00423, 40.90664}, //Windsor    Teaneck

  {-73.99360, 40.89639}, //Argonne    Teaneck/Englewood

  {-73.98284, 40.89230}, //MacKay    Englewood

  {-74.08842, 40.90839}, //Saddle River County Park     Saddle Brook

  {-74.07862, 40.90832}, //Carlock Field     Rochelle Park

  {-74.08250, 40.91954}, //Cliff Genarelli-Paramus Sports-Plex     Paramus

  {-74.02835, 40.91382}, //Clarence W. Brett Park at Historic New Bridge Landing
  //  Teaneck

  {-74.02276, 40.91473}, //Matthew Feldman Nature Preserve   Teaneck

  {-74.02103, 40.91591}, //Continental Park   Teaneck

  {-74.00858, 40.87471}, //Teaneck Creek Conservancy   Teaneck

 };

  QPolygonF* qpf = new QPolygonF;
  (*qpf) << QPointF(-80, 180);
  (*qpf) << QPointF(0, 150);
  (*qpf) << QPointF(80, 180);
  (*qpf) << QPointF(0, 0);


  QVector<QPair<qreal, qreal>> locs1 {
   {-74.05170, 40.87953}, //essex
   {-74.04432, 40.89407}, //anderson
   {-74.03505, 40.91029}, //newbridge

   {-74.04244, 40.88201}, //h bus
   {-74.07940, 40.91912}, //gsp bus


  };

  QPolygonF* sqpf = new QPolygonF;
  (*sqpf) << QPointF(-110, -110);
  (*sqpf) << QPointF(-110, 110);
  (*sqpf) << QPointF(110, -110);
  (*sqpf) << QPointF(110, 110);

  //?QColor parks_clr = QColor(155, 0, 220, 220);
  QColor parks_clr = QColor(155, 0, 220, 220);

  QColor sq_clr = QColor(55, 90, 110, 255);

  QColor area_clr = QColor(155, 155, 90, 220);

  QPolygonF aqpf;
  aqpf << QPointF(-74.06934, 40.90717);
  aqpf << QPointF(-74.07225, 40.89537);
  aqpf << QPointF(-74.05996, 40.88404);
  aqpf << QPointF(-74.04937, 40.89864);

  // CircleObject* circle = new CircleObject(125, false, QColor(155, 220, 0, 220));
  // circle->setLatitude(40.8859);
  // circle->setLongitude(-74.0435);

  PolygonObject* poly = new PolygonObject(lanternfly_frame_->view(), aqpf, area_clr);

  poly->setLatitude(aqpf.first().y());
  poly->setLongitude(aqpf.first().x());

// ??  lanternfly_frame_->scene()->addObject(poly);

  // QColor(201, 159, 34
  //QColor(55, 120, 240,  220)

 int locs_count = 0;

 for(auto pr: locs)
 {
  CircleObject* circle = new CircleObject(lanternfly_frame_->view(), 125, false, parks_clr);
  circle->setFlags(0);
  circle->setLatitude(pr.second);
  circle->setLongitude(pr.first);
  lanternfly_frame_->scene()->addObject(circle);

  circle->ref = qpf;

  if(locs_count < 2)
    circle->outline_code = 64;

  else if(locs_count < 4)
    circle->outline_code = 3;

  else if(locs_count < 6)
    circle->outline_code = 5;

  else if(locs_count < 8)
    circle->outline_code = 7;

  else if(locs_count < 10)
    circle->outline_code = 8;

  else if(locs_count < 12)
    circle->outline_code = 9;

  else if(locs_count < 14)
    circle->outline_code = 12;

  else if(locs_count < 16)
    circle->outline_code = 16;

  else if(locs_count < 18)
    circle->outline_code = 17;

  else
    circle->outline_code = 64;

  ++locs_count;

 }

 locs_count = 0;

 for(auto pr: locs1)
 {
  CircleObject* circle = new CircleObject(lanternfly_frame_->view(), 125, false, sq_clr);
  circle->setFlags(0);
  circle->setLatitude(pr.second);
  circle->setLongitude(pr.first);
  lanternfly_frame_->scene()->addObject(circle);

  circle->ref = sqpf;

  if(locs_count == 0)
    circle->outline_code = 1;

  else if(locs_count == 1)
    circle->outline_code = 2;

  else if(locs_count == 2)
    circle->outline_code = 4;

  else if(locs_count == 3)
    circle->outline_code = 6;

  else if(locs_count == 4)
    circle->outline_code = 10;

  ++locs_count;

 }
#endif

 //QPointF
}

Lanternfly_Main_Window::~Lanternfly_Main_Window()
{
 //?   delete ui;
}

//private slot
void Lanternfly_Main_Window::on_actionExit_triggered()
{
 this->close();
}


#ifdef HIDE


//?    view->setTileSource(composite);

//Create a widget in the dock that lets us configure tile source layers

//    CompositeTileSourceConfigurationWidget * tileConfigWidget = new CompositeTileSourceConfigurationWidget(composite.toWeakRef(),
//      this->ui->dockWidget);
//    this->ui->dockWidget->setWidget(tileConfigWidget);
//    delete this->ui->dockWidgetContents;

//    this->ui->menuWindow->addAction(this->ui->dockWidget->toggleViewAction());
//    this->ui->dockWidget->toggleViewAction()->setText("&Layers");


//?  view->centerOn(-112.202442, 40.9936234);

// Create a circle on the map to demonstrate MapGraphicsObject a bit
// The circle can be clicked/dragged around and should be ~5km in radius

//?#ifdef HIDE
QPolygonF qpf;
qpf << QPointF(-74.0435, 40.8859);
qpf << QPointF(-74.02266, 40.84750);
qpf << QPointF(-74.10337, 40.85619);

// CircleObject* circle = new CircleObject(125, false, QColor(155, 220, 0, 220));
// circle->setLatitude(40.8859);
// circle->setLongitude(-74.0435);

PolygonObject* poly = new PolygonObject(qpf, QColor(155, 220, 0, 220));

poly->setLatitude(40.8859);
poly->setLongitude(-74.0435);

lanternfly_frame_->scene()->addObject(poly);

// circle->ref = poly;
// lanternfly_frame_->scene()->addObject(circle);
//?#endif //def HIDE

// QPolygonF qpf1;
// qpf1 << QPointF(40.8859, -74.0435);
// qpf1 << QPointF(40.84750, -74.02266);
// qpf1 << QPointF(40.85619, -74.10337);

// PolygonObject* poly1 = new PolygonObject(qpf1, QColor(9, 220, 155, 220));
// lanternfly_frame_->scene()->addObject(poly1);

//  QPolygonF qpf1;
//  qpf1 << QPointF(1, 1);
//  qpf1 << QPointF(1, -1);
//  qpf1 << QPointF(-1, -1);
//  qpf1 << QPointF(-1, 1);

//  PolygonObject* poly1 = new PolygonObject(qpf1, QColor(9, 220, 155, 220));
//  poly1->setLatitude(40.8859);
//  poly1->setLongitude(-74.0435);
//  lanternfly_frame_->scene()->addObject(poly1);

//?#ifdef HIDE

////   //
// CircleObject* circle1 = new CircleObject(125, false, QColor(155, 0, 220, 220));
//   //
// circle1->setLatitude(poly->geoPoly().at(0).x());
// circle1->setLongitude(poly->geoPoly().at(0).y());
// lanternfly_frame_->scene()->addObject(circle1);


// CircleObject* circle2 = new CircleObject(125, false, QColor(155, 0, 220, 220));
//   //
// circle2->setLatitude(poly->geoPoly().at(1).x());
// circle2->setLongitude(poly->geoPoly().at(1).y());
// lanternfly_frame_->scene()->addObject(circle2);


// CircleObject* circle3 = new CircleObject(125, false, QColor(155, 0, 220, 220));
//   //
// circle3->setLatitude(poly->geoPoly().at(2).x());
// circle3->setLongitude(poly->geoPoly().at(2).y());
// lanternfly_frame_->scene()->addObject(circle3);

//?#endif //def HIDE

  //     circle->setLongitude(pr.first);
  //     lanternfly_frame_->scene()->addObject(circle);



#endif
