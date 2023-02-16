
//          Copyright Nathaniel Christen 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include "lanternfly-sighting-dialog.h"

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


Lanternfly_Sighting_Dialog::Lanternfly_Sighting_Dialog(QWidget* parent)
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
 form_layout_ = new QFormLayout;

 plant_combo_box_ = new QComboBox(this);
 location_kind_combo_box_ = new QComboBox(this);
 specimen_stage_combo_box_ = new QComboBox(this);

 plant_combo_box_->addItems({"Tree of Heaven", "Grape Vine",
   "Apple/Crab Apple", "Stone Fruit", "Other"});

 location_kind_combo_box_->addItems({"Private House", "Apartment Building",
   "Port/Airport/Railroad Track" "Commercial/Retail", "Factory/Warehouse", "Parks/Recreation Area",
   "School/Religious Institution", "Farm/Agricultural", "Other"});

 specimen_stage_combo_box_->addItems({"Egg Mass", "Early Nympth",
   "Late Nympth", "Adult", "Unknown/Unidentified"});

 form_layout_->addRow("Plant Host Description:", plant_combo_box_);
 form_layout_->addRow("Location/Property Classification:", location_kind_combo_box_);
 form_layout_->addRow("Specimen Stage:", specimen_stage_combo_box_);

 form_layout_->addRow("Location:", new QLabel("Teaneck: 40.86695N/74.01307W"));

 form_layout_->addRow("Address:", new QLabel("Near 45 East Walnut Street\n(Parkview Drive)"));


// form_layout_->addRow("Address", new QLabel("Near 45 East Walnut Street\n(Parkview Drive)"));

 QHBoxLayout* pics = new QHBoxLayout;
 pics->addWidget(new QLabel("2"));

 QPushButton* pics_btn = new QPushButton("show");
 pics_btn->setMaximumWidth(37);

 pics_btn->setMaximumHeight(20);
 pics->addWidget(pics_btn);

 QPushButton* add_btn = new QPushButton("add");
 add_btn->setMaximumWidth(37);
 add_btn->setMaximumHeight(20);
 pics->addWidget(add_btn);

 pics->addStretch();

 QPushButton* folder_btn = new QPushButton("folder:");
 folder_btn->setMaximumWidth(47);
 folder_btn->setMaximumHeight(20);

 QLabel* folder_label = new QLabel("/home/demo");

 pics->addWidget(folder_btn);
 pics->addWidget(folder_label);
 pics->addStretch();


 form_layout_->addRow("Number of Pictures:", pics);

 follow_up_combo_box_ = new  QComboBox(this);
 follow_up_combo_box_->addItems({"Send Inspector", "Phone Call",
   "Inspector Visited (7/20)", "Called (7/19)", "Other", "Unspecified/Unknown"});

 form_layout_->addRow("Follow Up:", follow_up_combo_box_);

 main_layout_->addLayout(form_layout_);

 main_layout_->addWidget(button_box_);

 setLayout(main_layout_);

 setWindowTitle("Sighting Dialog");

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


Lanternfly_Sighting_Dialog::~Lanternfly_Sighting_Dialog()
{

}

void Lanternfly_Sighting_Dialog::cancel()
{
 Q_EMIT(rejected());
 Q_EMIT(canceled(this));
 Q_EMIT(rejected());
 close();
}

void Lanternfly_Sighting_Dialog::accept()
{
 Q_EMIT(accepted(this));
}
