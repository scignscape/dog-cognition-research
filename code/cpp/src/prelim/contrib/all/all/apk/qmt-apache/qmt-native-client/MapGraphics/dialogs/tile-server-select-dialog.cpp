
//          Copyright Nathaniel Christen 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include "tile-server-select-dialog.h"

#include "nlohmann-fifo-map.h"

#include "global-types.h"
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


Tile_Server_Select_Dialog::Tile_Server_Select_Dialog(int index, QString current_host, QWidget* parent)
  : QDialog(parent)
{
 button_box_ = new QDialogButtonBox(this);

 button_proceed_ = new QPushButton("OK");
 button_cancel_ = new QPushButton("Cancel");

 button_proceed_->setDefault(false);
 button_proceed_->setAutoDefault(false);

 button_cancel_->setDefault(true);

 button_proceed_->setEnabled(false);


 button_box_->addButton(button_cancel_, QDialogButtonBox::RejectRole);
 button_box_->addButton(button_proceed_, QDialogButtonBox::ApplyRole);

// button_ok_->setStyleSheet(basic_button_style_sheet_());
// button_proceed_->setStyleSheet(basic_button_style_sheet_());
// button_cancel_->setStyleSheet(basic_button_style_sheet_());

 connect(button_proceed_, SIGNAL(clicked()), this, SLOT(proceed()));
 connect(button_box_, SIGNAL(rejected()), this, SLOT(cancel()));

 main_layout_ = new QVBoxLayout;
 form_layout_ = new QFormLayout;

 server_name_combo_box_ = new QComboBox(this);
 overlay_combo_box_ = new QComboBox(this);
 local_server_combo_box_ = new QComboBox(this);

 nlohmann::fifo_map<QString, QPair<QString, QString>> hosts_map {
  { "https://b.tile.openstreetmap.org/", {"OpenStreetMap", "%1/%2/%3.png"} },
  { "https://b.tile.openstreetmap.fr/hot/", {"OpenStreetMap (French Style)", "%1/%2/%3.png"} },
  { "https://tile.thunderforest.com/cycle/", {"Thunder Forest (cycle)", "%1/%2/%3.png"} },
  { "https://tile.thunderforest.com/transport/", {"Thunder Forest (transport)",  "%1/%2/%3.png"} },
  { "https://tile.thunderforest.com/outdoors/", { "Thunder Forest (outdoors)", "%1/%2/%3.png"} },
  { "https://api.wikiocity.com/r/raster/en/", {"Wikiocity", "%1/%2/%3.png"} },

  { "https://maps.nyc.gov/xyz/1.0.0/photo/2016/", {"NYC-photo-2016", "%1/%2/%3.png8"} },
  { "https://maps.nyc.gov/xyz/1.0.0/carto/basemap/", {"NYC-carto", "%1/%2/%3.jpg"} },

  { "https://cartodb-basemaps-a.global.ssl.fastly.net/light_all/", {"cartodb", "%1/%2/%3.png"} },
  { "https://stamen-tiles.a.ssl.fastly.net/terrain/", {"Stamen (terrain)", "%1/%2/%3.png"} },
  { "https://stamen-tiles.a.ssl.fastly.net/watercolor/", {"Stamen (watercolor)", "%1/%2/%3.jpg"} },
  { "https://gis.apfo.usda.gov/arcgis/rest/services/NAIP/USDA_CONUS_PRIME/ImageServer/tile/", {"apfo",  "%1/%3/%2"} },
  { "https://tile.opentopomap.org/", {"Topomap", "%1/%2/%3.png"} },
  { "https://services.arcgisonline.com/arcgis/rest/services/World_Imagery/MapServer/tile/", {"ArcGIS", "%1/%3/%2"} }
     };

 QStringList names;

 auto transform = [&hosts_map, this](QStringList* qsl) {
  std::transform(hosts_map.begin(), hosts_map.end(),
    std::back_inserter(*qsl),
    [qsl, this](decltype(hosts_map)::value_type const& pair)
  {
   return (qsl == &known_hosts_)? pair.first :
     (qsl == &known_urls_)? pair.second.second : pair.second.first;
  }
  );
 };

 for(QStringList* qsl: QVector<QStringList*> {&names, &known_hosts_, &known_urls_})
   transform(qsl);


 server_name_combo_box_->addItems(names);


 if(index)
 {
  server_name_combo_box_->setCurrentIndex(index);
  current_host_ = known_hosts_.value(index - 1);
 }
 else
   current_host_ = current_host.isEmpty()? known_hosts_.first() : current_host_;


 auto connect_for_button_proceed_enabled = [this](QComboBox* cb)
 {
  connect(cb, QOverload<int>::of(&QComboBox::currentIndexChanged),
    [this](int)
  {
   button_proceed_->setEnabled(true);
   button_proceed_->setDefault(true);
  });
 };

 connect_for_button_proceed_enabled(server_name_combo_box_);
 connect_for_button_proceed_enabled(overlay_combo_box_);
 connect_for_button_proceed_enabled(local_server_combo_box_);


 overlay_combo_box_->addItems({"None", "Bus", "Train",
   "Cycle", "Hike"});

 local_server_combo_box_->addItems({"No Local Server",
   "QMT (port 6600)",
   "Late Nympth", "Adult", "Unknown/Unidentified"});

 api_key_ = new QLineEdit(this);
 api_key_->setPlaceholderText("(if needed for the server)");


 form_layout_->addRow("Name:", server_name_combo_box_);
 form_layout_->addRow("Overlays:", overlay_combo_box_);
 form_layout_->addRow("Local Server:", local_server_combo_box_);

 form_layout_->addRow("API Key:", api_key_);


 main_layout_->addLayout(form_layout_);

 main_layout_->addWidget(button_box_);

 setLayout(main_layout_);

 setWindowTitle("Select Tile Server");

}

//top_buttons_layout_ = new QHBoxLayout;

//take_screenshot_button_ = new QPushButton("Screenshot", this);

//activate_tcp_button_ = new QPushButton("Activate TCP", this);

//take_screenshot_button_->setStyleSheet(colorful_button_style_sheet_());
//activate_tcp_button_->setStyleSheet(colorful_button_style_sheet_());

//connect(take_screenshot_button_, SIGNAL(clicked()),
//  this, SLOT(handle_take_screenshot_requested()));

//connect(activate_tcp_button_, SIGNAL(clicked()),
//  this, SLOT(activate_tcp_requested()));

//top_buttons_layout_->addStretch();

//top_buttons_layout_->addWidget(activate_tcp_button_);

//top_buttons_layout_->addWidget(take_screenshot_button_);

//?  https://www.openstreetmap.org/#map=16/40.8561/-73.9780&layers=T

//   hosts = QStringList{"http://b.tile.openstreetmap.org/"};
//   urls = QStringList{"%1/%2/%3.png"};

//      hosts = QStringList{"https://tile.openstreetmap.org/"};
//      urls = QStringList{"%1/%2/%3.png"};

//         hosts = QStringList{"https://tile.openstreetmap.de/"};
//         urls = QStringList{"%1/%2/%3.png"};

//            hosts = QStringList{"https://tile.thunderforest.com/cycle/"};
//            urls = QStringList{"%1/%2/%3.png"};

//       hosts = QStringList{"https://b.tile.openstreetmap.fr/hot/"};
//       urls = QStringList{"%1/%2/%3.png"};

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


void Tile_Server_Select_Dialog::proceed()
{
 int ci = server_name_combo_box_->currentIndex();
 QString host = known_hosts_.value(ci);
 if(host == current_host_)
 {

 }

 Q_EMIT update_requested(this, Summary{
   ci, host, known_urls_[ci], api_key_->text(), {}
  });
}



Tile_Server_Select_Dialog::~Tile_Server_Select_Dialog()
{

}

void Tile_Server_Select_Dialog::cancel()
{
 Q_EMIT(rejected());
 Q_EMIT(canceled(this));
 Q_EMIT(rejected());
 close();
}

void Tile_Server_Select_Dialog::accept()
{
 //Q_EMIT(accepted(this));
}
