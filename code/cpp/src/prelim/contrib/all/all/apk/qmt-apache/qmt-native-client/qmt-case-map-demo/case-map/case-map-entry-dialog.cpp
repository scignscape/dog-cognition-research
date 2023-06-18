
//          Copyright Nathaniel Christen 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include "case-map-entry-dialog.h"

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


Case_Map_Entry_Dialog::Case_Map_Entry_Dialog(QWidget* parent)
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
 entry_layout_ = new QVBoxLayout;

 info_group_box_ = new QGroupBox("Personal Info", this);
 location_group_box_ = new QGroupBox("Location", this);
 children_group_box_ = new QGroupBox("About your Children", this);

 info_group_box_layout_ = new QHBoxLayout(info_group_box_);

 location_group_box_layout_ = new QHBoxLayout(location_group_box_);
 location_group_box_left_layout_ = new QFormLayout;
 children_group_box_layout_ = new QVBoxLayout(children_group_box_);

 le_county_ = new QLineEdit(this);
 le_city_ = new QLineEdit(this);
 le_state_ = new QLineEdit(this);

 location_group_box_left_layout_->addRow("City", le_city_);
 location_group_box_left_layout_->addRow("State", le_state_);
 location_group_box_left_layout_->addRow("County", le_county_);

 location_group_box_layout_->addLayout(location_group_box_left_layout_);

 location_group_box_right_layout_ = new QVBoxLayout;
 location_group_box_right_layout_->addWidget(new QLabel("Your address (optional):", this));
 QTextEdit* address_text_edit = new QTextEdit(this);
 address_text_edit->setPlaceholderText("Enter address here, or leave empty");
 location_group_box_right_layout_->addWidget(address_text_edit);
 address_text_edit->setMaximumHeight(65);

 location_group_box_layout_->addLayout(location_group_box_right_layout_);

 entry_layout_->addWidget(info_group_box_);

 le_first_name_ = new QLineEdit(this);
 le_last_name_ = new QLineEdit(this);
 le_phone_number_ = new QLineEdit(this);
 le_email_ = new QLineEdit(this);

 info_group_box_left_layout_ = new QFormLayout;
 info_group_box_right_layout_ = new QFormLayout;

 info_group_box_left_layout_->addRow("First Name", le_first_name_);
 info_group_box_right_layout_->addRow("Last Name", le_last_name_);
 info_group_box_left_layout_->addRow("Phone Number\n(optional)", le_phone_number_);
 info_group_box_right_layout_->addRow("Email\n(optional)", le_email_);

 info_group_box_layout_->addLayout(info_group_box_left_layout_);
 info_group_box_layout_->addLayout(info_group_box_right_layout_);
 

 entry_layout_->addWidget(location_group_box_);
 entry_layout_->addWidget(children_group_box_);

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


 main_layout_->addLayout(entry_layout_);

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


Case_Map_Entry_Dialog::~Case_Map_Entry_Dialog()
{

}

void Case_Map_Entry_Dialog::cancel()
{
 Q_EMIT(rejected());
 Q_EMIT(canceled(this));
 Q_EMIT(rejected());
 close();
}

void Case_Map_Entry_Dialog::accept()
{
 Q_EMIT(accepted(this));
}
