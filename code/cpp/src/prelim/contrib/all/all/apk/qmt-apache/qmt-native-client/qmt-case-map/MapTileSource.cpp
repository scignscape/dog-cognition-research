#include "MapTileSource.h"

#include <QStringBuilder>
#include <QMutexLocker>
#include <QtDebug>
#include <QStringList>
#include <QDataStream>

const QString MAPGRAPHICS_CACHE_FOLDER_NAME = ".MapGraphicsCache";
const quint32 DEFAULT_CACHE_DAYS = 7;
const quint64 MAX_DISK_CACHE_READ_ATTEMPTS = 100000;

MapTileSource::MapTileSource() :
  QObject(), _cacheExpirationsLoaded(false),
  current_local_host_status_(0),
  current_cache_({nullptr, nullptr, nullptr, {}})
{
//
 this->setCacheMode(DiskAndMemCaching);

// this->setCacheMode(NoCaching);


 //We connect this signal/slot pair to communicate across threads.
 connect(this,
         SIGNAL(tileRequested(quint32,quint32,quint8)),
         this,
         SLOT(startTileRequest(quint32,quint32,quint8)),
         Qt::QueuedConnection);

 /*
      When all our tiles have been invalidated, we clear our temp cache so any misinformed clients
      that don't notice will get a null tile instead of an old tile.
    */
 connect(this,
         SIGNAL(allTilesInvalidated()),
         this,
         SLOT(clearTempCache()));
}

void MapTileSource::update_host_cache()
{
// if(cacheMode() == NoCaching)
//   return;

 if(current_cache_.expirations_hash)
   this->saveCacheExpirationsToDisk();

 _cacheExpirationsLoaded = false;

 auto it = caches_.find(current_host_);
 if(it == caches_.end())
 {
  current_cache_ = _Cache { current_host_,
    new QCache<QString, QImage>,
    cacheMode() == NoCaching? nullptr : new QCache<QString, QImage>,
    cacheMode() == NoCaching? nullptr : new QHash<QString, QDateTime>, {}
  };
  caches_[current_host_] = current_cache_;
 }
 else
   current_cache_ = it.value();

 if(cacheMode() != NoCaching)
   loadCacheExpirationsFromDisk();

// _Cache c = caches_.value(current_host_);
// QCache<QString, QImage>* mem = memory_caches_.value(current_host_);
// if(!mem)
// {
//  mem = new QCache<QString, QImage>;
//  memory_caches_[current_host_] = mem;
// }
// current_cache_.memory_cache = mem;

// QCache<QString, QImage>* temp = temp_caches_.value(current_host_);
// if(!temp)
// {
//  temp = new QCache<QString, QImage>;
//  temp_caches_[current_host_] = mem;
// }
// current_temp_cache_ = mem;

   //*temp;

// auto it = memory_caches_.find(current_host_);
// if(it == memory_caches_.end())
// {
//  mem = new
// }
}

MapTileSource::~MapTileSource()
{
 this->saveCacheExpirationsToDisk();

 for(_Cache c : caches_)
 {
  delete c.expirations_hash;
  delete c.temp_cache;
  delete c.memory_cache;
 }
}

void MapTileSource::requestTile(quint32 x, quint32 y, quint8 z)
{
 /*We emit a signal to communicate across threads. MapTileSource (usually) runs in its own
      thread, but this method will be called from a different thread (probably the GUI thread).
      It's easy to communicate across threads with queued signals/slots.
    */
 this->tileRequested(x,y,z);
}

QImage *MapTileSource::getFinishedTile(quint32 x, quint32 y, quint8 z)
{
 const QString cacheID = MapTileSource::createCacheID(x,y,z);
 QMutexLocker lock(&_tempCacheLock);
 if (!current_cache_.temp_cache->contains(cacheID))
 {
  qWarning() << "getFinishedTile() called, but the tile is not present";
  return 0;
 }
 return current_cache_.temp_cache->take(cacheID);
}

MapTileSource::CacheMode MapTileSource::cacheMode() const
{
 return _cacheMode;
}

void MapTileSource::setCacheMode(MapTileSource::CacheMode nMode)
{
// this->setCacheMode(MapTileSource::NoCaching);
// _cacheMode = MapTileSource::NoCaching;
 _cacheMode = nMode;
}

//private slot
void MapTileSource::startTileRequest(quint32 x, quint32 y, quint8 z)
{
 //Check caches for the tile first
 if (this->cacheMode() == DiskAndMemCaching)
 {
  const QString cacheID = MapTileSource::createCacheID(x,y,z);
  QImage* cached = this->fromMemCache(cacheID);
  if (!cached)
   cached = this->fromDiskCache(cacheID);

  //If we got an image from one of the caches, prepare it for the client and return
  if (cached)
  {
   this->prepareRetrievedTile(x,y,z,cached);
   return;
  }
 }
// else
// {
//  qDebug() << "No caching ...";
// }

 //If we get here, the tile was not cached and we must try to retrieve it
 this->fetchTile(x,y,z);
}

//private slot
void MapTileSource::clearTempCache()
{
 if(current_cache_.temp_cache)
   current_cache_.temp_cache->clear();
}

//protected static
QString MapTileSource::createCacheID(quint32 x, quint32 y, quint8 z)
{
 //We use % because it's more efficient to concatenate with QStringBuilder
 QString toRet = QString::number(x) % "," % QString::number(y) % "," % QString::number(z);
 return toRet;
}

//protected static
bool MapTileSource::cacheID2xyz(const QString & string, quint32 *x, quint32 *y, quint32 *z)
{
 QStringList list = string.split(',');
 if (list.size() != 3)
 {
  qWarning() << "Bad cacheID" << string << "cannot convert";
  return false;
 }

 bool ok = true;
 *x = list.at(0).toUInt(&ok);
 if (!ok)
  return false;
 *y = list.at(1).toUInt(&ok);
 if (!ok)
  return false;
 *z = list.at(2).toUInt(&ok);
 return ok;
}

QImage* MapTileSource::fromMemCache(const QString &cacheID)
{
 QImage* toRet = 0;

 if (current_cache_.memory_cache->contains(cacheID))
 {
  //Figure out when the tile we're loading from cache was supposed to expire
  QDateTime expireTime = this->getTileExpirationTime(cacheID);

  //If the cached tile is older than we would like, throw it out
  if (QDateTime::currentDateTimeUtc().secsTo(expireTime) <= 0)
  {
   current_cache_.memory_cache->remove(cacheID);
  }
  //Otherwise, make a copy of the cached tile and return it to the caller
  else
  {
   toRet = new QImage(*current_cache_.memory_cache->object(cacheID));
  }
 }

 return toRet;
}

void MapTileSource::toMemCache(const QString &cacheID, QImage *toCache, const QDateTime &expireTime)
{
 if (toCache == 0)
  return;

 if (current_cache_.memory_cache->contains(cacheID))
  return;

 //?
 if(expireTime == QDateTime::fromSecsSinceEpoch(100'000))
 {
//?  qDebug() << "cache id expired (mem): " << cacheID;
  return;
 }


 //Note when the tile will expire
 this->setTileExpirationTime(cacheID, expireTime);

 //Make a copy of the QImage
 QImage * copy = new QImage(*toCache);
 current_cache_.memory_cache->insert(cacheID,copy);
}

QImage *MapTileSource::fromDiskCache(const QString &cacheID)
{
 //Figure out x,y,z based on the cacheID
 quint32 x,y,z;
 if (!MapTileSource::cacheID2xyz(cacheID,&x,&y,&z))
  return 0;

 //See if we've got it in the cache
 const QString path = this->getDiskCacheFile(x,y,z);
 QFile fp(path);
 if (!fp.exists())
  return 0;

 //Figure out when the tile we're loading from cache was supposed to expire
 QDateTime expireTime = this->getTileExpirationTime(cacheID);

 //If the cached tile is older than we would like, throw it out
 if (QDateTime::currentDateTimeUtc().secsTo(expireTime) <= 0)
 {
  if (!QFile::remove(path))
   qWarning() << "Failed to remove old cache file" << path;
  return 0;
 }

 if (!fp.open(QFile::ReadOnly))
 {
  qWarning() << "Failed to open" << QFileInfo(fp.fileName()).baseName() << "from cache";
  return 0;
 }

 QByteArray data;
 quint64 counter = 0;
 while (data.length() < fp.size())
 {
  data += fp.read(20480);
  if (++counter >= MAX_DISK_CACHE_READ_ATTEMPTS)
  {
   qWarning() << "Reading cache file" << fp.fileName() << "took too long. Aborting.";
   return 0;
  }
 }

 QImage * image = new QImage();
 if (!image->loadFromData(data))
 {
  delete image;
  return 0;
 }

 return image;
}

void MapTileSource::toDiskCache(const QString &cacheID, QImage *toCache, const QDateTime &expireTime)
{
 //?
 if(expireTime ==  QDateTime::fromSecsSinceEpoch(100'000))
 {
  //?
  this->setTileExpirationTime(cacheID, QDateTime());

//?  qDebug() << "cache id expired (disk): " << cacheID;
  return;
 }


 //Figure out x,y,z based on the cacheID
 quint32 x,y,z;
 if (!MapTileSource::cacheID2xyz(cacheID,&x,&y,&z))
  return;

 //Find out where we'll be caching
 const QString filePath = this->getDiskCacheFile(x,y,z);

 //If we've already cached something, do not cache it again
 QFile fp(filePath);
 if (fp.exists())
  return;

 //Note when the tile will expire
 this->setTileExpirationTime(cacheID, expireTime);

 //Auto-detect file format
 const char * format = 0;

 //No compression for lossy file types!
 const int quality = 100;

 //Try to write the data
 if (!toCache->save(filePath,format,quality))
  qWarning() << "Failed to put" << this->name() << x << y << z << "into disk cache";
}

void MapTileSource::prepareRetrievedTile(quint32 x, quint32 y, quint8 z, QImage *image)
{
 //Do tile sanity check here optionally
 if (image == 0)
  return;

 //Put it into the "temporary retrieval cache" so the user can grab it
 QMutexLocker lock(&_tempCacheLock);
 current_cache_.temp_cache->insert(MapTileSource::createCacheID(x,y,z),
                   image);
 /*
      We must explicitly unlock the mutex before emitting tileRetrieved in case
      we're running in the GUI thread (since the signal can trigger
      slots immediately in that case).
    */
 lock.unlock();

 //Emit signal so user knows to call getFinishedTile()
 this->tileRetrieved(x,y,z);
}

void MapTileSource::prepareNewlyReceivedTile(quint32 x, quint32 y, quint8 z, QImage *image,
  QDateTime expireTime)
{
 //image->save("/home/nlevisrael/gits/lantern/img/t1.png");
 //Insert into caches when applicable
 const QString cacheID = MapTileSource::createCacheID(x,y,z);
 if (this->cacheMode() == DiskAndMemCaching)
 {
  this->toMemCache(cacheID, image, expireTime);
  this->toDiskCache(cacheID, image, expireTime);
 }

 //Put the tile in a client-accessible place and notify them
 this->prepareRetrievedTile(x, y, z, image);
}

//protected
QDateTime MapTileSource::getTileExpirationTime(const QString &cacheID)
{
 //Make sure we've got our expiration database loaded
 this->loadCacheExpirationsFromDisk();

 QDateTime expireTime;
 if (current_cache_.expirations_hash->contains(cacheID))
  expireTime = current_cache_.expirations_hash->value(cacheID);
 else
 {
  qWarning() << "Tile" << cacheID << "has unknown expire time. Resetting to default of" << DEFAULT_CACHE_DAYS << "days.";
  expireTime = QDateTime::currentDateTimeUtc().addDays(DEFAULT_CACHE_DAYS);
  current_cache_.expirations_hash->insert(cacheID,expireTime);
 }

 return expireTime;
}

//protected
void MapTileSource::setTileExpirationTime(const QString &cacheID, QDateTime expireTime)
{
 //Make sure we've got our expiration database loaded
 this->loadCacheExpirationsFromDisk();

 //If they told us when the tile expires, store that expiration. Otherwise, use the default.
 if (expireTime.isNull())
 {
  expireTime = QDateTime::currentDateTimeUtc().addDays(DEFAULT_CACHE_DAYS);
 }

 current_cache_.expirations_hash->insert(cacheID, expireTime);
}

//private
QDir MapTileSource::getDiskCacheDirectory(quint32 x, quint32 y, quint8 z) const
{
 Q_UNUSED(y)
 QString pathString = QDir::homePath() % "/" % MAPGRAPHICS_CACHE_FOLDER_NAME % "/" % this->name() % "/" % QString::number(z) % "/" % QString::number(x);
 QDir toRet = QDir(pathString);
 if (!toRet.exists())
 {
  if (!toRet.mkpath(toRet.absolutePath()))
   qWarning() << "Failed to create cache directory" << toRet.absolutePath();
 }
 return toRet;
}

//private
QString MapTileSource::getDiskCacheFile(quint32 x, quint32 y, quint8 z) const
{
 QString toRet = this->getDiskCacheDirectory(x,y,z).absolutePath() % "/" % QString::number(y) % "." % this->tileFileExtension();
 return toRet;
}


QString MapTileSource::make_cache_expirations_file_path()
{
 QDir dir = this->getDiskCacheDirectory(0,0,0);
 QString path = dir.absolutePath() % "/" % "cacheExpirations.db";
 return path;
}

//private
void MapTileSource::loadCacheExpirationsFromDisk()
{
 if (_cacheExpirationsLoaded)
  return;

 //If we try to do this and succeed or even fail, don't try again
 _cacheExpirationsLoaded = true;

 QString path = make_cache_expirations_file_path();

 QFile fp(path);
 if (!fp.exists())
   return;

 if (!fp.open(QIODevice::ReadOnly))
 {
  qWarning() << "Failed to open cache expiration file for reading:" << fp.errorString();
  return;
 }

 current_cache_.expirations_file = path;

 QDataStream stream(&fp);
 stream >> *current_cache_.expirations_hash;
}

void MapTileSource::saveCacheExpirationsToDisk()
{
 if (!_cacheExpirationsLoaded || current_cache_.expirations_file.isEmpty())
  return;

 QFile fp(current_cache_.expirations_file);

 if (!fp.open(QIODevice::Truncate | QIODevice::WriteOnly))
 {
  qWarning() << "Failed to open cache expiration file for writing:" << fp.errorString();
  return;
 }

 QDataStream stream(&fp);
 stream << *current_cache_.expirations_hash;
 qDebug() << "Cache expirations saved to" << current_cache_.expirations_file;
}
