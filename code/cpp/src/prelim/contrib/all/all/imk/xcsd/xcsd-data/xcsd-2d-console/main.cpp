
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "xcsd-2d/mat2d.h"

#include "xcsd-2d/mat2d.templates.h"

#include "xcsd-1d/vec1d.h"

#include "xcsd-2d/xcsd-image.h"

#include "xcsd-2d/xcsd-tierbox.h"

#include <QPixmap>
#include <QPainter>

#include <QGuiApplication>


USING_XCNS(XCSD)

int main6(int argc , char **argv)
{
 QGuiApplication app(argc, argv);

 XCSD_Image_Geometry xcsg;
 xcsg.set_total_size(27 * 9, 27 * 5);

 xcsg.init_tier_counts(XCSD_Image_Geometry::TierGrid_Preferances::Minimize_Outer_Tiers);

 xcsg.draw_tier_summary(QString(ROOT_FOLDER "/../test/t%1x%2.png")
     .arg(xcsg.total_size().width).arg(xcsg.total_size().height),
   QString(ROOT_FOLDER "/../test/t%1x%2-seq.png")
     .arg(xcsg.total_size().width).arg(xcsg.total_size().height),
                        3.3, 8);
}

int main(int argc , char **argv)
{
 QGuiApplication app(argc, argv);

// XCSD_Image_Geometry xcsg;
//xcsg.set_total_size(54, 108);
// xcsg.set_total_size(160, 90);

 // landscape
 // xcsg.set_total_size(304, 194);
 // xcsg.set_total_size(304 + 54, 194 + 54);
 // xcsg.set_total_size(284, 194);
 // xcsg.set_total_size(284 + 54, 194 + 54);
 // xcsg.set_total_size(304, 174);
 // xcsg.set_total_size(304 + 54, 174 + 54);
 // xcsg.set_total_size(284, 174);

 // portrait
 // xcsg.set_total_size(194, 304);
 // xcsg.set_total_size(194 + 54, 304 + 54);
 // xcsg.set_total_size(194, 284);
 // xcsg.set_total_size(194 + 54, 284 + 54);
 // xcsg.set_total_size(174, 304);
 // xcsg.set_total_size(174 + 54, 304 + 54);
 // xcsg.set_total_size(174, 284);

 // square
 // xcsg.set_total_size(194, 194);
 // xcsg.set_total_size(284, 284);
 // xcsg.set_total_size(304, 304);

 // xcsd.load_image(ROOT_FOLDER "/../test/angle7.png");

// XCSD_Image xcsd1;

// xcsd1.load_image(ROOT_FOLDER "/../test/angle7.png");
// QImage src = xcsd1.image();
// QImage copy = src.copy(0, 0, src.width() - 27 * 3,
//                        src.height() - 27 * 2);
// copy.save(ROOT_FOLDER "/../test/angle.png");

 // return 0;


 XCSD_Image xcsd;

// xcsd.load_image(ROOT_FOLDER "/../test/anglez.png");
//
 xcsd.load_image(ROOT_FOLDER "/../ukraine/copy/sub1.png");
// xcsd.load_image(ROOT_FOLDER "/../ukraine/copy/anglez.png");


// xcsd.load_image("/home/nlevisrael/gits/ctg-temp/pics/ukraine/sub-buzz-742-1646084436-1.webp");

// xcsd.image().save("/home/nlevisrael/gits/ctg-temp/pics/ukraine/sub.png");

// xcsd.load_image("/home/nlevisrael/gits/ctg-temp/pics/ukraine/sub1.png");

 //return 0;

 //xcsd.load_image(ROOT_FOLDER "/../test/ft12.png");

// xcsd.load_image(ROOT_FOLDER "/../test/t1-36x36b.png");
// xcsd.load_image(ROOT_FOLDER "/../test/t1-27x27.png");
// xcsd.load_image(ROOT_FOLDER "/../pics/angle.grid.png");
 //xcsd.load_image(ROOT_FOLDER "/../pi/t1-30x30.png");
 xcsd.init_geometry();
 XCSD_Image_Geometry& xcsg = xcsd.geometry();

 xcsg.init_tier_counts(XCSD_Image_Geometry::TierGrid_Preferances::Minimize_Outer_Tiers);

// xcsg.draw_tier_summary(QString(ROOT_FOLDER "/../test/t%1x%2.png")
//     .arg(xcsg.total_size().width).arg(xcsg.total_size().height),
//   QString(ROOT_FOLDER "/../test/t%1x%2-seq.png")
//     .arg(xcsg.total_size().width).arg(xcsg.total_size().height),
//                        3.3, 8);

//?
 xcsg.init_outer_ring_positions();

 xcsd.init_pixel_data(ROOT_FOLDER "/../test/ukr");

 xcsd.init_tierboxes();

 xcsd.draw_tierboxes_to_folder(ROOT_FOLDER "/../test/ukr");

// xcsd.save_full_tier_image(ROOT_FOLDER "/../test/ft13a.png",
//   ROOT_FOLDER "/../test/ti1");

 xcsd.save_full_tier_image(ROOT_FOLDER "/../test/ukr/u/t1.png",
   XCSD_Image::Save_Mode::Save_QRgb,
   ROOT_FOLDER "/../test/ukr/u1");



#ifdef HIDE
 xcsd.save_full_tier_image(ROOT_FOLDER "/../test/ft13a.png",
   {}, //ROOT_FOLDER "/../test/tk1",
   [](QImage& ti, XCSD_Image_Geometry::Grid_TierBox& gtb,
      XCSD_Image_Geometry::Iteration_Environment ienv,
      u4 data_index, n8* data_start ,//pr2s mch,
      const XCSD_Image_Geometry::MCH_Info& mchi,
      QString info_folder, u1 tierbox_w)
 {

 },
 [](QImage& ti, s1 index)
 {
//  bool secondary;
//  if((secondary = (index < 0)))
//    index = 1 + index;

//  qDebug() << "index = " << index;
//  qDebug() << "s = " << secondary;


//  if(index == 2 || index == 11)
//  {
//   QPainter painter(&ti);
//   painter.setBrush(Qt::darkRed);
//   painter.setPen(Qt::white);
//   painter.drawRect(ti.rect());
//  }
//  else if(index == 0)
//  {
//   QPainter painter(&ti);
//   painter.setBrush(Qt::darkMagenta);
//   painter.setPen(QPen(Qt::white, 2));
//   if(secondary)
//     painter.drawRect(1, 1, ti.width() - 1, ti.height() - 1);
//   else
//   {
//    painter.drawRect(6, 1, ti.width() - 6, ti.height() - 1);
//    painter.setBrush(QBrush(Qt::magenta, Qt::BrushStyle::Dense1Pattern));
//    painter.setPen(Qt::white);
//    painter.drawRect(0, 0, 5, 9);
//   }
//  }
 }
 );
#endif
 return 0;
}

#ifdef HIDE
 if(0)
 xcsd.save_full_tier_image(ROOT_FOLDER "/../test/ft2.png",
   {}, //ROOT_FOLDER "/../test/tk1",
   [](QImage& ti, XCSD_Image_Geometry::Grid_TierBox& gtb,
      XCSD_Image_Geometry::Iteration_Environment ienv,
      u4 data_index, n8* data_start ,//pr2s mch,
      const XCSD_Image_Geometry::MCH_Info& mchi,
      QString info_folder, u1 tierbox_w)
 {
  QPainter painter(&ti);

  QFont font = painter.font();
  font.setPointSize(7);
  painter.setFont(font);

  u1 dir = mchi.get_clock_index_to_direction();

  QColor hcolor(200, 0, 50);
  QColor vcolor(230, 200, 50);
  QColor dcolor(170, 200, 0);

  QColor hcolortr(200, 0, 50, 100);
  QColor vcolortr(230, 200, 50, 100);

  QPoint tl = ti.rect().topLeft();
  QPoint tr = ti.rect().topRight();
  QPoint bl = ti.rect().bottomLeft();
  QPoint br = ti.rect().bottomRight();
  QPoint tc = (tl + tr) / 2;
  QPoint bc = (bl + br) / 2;
  QPoint lc = (tl + bl) / 2;
  QPoint rc = (tr + br) / 2;
  QPoint cc = ti.rect().center();


  switch (mchi.get_clock_index_to_direction())
  {
  case 1:
   painter.setPen(hcolor);
   painter.drawLine(lc, rc - QPoint{4,0});
   painter.setPen(hcolortr);
   painter.drawLine(lc, rc);
   break;

  case 5:
   painter.setPen(hcolor);
   painter.drawLine(lc + QPoint{4,0}, rc);
   painter.setPen(hcolortr);
   painter.drawLine(lc, rc);
   break;

  case 2:
   painter.setPen(QPen(dcolor,1));
   painter.drawLine(tl, br);
   painter.setPen(hcolor);
   painter.drawLine(cc - QPoint{3,0},lc);
   painter.setPen(vcolor);
   painter.drawLine(cc - QPoint{0,3},tc);
   break;

  case 4:
   painter.setPen(QPen(dcolor,1));
   painter.drawLine(bl, tr);
   painter.setPen(hcolor);
   painter.drawLine(cc + QPoint{3,0},rc);
   painter.setPen(vcolor);
   painter.drawLine(cc - QPoint{0,3},tc);
   break;

  case 6:
   painter.setPen(QPen(dcolor,1));
   painter.drawLine(tl, br);
   painter.setPen(hcolor);
   painter.drawLine(cc + QPoint{3,0},rc);
   painter.setPen(vcolor);
   painter.drawLine(cc + QPoint{0,3},bc);
   break;

  case 3:
   painter.setPen(vcolor);
   painter.drawLine(tc, bc - QPoint{0,4});
   painter.setPen(vcolortr);
   painter.drawLine(tc, bc);
   break;

  case 7:
   painter.setPen(vcolor);
   painter.drawLine(tc + QPoint{0,4}, bc);
   painter.setPen(vcolortr);
   painter.drawLine(tc, bc);
   break;

  case 8:
   painter.setPen(QPen(dcolor,1));
   painter.drawLine(bl, tr);
   painter.setPen(hcolor);
   painter.drawLine(cc - QPoint{3,0},lc);
   painter.setPen(vcolor);
   painter.drawLine(cc + QPoint{0,3},bc);
   break;

  case 0:
   painter.setPen(Qt::yellow);
   painter.drawEllipse(ti.rect().center(), 4, 4);
   break;

  default: break;

  }


  painter.setPen(QColor(100,220,220));
  //painter.drawText(2, 25, QString("%1").arg(dir));
  painter.drawText(4, 25, QString("%1,%2").arg(gtb.loc.r()).arg(gtb.loc.c()));
 });

 if(0)
 xcsd.save_full_tier_image(ROOT_FOLDER "/../test/ft3.png",
   {}, //ROOT_FOLDER "/../test/tk1",
   [&xcsg](QImage& ti, XCSD_Image_Geometry::Grid_TierBox& gtb,
      XCSD_Image_Geometry::Iteration_Environment ienv,
      u4 data_index, n8* data_start ,  //pr2s mch,
      const XCSD_Image_Geometry::MCH_Info& mchi,
      QString info_folder, u1 tierbox_w)
 {
  QPainter painter(&ti);

  pr2s mch = gtb.loc.get_mch_code();
  u2 dist = mch.abs().greater();
  u2 half_side = xcsg.full_tier_counts().greater() / 2;

  r8 prop = (r8) dist / half_side;

  u1 coffset = prop * 50;

  qDebug() << "half = " << half_side << "prop = " << prop << " dist = " << dist << " coffset = " << coffset;

  painter.setBrush(QColor(100, dist * 20, dist * 20, 100));
  //painter.drawText(2, 25, QString("%1").arg(dir));
  painter.drawRect(ti.rect());

  painter.setPen(QColor(100,220,220));
  painter.drawText(2, 25, QString("%1").arg(dist));

 });


// if(0)
 // // //


if(0)
 xcsd.save_full_tier_image({}, // ROOT_FOLDER "/../test/ft9.png",
   {}, //ROOT_FOLDER "/../test/tk1",
   [&xcsg, &xcsd](QImage& ti, XCSD_Image_Geometry::Grid_TierBox& gtb,
      XCSD_Image_Geometry::Iteration_Environment ienv,
      u4 data_index, n8* data_start ,  //pr2s mch,
      const XCSD_Image_Geometry::MCH_Info& mchi,
      QString info_folder, u1 tierbox_w)
 {
  if(gtb.loc.rc() != rc2s{16,25})
    return;

  std::map<s1, std::pair<u2, std::vector<n8>>> sdi;

  xcsd.data_tierbox_to_sdi_pixel_map(mchi.full_tier_index, sdi);

  u1 mag = 2;
  u1 mult = 50;

  mult *= mag;

  QImage si(tierbox_w * mult, tierbox_w * mult, QImage::Format_ARGB32);
  QPainter painter(&si);

  for(auto const& [ab_s1, thr_vec]: sdi)
  {
   ab1 ab = {(u1)((u1)ab_s1 / 10), (u1)((u1)ab_s1 % 10)};
   ab = ab.double_minus(1);

//   // // rc here is 0 - 3
   rc1 arc = {(u1)(ab.a / 3), (u1)(ab.a % 3)};
   rc1 brc = {(u1)(ab.b / 3), (u1)(ab.b % 3)};


//   u2 thro_1 =  3 * brc.r + brc.c;
//   u2 thro_2 =  9 * thro_1;

//   u2 thro_3 =  3 * arc.r + arc.c;
//   u2 thro_4 =  81 * thro_3;

//   u2 thro = thro_2 + thro_4;
    u2 thro = XCSD_Image_Geometry::sdi_index_to_ground_offset(ab_s1);

//   qDebug() << "thro = " << thro << " thr = " << thr_vec.first;



   u1 tl_scan_row = arc.r * 9 + brc.r * 3;
   u1 tl_scan_column = arc.c * 9 + brc.c * 3;

   u1 vi = 0; // vector index
   for(u1 y = 0; y < 3; ++y)
   {
    //QRgb* img_pixels = (QRgb*) target.scanLine(tl_scan_row + y);
    //img_pixels += tl_scan_column;
    for(u1 x = 0; x < 3; ++x)
    {
     go_xy1 coords{(u1)(tl_scan_column + x), (u1)(tl_scan_row + y)};

     u2 thro1 = XCSD_Image_Geometry::ground_offset_coords_to_ground_offset(coords);

//     qDebug() << "thro1 = " << thro1; // << " thr = " << thr_vec.first;

//     go_xy1 coords_off = coords.minus({1,1});

//     qDebug() << "coords = " << coords;

//     n8 pixel = thr_vec.second[vi];

     n8 pixel = *(data_start + thro1); //xcsd.get_pixel_at_ground_index(data_index);


     QColor clr = xcsd.pixel_number_to_qcolor(pixel);

     painter.setPen(Qt::NoPen);

     xy2 local {(u2)(coords.go_x * mult), (u2)(coords.go_y * mult)};


     if(coords.go_x % 3 == 1 && coords.go_y % 3 == 1)
     {
      painter.setBrush(Qt::lightGray);
      painter.drawRect(local.x, local.y, mult, mult) ;

      painter.setBrush(Qt::white);
      painter.drawRect(local.x + 2 * mag,
        local.y + 20 * mag, mult - 4 * mag, mult - 22 * mag);
     }
     else
     {
      painter.setBrush(Qt::white);
      painter.drawRect(local.x, local.y, mult, mult) ;
     }

//     painter.drawRect(local.x + 1 * mag,
//       local.y + 1 * mag, mult - 1 * mag, mult - 1 * mag) ;

     painter.setBrush(clr);

     painter.drawRect(local.x + 4 * mag,
       local.y + 21 * mag, mult - 8 * mag, mult - 29 * mag);

     painter.setPen(QColor(40,120,70));

     QFont font = painter.font();
     font.setPointSize(5 * mag);
     painter.setFont(font);

     painter.drawText(local.x + 3 * mag, local.y + 8 * mag,
       QString("%1").arg(coords.go_x));

     painter.drawText(local.x + 3 * mag, local.y + 17 * mag,
       QString("%1").arg(coords.go_y));

     font.setPointSize(6 * mag);
     painter.setFont(font);

     painter.setPen(QColor(140,0,30));
     painter.drawText(local.x + 15 * mag, local.y + 10 * mag,
       QString("%1")
         .arg(clr.red()));

     painter.setPen(QColor(0,140,30));
     painter.drawText(local.x + 31 * mag, local.y + 10 * mag,
       QString("%1")
         .arg(clr.green()));

     painter.setPen(QColor(30,0,140));
     painter.drawText(local.x + 15 * mag, local.y + 19 * mag,
       QString("%1")
         .arg(clr.blue()));

     painter.setPen(QColor(30,30,14));
     painter.drawText(local.x + 31 * mag, local.y + 19 * mag,
       QString("%1")
         .arg(255 - clr.alpha()));


     font.setPointSize(5 * mag);
     painter.setFont(font);

     painter.setPen(Qt::NoPen);
     painter.setBrush(QColor(255,255,255,200));
     painter.drawRect(local.x + 26 * mag, local.y + 19 * mag, 20 * mag, 9 * mag);
     painter.drawRect(local.x + 4 * mag, local.y + mult - 15 * mag, 13 * mag, 8 * mag);

     painter.setBrush(QColor(225,225,255,255));
     painter.drawEllipse(local.x + 22 * mag, local.y + mult - 18 * mag, 19 * mag, 7 * mag);

     painter.setPen(Qt::black);
     painter.drawText(local.x + 27 * mag, local.y + 26 * mag, "rgba");

     font.setPointSize(4);
     painter.drawText(local.x + 23 * mag, local.y + mult - 11 * mag,
       QString("+%1").arg(thr_vec.first + vi));

     font.setPointSize(5);
     painter.setPen(Qt::darkYellow);
     painter.drawText(local.x + 5 * mag, local.y + mult - 9 * mag, "hsv");

     painter.setPen(Qt::darkYellow);
     painter.drawText(local.x + 4 * mag, local.y + mult - 3 * mag,
       QString("%1 %2 %3")
         .arg(clr.hue()).arg(clr.saturation()).arg(clr.value()));

     //clr.hslHue()

     if(coords.go_x % 9 == 0)
     {
      if(coords.go_x > 0)
      {
       painter.setPen(QPen(Qt::red, 3));
       painter.drawLine(local.x, local.y, local.x, local.y + mult);
      }
     }
     else if(coords.go_x % 3 == 0)
     {
      painter.setPen(QPen(Qt::darkMagenta, 2 * mag));
      painter.drawLine(local.x, local.y, local.x, local.y + mult);
     }
     else
     {
      painter.setPen(QPen(Qt::darkBlue, 1 * mag));
      painter.drawLine(local.x, local.y, local.x, local.y + mult);
     }

     if(coords.go_y % 9 == 0)
     {
      if(coords.go_y > 0)
      {
       painter.setPen(QPen(Qt::red, 3));
       painter.drawLine(local.x, local.y, local.x + mult, local.y);
      }
     }
     else if(coords.go_y % 3 == 0)
     {
      painter.setPen(QPen(Qt::darkMagenta, 2 * mag));
      painter.drawLine(local.x, local.y, local.x + mult, local.y);
     }
     else
     {
      painter.setPen(QPen(Qt::darkBlue, 1 * mag));
      painter.drawLine(local.x, local.y, local.x + mult, local.y);
     }


//     else if(coords.go_y % 9 == 0)
//     {
//      painter.setPen(QPen(Qt::red, 3));
//      painter.drawLine(0, 0, 0, mult);
//     }

//     else if(x == 0)
//     {
//      painter.setPen(QPen(Qt::darkBlue, 1));
//      painter.drawLine(0, 0, mult, 0);
//     }
//     else if(y == 0)
//     {
//      painter.setPen(QPen(Qt::darkBlue, 1));
//      painter.drawLine(0, 0, 0, mult);
//     }

     ++vi;
    }
   }
  }
  si.save(ROOT_FOLDER "/../test/diagram1.png");
  return;
 });

 if(0)
 xcsd.save_full_tier_image({}, // ROOT_FOLDER "/../test/ft9.png",
   {}, //ROOT_FOLDER "/../test/tk1",
   [&xcsg, &xcsd](QImage& ti, XCSD_Image_Geometry::Grid_TierBox& gtb,
      XCSD_Image_Geometry::Iteration_Environment ienv,
      u4 data_index, n8* data_start ,  //pr2s mch,
      const XCSD_Image_Geometry::MCH_Info& mchi,
      QString info_folder, u1 tierbox_w)
 {
  if(gtb.loc.rc() != rc2s{16,25})
    return;

  std::map<s1, std::pair<u2, std::vector<n8>>> sdi;

  xcsd.data_tierbox_to_sdi_pixel_map(mchi.full_tier_index, sdi);

  u1 mag = 2;
  u1 mult = 50;

  mult *= mag;

  QImage si(tierbox_w * mult, tierbox_w * mult, QImage::Format_ARGB32);
  QPainter painter(&si);


  pr2s mch = gtb.loc.get_mch_code();
  u2 dist = mch.abs().make_descending().inner_difference();

  for(u1 y = 0; y < 27; ++y)
  {
   for(u1 x = 0; x < 27; ++x)
   {

    //s2 thro1 = XCSD_Image_Geometry::ground_offset_to_sdi3(index);
    //go_xy1 coords = XCSD_Image_Geometry::ground_offset_to_ground_offset_coords(index);

    go_xy1 coords {x, y};
    qDebug() << "coords = " << coords;

//    ab1 ab = XCSD_Image_Geometry::ground_offset_coords_to_sdi_coords(coords);

    u2 index = XCSD_Image_Geometry::ground_offset_coords_to_ground_offset(coords);

    n8 pixel = *(data_start + index); //xcsd.get_pixel_at_ground_index(data_index);

//    u1 tl_scan_row = y - y % 3;
//    u1 tl_scan_column = x - x % 3;
//    u1 vi = 3 * (y % 3) + (x % 3);  // vector index

    QColor clr = xcsd.pixel_number_to_qcolor(pixel);

    painter.setPen(Qt::NoPen);

    xy2 local {(u2)(coords.go_x * mult), (u2)(coords.go_y * mult)};


    if(coords.go_x % 3 == 1 && coords.go_y % 3 == 1)
    {
     painter.setBrush(Qt::lightGray);
     painter.drawRect(local.x, local.y, mult, mult) ;

     painter.setBrush(Qt::white);
     painter.drawRect(local.x + 2 * mag,
       local.y + 20 * mag, mult - 4 * mag, mult - 22 * mag);
    }
    else
    {
     painter.setBrush(Qt::white);
     painter.drawRect(local.x, local.y, mult, mult) ;
    }

    //     painter.drawRect(local.x + 1 * mag,
 //       local.y + 1 * mag, mult - 1 * mag, mult - 1 * mag) ;

    painter.setBrush(clr);

    painter.drawRect(local.x + 4 * mag,
      local.y + 21 * mag, mult - 8 * mag, mult - 29 * mag);

    painter.setPen(QColor(40,120,70));

    QFont font = painter.font();
    font.setPointSize(5 * mag);
    painter.setFont(font);

    painter.drawText(local.x + 3 * mag, local.y + 8 * mag,
      QString("%1").arg(coords.go_x));
    painter.drawText(local.x + 3 * mag, local.y + 17 * mag,
      QString("%1").arg(coords.go_y));

    font.setPointSize(6 * mag);
    painter.setFont(font);

    painter.setPen(QColor(140,0,30));
    painter.drawText(local.x + 15 * mag, local.y + 10 * mag,
      QString("%1")
        .arg(clr.red()));

    painter.setPen(QColor(0,140,30));
    painter.drawText(local.x + 31 * mag, local.y + 10 * mag,
      QString("%1")
        .arg(clr.green()));

    painter.setPen(QColor(30,0,140));
    painter.drawText(local.x + 15 * mag, local.y + 19 * mag,
      QString("%1")
        .arg(clr.blue()));

    painter.setPen(QColor(30,30,14));
    painter.drawText(local.x + 31 * mag, local.y + 19 * mag,
      QString("%1")
        .arg(255 - clr.alpha()));


    font.setPointSize(5 * mag);
    painter.setFont(font);

    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(255,255,255,200));
    painter.drawRect(local.x + 26 * mag, local.y + 19 * mag, 20 * mag, 9 * mag);
    painter.drawRect(local.x + 4 * mag, local.y + mult - 15 * mag, 13 * mag, 8 * mag);

    painter.setBrush(QColor(225,225,255,255));
    painter.drawEllipse(local.x + 22 * mag, local.y + mult - 18 * mag, 19 * mag, 7 * mag);

    painter.setPen(Qt::black);
    painter.drawText(local.x + 27 * mag, local.y + 26 * mag, "rgba");

    font.setPointSize(4);
    painter.drawText(local.x + 23 * mag, local.y + mult - 11 * mag,
      QString("+%1").arg(index));

    font.setPointSize(5);
    painter.setPen(Qt::darkYellow);
    painter.drawText(local.x + 5 * mag, local.y + mult - 9 * mag, "hsv");

    painter.setPen(Qt::darkYellow);
    painter.drawText(local.x + 4 * mag, local.y + mult - 3 * mag,
      QString("%1 %2 %3")
        .arg(clr.hue()).arg(clr.saturation()).arg(clr.value()));

      //clr.hslHue()

    if(coords.go_x % 9 == 0)
    {
     if(coords.go_x > 0)
     {
      painter.setPen(QPen(Qt::red, 3));
      painter.drawLine(local.x, local.y, local.x, local.y + mult);
     }
    }
    else if(coords.go_x % 3 == 0)
    {
     painter.setPen(QPen(Qt::darkMagenta, 2 * mag));
     painter.drawLine(local.x, local.y, local.x, local.y + mult);
    }
    else
    {
     painter.setPen(QPen(Qt::darkBlue, 1 * mag));
     painter.drawLine(local.x, local.y, local.x, local.y + mult);
    }

    if(coords.go_y % 9 == 0)
    {
     if(coords.go_y > 0)
     {
      painter.setPen(QPen(Qt::red, 3));
      painter.drawLine(local.x, local.y, local.x + mult, local.y);
     }
    }
    else if(coords.go_y % 3 == 0)
    {
     painter.setPen(QPen(Qt::darkMagenta, 2 * mag));
     painter.drawLine(local.x, local.y, local.x + mult, local.y);
    }
    else
    {
     painter.setPen(QPen(Qt::darkBlue, 1 * mag));
     painter.drawLine(local.x, local.y, local.x + mult, local.y);
    }

   }
  }
  si.save(ROOT_FOLDER "/../test/diagram2.png");
 });

 if(0)
 xcsd.save_full_tier_image({}, // ROOT_FOLDER "/../test/ft9.png",
   {}, //ROOT_FOLDER "/../test/tk1",
   [&xcsg, &xcsd](QImage& ti, XCSD_Image_Geometry::Grid_TierBox& gtb,
      XCSD_Image_Geometry::Iteration_Environment ienv,
      u4 data_index, n8* data_start ,  //pr2s mch,
      const XCSD_Image_Geometry::MCH_Info& mchi,
      QString info_folder, u1 tierbox_w)
 {
  if(gtb.loc.rc() != rc2s{16,25})
    return;

  std::map<s1, std::pair<u2, std::vector<n8>>> sdi;

  xcsd.data_tierbox_to_sdi_pixel_map(mchi.full_tier_index, sdi);

  u1 mag = 2;
  u1 mult = 50;

  mult *= mag;

  QImage si(tierbox_w * mult, tierbox_w * mult, QImage::Format_ARGB32);
  QPainter painter(&si);

  pr2s mch = gtb.loc.get_mch_code();
  u2 dist = mch.abs().make_descending().inner_difference();

//  for(u1 y = 0; y < 27; ++y)
//  {
//   for(u1 x = 0; x < 27; ++x)
//   {

  for(u2 index = 0; index < 729; ++index)
  {
    //s2 thro1 = XCSD_Image_Geometry::ground_offset_to_sdi3(index);

   go_xy1 coords = XCSD_Image_Geometry::ground_offset_to_ground_offset_coords(index);

   qDebug() << "coords = " << coords;

   ab1 ab = XCSD_Image_Geometry::ground_offset_coords_to_sdi_coords(coords);

   u1 x = coords.go_x;
   u1 y = coords.go_y;

    //u2 index = XCSD_Image_Geometry::ground_offset_coords_to_ground_offset(coords);

   n8 pixel = *(data_start + index); //xcsd.get_pixel_at_ground_index(data_index);

   u1 tl_scan_row = y - y % 3;
   u1 tl_scan_column = x - x % 3;

   u1 vi = 3 * (y % 3) + (x % 3);  // vector index

   QColor clr = xcsd.pixel_number_to_qcolor(pixel);

   painter.setPen(Qt::NoPen);

   xy2 local {(u2)(coords.go_x * mult), (u2)(coords.go_y * mult)};


   if(coords.go_x % 3 == 1 && coords.go_y % 3 == 1)
   {
    painter.setBrush(Qt::lightGray);
    painter.drawRect(local.x, local.y, mult, mult) ;
    painter.setBrush(Qt::white);
    painter.drawRect(local.x + 2 * mag,
      local.y + 20 * mag, mult - 4 * mag, mult - 22 * mag);
   }
   else
   {
    painter.setBrush(Qt::white);
    painter.drawRect(local.x, local.y, mult, mult) ;
   }
    //     painter.drawRect(local.x + 1 * mag,
 //       local.y + 1 * mag, mult - 1 * mag, mult - 1 * mag) ;

   painter.setBrush(clr);

   painter.drawRect(local.x + 4 * mag,
     local.y + 21 * mag, mult - 8 * mag, mult - 29 * mag);

   painter.setPen(QColor(40,120,70));

   QFont font = painter.font();
   font.setPointSize(5 * mag);
   painter.setFont(font);

   painter.drawText(local.x + 3 * mag, local.y + 8 * mag,
     QString("%1").arg(coords.go_x));
   painter.drawText(local.x + 3 * mag, local.y + 17 * mag,
     QString("%1").arg(coords.go_y));

   font.setPointSize(6 * mag);
   painter.setFont(font);

   painter.setPen(QColor(140,0,30));
   painter.drawText(local.x + 15 * mag, local.y + 10 * mag,
     QString("%1")
       .arg(clr.red()));

   painter.setPen(QColor(0,140,30));
   painter.drawText(local.x + 31 * mag, local.y + 10 * mag,
     QString("%1")
       .arg(clr.green()));

   painter.setPen(QColor(30,0,140));
   painter.drawText(local.x + 15 * mag, local.y + 19 * mag,
     QString("%1")
       .arg(clr.blue()));

   painter.setPen(QColor(30,30,14));
   painter.drawText(local.x + 31 * mag, local.y + 19 * mag,
     QString("%1")
       .arg(255 - clr.alpha()));


   font.setPointSize(5 * mag);
   painter.setFont(font);

   painter.setPen(Qt::NoPen);
   painter.setBrush(QColor(255,255,255,200));
   painter.drawRect(local.x + 26 * mag, local.y + 19 * mag, 20 * mag, 9 * mag);
   painter.drawRect(local.x + 4 * mag, local.y + mult - 15 * mag, 13 * mag, 8 * mag);

   painter.setBrush(QColor(225,225,255,255));
   painter.drawEllipse(local.x + 22 * mag, local.y + mult - 18 * mag, 19 * mag, 7 * mag);

   painter.setPen(Qt::black);
   painter.drawText(local.x + 27 * mag, local.y + 26 * mag, "rgba");

   font.setPointSize(4);
   painter.drawText(local.x + 23 * mag, local.y + mult - 11 * mag,
     QString("+%1").arg(index));

   font.setPointSize(5);
   painter.setPen(Qt::darkYellow);
   painter.drawText(local.x + 5 * mag, local.y + mult - 9 * mag, "hsv");

   painter.setPen(Qt::darkYellow);
   painter.drawText(local.x + 4 * mag, local.y + mult - 3 * mag,
     QString("%1 %2 %3")
       .arg(clr.hue()).arg(clr.saturation()).arg(clr.value()));

      //clr.hslHue()

   if(coords.go_x % 9 == 0)
   {
    if(coords.go_x > 0)
    {
     painter.setPen(QPen(Qt::red, 3));
     painter.drawLine(local.x, local.y, local.x, local.y + mult);
    }
   }
   else if(coords.go_x % 3 == 0)
   {
    painter.setPen(QPen(Qt::darkMagenta, 2 * mag));
    painter.drawLine(local.x, local.y, local.x, local.y + mult);
   }
   else
   {
    painter.setPen(QPen(Qt::darkBlue, 1 * mag));
    painter.drawLine(local.x, local.y, local.x, local.y + mult);
   }

   if(coords.go_y % 9 == 0)
   {
    if(coords.go_y > 0)
    {
     painter.setPen(QPen(Qt::red, 3));
     painter.drawLine(local.x, local.y, local.x + mult, local.y);
    }
   }
   else if(coords.go_y % 3 == 0)
   {
    painter.setPen(QPen(Qt::darkMagenta, 2 * mag));
    painter.drawLine(local.x, local.y, local.x + mult, local.y);
   }
   else
   {
    painter.setPen(QPen(Qt::darkBlue, 1 * mag));
    painter.drawLine(local.x, local.y, local.x + mult, local.y);
   }

  }
//  }

  si.save(ROOT_FOLDER "/../test/diagram3.png");
  return;
 });


 if(0)
 xcsd.save_full_tier_image(ROOT_FOLDER "/../test/ft4.png",
   {}, //ROOT_FOLDER "/../test/tk1",
   [&xcsg](QImage& ti, XCSD_Image_Geometry::Grid_TierBox& gtb,
      XCSD_Image_Geometry::Iteration_Environment ienv,
      u4 data_index, n8* data_start ,  //pr2s mch,
      const XCSD_Image_Geometry::MCH_Info& mchi,
      QString info_folder, u1 tierbox_w)
 {
  QPainter painter(&ti);

  pr2s mch = gtb.loc.get_mch_code();
  u2 dist = mch.abs().make_descending().inner_difference();

//  u2 half_side = xcsg.full_tier_counts().greater() / 2;
//  r8 prop = (r8) dist / half_side;
//  u1 coffset = prop * 50;
//  qDebug() << "half = " << half_side << "prop = " << prop << " dist = " << dist << " coffset = " << coffset;

  painter.setBrush(QColor(dist * 20, dist * 20, 100, 100));
  //painter.drawText(2, 25, QString("%1").arg(dir));
  painter.drawRect(ti.rect());

  painter.setPen(QColor(100,220,220));
  painter.drawText(2, 25, QString("%1").arg(dist));

 });

 // // //

 if(0)
 xcsd.save_full_tier_image(ROOT_FOLDER "/../test/ft6.png",
   {}, //ROOT_FOLDER "/../test/tk1",
   [&xcsg, &xcsd](QImage& ti, XCSD_Image_Geometry::Grid_TierBox& gtb,
      XCSD_Image_Geometry::Iteration_Environment ienv,
      u4 data_index, n8* data_start ,  //pr2s mch,
      const XCSD_Image_Geometry::MCH_Info& mchi,
      QString info_folder, u1 tierbox_w)
 {

  rc2s quadrant = gtb.loc.rc() - xcsg.directed_centers().back().rc();
  rc2s quadrant_mask = quadrant.spaceship_mask();

  QPainter painter(&ti);


  pr2s mch = gtb.loc.get_mch_code();
  u2 dist = mch.abs().greater();
  u2 half_side = xcsg.full_tier_counts().greater() / 2;
  u2 manh = mch.abs().make_descending().inner_difference();

  r8 prop = (r8) dist / half_side;

  u1 coffset = prop * 50;

  u2 comp = (dist + manh) / 2;

  qDebug() << "half = " << half_side << "prop = " << prop << " dist = " << dist << " coffset = " << coffset;

//  painter.setBrush(QColor(0, dist * 16, dist * 16, 100));
//  //painter.drawText(2, 25, QString("%1").arg(dir));
//  painter.drawRect(ti.rect());

//  painter.setBrush(QColor(manh * 16, manh * 16, 0, 100));
//  painter.drawRect(ti.rect());

  u1 dmagn = 20;
  u1 mmagn = 12;
  u1 smmagn = 20;
  u1 cmagn = 9;
  u1 ccmagn = 7;

  u1 mmmagn = 10;

  s2 radj = mchi.tier_ring * quadrant_mask.r;
  s2 cadj = mchi.inner_pushout * quadrant_mask.c;

  painter.setPen(Qt::NoPen);

  painter.setBrush(QColor(255, 255 - dist * dmagn, 255 - dist * dmagn, 130));
  painter.drawRect(ti.rect());

  if(manh < 13)
    painter.setBrush(QColor(255 - manh * mmagn, 255 - manh * mmagn, 255, 255 - manh * mmmagn));
  else
    painter.setBrush(QColor(255 - manh * smmagn, 255 - manh * smmagn, 255, 255 - manh * mmmagn));

  painter.drawRect(ti.rect());

  painter.setBrush(QColor(comp * cmagn, comp * cmagn, 100, comp * ccmagn + 30));
  painter.drawRect(ti.rect());

  QFont font = painter.font();
  font.setPointSize(8);
  painter.setFont(font);

  painter.setPen(QColor(220,40,60));
  painter.drawText(2, 12, QString("%1 %2").arg(mchi.inner_pushout).arg(mchi.tier_ring)); //.arg(comp));

  font.setPointSize(6);
  painter.setFont(font);


  painter.setPen(QColor(100,220,220));
  painter.drawText(2, 25, QString("%1 %2").arg(radj).arg(cadj)); //.arg(comp));

 });

 if(0)
 xcsd.save_full_tier_image(ROOT_FOLDER "/../test/ft7.png",
   {}, //ROOT_FOLDER "/../test/tk1",
   [&xcsg, &xcsd](QImage& ti, XCSD_Image_Geometry::Grid_TierBox& gtb,
      XCSD_Image_Geometry::Iteration_Environment ienv,
      u4 data_index, n8* data_start ,  //pr2s mch,
      const XCSD_Image_Geometry::MCH_Info& mchi,
      QString info_folder, u1 tierbox_w)
 {

  if(gtb.loc.c() == 16 && gtb.loc.r() == 12)
  {
   QPainter painter(&ti);
   QBrush br(QColor(240, 210, 70, 229), Qt::DiagCrossPattern);
   painter.setBrush(br);
   painter.setPen(Qt::NoPen);
   painter.drawRect(ti.rect());
   QBrush br1(QColor(240, 210, 70, 199));
   painter.setBrush(br1);
   painter.drawRect(ti.rect());
  }
  else if(gtb.loc.r() == 12)
  {
   QPainter painter(&ti);
   QBrush br(QColor(240, 110, 170, 189), Qt::BDiagPattern);
   painter.setBrush(br);
   painter.setPen(Qt::NoPen);
   painter.drawRect(ti.rect());
   QBrush br1(QColor(240, 110, 170, 49));
   painter.setBrush(br1);
   painter.drawRect(ti.rect());
  }
  else if(gtb.loc.c() == 16)
  {
   QPainter painter(&ti);
   QBrush br(QColor(240, 240, 40, 189), Qt::FDiagPattern);
   painter.setBrush(br);
   painter.setPen(Qt::NoPen);
   painter.drawRect(ti.rect());
   QBrush br1(QColor(240, 240, 40, 49));
   painter.setBrush(br1);
   painter.drawRect(ti.rect());
  }
 });

 if(0)
 xcsd.save_full_tier_image(ROOT_FOLDER "/../test/ft8.png",
   {}, //ROOT_FOLDER "/../test/tk1",
   [&xcsg, &xcsd](QImage& ti, XCSD_Image_Geometry::Grid_TierBox& gtb,
      XCSD_Image_Geometry::Iteration_Environment ienv,
      u4 data_index, n8* data_start ,  //pr2s mch,
      const XCSD_Image_Geometry::MCH_Info& mchi,
      QString info_folder, u1 tierbox_w)
 {
  QString maskss {
   "kbff-fbkk-kkkk-kkkk_"
   "kbff-ffbk-kkkk-kkkk_"
   "bfff-ffff-bkkk-skkk_"
   "kkbf-ffff-ffff-sfff_"

   "kkks-ffff-ffff-ffff_"
   "kkkb-ffff-ffff-ffff_"
   "kkbf-fffb-ksff-fffb_"
   "kkbf-fffk-kbff-ffbk"
  };

  QMap<QChar, u1> codes { {'k', 0}, {'b', 2}, {'s', 1}, {'f', 3} };

  maskss.replace('-', "");

  QStringList qsl = maskss.split('_');

  n8 masks [4] {0,0,0,0};

  for(u1 half = 0; half < 8; half += 4)
  {
   for(u1 r = 0; r < 4; ++r)
   {
    for(u1 c = 0; c < 16; ++c)
    {
     QChar ch = qsl[half + r][c];
     u1 code = codes[ch];

     bb1 bb{(u1)(7 - (c % 8)), (u1)((3 - r) * 2)};

//     u1 byte = 7 - (c % 8);
//     u1 bit = (3 - r) * 2;

     //u1 offset =  bb.times(bb1{8,1}).inner_sum(); // 8 * byte + bit;

     u1 offset =  8 * bb.byte + bb.bit;

     n8 ofc = ((n8) code) << offset;

     masks[(half / 2) + (c / 8)] |= ofc;
    }
   }
  }

  if( gtb.loc.c() >= 16 && gtb.loc.r() >= 8
     && gtb.loc.c() < 32 && gtb.loc.r() < 16 )
  {
   u1 qc = gtb.loc.rc().quadrant_code_against(rc2s{12, 24});

   n8 mask = masks[qc];  //0xFFFF'FFFF'FFFF'FFFF; //  0b11'11'11'11'11'11'11'11'11'11'11'11'11'11'11'11;

   bb1 bb = gtb.loc.rc()._transposed().minus(rc2s{16,8})._to<bb1>();
   bb.byte %= 8;
   bb.byte = 7 - bb.byte;

   bb.bit %= 4;
   bb.bit = 3 - bb.bit;
   bb.bit *= 2;
   u1 adj = (mask >> (bb.byte * 8)) & 255;
   adj >>= bb.bit;
   adj &= 3;

   QPainter painter(&ti);

   switch(adj)
   {
   case 0:
    {
     QBrush br(QColor(24, 24, 40, 119), Qt::Dense2Pattern);
     painter.setBrush(br);
     painter.setPen(Qt::NoPen);
     painter.drawRect(ti.rect());
     QBrush br1(QColor(24, 24, 40, 89));
     painter.setBrush(br1);
     painter.drawRect(ti.rect());
    }
    break;
   case 3:
    {
     QBrush br(QColor(224, 224, 240, 189), Qt::Dense2Pattern);
     painter.setBrush(br);
     painter.setPen(Qt::NoPen);
     painter.drawRect(ti.rect());
     QBrush br1(QColor(224, 224, 240, 89));
     painter.setBrush(br1);
     painter.drawRect(ti.rect());
    }
    break;
   case 2:
    {
     QBrush br(QColor(124, 124, 124, 219), Qt::Dense4Pattern);
     painter.setBrush(br);
     painter.setPen(Qt::NoPen);
     painter.drawRect(ti.rect());
     QBrush br1(QColor(124, 124, 124, 89));
     painter.setBrush(br1);
     painter.drawRect(ti.rect());
    }
    break;
   case 1:
    {
     QBrush br(QColor(12, 124, 124, 219), Qt::Dense4Pattern);
     painter.setBrush(br);
     painter.setPen(Qt::NoPen);
     painter.drawRect(ti.rect());
     QBrush br1(QColor(12, 124, 124, 89));
     painter.setBrush(br1);
     painter.drawRect(ti.rect());
    }
    break;
   }

   QFont font = painter.font();
   font.setPointSize(8);
   painter.setFont(font);

   painter.setPen(QColor(220,40,60));
   painter.drawText(2, 12, QString("%1 %2").arg(bb.byte).arg(bb.bit)); //.arg(comp));

   font.setPointSize(6);
   painter.setFont(font);

   if(adj == 3)
     painter.setPen(QColor(50,120,120));
   else
     painter.setPen(QColor(100,220,220));
   painter.drawText(2, 25, QString("%1 %2")
     .arg(adj).arg(qc)); //.arg(comp));

  }
 });

// xcsg.draw_tier_summary(ROOT_FOLDER "/../tiers/t284x194.png", 2.5, 4);
// xcsg.draw_tier_summary(ROOT_FOLDER "/../tiers/t284x194.png", 2.5, 4);
// xcsg.draw_tier_summary(ROOT_FOLDER "/../tiers/t284x194.png", 2.5, 4);

 qDebug() << "full = " << xcsg.full_tier_counts();
 qDebug() << "overall = " << xcsg.overall_tier_counts();

 qDebug() << "outer h = " << xcsg.horizontal_outer_sizes();
 qDebug() << "outer v = " << xcsg.vertical_outer_sizes();

// TierBox_Location tbl = xcsg.get_tierbox_location_from_ground_position(80, 60);

// qDebug() << "tbl = " << tbl.rc();

// xcsg.calculate_tier_ring(tbl);

// qDebug() << "ring = " << tbl.tier_ring();

 return 0;
}
#endif

int main3(int argc , char **argv)
{
 //Mat2d<Vec1d<int>> mat;

// Box9x9_8bytepx* box = new Box9x9_8bytepx;

// return 0;

// QGuiApplication app(argc, argv);


 XCSD_Image xcsd;

 //xcsd.load_image(ROOT_FOLDER "/../pics/angle.jpg");
 xcsd.load_image(ROOT_FOLDER "/../pi/t1-30x30.png");

 //xcsd.image().setText("test", "result");
 // qDebug() << "image = " << xcsd.image().text();

// xcsd.init_tier_counts();
// xcsd.init_tierboxes();

 //rc2 rc = xcsd.get_tierbox_at_ground_position_RC2(4, 4);

 //qDebug() << "rc = " << rc;

// SDI_Position sdi = xcsd.get_sdi_at_ground_position(18, 19);

 //SDI_Position sdi = sdi_octal(4, 0111, 5, 0222);
 //SDI_Position sdi = sdi_octal(4'0111_sdi, 5'0222_sdi);
 SDI_Position sdi = 4'5'999_sd2;

 qDebug() << "sdi = " << sdi;

 xy1s m1 = sdi.get_mid1();
 xy1s m2 = sdi.get_mid2();
 xy1s gr = sdi.get_ground();

 qDebug() << "m1 = " << m1;
 qDebug() << "m2 = " << m2;
 qDebug() << "gr = " << gr;



// QVector<n8> pixels;
// xcsd.get_pixels()

 //XCSD_TierBox* trb = xcsd.get_tierbox_at_ground_position(4, 4);

// QImage& image = xcsd.image();

// u2 w = image.width();
// u2 h = image.height();

// qDebug() << "w = " << w / 27;
// qDebug() << "h = " << h / 27;

// u2 l0 = w % 27 / 2;
// u2 h0 = h % 27 / 2;

// qDebug() << "l0 = " << l0;
// qDebug() << "h0 = " << h0;



 return 0;
}



// // // // // // //




//QPixmap pixmap = QPixmap::fromImage(image);

//QPainter painter(&pixmap);

//painter.setPen(QColor::fromRgb(215, 255, 255));
//painter.setBrush(QColor::fromRgb(255, 255, 255));

//for(u2 x = l0; x < w; x += 27)
//{
// for(u2 y = 0; y < h; ++y)
// {
//  QRgb rgb = image.pixel(x, y);

//  u1 r = qRed(rgb);
//  u1 g = qGreen(rgb);
//  u1 b = qBlue(rgb);

//  r = qMin(r + 60, 255);
//  g = qMin(g + 60, 255);
//  b = qMin(b + 60, 255);

//  //QRgb rgb1 = QColor::fromRgb(255, g, b).rgb();

//  painter.setPen(QColor::fromRgb(r, g, b));

//  painter.drawPoint(x, y);

//  //painter.drawLine(0, y, w, y);
// }
// //painter.drawLine(x, 0, x, h);
//}

//for(u2 y = h0; y < h; y += 27)
//{
// for(u2 x = 0; x < w; ++x)
// {
//  //painter.drawLine(0, y, w, y);
//  QRgb rgb = image.pixel(x, y);

//  u1 r = qRed(rgb);
//  u1 g = qGreen(rgb);
//  u1 b = qBlue(rgb);

//  r = qMin(r + 60, 255);
//  g = qMin(g + 60, 255);
//  b = qMin(b + 60, 255);

//  //QRgb rgb1 = QColor::fromRgb(255, g, b).rgb();

//  painter.setPen(QColor::fromRgb(r, g, b));

//  painter.drawPoint(x, y);
// }
//}


//pixmap.save(ROOT_FOLDER "/../pics/angle.grid.png");

////  QPixmap pixmap = QPixmap::fromImage(image);
////  QPainter painter(&pixmap);





void show_255_palatte(QVector<QColor>& vec, QString path,
  QString sorted_path,
  u1 box_width,
  u1 padline_width)
{
 QPixmap pixmap(box_width * 30 + 20, box_width * 17);
 QPainter painter(&pixmap);

 u1 index = 0;

 bool needs_padline = false;

 painter.setPen(Qt::NoPen);

 QMap<QRgb, u1> positions;

 QMap<QRgb, QPoint> left_positions;

 painter.setBrush(QColor(255, 255, 255));
 painter.drawRect(0, 0, pixmap.width(), pixmap.height());

 for(u1 y = 0; y < 17; ++y)
 {
  u2 top = y * box_width;

  for(u1 x = 0; x < 15; ++x)
  {
   QColor c = vec[index];

   positions[c.rgb()] = index;

   if(y > 0)
   {
    if(y % 2)
      needs_padline = (x < 14);
    else
      needs_padline = (x > 0);
   }

   painter.setBrush(c);


   u2 left = x * box_width;

   QRect full_rect(left, top, box_width, box_width);
   left_positions[c.rgb()] = full_rect.center();

   if(needs_padline)
   {
    painter.drawRect(left, top + padline_width, box_width, box_width - padline_width);
//    painter.setBrush(QColor(255, 255, 255));
//    painter.drawRect(left, top, box_width, padline_width);
   }
   else
     painter.drawRect(left, top, box_width, box_width);

   ++index;
  }
 }

// pixmap.save(path);

 QVector<QColor> vec1 = vec;

 std::sort(vec1.begin(), vec1.end(), [](QColor lhs, QColor rhs)
 {
  return lhs.value() < rhs.value();
 });

// QPixmap pixmap1(box_width * 15, box_width * 17);
// QPainter painter1(&pixmap1);

 index = 0;

 u2 xoffset = box_width * 15 + 20;

 //bool needs_padline = false;

 //QMap<QColor, u1> positions;

 for(u1 y = 0; y < 17; ++y)
 {
  u2 top = y * box_width;

  for(u1 x = 0; x < 15; ++x)
  {
   QColor c = vec1[index];


   painter.setBrush(c);

   u2 left = x * box_width + xoffset;

//   if(needs_padline)
//   {
//    painter.drawRect(left, top + padline_width, box_width, box_width);
//    painter.setBrush(QColor(255, 255, 255));
//    painter.drawRect(left, top, box_width, padline_width);
//   }
//   else

   QRect full_rect(left, top, box_width, box_width);

   painter.setPen(Qt::NoPen);

   painter.drawRect(full_rect);

   QRgb rgb = c.rgb();
   QPoint qp = left_positions[rgb];

   u1 left_index = positions[rgb];

   left_index /= 17;

   QPen circle_pen = QPen(QColor(0, 0, 0));
   circle_pen.setWidth(2);

   painter.setPen(circle_pen);

   painter.setBrush(QColor(255, 255, 255));

   painter.drawEllipse(full_rect.center(), left_index, left_index);

   ++index;
  }
 }

// pixmap1.save(sorted_path);
 pixmap.save(path);


}

int main1(int argc , char **argv)
{
 //Mat2d<Vec1d<int>> mat;

 XCSD_Image xcsd;

 xcsd.load_image(ROOT_FOLDER "/../pics/p2.draw.bmp");

 QImage image = xcsd.image();

 u4 w = image.width();
 u4 h = image.height();

 QGuiApplication app(argc, argv);

 QPixmap pixmap = QPixmap::fromImage(image);

 QPainter painter(&pixmap);

 u2 shtop = 0;
 u2 shbot = 0;

 u2 shl = 0;
 u2 shr = 0;

 for(u4 x = 0; x < w; ++x)
 {
  for(u4 y = 0; y < h; ++y)
  {
   QRgb rgb = image.pixel(x, y);

   QRgb ref_rgb = QColor(153, 193, 241).rgb();
   QColor ref = QColor(153, 193, 241);

   QColor ic(rgb);

   s2 red = (s2)ic.red() - (s2)ref.red();
   s2 blue = (s2)ic.blue() - (s2)ref.blue();
   s2 green = (s2)ic.green() - (s2)ref.green();

   u1 r = qAbs(red);
   u1 g = qAbs(green);
   u1 b = qAbs(blue);

//   qDebug() << "red = " << r << " blue = " << b << " green = " << g;

   u1 offset = 1;



   if(r + b + g < 60)
   {
    if(x == 0)
    {
     if(shtop == 0)
       shtop = y;
     else if(shbot == 0)
       shbot = y;
    }
    else if(y == 0)
    {
     if(shl == 0)
       shl = x;
     else if(shr == 0)
       shr = x;
    }



    for(s1 j = -offset; j <= offset; ++j)
    {
     for(s1 k = -offset; k <= offset; ++k)
     {
      QRgb rgb = image.pixel(x + j, y + k);
      QColor c(rgb);
      double h = c.hsvHue();
      double s = c.hsvSaturation();
      double v = c.value();

//      if(v < 0.5) v += 0.5;
//      else v = 1;

      qDebug() << "v = " << v;

      v = 200;

      QColor c1 = QColor::fromHsv(h, s, v);
//      QColor c1 = c;

      qDebug() << "c = " << c << " c1 = " << c1;

      painter.setBrush(c1);
      painter.setPen(Qt::NoPen);

      painter.drawRect(x + j - 1, y + k - 1, 3, 3);
     }
    }

   }


//   u1 i = i255.pixelIndex(x, y);
//   ++indices[i].second;
  }

 }

 painter.setBrush(QColor(100, 200, 200, 200));

 qDebug() << "shl = " << shl;
 qDebug() << "shr = " << shr;

 qDebug() << "shtop = " << shtop;
 qDebug() << "shbot = " << shbot;

 painter.drawRect(shl, shtop, shr - shl, shbot - shtop);

 pixmap.save(ROOT_FOLDER "/../pics/p2.draw.proc.bmp");



}


int main2(int argc , char **argv)
{
 //Mat2d<Vec1d<int>> mat;

 XCSD_Image xcsd;

 xcsd.load_image(ROOT_FOLDER "/../pics/angle.jpg");

 xcsd.image().setText("test", "result");

 qDebug() << "image = " << xcsd.image().text();

 QVector<QColor> vec; //(255);

 xcsd.get_255_palette(vec);

 QGuiApplication app(argc, argv);

 show_255_palatte(vec, ROOT_FOLDER "/../pics/angle.jpg.pal.png",
   ROOT_FOLDER "/../pics/angle.jpg.pals.png", 50, 8);
 //show_255_palatte(vec, "/home/nlevisrael/gits/ctg-temp/pics/test.png", 50, 8);




 return 0;
}
