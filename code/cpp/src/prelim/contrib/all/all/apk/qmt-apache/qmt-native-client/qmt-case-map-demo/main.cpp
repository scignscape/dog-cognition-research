
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include <QApplication>
#include <QtDebug>
#include <QMainWindow>
#include <QPushButton>

#include "main-window.h"


#include <QGeoCodingManager>

#include <QGeoCodingManagerEngine>

#include <QGeoServiceProvider>

#include "global-types.h"


#include <iostream>
#include <sstream>

// Qt header:
#include <QtWidgets>
#include <QGeoAddress>
#include <QGeoCodingManager>
#include <QGeoCoordinate>
#include <QGeoLocation>
#include <QGeoServiceProvider>

void log(QTextEdit &qTxtLog, const QString &qString)
{
  qTxtLog.setPlainText(qTxtLog.toPlainText() + qString);
  qTxtLog.moveCursor(QTextCursor::End);
}
void log(QTextEdit &qTxtLog, const char *text)
{
  log(qTxtLog, QString::fromUtf8(text));
}
void log(QTextEdit &qTxtLog, const std::string &text)
{
  log(qTxtLog, text.c_str());
}

int main5(int argc, char **argv)
{
  qDebug() << "Qt Version:" << QT_VERSION_STR;
  // main application
  QApplication app(argc, argv);
  // setup GUI
  QWidget qWin;
  QVBoxLayout qBox;
  QFormLayout qForm;
  QLabel qLblCountry(QString::fromUtf8("Country:"));
  QLineEdit qTxtCountry;
  qForm.addRow(&qLblCountry, &qTxtCountry);
  QLabel qLblZipCode(QString::fromUtf8("Postal Code:"));
  QLineEdit qTxtZipCode;
  qForm.addRow(&qLblZipCode, &qTxtZipCode);
  QLabel qLblCity(QString::fromUtf8("City:"));
  QLineEdit qTxtCity;
  qForm.addRow(&qLblCity, &qTxtCity);
  QLabel qLblStreet(QString::fromUtf8("Street:"));
  QLineEdit qTxtStreet;
  qForm.addRow(&qLblStreet, &qTxtStreet);
  QLabel qLblProvider(QString::fromUtf8("Provider:"));
  QComboBox qLstProviders;
  qForm.addRow(&qLblProvider, &qLstProviders);
  qBox.addLayout(&qForm);
  QPushButton qBtnFind(QString::fromUtf8("Find Coordinates"));
  qBox.addWidget(&qBtnFind);
  QLabel qLblLog(QString::fromUtf8("Log:"));
  qBox.addWidget(&qLblLog);
  QTextEdit qTxtLog;
  qTxtLog.setReadOnly(true);
  qBox.addWidget(&qTxtLog);
  qWin.setLayout(&qBox);
  qWin.show();
  // initialize Geo Service Providers
  std::vector<QGeoServiceProvider*> pQGeoProviders;
  { std::ostringstream out;
    QStringList qGeoSrvList
      = QGeoServiceProvider::availableServiceProviders();
    for (QString entry : qGeoSrvList) {
      out << "Try service: " << entry.toStdString() << '\n';
      // choose provider
      QGeoServiceProvider *pQGeoProvider = new QGeoServiceProvider(entry);
      if (!pQGeoProvider) {
        out
          << "ERROR: GeoServiceProvider '" << entry.toStdString()
          << "' not available!\n";
        continue;
      }
      QGeoCodingManager *pQGeoCoder = pQGeoProvider->geocodingManager();
      if (!pQGeoCoder) {
        out
          << "ERROR: GeoCodingManager '" << entry.toStdString()
          << "' not available!\n";
        delete pQGeoProvider;
        continue;
      }
      QLocale qLocaleC(QLocale::C, QLocale::AnyCountry);
      pQGeoCoder->setLocale(qLocaleC);
      qLstProviders.addItem(entry);
      pQGeoProviders.push_back(pQGeoProvider);
      out << "Service " << entry.toStdString() << " available.\n";
    }
    log(qTxtLog, out.str());
  }
  if (pQGeoProviders.empty()) qBtnFind.setEnabled(false);
  // install signal handlers
  QObject::connect(&qBtnFind, &QPushButton::clicked,
    [&]() {
      // get current geo service provider
      QGeoServiceProvider *pQGeoProvider
        = pQGeoProviders[qLstProviders.currentIndex()];
      // fill in request
      QGeoAddress *pQGeoAddr = new QGeoAddress;
      pQGeoAddr->setCountry(qTxtCountry.text());
      pQGeoAddr->setPostalCode(qTxtZipCode.text());
      pQGeoAddr->setCity(qTxtCity.text());
      pQGeoAddr->setStreet(qTxtStreet.text());
      QGeoCodeReply *pQGeoCode
        = pQGeoProvider->geocodingManager()->geocode(*pQGeoAddr);
      if (!pQGeoCode) {
        delete pQGeoAddr;
        log(qTxtLog, "GeoCoding totally failed!\n");
        return;
      }
      { std::ostringstream out;
        out << "Sending request for:\n"
          << pQGeoAddr->country().toUtf8().data() << "; "
          << pQGeoAddr->postalCode().toUtf8().data() << "; "
          << pQGeoAddr->city().toUtf8().data() << "; "
          << pQGeoAddr->street().toUtf8().data() << "...\n";
        log(qTxtLog, out.str());
      }
      // install signal handler to process result later
      QObject::connect(pQGeoCode, &QGeoCodeReply::finished,
        [&qTxtLog, pQGeoAddr, pQGeoCode]() {
          // process reply
          std::ostringstream out;
          out << "Reply: " << pQGeoCode->errorString().toStdString() << '\n';
          switch (pQGeoCode->error()) {
            case QGeoCodeReply::NoError: {
              // eval result
              QList<QGeoLocation> qGeoLocs = pQGeoCode->locations();
              out << qGeoLocs.size() << " location(s) returned.\n";
              for (QGeoLocation &qGeoLoc : qGeoLocs) {
                qGeoLoc.setAddress(*pQGeoAddr);
                QGeoCoordinate qGeoCoord = qGeoLoc.coordinate();
                out
                  << "Lat.:  " << qGeoCoord.latitude() << '\n'
                  << "Long.: " << qGeoCoord.longitude() << '\n'
                  << "Alt.:  " << qGeoCoord.altitude() << '\n';
              }
            } break;
#define CASE(ERROR) \
            case QGeoCodeReply::ERROR: out << #ERROR << '\n'; break
            CASE(EngineNotSetError);
            CASE(CommunicationError);
            CASE(ParseError);
            CASE(UnsupportedOptionError);
            CASE(CombinationError);
            CASE(UnknownError);
#undef CASE
            default: out << "Undocumented error!\n";
          }
          // log result
          log(qTxtLog, out.str());
          // clean-up
          delete pQGeoAddr;
          /* delete sender in signal handler could be lethal
           * Hence, delete it later...
           */
          pQGeoCode->deleteLater();
        });
    });
  // fill in a sample request with a known address initially
  qTxtCountry.setText(QString::fromUtf8("Germany"));
  qTxtZipCode.setText(QString::fromUtf8("88250"));
  qTxtCity.setText(QString::fromUtf8("Weingarten"));
  qTxtStreet.setText(QString::fromUtf8("Danziger Str. 3"));
  // runtime loop
  app.exec();
  // done
  return 0;
}

#include <QEventLoop>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkAccessManager>

int main4(int argc, char *argv[])
{
 QApplication qapp(argc, argv);

 QGeoServiceProvider gsp("osm");
 QGeoCodingManager* gcm = gsp.geocodingManager();

// QGeoServiceProvider gsp("esri");
// QGeoCodingManager* gcm = gsp.geocodingManager();

 QGeoAddress* pQGeoAddr = new QGeoAddress;

 pQGeoAddr->setCountry("USA");
 pQGeoAddr->setPostalCode("07024");
 pQGeoAddr->setCity("Fort Lee");
 pQGeoAddr->setState("NJ");
 pQGeoAddr->setStreet("320 Main Street");

// pQGeoAddr->setStreetNumber("320MainStreet");
// pQGeoAddr->setText("1A");


// pQGeoAddr->setCountry("Germany");
// pQGeoAddr->setPostalCode("88250");
// pQGeoAddr->setCity("Weingarten");
// pQGeoAddr->setStreet("Danziger");


 QGeoCodeReply* pQGeoCode
   = gcm->geocode(*pQGeoAddr);

// QGeoCodeReply* pQGeoCode
//   = gcm->geocode("320MainStreet,1A,FortLee,NJ,USA");


// QString ss = QSslSocket::sslLibraryBuildVersionString();
// qDebug() << "sslLibraryBuildVersionString = " << ss;

// if(QSslSocket::supportsSsl())
//   qDebug() << "supportsSsl";
// else
//   qDebug() << "!supportsSsl";


// QNetworkRequest qnr;
// qnr.setUrl(QUrl(
//   "http://geocode.arcgis.com/arcgis/rest/services/World/GeocodeServer/findAddressCandidates?singleLine=320MainStreet,1A,FortLee,NJ,USA&f=json&outFields=*"));

// QNetworkAccessManager qnam;

 QEventLoop qel;

// QNetworkReply* reply = qnam.get(qnr);

// QObject::connect(reply, &QNetworkReply::finished, [reply, &qel]()
// {
//  QByteArray qba = reply->readAll();
//  qDebug() << "qba = " << qba;

//  qel.exit();
// });

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
   return 0;

 QGeoLocation loc1 = reply_locations.first();
 r8 lat1 = loc1.coordinate().latitude();
 r8 lon1 = loc1.coordinate().longitude();

 qDebug() << "lat 1 = " << lat1 << " and lon 1 = " << lon1;

 r8 lat = -74.0271;
 r8 lon = 40.8896;


 QGeoLocation loc2;
 loc2.setCoordinate(QGeoCoordinate(lat, lon));


 QGeoCodeReply* gcr
   = gcm->reverseGeocode(loc2.coordinate());

 QObject::connect(gcr, &QGeoCodeReply::finished,
   [&qel, gcr]
 {

  switch (gcr->error())
  {
   case QGeoCodeReply::NoError:
     qDebug() << "address: " << gcr->locations().first().address().text();
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

  qDebug() << gcr->errorString();

  qel.exit();
 });



 qel.exec();


// QGeoCodingManagerEngine gcme()
// QGeoCodingManager m();
// QGeoCodeReply* gcr = m.geocode();

//    QApplication a(argc, argv);

//    Lanternfly_Main_Window w;
//    w.show();

//    return a.exec();
}



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Lanternfly_Main_Window w;
    w.show();

    return a.exec();
}
