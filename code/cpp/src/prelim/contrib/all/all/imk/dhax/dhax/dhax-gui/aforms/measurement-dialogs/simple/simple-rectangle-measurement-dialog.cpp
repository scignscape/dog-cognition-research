
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "simple-rectangle-measurement-dialog.h"

#include "aforms/simple/simple-rectangle-annotation.h"

#include "styles.h"

#include <QPushButton>

#include <QDebug>
#include <QMessageBox>

#include <QFileDialog>

#include <QMenu>

#include "subwindows/clickable-label.h"


#include <QPainter>
#include <QPainterPath>
#include <QPen>

#include <QFileInfo>


QString add_ratio_glyph(QString s)
{
 return s + QString(" (%1)").arg(QChar(0x223A));
}


void Solid_Color_Label::paintEvent(QPaintEvent* e)
{
 QPainter p(this);
 p.setRenderHint(QPainter::Antialiasing);
 QPainterPath path;
 path.addRoundedRect(QRectF(1, 1, width_, height_), corners_, corners_);
 p.setPen(Qt::NoPen);
 p.fillPath(path, color_);
 p.drawPath(path);

 QFont font;
 font.setPixelSize(font_pixel_size_);

 QPen pen(Qt::black, 1);
 p.setPen(pen);
 p.setFont(font);
 p.drawText(width_ + text_offset_, height_ - ((height_ - font_pixel_size_) / 2),
   QString("Hex: %1").arg(QString::number(color_.rgb(), 16).mid(2)));
}



Simple_Rectangle_Measurement_Dialog::Simple_Rectangle_Measurement_Dialog(Simple_Rectangle_Annotation* ann,
  QWidget* parent)
  :  QDialog(parent), color_mean_counts_(nullptr)
{
 annotation_ = ann;
 main_layout_ = new QVBoxLayout;

 info_layout_ = new QFormLayout;

 info_scroll_area_ = new QScrollArea(this);

 info_frame_ = new QFrame(this);


 Simple_Rectangle_Annotation::Measurements& ms = ann->get_measurements();

 using Parameters = Simple_Rectangle_Annotation::Parameters;
 parameter_labels_.resize(Parameters::count);

 parameter_labels_[Parameters::u2_width] = new_QLabel(ms.width);
 parameter_labels_[Parameters::u2_height] = new_QLabel(ms.height);
 parameter_labels_[Parameters::u2_perimeter] = new_QLabel(ms.perimeter);

 parameter_labels_[Parameters::u2_image_width] = new_QLabel(ms.image_width);
 parameter_labels_[Parameters::u2_image_height] = new_QLabel(ms.image_height);
 parameter_labels_[Parameters::u2_image_perimeter] = new_QLabel(ms.image_perimeter);

 parameter_labels_[Parameters::u4_area] = new_QLabel(ms.area);
 parameter_labels_[Parameters::u4_image_area] = new_QLabel(ms.image_area);

 parameter_labels_[Parameters::r8_wh_ratio] = new_QLabel(ms.wh_ratio);
 parameter_labels_[Parameters::r8_hw_ratio] = new_QLabel(ms.hw_ratio);
 parameter_labels_[Parameters::r8_image_wh_ratio] = new_QLabel(ms.image_wh_ratio);
 parameter_labels_[Parameters::r8_image_hw_ratio] = new_QLabel(ms.image_hw_ratio);

 parameter_labels_[Parameters::r8_width_against_image] = new_QLabel(ms.width_against_image);
 parameter_labels_[Parameters::r8_height_against_image] = new_QLabel(ms.height_against_image);
 parameter_labels_[Parameters::r8_perimeter_against_image] = new_QLabel(ms.perimeter_against_image);
 parameter_labels_[Parameters::r8_area_against_image] = new_QLabel(ms.area_against_image);

 using D = Simple_Rectangle_Annotation::Directions;

 parameter_labels_[Parameters::u2_left_margin] = new_QLabel(ms.margins[D::left]);
 parameter_labels_[Parameters::u2_top_left_margin] = new_QLabel(ms.margins[D::top_left]);
 parameter_labels_[Parameters::u2_top_margin] = new_QLabel(ms.margins[D::top]);
 parameter_labels_[Parameters::u2_top_right_margin] = new_QLabel(ms.margins[D::top_right]);

 parameter_labels_[Parameters::u2_right_margin] = new_QLabel(ms.margins[D::right]);
 parameter_labels_[Parameters::u2_bottom_right_margin] = new_QLabel(ms.margins[D::bottom_right]);
 parameter_labels_[Parameters::u2_bottom_margin] = new_QLabel(ms.margins[D::bottom]);
 parameter_labels_[Parameters::u2_bottom_left_margin] = new_QLabel(ms.margins[D::bottom_left]);

 parameter_labels_[Parameters::r8_left_margin_against_image] = new_QLabel(ms.margins_against_image[D::left]);
 parameter_labels_[Parameters::r8_top_left_margin_against_image] = new_QLabel(ms.margins_against_image[D::top_left]);
 parameter_labels_[Parameters::r8_top_margin_against_image] = new_QLabel(ms.margins_against_image[D::top]);
 parameter_labels_[Parameters::r8_top_right_margin_against_image] = new_QLabel(ms.margins_against_image[D::top_right]);

 parameter_labels_[Parameters::r8_right_margin_against_image] = new_QLabel(ms.margins_against_image[D::right]);
 parameter_labels_[Parameters::r8_bottom_right_margin_against_image] = new_QLabel(ms.margins_against_image[D::bottom_right]);
 parameter_labels_[Parameters::r8_bottom_margin_against_image] = new_QLabel(ms.margins_against_image[D::bottom]);
 parameter_labels_[Parameters::r8_bottom_left_margin_against_image] = new_QLabel(ms.margins_against_image[D::bottom_left]);


 info_layout_->addRow("Width", parameter_labels_[Parameters::u2_width]);
 info_layout_->addRow("Height", parameter_labels_[Parameters::u2_height]);
 info_layout_->addRow("Perimeter", parameter_labels_[Parameters::u2_perimeter]);

 info_layout_->addRow("Image Width", parameter_labels_[Parameters::u2_image_width]);
 info_layout_->addRow("Image Height", parameter_labels_[Parameters::u2_image_height]);
 info_layout_->addRow("Image Perimeter", parameter_labels_[Parameters::u2_image_perimeter]);

 info_layout_->addRow("Area", parameter_labels_[Parameters::u4_area]);
 info_layout_->addRow("Image Area", parameter_labels_[Parameters::u4_image_area]);

 info_layout_->addRow("Width/Height", parameter_labels_[Parameters::r8_wh_ratio]);
 info_layout_->addRow("Height/Width", parameter_labels_[Parameters::r8_hw_ratio]);
 info_layout_->addRow("Image Width/Height", parameter_labels_[Parameters::r8_image_wh_ratio]);
 info_layout_->addRow("Image Height/Width", parameter_labels_[Parameters::r8_image_hw_ratio]);

 info_layout_->addRow(add_ratio_glyph("Width"), parameter_labels_[Parameters::r8_width_against_image]);
 info_layout_->addRow(add_ratio_glyph("Height"), parameter_labels_[Parameters::r8_height_against_image]);
 info_layout_->addRow(add_ratio_glyph("Perimeter"), parameter_labels_[Parameters::r8_perimeter_against_image]);
 info_layout_->addRow(add_ratio_glyph("Area"), parameter_labels_[Parameters::r8_area_against_image]);


 info_layout_->addRow("Left Margin", parameter_labels_[Parameters::u2_left_margin]); //  = new_QLabel(ms.margins[D::left]);
 info_layout_->addRow("Top Left Margin", parameter_labels_[Parameters::u2_top_left_margin]); //  = new_QLabel(ms.margins[D::top_left]);
 info_layout_->addRow("Top Margin", parameter_labels_[Parameters::u2_top_margin]); //  = new_QLabel(ms.margins[D::top]);
 info_layout_->addRow("Top Right Margin", parameter_labels_[Parameters::u2_top_right_margin]); //  = new_QLabel(ms.margins[D::top_right]);

 info_layout_->addRow("Right Margin", parameter_labels_[Parameters::u2_right_margin]); //  = new_QLabel(ms.margins[D::right]);
 info_layout_->addRow("Bottom Right Margin", parameter_labels_[Parameters::u2_bottom_right_margin]); //  = new_QLabel(ms.margins[D::bottom_right]);
 info_layout_->addRow("Bottom Margin", parameter_labels_[Parameters::u2_bottom_margin]); //  = new_QLabel(ms.margins[D::bottom]);
 info_layout_->addRow("Bottom Left Margin", parameter_labels_[Parameters::u2_bottom_left_margin]); //  = new_QLabel(ms.margins[D::bottom_left]);


 info_layout_->addRow(add_ratio_glyph("Left Margin"), parameter_labels_[Parameters::r8_left_margin_against_image]); //  = new_QLabel(ms.margins_against_image[D::left]);
 info_layout_->addRow(add_ratio_glyph("Top Left Margin"), parameter_labels_[Parameters::r8_top_left_margin_against_image]); //  = new_QLabel(ms.margins_against_image[D::top_left]);
 info_layout_->addRow(add_ratio_glyph("Top Margin"), parameter_labels_[Parameters::r8_top_margin_against_image]); //  = new_QLabel(ms.margins_against_image[D::top]);
 info_layout_->addRow(add_ratio_glyph("Top Right Margin"), parameter_labels_[Parameters::r8_top_right_margin_against_image]); //  = new_QLabel(ms.margins_against_image[D::top_right]);

 info_layout_->addRow(add_ratio_glyph("Right Margin"), parameter_labels_[Parameters::r8_right_margin_against_image]); //  = new_QLabel(ms.margins_against_image[D::right]);
 info_layout_->addRow(add_ratio_glyph("Bottom Right Margin"), parameter_labels_[Parameters::r8_bottom_right_margin_against_image]); //  = new_QLabel(ms.margins_against_image[D::bottom_right]);
 info_layout_->addRow(add_ratio_glyph("Bottom Margin"), parameter_labels_[Parameters::r8_bottom_margin_against_image]); //  = new_QLabel(ms.margins_against_image[D::bottom]);
 info_layout_->addRow(add_ratio_glyph("Bottom Left Margin"), parameter_labels_[Parameters::r8_bottom_left_margin_against_image]); //  = new_QLabel(ms.margins_against_image[D::bottom_left]);


// color_mean_counts_ = new QVector<u4> [3];
// color_mean_counts_[0] = QVector<u4> {256};
// color_mean_counts_[1] = QVector<u4> {256};
// color_mean_counts_[2] = QVector<u4> {256};

// QVector<u4> red_counts(256);
// QVector<u4> green_counts(256);
// QVector<u4> blue_counts(256);

 //QVector<u4> rgb[3]{red_counts, green_counts, blue_counts};

 //QVector<u4> (*rgb) [3] = new QVector<u4> [3]{red_counts, green_counts, blue_counts};
// QVector<u4> (*rgb) [3] = (QVector<u4> (*)[3]) malloc(3 * sizeof(QVector<u4>));

 color_mean_counts_ = (QVector<u4> (*) [3]) new QVector<u4> [3] {QVector<u4>(256), QVector<u4>(256), QVector<u4>(256)};
// *color_mean_counts_[0] = QVector<u4>(256);
// *color_mean_counts_[1] = QVector<u4>(256);
// *color_mean_counts_[2] = QVector<u4>(256);

   //new QVector<u4> [3]{red_counts, green_counts, blue_counts};

 annotation_->get_occurants_vectors(*color_mean_counts_);

// ann->get_occurants_vectors(color_mean_counts_);
// QColor qc = ann->get_occurant_color_mean(color_mean_counts_);

 //ttest = new int[3];

 QColor qc = ann->get_occurant_color_mean();

 solid_color_labels_.resize(2);
 solid_color_labels_[0] = new Solid_Color_Label(qc, 0, "occurant-color-mean");

 connect(solid_color_labels_[0], &Solid_Color_Label::customContextMenuRequested,
   this, &Simple_Rectangle_Measurement_Dialog::show_solid_color_label_context_menu);

//   [this] (const QPoint& pos)
// {
//  qDebug() << "pos = " << pos;
// }

 //qDebug() << "qc = " << qc;

 //fill_solid_color_label(solid_color_labels_[0], qc);

 info_layout_->addRow("Occurant Color Mean (10 iterations)", solid_color_labels_[0]);

 QColor qc1 = ann->get_additive_color_mean(*color_mean_counts_);

 //solid_color_labels_[0] = new QLabel(this);
 solid_color_labels_[1] = new Solid_Color_Label(qc1, 1, "additive-color-mean");

 connect(solid_color_labels_[1], &Solid_Color_Label::customContextMenuRequested,
   this, &Simple_Rectangle_Measurement_Dialog::show_solid_color_label_context_menu);

 info_layout_->addRow("Additive Color Mean", solid_color_labels_[1]);

 info_frame_->setLayout(info_layout_);

 info_scroll_area_->setWidget(info_frame_);

 //info_scroll_area_->setWidgetResizable(true);

 main_layout_->addWidget(info_scroll_area_);

 //setMinimumWidth(400);

 setWindowTitle("Annotation Measurement");

 button_box_ = new QDialogButtonBox(this);

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


 connect(button_box_, SIGNAL(accepted()), this, SLOT(accept()));
 connect(button_box_, SIGNAL(rejected()), this, SLOT(close()));

 main_layout_->addWidget(button_box_);

// setWindowFlags(windowFlags() | Qt::FramelessWindowHint);


 setLayout(main_layout_);
}


void Simple_Rectangle_Measurement_Dialog::check_reset_base_temp_folder(QString file_path)
{
 base_temp_folder_ = DEFAULT_DHAX_TEMP_FOLDER;
 if(base_temp_folder_.isEmpty())
 {
  QFileInfo qfi(file_path);
  base_temp_folder_ = qfi.absolutePath();
 }
}

void Simple_Rectangle_Measurement_Dialog::create_overlay_file(QString path, QColor color)
{
 Simple_Rectangle_Annotation::Measurements& ms = annotation_->get_measurements();

 using D = Simple_Rectangle_Annotation::Directions;

 u2 piw = ms.image_width;
 u2 pih = ms.image_height;
 u2 pw = ms.width;
 u2 ph = ms.height;
 u2 mt = ms.margins[D::top];
 u2 ml = ms.margins[D::left];

 QPixmap qpx(piw + 20, pih + 20);
 QPainter pr(&qpx);

// pr.setBrush(Qt::cyan);
// pr.drawRect(qpx.rect());


 pr.setBrush(Qt::white);
 pr.drawRect(10, 10, piw, pih);


 QBrush br;
 br.setColor(Qt::darkCyan);
 br.setStyle(Qt::Dense2Pattern);
 QPen pen;
 pen.setWidth(10);
 pen.setBrush(br);
 pr.setPen(pen);
 pr.drawRect(qpx.rect());
 pr.setPen(Qt::NoPen);
 pr.setBrush(color);
 pr.drawRect(mt + 10, ml + 10, pw, ph);

// QFileInfo qfi(image_file_path_);

// QString baseName = qfi.completeBaseName();

// qDebug() << baseName;

 //QString path = image_file_path_ + ".overlay.png"; //+ qfi.suffix();
 qpx.save(path);
}

QString Simple_Rectangle_Measurement_Dialog::generate_overlay_file(Solid_Color_Label* scl, QString temp_dir)
{
 QFileInfo qfi(image_file_path_);

 QString path;

 static QString path_pattern = "%1/%2-overlay.%3.png";

 if(temp_dir.isEmpty())
 {
  path = path_pattern.arg(qfi.absolutePath()).arg(qfi.completeBaseName()).arg(scl->role());

  QString sel = QFileDialog::getSaveFileName(this, "Enter or Select File Name", path);
  if(sel.isEmpty())
   return {};

  path = sel;
 }
 else if(temp_dir.startsWith('@'))
 {
  temp_dir.replace(0, 1, '/');
  QString dir = qfi.absolutePath() + temp_dir;

  QDir qd(dir);
  qd.mkpath(".");

  path = path_pattern.arg(dir).arg(qfi.completeBaseName()).arg(scl->role());
 }
 else
   path = path_pattern.arg(temp_dir).arg(qfi.completeBaseName()).arg(scl->role());

 create_overlay_file(path, scl->color());

 return path;

}


void Simple_Rectangle_Measurement_Dialog::show_solid_color_label_context_menu(const QPoint& pos)
{
 QMenu* menu = new QMenu(this);//

 Solid_Color_Label* scl = qobject_cast<Solid_Color_Label*>(sender());

 menu->addAction("Generate Overlay File", [this, scl]
 {
  generate_overlay_file(scl); // scl->color();
 });

 menu->addAction("Generate Color-Mean Summary File", [this, scl]
 {
  generate_occurant_color_mean_summary_file(); // scl->color();
 });

 menu->addAction("Show Dialog", [this]
 {
  //QFileInfo qfi(image_file_path_);

  //this->metaObject()->className();

  QString cnf = class_name_folder("@_proc");

  QStringList qsl;
  QString path = generate_occurant_color_mean_summary_file(cnf); // scl->color();
  qsl << path;
  path = generate_overlay_file(solid_color_labels_[0], cnf); // scl->color();
  qsl << path;
  path = generate_overlay_file(solid_color_labels_[1], cnf); // scl->color();
  qsl << path;

  Q_EMIT color_mean_dialog_requested(base_temp_folder_, qsl);

 });

 qDebug() << "pos = " << pos;

 menu->popup(scl->mapToGlobal(pos));
}

QString Simple_Rectangle_Measurement_Dialog::generate_occurant_color_mean_summary_file(QString temp_dir)
{
 QString path;

 QFileInfo qfi(image_file_path_);
 static QString path_pattern = "%1/%2-o-means.png";


 if(temp_dir.isEmpty())
 {
  path = path_pattern.arg(qfi.absolutePath()).arg(qfi.completeBaseName());
  qDebug() << path;

  QString sel = QFileDialog::getSaveFileName(this, "Enter or Select File Name", path);
  if(sel.isEmpty())
    return {};
 }
 else if(temp_dir.startsWith('@'))
 {
  temp_dir.replace(0, 1, '/');
  QString dir = base_temp_folder_ + temp_dir;

  QDir qd(dir);
  qd.mkpath(".");

  path = path_pattern.arg(dir).arg(qfi.completeBaseName());
 }
 else
   path = path_pattern.arg(temp_dir).arg(qfi.completeBaseName());


 QColor colors[9][9];

 QColor am = annotation_->get_additive_color_mean(*color_mean_counts_);

 for(u1 r = 1, row = 0; row < 9; ++row, r += 2) // rounding factor from 1 to 17  (17 * 15 = 255)
 {
  for(u1 i = 1, col = 0; col < 9; ++col, i += 3) // iterations from 1 to 25
  {
   QColor c = annotation_->get_occurant_color_mean(*color_mean_counts_, i, r); //*color_mean_counts
   colors[row][col] = c;
  }
 }

 QPixmap qpx(270, 300);
 QPainter pr(&qpx);
 pr.setPen(Qt::NoPen);

 pr.setBrush(Qt::white);
 pr.drawRect(0, 0, 270, 30);

 pr.setBrush(am);
 pr.drawRect(2, 2, 266, 27);

 for(u2 x = 0, row = 0; row < 9; ++row, x += 30)
 {
  for(u2 y = 30, col = 0; col < 9; ++col, y += 30)
  {
   pr.setBrush(colors[row][col]);
   pr.drawRect(x, y, 30, 30);
  }
 }
 qpx.save(path);

 return path;
}


Simple_Rectangle_Measurement_Dialog::~Simple_Rectangle_Measurement_Dialog()
{
 delete [] color_mean_counts_;
}
