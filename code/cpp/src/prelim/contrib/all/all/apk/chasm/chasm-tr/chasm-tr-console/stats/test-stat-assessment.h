
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef DHAX_STAT_ASSESSMENT__H
#define DHAX_STAT_ASSESSMENT__H


#include <QString>

#include <QImage>

#include "accessors.h"

#include "global-types.h"

//?#include "xcsd-2d/xcsd-image.h"



#ifdef USE_OpenCV

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <opencv2/xfeatures2d/nonfree.hpp>

#include "opencv2/features2d/features2d.hpp"
#include "opencv2/xfeatures2d.hpp"

#endif



class Feature_Classifier_Transform;

class Test_Application_Controller;

class Test_Stat_Assessment
{
 QString full_image_path_;
 QString gray_image_path_;
 QString one_channel_image_path_;
 QString one_channel_dist_image_path_;
 QString one_channel_dist_display_image_path_;

 QString eight_bit_image_path_;

 QString current_out_subfolder_;

 QString algorithm_name_;

 Feature_Classifier_Transform* feature_classifier_transform_;

// typedef void (*proc_type) (Test_Stat_Assessment&);

// typedef std::function<void(Test_Stat_Assessment&)> proc_type;

 void (*proc_)(Test_Stat_Assessment&); // proc_;
 void (*follow_up_)(Test_Stat_Assessment&); // proc_;
// proc_type proc_;

 void* user_data_;

 QVector<QString> ref_image_paths_;
 QVector<QString> prior_ref_image_paths_;


#ifdef USE_OpenCV

 cv::Mat full_image_;
 cv::Mat gray_image_;
 cv::Mat one_channel_image_;
 cv::Mat one_channel_display_image_;
 cv::Mat one_channel_dist_image_;
 cv::Mat one_channel_dist_display_image_;

 std::vector<cv::KeyPoint> keypoints_full_, keypoints_1c_,
   keypoints_dist_1c_, keypoints_1c_screened_;


#endif

 void check_subfolder(QString& result);

public:

 Test_Stat_Assessment();


 ACCESSORS(QString ,full_image_path)
 ACCESSORS(QString ,gray_image_path)
 ACCESSORS(QString ,one_channel_image_path)
 ACCESSORS(QString ,one_channel_dist_display_image_path)
 ACCESSORS(QString ,one_channel_dist_image_path)
 ACCESSORS(QString ,eight_bit_image_path)

 ACCESSORS(QVector<QString> ,ref_image_paths)
 ACCESSORS(QVector<QString> ,prior_ref_image_paths)

 void add_ref_image_path(QString path)
 {
  ref_image_paths_.push_back(path);
 }

 void add_prior_ref_image_path(QString path)
 {
  prior_ref_image_paths_.push_back(path);
 }


 ACCESSORS__RGET(std::vector<cv::KeyPoint> ,keypoints_full)
 ACCESSORS__RGET(std::vector<cv::KeyPoint> ,keypoints_1c)
 ACCESSORS__RGET(std::vector<cv::KeyPoint> ,keypoints_dist_1c)
 ACCESSORS__RGET(std::vector<cv::KeyPoint> ,keypoints_1c_screened)

 ACCESSORS(QString ,current_out_subfolder)

 void set_current_out_subfolder(u1 dim);

 ACCESSORS(QString ,algorithm_name)

 ACCESSORS(void* ,user_data)

 ACCESSORS(Feature_Classifier_Transform* ,feature_classifier_transform)

 ACCESSORS(cv::Mat ,full_image)
 ACCESSORS(cv::Mat ,gray_image)
 ACCESSORS(cv::Mat ,one_channel_image)
 ACCESSORS(cv::Mat ,one_channel_display_image)
 ACCESSORS(cv::Mat ,one_channel_dist_image)
 ACCESSORS(cv::Mat ,one_channel_dist_display_image)


 void run_classifier_transform();


 QString get_full_1c_out_path(QString name_extra);
 QString get_full_1c_screened_out_path(QString name_extra);
 QString get_1c_out_path(QString name_extra);
 QString get_full_out_path(QString name_extra);
 QString get_dist_1c_out_path(QString name_extra);
 QString get_full_dist_1c_out_path(QString name_extra);


 QString get_full_1c_oa_out_path(QString name_extra);
 QString get_full_oa_out_path(QString name_extra);
 QString get_dist_1c_oa_out_path(QString name_extra);


 QString get_full_out_path()
 {
  return get_full_out_path(algorithm_name_);
 }

 QString get_dist_1c_out_path()
 {
  return get_dist_1c_out_path(algorithm_name_);
 }

 QString get_full_1c_out_path()
 {
  return get_full_1c_out_path(algorithm_name_);
 }

 QString get_full_1c_screened_out_path()
 {
  return get_full_1c_screened_out_path(algorithm_name_);
 }

 QString get_1c_out_path()
 {
  return get_1c_out_path(algorithm_name_);
 }

 QString get_full_dist_1c_out_path()
 {
  return get_full_dist_1c_out_path(algorithm_name_);
 }


 QString get_full_oa_out_path()
 {
  return get_full_oa_out_path(algorithm_name_);
 }

 QString get_dist_1c_oa_out_path()
 {
  return get_dist_1c_oa_out_path(algorithm_name_);
 }

 QString get_full_1c_oa_out_path()
 {
  return get_full_1c_oa_out_path(algorithm_name_);
 }


 void run();

 void check_follow_up();

 ACCESSORS__FNP(void, Test_Stat_Assessment& ,proc)
 ACCESSORS__FNP(void, Test_Stat_Assessment& ,follow_up)

// ACCESSORS__SET_FNP(void, Test_Stat_Assessment& ,proc)
// ACCESSORS__GET_FNP(void, Test_Stat_Assessment& ,proc)

// void set_proc(void (*proc)(Test_Stat_Assessment&))
// {
//  proc_ = proc;
// }

// void (*get_proc(Test_Stat_Assessment&))()
// {
//  return proc_;
// }

// ACCESSORS(void (*)()  ,proc)
// ACCESSORS(proc_type ,proc)



 void load_images();

 static void run_demo_test(QString folder, QString base_file_name,
   QString extension, Test_Application_Controller* application_controller);


};


#endif // TEST_STAT_ASSESSMENT__H
