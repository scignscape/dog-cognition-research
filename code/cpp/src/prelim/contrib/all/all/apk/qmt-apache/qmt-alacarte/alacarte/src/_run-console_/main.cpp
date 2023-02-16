
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include <QDebug>

#include <QString>
#include <QFileInfo>

#include <QtMath>

#include "global-types.h"
#include "qt-logger.h"

#include "qmt-painter.h"
#include "qmt-paint-context.h"

#include "qmt-render-broker.h"

#include "utils/transform.hpp"



#include <QImage>
#include <QPainter>

#include <QApplication>

#include <QVector2D>

#include <QFileDialog>
#include <QFileInfo>

static constexpr u2 mr_factor = 4;


QString sub_or_parent_sibling_folder(QDir qdir, QString name)
{
 QString result = qdir.absoluteFilePath(name);
 if(qdir.exists(result))
   return result;

 if(qdir.cdUp())
  if(qdir.cdUp())
  {
   // //  same, idea two levels up ...
   result = qdir.filePath(name);
   if(qdir.exists(result))
     return result;
  }

 return {};
}

QMap<QString, u4> parse_min_max(QString text, QString& style)
{
 QMap<QString, u4> result;
 QStringList qsl = text.split(';', QString::SplitBehavior::SkipEmptyParts);

 QMap<QString, r8> latlon;

 r8 llminmax[4];

 for(QString line : qsl)
 {
  QStringList qsl1 = line.split('=');

  QString key = qsl1.value(0).trimmed();
  if(key.isEmpty())
    continue;
  QString value = qsl1.value(1).trimmed();
  if(key == "style")
  {
   if(!value.isEmpty())
     style = value;
   continue;
  }
  if(key.startsWith('l'))
    latlon[key] = value.toDouble();
  else
    result[key] = value.toUInt();
 }

 u4 zoom_min = result.value("zoom_min");
 u4 zoom_max = result.value("zoom_max", zoom_min);

 if(!latlon.isEmpty())
 {
  llminmax[0] = latlon.value("lx_min");
  llminmax[1] = latlon.value("ly_min");
  llminmax[2] = latlon.value("lx_max");
  llminmax[3] = latlon.value("ly_max");
 }

 FloatPoint pmin, pmax;

 coord_t cxmin, cymin, cxmax, cymax;

 i4 txmin, tymin, txmax, tymax;

 if(llminmax[0] && llminmax[1])
 {
  pmin.lon = llminmax[0]; // -73.8986;
  pmin.lat = llminmax[1]; // 40.8862;
  projectMercator(pmin, cxmin, cymin);

  for(u4 zoom = zoom_min; zoom <= zoom_max; ++zoom)
  {
   mercatorToTile(cxmin, cymin, zoom, txmin, tymin);
   result["x_min-%1"_qt.arg(zoom)] = txmin;
   result["y_min-%1"_qt.arg(zoom)] = tymin;
  }
 }

 if(llminmax[2] && llminmax[3])
 {
  pmax.lon = llminmax[2];
  pmax.lat = llminmax[3];
  projectMercator(pmax, cxmax, cymax);
  for(u4 zoom = zoom_min; zoom <= zoom_max; ++zoom)
  {
   mercatorToTile(cxmax, cymax, zoom, txmax, tymax);
   result["x_max-%1"_qt.arg(zoom)] = txmax;
   result["y_max-%1"_qt.arg(zoom)] = tymax;
  }
 }

 return result;
}

int main(int argc, char* argv[])
{
 QApplication app(argc, argv);
 app.processEvents();

 QString test_data_path = QFileDialog::getOpenFileName(nullptr, "Select Data File",
   ALACARTE_FACTORY_FOLDER, "*.carte *.carte.min-max");

 if(test_data_path.isEmpty())
   return 0; //= "/quasihome/nlevisrael/osm/alacarte/monaco/monaco-data.carte";

 if(test_data_path.endsWith(".min-max"))
 {
  test_data_path.chop(8);
 }

 QFileInfo qfi(test_data_path);

 if(!qfi.exists())
 {
  qDebug() << "Can't open " << test_data_path << "; exiting";
  return 0;
 }

 QDir qd = qfi.absoluteDir();

 QString qdn = qd.dirName();

 QString stylesheet_folder_path = sub_or_parent_sibling_folder(qd, "styles");
 if(stylesheet_folder_path.isEmpty())
 {
  qDebug() << "Can't find stylesheet folder; exiting";
  return 0;
 }

// QString stylesheet_path_name = "ttest-default";


 //QString outfile = ALACARTE_QLOG_FOLDER;

 QString image_folder = sub_or_parent_sibling_folder(qd, "%1-test-render"_qt.arg(qdn));
 if(image_folder.isEmpty())
 {
  qDebug() << "Can't find image folder; exiting (" << qd << ")";
  return 0;
 }


// QMT_Render_Broker qrb(test_data_path);
// qrb.set_stylesheet_folder_path(stylesheet_folder_path);

 QString test_data_path_minmax = test_data_path + ".min-max";

 QMap<QString, u4> parse;

 QString stylesheet_path_name = "default";

 QFile minmax_file(test_data_path_minmax);
 if(minmax_file.open(QIODevice::Text | QIODevice::ReadOnly))
 {
  QString minmax = minmax_file.readAll();
  minmax_file.close();
  parse = parse_min_max(minmax, stylesheet_path_name);
 }

 if(parse.size() < 6)
 {
  qDebug() << "Could not properly read the min-max file; exiting";
  return 0;
 }

 u4 zoom_min = parse.value("zoom_min");
 u4 zoom_max = parse.value("zoom_max");

 if((zoom_max - zoom_min) > MAX_ZOOM_DIFF)
 {
  qDebug() << "Too large a zoom differential; exiting";
  return 0;
 }

 QVector<u4> x_min, y_min, x_max, y_max;

 for(u4 zoom = zoom_min; zoom <= zoom_max; ++zoom)
 {
  u4 _x_min = parse.value("x_min-%1"_qt.arg(zoom));
  u4 _x_max = parse.value("x_max-%1"_qt.arg(zoom));

  if(_x_max < _x_min)
    std::swap(_x_max, _x_min);

  if((_x_max - _x_min) > MAX_X_DIFF)
  {
   qDebug() << "Too large a x differential; exiting";
   return 0;
  }

  x_min.push_back(_x_min);
  x_max.push_back(_x_max);

  u4 _y_min = parse.value("y_min-%1"_qt.arg(zoom));
  u4 _y_max = parse.value("y_max-%1"_qt.arg(zoom));

  if(_y_max < _y_min)
    std::swap(_y_max, _y_min);

  if((_y_max - _y_min) > MAX_Y_DIFF)
  {
   qDebug() << "Too large a y differential; exiting";
   return 0;
  }

  y_min.push_back(_y_min);
  y_max.push_back(_y_max);
 }


// for(u4 zoom = zoom_min; zoom <= zoom_max; ++zoom)
//  for(u4 x = x_min; x <= x_max; ++x)
//   for(u4 y = y_min; y <= y_max; ++y)
//   {
//    QMT_Render_Broker qrb(test_data_path);
//    qrb.set_stylesheet_folder_path(stylesheet_folder_path);
//    qrb.set_stylesheet_path_name(stylesheet_path_name);

//    QString image_path = image_folder + "/%1|.png"_qt
//      .arg(qfi.completeBaseName());
//      //.arg(qfi.completeBaseName()).arg(zoom).arg(x).arg(y);
//    qrb.set_out_file_pattern(image_path);

//    qrb.set_zoom_max(zoom);
//    qrb.set_zoom_min(zoom);

//    qrb.set_x_min(x);
//    qrb.set_x_max(x);

//    qrb.set_y_min(y);
//    qrb.set_y_max(y);

//    qrb.generate_png();

//   }


 QMT_Render_Broker qrb(test_data_path);
 qrb.set_stylesheet_folder_path(stylesheet_folder_path);
 qrb.set_stylesheet_path_name(stylesheet_path_name);

 QString image_path = image_folder + "/%1|.png"_qt
   .arg(qfi.completeBaseName());
   //.arg(qfi.completeBaseName()).arg(zoom).arg(x).arg(y);
 qrb.set_out_file_pattern(image_path);

 qrb.set_zoom_min(zoom_min);
 qrb.set_zoom_max(zoom_max);

 qrb.set_x_min(x_min);
 qrb.set_x_max(x_max);

 qrb.set_y_min(y_min);
 qrb.set_y_max(y_max);

 qrb.generate_png();

 return 0;
}




u2 operator ""_mr(n8 value)
{
 return value * mr_factor;
}

void draw_image(QImage& image)
{
 QMT_Painter painter(&image);
 QMT_Paint_Context paint_context(&image);

 QPoint focus = image.rect().center();

//? painter.drawRect(image.rect());
 painter.draw_rect();

 painter.setPen(Qt::darkRed);
 QRect c_rect = paint_context.make_rectangle_from_center(focus, 44_mr, 78_mr);
 painter.drawRect(c_rect);
 paint_context.center_transpose(c_rect);
 painter.drawRect(c_rect);

 painter.setPen(Qt::black);


 QRect d_rect = paint_context.make_rectangle_from_center(focus, 33_mr, 44_mr);

 //painter.drawRect(d_rect);
 painter.drawLine(d_rect.topLeft(), d_rect.bottomLeft());
 painter.drawLine(d_rect.topRight(), d_rect.bottomRight());


 paint_context.center_transpose(d_rect);
// painter.drawRect(d_rect);

 painter.drawLine(d_rect.topLeft(), d_rect.topRight());
 painter.drawLine(d_rect.bottomLeft(), d_rect.bottomRight());

// QRect b_rect = make_rectangle_from_center(focus, 55_mr, 77_mr);

// painter.drawRect(b_square);

// QRect b_rect1 = make_rectangle_from_center(focus, 55_mr, 33_mr);
// painter.drawRect(b_rect1);
// center_transpose(b_rect1);
// painter.drawRect(b_rect1);


 QPoint aline_center = focus - QPoint(66_mr, 0);
 QLine l1 = paint_context.make_vline(aline_center, 44_mr);
 painter.drawLine(l1);

 aline_center = focus + QPoint(66_mr, 0);
 l1 = paint_context.make_vline(aline_center, 44_mr);
 painter.drawLine(l1);

 aline_center = focus - QPoint(0, 66_mr);
 l1 = paint_context.make_hline(aline_center, 44_mr);
 painter.drawLine(l1);

 aline_center = focus + QPoint(0, 66_mr);
 l1 = paint_context.make_hline(aline_center, 44_mr);
 painter.drawLine(l1);

 QRect z_rect = paint_context.make_rectangle_from_center(focus, 92_mr, 55_mr);

 QRect b_square = paint_context.make_square_from_center(focus, 55_mr);

 painter.setPen(Qt::red);
 painter.drawLine(z_rect.topLeft(), b_square.topLeft());
 painter.drawLine(z_rect.bottomLeft(), b_square.bottomLeft());
 painter.drawLine(z_rect.topRight(), b_square.topRight());
 painter.drawLine(z_rect.bottomRight(), b_square.bottomRight());


 painter.setPen(Qt::darkCyan);

//? painter.drawRect(z_rect);
 QLine zline(z_rect.topLeft(), z_rect.bottomLeft());
 painter.drawLine(zline);
 zline.translate(14_mr, 0);
 painter.drawLine(zline);

 zline = QLine(z_rect.topRight(), z_rect.bottomRight());
 painter.drawLine(zline);
 zline.translate(-14_mr, 0);
 painter.drawLine(zline);


 paint_context.center_transpose(z_rect);

 painter.setPen(Qt::red);
 painter.drawLine(z_rect.topLeft(), b_square.topLeft());
 painter.drawLine(z_rect.bottomLeft(), b_square.bottomLeft());
 painter.drawLine(z_rect.topRight(), b_square.topRight());
 painter.drawLine(z_rect.bottomRight(), b_square.bottomRight());

 paint_context.draw_gappy_rectangle(painter, b_square, 11_mr);

 painter.setPen(Qt::darkCyan);



// painter.drawRect(z_rect);
// painter.drawLine(z_rect.topLeft(), z_rect.topRight());
// painter.drawLine(z_rect.bottomLeft(), z_rect.bottomRight());

 zline = QLine(z_rect.topLeft(), z_rect.topRight());
 painter.drawLine(zline);
 zline.translate(0, 14_mr);
 painter.drawLine(zline);

 zline = QLine(z_rect.bottomLeft(), z_rect.bottomRight());
 painter.drawLine(zline);
 zline.translate(0, -14_mr);
 painter.drawLine(zline);

 painter.setPen(Qt::NoPen);
 painter.setBrush(QColor("orange"));
 //QRect goal_rect = make_rectangle_from_side_centers(focus.x() - 90_mr)

 //painter.drawLine(focus.x() - 88_mr, focus.y(), focus.x() - 33_mr, focus.y());
 painter.drawRect(focus.x() - 92_mr, focus.y() - 10_mr, 4_mr, 20_mr);
 painter.drawRect(focus.x() + 92_mr, focus.y() - 10_mr, -4_mr, 20_mr);

 painter.drawRect(focus.x() - 10_mr, focus.y() - 92_mr, 20_mr, 4_mr);
 painter.drawRect(focus.x() - 10_mr, focus.y() + 92_mr, 20_mr, -4_mr);

 painter.setPen(Qt::darkGreen);

 painter.drawLine(focus.x() - 82_mr, focus.y() - 8_mr, focus.x() - 33_mr, focus.y() - 8_mr);
 painter.drawLine(focus.x() - 88_mr, focus.y(), focus.x() - 33_mr, focus.y());

 painter.drawLine(focus.x() - 82_mr, focus.y() + 8_mr, focus.x() - 33_mr, focus.y() + 8_mr);
 painter.drawLine(focus.x() - 82_mr, focus.y() - 8_mr, focus.x() - 82_mr, focus.y() + 8_mr);

 painter.drawLine(focus.x() + 82_mr, focus.y() - 8_mr, focus.x() + 33_mr, focus.y() - 8_mr);
 painter.drawLine(focus.x() + 88_mr, focus.y(), focus.x() + 33_mr, focus.y());
 painter.drawLine(focus.x() + 82_mr, focus.y() + 8_mr, focus.x() + 33_mr, focus.y() + 8_mr);
 painter.drawLine(focus.x() + 82_mr, focus.y() - 8_mr, focus.x() + 82_mr, focus.y() + 8_mr);


 painter.drawLine(focus.x() - 8_mr, focus.y() - 82_mr, focus.x() - 8_mr, focus.y() - 33_mr);
 painter.drawLine(focus.x(), focus.y() - 88_mr, focus.x(), focus.y() - 33_mr);
 painter.drawLine(focus.x() + 8_mr, focus.y() - 82_mr, focus.x() + 8_mr, focus.y() - 33_mr);
 painter.drawLine(focus.x() - 8_mr, focus.y() - 82_mr, focus.x() + 8_mr, focus.y() - 82_mr);

 painter.drawLine(focus.x() - 8_mr, focus.y() + 82_mr, focus.x() - 8_mr, focus.y() + 33_mr);
 painter.drawLine(focus.x(), focus.y() + 88_mr, focus.x(), focus.y() + 33_mr);
 painter.drawLine(focus.x() + 8_mr, focus.y() + 82_mr, focus.x() + 8_mr, focus.y() + 33_mr);
 painter.drawLine(focus.x() - 8_mr, focus.y() + 82_mr, focus.x() + 8_mr, focus.y() + 82_mr);

 painter.setPen(Qt::darkMagenta);

 u2 gap = 13_mr;
 QRect octa = paint_context.make_square_from_center(focus, 22_mr);
 paint_context.draw_gappy_rectangle_as_octagon(painter, octa, gap);

// painter.setPen(Qt::magenta);
// u2 gap1 = 6_mr;
// QRect octa1 = make_square_from_center(focus, 27_mr);
// draw_gappy_rectangle_as_octagon(painter, octa1, gap1);

// painter.setPen(Qt::darkYellow);
 QPen new_pen(Qt::darkYellow);
 new_pen.setWidth(2);
 painter.setPen(new_pen);
 QRect d_square = paint_context.make_square_from_center(focus, 33_mr);
// painter.drawRect(d_square);

 u2 base_radius = 4;

 u2 behind_home = 2_mr;
 u2 pitch_offset = 22_mr - behind_home;


 QPoint home_bl = d_square.bottomLeft();
 QPoint stumps_bl = home_bl + QPoint(-behind_home * M_SQRT1_2, behind_home * M_SQRT1_2);
 QPoint pitch_bl = home_bl + QPoint(pitch_offset * M_SQRT1_2, -pitch_offset * M_SQRT1_2);


 QPoint ref_bl_1 = home_bl + QPoint(28_mr, 0);
 QPoint ref_bl_6 = home_bl + QPoint(0, -28_mr);
 QPoint mid_bl_1 = ref_bl_1 + QPoint(-1_mr / 2, 2_mr);
 QPoint mid_bl_6 = ref_bl_6 + QPoint(-2_mr, -1_mr / 2);
 QPoint mid_bl_2 = mid_bl_1 + QPoint(26_mr, -10_mr);
 QPoint mid_bl_5 = mid_bl_6 + QPoint(10_mr, -26_mr);
 QPoint ref_bl_3 = home_bl + QPoint(55_mr, -38_mr);
 QPoint mid_bl_3 = ref_bl_3 + QPoint(0_mr, 5_mr / 2);
 QPoint ref_bl_4 = home_bl + QPoint(38_mr, -55_mr);
 QPoint mid_bl_4 = ref_bl_4 + QPoint(-5_mr / 2, 0_mr);

 painter.setBrush(Qt::yellow);

 painter.drawLine(stumps_bl + QPoint(5, 5), stumps_bl + QPoint(-5, -5));
 painter.drawLine(pitch_bl + QPoint(5, 5), pitch_bl + QPoint(-5, -5));
// painter.drawLine(pitch_bl, pitch_bl + QPoint(4, 6));

// painter.drawEllipse(home_bl, base_radius, base_radius);
 painter.drawEllipse(mid_bl_1, base_radius, base_radius);
 painter.drawEllipse(mid_bl_2, base_radius, base_radius);
 painter.drawEllipse(mid_bl_3, base_radius, base_radius);
 painter.drawEllipse(mid_bl_4, base_radius, base_radius);
 painter.drawEllipse(mid_bl_5, base_radius, base_radius);
 painter.drawEllipse(mid_bl_6, base_radius, base_radius);

 painter.drawEllipse(mid_bl_4, base_radius - 2, base_radius - 2);
 painter.drawEllipse(mid_bl_5, base_radius - 2, base_radius - 2);
 painter.drawEllipse(mid_bl_6, base_radius - 2, base_radius - 2);


 QPoint home_tr = d_square.topRight();
 QPoint stumps_tr = home_tr + QPoint(behind_home * M_SQRT1_2, -behind_home * M_SQRT1_2);
 QPoint pitch_tr = home_tr + QPoint(-pitch_offset * M_SQRT1_2, pitch_offset * M_SQRT1_2);


 QPoint ref_tr_1 = home_tr + QPoint(-28_mr, 0);
 QPoint ref_tr_6 = home_tr + QPoint(0, 28_mr);
 QPoint mid_tr_1 = ref_tr_1 + QPoint(1_mr / 2, -2_mr);
 QPoint mid_tr_6 = ref_tr_6 + QPoint(2_mr, 1_mr / 2);
 QPoint mid_tr_2 = mid_tr_1 + QPoint(-26_mr, 10_mr);
 QPoint mid_tr_5 = mid_tr_6 + QPoint(-10_mr, 26_mr);
 QPoint ref_tr_3 = home_tr + QPoint(-55_mr, 38_mr);
 QPoint mid_tr_3 = ref_tr_3 + QPoint(0_mr, -5_mr / 2);
 QPoint ref_tr_4 = home_tr + QPoint(-38_mr, 55_mr);
 QPoint mid_tr_4 = ref_tr_4 + QPoint(5_mr / 2, 0_mr);

 painter.setBrush(Qt::red);

 painter.drawLine(stumps_tr + QPoint(5, 5), stumps_tr + QPoint(-5, -5));
 painter.drawLine(pitch_tr + QPoint(5, 5), pitch_tr + QPoint(-5, -5));

// painter.drawEllipse(home_tr, base_radius, base_radius);
 painter.drawEllipse(mid_tr_1, base_radius, base_radius);
 painter.drawEllipse(mid_tr_2, base_radius, base_radius);
 painter.drawEllipse(mid_tr_3, base_radius, base_radius);
 painter.drawEllipse(mid_tr_4, base_radius, base_radius);
 painter.drawEllipse(mid_tr_5, base_radius, base_radius);
 painter.drawEllipse(mid_tr_6, base_radius, base_radius);

 painter.drawEllipse(mid_tr_4, base_radius - 2, base_radius - 2);
 painter.drawEllipse(mid_tr_5, base_radius - 2, base_radius - 2);
 painter.drawEllipse(mid_tr_6, base_radius - 2, base_radius - 2);


// painter.drawText(base_b1_1, "1");
// painter.drawText(base_b1_2, "2");
// painter.drawText(base_b1_3, "3");
// painter.drawText(base_b1_4, "4");
// painter.drawText(base_b1_5, "5");
// painter.drawText(base_b1_6, "6");



 QPoint home_br = d_square.bottomRight();
 QPoint stumps_br = home_br + QPoint(behind_home * M_SQRT1_2, behind_home * M_SQRT1_2);
 QPoint pitch_br = home_br + QPoint(-pitch_offset * M_SQRT1_2, -pitch_offset * M_SQRT1_2);

 QPoint ref_br_6 = home_br + QPoint(-28_mr, 0);
 QPoint ref_br_1 = home_br + QPoint(0, -28_mr);
 QPoint mid_br_6 = ref_br_6 + QPoint(1_mr / 2, 2_mr);
 QPoint mid_br_1 = ref_br_1 + QPoint(2_mr, -1_mr / 2);
 QPoint mid_br_5 = mid_br_6 + QPoint(-26_mr, -10_mr);
 QPoint mid_br_2 = mid_br_1 + QPoint(-10_mr, -26_mr);
 QPoint ref_br_4 = home_br + QPoint(-55_mr, -38_mr);
 QPoint mid_br_4 = ref_br_4 + QPoint(0_mr, 5_mr / 2);
 QPoint ref_br_3 = home_br + QPoint(-38_mr, -55_mr);
 QPoint mid_br_3 = ref_br_3 + QPoint(5_mr / 2, 0_mr);


 new_pen.setColor(Qt::blue);
 painter.setPen(new_pen);
 painter.setBrush(QColor(Qt::cyan));

 painter.drawLine(stumps_br + QPoint(-5, 5), stumps_br + QPoint(5, -5));
 painter.drawLine(pitch_br + QPoint(-5, 5), pitch_br + QPoint(5, -5));
// painter.drawEllipse(home_br, base_radius, base_radius);
 painter.drawEllipse(mid_br_1, base_radius, base_radius);
 painter.drawEllipse(mid_br_2, base_radius, base_radius);
 painter.drawEllipse(mid_br_3, base_radius, base_radius);
 painter.drawEllipse(mid_br_4, base_radius, base_radius);
 painter.drawEllipse(mid_br_5, base_radius, base_radius);
 painter.drawEllipse(mid_br_6, base_radius, base_radius);

 painter.drawEllipse(mid_br_4, base_radius - 2, base_radius - 2);
 painter.drawEllipse(mid_br_5, base_radius - 2, base_radius - 2);
 painter.drawEllipse(mid_br_6, base_radius - 2, base_radius - 2);

//  painter.drawText(mid_br_1, "1");
//  painter.drawText(mid_br_2, "2");
//  painter.drawText(mid_br_3, "3");
//  painter.drawText(mid_br_4, "4");
//  painter.drawText(mid_br_5, "5");
//  painter.drawText(mid_br_6, "6");

  QPoint home_tl = d_square.topLeft();
  QPoint stumps_tl = home_tl + QPoint(-behind_home * M_SQRT1_2, -behind_home * M_SQRT1_2);
  QPoint pitch_tl = home_tl + QPoint(pitch_offset * M_SQRT1_2, pitch_offset * M_SQRT1_2);

  QPoint ref_tl_6 = home_tl + QPoint(28_mr, 0);
  QPoint ref_tl_1 = home_tl + QPoint(0, 28_mr);
  QPoint mid_tl_6 = ref_tl_6 + QPoint(-1_mr / 2, -2_mr);
  QPoint mid_tl_1 = ref_tl_1 + QPoint(-2_mr, 1_mr / 2);
  QPoint mid_tl_5 = mid_tl_6 + QPoint(26_mr, 10_mr);
  QPoint mid_tl_2 = mid_tl_1 + QPoint(10_mr, 26_mr);
  QPoint ref_tl_4 = home_tl + QPoint(55_mr, 38_mr);
  QPoint mid_tl_4 = ref_tl_4 + QPoint(0_mr, -5_mr / 2);
  QPoint ref_tl_3 = home_tl + QPoint(38_mr, 55_mr);
  QPoint mid_tl_3 = ref_tl_3 + QPoint(-5_mr / 2, 0_mr);

// new_pen.setColor(Qt::blue);
// painter.setPen(new_pen);
 painter.setBrush(QColor(Qt::gray));

 painter.drawLine(stumps_tl + QPoint(-5, 5), stumps_tl + QPoint(5, -5));
 painter.drawLine(pitch_tl + QPoint(-5, 5), pitch_tl + QPoint(5, -5));
// painter.drawEllipse(home_tl, base_radius, base_radius);
 painter.drawEllipse(mid_tl_1, base_radius, base_radius);
 painter.drawEllipse(mid_tl_2, base_radius, base_radius);
 painter.drawEllipse(mid_tl_3, base_radius, base_radius);
 painter.drawEllipse(mid_tl_4, base_radius, base_radius);
 painter.drawEllipse(mid_tl_5, base_radius, base_radius);
 painter.drawEllipse(mid_tl_6, base_radius, base_radius);

 painter.drawEllipse(mid_tl_4, base_radius - 2, base_radius - 2);
 painter.drawEllipse(mid_tl_5, base_radius - 2, base_radius - 2);
 painter.drawEllipse(mid_tl_6, base_radius - 2, base_radius - 2);


// QPoint base_br_6 = home_br + QPoint(-28_mr, 0);
// QPoint base_br_1 = home_br + QPoint(0, -28_mr);
// QPoint base_br_5 = base_br_6 + QPoint(-27_mr, -10_mr);
// QPoint base_br_2 = base_br_1 + QPoint(-10_mr, -27_mr);
// QPoint base_br_4 = base_br_5 + QPoint(0, -28_mr);
// QPoint base_br_3 = base_br_2 + QPoint(-28_mr, 0);

// painter.drawText(base_br_1, "1");
// painter.drawText(base_br_2, "2");
// painter.drawText(base_br_3, "3");
// painter.drawText(base_br_4, "4");
// painter.drawText(base_br_5, "5");
// painter.drawText(base_br_6, "6");

// painter.drawEllipse(home_br, base_radius, base_radius);

// painter.drawEllipse(base_br_1, base_radius, base_radius);
//// painter.drawEllipse(base_br_2, base_radius, base_radius);
// painter.drawEllipse(base_br_3, base_radius, base_radius);
// painter.drawEllipse(base_br_4, base_radius, base_radius);
//// painter.drawEllipse(base_br_5, base_radius, base_radius);
// painter.drawEllipse(base_br_6, base_radius, base_radius);



// QPoint base_tr_1 = home_tr + QPoint(-28_mr, 0);
// QPoint base_tr_6 = home_tr + QPoint(0, 28_mr);


// QPoint base_tr_2 = base_tr_1 + QPoint(-27_mr, 10_mr);
// QPoint base_tr_5 = base_tr_6 + QPoint(-10_mr, 27_mr);

// QPoint base_tr_3 = base_tr_2 + QPoint(0, 28_mr);
// QPoint base_tr_4 = base_tr_5 + QPoint(-28_mr, 0);

// new_pen.setColor(Qt::darkYellow);
// painter.setPen(new_pen);
// painter.setBrush(Qt::yellow);

// painter.drawLine(stumps_tr + QPoint(-5, -5), stumps_tr + QPoint(5, 5));

//// painter.drawText(base_tr_1, "1");
//// painter.drawText(base_tr_2, "2");
//// painter.drawText(base_tr_3, "3");
//// painter.drawText(base_tr_4, "4");
//// painter.drawText(base_tr_5, "5");
//// painter.drawText(base_tr_6, "6");

//// painter.drawEllipse(home_tr, base_radius, base_radius);

//// painter.drawEllipse(base_tr_1, base_radius, base_radius);
////// painter.drawEllipse(base_tr_2, base_radius, base_radius);
//// painter.drawEllipse(base_tr_3, base_radius, base_radius);
//// painter.drawEllipse(base_tr_4, base_radius, base_radius);
////// painter.drawEllipse(base_tr_5, base_radius, base_radius);
//// painter.drawEllipse(base_tr_6, base_radius, base_radius);

//// QPoint mid_bl_5_tr_2 ((base_bl_5 + base_tr_2) / 2);
//// mid_bl_5_tr_2 -= QPoint(2_mr, 2_mr);
//// painter.drawEllipse(mid_bl_5_tr_2, base_radius, base_radius);

//// painter.drawEllipse( (base_bl_5 + base_tr_2) / 2, base_radius, base_radius);

//// painter.drawEllipse( (base_bl_2 + base_tr_5) / 2, base_radius, base_radius);

//// QPoint mid_bl_2_tr_5 ((base_bl_2 + base_tr_5) / 2);
//// mid_bl_2_tr_5 -= QPoint(2_mr, 2_mr);
//// painter.drawEllipse(mid_bl_2_tr_5, base_radius, base_radius);



// QPoint home_tl = d_square.topLeft();
// QPoint stumps_tl = home_tl + QPoint(-5_mr * M_SQRT1_2, -5_mr * M_SQRT1_2);

// QPoint base_tl_6 = home_tl + QPoint(28_mr, 0);
// QPoint base_tl_1 = home_tl + QPoint(0, 28_mr);

// QPoint base_tl_5 = base_tl_6 + QPoint(27_mr, 10_mr);
// QPoint base_tl_2 = base_tl_1 + QPoint(10_mr, 27_mr);

// QPoint base_tl_4 = base_tl_5 + QPoint(0, 28_mr);
// QPoint base_tl_3 = base_tl_2 + QPoint(28_mr, 0);

// new_pen.setColor(Qt::blue);
// painter.setPen(new_pen);
// painter.setBrush(Qt::cyan);

// painter.drawLine(stumps_tl + QPoint(5, -5), stumps_tl + QPoint(-5, 5));

// painter.drawEllipse(home_tl, base_radius, base_radius);



// painter.drawText(base_tl_1, "1");
// painter.drawText(base_tl_2, "2");
// painter.drawText(base_tl_3, "3");
// painter.drawText(base_tl_4, "4");
// painter.drawText(base_tl_5, "5");
// painter.drawText(base_tl_6, "6");

// painter.drawEllipse(base_tl_1, base_radius, base_radius);
//// painter.drawEllipse(base_tl_2, base_radius, base_radius);
// painter.drawEllipse(base_tl_3, base_radius, base_radius);
// painter.drawEllipse(base_tl_4, base_radius, base_radius);
//// painter.drawEllipse(base_tl_5, base_radius, base_radius);
// painter.drawEllipse(base_tl_6, base_radius, base_radius);

// QPoint mid_tl_5_br_2 ((base_tl_5 + base_br_2) / 2);
// mid_tl_5_br_2 -= QPoint(2_mr, 2_mr);

// painter.drawEllipse(mid_tl_5_br_2, base_radius, base_radius);
// painter.drawEllipse( (base_tl_2 + base_br_5) / 2, base_radius, base_radius);




// painter.drawLine(home, base_b1_1);
// painter.drawLine(home, base_b1_6);
// painter.drawLine(base_b1_1, base_b1_2);
// painter.drawLine(base_b1_6, base_b1_5);
// painter.drawLine(base_b1_2, base_b1_3);
// painter.drawLine(base_b1_5, base_b1_4);

 painter.setBrush(Qt::NoBrush);


// painter.drawEllipse(mid_bl_2_tr_5, base_radius * 2, base_radius * 2);


 QLine dist_line_hbl1(home_bl, mid_bl_1);
 QVector2D dist_vec_hbl1(dist_line_hbl1.dx(), dist_line_hbl1.dy());
 qDebug() << "dist_vec_hbl1 = " << dist_vec_hbl1 << " l = " << dist_vec_hbl1.length() / mr_factor;

 QLine dist_line_bl12(mid_bl_1, mid_bl_2);
 QVector2D dist_vec_bl12(dist_line_bl12.dx(), dist_line_bl12.dy());
 qDebug() << "dist_vec_bl12 = " << dist_vec_bl12 << " l = " << dist_vec_bl12.length() / mr_factor;


 QLine dist_line_bl23(mid_bl_2, mid_bl_3);
 QVector2D dist_vec_bl23(dist_line_bl23.dx(), dist_line_bl23.dy());
 qDebug() << "dist_vec_bl23 = " << dist_vec_bl23 << " l = " << dist_vec_bl23.length() / mr_factor;

 QLine dist_line_bl34(mid_bl_3, mid_bl_4);
 QVector2D dist_vec_bl34(dist_line_bl34.dx(), dist_line_bl34.dy());
 qDebug() << "dist_vec_bl34 = " << dist_vec_bl34 << " l = " << dist_vec_bl34.length() / mr_factor;

 QLine dist_line_bl45(mid_bl_4, mid_bl_5);
 QVector2D dist_vec_bl45(dist_line_bl45.dx(), dist_line_bl45.dy());
 qDebug() << "dist_vec_bl45 = " << dist_vec_bl45 << " l = " << dist_vec_bl45.length() / mr_factor;

 QLine dist_line_bl56(mid_bl_5, mid_bl_6);
 QVector2D dist_vec_bl56(dist_line_bl56.dx(), dist_line_bl56.dy());
 qDebug() << "dist_vec_bl56 = " << dist_vec_bl56 << " l = " << dist_vec_bl56.length() / mr_factor;

 QLine dist_line_bl2_hbr(mid_bl_2, home_br);
 QVector2D dist_vec_bl2_hbr(dist_line_bl2_hbr.dx(), dist_line_bl2_hbr.dy());
 qDebug() << "dist_vec_bl2_hbr = " << dist_vec_bl2_hbr << " l = " << dist_vec_bl2_hbr.length() / mr_factor;




// QLine dist_line(home_br, mid_bl_2_tr_5);
// QVector2D dist_vec(dist_line.dx(), dist_line.dy());
// qDebug() << "dist_vec = " << dist_vec << " l = " << dist_vec.length() / mr_factor;

// QLine dist_line1(base_bl_1, mid_bl_2_tr_5);
// QVector2D dist_vec1(dist_line1.dx(), dist_line1.dy());
// qDebug() << "dist_vec1 = " << dist_vec1 << " l = " << dist_vec1.length() / mr_factor;

// QLine dist_line2(mid_bl_2_tr_5, mid_bl_3);
// QVector2D dist_vec2(dist_line2.dx(), dist_line2.dy());
// qDebug() << "dist_vec2 = " << dist_vec2 << " l = " << dist_vec2.length() / mr_factor;

// QLine dist_line3(mid_bl_3, base_bl_4);
// QVector2D dist_vec3(dist_line3.dx(), dist_line3.dy());
// qDebug() << "dist_vec3 = " << dist_vec3 << " l = " << dist_vec3.length() / mr_factor;


// QPoint mid34 = (base_bl_3 + base_tl_4) / 2;
// QPoint mid43 = (base_bl_4 + base_br_3) / 2;

// painter.drawEllipse(mid34, base_radius * 2, base_radius * 2);
// painter.drawEllipse(mid43, base_radius * 2, base_radius * 2);


// QLine dist_line23(base_bl_2, mid34);
// QVector2D dist_vec23(dist_line23.dx(), dist_line23.dy());
// qDebug() << "dist_vec23 = " << dist_vec23 << " l = " << dist_vec23.length() / mr_factor;

// QLine dist_line3443(mid34, mid43);
// QVector2D dist_vec3443(dist_line3443.dx(), dist_line3443.dy());
// qDebug() << "dist_vec3443 = " << dist_vec3443 << " l = " << dist_vec3443.length() / mr_factor;

// QLine dist_line34(mid34, base_bl_4);
// QVector2D dist_vec34(dist_line34.dx(), dist_line34.dy());
// qDebug() << "dist_vec34 = " << dist_vec34 << " l = " << dist_vec34.length() / mr_factor;



 //u2 dist = home_bl

}


int main1(int argc, char* argv[])
{
 QGuiApplication app(argc, argv);


 QString image_path = ALACARTE_QLOG_FOLDER "/img.png"_qt;

 QFileInfo qfi(image_path);

 qDebug() << "image = " << qfi.absoluteFilePath();

 QImage image(188_mr, 188_mr, QImage::Format_RGB32);


 image.fill(Qt::white);

 draw_image(image);

 image.save(qfi.absoluteFilePath());

 return 0;

}
