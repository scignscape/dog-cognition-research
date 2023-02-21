
//          Copyright Nathaniel Christen 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include "ses-filter-dialog.h"

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
#include <QSpinBox>

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
#include <QStandardItemModel>

#include "global-types.h"


SES_Filter_Dialog::SES_Filter_Dialog(QWidget* parent)
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
  "Energy-Conserving Architecture/Design", "Energy-Conserving Equipment/Installation",
  "Sustainable/Ecosensitive Materials/Sourcing", "Parks, Green Spaces, Public Areas"
  "Carbon-Neutral and/or Carbon Offsets", "Waterfront Zoning/Coastal Zone",
  "E-Designation", "FRESH (Food Retail Expansion)",
  "Environmental Rehabilitation", "Sustainable Infrastructure (transit, walkability)",
 };

 main_table_->setHorizontalHeaderLabels({"Description", "Overall\nCount", "Active"});

 main_table_->setColumnWidth(0, 270);
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

 QLabel* location_notes_label = new QLabel("Notes: Overall Count current as of March 1, 2023"
   "                \n"
   "\"Active\" means included in the current search/display filter");

 main_table_layout_->addWidget(main_table_);
 main_table_layout_->addWidget(location_notes_label);

 main_table_->setMinimumWidth(450);


 genres_table_layout_ = new QVBoxLayout;

 genres_table_group_box_ = new QGroupBox("Resource/Media Classification", this);
 genres_table_ = new QTableWidget(10, 4, this);

 genres_table_layout_ = new QVBoxLayout;
 genres_table_group_box_->setLayout(genres_table_layout_);

// genres_table_->setMinimumWidth(340);

 genres_table_->setStyleSheet(tables_ss);

 QStringList genres   {
  "Video", "Document/PDF",
  "Virtual Tour", "Street View", "3D Model",
  "2D Floor Plan", "Data Visualization",
  "Simulation", "Image Series", "Data Set", "Application/Module"
 };

 genres_table_->setHorizontalHeaderLabels({"Genre", "File Types", "Overall\nCount", "Active"});

 genres_table_->setColumnWidth(0, 140);
 genres_table_->setColumnWidth(1, 55);
 genres_table_->setColumnWidth(2, 50);
 genres_table_->setColumnWidth(3, 60);
 genres_table_->verticalHeader()->setVisible(false);

 r = 0;
 for(QString ph : genres)
 {
  QTableWidgetItem* qtwi1 = new QTableWidgetItem(ph);
  QTableWidgetItem* qtwi2 = new QTableWidgetItem("(all)");
  QTableWidgetItem* qtwi3 = new QTableWidgetItem("(TBD)");
  QTableWidgetItem* qtwi4 = new QTableWidgetItem("Yes");

  qtwi2->setTextAlignment(Qt::AlignCenter);
  qtwi3->setTextAlignment(Qt::AlignCenter);
  qtwi4->setTextAlignment(Qt::AlignCenter);

  //qtwi2->setStyleSheet("");

  genres_table_->setItem(r, 0, qtwi1);
  genres_table_->setItem(r, 1, qtwi2);
  genres_table_->setItem(r, 2, qtwi3);
  genres_table_->setItem(r, 3, qtwi4);

  qtwi2->setData(Qt::ForegroundRole, QVariant(QColor(110, 80, 80)));
  qtwi3->setData(Qt::ForegroundRole, QVariant(QColor(110, 80, 80)));
  qtwi4->setData(Qt::BackgroundRole, QVariant(QColor(210, 202, 255)));

  ++r;
 }

 QLabel* genres_notes_label = new QLabel("Notes: \"active\" selects all file/MIME "
   "types and extensions. Use\nthe extension-filter "
   "dialog to toggle matches based on file type.");

 genres_table_layout_->addWidget(genres_table_);
 genres_table_layout_->addWidget(genres_notes_label);


 group_boxes_layout_ = new QHBoxLayout;

 group_boxes_layout_->addWidget(main_table_group_box_);
 group_boxes_layout_->addWidget(genres_table_group_box_);

 group_boxes_layout_->addStretch();

 main_layout_->addLayout(group_boxes_layout_);



 geo_group_box_ = new QGroupBox("Geographic Area Options");
 geo_combo_box_ = new QComboBox(this);
 geo_layout_ = new QFormLayout;

 QStringList geo_filters { "None (no restrictions)", "County", "Borough",
    "Municipality", "Zoning District",
    "Council District", "State Senate", "Assembly"};

 for(QString gf : geo_filters)
 {
  geo_combo_box_->addItem(gf);
  geo_combo_box_->setItemData(Qt::Unchecked, Qt::CheckStateRole);
 }

 property_location_combo_box_ = new QComboBox(this);

 QStringList property_location_filters { "All", "Residential (multi-unit)",
    "Residential (single family or small multi-unit)", "Commercial (retail)",
    "Commercial (offices)", "Commercial (public-related services)",
    "Govermental (offices/services)", "Public Infrastructure",
    "Educational (public or non-profit)",
    "Non-Profit (religious)", "Non-Profit (other)",
    "Tourism and Hospitality", "Manufacturing/Industrial"};

 QStandardItemModel* property_location_filters_model = new QStandardItemModel(property_location_filters.size(), 1); // 3 rows, 1 col


 u1 index = 0;
 for(QString plf : property_location_filters)
 {
     QStandardItem* item = new QStandardItem(plf);

     item->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
     item->setData(Qt::Unchecked, Qt::CheckStateRole);

     property_location_filters_model->setItem(index, 0, item);
     ++index;
 }

 property_location_combo_box_->setModel(property_location_filters_model);



 size_and_web_links_layout_ = new QHBoxLayout;

 include_web_links_check_box_ = new QCheckBox("Include Web Links", this);
 size_and_web_links_layout_->addWidget(include_web_links_check_box_);

 maximum_file_size_layout_ = new QHBoxLayout;

 maximum_file_size_check_box_ = new QCheckBox("Maxiumum File Size", this);

 maximum_file_size_layout_->addStretch();

 maximum_file_size_spin_box_ = new QSpinBox;
 maximum_file_size_spin_box_->setMinimum(0);
 maximum_file_size_spin_box_->setMaximum(1000);

 maximum_file_size_layout_->addWidget(maximum_file_size_check_box_);
 maximum_file_size_layout_->addWidget(maximum_file_size_spin_box_);

 size_and_web_links_layout_->addLayout(maximum_file_size_layout_);



// include_web_links_reset_ = new QPushButton("reset", this);
// include_web_links_reset_->setMaximumHeight(20);
// include_web_links_reset_->setMaximumWidth(40);

// size_and_web_links_layout_->addWidget(include_web_links_reset_);

//? size_and_web_links_layout_->addStretch();



 geo_layout_->addRow("Property/Location Filter:", property_location_combo_box_);
 geo_layout_->addRow("Geographic Area:", geo_combo_box_);

 geo_layout_->addRow(size_and_web_links_layout_);


 bottom_layout_ = new QHBoxLayout;
 bottom_layout_->addLayout(geo_layout_);

 deco_frame_ = new QFrame(this); //("Map Item Indicators");
 deco_layout_ = new QVBoxLayout;
 deco_frame_->setLayout(deco_layout_);

 indicate_without_ = new QCheckBox("Show indicator even if no "
   "matches are available\n(the location will be marked with a dotted outline)");

 deco_layout_->addWidget(indicate_without_);

 QCheckBox* show_sample_stage_ = new QCheckBox("Use outlines to indicate resource classification "
   "\n(visit the configuration dialog to review/edit the display formats)");

 deco_layout_->addWidget(show_sample_stage_);

 deco_frame_->setFrameShape(QFrame::Panel);
 deco_frame_->setFrameShadow(QFrame::Raised);

 bottom_layout_->addWidget(deco_frame_);

 main_layout_->addLayout(bottom_layout_);

 main_layout_->addWidget(button_box_);

 setLayout(main_layout_);

 setWindowTitle("Resource Filter/Query Dialog");

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


SES_Filter_Dialog::~SES_Filter_Dialog()
{

}

void SES_Filter_Dialog::cancel()
{
 Q_EMIT(rejected());
 Q_EMIT(canceled(this));
 Q_EMIT(rejected());
 close();
}

void SES_Filter_Dialog::accept()
{
 Q_EMIT(accepted(this));
}
