
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "dhax-stat-assessment.h"

#include <QDebug>

#include <QtMath>

#include <QDir>

#include "feature-classifier-transform.h"

#include "application/dhax-application-controller.h"

#include <QMessageBox>

//void ((*_make_run_0d))(DHAX_Stat_Assessment&)

//typedef void(*_make_run_0d_type)(DHAX_Stat_Assessment&);
//_make_run_0d_type _make_run_0d()
//void ((*_make_run_0d)(DHAX_Stat_Assessment&))()


//


//{
// cv::Mat dst, cdst, cdstP;

////   const char* default_file = "sudoku.png";
////   // Loads an image
////   cv::Mat src = imread( cv::samples::findFile( default_file ), cv::IMREAD_GRAYSCALE );

// cv::Mat src = cv::imread("/home/nlevisrael/gits/ctg-temp/dev/dhax-stats/test-combined/default/out/angle/angle.fb-1c.jpg",
//    cv::IMREAD_GRAYSCALE );

////?  cv::Mat src = stat.gray_image();

// // Edge detection
// cv::Canny(src, dst, 50, 200, 3);
// // Copy edges to the images that will display the results in BGR
// cv::cvtColor(dst, cdst, cv::COLOR_GRAY2BGR);
// cdstP = cdst.clone();
// // Standard Hough Line Transform
// std::vector<cv::Vec2f> lines; // will hold the results of the detection
// cv::HoughLines(dst, lines, 1, CV_PI/180, 50, 0, 0 ); // runs the actual detection
// // Draw the lines
// for( size_t i = 0; i < lines.size(); i++ )
// {
//     float rho = lines[i][0], theta = lines[i][1];
//     cv::Point pt1, pt2;
//     double a = cos(theta), b = sin(theta);
//     double x0 = a*rho, y0 = b*rho;
//     pt1.x = cvRound(x0 + 1000*(-b));
//     pt1.y = cvRound(y0 + 1000*(a));
//     pt2.x = cvRound(x0 - 1000*(-b));
//     pt2.y = cvRound(y0 - 1000*(a));
//     line( cdst, pt1, pt2, cv::Scalar(0,0,255), 3, cv::LINE_AA);
// }
// // Probabilistic Line Transform
// std::vector<cv::Vec4i> linesP; // will hold the results of the detection
// cv::HoughLinesP(dst, linesP, 1, CV_PI/180, 15, 50, 20 ); // runs the actual detection
// // Draw the lines
// for( size_t i = 0; i < linesP.size(); i++ )
// {
//     cv::Vec4i l = linesP[i];
//     cv::line( cdstP, cv::Point(l[0], l[1]), cv::Point(l[2], l[3]), cv::Scalar(0,0,255), 3, cv::LINE_AA);
// }

// cv::imwrite("/home/nlevisrael/gits/ctg-temp/dev/dhax-stats/cdist.png", cdst);
// cv::imwrite("/home/nlevisrael/gits/ctg-temp/dev/dhax-stats/cdistp.png", cdstP);

////   // Show results
////   cv::imshow("Source", src);
////   cv::imshow("Detected Lines (in red) - Standard Hough Line Transform", cdst);
////   cv::imshow("Detected Lines (in red) - Probabilistic Line Transform", cdstP);
////   // Wait and Exit

//}


//make_lines_proc(HOUGH)
//HOUGH_stat->run();

#include "slic/slic.h"
#include "slico/slico.h"

void (*_make_run_superpixels())(DHAX_Stat_Assessment&)
{
 return [](DHAX_Stat_Assessment& stat)
 {
  stat.load_images();

  extern char *optarg;
  extern int optopt;

 // QString input_file = stat.full_image_path();

  stat.set_current_out_subfolder(2);

//  QString output_file = stat.get_full_1c_out_path();
//  cv::Mat inputMatrix = stat.full_image();

  const int numberOfSuperpixels = 800;
  const int compactness = 50;
  const double treshold = 30.0;

//  cv::Mat onec = stat.one_channel_image();
//  qDebug() << "on " << stat.one_channel_display_image_path();

  superpixel::SLIC sslic1, sslic2;
  SLIC slic, slic_8b;

  cv::Mat img, img_8b, img_ref1, img_ref2, img_on_full, result, result_ref1,
    result_ref2, result_8b, result_8bf, result_ref1f, result_8b_on_full, result_8b_ref1, result_8b_ref2; //, result_8b_ref21;

  img = stat.full_image().clone();
  img_on_full = img.clone();

  img_8b = cv::imread(stat.eight_bit_image_path().toStdString());
  //imgc = stat.one_channel_dist_image();

  //slic.GetImgWithContours(stat.full_image(), stat.get_full_out_path(), numberOfSuperpixels, compactness, treshold);

  slic.GenerateSuperpixels(img, numberOfSuperpixels);
  slic_8b.GenerateSuperpixels(img_8b, numberOfSuperpixels);

  result = slic.GetImgWithContours(cv::Scalar(0, 0, 255));
  result_8b = slic_8b.GetImgWithContours(cv::Scalar(255, 255, 100));



//  BRISK

  img_ref1 = cv::imread(stat.prior_ref_image_paths()[0].toStdString());
  img_ref2 = cv::imread(stat.prior_ref_image_paths()[1].toStdString());


  std::vector<cv::KeyPoint>& kps = stat.keypoints_1c_screened();
  result_8bf = slic_8b.GetImgWithContours(cv::Scalar(255, 255, 100), img_ref1, &kps);
  result_ref1f = slic.GetImgWithContours(cv::Scalar(255, 255, 100), img_ref1, &kps, Qt::red);


  result_8b_ref1 = slic_8b.GetImgWithContours(cv::Scalar(255, 255, 100), img_ref1);
  result_ref1 = slic.GetImgWithContours(cv::Scalar(0, 0, 255), img_ref1);

  result_8b_ref2 = slic_8b.GetImgWithContours(cv::Scalar(255, 255, 100), img_ref2);
  result_ref2 = slic.GetImgWithContours(cv::Scalar(255, 0, 0), img_ref2);
//  result_8b_ref21 = slic_8b.GetImgWithContours(cv::Scalar(255, 255, 100), img_ref2);

  result_8b_on_full = slic_8b.GetImgWithContours(cv::Scalar(255, 255, 100), img_on_full);

  QString out = stat.get_full_out_path();
  QString out_f = out, out_8b = out, out_o8b = out,
    out_o8b_on_full = out, out_o8b_ref1 = out, out_o8b_ref2 = out,
    out_ref1 = out, out_ref1f = out, out_ref2 = out, out_o8bf = out;

  out_f.replace("full", "full-o");
  out_o8b.replace("full", "full-o8b");
  out_8b.replace("full", "full-8b");
  out_o8b_ref1.replace("full", "full-o8b-ref1");
  out_o8b_ref2.replace("full", "full-o8b-ref2");
  out_o8b_on_full.replace("full", "on-full-o8b");
  out_ref1.replace("full", "full-o-ref1");
  out_ref2.replace("full", "full-o-ref2");
  out_o8bf.replace("full", "full-o-8bf");
  out_ref1f.replace("full", "full-o-ref1f");

  cv::imwrite(out_f.toStdString(), result);
  cv::imwrite(out_o8b.toStdString(), result_8b);
  cv::imwrite(out_o8b_ref1.toStdString(), result_8b_ref1);
  cv::imwrite(out_ref1.toStdString(), result_ref1);
  cv::imwrite(out_o8b_ref2.toStdString(), result_8b_ref2);
  cv::imwrite(out_ref2.toStdString(), result_ref2);
  cv::imwrite(out_o8b_on_full.toStdString(), result_8b_on_full);
  cv::imwrite(out_o8bf.toStdString(), result_8bf);
  cv::imwrite(out_ref1f.toStdString(), result_ref1f);

  sslic1.getSupperpixels(stat.full_image(), out, numberOfSuperpixels, compactness, treshold);
//?  sslic2.getSupperpixels(img_8b, out_8b, numberOfSuperpixels, compactness, treshold);


 };
}


// //   downloaded from: https://gist.github.com/insaneyilin/164267440dd19511f20f8546c3c98296
void DrawDashedLine(cv::Mat& img, cv::Point pt1, cv::Point pt2,
                    cv::Scalar color, int thickness, std::string style,
                    int gap) {
  float dx = pt1.x - pt2.x;
  float dy = pt1.y - pt2.y;
  float dist = std::hypot(dx, dy);

  std::vector<cv::Point> pts;
  for (int i = 0; i < dist; i += gap) {
    float r = static_cast<float>(i / dist);
    int x = static_cast<int>((pt1.x * (1.0 - r) + pt2.x * r) + .5);
    int y = static_cast<int>((pt1.y * (1.0 - r) + pt2.y * r) + .5);
    pts.emplace_back(x, y);
  }

  int pts_size = pts.size();

  if (style == "dotted") {
    for (int i = 0; i < pts_size; ++i) {
      cv::circle(img, pts[i], thickness, color, -1);
    }
  } else {
    cv::Point s = pts[0];
    cv::Point e = pts[0];

    for (int i = 0; i < pts_size; ++i) {
      s = e;
      e = pts[i];
      if (i % 2 == 1) {
        cv::line(img, s, e, color, thickness);
      }
    }
  }
}

void (*_make_run_lines())(DHAX_Stat_Assessment&)
{
 return [](DHAX_Stat_Assessment& stat)
 {
  stat.load_images();

  cv::Mat canny_full, out_color_full, out_color_p_full;
  cv::Mat canny_1c, out_color_1c, out_color_p_1c;
  cv::Mat canny_dist_1c, out_color_dist_1c, out_color_p_dist_1c;

  cv::Canny(stat.gray_image(), canny_full, 50, 200, 3);
//  cv::cvtColor(canny_full, out_color_full, cv::COLOR_GRAY2BGR);

  cv::Canny(stat.one_channel_image(), canny_1c, 50, 200, 3);
//  cv::cvtColor(canny_full, out_color_1c, cv::COLOR_GRAY2BGR);

  cv::Canny(stat.one_channel_dist_image(), canny_dist_1c, 50, 200, 3);
//  cv::cvtColor(canny_full, out_color_dist_1c, cv::COLOR_GRAY2BGR);


  out_color_full = stat.full_image().clone();
//  out_color_1c = stat.one_channel_display_image().clone();
//  out_color_dist_1c = stat.one_channel_dist_display_image().clone();
  out_color_1c = stat.full_image().clone();
  out_color_dist_1c = stat.full_image().clone();

  out_color_p_full = out_color_full.clone();
  out_color_p_1c = out_color_1c.clone();
  out_color_p_dist_1c = out_color_dist_1c.clone();


//  cv::Mat threshold_full, threshold_1c, threshold_dist_1c;
//  cv::threshold(stat.gray_image(), threshold_full, 200, 255, cv::THRESH_BINARY);
//  cv::threshold(stat.one_channel_image(), threshold_1c, 200, 255, cv::THRESH_BINARY);
//  cv::threshold(stat.one_channel_dist_image(), threshold_dist_1c, 200, 255, cv::THRESH_BINARY);

  r8 rho = 1;  // distance resolution in pixels of the Hough grid
  r8 theta = CV_PI / 180;  // angular resolution in radians of the Hough grid
  u4 threshold = 15;  // minimum number of votes (intersections in Hough grid cell)
  u4 min_line_length = 50; // minimum number of pixels making up a line
  u4 max_line_gap = 20; // # maximum gap in pixels between connectable line segments

  threshold = 150;  // minimum number of votes (intersections in Hough grid cell)
  min_line_length = 0; // minimum number of pixels making up a line
  max_line_gap = 0; // # maximum gap in pixels between connectable line segments

//  cv::Mat copy_full = stat.full_image().clone();
//  cv::Mat line_results;
//  cv::HoughLinesP(stat.gray_image(), copy_full, rho, theta, threshold,
//    min_line_length, max_line_gap);

  std::vector<cv::Vec2f> lines_full, lines_1c, lines_dist_1c;

  cv::HoughLines(canny_full, lines_full, rho, theta, threshold, min_line_length, max_line_gap); // runs the actual detection
  cv::HoughLines(canny_1c, lines_1c, rho, theta, threshold, min_line_length, max_line_gap); // runs the actual detection
  cv::HoughLines(canny_dist_1c, lines_dist_1c, rho, theta, threshold, min_line_length, max_line_gap); // runs the actual detection

  // Draw the lines

  auto draw_lines = [](std::vector<cv::Vec2f>& lines, u2 extent, cv::Mat out, r8& theta_avg,
    r8 fct_rotation, bool debug_theta = false)
  {
   std::vector<r8> diffs_avg, diffs_rotation;
   diffs_avg.resize(lines.size());
   diffs_rotation.resize(lines.size());

   r8 avg = 0;

   for( size_t i = 0; i < lines.size(); i++ )
   {
    avg += lines[i][1];
   }

   if(lines.size())
     avg /= lines.size();

   for( size_t i = 0; i < lines.size(); i++ )
   {
    diffs_avg[i] = qAbs(lines[i][1] - avg);
    diffs_rotation[i] = qAbs(lines[i][1] - fct_rotation);
   }

   auto it_avg = std::min_element(diffs_avg.begin(), diffs_avg.end());
   size_t best_fit_avg = std::distance(diffs_avg.begin(), it_avg);

   auto it_rotation = std::min_element(diffs_rotation.begin(), diffs_rotation.end());
   size_t best_fit_rotation = std::distance(diffs_rotation.begin(), it_rotation);

   auto draw_line = [&out](float angle, float rho, QColor color, u1 width, u2 extent, u1 gap = 0) //cv::Scalar cv_color)
   {
    cv::Scalar cv_color(color.blue(), color.green(), color.red());
    cv::Point pt1, pt2;
    double a = cos(angle), b = sin(angle);
    double x0 = a*rho, y0 = b*rho;

    pt1.x = cvRound(x0 + extent * (-b));
    pt1.y = cvRound(y0 + extent * (a));
    pt2.x = cvRound(x0 - extent * (-b));
    pt2.y = cvRound(y0 - extent * (a));

    if(gap)
      DrawDashedLine(out, pt1, pt2, cv_color, width, "dotted", gap);

    else
      cv::line(out, pt1, pt2, cv_color, width, cv::LINE_AA);
   };

   for( size_t i = 0; i < lines.size(); i++ )
   {
    float rho = lines[i][0], theta = lines[i][1];

    if(debug_theta)
      qDebug() << "theta = " << qRadiansToDegrees(theta);

    draw_line(theta, rho, QColor(Qt::cyan).lighter(175), 2, extent);

//    draw_line(qDegreesToRadians(90.), Qt::yellow);
//    draw_line(qDegreesToRadians(45.), Qt::magenta);
   }

   QColor semi = QColor("orange").lighter(180);
   draw_line(lines[best_fit_rotation][1], lines[best_fit_rotation][0], semi, 15, extent, 38);

   semi = QColor(Qt::magenta).lighter(120);
   semi.setRed(semi.red() + 30);
   draw_line(lines[best_fit_avg][1], lines[best_fit_avg][0], semi, 13, extent, 36);

//   if(i == best_fit_rotation)



   theta_avg = qRadiansToDegrees(avg);
  };

  r8 avg_full, avg_1c, avg_dist_1c;

  //qRad()

  r8 fct_rotation = 0;
  if(stat.feature_classifier_transform())
  {
   fct_rotation = qDegreesToRadians(stat.feature_classifier_transform()->rotation() + 90);
  }

  u2 extent = canny_full.cols * 2;

  qDebug() << "extent = " << extent;

  draw_lines(lines_full, extent, out_color_full, avg_full, fct_rotation);
  draw_lines(lines_1c, extent, out_color_1c, avg_1c, fct_rotation);
  draw_lines(lines_dist_1c, extent, out_color_dist_1c, avg_dist_1c, fct_rotation);

  //qDebug() << "theta average (dist 1c) = " << avg_dist_1c;

  {
   r8 fctr = stat.feature_classifier_transform()->rotation();
   r8 fct90 = fctr + 90;

   r8 accuracy = avg_dist_1c - fctr;
   if(accuracy < 0)
     accuracy += 90;
   else if(accuracy > 90)
     accuracy = 180 - accuracy;

   r8 gaccuracy = avg_full - fctr;
   if(gaccuracy < 0)
     gaccuracy += 90;
   else if(gaccuracy > 90)
     gaccuracy = 180 - gaccuracy;

   accuracy /= 90;
   gaccuracy /= 90;
//?
//   r8 accuracy = qMin(avg_dist_1c, fct90) / qMax(avg_dist_1c, fct90);
//   r8 gaccuracy = qMin(avg_full, fct90) / qMax(avg_full, fct90);

   QString msg = R"(Predefined Rotation (against vertical): %1
Grayscale Line Average: %2
Toroidal Color Model Line Average: %3
Grayscale Accuracy (against predefined): %4 (%5%)
Toroidal Accuracy: %6 (%7%)
                 )"_qt.arg(fct90)
     .arg(avg_full).arg(avg_dist_1c).arg(gaccuracy).arg((int)(gaccuracy * 100))
     .arg(accuracy).arg((int)(accuracy * 100))
     ;


   QMessageBox* message_box = new QMessageBox();
   message_box->setMinimumWidth(350);
   message_box->setText("Line Detection Angles (compared to predefined transform)"_qt);
   message_box->setInformativeText(R"(Hit "Show Details" for a breakdown)");
   message_box->setDetailedText(msg);
   message_box->setModal(false);
   message_box->show();
  }


  std::vector<cv::Vec4i> linesP_full, linesP_1c, linesP_dist_1c;
  cv::HoughLinesP(canny_full, linesP_full, 1, CV_PI/180, 50, 50, 10 ); // runs the actual detection

  auto draw_linesP = [](std::vector<cv::Vec4i>& lines, cv::Mat out)
  {
   for( size_t i = 0; i < lines.size(); i++ )
   {
    cv::Vec4i l = lines[i];
    cv::line(out, cv::Point(l[0], l[1]), cv::Point(l[2], l[3]), cv::Scalar(0,0,255), 3, cv::LINE_AA);
   }
  };

  draw_linesP(linesP_full, out_color_p_full);
  draw_linesP(linesP_1c, out_color_p_1c);
  draw_linesP(linesP_dist_1c, out_color_p_dist_1c);

//  cv::imwrite("/home/nlevisrael/gits/ctg-temp/dev/dhax-stats/HOUGH.png", line_results);

  cv::imwrite(stat.get_full_out_path("HOUGH").toStdString(), out_color_full);
  cv::imwrite(stat.get_full_out_path("HOUGHP").toStdString(), out_color_p_full);

  cv::imwrite(stat.get_full_1c_out_path("HOUGH").toStdString(), out_color_1c);
  cv::imwrite(stat.get_full_1c_out_path("HOUGHP").toStdString(), out_color_p_1c);

  cv::imwrite(stat.get_dist_1c_out_path("HOUGH").toStdString(), out_color_dist_1c);
  cv::imwrite(stat.get_dist_1c_out_path("HOUGHP").toStdString(), out_color_p_dist_1c);  
 };
}

template<cv::RetrievalModes rm, cv::ContourApproximationModes cam>
void (*_make_run_contours())(DHAX_Stat_Assessment&)
{
 return [](DHAX_Stat_Assessment& stat)
 {
  stat.load_images();

  cv::Mat eight_bit_image = cv::imread(stat.eight_bit_image_path().toStdString());

  cv::Mat eight_bit_image_gray;
  cv::cvtColor(eight_bit_image, eight_bit_image_gray, cv::COLOR_BGR2GRAY);

  cv::Mat threshold_full, threshold_8b, threshold_1c, threshold_dist_1c;
  cv::threshold(stat.gray_image(), threshold_full, 200, 255, cv::THRESH_BINARY);
  cv::threshold(stat.one_channel_image(), threshold_1c, 200, 255, cv::THRESH_BINARY);
  cv::threshold(stat.one_channel_dist_image(), threshold_dist_1c, 200, 255, cv::THRESH_BINARY);
  cv::threshold(eight_bit_image_gray, threshold_8b, 200, 255, cv::THRESH_BINARY);

  cv::Mat copy_full = stat.full_image().clone();

  cv::Mat copy_8b = eight_bit_image.clone();

  cv::Mat copy_1c = stat.one_channel_display_image().clone();

  cv::Mat copy_full_1c = stat.full_image().clone();

  cv::Mat copy_full_dist_1c = stat.full_image().clone();
//  cv::Mat copy_dist_1c = stat.one_channel_dist_image().clone();
  cv::Mat copy_dist_1cd = stat.one_channel_dist_display_image().clone();

  std::vector<std::vector<cv::Point>> contours_full, contours_8b, contours_1c, contours_dist_1c;
  std::vector<cv::Vec4i> hierarchy_full, hierarchy_8b, hierarchy_1c, hierarchy_dist_1c;

  cv::findContours(threshold_full, contours_full, hierarchy_full,
    rm, cam); //cv::CHAIN_APPROX_NONE);

  cv::findContours(threshold_8b, contours_8b, hierarchy_8b,
    rm, cam); //cv::CHAIN_APPROX_NONE);

  cv::findContours(threshold_1c, contours_1c, hierarchy_1c,
    rm, cam); //, cv::CHAIN_APPROX_NONE);

  cv::findContours(threshold_dist_1c, contours_dist_1c, hierarchy_dist_1c,
    rm, cam); //, cv::CHAIN_APPROX_NONE);

  static auto less_than = [](std::vector<cv::Point>& lhs,
    std::vector<cv::Point>& rhs)
  {
   return lhs.size() < rhs.size();
  };

  auto it_full = std::max_element(contours_full.begin(), contours_full.end(), less_than);

  auto it_8b = std::max_element(contours_8b.begin(), contours_8b.end(), less_than);

  auto it_1c = std::max_element(contours_1c.begin(), contours_1c.end(), less_than);

  auto it_dist_1c = std::max_element(contours_dist_1c.begin(), contours_dist_1c.end(), less_than);


  std::vector<cv::Point>& max_full = *it_full;
//  std::vector<cv::Point>& max_8b = *it_8b;
  std::vector<cv::Point>& max_1c = *it_1c;
  std::vector<cv::Point>& max_dist_1c = *it_dist_1c;


  qDebug() << "max = " << max_full.size();
  //?qDebug() << "max 8b = " << max_8b.size();
  qDebug() << "max 1c = " << max_1c.size();
  qDebug() << "max dist 1c = " << max_dist_1c.size();


  std::vector<std::vector<cv::Point>> larger_contours_full,
    larger_contours_8b, larger_contours_1c, larger_contours_dist_1c;

  std::vector<std::vector<cv::Point>> largest_contours_full,
    largest_contours_8b, largest_contours_1c, largest_contours_dist_1c;

  std::vector<std::vector<cv::Point>> smaller_contours_full,
    smaller_contours_8b, smaller_contours_1c, smaller_contours_dist_1c;

  largest_contours_full.push_back(max_full);
 //? largest_contours_8b.push_back(max_8b);
  largest_contours_1c.push_back(max_1c);
  largest_contours_dist_1c.push_back(max_dist_1c);

  for(size_t i = 0;  i < contours_full.size(); ++i)
  {
   if(contours_full[i].size() > (max_full.size() / 2))
     larger_contours_full.push_back(contours_full[i]);

   else
     smaller_contours_full.push_back(contours_full[i]);
  }

  for(size_t i = 0;  i < contours_8b.size(); ++i)
  {
//   if(contours_8b[i].size() > (max_8b.size() / 2))
//     larger_contours_8b.push_back(contours_8b[i]);

//   else
     smaller_contours_8b.push_back(contours_8b[i]);
  }

  for(size_t i = 0;  i < contours_1c.size(); ++i)
  {
   if(contours_1c[i].size() > (max_1c.size() / 2))
     larger_contours_1c.push_back(contours_1c[i]);

   else
     smaller_contours_1c.push_back(contours_1c[i]);
  }

  for(size_t i = 0;  i < contours_dist_1c.size(); ++i)
  {
   if(contours_dist_1c[i].size() > (max_dist_1c.size() / 2))
     larger_contours_dist_1c.push_back(contours_dist_1c[i]);

   else
     smaller_contours_dist_1c.push_back(contours_dist_1c[i]);
  }


  drawContours(copy_full, smaller_contours_full, -1, cv::Scalar(255, 0, 0), 1);
  drawContours(copy_8b, smaller_contours_8b, -1, cv::Scalar(255, 0, 0), 1);
  drawContours(copy_full_1c, smaller_contours_1c, -1, cv::Scalar(255, 0, 0), 1);
  drawContours(copy_1c, smaller_contours_1c, -1, cv::Scalar(255, 0, 0), 1);
  drawContours(copy_dist_1cd, smaller_contours_dist_1c, -1, cv::Scalar(255, 0, 0), 1);
  drawContours(copy_full_dist_1c, smaller_contours_dist_1c, -1, cv::Scalar(255, 0, 0), 1);


  drawContours(copy_full, larger_contours_full, -1, cv::Scalar(0, 255, 0), 2);
  drawContours(copy_8b, larger_contours_8b, -1, cv::Scalar(0, 255, 0), 2);
  drawContours(copy_full_1c, larger_contours_1c, -1, cv::Scalar(0, 255, 0), 2);
  drawContours(copy_1c, larger_contours_1c, -1, cv::Scalar(0, 255, 0), 2);
  drawContours(copy_dist_1cd, larger_contours_dist_1c, -1, cv::Scalar(0, 255, 0), 2);
  drawContours(copy_full_dist_1c, larger_contours_dist_1c, -1, cv::Scalar(0, 255, 0), 2);


  drawContours(copy_full, largest_contours_full, -1, cv::Scalar(0, 0, 255), 3);
  drawContours(copy_8b, largest_contours_8b, -1, cv::Scalar(0, 0, 255), 3);
  drawContours(copy_full_1c, largest_contours_1c, -1, cv::Scalar(0, 0, 255), 3);
  drawContours(copy_1c, largest_contours_1c, -1, cv::Scalar(0, 0, 255), 3);
  drawContours(copy_dist_1cd, largest_contours_dist_1c, -1, cv::Scalar(0, 0, 255), 3);
  drawContours(copy_full_dist_1c, largest_contours_dist_1c, -1, cv::Scalar(0, 0, 255), 3);

  cv::imwrite(stat.get_full_out_path().toStdString(), copy_full);

  QString out_8b = stat.get_full_out_path();
  out_8b.replace("full", "8b");

  qDebug() << "out 8b = " << out_8b;
  cv::imwrite(out_8b.toStdString(), copy_8b);

  cv::imwrite(stat.get_full_1c_out_path().toStdString(), copy_full_1c);
  cv::imwrite(stat.get_1c_out_path().toStdString(), copy_1c);

  cv::imwrite(stat.get_dist_1c_out_path().toStdString(), copy_dist_1cd);
  cv::imwrite(stat.get_full_dist_1c_out_path().toStdString(), copy_dist_1cd);


 // drawContours(image_copy, {max}, -1, cv::Scalar(0, 255, 0), 2);
 // // drawContours(image_copy, contours, -1, cv::Scalar(0, 255, 0), 2);
 // imwrite("contours_filter_image1.jpg", image_copy);

 };
}


// //  these are the same as
 //    Heuristic Color Maxk in the editor ...
u1 diff(u1 a1, u1 a2)
{
 return a1 > a2? a1 - a2 : a2 - a1;
}
bool test(u1 offset, u1 rdiff, u1 gdiff, u1 bdiff)
{
 return rdiff <= offset && gdiff <= offset && bdiff <= offset;
}


template<typename ALGORITHM_Type>
void (*_make_run_0d())(DHAX_Stat_Assessment&)
{
 return [](DHAX_Stat_Assessment& stat)
 {
  cv::Ptr<cv::FeatureDetector> detector;
  cv::Ptr<cv::DescriptorExtractor> descriptor;
  stat.load_images();

  detector = ALGORITHM_Type::create();
  descriptor = ALGORITHM_Type::create();

//  stat.set_user_data(detector.get());
  stat.set_user_data(detector.get());
  stat.check_follow_up();

//  if(stat.get_follow_up())
//  {
//   qDebug() << "Upright ...";
//   detector.staticCast<cv::xfeatures2d::SURF>()->setUpright(true);
//  }

//#ifdef _make_run_0d_UPRIGHT
//  qDebug() << "Upright ..."
//  detector.staticCast<cv::xfeatures2d::SURF>()->setUpright(true);
//#endif

  cv::Mat image_full, out_full, image_1c, out_1c, out_1c_screened,
    image_dist_1c, out_dist_1c, out_full_dist_1c;

  std::vector<cv::KeyPoint>& keypoints_full = stat.keypoints_full(),
    &keypoints_1c_screened = stat.keypoints_1c_screened(),
    &keypoints_1c = stat.keypoints_1c(), &keypoints_dist_1c = stat.keypoints_dist_1c();


  detector->detectAndCompute(stat.gray_image(), cv::noArray(), keypoints_full, image_full);
  cv::drawKeypoints(stat.full_image(),
    keypoints_full, out_full, cv::Scalar(0, 255, 0));
  cv::imwrite(stat.get_full_out_path().toStdString(), out_full);
//?  cv::imwrite(stat.get_full_oa_out_path().toStdString(), image_full);


  detector->detectAndCompute(stat.one_channel_image(), cv::noArray(), keypoints_1c, image_1c);
  cv::drawKeypoints(stat.full_image(),
     keypoints_1c, out_1c, cv::Scalar(0, 255, 0));
  cv::imwrite(stat.get_full_1c_out_path().toStdString(), out_1c);

  static u1 diff_offset = 120;

  for(cv::KeyPoint kp : keypoints_1c)
  {
   u2 x = kp.pt.x, y = kp.pt.y;
   //QColor c = qim.pixelColor(x, y);

   //? BGR& bgr = image.ptr<BGR>(y)[x];
   cv::Vec3b vec = stat.full_image().at<cv::Vec3b>(y, x);

   QColor foreground_color;

   if(stat.feature_classifier_transform())
     foreground_color = stat.feature_classifier_transform()->foreground_color();
   else if(stat.xcsd_image())
     foreground_color = stat.xcsd_image()->foreground_pole();

   if(foreground_color.isValid())
   {
    QColor vec_color(vec[2], vec[1], vec[0]);

    s2 vec_hue = vec_color.hue();
    s2 foreground_hue = foreground_color.hue();

    s2 diff = vec_hue - foreground_hue;
    if(qAbs(diff) < diff_offset)
    {
     keypoints_1c_screened.push_back(kp);
    }
   }
//   if(test(diff_offset, diff(vec[2], foreground_color.red()),
//     diff(vec[1], foreground_color.green()),
//     diff(vec[2], foreground_color.blue())))
//   {
//    keypoints_1c_screened.push_back(kp);
//   }

  }
  cv::drawKeypoints(stat.full_image(),
     keypoints_1c_screened, out_1c_screened, cv::Scalar(0, 255, 0));
  cv::imwrite(stat.get_full_1c_screened_out_path().toStdString(), out_1c_screened);

  stat.add_ref_image_path(stat.get_full_1c_screened_out_path());
//  stat.add_ref_image_path(stat.get_full_1c_out_path());

//?  cv::imwrite(stat.get_full_1c_oa_out_path().toStdString(), image_1c);


  detector->detectAndCompute(stat.one_channel_dist_image(), cv::noArray(), keypoints_dist_1c,
    image_dist_1c);
  cv::drawKeypoints(stat.full_image(),
     keypoints_dist_1c, out_dist_1c, cv::Scalar(0, 255, 0));
  cv::imwrite(stat.get_dist_1c_out_path().toStdString(), out_dist_1c);
//?  cv::imwrite(stat.get_dist_1c_oa_out_path().toStdString(), image_dist_1c);


  cv::drawKeypoints(stat.full_image(),
     keypoints_dist_1c, out_full_dist_1c, cv::Scalar(0, 255, 0));
  cv::imwrite(stat.get_full_dist_1c_out_path().toStdString(), out_full_dist_1c);



//  cv::imwrite("/home/nlevisrael/gits/im-cv/i4/images/AKAZE-result.jpg", _out);

 };
}



void DHAX_Stat_Assessment::run_demo_test(QString folder, QString base_file_name,
  QString extension, DHAX_Application_Controller* application_controller, XCSD_Image* xcsd)
{
 Feature_Classifier_Transform* fct = nullptr;

 QString ntxh;

 if(xcsd)
   ntxh = xcsd->ntxh_file();

 if(!ntxh.isEmpty())
 {
  fct = new Feature_Classifier_Transform;
  fct->init_from_ntxh(xcsd->ntxh_file());
 }


#ifdef USE_OpenCV

 QDir qd(folder);

 QString full = qd.absoluteFilePath(base_file_name + "-full." + extension);
 QString one_channel_dist = qd.absoluteFilePath(base_file_name + "-dist-1c." + extension);
 QString one_channel_dist_display = qd.absoluteFilePath(base_file_name + "-1cd." + extension);

 QString one_channel_fb = qd.absoluteFilePath(base_file_name + ".fb-1c." + extension);
 QString eight_b = qd.absoluteFilePath(base_file_name + ".8ba." + extension);

 std::shared_ptr<DHAX_Stat_Assessment> HOUGH_stat( new DHAX_Stat_Assessment );
 std::shared_ptr<DHAX_Stat_Assessment> SLIC_stat( new DHAX_Stat_Assessment );

 std::shared_ptr<DHAX_Stat_Assessment> AKAZE_stat( new DHAX_Stat_Assessment );
 std::shared_ptr<DHAX_Stat_Assessment> SIFT_stat( new DHAX_Stat_Assessment );
 std::shared_ptr<DHAX_Stat_Assessment> BRISK_stat( new DHAX_Stat_Assessment );
 std::shared_ptr<DHAX_Stat_Assessment> ORB_stat( new DHAX_Stat_Assessment );
 std::shared_ptr<DHAX_Stat_Assessment> SURF_stat( new DHAX_Stat_Assessment );
 std::shared_ptr<DHAX_Stat_Assessment> USURF_stat( new DHAX_Stat_Assessment );

 std::shared_ptr<DHAX_Stat_Assessment> RETR_TREE_CHAIN_APPROX_NONE_stat( new DHAX_Stat_Assessment );

 std::shared_ptr<QMap<QString, std::shared_ptr<DHAX_Stat_Assessment>>> transforms_map
   ( new QMap<QString, std::shared_ptr<DHAX_Stat_Assessment>> );

// AKAZE_stat->set_full_image_path(full);
// AKAZE_stat->set_one_channel_image_path(one_channel);
// AKAZE_stat->set_one_channel_display_image_path(one_channel_display);

// SIFT_stat->set_full_image_path(full);
// SIFT_stat->set_one_channel_image_path(one_channel);
// SIFT_stat->set_one_channel_display_image_path(one_channel_display);

// BRISK_stat->set_full_image_path(full);
// BRISK_stat->set_one_channel_image_path(one_channel);
// BRISK_stat->set_one_channel_display_image_path(one_channel_display);

// ORB_stat->set_full_image_path(full);
// ORB_stat->set_one_channel_image_path(one_channel);
// ORB_stat->set_one_channel_display_image_path(one_channel_display);

// SURF_stat->set_full_image_path(full);
// SURF_stat->set_one_channel_image_path(one_channel);
// SURF_stat->set_one_channel_display_image_path(one_channel_display);

// USURF_stat->set_full_image_path(full);
// USURF_stat->set_one_channel_image_path(one_channel);
// USURF_stat->set_one_channel_display_image_path(one_channel_display);

#define setup(ALGORITHM_NAME) \
 ALGORITHM_NAME##_stat->set_full_image_path(full); \
 ALGORITHM_NAME##_stat->set_one_channel_image_path(one_channel_fb); \
 ALGORITHM_NAME##_stat->set_eight_bit_image_path(eight_b); \
 ALGORITHM_NAME##_stat->set_one_channel_dist_image_path(one_channel_dist); \
 ALGORITHM_NAME##_stat->set_one_channel_dist_display_image_path(one_channel_dist_display); \
 ALGORITHM_NAME##_stat->set_algorithm_name(#ALGORITHM_NAME); \
 ALGORITHM_NAME##_stat->set_feature_classifier_transform(fct); \
 ALGORITHM_NAME##_stat->set_xcsd_image(xcsd); \


#define make_0d_proc(ALGORITHM) \
 setup(ALGORITHM) \
 (*transforms_map)[#ALGORITHM] = ALGORITHM##_stat; \
 ALGORITHM##_stat->set_current_out_subfolder(0); \
 ALGORITHM##_stat->set_proc(_make_run_0d<cv::ALGORITHM>()); \

#define make_0d_xproc(ALGORITHM) \
 setup(ALGORITHM) \
 (*transforms_map)[#ALGORITHM] = ALGORITHM##_stat; \
 ALGORITHM##_stat->set_current_out_subfolder(0); \
 ALGORITHM##_stat->set_proc(_make_run_0d<cv::xfeatures2d::ALGORITHM>()); \

#define make_0d_uxproc(ALGORITHM) \
 setup(U##ALGORITHM) \
 (*transforms_map)["U" #ALGORITHM] = U##ALGORITHM##_stat; \
 U##ALGORITHM##_stat->set_current_out_subfolder(0); \
 U##ALGORITHM##_stat->set_proc(_make_run_0d<cv::xfeatures2d::ALGORITHM>()); \


#define make_lines_proc(ALGORITHM) \
 setup(ALGORITHM) \
 ALGORITHM##_stat->set_current_out_subfolder(1); \
 ALGORITHM##_stat->set_proc(_make_run_lines()); \


#define make_superpixels_proc(ALGORITHM) \
 setup(ALGORITHM) \
 ALGORITHM##_stat->set_current_out_subfolder(1); \
 ALGORITHM##_stat->set_proc(_make_run_superpixels()); \


#define make_contours_proc(retrievalModes, contourApproximationModes)  \
 setup(retrievalModes ##_## contourApproximationModes) \
 retrievalModes ##_## contourApproximationModes ##_stat \
   ->set_current_out_subfolder(2); \
 retrievalModes ##_## contourApproximationModes ##_stat \
   ->set_proc(_make_run_contours<cv::retrievalModes, \
     cv::contourApproximationModes>()); \


// make_0d_proc(AKAZE)
// AKAZE_stat->run();

// make_0d_proc(SIFT)
// SIFT_stat->run();

// make_0d_proc(ORB)
// ORB_stat->run();

// make_0d_xproc(SURF)
// SURF_stat->run();

// make_0d_uxproc(SURF)
// USURF_stat->set_follow_up([](DHAX_Stat_Assessment& stat)
// {
//  qDebug() << "setting upright ";
//  (static_cast<cv::xfeatures2d::SURF*>(stat.user_data()))->setUpright(true);
// });
// USURF_stat->run();

 make_contours_proc(RETR_TREE, CHAIN_APPROX_NONE);
 RETR_TREE_CHAIN_APPROX_NONE_stat->run();

// CHAIN_APPROX_NONE_stat->set_proc(_make_run_contours<cv::CHAIN_APPROX_NONE>());


 make_lines_proc(HOUGH)
 HOUGH_stat->run();

 application_controller->set_bookmarked_image_path(HOUGH_stat->get_dist_1c_out_path("HOUGH"));



 make_0d_proc(BRISK)
 BRISK_stat->run();

 application_controller->show_keypoints(transforms_map, full, BRISK_stat->keypoints_1c_screened());

//? BRISK_stat->run_classifier_transform();

 make_superpixels_proc(SLIC)
 SLIC_stat->set_prior_ref_image_paths(BRISK_stat->ref_image_paths());
 SLIC_stat->add_prior_ref_image_path(eight_b);

 SLIC_stat->keypoints_1c_screened() = BRISK_stat->keypoints_1c_screened();

 SLIC_stat->run();


#undef make_0d_proc
#undef make_0d_xproc
#undef make_0d_uxproc

#undef make_contours_proc
#undef setup

//   AKAZE_detector = cv::AKAZE::create();
//   SIFT_detector = cv::SIFT::create(); //?min
//   BRISK_detector = cv::BRISK::create();
//   ORB_detector = cv::ORB::create(2000);
//   SURF_detector = cv::xfeatures2d::SURF::create();
//   USURF_detector = cv::xfeatures2d::SURF::create();

//?

#endif
}
