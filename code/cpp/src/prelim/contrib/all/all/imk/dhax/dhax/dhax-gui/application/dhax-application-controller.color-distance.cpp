
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

//?

// //   this include should come first
 //     to not conflict with "_flags" ...
#include "stats/dhax-stat-assessment.h"


#include "dhax-application-controller.h"

#include "image-viewer/image-document-controller.h"
#include "main-window/dhax-main-window-controller.h"

#include "stats/stat-test-image.h"
#include "stats/feature-classifier-transform.h"

#include "textio.h"

#include <QVector2D>

#include <QtMath>

#include <QFileDialog>
#include <QDirIterator>

u1 angle_distance(pr2 angles)
{
 u2 gap = angles.inner_positive_difference();

 if(gap > 360)
 {
  // // perhaps a warning?
  gap %= 360;
 }

 if(gap > 180)
   return 360 - gap;

 return gap;
}

struct SV_Centered_Vector
{
 QVector2D qvector;

 SV_Centered_Vector& disk_protrude();

 r8 angle_against_positive_verical() const;
 r8 angle_against_pure_color() const;
 r8 angle_against_nearest_diagonal() const;

 r4 x() const { return qvector.x(); }
 r4 y() const { return qvector.y(); }

 r4 x_abs() const { return qAbs(qvector.x()); }
 r4 y_abs() const { return qAbs(qvector.y()); }

 s1 x_sign() const { return x() < 0 ? -1 : x() > 0? 1 : 0; }
 s1 y_sign() const { return y() < 0 ? -1 : y() > 0? 1 : 0; }

 r4 raw_euclidean_distance(const SV_Centered_Vector& scv) const;

 u1 get_binned_sv_angle() const;

 u1 get_5_10_20_bin() const;

 r4 get_length_protruded() const;

};

r4 SV_Centered_Vector::raw_euclidean_distance(const SV_Centered_Vector& scv) const
{
 return qvector.distanceToPoint(scv.qvector);
}


r8 SV_Centered_Vector::angle_against_positive_verical() const
{
 if(y() > 0)
 {
  r8 radians = qAtan(x() / y());
  return qRadiansToDegrees(radians);
 }
 if(y() < 0)
 {
  r8 radians = qAtan(x() / y_abs());
  return qRadiansToDegrees(radians) + 90;
 }
 return 90 * x_sign();
}


r8 SV_Centered_Vector::angle_against_pure_color() const
{
 r8 angle = angle_against_positive_verical();
 if(angle < -60)
   return angle + 240;
 return qAbs(angle - 120);
}


r8 SV_Centered_Vector::angle_against_nearest_diagonal() const
{
 // //  return values in range 0 - 60
 r8 angle = qAbs(angle_against_positive_verical());
 if(angle < 60)
   return angle;
 return qAbs(angle - 120);
}

r4 SV_Centered_Vector::get_length_protruded() const
{
 r8 stretch, angle = angle_against_nearest_diagonal();
 if(angle == 0)
   stretch = 1;
 else
   stretch = 120 / angle;
 return qvector.length() * stretch;
}

SV_Centered_Vector& SV_Centered_Vector::disk_protrude()
{
 r8 angle = angle_against_nearest_diagonal();
 if(angle > 0)
   //qvector *= ((120 / angle));
   //?
   qvector *= (1 + (angle / 120));
 return *this;
}

#include "global-macros.h"

#define _CASE_MACRO_2(a1, a2)  case a1: case a2:
#define _CASE_MACRO_3(a1, a2, a3)  _CASE_MACRO_2(a1, a2) case a3:
#define _CASE_MACRO_4(a1, a2, a3, a4)  _CASE_MACRO_3(a1, a2, a3) case a4:
#define _CASE_MACRO_5(a1, a2, a3, a4, a5)  _CASE_MACRO_4(a1, a2, a3, a4) case a5:
#define _CASE_MACRO_6(a1, a2, a3, a4, a5, a6)  _CASE_MACRO_5(a1, a2, a3, a4, a5) case a6:
#define _CASE_MACRO_7(a1, a2, a3, a4, a5, a6, a7)  _CASE_MACRO_6(a1, a2, a3, a4, a5, a6) case a7:
#define _CASE_MACRO_8(a1, a2, a3, a4, a5, a6, a7, a8)  _CASE_MACRO_7(a1, a2, a3, a4, a5, a6, a7) case a8:
#define _CASE_MACRO_9(a1, a2, a3, a4, a5, a6, a7, a8, a9) \
  _CASE_MACRO_8(a1, a2, a3, a4, a5, a6, a7, a8) case a9:


#define _CASE_MACRO_(...) _preproc_CONCAT(_CASE_MACRO_, _preproc_NUM_ARGS (__VA_ARGS__)) (__VA_ARGS__)

u1 SV_Centered_Vector::get_binned_sv_angle() const
{
 u1 base = (u1) angle_against_pure_color();
 switch (base)
 {
 _CASE_MACRO_(0, 1) return 0;
 _CASE_MACRO_(2, 3, 4) return 1;
 _CASE_MACRO_(5, 6, 7) return 2;
 _CASE_MACRO_(8, 9, 10, 11) return 3;
 _CASE_MACRO_(12, 13, 14, 15, 16) return 4;
 _CASE_MACRO_(17, 18, 19, 20, 21, 22) return 5;
 _CASE_MACRO_(23, 24, 25, 26, 27, 28, 29) return 6;
 _CASE_MACRO_(30, 31, 32, 33, 34, 35, 36, 37) return 7;
 _CASE_MACRO_(38, 39, 40, 41, 42, 43, 44, 45, 46) return 8;
 default: break;
 }

 if(base < 107)
 {
  if(base < 57) // 47 - 56  (10)
    return 9;

  if(base < 68) // 57 - 67  (11)
    return 10;

  if(base < 80) // 68 - 79  (12)
    return 11;

  if(base < 93)  // 80 - 92  (13)
    return 12;

  return 13; // 93 - 106  (14)
 }


 if(base < 122) // 107 - 121  (15)
   return 14;

 if(base < 138) // 122 - 137  (16)
   return 15;

 if(base < 153) // 138 - 152  (15)
   return 17;

 if(base < 167) // 153 - 166  (14)
   return 18;

 return 19; // 167 - 180
}

u1 SV_Centered_Vector::get_5_10_20_bin() const
{
 u1 sv_bin = get_binned_sv_angle();
 r4 len = get_length_protruded();

 if(len < 60)
   return 30 + (sv_bin / 4);
 if(len < 120)
   return 20 + (sv_bin / 2);
 return sv_bin;
}


SV_Centered_Vector& get_sv_centered_coordinates(SV_Centered_Vector& scv, u1 s, u1 v)
{
 // //  center on v = 170, s = 127.5
 s1 v_altitude = 170 - v;
 //?r8 s_ratio = v == 0 ? 0 : (255 - (s * 2)) / (255 - v);

 //? r8 s_ratio =  (127.5 - s) / 255;
 r4 s_ratio =  1 - (s / 127.5);
 r4 s_altitude =  s_ratio * (v / 2);

 scv = { {s_altitude, (float) v_altitude} };
 //QVector2D sv_vector_n = sv_vector.normalized();

 return scv;
}

u1 raw_hue_distance(u2 ch, u2 h)
{
 // //  result range 0 - 180
 u1 result = qAbs(ch - h);
 if(result > 180)
   result = 360 - result;
 return result;
}

r8 blue_yellow_factor(u2 hue, r8 factor = 12)
{
 if( (hue > 30) && (hue < 210) )
   return qAbs(hue - 120) / (18 * factor);
 if(hue < 30)
   hue += 360;
 return qAbs(hue - 300) / (18 * factor);
}

r8 blue_yellow_factor_average(u2 ch, u2 h, r8 factor = 12)
{
 return (blue_yellow_factor(h, factor) + blue_yellow_factor(ch, factor)) / 2;
}


//r8 red_green_factor(u2 hue, r8 factor = 6)
//{
// if( (hue > 30) && (hue < 210) )
//   return qAbs(hue - 120) / (18 * factor);
// if(hue < 30)
//   hue += 360;
// return qAbs(hue - 300) / (18 * factor);
//}


u1 adjusted_hue_distance(u1 ch, u1 h)
{
 u1 diff = raw_hue_distance(ch, h);

 return diff + (diff * blue_yellow_factor_average(ch, h));
}

r8 merged_distance(u1 h_distance, u1 sv_distance, const QPair<r4, r4>& weights)
{
 return (((r4) h_distance) * weights.first) + (((r4) sv_distance) * weights.second);
}


//?u1 binned_sv_color(const QColor& color)

//u1 binned_sv_color(const SV_Centered_Vector sv& sv)
//{

//}


SV_Centered_Vector get_sv_centered_vector(const QColor& color)
{
 int h, s, v;
 color.getHsv(&h, &s, &v);
 SV_Centered_Vector result;
 get_sv_centered_coordinates(result, s, v);
 return result;
}



u1 hsv_color_distance(const QColor& center_color, const QColor& color)
{
 int ch, cs, cv, h, s, v;

 center_color.getHsv(&ch, &cs, &cv);
 color.getHsv(&h, &s, &v);

 //u1 hgap = angle_distance(pr2{(u2)ch, (u2)h});

 // 2(255-s) - (y - 127.5) / r5
 // 510 - 2s -
 // (637.5 - y - 2s) / r5

 SV_Centered_Vector sv, csv;

 get_sv_centered_coordinates(csv, cs, cv).disk_protrude();
 get_sv_centered_coordinates(sv, s,  v).disk_protrude();

 u1 h_distance = adjusted_hue_distance(ch, h);

 u1 sv_distance = csv.raw_euclidean_distance(sv);

 static QPair<r4, r4> rel_weights(2./3, 1./3);

 r8 md = merged_distance(h_distance, sv_distance, rel_weights);

 return (u1) md;

// sv1s csv { (s1)(127 - cs), (s1)(127 - cv) };
// sv1s sv { (s1)(127 - s), (s1)(127 - v) };


}

u1 hsv_color_distance(QRgb center_pixel, QRgb pixel)
{
 return hsv_color_distance(QColor(center_pixel), QColor(pixel));
}

//QColor normalize_rgb

#ifdef USE_XCSD
void DHAX_Application_Controller::register_test_image(bool then_run)
{
 QString file;

 {
  file = QFileDialog::getOpenFileName(nullptr,
   "Select File", DHAX_STAT_FOLDER "/test-combined");

  if(file.isEmpty())
    return;
 }

 QString folder = DHAX_STAT_FOLDER "/test-combined";
 QDir qd(folder);

 QDirIterator it(folder, QDir::Filter::Dirs | QDir::Filter::NoDotAndDotDot);

 u2 count = 0;
 while(it.hasNext())
 {
  it.next();
  u2 name = it.fileName().toInt();
  if(count < name)
    count = name;
 }

 qd.mkdir(QString::number(count + 1));

 QString new_folder = qd.absoluteFilePath(QString::number(count + 1));

 QString new_file = KA::TextIO::copy_binary_file_to_folder(file, new_folder);

 if(then_run)
   run_combined_test_stats(new_folder, new_file);
}

void DHAX_Application_Controller::combined_test_stats()
{
 QString folder = QFileDialog::getExistingDirectory(nullptr,
   "Select Folder (should have one test image)", DHAX_STAT_FOLDER "/test-combined");

 if(!folder.isEmpty())
   run_combined_test_stats(folder);
}


void DHAX_Application_Controller::run_combined_test_stats()
{
 run_combined_test_stats(DHAX_STAT_FOLDER "/test-combined/default");
}


void DHAX_Application_Controller::run_combined_test_stats(QString folder)
{
 QString path = get_test_file_from_folder(folder);
 if(path.isEmpty())
   return;

 run_combined_test_stats(folder, path);
}


void DHAX_Application_Controller::run_combined_test_stats(QString folder, QString file_path)
{
//? QString folder = DHAX_STAT_FOLDER "/test-combined";

 QDir qd(folder);
 if(!qd.exists("out"))
   qd.mkdir("out");

 qd.cd("out");

 QFileInfo qfi(file_path);
 QString base_name = qfi.baseName();

 if(!qd.exists(base_name))
   qd.mkdir(base_name);

 qd.cd(base_name);

 if(!qd.exists("out-dist"))
   qd.mkdir("out-dist");
 if(!qd.exists("out-0d"))
   qd.mkdir("out-0d");
 if(!qd.exists("out-1d"))
   qd.mkdir("out-1d");
 if(!qd.exists("out-2d"))
   qd.mkdir("out-2d");


 folder = qd.absolutePath();
 file_path = KA::TextIO::copy_binary_file_to_folder(file_path, folder);


//??
// XCSD_Image* xcsd;
// test_pixel_local_aggregate_color_distance(file_path, "out-dist", &xcsd);

 QString ntxh_file;
 XCSD_Image* xcsd = new XCSD_Image;
 xcsd->find_ntxh_file(qd.absoluteFilePath(file_path));

 toroid_run_stats(folder, base_name, qfi.suffix(), xcsd);
}


void DHAX_Application_Controller::toroid_run_stats()
{
 toroid_run_stats(DHAX_STAT_FOLDER "/test", "i1", "png");
}


void DHAX_Application_Controller::toroid_run_stats(QString folder,
  QString file_name, QString extension, XCSD_Image* xcsd)
{
 qDebug() << "folder = " << folder << "file_name = " << file_name <<
             "extension = " << extension;
 DHAX_Stat_Assessment::run_demo_test(folder,
   file_name, extension, this, xcsd);
}


void DHAX_Application_Controller::show_pixel_local_aggregate_color_distance()
{
 Image_Document_Controller* idc = main_window_controller_->image_document_controller();
 if(!idc)
   return;

 // QString fp = idc->current_file_path();

 pixel_local_aggregate_color_distance(idc->current_file_path(), {});
}


void DHAX_Application_Controller::test_pixel_local_aggregate_color_distance()
{
 test_pixel_local_aggregate_color_distance(DHAX_STAT_FOLDER "/test-dist");
}

void DHAX_Application_Controller::test_pixel_local_aggregate_color_distance(QString folder)
{
 QString file_path = get_test_file_from_folder(folder);
 test_pixel_local_aggregate_color_distance(file_path, folder);
}

void DHAX_Application_Controller::test_pixel_local_aggregate_color_distance(QString file_path,
   QString subfolder, XCSD_Image** _xcsd)
{
 qDebug() << "Calculating color distance for " << file_path;

 QString ntxh_file;

 XCSD_Image* xcsd = new XCSD_Image;

 xcsd->load_image_all(file_path, &ntxh_file);
   // xcsd->load_image(file_path, &ntxh_file);

 xcsd->autoset_fb_poles();

 xcsd->check_set_fb_gradient_trimap_to_channels();

 qDebug() << "Autoset background pole: " << xcsd->background_pole() <<
             " and foreground pole: " << xcsd->foreground_pole();

 pixel_local_aggregate_color_distance(file_path, subfolder, xcsd);

 if(_xcsd)
   *_xcsd = xcsd;
}


QString DHAX_Application_Controller::get_test_file_from_folder(QString folder)
{
 QDir qd(folder);
 QStringList images = qd.entryList(QDir::Files | QDir::Readable);

 qDebug() << images;

 if(images.isEmpty())
  return {};

 QString likely_file = *std::min_element(images.begin(), images.end(),
   [] (const QString& s1, const QString& s2)
 {
  return s1.length() < s2.length();
 });

 return qd.absoluteFilePath(likely_file);
}


void DHAX_Application_Controller::pixel_local_aggregate_color_distance(
  QString file_path, QString subfolder, XCSD_Image* xcsd)
{
 Stat_Test_Image stat_image(file_path);

 if(xcsd)
 {
  xcsd->save_foreground_distance_channel_to_red_black_image(stat_image.file_path_with_presuffix("fg", subfolder));
  xcsd->save_foreground_distance_channel_to_red_white_image(stat_image.file_path_with_presuffix("fgw", subfolder));

  xcsd->save_background_distance_channel_to_blue_black_image(stat_image.file_path_with_presuffix("bg", subfolder));
  xcsd->save_background_distance_channel_to_blue_white_image(stat_image.file_path_with_presuffix("bgw", subfolder));

  xcsd->save_fb_one_channel_image(stat_image.file_path_with_presuffix("fb-1c", subfolder));
  xcsd->save_fb_one_channel_image(stat_image.file_path_with_presuffix("fb-1c", "."));
 }


 static u1 corner_weights[3][3]
 {
  {3, 1, 1},
  {1, 3, 2},
  {1, 2, 3},
 };

 static u1 center_weights[3][3]
 {
  {1, 2, 1},
  {1, 3, 1},
  {1, 3, 1},
 };

 static u2 corner_weights_total = 0;
 if(corner_weights_total == 0)
 {
  for(u1 a = 0; a < 3; ++a)
   for(u1 b = 0; b < 3; ++b)
     corner_weights_total += corner_weights[a][b];
 }

 static u2 center_weights_total = 0;
 if(center_weights_total == 0)
 {
  for(u1 a = 0; a < 3; ++a)
   for(u1 b = 0; b < 3; ++b)
     center_weights_total += center_weights[a][b];
 }

// QString fp = idc->current_file_path();

 QImage image(file_path);

 QString result_3 = stat_image.file_path_with_presuffix("1c-3-dist", subfolder);
 QString result_5 = stat_image.file_path_with_presuffix("1c-5-dist", subfolder);
 QString result_7 = stat_image.file_path_with_presuffix("1c-7-dist", subfolder);

 QString result_7rgb = stat_image.file_path_with_presuffix("1c-7rgb-dist", subfolder);

 QString result_8b = stat_image.file_path_with_presuffix("8b", subfolder);
 QString result_8b_up = stat_image.file_path_with_presuffix("8b");

 QString result_8b_all = stat_image.file_path_with_presuffix("8ba", subfolder);
 QString result_8b_all_up = stat_image.file_path_with_presuffix("8ba");

 QString result_8b_all_sorted = stat_image.file_path_with_presuffix("8bas", subfolder);

 QString result_8b_125_cyan = stat_image.file_path_with_presuffix("8b-125-cyan", subfolder);
 QString result_8b_175_cyan = stat_image.file_path_with_presuffix("8b-175-cyan", subfolder);
 QString result_8b_225_cyan = stat_image.file_path_with_presuffix("8b-225-cyan", subfolder);

 wh2 wh = { (u2) image.width(), (u2) image.height()};
 wh2 wh_3 = wh - 3;

 QImage gray_3_image(wh.width, wh.height, QImage::Format_Grayscale8);
 QImage gray_5_image(wh.width, wh.height, QImage::Format_Grayscale8);
 QImage gray_7_image(wh.width, wh.height, QImage::Format_Grayscale8);

 QImage gray_7rgb_image(wh.width, wh.height, QImage::Format_RGB32);

 //?QImage cyan_8b_image(wh.width, wh.height, QImage::Format_RGB32);

 QImage cyan_8b_225_image(wh.width, wh.height, QImage::Format_RGB32);
 QImage cyan_8b_175_image(wh.width, wh.height, QImage::Format_RGB32);
 QImage cyan_8b_125_image(wh.width, wh.height, QImage::Format_RGB32);

 gray_3_image.fill(0);
 gray_5_image.fill(0);
 gray_7_image.fill(0);
 gray_7rgb_image.fill(0);

//? gray_image.save(result);

//? return {};

//? rc2 rc {0, 0};

 //?u1* gray_pixel = gray_image.bits();

 //?QMap<pr1, u4> bin_counts_5_10_20;
 std::map<pr1, pr4> bin_counts_5_10_20;
 std::map<pr1, pr4> bin_counts_5_10_20_all;

 static QRgb cyan = QColor(Qt::cyan).rgb();

 s1 len_r_7_max, len_r_7_min, len_r_5_max, len_r_5_min, len_r_3_max, len_r_3_min,
   len_c_7_max, len_c_7_min, len_c_5_max, len_c_5_min, len_c_3_max, len_c_3_min;

 for(u2 r = 0; r < wh.height; ++r)
 {
  s1 r_offset_min, r_offset_max, c_offset_min, c_offset_max;

  if(r < 3)
  {
   r_offset_min = -r;
   len_r_7_min = -qMin((s4) r, 3);
   len_r_5_min = -qMin((s4) r, 2);
   len_r_3_min = -qMin((s4) r, 1);
  }
  else
  {
   r_offset_min = -3;
   len_r_7_min = -3;
   len_r_5_min = -2;
   len_r_3_min = -1;
  }

  if(r >= wh_3.height)
  {
   r_offset_max = wh_3.height + 2 - r;
   len_r_7_max = qMin((s4) r_offset_max, 3);
   len_r_5_max = qMin((s4) r_offset_max, 2);
   len_r_3_max = qMin((s4) r_offset_max, 1);
  }
  else
  {
   r_offset_max = 3;
   len_r_7_max = 3;
   len_r_5_max = 2;
   len_r_3_max = 1;
  }


//?  QRgb* line = (QRgb*) image.scanLine(rc.r);
  QRgb* line = (QRgb*) image.scanLine(r);

//  u1* gray_3_line =  (u1*) gray_3_image.scanLine(rc.r);
//  u1* gray_5_line =  (u1*) gray_5_image.scanLine(rc.r);
//  u1* gray_7_line =  (u1*) gray_7_image.scanLine(rc.r);

//  QRgb* gray_3_line =  (QRgb*) gray_3_image.scanLine(rc.r);
//  QRgb* gray_5_line =  (QRgb*) gray_5_image.scanLine(rc.r);
//  QRgb* gray_7_line =  (QRgb*) gray_7_image.scanLine(rc.r);

  u1* gray_3_line = (u1*) gray_3_image.scanLine(r);
  u1* gray_5_line = (u1*) gray_5_image.scanLine(r);
  u1* gray_7_line = (u1*) gray_7_image.scanLine(r);
  QRgb* gray_7rgb_line = (QRgb*) gray_7rgb_image.scanLine(r);

  QRgb* cyan_8b_225_line = (QRgb*) cyan_8b_225_image.scanLine(r);
  QRgb* cyan_8b_175_line = (QRgb*) cyan_8b_175_image.scanLine(r);
  QRgb* cyan_8b_125_line = (QRgb*) cyan_8b_125_image.scanLine(r);


  for(u2 c = 0; c < wh.width; ++c)
  {
   if(c < 3)
   {
    c_offset_min = -c;
    len_c_7_min = -qMin((s4) c, 3);
    len_c_5_min = -qMin((s4) c, 2);
    len_c_3_min = -qMin((s4) c, 1);
   }
   else
   {
    c_offset_min = -3;
    len_c_7_min = -3;
    len_c_5_min = -2;
    len_c_3_min = -1;
   }

   if(c >= wh_3.width)
   {
    c_offset_max = wh_3.width + 2 - c;
    len_c_7_max = qMin((s4) c_offset_max, 3);
    len_c_5_max = qMin((s4) c_offset_max, 2);
    len_c_3_max = qMin((s4) c_offset_max, 1);
   }
   else
   {
    c_offset_max = 3;
    len_c_7_max = 3;
    len_c_5_max = 2;
    len_c_3_max = 1;
   }

   u1 area_7 = (len_c_7_max - len_c_7_min + 1) *
     (len_r_7_max - len_r_7_min + 1) - 1;

   u1 area_5 = (len_c_5_max - len_c_5_min + 1) *
     (len_r_5_max - len_r_5_min + 1) - 1;

   u1 area_3 = (len_c_3_max - len_c_3_min + 1) *
     (len_r_3_max - len_r_3_min + 1) - 1;

//   qDebug() << "area 7 = " << area_7;
//   qDebug() << "area 5 = " << area_5;
//   qDebug() << "area 3 = " << area_3;

//   u1 area_5 = (c_offset_max - c_offset_min + 1) *
//     (r_offset_max - r_offset_min + 1) - 1;


//?   QRgb& center_pixel = line[rc.c];
   QRgb& center_pixel = line[c];

   u2 total3 = 0, total5 = 0, total7 = 0;

   for(s1 r_offset = r_offset_min; r_offset <= r_offset_max; ++r_offset)
   {
//    QRgb* rline = (QRgb*) image.scanLine(rc.r + r_offset);
    QRgb* rline = (QRgb*) image.scanLine(r + r_offset);

    for(s1 c_offset = c_offset_min; c_offset <= c_offset_max; ++c_offset)
    {
     if(r_offset == 0 && c_offset == 0)
       continue;

     u1 r_offset_abs = qAbs(r_offset);
     u1 c_offset_abs = qAbs(c_offset);

//?     QRgb& pixel = rline[rc.c + c_offset];
     QRgb& pixel = rline[c + c_offset];

     u1 dist = hsv_color_distance(center_pixel, pixel);

     total7 += (u2) dist;

     if( (r_offset_abs < 3) && (c_offset_abs < 3) )
       total5 += (u2) dist;

     if( (r_offset_abs < 2) && (c_offset_abs < 2) )
       total3 += (u2) dist;

    }
   }

//?   u1 gray7 = total7 / 48, gray5 = total5 / 24, gray3 = total3 / 8;
   u1 gray7 = total7 / area_7, gray5 = total5 / area_5, gray3 = total3 / area_3;



//   *gray_pixel = gray;

//   n8 gp = (n8) gray_pixel;

  //? QRgb rr7 = QColor(gray7, gray7, gray7).rgb();

   gray7 = 255 - gray7;
   gray5 = 255 - gray5;
   gray3 = 255 - gray3;

   QColor center_color = QColor::fromRgb(center_pixel);
   QColor gray7rgb = QColor::fromHsv(center_color.hsvHue(), 255 - gray7, gray7);

   //QColor normed = normalize_rgb(center_color);


   SV_Centered_Vector scv = get_sv_centered_vector(center_color).disk_protrude();
   u1 bin = scv.get_5_10_20_bin();
   u1 h = center_color.hsvHue() / 12;
   {
    auto it = bin_counts_5_10_20_all.find({h, bin});
    if(it == bin_counts_5_10_20_all.end())
      bin_counts_5_10_20_all[{h, bin}] = {1, center_color.rgb()};
    else
      ++bin_counts_5_10_20_all[{h, bin}].first;
   }

   if(gray7 > 125)
   {
    auto it = bin_counts_5_10_20.find({h, bin});
    if(it == bin_counts_5_10_20.end())
      bin_counts_5_10_20[{h, bin}] = {1, center_color.rgb()};
    else
      ++bin_counts_5_10_20[{h, bin}].first;

    cyan_8b_125_line[c] = center_pixel;

    if(gray7 > 175)
    {
     cyan_8b_175_line[c] = center_pixel;
     if(gray7 > 225)
       cyan_8b_225_line[c] = center_pixel;
     else
       cyan_8b_225_line[c] = cyan;
    }
    else
    {
     cyan_8b_175_line[c] = cyan;
     cyan_8b_225_line[c] = cyan;
    }
   }

   else
   {
    cyan_8b_225_line[c] = cyan;
    cyan_8b_175_line[c] = cyan;
    cyan_8b_125_line[c] = cyan;
   }


//   QRgb rr7 = QColor(gray7, gray7, gray7).rgb();
//   QRgb rr5 = QColor(gray5, gray5, gray5).rgb();
//   QRgb rr3 = QColor(gray3, gray3, gray3).rgb();
//   QRgb rr73 = QColor(gray73, gray73, gray73).rgb();

//
   gray_7_line[c] = gray7;
   gray_5_line[c] = gray5;
   gray_3_line[c] = gray3;

   gray_7rgb_line[c] = gray7rgb.rgb();

//   gray_7_image.setPixel(rc.c - 3, rc.r - 3, rr7);
//   gray_5_image.setPixel(rc.c - 3, rc.r - 3, rr5);
//   gray_3_image.setPixel(rc.c - 3, rc.r - 3, rr3);


//   gray_73_image.setPixel(rc.c - 3, rc.r - 3, rr73);

//   gray_test_image.setPixel(rc.c - 3, rc.r - 3, rr);

//   //gray_image.setPixel(rc.c - 3, rc.r - 3, rr);

//   uchar& gg = gline[rc.c - 3];
//   gg = gray;

//?
//   gray_7_line[rc.c - 3] = gray7;
//   gray_5_line[rc.c - 3] = gray5;
//   gray_3_line[rc.c - 3] = gray3;

   //++gray_pixel;
//??   ++rc.c;
  }
//??  ++rc.r;
//??  rc.c = 3;
 }


 qDebug() << "\nbin counts all size = " << bin_counts_5_10_20_all.size();
 qDebug() << "bin counts size = " << bin_counts_5_10_20.size();

 qDebug() << "\nbin counts all = " << bin_counts_5_10_20_all;
 qDebug() << "bin counts = " << bin_counts_5_10_20;

 QMap<pr1, QColor> most_common, most_common_all;

 QVector<QRgb> i8b_color_table, i8b_color_table_all,
   i8b_color_table_all_adj, i8b_color_table_all_sorted;

 i8b_color_table.push_back(cyan);

 u2 most_common_count = 0;

 while(most_common_count < 255)
 {
  if(bin_counts_5_10_20.empty())
    break;
  auto pr = std::max_element
  (
      std::begin(bin_counts_5_10_20), std::end(bin_counts_5_10_20),
      [] (const auto& p1, const auto& p2)
      {
          return p1.second < p2.second;
      }
  );
  most_common[pr->first] = QColor::fromRgb(pr->second.second);
  i8b_color_table.push_back(pr->second.second);
  ++most_common_count;
  bin_counts_5_10_20.erase(pr);
 }

 u2 most_common_count_all = 0;
 while(most_common_count_all < 255)
 {
  if(bin_counts_5_10_20_all.empty())
    break;
  auto pr = std::max_element
  (
      std::begin(bin_counts_5_10_20_all), std::end(bin_counts_5_10_20_all),
      [] (const auto& p1, const auto& p2)
      {
          return p1.second < p2.second;
      }
  );
  most_common_all[pr->first] = QColor::fromRgb(pr->second.second);
  i8b_color_table_all.push_back(pr->second.second);
  ++most_common_count_all;
  bin_counts_5_10_20_all.erase(pr);
 }

 QVector<QPair<u1, QColor>> sort;

 for(QRgb rgb : i8b_color_table_all)
 {
  QColor c = QColor::fromRgb(rgb);
  sort.push_back({c.lightness(), c});
  c.setGreen(c.green() / 2);
  QRgb rgb1 = c.rgb();
  i8b_color_table_all_adj.push_back(rgb1);
 }

 std::sort(sort.begin(), sort.end(), [](auto lhs, auto rhs)
 {
  return lhs.first < rhs.first;
 });

 qDebug() << "sort = " << sort;

 for(auto pr : sort)
 {
  i8b_color_table_all_sorted.push_back(pr.second.rgb());
 }



 QImage i8b = image.convertToFormat(QImage::Format_Indexed8,
   i8b_color_table, Qt::ThresholdDither|Qt::AutoColor);

 QImage i8b_all = image.convertToFormat(QImage::Format_Indexed8,
   i8b_color_table_all_adj, Qt::ThresholdDither|Qt::AutoColor);

 QImage i8b_all_sorted = image.convertToFormat(QImage::Format_Indexed8,
   i8b_color_table_all_sorted, Qt::ThresholdDither|Qt::AutoColor);

 QImage p8b_125 = cyan_8b_125_image.convertToFormat(QImage::Format_Indexed8,
   i8b_color_table, Qt::ThresholdDither|Qt::AutoColor);

 QImage p8b_175 = cyan_8b_175_image.convertToFormat(QImage::Format_Indexed8,
   i8b_color_table, Qt::ThresholdDither|Qt::AutoColor);

 QImage p8b_225 = cyan_8b_225_image.convertToFormat(QImage::Format_Indexed8,
   i8b_color_table, Qt::ThresholdDither|Qt::AutoColor);


// (wh.width, wh.height, QImage::Format_Indexed8);
// i8b.setColorTable(i8b_color_table);

// i8b.convertToFormat()


 qDebug() << "saving " << result_7 << " ...";

 gray_7_image.save(result_7);
 gray_5_image.save(result_5);
 gray_3_image.save(result_3);
 gray_7rgb_image.save(result_7rgb);

 i8b.save(result_8b);
 i8b.save(result_8b_up);

 i8b_all.save(result_8b_all);
 i8b_all.save(result_8b_all_up);

 i8b_all_sorted.save(result_8b_all_sorted);

 p8b_125.save(result_8b_125_cyan);
 p8b_175.save(result_8b_175_cyan);
 p8b_225.save(result_8b_225_cyan);

 qDebug() << "ok";


  //result_7rgb

 QString result_1cd = stat_image.file_path_with_name_addon("-1cd");
 KA::TextIO::copy_binary_file(result_7rgb, result_1cd);

 QString result_d1c = stat_image.file_path_with_name_addon("-dist-1c");
 KA::TextIO::copy_binary_file(result_7, result_d1c);

 KA::TextIO::copy_binary_file(file_path, stat_image.file_path_with_name_addon("-full"));
}
#endif//def USE_XCSD


#ifdef HIDE

QString DHAX_Application_Controller::pixel_local_aggregate_color_distance(QString file_path)
{
 Stat_Test_Image stat_image(file_path);

 static u1 corner_weights[3][3]
 {
  {3, 1, 1},
  {1, 3, 2},
  {1, 2, 3},
 };

 static u1 center_weights[3][3]
 {
  {1, 2, 1},
  {1, 3, 1},
  {1, 3, 1},
 };

 static u2 corner_weights_total = 0;
 if(corner_weights_total == 0)
 {
  for(u1 a = 0; a < 3; ++a)
   for(u1 b = 0; b < 3; ++b)
     corner_weights_total += corner_weights[a][b];
 }

 static u2 center_weights_total = 0;
 if(center_weights_total == 0)
 {
  for(u1 a = 0; a < 3; ++a)
   for(u1 b = 0; b < 3; ++b)
     center_weights_total += center_weights[a][b];
 }

 QImage image(file_path);

 if(image.isNull())
   return {};

 QString result = stat_image.file_path_with_presuffix("gray-7-dist");
 QString result_7rgb = stat_image.file_path_with_presuffix("gray-7rgb-dist");

 wh2 wh = { (u2) image.width(), (u2) image.height()};
 wh -= 6;

 QImage gray_7_image(wh.width, wh.height, QImage::Format_Grayscale8);

 QImage gray_7rgb_image(wh.width, wh.height, QImage::Format_RGB32);

 gray_7_image.fill(0);
 gray_7rgb_image.fill(0);

 rc2 rc {3, 3};

 std::map<pr1, pr4> bin_counts_5_10_20;

 static QRgb cyan = QColor(Qt::cyan).rgb();

 for(u2 r = 0; r < wh.height; ++r)
 {
  QRgb* line = (QRgb*) image.scanLine(rc.r);

  u1* gray_7_line = (u1*) gray_7_image.scanLine(r);
  QRgb* gray_7rgb_line = (QRgb*) gray_7rgb_image.scanLine(r);

  for(u2 c = 0; c < wh.width; ++c)
  {
   QRgb& center_pixel = line[rc.c];

   u2//? total3 = 9, total5 = 9,
     total7 = 0;

   for(s1 r_offset = -3; r_offset <= 3; ++r_offset)
   {
    QRgb* rline = (QRgb*) image.scanLine(rc.r + r_offset);

    for(s1 c_offset = -3; c_offset <= 3; ++c_offset)
    {
     if(r_offset == 0 && c_offset == 0)
       continue;

     u1 r_offset_abs = qAbs(r_offset);
     u1 c_offset_abs = qAbs(c_offset);

     QRgb& pixel = rline[rc.c + c_offset];

     u1 dist = hsv_color_distance(center_pixel, pixel);

     total7 += (u2) dist;

//     if( (r_offset_abs < 3) && (c_offset_abs < 3) )
//       total5 += (u2) dist;

//     if( (r_offset_abs < 2) && (c_offset_abs < 2) )
//        total3 += (u2) dist;

    }
   }

   u1 gray7 = total7 / 48; //, gray5 = total5 / 24, gray3 = total3 / 8;
   //u1 gray73 = qAbs(gray7 - gray3);




//   *gray_pixel = gray;

//   n8 gp = (n8) gray_pixel;

  //? QRgb rr7 = QColor(gray7, gray7, gray7).rgb();

   gray7 = 255 - gray7;
//   gray5 = 255 - gray5;
//   gray3 = 255 - gray3;
//   gray73 = 255 - gray73;

   QColor center_color = QColor::fromRgb(center_pixel);
   QColor gray7rgb = QColor::fromHsv(center_color.hsvHue(), 255 - gray7, gray7);

   if(gray7 > 125)
   {
    SV_Centered_Vector scv = get_sv_centered_vector(center_color).disk_protrude();
    u1 bin = scv.get_5_10_20_bin();
    u1 h = center_color.hsvHue() / 12;

    auto it = bin_counts_5_10_20.find({h, bin});
    if(it == bin_counts_5_10_20.end())
      bin_counts_5_10_20[{h, bin}] = {1, center_color.rgb()};
    else
      ++bin_counts_5_10_20[{h, bin}].first;

//    cyan_8b_125_line[c] = center_pixel;
//    if(gray7 > 175)
//    {
//     cyan_8b_175_line[c] = center_pixel;
//     if(gray7 > 225)
//       cyan_8b_225_line[c] = center_pixel;
//     else
//       cyan_8b_225_line[c] = cyan;
//    }
//    else
//    {
//     cyan_8b_175_line[c] = cyan;
//     cyan_8b_225_line[c] = cyan;
//    }
   }

//   else
//   {
//    cyan_8b_225_line[c] = cyan;
//    cyan_8b_175_line[c] = cyan;
//    cyan_8b_125_line[c] = cyan;
//   }


//
   gray_7_line[c] = gray7;

   gray_7rgb_line[c] = gray7rgb.rgb();

//   gray_7_image.setPixel(rc.c - 3, rc.r - 3, rr7);
//   gray_5_image.setPixel(rc.c - 3, rc.r - 3, rr5);
//   gray_3_image.setPixel(rc.c - 3, rc.r - 3, rr3);


//   gray_73_image.setPixel(rc.c - 3, rc.r - 3, rr73);

//   gray_test_image.setPixel(rc.c - 3, rc.r - 3, rr);

//   //gray_image.setPixel(rc.c - 3, rc.r - 3, rr);

//   uchar& gg = gline[rc.c - 3];
//   gg = gray;

//?
//   gray_7_line[rc.c - 3] = gray7;
//   gray_5_line[rc.c - 3] = gray5;
//   gray_3_line[rc.c - 3] = gray3;

   //++gray_pixel;
   ++rc.c;
  }
  ++rc.r;
  rc.c = 3;
 }

#ifdef HIDE
 QMap<pr1, QColor> most_common;

 QVector<QRgb> i8b_color_table;

 i8b_color_table.push_back(cyan);

 u2 most_common_count = 0;

 while(most_common_count < 255)
 {
  if(bin_counts_5_10_20.empty())
    break;
  auto pr = std::max_element
  (
      std::begin(bin_counts_5_10_20), std::end(bin_counts_5_10_20),
      [] (const auto& p1, const auto& p2)
      {
          return p1.second < p2.second;
      }
  );
  most_common[pr->first] = QColor::fromRgb(pr->second.second);
  i8b_color_table.push_back(pr->second.second);
  ++most_common_count;
  bin_counts_5_10_20.erase(pr);
 }

// QImage i8b = image.convertToFormat(QImage::Format_Indexed8,
//   i8b_color_table, Qt::ThresholdDither|Qt::AutoColor);

// QImage p8b_125 = cyan_8b_125_image.convertToFormat(QImage::Format_Indexed8,
//   i8b_color_table, Qt::ThresholdDither|Qt::AutoColor);
// QImage p8b_175 = cyan_8b_175_image.convertToFormat(QImage::Format_Indexed8,
//   i8b_color_table, Qt::ThresholdDither|Qt::AutoColor);
// QImage p8b_225 = cyan_8b_225_image.convertToFormat(QImage::Format_Indexed8,
//   i8b_color_table, Qt::ThresholdDither|Qt::AutoColor);


// (wh.width, wh.height, QImage::Format_Indexed8);
// i8b.setColorTable(i8b_color_table);

// i8b.convertToFormat()

#endif

 qDebug() << "saving " << result << " ...";

 gray_7_image.save(result);
 gray_7rgb_image.save(result_7rgb);

// i8b.save(result_8b);
// p8b_125.save(result_8b_125_cyan);
// p8b_175.save(result_8b_175_cyan);
// p8b_225.save(result_8b_225_cyan);

 qDebug() << "ok";

 return result;
}

#endif



