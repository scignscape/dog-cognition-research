
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "qmt-render-broker.h"

#include "qt-logger.h"

#include "qmt-tile-object.h"

#include <QtMath>

#include <QDebug>

#include "server/request_manager.hpp"


#include "general/configuration.hpp"
#include "general/geodata.hpp"

#include "server/cache.hpp"
#include "server/http_server.hpp"
#include "server/renderer/renderer.hpp"
#include "server/request_manager.hpp"
#include "server/stylesheet_manager.hpp"

#include <QFileInfo>



QMT_Render_Broker::QMT_Render_Broker(QString geodata_file, RequestManager* request_manager)
  : geodata_file_(geodata_file),
    zoom_min_(0), zoom_max_(0),
    x_min_(0), x_max_(0), y_min_(0), y_max_(0),
    request_manager_(request_manager)
{
 configuration_qmap_ = QMap<QString, QString> {
  {"logfile", ALACARTE_RUNTIME_FOLDER "/system/var/log/alacarte-maps/info.log"},
  {"access-log", ALACARTE_RUNTIME_FOLDER "/system/var/log/alacarte-maps/access.log"},
  {"geo-data", geodata_file_},

  {"server.style-src", ALACARTE_FACTORY_FOLDER "/styles/mapcss"},

  {"#server.prerender-level", "12"},
  {"server.default-tile", ALACARTE_RUNTIME_FOLDER "/default.png"},
  {"#server.cache-size", "1024"},
  {"server.cache-path", ALACARTE_RUNTIME_FOLDER "/cache"},

  {"server.default-style", "default"},
  {"#server.parse-timeout", "1500"}, // // the code has default value 750



//  {"server.cache-keep-tile", "#0"},

//  cache-keep-tile

 };

 init();
}

void  QMT_Render_Broker::init()
{
 shared_ptr<Configuration> config = boost::make_shared<Configuration>();


 config->set_suppmental_qmap(&configuration_qmap_);

 Statistic::Init(config);

 //config.

 shared_ptr<Geodata> geodata = boost::make_shared<Geodata>();

 geodata->load(geodata_file_.toStdString());

 shared_ptr<Cache> cache = boost::make_shared<Cache>(config);
 shared_ptr<StylesheetManager> ssm = boost::make_shared<StylesheetManager>(config);
 shared_ptr<Renderer> renderer = boost::make_shared<Renderer>(geodata);


// shared_ptr<RequestManager> req_manager = make_shared<RequestManager>(config, geodata, renderer, cache, ssm);

 if(!request_manager_)
   request_manager_ = boost::make_shared<RequestManager>(this, config, geodata, renderer, cache, ssm);

 ssm->startStylesheetObserving(request_manager_);


}



void QMT_Render_Broker::generate_png()
{
 QString sn = stylesheet_path_name_;

 if(sn.isEmpty())
   sn = "default";

 request_manager_->push_factory();

 QString pattern = out_file_pattern_.replace('|', "-%1-%2-%3");

 for(u4 z = 0, zoom = zoom_min_; zoom <= zoom_max_; ++zoom, ++z)
 {
  for(u4 x = x_min_[z]; x <= x_max_[z]; ++x)
   for(u4 y = y_min_[z]; y <= y_max_[z]; ++y)
   {
    QFileInfo qfi(pattern.arg(zoom).arg(x).arg(y));

    QString out_file = qfi.absoluteFilePath();

    qDebug() << "\nRendering: " << out_file << "\n";

    QMT_Tile_Object_Coordinates coords {(u1)zoom, x, y, &out_file};
    request_manager_->create_and_run_job(&coords, "png",
      stylesheet_folder_path_.toStdString(), sn.toStdString());
   }
 }

 request_manager_->pop_factory();

}
