
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "test-stat-assessment.h"

#include "feature-classifier-transform.h"



#include <QFileInfo>


Test_Stat_Assessment::Test_Stat_Assessment()
  :  user_data_(nullptr), proc_(nullptr),
     follow_up_(nullptr),
     feature_classifier_transform_(nullptr)
{

}

void Test_Stat_Assessment::load_images()
{
#ifdef USE_OpenCV

 full_image_ = cv::imread(full_image_path_.toStdString());

 if(gray_image_path_.isEmpty())
   cv::cvtColor(full_image_, gray_image_, cv::COLOR_BGR2GRAY);
 else
   gray_image_ = cv::imread(gray_image_path_.toStdString());

 one_channel_image_ = cv::imread(one_channel_image_path_.toStdString(),
   cv::IMREAD_GRAYSCALE);

 one_channel_display_image_ = cv::imread(one_channel_image_path_.toStdString());

 one_channel_dist_image_ = cv::imread(one_channel_dist_image_path_.toStdString(),
   cv::IMREAD_GRAYSCALE);

 one_channel_dist_display_image_ = cv::imread(one_channel_dist_display_image_path_.toStdString());


#else
// //?  Anything here?
#endif

}


void Test_Stat_Assessment::run()
{
 proc_(*this);
}

void Test_Stat_Assessment::check_follow_up()
{
 if(follow_up_)
   follow_up_(*this);
}


void Test_Stat_Assessment::set_current_out_subfolder(u1 dim)
{
 current_out_subfolder_ = "out-%1d"_qt.arg(dim);
}


void Test_Stat_Assessment::check_subfolder(QString& result)
{
 if(current_out_subfolder_.isEmpty())
   return;

 QFileInfo qfi(result);

 result =
   qfi.absolutePath() + "/" + current_out_subfolder_ + "/"
   + qfi.completeBaseName() + "." + qfi.suffix();
}


QString Test_Stat_Assessment::get_full_1c_screened_out_path(QString name_extra)
{
 QString result = full_image_path_;
 check_subfolder(result);

 return result.replace("-full", "-full-1c-screened-" + name_extra);
}

QString Test_Stat_Assessment::get_full_1c_out_path(QString name_extra)
{
 QString result = full_image_path_;
 check_subfolder(result);

 return result.replace("-full", "-full-1c-" + name_extra);
}

QString Test_Stat_Assessment::get_1c_out_path(QString name_extra)
{
 QString result = one_channel_image_path_;
 check_subfolder(result);

 return result.replace("-1c", "-1c-" + name_extra);
}

QString Test_Stat_Assessment::get_full_out_path(QString name_extra)
{
 QString result = full_image_path_;
 check_subfolder(result);

 return result.replace("-full", "-full-" + name_extra);
}

QString Test_Stat_Assessment::get_dist_1c_out_path(QString name_extra)
{
 QString result = one_channel_dist_image_path_;
 check_subfolder(result);

 return result.replace("-1c", "-1c-" + name_extra);
}

QString Test_Stat_Assessment::get_full_dist_1c_out_path(QString name_extra)
{
 QString result = full_image_path_;
 check_subfolder(result);

 return result.replace("-full", "-full-1cd-" + name_extra);
}


QString Test_Stat_Assessment::get_full_1c_oa_out_path(QString name_extra)
{
 QString result = full_image_path_;
 check_subfolder(result);

 return result.replace("-full", "-full-1c-oa-" + name_extra);
}

QString Test_Stat_Assessment::get_full_oa_out_path(QString name_extra)
{
 QString result = full_image_path_;
 check_subfolder(result);

 return result.replace("-full", "-full-oa-" + name_extra);
}

QString Test_Stat_Assessment::get_dist_1c_oa_out_path(QString name_extra)
{
 QString result = one_channel_dist_image_path_;
 check_subfolder(result);

 return result.replace("-1c", "-1c-oa-" + name_extra);
}

void Test_Stat_Assessment::run_classifier_transform()
{
 if(!feature_classifier_transform_)
   return;

 QFileInfo qfi(full_image_path_);

 QImage qim;

 //?QImage& qim = dlg->get_active_image().getQImage();

 for(cv::KeyPoint kp : keypoints_1c_screened_)
 {
  u2 x = kp.pt.x, y = kp.pt.y;
  QColor c = qim.pixelColor(x, y);
  c.setAlpha(1);
  qim.setPixelColor(x, y, c);
 }

 for(cv::KeyPoint kp : keypoints_1c_)
 {
  u2 x = kp.pt.x, y = kp.pt.y;
  QColor c = qim.pixelColor(x, y);

  if(c.alpha() == 1)
    c.setAlpha(254);
  else // //  screened out
    c.setAlpha(251);

  qim.setPixelColor(x, y, c);
 }

 for(cv::KeyPoint kp : keypoints_full_)
 {
  u2 x = kp.pt.x, y = kp.pt.y;
  QColor c = qim.pixelColor(x, y);

  if(c.alpha() == 255)
    c.setAlpha(253);
  else
    c.setAlpha(252);

//  c.setAlpha(c.alpha() - 2);

//  if(c.alpha() < 252)
//  {
//   qDebug() << "c a: " << c.alpha();
//  }

  qim.setPixelColor(x, y, c);
 }


//? qim.save("/home/nlevisrael/gits/ctg-temp/dev/Test-stats/temp.png");

// for(u2 y = 0; y < qim.height(); ++y)
//  for(u2 x = 0; x < qim.width(); ++x)
//  {
//   qim.pixel()
//  }

 //qim.setPixel()


// dlg->set_default_image_file(main_window_controller_->current_image_file_path());


// QVector<std::shared_ptr<ICommand>> cmds;
}


