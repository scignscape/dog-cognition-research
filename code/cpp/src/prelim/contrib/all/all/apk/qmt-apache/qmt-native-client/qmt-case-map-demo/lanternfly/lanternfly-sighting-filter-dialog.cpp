
//          Copyright Nathaniel Christen 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include "lanternfly-sighting-filter-dialog.h"

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
#include <QCheckBox>

#include <QGraphicsView>
#include <QScrollArea>

//#include <QTcpServer>
//#include <QNetworkAccessManager>

#include <QHeaderView>

#include <QMenu>
#include <QAction>

#include <QListWidget>

#include <QComboBox>


Lanternfly_Sighting_Filter_Dialog::Lanternfly_Sighting_Filter_Dialog(QWidget* parent)
  : QDialog(parent)
{
 // // setup RZW

 button_box_ = new QDialogButtonBox(this);

 button_ok_ = new QPushButton("OK");
 button_proceed_ = new QPushButton("Edit");
 button_cancel_ = new QPushButton("Cancel");

 button_ok_->setDefault(false);
 button_ok_->setAutoDefault(false);

 button_proceed_->setDefault(false);
 button_proceed_->setAutoDefault(false);

 button_cancel_->setDefault(true);

 button_ok_->setEnabled(false);

 // // unless this is being embedded ...
 button_proceed_->setEnabled(false);
 button_cancel_->setText("Close");

 button_box_->addButton(button_ok_, QDialogButtonBox::AcceptRole);
 button_box_->addButton(button_proceed_, QDialogButtonBox::ApplyRole);
 button_box_->addButton(button_cancel_, QDialogButtonBox::RejectRole);

// button_ok_->setStyleSheet(basic_button_style_sheet_());
// button_proceed_->setStyleSheet(basic_button_style_sheet_());
// button_cancel_->setStyleSheet(basic_button_style_sheet_());

 connect(button_proceed_, SIGNAL(clicked()), this, SLOT(proceed()));
 connect(button_box_, SIGNAL(accepted()), this, SLOT(accept()));
 connect(button_box_, SIGNAL(rejected()), this, SLOT(cancel()));

 main_layout_ = new QVBoxLayout;

 main_table_group_box_ = new QGroupBox("Location Classification", this);
 main_table_ = new QTableWidget(10, 3, this);

 main_table_layout_ = new QVBoxLayout;
 main_table_group_box_->setLayout(main_table_layout_);

 QStringList location_classification   {
  "Private House", "Apartment Building", "Parks/Recreation Area",
  "Transit Stop/Center",
  "Port/Airport/Railroad Track", "Commercial/Retail", "Factory/Warehouse",
  "School/Religious Institution", "Farm/Agricultural Site", "Other"
 };

 main_table_->setHorizontalHeaderLabels({"Description", "Overall\nCount", "Active"});

 main_table_->setColumnWidth(0, 170);
 main_table_->setColumnWidth(1, 50);
 main_table_->setColumnWidth(2, 40);

 main_table_->verticalHeader()->setVisible(false);

 QString tables_ss = R"(
 QTableView
 {
     border: 13px solid white;
     gridline-color: white;
 }
 )"; //     color: {white};      background: {color};

 main_table_->setStyleSheet(tables_ss);

 int r = 0;
 for(QString lc : location_classification)
 {
  QTableWidgetItem* qtwi1 = new QTableWidgetItem(lc);
  QTableWidgetItem* qtwi2 = new QTableWidgetItem("(TBD)");
  QTableWidgetItem* qtwi3 = new QTableWidgetItem("No");


  qtwi2->setTextAlignment(Qt::AlignCenter);
  qtwi3->setTextAlignment(Qt::AlignCenter);

  main_table_->setItem(r, 0, qtwi1);
  main_table_->setItem(r, 1, qtwi2);
  main_table_->setItem(r, 2, qtwi3);

  qtwi2->setData(Qt::ForegroundRole, QVariant(QColor(110, 80, 80)));
  qtwi3->setData(Qt::BackgroundRole, QVariant(QColor(190, 190, 180)));

  if(r == 2 || r == 3)
  {
   qtwi3->setText("Yes");
   qtwi3->setData(Qt::BackgroundRole, QVariant(QColor(210, 202, 255)));
  }

  ++r;
 }

 QLabel* location_notes_label = new QLabel("Notes: Overall Count current as of 7/12\n"
   "\"Active\" means included in the current search/display filter");

 main_table_layout_->addWidget(main_table_);
 main_table_layout_->addWidget(location_notes_label);



 plants_table_layout_ = new QVBoxLayout;

 plants_table_group_box_ = new QGroupBox("Plant Host", this);
 plants_table_ = new QTableWidget(10, 4, this);

 plants_table_layout_ = new QVBoxLayout;
 plants_table_group_box_->setLayout(plants_table_layout_);

 plants_table_->setMinimumWidth(410);

 plants_table_->setStyleSheet(tables_ss);

 QStringList plant_hosts   {
  "Tree of Heaven", "Apple/Crabapple",
  "Maple", "Birch", "Walnut",
  "Other Trees", "Unknown Tree",
  "Grapes", "Stone Fruit", "Ornamental Tree/Plant", "Other"
 };

 plants_table_->setHorizontalHeaderLabels({"Host", "Reference Photo", "Overall\nCount", "Active"});

 plants_table_->setColumnWidth(0, 140);
 plants_table_->setColumnWidth(2, 50);
 plants_table_->setColumnWidth(3, 60);
 plants_table_->verticalHeader()->setVisible(false);

 r = 0;
 for(QString ph : plant_hosts)
 {
  QTableWidgetItem* qtwi1 = new QTableWidgetItem(ph);
  QTableWidgetItem* qtwi2 = new QTableWidgetItem("(unassigned)");
  QTableWidgetItem* qtwi3 = new QTableWidgetItem("(TBD)");
  QTableWidgetItem* qtwi4 = new QTableWidgetItem("Yes");

  qtwi2->setTextAlignment(Qt::AlignCenter);
  qtwi3->setTextAlignment(Qt::AlignCenter);
  qtwi4->setTextAlignment(Qt::AlignCenter);

  //qtwi2->setStyleSheet("");

  plants_table_->setItem(r, 0, qtwi1);
  plants_table_->setItem(r, 1, qtwi2);
  plants_table_->setItem(r, 2, qtwi3);
  plants_table_->setItem(r, 3, qtwi4);

  qtwi2->setData(Qt::ForegroundRole, QVariant(QColor(110, 80, 80)));
  qtwi3->setData(Qt::ForegroundRole, QVariant(QColor(110, 80, 80)));
  qtwi4->setData(Qt::BackgroundRole, QVariant(QColor(210, 202, 255)));

  ++r;
 }

 QLabel* plants_notes_label = new QLabel("Notes: Apple/Crabapple refers "
   "to any \"Malus\" tree.\n\"Unknown Tree\" applies to hosts recognized to be a\n"
   "tree variety but whose species was unknown or unreported.");

 plants_table_layout_->addWidget(plants_table_);
 plants_table_layout_->addWidget(plants_notes_label);


 group_boxes_layout_ = new QHBoxLayout;

 group_boxes_layout_->addWidget(main_table_group_box_);
 group_boxes_layout_->addWidget(plants_table_group_box_);

 group_boxes_layout_->addStretch();

 main_layout_->addLayout(group_boxes_layout_);



 geo_group_box_ = new QGroupBox("Geographic Area Options");
 geo_combo_box_ = new QComboBox(this);
 geo_layout_ = new QFormLayout;

 QStringList geo_filters { "None", "County", "Quarantined County",
    "Municipality", "Viewed Locations", "Sighting Density", "Current Viweport", "Selected Area"};

 for(QString gf : geo_filters)
 {
  geo_combo_box_->addItem(gf);
 }

 density_combo_box_ = new QComboBox(this);
 density_combo_box_->addItem("At least 3 per square mile");


 density_merge_layout_ = new QHBoxLayout;

 density_merge_check_box_ = new QCheckBox("Merge with other criteria", this);
 density_merge_layout_->addWidget(density_merge_check_box_);

 density_merge_reset_ = new QPushButton("reset", this);
 density_merge_reset_->setMaximumHeight(20);
 density_merge_reset_->setMaximumWidth(40);

 density_merge_layout_->addWidget(density_merge_reset_);
 density_merge_layout_->addStretch();

 geo_layout_->addRow("Density/Threshold:", density_combo_box_);
 geo_layout_->addRow("", density_merge_layout_);
 geo_layout_->addRow("Geographic Area:", geo_combo_box_);



 bottom_layout_ = new QHBoxLayout;
 bottom_layout_->addLayout(geo_layout_);

 deco_frame_ = new QFrame(this); //("Map Item Indicators");
 deco_layout_ = new QVBoxLayout;
 deco_frame_->setLayout(deco_layout_);

 indicate_without_sighting_ = new QCheckBox("Show indicator even if no "
   "sightings have been reported\n(the location will be marked with a dotted outline)");

 deco_layout_->addWidget(indicate_without_sighting_);

 QCheckBox* show_sample_stage_ = new QCheckBox("Use outlines to indicated observed insect stage "
   "\n(for sightings where the samples' ages/stages are reported)");

 deco_layout_->addWidget(show_sample_stage_);

 deco_frame_->setFrameShape(QFrame::Panel);
 deco_frame_->setFrameShadow(QFrame::Raised);

 bottom_layout_->addWidget(deco_frame_);

 main_layout_->addLayout(bottom_layout_);

 main_layout_->addWidget(button_box_);

 setLayout(main_layout_);

 setWindowTitle("Sighting Filter/Query Dialog");

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


Lanternfly_Sighting_Filter_Dialog::~Lanternfly_Sighting_Filter_Dialog()
{

}

void Lanternfly_Sighting_Filter_Dialog::cancel()
{
 Q_EMIT(rejected());
 Q_EMIT(canceled(this));
 Q_EMIT(rejected());
 close();
}

void Lanternfly_Sighting_Filter_Dialog::accept()
{
 Q_EMIT(accepted(this));
}
