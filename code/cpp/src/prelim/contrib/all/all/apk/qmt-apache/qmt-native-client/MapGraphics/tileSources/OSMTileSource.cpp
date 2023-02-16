

#include "OSMTileSource.h"

#include "guts/MapGraphicsNetwork.h"

#include <cmath>
#include <QPainter>
#include <QStringBuilder>
#include <QtDebug>
#include <QNetworkReply>

#include "qmt/qmt-resource-info.h"

const qreal PI = 3.14159265358979323846;
const qreal deg2rad = PI / 180.0;
const qreal rad2deg = 180.0 / PI;

OSMTileSource::OSMTileSource(OSMTileType tileType) :
  MapTileSource(), _tileType(tileType)
{
 this->setCacheMode(MapTileSource::DiskAndMemCaching);
}

OSMTileSource::~OSMTileSource()
{
 qDebug() << this << this->name() << "Destructing";
}

QPointF OSMTileSource::ll2qgs(const QPointF &ll, quint8 zoomLevel) const
{
 const qreal tilesOnOneEdge = pow(2.0,zoomLevel);
 const quint16 tileSize = this->tileSize();
 qreal x = (ll.x()+180) * (tilesOnOneEdge*tileSize)/360; // coord to pixel!
 qreal y = (1-(log(tan(PI/4+(ll.y()*deg2rad)/2)) /PI)) /2  * (tilesOnOneEdge*tileSize);

 return QPoint(int(x), int(y));
}

QPointF OSMTileSource::qgs2ll(const QPointF &qgs, quint8 zoomLevel) const
{
 const qreal tilesOnOneEdge = pow(2.0,zoomLevel);
 const quint16 tileSize = this->tileSize();
 qreal longitude = (qgs.x()*(360/(tilesOnOneEdge*tileSize)))-180;
 qreal latitude = rad2deg*(atan(sinh((1-qgs.y()*(2/(tilesOnOneEdge*tileSize)))*PI)));

 return QPointF(longitude, latitude);
}

quint64 OSMTileSource::tilesOnZoomLevel(quint8 zoomLevel) const
{
 return pow(4.0,zoomLevel);
}

quint16 OSMTileSource::tileSize() const
{
 return 256;
}

quint8 OSMTileSource::minZoomLevel(QPointF ll)
{
 Q_UNUSED(ll)
 return 0;
}

quint8 OSMTileSource::maxZoomLevel(QPointF ll)
{
 Q_UNUSED(ll)
 return 18;
}

QString OSMTileSource::name() const
{
 QString current_host = current_host_;

 if(current_host.startsWith("https://"))
   current_host = current_host.mid(8);
 else if(current_host.startsWith("http://"))
   current_host = current_host.mid(7);
 current_host.replace('/', '>')
   .replace('.', '<');

 //?.replace(':', '$')

 switch(_tileType)
 {
 case OSMTiles:
  return "OpenStreetMap-Tiles~" + current_host;
  break;

 default:
  return "Unknown-Tiles";
  break;
 }
}

QString OSMTileSource::tileFileExtension() const
{
 if (_tileType == OSMTiles)
  return "png";
 else
  return "jpg";
}

//protected
void OSMTileSource::fetchTile(quint32 x, quint32 y, quint8 z)
{
 fetchTile(x, y, z, 0, -1);
}


void OSMTileSource::update_host_cache()
{
 _pendingReplies.clear();
 _pendingRequests.clear();
 this->MapTileSource::update_host_cache();
}


void OSMTileSource::fetchTile(quint32 x, quint32 y, quint8 z, quint8 alternate, qint64 force_expiry)
{
 MapGraphicsNetwork * network = MapGraphicsNetwork::getInstance();

 QStringList hosts;
 QStringList urls;
 QString fetchURL;
 //QString url;

 //Figure out which server to request from based on our desired tile type
// if(preset_source.isEmpty())
// {
  if (_tileType == OSMTiles)
  {
   if(current_local_host_.isEmpty())
   {
    hosts = QStringList{current_host_};
    urls = QStringList{current_url_};
   }
   else if(current_local_info_host_.isEmpty())
   {
    hosts = QStringList{current_local_host_, current_host_};
    urls = QStringList{current_local_url_, current_url_};
   }
   else
   {
    hosts = QStringList{current_local_info_host_, current_local_host_, current_host_};
    //   hosts = QStringList{"http://localhost:6600/qmt/rI~png/~tiles/kherson/~osm-",
    //     "http://localhost:6600/qmt/rS~png/~tiles/kherson/~osm-",

     urls = QStringList{current_local_info_url_, current_local_url_, current_url_};

//       "%1-%2-%3",
//         "%1-%2-%3",
//          "%1/%2/%3.png"

    //?
   }
  }

 fetchURL = urls[alternate].arg(QString::number(z),
                                   QString::number(x),
                                   QString::number(y));

 //Use the unique cacheID to see if this tile has already been requested
 QString cacheID = this->createCacheID(x,y,z);

 cacheID += ":" + QString::number(alternate);

 if(current_local_host_status_ < 0)
 {
  qDebug() << " (deactivated) cacheID: " << cacheID;
 }

 if (_pendingRequests.contains(cacheID))
 {
  if(current_local_host_status_ < 0)
  {
   qDebug() << "pending: " << cacheID;
  }
  else //?
  return;
 }
 _pendingRequests.insert(cacheID);

 //Build the request
 qDebug() << "fetchURL = " << (hosts[alternate] + fetchURL);

 QNetworkRequest request(QUrl(hosts[alternate] + fetchURL));

 if(alternate == 0)
   hosts[0] = cacheID;
 else
   hosts = QStringList{cacheID};

 //Send the request and setupd a signal to ensure we're notified when it finishes
 QNetworkReply * reply = network->get(request);
 _pendingReplies.insert(reply,{hosts, force_expiry});

 connect(reply,
         SIGNAL(finished()),
         this,
         SLOT(handleNetworkRequestFinished()));


}

//private slot
void OSMTileSource::handleNetworkRequestFinished()
{
 QObject * sender = QObject::sender();
 QNetworkReply * reply = qobject_cast<QNetworkReply *>(sender);

 if (reply == 0)
 {
  qWarning() << "QNetworkReply cast failure";
  return;
 }

 /*
      We can do this here and use reply later in the function because the reply
      won't be deleted until execution returns to the event loop.
    */
 reply->deleteLater();

 if (!_pendingReplies.contains(reply))
 {
  qWarning() << "Unknown QNetworkReply";
  return;
 }

 //get the cacheID
 QPair<QStringList, qint64> pr = _pendingReplies.take(reply);
 QStringList host = pr.first;
 qint64 forced_expiry = pr.second;
 QString cacheID = host.takeFirst();

 QString ocacheID = cacheID;

 if(int index = cacheID.indexOf(':'))
   cacheID.chop(cacheID.length() - index);


//? _pendingRequests.remove(cacheID);
 _pendingRequests.remove(ocacheID);

 quint32 x,y,z;
 if (!MapTileSource::cacheID2xyz(cacheID,&x,&y,&z))
 {
  qWarning() << "Failed to convert cacheID" << cacheID << "back to xyz";
  return;
 }

 if (reply->error() != QNetworkReply::NoError)
 {
  if(host.isEmpty())
  {
   //If there was a network error, ignore the reply
   qDebug() << "Network Error:" << reply->errorString();
   return;
  }
  if(host.size() == 1)
  {
   // // this means that we started with two hosts,
    //   presumably one local and one not
   fetchTile(x, y, z, 1, -1);
   return;
  }
  // // this is the intended setup where we start
   //   with (at least) three hosts,
   //   the first two being local and the
   //   first for resource info
  fetchTile(x, y, z, 2, -1);
  return;
 }

 QByteArray bytes = reply->readAll();


 if(host.isEmpty())
 {
  // //  this means the reply is an actual image
  //Convert the cacheID back into x,y,z tile coordinates

  if(current_local_host_status_ < 0)
  {
   qDebug() << " (deactivated) finished: " << ocacheID << " | " << cacheID;
  }

  QImage image;// = new QImage();

  if (!image.loadFromData(bytes))
  {
   //delete image;
   qWarning() << "Failed to make QImage from network bytes";
   return;
  }

  // //  todo 256 should not be hard-coded
  QImage* scaled_image = new QImage(image.scaled(256, 256));


  //Figure out how long the tile should be cached
  QDateTime expireTime;
  if(forced_expiry == 0)
  {
//?    qDebug() << "cache id should expire: " << cacheID;

     expireTime = QDateTime::fromSecsSinceEpoch(100'000);
  }
  else if(forced_expiry > 0)
    expireTime = QDateTime::currentDateTimeUtc().addSecs(forced_expiry);
  else

   if (reply->hasRawHeader("Cache-Control"))
  {
   //We support the max-age directive only for now
   const QByteArray cacheControl = reply->rawHeader("Cache-Control");
   QRegExp maxAgeFinder("max-age=(\\d+)");
   if (maxAgeFinder.indexIn(cacheControl) != -1)
   {
    bool ok = false;
    const qint64 delta = maxAgeFinder.cap(1).toULongLong(&ok);

    if (ok)
     expireTime = QDateTime::currentDateTimeUtc().addSecs(delta);
   }
  }

  //Notify client of tile retrieval
  this->prepareNewlyReceivedTile(x,y,z, scaled_image, expireTime);
 }
 else
 {
  if(current_local_host_status_ < 0)
  {
   qDebug() << "deactivated: " << ocacheID << " | " << cacheID;
    // // deactivated ...
   fetchTile(x, y, z, 2, -1);
   return;
  }

  // //  this means the reply is info
  QMT_Resource_Info qri;
  qri.absorb_data(bytes);

//      fetchTile(x, y, z, 2);

  qDebug() << "qri size = " << qri.size();

  if(qri.size() == (u4) -1)
   // //  use second alternate
    fetchTile(x, y, z, 2, -1);
  else
    // //  use first alternate
    fetchTile(x, y, z, 1, 0);

 }

}


//?     host = "http://newjersey.maps.arcgis.com/apps/mapviewer/index.html";
//     host = "http://api.wikiocity.com/map#";
//     host = "http://b.tile.openstreetmap.org/";
//     url = "%1/%2/%3.png";

//?hosts = QStringList{"http://b.tile.openstreetmap.org/"};

//?
//   hosts = QStringList{"http://b.tile.openstreetmap.org/"};
//   urls = QStringList{"%1/%2/%3.png"};

//      hosts = QStringList{"https://tile.openstreetmap.org/"};
//      urls = QStringList{"%1/%2/%3.png"};

//         hosts = QStringList{"https://tile.openstreetmap.de/"};
//         urls = QStringList{"%1/%2/%3.png"};

//            hosts = QStringList{"https://tile.thunderforest.com/cycle/"};
//            urls = QStringList{"%1/%2/%3.png"};

//   hosts = QStringList{"https://b.tile.openstreetmap.fr/hot/"};
//   urls = QStringList{"%1/%2/%3.png"};

//      hosts = QStringList{"https://tile.thunderforest.com/transport/"};
//      urls = QStringList{"%1/%2/%3.png"};

//               hosts = QStringList{"https://api.wikiocity.com/r/raster/en/"};
//               urls = QStringList{"%1/%2/%3.png"};

//      hosts = QStringList{"https://tile.thunderforest.com/outdoors/"};
//      urls = QStringList{"%1/%2/%3.png"};

//?      hosts = QStringList{"https://cartodb-basemaps-a.global.ssl.fastly.net/light_all/"};
//      urls = QStringList{"%1/%2/%3.png"};


   //https://tile.tracestrack.com/en/{z}/{x}/{y}.png
  // https://maps.geoapify.com/v1/tile/osm-bright-smooth/{z}/{x}/{y}.png

//         hosts = QStringList{"https://tile.tracestrack.com/bus-route/"};
//         urls = QStringList{"%1/%2/%3.png?key=bb0a959e5202daa5a0e923268a36b09e"};

//   hosts = QStringList{"https://tile.tracestrack.com/base/"};
//   urls = QStringList{"%1/%2/%3.png?key=bb0a959e5202daa5a0e923268a36b09e"};

//         hosts = QStringList{"https://tile.tracestrack.com/en-name/"};
//         urls = QStringList{"%1/%2/%3.png?key=bb0a959e5202daa5a0e923268a36b09e"};


// status line or log to show/monitor network traffic,
// including tile urls,

   // https://tile.waymarkedtrails.org/hiking/${z}/${x}/${y}.png
   // https://tile.waymarkedtrails.org/cycling/${z}/${x}/${y}.png
   // https://tile.tracestrack.com/bus-route/${z}/${x}/${y}.png
   // https://tile.tracestrack.com/subway-route/${z}/${x}/${y}.png
   // https://tile.tracestrack.com/train-route/${z}/${x}/${y}.png
   // https://tile.tracestrack.com/bicycle-route/${z}/${x}/${y}.png


//   hosts = QStringList{"https://tile.waymarkedtrails.org/cycling/"};
//            urls = QStringList{"%1/%2/%3.png"};




//   hosts = QStringList{"https://stamen-tiles.a.ssl.fastly.net/terrain/"};
//   urls = QStringList{"%1/%2/%3.png"};

//      hosts = QStringList{"https://stamen-tiles.a.ssl.fastly.net/watercolor/"};
//      urls = QStringList{"%1/%2/%3.jpg"};

//   hosts = QStringList{"https://gis.apfo.usda.gov/arcgis/rest/services/NAIP/USDA_CONUS_PRIME/ImageServer/tile/"};
//   urls = QStringList{"%1/%3/%2"};


//   hosts = QStringList{"https://services.arcgisonline.com/arcgis/rest/services/World_Imagery/MapServer/tile/"};
//   urls = QStringList{"%1/%3/%2"};

// hosts = QStringList{"https://tile.opentopomap.org/"};
// urls = QStringList{"%1/%2/%3.png"};


//    hosts = QStringList{"https://b.tile-cyclosm.openstreetmap.fr/cyclosm/"};
//    urls = QStringList{"%1/%2/%3.png"};



//?
//   hosts = QStringList{"http://localhost:6600/qmt/rI~png/~tiles/kherson/~osm-",
//     "http://localhost:6600/qmt/rS~png/~tiles/kherson/~osm-",
//     "http://b.tile.openstreetmap.org/"};

//   urls = QStringList{"%1-%2-%3",
//     "%1-%2-%3",
//      "%1/%2/%3.png"};

