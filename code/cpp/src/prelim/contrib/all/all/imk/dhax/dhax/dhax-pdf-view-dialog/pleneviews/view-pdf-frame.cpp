
#include "view-pdf-frame.h"

//#include "clg-db-antemodel.h";

#include <QApplication>

#include <QHBoxLayout>
#include <QVBoxLayout>

#include <QScrollArea>
#include <QFileDialog>
#include <QTabWidget>
#include <QSplitter>
#include <QDialogButtonBox>
#include <QFormLayout>
#include <QCheckBox>
#include <QLineEdit>
#include <QGroupBox>
#include <QDockWidget>
#include <QFileInfo>

#include <QDesktopWidget>

#include <QPlainTextEdit>
#include <QTextStream>
#include <QProgressBar>

#include <QFileDialog>

#include <QProcess>

#include <QTableWidget>

#include <QMessageBox>

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrlQuery>

#include <QHeaderView>

#include <QListWidget>

#include "subwindows/pdf-document-widget.h"


#include "styles.h"
//#include "silotypes/ndp-project/ndp-project.h"
//#include "silotypes/ndp-project/ndp-project-initial.h"

USING_QSNS(ScignSeer)

View_PDF_Frame::View_PDF_Frame(QWidget* parent, QString pdf_file_path) //, NDP_Antemodel* antemodel)//, QString url, QWN_XMLDB_Configuration* config)
 : QFrame(parent), pdf_file_path_(pdf_file_path)//, antemodel_(antemodel)//, config_(config)
{

 main_layout_ = new QVBoxLayout();

 //controls_dock_widget_ = nullptr;
 //controls_frame_ = new QFrame(this);

 controls_layout_ = new QVBoxLayout;

// controls_dock_widget_ = new QDockWidget(this);
// controls_dock_widget_->setObjectName(QString::fromUtf8("controlsDockWidget"));
// controls_dock_widget_->setEnabled(true);
// controls_dock_widget_->setFloating(false);
// controls_dock_widget_->setFeatures(QDockWidget::AllDockWidgetFeatures);
// controls_dock_widget_->setAllowedAreas(Qt::BottomDockWidgetArea|Qt::TopDockWidgetArea);

// QWidget* dockWidgetContents = new QWidget(this);
// dockWidgetContents->setObjectName(QString::fromUtf8("dockWidgetContents"));
// QVBoxLayout* vboxLayout = new QVBoxLayout;//(dockWidgetContents);

 QHBoxLayout* hboxLayout = new QHBoxLayout(); // dockWidgetContents);
 hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
 hboxLayout->setContentsMargins(4, 0, 4, 0);
 QSpacerItem* horizontalSpacer = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

 hboxLayout->addItem(horizontalSpacer);

 QHBoxLayout* _2 = new QHBoxLayout();
 _2->setObjectName(QString::fromUtf8("_2"));

 page_label_ = new QLabel(this);
 page_label_->setObjectName(QString::fromUtf8("page_label_"));

 _2->addWidget(page_label_);

 page_spin_box_ = new Reverse_Spin_Box(this);
 //?page_spin_box_->setObjectName(QString::fromUtf8("page_spin_box_"));
//? page_spin_box_->setEnabled(false);

// page_spin_box_->setMaximum(0);
// page_spin_box_->setMinimum(-8);

 //page_spin_box_->set_maximum()


 _2->addWidget(page_spin_box_);


 hboxLayout->addLayout(_2);

 QSpacerItem* horizontalSpacer_2 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

 hboxLayout->addItem(horizontalSpacer_2);

 QHBoxLayout* _3 = new QHBoxLayout();
 _3->setObjectName(QString::fromUtf8("_3"));

 search_label_ = new QLabel(this);
 search_label_->setObjectName(QString::fromUtf8("search_label_"));
 search_label_->setTextFormat(Qt::AutoText);

 _3->addWidget(search_label_);

 search_line_edit_ = new QLineEdit(this);
 search_line_edit_->setObjectName(QString::fromUtf8("search_line_edit_"));
 search_line_edit_->setEnabled(false);

 _3->addWidget(search_line_edit_);

 search_combo_box_ = new QComboBox(this);
 search_combo_box_->setObjectName(QString::fromUtf8("search_combo_box_"));
 search_combo_box_->setEnabled(false);

 _3->addWidget(search_combo_box_);

 find_button_ = new QPushButton(this);
 find_button_->setObjectName(QString::fromUtf8("find_button_"));
 find_button_->setEnabled(false);

 _3->addWidget(find_button_);

 clear_button_ = new QPushButton(this);
 clear_button_->setObjectName(QString::fromUtf8("clear_button_"));
 clear_button_->setEnabled(false);

 _3->addWidget(clear_button_);

 box_button_ =  new QPushButton("Stencil", this);
 _3->addWidget(box_button_);

 hboxLayout->addLayout(_3);

 QSpacerItem* spacerItem = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

 hboxLayout->addItem(spacerItem);

 scale_label_ = new QLabel(this);
 scale_label_->setObjectName(QString::fromUtf8("label"));

 hboxLayout->addWidget(scale_label_);

 scale_combo_box_ = new QComboBox(this);
 scale_combo_box_->setObjectName(QString::fromUtf8("scale_combo_box_"));
 scale_combo_box_->setEnabled(true);

 hboxLayout->addWidget(scale_combo_box_);

 QSpacerItem* horizontalSpacer_3 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

 hboxLayout->addItem(horizontalSpacer_3);

 controls_layout_->addLayout(hboxLayout);

// vboxLayout->addLayout(hboxLayout);
// dockWidgetContents->setLayout(vboxLayout);
// controls_frame_->setLayout(controls_layout_);

 //controls_layout_->addWidget(controls_frame_);

 main_layout_->addLayout(controls_layout_);

// controls_frame_

// controls_dock_widget_->setWidget(dockWidgetContents);
 //
 //local_main_window_->addDockWidget(static_cast<Qt::DockWidgetArea>(4), controls_dock_widget_);

 QVector<qreal> scales {{ .25, .5, .75, 1, 1.25, 1.5, 2, 3, 4 }};

 connect(scale_combo_box_, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
  [this, scales](int index)
 {
  qreal scale = scales.value(index, 1);
//  if(index == 0)
//  {
//   return;
//  }
  pdf_document_widget_->reset_scale(scale);
 });


// connect(centerview_, SIGNAL(activate_screenshot()),
//         this, SLOT(activate_screenshot_requested()));





 pdf_document_widget_ = new PDF_Document_Widget(this);

 connect(pdf_document_widget_, SIGNAL(save_stencil_to_file_requested()),
   this, SLOT(handle_save_stencil_to_file_requested()));

 connect(pdf_document_widget_, SIGNAL(open_stencil_from_file_requested()),
   this, SLOT(handle_open_stencil_from_file_requested()));

 connect(pdf_document_widget_, SIGNAL(ocr_conversion_requested()),
   this, SLOT(handle_ocr_conversion_requested()));


 pdf_document_widget_->setDocument(pdf_file_path_);

  //  "/home/nlevisrael/NDP/pain-management-center-new-patient-history-2012.pdf"

// QFrame* qf = new QFrame(this);
// QVBoxLayout* pdf_document_vbox = new QVBoxLayout;
// pdf_document_vbox->addWidget(pdf_document_widget_);
// qf->setLayout(pdf_document_vbox);

// pdf_document_scroll_area_ = new QScrollArea(this);
// pdf_document_scroll_area_->setWidget(pdf_document_widget_);
// pdf_document_widget_->set_surrounding_scroll_area(pdf_document_scroll_area_);

 pdf_document_scroll_area_ = nullptr;

 int nop = pdf_document_widget_->number_of_pages();

 page_spin_box_->set_maximum(nop - 1);

 connect(page_spin_box_, SIGNAL(value_changed(int)),
         pdf_document_widget_, SLOT(setPage(int)));

 connect(pdf_document_widget_, SIGNAL(pageChanged(int)),
         page_spin_box_, SLOT(set_value(int)));


//? qf->setMinimumSize(300, 300);

//? pdf_document_vbox->setSizeConstraint(QLayout::SetFixedSize);

 go_button_ = new QPushButton("Go", this);

 open_button_ = new QPushButton("Open", this);


 connect(go_button_, &QPushButton::clicked, [this]
 {
  pdf_file_path_ = url_line_edit_->text();
  pdf_document_widget_->setDocument(pdf_file_path_);
 });

 connect(open_button_, &QPushButton::clicked, [this]
 {
  QFileInfo qfi(pdf_file_path_);

  QString dir = qfi.absoluteDir().absolutePath();

  QString fp = QFileDialog::getOpenFileName(this, "Open PDF File", dir, "*.pdf");

  pdf_document_widget_->setDocument(fp);

  int nop = pdf_document_widget_->number_of_pages();

  if(nop == 0)
  {
   QMessageBox::information(this,
     "Load Error", "PDF File Not Recognized.  File not loaded.");

   pdf_document_widget_->setDocument(pdf_file_path_);
  }
  else
  {
   pdf_file_path_ = fp;
   url_line_edit_->setText(pdf_file_path_);
   //pdf_document_widget_->setDocument(pdf_file_path_);
   page_spin_box_->set_maximum(nop);
  }
 });

 url_label_  = new QLabel("URL", this);
 url_line_edit_ = new QLineEdit(this);

 url_line_edit_->setText(pdf_file_path_);

 url_layout_ = new QHBoxLayout;
 url_layout_->addWidget(url_label_);
 url_layout_->addWidget(url_line_edit_);
 url_layout_->addWidget(go_button_);
 url_layout_->addWidget(open_button_);


 main_layout_->addWidget(pdf_document_widget_);
 main_layout_->addLayout(url_layout_);

 box_button_->setCheckable(true);


 setLayout(main_layout_);

 retranslate_ui();

 show();
}

bool View_PDF_Frame::wants_box()
{
 return box_button_->isChecked();
}

void View_PDF_Frame::load_file(QString path)
{
 pdf_file_path_ = path;
 pdf_document_widget_->setDocument(path);
 url_line_edit_->setText(path);
}


#define QUUTF8

void View_PDF_Frame::retranslate_ui()
{
//    MainWindow->setWindowTitle(QApplication::translate("MainWindow", "PDF Viewer", 0 QUUTF8));
//    openAction->setText(QApplication::translate("MainWindow", "&Open...", 0 QUUTF8));
//    openAction->setShortcut(QApplication::translate("MainWindow", "Ctrl+O", 0 QUUTF8));
//    exitAction->setText(QApplication::translate("MainWindow", "E&xit", 0 QUUTF8));
//    exitAction->setShortcut(QApplication::translate("MainWindow", "Ctrl+Q", 0 QUUTF8));
//    increaseScaleAction->setText(QApplication::translate("MainWindow", "&Increase Scale", 0 QUUTF8));
//    increaseScaleAction->setShortcut(QApplication::translate("MainWindow", "Ctrl++", 0 QUUTF8));
//    decreaseScaleAction->setText(QApplication::translate("MainWindow", "&Decrease Scale", 0 QUUTF8));
//    decreaseScaleAction->setShortcut(QApplication::translate("MainWindow", "Ctrl+-", 0 QUUTF8));
//    documentControlsAction->setText(QApplication::translate("MainWindow", "&Document Controls", 0 QUUTF8));
//    selectedTextAction->setText(QApplication::translate("MainWindow", "&Selected Text", 0 QUUTF8));
//    menu_File->setTitle(QApplication::translate("MainWindow", "&File", 0 QUUTF8));
//    menu_Windows->setTitle(QApplication::translate("MainWindow", "&Windows", 0 QUUTF8));
//    controlsDockWidget->setWindowTitle(QApplication::translate("MainWindow", "Document Controls", 0 QUUTF8));
    page_label_->setText(QApplication::translate("CLG_DB_Anteview", "Page:", 0 QUUTF8));
    search_label_->setText(QApplication::translate("MainWindow", "Search for:", 0 QUUTF8));
    search_combo_box_->clear();
    search_combo_box_->insertItems(0, QStringList()
     << QApplication::translate("MainWindow", "Forwards", 0 QUUTF8)
     << QApplication::translate("MainWindow", "Backwards", 0 QUUTF8)
    );
    find_button_->setText(QApplication::translate("MainWindow", "Find", 0 QUUTF8));
    clear_button_->setText(QApplication::translate("MainWindow", "Clear", 0 QUUTF8));
    scale_label_->setText(QApplication::translate("MainWindow", "Scale PDF Document:", 0 QUUTF8));
    scale_combo_box_->clear();
    scale_combo_box_->insertItems(0, QStringList()
     << QApplication::translate("MainWindow", "25%", 0 QUUTF8)
     << QApplication::translate("MainWindow", "50%", 0 QUUTF8)
     << QApplication::translate("MainWindow", "75%", 0 QUUTF8)
     << QApplication::translate("MainWindow", "100%", 0 QUUTF8)
     << QApplication::translate("MainWindow", "125%", 0 QUUTF8)
     << QApplication::translate("MainWindow", "150%", 0 QUUTF8)
     << QApplication::translate("MainWindow", "200%", 0 QUUTF8)
     << QApplication::translate("MainWindow", "300%", 0 QUUTF8)
     << QApplication::translate("MainWindow", "400%", 0 QUUTF8)
    );
    scale_combo_box_->setCurrentIndex(3);

     //selectionDockWidget->setWindowTitle(QApplication::translate("MainWindow", "Selected Text", 0 QUUTF8));
} // retranslateUi






View_PDF_Frame::~View_PDF_Frame()
{
 //?
}



