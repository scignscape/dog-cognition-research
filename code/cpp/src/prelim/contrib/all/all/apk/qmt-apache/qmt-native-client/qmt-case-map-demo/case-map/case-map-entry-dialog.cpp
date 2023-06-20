
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

#include <QGeoCoordinate>

#include "global-types.h"

#include "case-map-gis-service.h"

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
 cb_state_or_province_ = new QComboBox(this);

 //828 279 6735  arlene
 // //  locations checked via https://simplemaps.com/data/us-cities

 cb_state_or_province_->addItems({
"(choose one ...)",
"N/A (international)",
"AB (Alberta)", "AL (Alabama)", "AK (Alaska)", "AR (Arkansas)", "AZ (Arizona)",
"BC (British Columbia)", "CA (California)", "CO (Colorado)",
"CT (Connecticut)", "DC (District of Columbia)", "DE (Delaware)",
"FL (Florida)", "GA (Georgia)", "HI (Hawaii)",
"IA (Iowa)", "ID (Idaho)", "IN (Indiana)", "IL (Illinois)",
"KS (Kansas)", "KY (Kentucky)",
"LA (Louisiana)", "LB (Labrador)", "MA (Massachusetts)", "MB (Manitoba)",
"MD (Maryland)", "ME (Maine)",
"MI (Michigan)", "MN (Minnesota)", "MO (Missouri)",
"MS (Mississippi)", "MT (Montana)", "NB (New Brunswick)",
"NC (North Carolina)", "ND (North Dakota)",
"NE (Nebraska)", "NF (Newfoundland)", "NH (New Hampshire)",
"NJ (New Jersey)", "NM (New Mexico)", "NS (Nova Scotia)", "NU (Nunavut)",
"NV (Nevada)", "NW (North West Territories)", "NY (New York)",
"OH (Ohio)", "OK (Oklahoma)", "ON (Ontario)", "OR (Oregon)", "PA (Pennsylvania)",
"PE (Prince Edward Island)", "PR (Puerto Rico)", "QC (Quebec)",
"RI (Rhode Island)", "SC (South Carolina)", "SD (South Dakota)",
"SK (Saskatchewen)", "TN (Tennessee)", "TX (Texas)",
"US (other US territory)", "UT (Utah)",
"VA (Virginia)", "VT (Vermont)", "WA (Washington)",
"WI (Wisconsin)", "WV (West Virginia)", "WY (Wyoming)",
"YU (Yukon)"
});

 cb_state_or_province_->setMaxVisibleItems(12);
 cb_state_or_province_->setStyleSheet("combobox-popup: 0;");

 location_group_box_left_layout_->addRow("County", le_county_);
 location_group_box_left_layout_->addRow("City", le_city_);
 location_group_box_left_layout_->addRow("State/Territory\nor Province", cb_state_or_province_);

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



 children_group_box_layout_top_ = new QFormLayout; //(children_group_box_)

 cb_number_of_children_ = new QComboBox(this);
 cb_number_of_children_->addItems({QString::number(1),
   QString::number(2), QString::number(3), QString::number(4),
   QString::number(5), QString::number(6), QString::number(7),
   QString::number(8) });

 children_group_box_layout_top_->addRow("Number of Children: ",  cb_number_of_children_);

 children_group_box_layout_->addLayout(children_group_box_layout_top_);

 children_grid_layout_ = new QGridLayout;

 children_grid_layout_->addWidget(new QLabel("Child's Name:", this), 0, 0);
 children_grid_layout_->addWidget(new QLabel("Birth Year:", this), 0, 1);

 connect(cb_number_of_children_,  QOverload<int>::of(&QComboBox::currentIndexChanged),
   [this](int which)
 {
  if(which < 0)
    return;
  u1 count = which + 1;
  u1 rc = children_grid_layout_->rowCount() - 1;
  if(count == rc)
    return;
  if(count < rc)
  {
   // // erase lines?
   QMessageBox::StandardButton sb = QMessageBox::question(this, "Reduce number of lines?",
     "Do you want to delete the extra %1 lines?"_qt.arg(rc - count));

   if(sb == QMessageBox::Yes)
   {
    QVector<QWidget*> to_be_removed;
    for(u1 c = count; c < rc; ++c)
    {
     to_be_removed << children_grid_layout_->itemAtPosition(c + 1, 0)->widget();
     to_be_removed << children_grid_layout_->itemAtPosition(c + 1, 1)->widget();
    }

    for(QWidget* w : to_be_removed)
    {
     children_grid_layout_->removeWidget(w);
     w->hide();
     w->deleteLater();
    }
//    children_grid_layout_->removeItem(children_grid_layout_->itemAtPosition(rrc - 1, 0));


    //qDebug() << "erase!";
   }
  }
  else
  {
  while(rc++ < count)
    add_children_line();
  }

 });


 children_group_box_layout_->addLayout(children_grid_layout_);

 entry_layout_->addWidget(children_group_box_);

 main_layout_->addLayout(entry_layout_);

 button_do_map_ = new QPushButton("Map", this);

 connect(button_do_map_, &QPushButton::clicked, [this]()
 {
  QString city = le_city_->text();
  QString state = cb_state_or_province_->currentText();
  //if(state == "N/A")

  QRegularExpression rx("^(\\w\\w)\\s+\\(");
  QRegularExpressionMatch rxm = rx.match(state);
  if(!rxm.hasMatch())
    return;
  state = rxm.captured(1);

  qDebug() << "state = " << state;

  Case_Map_GIS_Service cmgs("osm");

  QPair<r8, r8> latlon = cmgs.get_city_latitude_and_longitude(city, state);

  qDebug() << "latlon = " << latlon;

  QGeoLocation loc;
  loc.setCoordinate(QGeoCoordinate(latlon.first, latlon.second));
  Q_EMIT(location_marker_requested(loc));

 });

 bottom_layout_ = new QHBoxLayout;

 bottom_layout_->addWidget(button_do_map_);
 bottom_layout_->addStretch();
 bottom_layout_->addWidget(button_box_);

 main_layout_->addLayout(bottom_layout_);


 setLayout(main_layout_);

 setWindowTitle("Entry Dialog");

}


void Case_Map_Entry_Dialog::add_children_line()
{
 u1 rc = children_grid_layout_->rowCount();

 QLineEdit* cn = new QLineEdit(this);
 QComboBox* cy = new QComboBox(this);

 for(u2 y = 2010; y <= 2023; ++y)
 {
  cy->addItem(QString::number(y));
 }

 children_grid_layout_->addWidget(cn, rc, 0);
 children_grid_layout_->addWidget(cy, rc, 1);

}




//QHBoxLayout* pics = new QHBoxLayout;
//pics->addWidget(new QLabel("2"));

//QPushButton* pics_btn = new QPushButton("show");
//pics_btn->setMaximumWidth(37);

//pics_btn->setMaximumHeight(20);
//pics->addWidget(pics_btn);

//QPushButton* add_btn = new QPushButton("add");
//add_btn->setMaximumWidth(37);
//add_btn->setMaximumHeight(20);
//pics->addWidget(add_btn);

//pics->addStretch();

//QPushButton* folder_btn = new QPushButton("folder:");
//folder_btn->setMaximumWidth(47);
//folder_btn->setMaximumHeight(20);

//QLabel* folder_label = new QLabel("/home/demo");

//pics->addWidget(folder_btn);
//pics->addWidget(folder_label);
//pics->addStretch();



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
