
//          Copyright Nathaniel Christen 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include "case-map-gis-service.h"

//?#include "styles.h"




#include <QApplication>

#include <QHBoxLayout>
#include <QVBoxLayout>

#include <QButtonGroup>
#include <QScrollArea>
#include <QFileDialog>
#include <QTabWidget>
#include <QSplitter>
#include <QDialogButtonBox>
#include <QFormLayout>
#include <QCheckBox>
#include <QLineEdit>
#include <QGroupBox>

#include <QPlainTextEdit>
#include <QTextStream>

#include <QtMultimedia/QMediaPlayer>

#include <QPainter>
#include <QPushButton>
#include <QLabel>

//#include <QNetworkAccessManager>
//#include <QNetworkReply>

#include <QTableWidget>
#include <QGraphicsPixmapItem>

#include <QMessageBox>
#include <QDebug>
#include <QClipboard>

#include <QProcess>

#include <QGraphicsView>
#include <QScrollArea>

//#include <QTcpServer>
//#include <QNetworkAccessManager>

#include <QHeaderView>

#include <QMenu>
#include <QAction>

#include <QListWidget>

#include <QComboBox>

#include "global-types.h"


// Qt header:
//?#include <QtWidgets>
#include <QGeoAddress>
#include <QGeoCodingManager>
#include <QGeoCoordinate>
#include <QGeoLocation>
#include <QGeoServiceProvider>

Case_Map_GIS_Service::Case_Map_GIS_Service(QString provider)
 : provider_(provider)
{
}

QPair<r8, r8> Case_Map_GIS_Service::get_city_latitude_and_longitude(QString city, QString state)
{
 QGeoServiceProvider gsp(provider_);
 QGeoCodingManager* gcm = gsp.geocodingManager();

 QGeoAddress* pQGeoAddr = new QGeoAddress;

 pQGeoAddr->setCountry("USA");
// pQGeoAddr->setPostalCode("07024");

 pQGeoAddr->setCity(city);
 pQGeoAddr->setState(state);
// pQGeoAddr->setStreet("320 Main Street");

 QGeoCodeReply* pQGeoCode
   = gcm->geocode(*pQGeoAddr);


 QEventLoop qel;

 QList<QGeoLocation> reply_locations;


 QObject::connect(pQGeoCode, &QGeoCodeReply::finished,
   [pQGeoCode, &qel, &reply_locations]
 {
  qDebug() << "Reply: " << pQGeoCode->errorString();

  switch (pQGeoCode->error())
  {
   case QGeoCodeReply::NoError:
     reply_locations = pQGeoCode->locations();
     break;
#define CASE(ERROR) \
    case QGeoCodeReply::ERROR: qDebug() << #ERROR << '\n'; break;
    CASE(EngineNotSetError)
    CASE(CommunicationError)
    CASE(ParseError)
    CASE(UnsupportedOptionError)
    CASE(CombinationError)
    CASE(UnknownError)
#undef CASE
    default: qDebug() << "Undocumented error!\n";
  }

  qel.exit();
 });

 qel.exec();

 if(reply_locations.isEmpty())
   return {0, 0};

 return {reply_locations.first().coordinate().latitude(),
   reply_locations.first().coordinate().longitude()};

}

