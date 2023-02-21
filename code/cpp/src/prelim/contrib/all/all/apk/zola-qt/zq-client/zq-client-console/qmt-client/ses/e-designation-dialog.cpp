
//          Copyright Nathaniel Christen 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include "e-designation-dialog.h"

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
#include <QCalendarWidget>


E_Designation_Dialog::E_Designation_Dialog(QWidget* parent, QString number)
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

 ed_classification_combo_box_ = new QComboBox(this);
 zoning_classification_combo_box_ = new QComboBox(this);
 borough_combo_box_ = new QComboBox(this);

 ed_classification_combo_box_->addItems({"Hazardous materials", "Noise",
   "AIR" });

 zoning_classification_combo_box_->addItems({"R1", "R2",
   "R3", "R4",  "R5", "R6", "R7", "R8",  "R9", "R10",
   "C1", "C2", "C3", "C4", "C5", "C6", "C7", "C8",
   "M1", "M2", "M3",
   });

 borough_combo_box_->addItems({"Manhattan", "Brooklyn",
   "Queens", "Bronx", "Staten Island"});

 ed_number_line_edit_ = new QLineEdit(number, this);
 form_layout_->addRow("E-Designation Number:", ed_number_line_edit_);



 form_layout_->addRow("E-Designation Classification:", ed_classification_combo_box_);
 form_layout_->addRow("Zoning Classification:", zoning_classification_combo_box_);
 form_layout_->addRow("Borough:", borough_combo_box_);

 block_number_line_edit_ = new QLineEdit(this);
 block_number_line_edit_->setPlaceholderText("TBD");

 lot_number_line_edit_ = new QLineEdit(this);
 lot_number_line_edit_->setPlaceholderText("TBD");

 form_layout_->addRow("Lot Number:", lot_number_line_edit_);
 form_layout_->addRow("Block Number:", block_number_line_edit_);


// form_layout_->addRow("Address", new QLabel("Near 45 East Walnut Street\n(Parkview Drive)"));

 QHBoxLayout* ceqr = new QHBoxLayout;
 ceqr->addWidget(new QLabel("CEQR #"));

 QLineEdit* ceqr_line_edit_ = new QLineEdit(this);
 ceqr_line_edit_->setPlaceholderText("TBD");

 ceqr_line_edit_->setMaximumWidth(40);
 ceqr_line_edit_->setToolTip("City Environmental Quality Review");

// add_btn->setMaximumWidth(37);
// add_btn->setMaximumHeight(20);
 ceqr->addWidget(ceqr_line_edit_);

 QPushButton* ceqr_pdf_btn = new QPushButton("PDF");
 ceqr_pdf_btn->setMaximumWidth(37);

 ceqr_pdf_btn->setMaximumHeight(20);
 ceqr->addWidget(ceqr_pdf_btn);

 ceqr->addStretch();


 ceqr->addWidget(new QLabel("ULURP"));


 QLineEdit*  ULURP_line_edit_ = new QLineEdit(this);
 ULURP_line_edit_->setPlaceholderText("TBD");
 ULURP_line_edit_->setMaximumWidth(40);
 ULURP_line_edit_->setToolTip("Uniform Land Use Review Procedure");
// add_btn->setMaximumWidth(37);
// add_btn->setMaximumHeight(20);
 ceqr->addWidget(ULURP_line_edit_);

 QPushButton*  ULURP_pdf_btn = new QPushButton("PDF");
 ULURP_pdf_btn->setMaximumWidth(37);

 ULURP_pdf_btn->setMaximumHeight(20);
 ceqr->addWidget(ULURP_pdf_btn);

 ceqr->addStretch();




// QPushButton* folder_btn = new QPushButton("folder:");
// folder_btn->setMaximumWidth(47);
// folder_btn->setMaximumHeight(20);

// QLabel* folder_label = new QLabel("/home/demo");

// pics->addWidget(folder_btn);
// pics->addWidget(folder_label);
// pics->addStretch();


 form_layout_->addRow("CEQR Info/Links:", ceqr);

 form_layout_->itemAt(form_layout_->rowCount() - 1, QFormLayout::LabelRole)->widget()->setToolTip(
   "City Environmental Quality Review");






 start_date_calendar_ = new QCalendarWidget;
// follow_up_combo_box_->addItems({"Send Inspector", "Phone Call",
//   "Inspector Visited (7/20)", "Called (7/19)", "Other", "Unspecified/Unknown"});

 form_layout_->addRow("Effective Date:",  start_date_calendar_);

 main_layout_->addLayout(form_layout_);

 main_layout_->addWidget(button_box_);

 setLayout(main_layout_);

 setWindowTitle("E-Designation Dialog");

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


E_Designation_Dialog::~E_Designation_Dialog()
{

}

void E_Designation_Dialog::cancel()
{
 Q_EMIT(rejected());
 Q_EMIT(canceled(this));
 Q_EMIT(rejected());
 close();
}

void E_Designation_Dialog::accept()
{
 Q_EMIT(accepted(this));
}
