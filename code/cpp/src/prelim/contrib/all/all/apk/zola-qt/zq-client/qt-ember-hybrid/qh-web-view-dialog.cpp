
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "qh-web-view-dialog.h"

#include <QPushButton>
#include <QTabBar>

#include <QHeaderView>

#include <QRegularExpression>

//? #include "context-menu-provider.h"

#include "qh-web-engine-view.h"

#include "styles.h"

#include <cmath>

#include <QTimer>
#include <QScreen>

#include <QUrlQuery>

#include <QRegularExpression>
#include <QRegularExpressionMatch>

#include <QWebEngineProfile>

#include "JsInterface.h"


void QH_Web_View_Dialog::reset_tab_selection()
{
 qtw_->setCurrentIndex(1);
 qtw_->setCurrentIndex(0);

// qtw_->setCurrentWidget(wev_scroll_area_);
}


WebUrlRequestInterceptor::WebUrlRequestInterceptor(QObject *p)
  :QWebEngineUrlRequestInterceptor(p)
{

}
void WebUrlRequestInterceptor::interceptRequest(QWebEngineUrlRequestInfo &info) {
    QString rsrct = "";
    switch(info.resourceType()){
        case 0:rsrct="ResourceTypeMainFrame = 0, // top level page";break;
        case 1:rsrct="ResourceTypeSubFrame, // frame or iframe";break;
        case 2:rsrct="ResourceTypeStylesheet, // a CSS stylesheet";break;
        case 3:rsrct="ResourceTypeScript, // an external script";break;
        case 4:rsrct="ResourceTypeImage, // an image (jpg/gif/png/etc)";break;
        case 5:rsrct="ResourceTypeFontResource, // a font";break;
        case 6:rsrct="ResourceTypeSubResource, // an other subresource.";break;
        case 7:rsrct="ResourceTypeObject, // an object (or embed) tag for a plugin,";break;
        case 8:rsrct="ResourceTypeMedia, // a media resource.";break;
        case 9:rsrct="ResourceTypeWorker, // the main resource of a dedicated worker.";break;
        case 10:rsrct="ResourceTypeSharedWorker, // the main resource of a shared worker.";break;
        case 11:rsrct="ResourceTypePrefetch, // an explicitly requested prefetch";break;
        case 12:rsrct="ResourceTypeFavicon, // a favicon";break;
        case 13:rsrct="ResourceTypeXhr, // a XMLHttpRequest";break;
        case 14:rsrct="ResourceTypePing, // a ping request for <a ping>";break;
        case 15:rsrct="ResourceTypeServiceWorker, // the main resource of a service worker.";break;
        case 16:rsrct="ResourceTypeUnknown";break;

        default : rsrct="Unknown type";break;
    }

  qDebug() << " " << Q_FUNC_INFO << ":\n" << "WebUrlRequestInterceptor::interceptRequest    " <<info.requestMethod()
         <<"\n  "<<info.requestUrl() << "   " << rsrct      << "\n";

}

void QH_Web_View_Dialog::add_url_pattern(QUrl url)
{
 WebUrlRequestInterceptor *wuri = new WebUrlRequestInterceptor();
 QWebEngineProfile::defaultProfile()->setRequestInterceptor(wuri);


 QString path = url.path();

// if(path.startsWith("/l"))
//   path = path.mid(2);

 static QRegularExpression rx("/([\\w-]+)");

 QRegularExpressionMatchIterator it = rx.globalMatch(path);

 QVector<QString> parts;
 while (it.hasNext())
 {
  QRegularExpressionMatch m = it.next();
  QString c = m.captured(1);

  parts.push_back(c);
 }

 int rc = url_patterns_table_->rowCount();
 url_patterns_table_->insertRow(rc);

 QDateTime qdt = QDateTime::currentDateTime();


 QUrlQuery query(url);

 QList<QPair<QString, QString>> items = query.queryItems(QUrl::FullyDecoded);


 for(QPair<QString, QString> pr : items)
 {
  qDebug() << "1: " << pr.first << " 2: " << pr.second;
 }


 u1 max =  parts.value(0) == "l"? 6 : 2;

 for(int i = 0; i < max; ++i)
 {
  QTableWidgetItem* twi = new QTableWidgetItem();
  url_patterns_table_->setItem(rc, i, twi);
  twi->setFlags(twi->flags() & (~ (Qt::ItemIsEditable | Qt::ItemIsSelectable)));
  switch (i)
  {
  case 0: twi->setText(qdt.toString()); break;
  case 1: twi->setText(path); break;

  case 2: twi->setText(parts.value(1)); break;
  case 3: twi->setText(parts.value(2)); break;
  case 4: twi->setText(query.queryItemValue("layer-groups", QUrl::FullyDecoded)); break;
  case 5: twi->setText(query.queryItemValue("selectedZoning", QUrl::FullyDecoded)); break;

//  case 2: twi->setText(query.queryItemValue("layer-groups")); break;
//  case 3: twi->setText(query.queryItemValue("selectedZoning")); break;
//  case 4: twi->setText(query.queryItemValue("zoning-districts")); break;
  }

 }


}







QH_Web_View_Dialog::QH_Web_View_Dialog(QWidget* parent)
  :  QDialog(parent), mark_location_callback_(nullptr),
     url_changed_callback_(nullptr),
     zoom_or_coordinates_changed_callback_(nullptr) //?, context_menu_provider_(nullptr), pm_runtime_(nullptr)
{
//? pm_runtime_ = new Pattern_Matcher_Runtime;

 main_layout_ = new QVBoxLayout;

 wev_scroll_area_ = new QScrollArea(this);

 wev_scroll_area_->setWidgetResizable(true);


 wev_ = new QH_Web_Engine_View(this);
 //wev->setGeometry(0,0,700,600);

//?
 wep_ = new QH_Web_Engine_Page(wev_);

 QObject::connect(wep_, &QH_Web_Engine_Page::urlChanged,[this](const QUrl& url)
 {
  if(url_changed_callback_)
    url_changed_callback_(url);

//  QString path = url.path();
//  QString fragment = url.fragment();

//  QString url_string = url.toString();

//  if(fragment.isEmpty())
//  {
//   QString query = url.query(QUrl::ComponentFormattingOption::FullyDecoded);

//   s4 index = url_string.indexOf('#');
//   if(index != -1)
//   {
//    QUrl u = url;
//    u.setQuery("");
//    fragment = url_string.mid(index);
//    url_string = u.toString() + "?...#" + fragment;
//   }
//  }

//  if(path.startsWith("/about") || path.startsWith("/l"))
//  {
////?   qDebug() << "new url = " << fragment;
//   process_new_url_geo_fragment(url_string, fragment);
//  }

 });

 QObject::connect(wep_, &QH_Web_Engine_Page::navRequest,[this](const QUrl &url, QPoint pos)
 {
  qDebug() << "pos:" << pos;

  qDebug() << "req:" << url.toString();
  //? check_url_patterns(url.toString().prepend("navRequest!"));
 });

 QObject::connect(wep_, &QH_Web_Engine_Page::qh_link_request,[this](const QUrl &url,
    const QPoint pos, const QSize window_size, QString cut_path, QWebEnginePage::NavigationType navtype)
 {
  if(qh_link_request_callback_)
    qh_link_request_callback_(url, pos, window_size, cut_path, navtype);
 });


 QObject::connect(wep_, &QH_Web_Engine_Page::linkHovered,[](const QUrl &url){
  qDebug() << "H:" << url.toString();
 });

//? //?
// myp_ = new MyPage;
// QWebChannel* channel = new QWebChannel(wev_);
// channel->registerObject(QStringLiteral("content"), myp_);
// wep_->setWebChannel(channel);

 //?
 wev_->setPage(wep_);

 connect(wev_, SIGNAL(snapshot_saved(QString)), this, SIGNAL(snapshot_saved(QString)));
 connect(wev_, SIGNAL(youtube_download_requested(QString)), this, SIGNAL(youtube_download_requested(QString)));

//? QString url = "http://localhost:%1/raw/temp.html"_qt.arg(EMBER_PORT);
//? QString url = "http://localhost:6409/ctrl-test";
 QString url = "http://localhost:6409/map-gl";

 initial_url_ = url;

 qDebug() << "url = " << url;

 wep_->load(QUrl(url));

// QString url = "http://localhost:%1/qh-link"_qt.arg(EMBER_PORT);


// QWebChannel* channel_ = new QWebChannel(wep_);
// //attach it to the QWebEnginePage
// wep_->setWebChannel(channel_);
// //register a QObject to be exposed to JavaScript
// channel_->registerObject(QStringLiteral("jshelper"), this);

// QFile apiFile(":/qtwebchannel/qwebchannel.js"); //load the API from the resources
// if(!apiFile.open(QIODevice::ReadOnly))
//     qDebug()<<"Couldn't load Qt's QWebChannel API!";
// QString apiScript = QString::fromLatin1(apiFile.readAll());
// apiFile.close();

// wep_->load(QUrl("https://www.google.com/maps/place/Philadelphia,+PA/@39.9558052,-75.1581506,13.75z/data=!4m5!3m4!1s0x89c6b7d8d4b54beb:0x89f514d88c3e58c1!8m2!3d39.9525839!4d-75.1652215"));

 qtw_ = new QTabWidget(this);

 wev_scroll_area_frame_ = new QFrame;

 wev_scroll_area_frame_->setMinimumSize(500, 500);
 QVBoxLayout* vb = new QVBoxLayout(wev_scroll_area_frame_);
 vb->addWidget(wev_);

 wev_scroll_area_->setWidget(wev_scroll_area_frame_);

 wev_->set_scroll_container(wev_scroll_area_);

 qtw_->addTab(wev_scroll_area_, "Tour");

//? QString iurl = ROOT_FOLDER "/../testdia/matterport/info.html";

// iwev_ = new QWebEngineView(this);
// iwev_->page()->load(url); //  QUrl("file:///" + iurl));
// qtw_->addTab(iwev_, "360 Provider Info");

 qtw_->tabBar()->setShape(QTabBar::TriangularNorth);
 //?
 qtw_->setStyleSheet(tab_style_sheet_());


 url_patterns_frame_ = new QFrame(this);
 url_patterns_table_ = new QTableWidget(this);
 url_patterns_layout_ = new QVBoxLayout;
 url_patterns_layout_->addWidget(url_patterns_table_);
 url_patterns_frame_->setLayout(url_patterns_layout_);

 qtw_->addTab(url_patterns_frame_, "URL Patterns");

 url_patterns_table_->setColumnCount(6);
 url_patterns_table_->setRowCount(0);

 // // urlChanged!.*www.google.com/maps/place/([\w+]+) <QString-> PN:`.1
 url_patterns_table_->setHorizontalHeaderLabels({"Date/Time", "URL", "Latitude", "Longitude", "Zoom", "Classification"});

// url_patterns_table_->setColumnWidth(0, 60);
// url_patterns_table_->setColumnWidth(2, 130);
//// url_patterns_table_->setSt
// url_patterns_table_->setColumnWidth(5, 150);
//// url_patterns_table_->setColumnWidth(4, 50);
//// url_patterns_table_->setColumnWidth(5, 60);


//? url_patterns_table_->horizontalHeader()->setSectionResizeMode(4, QHeaderView::Stretch);

// add_fixed_url_pattern("C", {},
//   ".*www.google.com/maps/place/([^/]+)(?:/@([\\d,.\\w-]+))?", "test_map_places",
//   "$.1$ ; $.2$ ; $winid$ ; $gx$ ; $gy$");
//                       // // "<QString-> `.1");

 QHBoxLayout* add_row_layout = new QHBoxLayout;
 QPushButton* add_row_button = new QPushButton("Add", this);
 add_row_layout->addStretch();
 add_row_layout->addWidget(add_row_button);
 add_row_layout->addStretch();

 url_patterns_layout_->addLayout(add_row_layout);

 connect(add_row_button, &QPushButton::clicked,
   [this]()
   {
//?    handle_add_url_patterns_row();
   });


 url_patterns_layout_->addStretch();

// url_patterns_table_->horizontalHeaderItem(3)->set



 main_layout_->addWidget(qtw_);

 button_box_ = new QDialogButtonBox(this);

 //?url_label_ = new QLabel(this);
  //?url_label_->setText(url);

// name_qle_ = new QLineEdit(this);

 button_ok_ = new QPushButton("OK");
 //? button_proceed_ = new QPushButton("Proceed");
 button_cancel_ = new QPushButton("Cancel");

 button_ok_->setDefault(false);
 button_ok_->setAutoDefault(false);

 //?button_proceed_->setDefault(false);
 //?button_proceed_->setAutoDefault(false);

 button_cancel_->setDefault(true);

 button_ok_->setStyleSheet(basic_button_style_sheet_());
 button_cancel_->setStyleSheet(basic_button_style_sheet_());


 //?button_ok_->setEnabled(false);

 button_box_->addButton(button_ok_, QDialogButtonBox::AcceptRole);
 //?button_box_->addButton(button_proceed_, QDialogButtonBox::ApplyRole);
 button_box_->addButton(button_cancel_, QDialogButtonBox::RejectRole);


 //?connect(button_proceed_, SIGNAL(clicked()), this, SLOT(proceed()));
 connect(button_box_, SIGNAL(accepted()), this, SLOT(accept()));
 connect(button_box_, SIGNAL(rejected()), this, SLOT(close()));

 main_layout_->addWidget(button_box_);

 setLayout(main_layout_);

 //->setCentralWidget(qtw);
 //mw->setGeometry(5,50,900,650);

 //wev->show();
 //this->show();

}

void QH_Web_View_Dialog::handle_mark_location_requested(const QH_Cross_Map_Coords& coords)
{
 if(mark_location_callback_)
   mark_location_callback_(coords);
}


//void QH_Web_View_Dialog::process_new_url_geo_fragment(QString url, QString fragment)
//{
//}

void QH_Web_View_Dialog::resizeEvent(QResizeEvent* resize_event)
{
 Q_EMIT web_view_geometry_updated(get_web_view_geometry());
}

void QH_Web_View_Dialog::moveEvent(QMoveEvent* move_event)
{
 if(this->isVisible())
   Q_EMIT web_view_geometry_updated(get_web_view_geometry());
}


QRect QH_Web_View_Dialog::get_web_view_geometry()
{
 return wev_scroll_area_->geometry().translated
   (wev_scroll_area_->mapToGlobal(QPoint(0, 0)));
}


void QH_Web_View_Dialog::mouseReleaseEvent(QMouseEvent* mev)
{
 qDebug() << " mr: " << mev->pos();

 mev->ignore();
}


void QH_Web_View_Dialog::mousePressEvent(QMouseEvent* mev)
{
 qDebug() << " mp: " << mev->pos();


 Qt::MouseButton mb = mev->button();

 if(mb == Qt::RightButton)
 {
  QWidget* qw = qtw_->currentWidget();
  if(QH_Web_Engine_View* zwev = qobject_cast<QH_Web_Engine_View*>(qw))
  {
   zwev->generate_context_menu(mev->globalPos(), mev->pos(), (n8) this, nullptr, mev);
   mev->accept();
   return;
  }
 }

 if(mb == Qt::LeftButton)
 {
  qDebug() << " lb: " << mev->pos();
 }

 mev->ignore();
}



QH_Web_View_Dialog::~QH_Web_View_Dialog()
{

}






//void QH_Web_View_Dialog::set_context_menu_provider(Context_Menu_Provider *context_menu_provider)
//{
// context_menu_provider_ = context_menu_provider;
// wev_->set_context_menu_provider(context_menu_provider_);
// wev_->set_pm_runtime(pm_runtime_);
// //context_menu_provider_->url_patterns() = url_patterns_;
//}


//void QH_Web_View_Dialog::add_fixed_url_pattern(QString context, QString sec, QString pattern,
//  QString procedure, QString arguments)
//{
//// pm_runtime_->add_url_pattern(context, sec, pattern,
////   procedure, arguments);

// int rc = url_patterns_table_->rowCount();
// url_patterns_table_->insertRow(rc);

// for(int i = 0; i < 5; ++i)
// {
//  QTableWidgetItem* twi = new QTableWidgetItem();
//  url_patterns_table_->setItem(rc, i, twi);
//  twi->setFlags(twi->flags() & (~ (Qt::ItemIsEditable | Qt::ItemIsSelectable)));
//  switch (i)
//  {
//  case 0: twi->setText(context); break;
//  case 1: twi->setText(sec); break;
//  case 2: twi->setText(pattern); break;
//  case 3: twi->setText(procedure); break;
//  case 4: twi->setText(arguments); break;
//  }
// }

//}


//void QH_Web_View_Dialog::handle_add_url_patterns_row()
//{
// //pm_runtime_->add_url_pattern();
// //url_patterns_.push_back(URL_Or_Event_Pattern({}));
// int rc = url_patterns_table_->rowCount();
// url_patterns_table_->insertRow(rc);

// patterns_by_row_.insert((u2) rc, nullptr);

// QPushButton* edit_row_button = new QPushButton("Edit", this);
// edit_row_button->setMaximumWidth(45);
// edit_row_button->setMaximumHeight(20);

// connect(edit_row_button, &QPushButton::clicked,
//  [this, rc](){ handle_edit_url_patterns_row(rc); });

// QPushButton* save_row_button = new QPushButton("Save", this);

// save_row_button->setMaximumWidth(45);
// save_row_button->setMaximumHeight(20);

// connect(save_row_button, &QPushButton::clicked,
//  [this, rc](){ handle_save_url_patterns_row(rc); });

// QPushButton* cancel_remove_row_button = new QPushButton("Remove", this);
// connect(cancel_remove_row_button, &QPushButton::clicked,
//  [this, rc](){ handle_cancel_remove_url_patterns_row(rc); });

// cancel_remove_row_button->setMaximumWidth(45);
// cancel_remove_row_button->setMaximumHeight(20);

// QWidget* cell_widget = new QWidget(this);
// QHBoxLayout* cell_widget_layout = new QHBoxLayout;//(cell_widget);
//// QHBoxLayout* cell_widget_vlayout = new QHBoxLayout;//(cell_widget);

// cell_widget_layout->addStretch();
// cell_widget_layout->addWidget(edit_row_button);
// cell_widget_layout->addWidget(save_row_button);
// cell_widget_layout->addWidget(cancel_remove_row_button);
// cell_widget_layout->addStretch();
// cell_widget_layout->setAlignment(Qt::AlignCenter); //set Alignment layout
// cell_widget_layout->setContentsMargins(0,0,0,0);
// cell_widget->setLayout(cell_widget_layout);
// url_patterns_table_->setCellWidget(rc, 5, cell_widget);



//// url_patterns_table_->item(rc, 5)->setTextAlignment(Qt::AlignHCenter | Qt::AlignCenter);
//// cancel_remove_row_button->setStyleSheet( "text-align: center; margin-left:50%; margin-right:50%;" );

//for(int i = 0; i < 5; ++i)
// {
//  QTableWidgetItem* twi = new QTableWidgetItem();
//  url_patterns_table_->setItem(rc, i, twi);
//  twi->setFlags(twi->flags() & (~ (Qt::ItemIsEditable | Qt::ItemIsSelectable)));
// }


//}


//void QH_Web_View_Dialog::handle_edit_url_patterns_row(int rc)
//{
// qDebug() << "rc = " << rc;

// for(int i = 0; i < 5; ++i)
// {
//  QTableWidgetItem* twi = url_patterns_table_->item(rc, i);
//  twi->setFlags(twi->flags() | (Qt::ItemIsEditable | Qt::ItemIsSelectable));
// }

//// QTableWidgetItem* twi = url_patterns_table_->item(rc, 5);
////? qobject_cast<QPushButton*>(url_patterns_table_->cellWidget(rc, 5))->setText("Cancel");
//}

//void QH_Web_View_Dialog::handle_cancel_remove_url_patterns_row(int rc)
//{
//// QString text = qobject_cast<QPushButton*>(url_patterns_table_->cellWidget(rc, 5))->text();
//// if(text == "Cancel")
//// {
////  for(int i = 0; i < 3; ++i)
////  {
////   QTableWidgetItem* twi = url_patterns_table_->item(rc, i);
////   twi->setFlags(twi->flags() & (~ (Qt::ItemIsEditable | Qt::ItemIsSelectable)));
////  }
//// }
//// else if(text == "Remove")
//// {
////  url_patterns_.remove(rc);
////  url_patterns_table_->removeRow(rc);
////  Q_EMIT url_patterns_changed();
//// }
//}


//void QH_Web_View_Dialog::handle_save_url_patterns_row(int rc)
//{
// for(int i = 0; i < 5; ++i)
// {
//  QTableWidgetItem* twi = url_patterns_table_->item(rc, i);
//  twi->setFlags(twi->flags() & (~ (Qt::ItemIsEditable | Qt::ItemIsSelectable)));
// }

// auto it = patterns_by_row_.find(rc);

// URL_Or_Event_Pattern* pattern = nullptr;

// if(it == patterns_by_row_.end())
// {
//  pattern = pm_runtime_->add_url_pattern();
//  patterns_by_row_[rc] = pattern;
// }
// else if(it.value() == nullptr)
// {
//  pattern = pm_runtime_->add_url_pattern();
//  it.value() = pattern;
// }
// else
//   pattern = it.value();

// pattern->set_pattern_context_string(url_patterns_table_->item(rc, 0)->text());
// pattern->set_secondary_context(url_patterns_table_->item(rc, 1)->text());
// pattern->set_pattern_expression(url_patterns_table_->item(rc, 2)->text());
// pattern->set_procedure_name(url_patterns_table_->item(rc, 3)->text());
// pattern->set_procedure_arguments(url_patterns_table_->item(rc, 4)->text());

////? qobject_cast<QPushButton*>(url_patterns_table_->cellWidget(rc, 5))->setText("Remove");

// Q_EMIT url_patterns_changed();
//}



