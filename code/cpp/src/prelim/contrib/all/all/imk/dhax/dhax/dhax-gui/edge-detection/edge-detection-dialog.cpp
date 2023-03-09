
#include <QtWidgets>
#include <functional>

#include "edge-detection-dialog.h"
//#include "ui_edge-detection-dialog.h"

#include "edge-detection-algorithms.h"

#include "self-connect.h"

#include "stash-signals.h"


using namespace std;


Edge_Detection_Dialog::Edge_Detection_Dialog(QString file_path, QString file_path_q3x3, QWidget *parent) :
  Edge_Detection_Dialog(file_path, file_path_q3x3, QColor(), QColor(), parent)
{

}



Edge_Detection_Dialog::Edge_Detection_Dialog(QString file_path, QString file_path_q3x3,
  QColor background_pole, QColor foreground_pole, QWidget *parent) :
  QDialog(parent), blur_factor_(0), images_count_(0), background_pole_(background_pole),
  foreground_pole_(foreground_pole)
//    ui(new Ui::Edge_Detection_Dialog)
{
 setObjectName("Edge_Detection_Dialog");

 //    ui_->setupUi(this);
 scene_ = new QGraphicsScene(this);

 setWindowModality(Qt::NonModal);
 resize(441, 453);
 setAutoFillBackground(false);
 //setStyleSheet(QString::fromUtf8(""));
 main_layout_ = new QVBoxLayout(this);
 main_layout_->setSpacing(6);
 main_layout_->setContentsMargins(11, 11, 11, 11);

// main_layout_->setObjectName(QString::fromUtf8("verticalLayout"));

 view_group_box_ = new QGroupBox(this);

 view_group_box_->setMaximumHeight(55);


 _AUTO_OBJECT_NAME_(view_group_box_) //->setObjectName(QString::fromUtf8("groupBox"));

 view_group_box_->setStyleSheet(
   "QGroupBox {"
   "background-color: qlineargradient(x1: 0, y1: 0, x2: 0.5, y2: 1, stop: 0 #E0E0E0, stop: 1 #F3D3E3);"
   "border: 2px solid gray;"
   "border-radius: 5px;"
   "margin-top: 3ex;}"
   "QGroupBox::title {"
   "subcontrol-origin: margin;"
   "padding: 1 4px;}");


//    QString::fromUtf8("QGroupBox{background-color: #F3D3E3; color: black}"
//    "QGroupBox::title{background-color: #F3F3F3;}"
//    "QGroupBox::title{background-color: #F3F3F3;}"

//                                            ));

 //save_button_->setText(

 view_group_box_layout_ = new QHBoxLayout(view_group_box_); //view_group_box_);

 view_group_box_layout_->addStretch();

 view_group_box_layout_->setSpacing(0);
 view_group_box_layout_->setContentsMargins(0,0,0,0);

// view_group_box_layout_->setObjectName(QString::fromUtf8("horizontalLayout_2"));

 select_image_button_ = new QPushButton(view_group_box_);

// select_image_button_->setObjectName(QString::fromUtf8("pushButton"));

 _AUTO_OBJECT_NAME_(select_image_button_) //->setObjectName(QString::fromUtf8("groupBox"));


 select_image_button_->setText("Select New Image");
 select_image_button_->setMaximumWidth(150);

 view_group_box_layout_->addWidget(select_image_button_);
// view_group_box_layout_->addStretch();
 view_group_box_layout_->addSpacing(28);

 view_combo_box_label_ = new QLabel("View:", view_group_box_);
 view_combo_box_label_->setMaximumWidth(30);
 view_combo_box_label_->setMargin(0);

 view_group_box_layout_->addWidget(view_combo_box_label_, Qt::AlignRight);


 view_combo_box_ = new QComboBox(view_group_box_);
 view_combo_box_->addItem(QString());
 view_combo_box_->addItem(QString());
 view_combo_box_->addItem(QString());
 view_combo_box_->addItem(QString());
 view_combo_box_->addItem(QString());
 view_combo_box_->addItem(QString());
// view_combo_box_->addItem("Original"); //QString());
// view_combo_box_->addItem("Canny");
// view_combo_box_->addItem("Sobel");
// view_combo_box_->addItem("Prewitt");
// view_combo_box_->addItem("Roberts");
// view_combo_box_->addItem("Scharr");
 view_combo_box_->setObjectName(QString::fromUtf8("comboBox"));
 view_combo_box_->setLayoutDirection(Qt::LeftToRight);
 view_combo_box_->setMaximumWidth(80);

 _AUTO_OBJECT_NAME_(view_combo_box_) //->setObjectName(QString::fromUtf8("groupBox"));

 view_group_box_layout_->addWidget(view_combo_box_);
// view_group_box_layout_->addStretch();

 view_group_box_layout_->addSpacing(15);

 canny_min_combo_box_ = new QComboBox(view_group_box_);
 {
  const QSignalBlocker blocker(canny_min_combo_box_);

  for(u1 u = 10; u <= 220; u += 10)
  {
   canny_min_combo_box_->addItem(QString::number(u));
  }
  canny_min_combo_box_ >> Connect(int overload_of QComboBox::currentIndexChanged)
    to_lambda[this](int index)
  {
   canny_min_ = 10 * (index + 1);

   if(image_ && (view_combo_box_->currentIndex() == 1))
     recalculate_image(); //calculate_image(view_combo_box_->currentIndex());
  };

 }

 canny_min_combo_box_->setStyleSheet("combobox-popup: 0;");
 canny_min_combo_box_->setMaxVisibleItems(5);
 canny_min_combo_box_->setCurrentIndex(3);
 canny_min_combo_box_label_ = new QLabel("Canny min:");
 view_group_box_layout_->addWidget(canny_min_combo_box_label_);
 view_group_box_layout_->addWidget(canny_min_combo_box_);

 view_group_box_layout_->addSpacing(4);


 canny_max_combo_box_ = new QComboBox(view_group_box_);

 {
  const QSignalBlocker blocker(canny_max_combo_box_);

  for(u1 u = 20; u <= 240; u += 10)
  {
   canny_max_combo_box_->addItem(QString::number(u));
  }
  canny_max_combo_box_ >> Connect(int overload_of QComboBox::currentIndexChanged)
    to_lambda[this](int index)
  {
   canny_max_ = 10 + (10 * (index + 1));

   if(image_ && (view_combo_box_->currentIndex() == 1) )
     recalculate_image(); //view_combo_box_->currentIndex());
  };
 }

 canny_max_combo_box_->setStyleSheet("combobox-popup: 0;");
 canny_max_combo_box_->setMaxVisibleItems(5);
 canny_max_combo_box_->setCurrentIndex(10);
 canny_max_combo_box_label_ = new QLabel("max:");
 view_group_box_layout_->addWidget(canny_max_combo_box_label_);
 view_group_box_layout_->addWidget(canny_max_combo_box_);

 view_group_box_layout_->addSpacing(15);

 check_box_layout_ = new QVBoxLayout;

 check_box_layout_->setContentsMargins(0,0,0,0);
 check_box_layout_->setSpacing(0);

 check_box_layout_->addStretch();

 blur_check_box_ = new QCheckBox("Use Blur", this);
 connect(blur_check_box_, &QCheckBox::toggled, [=](bool checked)
 {
  if(checked)
    blur_factor_ = 1;
  else
    blur_factor_ = 0;

  recalculate_image();
 });

 check_box_layout_->addWidget(blur_check_box_);


 fb_poles_check_box_ = new QCheckBox("Use F/B Poles", this);

 if(background_pole_.isValid() && foreground_pole_.isValid())
 {
  //QPair<QColor, QColor>* _poles = new QPair<QColor, QColor>(foreground_pole_, background_pole_);
  poles_ = (n8) new QPair<QColor, QColor>(foreground_pole_, background_pole_);
  ++poles_;
  connect(fb_poles_check_box_, &QCheckBox::toggled, [=](bool checked)
  {
   if(checked)
   {
    if(poles_ % 2)
      --poles_;
   }
   else
   {
    if((poles_ % 2) == 0)
      ++poles_;
   }
   recalculate_image();

  });
 }
 else
 {
  poles_ = 1;
  fb_poles_check_box_->setEnabled(false);
 }

 check_box_layout_->addWidget(fb_poles_check_box_);

 check_box_layout_->addStretch();

 view_group_box_layout_->addLayout(check_box_layout_);

 view_group_box_layout_->addSpacing(18);

 save_button_ = new QPushButton(view_group_box_);
// save_button_->setObjectName(QString::fromUtf8("select_image_button_2"));

 _AUTO_OBJECT_NAME_(save_button_) //->setObjectName(QString::fromUtf8("groupBox"));


 save_button_->setMaximumWidth(50);

 view_group_box_layout_->addWidget(save_button_);

 view_group_box_layout_->addSpacing(5);
 view_group_box_layout_->addStretch();

 close_button_ = new QPushButton("Close", this);
 close_button_->setMaximumWidth(50);
 view_group_box_layout_->addWidget(close_button_);

 close_button_
   >> Connect(clicked)
   to_lambda[this](bool)
 {
  close();
 };


 main_layout_->addWidget(view_group_box_);

 image_ = new QGraphicsView(this);
 image_->setObjectName(QString::fromUtf8("image"));
 image_->setStyleSheet(QString::fromUtf8("border-style: solid; border-width: 0"));

 main_layout_->addWidget(image_);

 //Edge_Detection_Dialog_->setCentralWidget(centralWidget);

 //retranslateUi(Edge_Detection_Dialog);

 retranslateUi();

 view_combo_box_->setCurrentIndex(0);
// view_combo_box_->setT("View:");

 if(file_path.isEmpty())
 {
  set_view_box_title("(no file)");
 }
 else
 {
  filename_ = file_path;
  load_file(file_path);
  check_reset_base_temp_folder(file_path);

  original_q3x3_ = QImage(file_path_q3x3);

  QTimer::singleShot(0, [this]
  {
   image_->fitInView(scene_->sceneRect(), Qt::KeepAspectRatio);
  });
 }


 QMetaObject::connectSlotsByName(this);
}


void Edge_Detection_Dialog::set_view_box_title(QString file_path)
{
 view_group_box_->setTitle(QString("Image: %1").arg(file_path));
}


void Edge_Detection_Dialog::retranslateUi()
{
 setWindowTitle(QCoreApplication::translate("Edge_Detection_Dialog", "Edge detection", nullptr));
// view_group_box_->setTitle(QCoreApplication::translate("Edge_Detection_Dialog", "Image: ", nullptr));
// select_image_button_->setText(QCoreApplication::translate("Edge_Detection_Dialog", "Select New Image", nullptr));
 view_combo_box_->setItemText(0, QCoreApplication::translate("Edge_Detection_Dialog", "Original", nullptr));
 view_combo_box_->setItemText(1, QCoreApplication::translate("Edge_Detection_Dialog", "Canny", nullptr));
 view_combo_box_->setItemText(2, QCoreApplication::translate("Edge_Detection_Dialog", "Sobel", nullptr));
 view_combo_box_->setItemText(3, QCoreApplication::translate("Edge_Detection_Dialog", "Prewitt", nullptr));
 view_combo_box_->setItemText(4, QCoreApplication::translate("Edge_Detection_Dialog", "Roberts", nullptr));
 view_combo_box_->setItemText(5, QCoreApplication::translate("Edge_Detection_Dialog", "Scharr", nullptr));

// view_combo_box_->setCurrentText(QCoreApplication::translate("Edge_Detection_Dialog", "Original", nullptr));
 save_button_->setText(QCoreApplication::translate("Edge_Detection_Dialog", "Save", nullptr));
} // retranslateUi


Edge_Detection_Dialog::~Edge_Detection_Dialog()
{
 //    delete ui;
}


void Edge_Detection_Dialog::on_select_image_button_clicked(bool)
{
 filename_ = QFileDialog::getOpenFileName(this, tr("Select a single image"), DHAX_IMAGE_FOLDER);
 load_file(filename_);
 check_reset_base_temp_folder(filename_);
}

void Edge_Detection_Dialog::check_reset_base_temp_folder(QString file_path)
{
 base_temp_folder_ = DEFAULT_DHAX_TEMP_FOLDER;
 if(base_temp_folder_.isEmpty())
 {
  QFileInfo qfi(file_path);
  base_temp_folder_ = qfi.absolutePath();
 }
}


void Edge_Detection_Dialog::load_file(QString file_path)
{
 original_ = QImage(file_path);
 display(original_);
 grayscale_ = original_.convertToFormat(QImage::Format_Grayscale8);
 original_grayscale_ = grayscale_;
 view_combo_box_->setCurrentIndex(0);

 set_view_box_title(file_path);
}


void Edge_Detection_Dialog::display(const QImage& image)
{
 ++images_count_;

 QFileInfo qfi(filename_);
 QDir qdir(qfi.absolutePath() + class_name_folder("/_proc") + "/display");

 qdir.mkpath(".");
 QString path = qdir.absoluteFilePath(QString::number(images_count_) + "." + qfi.suffix());
 image.save(path);


 scene_->clear();
 scene_->addPixmap(QPixmap::fromImage(image));
 scene_->setSceneRect(image.rect());
 image_->setScene(scene_);
 image_->fitInView(scene_->sceneRect(), Qt::KeepAspectRatio);
 current_ = image;
}


void Edge_Detection_Dialog::on_view_combo_box_currentIndexChanged(int index)
{
  calculate_image(index);
}

void Edge_Detection_Dialog::recalculate_image()
{
 u1 index = view_combo_box_->currentIndex();
 if(index > 0)
 {
  //calculate_image(0);
  current_ = original_;
  //
  grayscale_ = original_grayscale_;

  //grayscale_ = original_.convertToFormat(QImage::Format_Grayscale8);

  calculate_image(index);
 }
 else
 {
  if(blur_factor_ == 0)
    display(original_);
  else
    display(original_q3x3_);
 }
}


void Edge_Detection_Dialog::calculate_image(u1 index)
{
 QPair<QColor, QColor>* poles = poles_? (poles_ % 2) ? nullptr :
   (QPair<QColor, QColor>*) poles_ : nullptr;

 const QImage& src = poles? original_ : grayscale_;

 QImage::Format out_format = poles? QImage::Format_Grayscale8 : src.format();

 switch (index)
 {
 case 0:
  if(blur_factor_ == 0)
    display(original_);
  else
    display(original_q3x3_);
  break;
 case 1:
  display(canny(src, 1, canny_min_, canny_max_, out_format, blur_factor_, poles));
  break;
 default:
  function<QImage(const QImage&, QImage::Format, u1, QPair<QColor, QColor>*)> functions[] = {
   sobel,
   prewitt,
   roberts,
   scharr
  };
  display(functions[index - 2](src, out_format, blur_factor_, poles));
  break;
 }
}


void Edge_Detection_Dialog::resizeEvent(QResizeEvent* event)
{
 QDialog::resizeEvent(event);
 image_->fitInView(scene_->sceneRect(), Qt::KeepAspectRatio);
}


void Edge_Detection_Dialog::on_save_button_clicked(bool)
{
 auto path_ = QFileDialog::getExistingDirectory(this, tr("Destination"));
 auto name_ = QString("%1_%2").arg(view_combo_box_->currentText(), QFileInfo(filename_).fileName());
 current_.save(QDir(path_).filePath(name_));
}
