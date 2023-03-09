
#include "color-mean-demo-frame.h"



Color_Mean_Demo_Frame::Color_Mean_Demo_Frame(QVector<QStringList> paths,
  u4 image_width, u4 large_image_width,
  u4 scroll_minimum_width,
  u4 image_height, u4 large_image_height)
  :  image_width_(image_width),
     large_image_width_(large_image_width),
     image_height_(image_height),
     large_image_height_(large_image_height)
{

// DGI_Image*

//     DGI_Image* circles;
// DGI_Image* approx_poly;
// DGI_Image* hull_poly;
// DGI_Image* hull_poly_color_mean;

 main_layout_ = new QHBoxLayout;
 left_layout_ = new QGridLayout;

 large_images_ = new QStackedWidget(this);

 left_buttons_ = new QButtonGroup;

// QPushButton* overlay_button_;
// QPushButton* color_mean_button_;
// QPushButton* tierboxes_button_;


// u1 total = std::accumulate(paths.begin(), paths.end(), 0, [](QStringList qsl)
// {
//  return qsl.size();
// });

 u1 total = std::accumulate(paths.begin(), paths.end(), 0, [](int sum, QStringList qsl)
 {
  return sum + qsl.size();
 });

// u1 total = std::accumulate(paths.begin(), paths.end(), 0,
//  std::bind(std::plus<size_t>(), std::placeholders::_1, bind(&QStringList::size, std::placeholders::_2)));

// bind(plus<size_t>(), _1, bind(&C::GetCount, _2)

 buttons_.resize(total);
 labels_.resize(total);


 u1 col = 0;
 for(QStringList qsl : paths)
 {
  u1 row = 0;
  for(QString path : qsl)
  {
   buttons_[row] = image_path_as_qbutton(this, path, image_width_, image_height_);
   labels_[row] = image_path_as_qlabel(this, path, large_image_width_, large_image_height_);
   left_layout_->addWidget(buttons_[row], row, col);
   large_images_->addWidget(labels_[row]);
   buttons_[row]->setCheckable(true);
   buttons_[row]->setChecked(false);
   left_buttons_->addButton(buttons_[row]);
   ++row;
  }
  ++col;
 }

 buttons_[0]->setChecked(true);

// color_mean_button_ = image_path_as_qbutton(this, paths[1], image_width_, image_height_);
// color_mean_label_ = image_path_as_qlabel(this, paths[1], large_image_width_, large_image_height_);
// left_layout_->addWidget(color_mean_button_, 1, 0);
// large_images_->addWidget(color_mean_label_);
// color_mean_button_->setCheckable(true);
// color_mean_button_->setChecked(false);
// left_buttons_->addButton(color_mean_button_);

// tierboxes_button_ = image_path_as_qbutton(this, paths[2], image_width_, image_height_);
// tierboxes_label_ = image_path_as_qlabel(this, paths[2], large_image_width_, large_image_height_);
// left_layout_->addWidget(tierboxes_button_, 2, 0);
// large_images_->addWidget(tierboxes_label_);
// tierboxes_button_->setCheckable(true);
// tierboxes_button_->setChecked(false);
// left_buttons_->addButton(tierboxes_button_);


 connect(left_buttons_, static_cast<void(QButtonGroup::*)(int)>
         (&QButtonGroup::buttonClicked),
   [this](int i)
 {
  large_images_->setCurrentIndex(-i - 2);
 });



 main_layout_->addLayout(left_layout_);

 large_image_scroll_ = new QScrollArea(this);
 large_image_scroll_->setWidget(large_images_);

 large_images_->setCurrentIndex(0);

 main_layout_->addWidget(large_image_scroll_);

 large_image_scroll_->resize(500,300);
 large_image_scroll_->setMinimumWidth(scroll_minimum_width);
 large_image_scroll_->setWidgetResizable(true);

 setLayout(main_layout_);
}

QPushButton* Color_Mean_Demo_Frame::image_path_as_qbutton(QWidget* parent, QString path, u4 image_width, u4 image_height)
{
 if(image_height == 0)
   image_height = image_width;

 QImage image;
 image.load(path);

// = new QImage((uchar*) rgb_matrix.data,
//   rgb_matrix.cols, rgb_matrix.rows, rgb_matrix.step, QImage::Format_RGB888);



 QPushButton* result = new QPushButton(parent);

 if(image_width == 0)
 {
  QPixmap qpm = QPixmap::fromImage(image);
  QIcon icon(qpm);
  result->setIcon(icon);
  result->setIconSize(qpm.rect().size());
 }
 else
 {
  QPixmap qpm = QPixmap::fromImage(image.scaled(image_width, image_height, Qt::KeepAspectRatio));
  QIcon icon(qpm);
  result->setIcon(icon);
  result->setIconSize(qpm.rect().size());
 }
//   result->setPixmap(QPixmap::fromImage(image->scaled(w, h, Qt::KeepAspectRatio)));

 return result;
}

QLabel* Color_Mean_Demo_Frame::image_path_as_qlabel(QWidget* parent, QString path, u4 image_width, u4 image_height)
{
 if(image_height == 0)
   image_height = image_width;

 QImage image;
 image.load(path);

// = new QImage((uchar*) rgb_matrix.data,
//   rgb_matrix.cols, rgb_matrix.rows, rgb_matrix.step, QImage::Format_RGB888);

 QLabel* result = new QLabel(parent);

 if(image_width == 0)
 {
  QPixmap qpm = QPixmap::fromImage(image);
  result->setPixmap(qpm);
 }
 else
 {
  QPixmap qpm = QPixmap::fromImage(image.scaled(image_width, image_height, Qt::KeepAspectRatio));
  result->setPixmap(qpm);
 }

 return result;
}



#ifdef HIDE
int thresh = 100;
cv::RNG rng(12345);

QMap<int, int> child_contours_count;
QMap<int, int> contours_depth;


int get_contours_depth(int i, const std::vector<cv::Vec4i>& data)
{
 if(contours_depth.contains(i))
   return contours_depth[i];

 if(data[i][3] == -1)
 {
  contours_depth[i] = 0;
  return 0;
 }

 int result = 0;
 int j = data[i][3];
 ++result;
 result += get_contours_depth(j, data);

 contours_depth[i] = result;

 return result;
}

int count_child_contours(int i, const std::vector<cv::Vec4i>& data)
{
 if(child_contours_count.contains(i))
   return child_contours_count[i];

 if(data[i][2] == -1)
 {
  child_contours_count[i] = 0;
  return 0;
 }

 int result = 0;
 int j = data[i][2];
 while(j != -1)
 {
  ++result;
  result += count_child_contours(j, data);
  j = data[j][0];
 }

 child_contours_count[i] = result;

 return result;
}

void imshow(cv::Mat _img)
{
 cv::Mat img;
 cv::cvtColor( _img, img, cv::COLOR_BGR2RGB );


 // image is created according to Mat dimensions
 QImage* image = new QImage(img.size().width, img.size().height, QImage::Format_RGB32);
 // Copy cv::Mat to QImage
 memcpy(image->scanLine(0), img.data, static_cast<size_t>(image->width() * image->height() * img.channels()));
 // Display the QImage in a QLabel
 QLabel* label = new QLabel;
 label->setPixmap(QPixmap::fromImage(*image));
 label->show();

}

QLabel* _imshow(const cv::Mat& src, QString title)
{
 cv::Mat mat;
 cv::cvtColor(src, mat, cv::COLOR_BGR2RGB);

 // image is created according to Mat dimensions
 QImage* image = new QImage(mat.size().width, mat.size().height, QImage::Format_RGB888);

 // Copy cv::Mat to QImage
 memcpy(image->scanLine(0), mat.data, static_cast<size_t>(image->width() * image->height() * mat.channels()));

 // Display the QImage in a QLabel
 QLabel* label = new QLabel;
 label->setPixmap(QPixmap::fromImage(*image));
// label->setText(title);

 //label->show();

 return label;
}


void thresh_callback(int, void*, const cv::Mat& src, cv::Mat& drawing, cv::Mat& hpoly,
  cv::Mat& apoly, cv::Mat& icirc, cv::Mat& colorsh)
{
    cv::Mat canny_output;
    Canny( src, canny_output, thresh, thresh*2 );


    int dilation_elem = 0;
    int dilation_size = 1;

    int dilation_pt = 1;

    int const max_elem = 2;
    int const max_kernel_size = 21;

    cv::Mat element = cv::getStructuringElement( cv::MORPH_ELLIPSE,
                         cv::Size( 2*dilation_size + 1, 2*dilation_size+1 ),
                         cv::Point( dilation_pt, dilation_pt ) );

     cv::dilate(canny_output, canny_output, element); //gray,kernel,iterations = 1)


    std::vector<std::vector<cv::Point> > contours;
    std::vector<cv::Vec4i> hierarchy;

    findContours( canny_output, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE );

    drawing = cv::Mat::zeros( canny_output.size(), CV_8UC3 );
    hpoly = cv::Mat::zeros( canny_output.size(), CV_8UC3 );
    apoly = cv::Mat::zeros( canny_output.size(), CV_8UC3 );
    icirc = cv::Mat::zeros( canny_output.size(), CV_8UC3 );
    colorsh = cv::Mat::zeros( canny_output.size(), CV_8UC3 );


    std::vector<std::vector<cv::Point> > hcontours;
    std::vector<std::vector<cv::Point> > acontours;

    std::vector<cv::Vec4i> chierarchy;

    std::vector<int> has_parent;

    for( size_t i = 0; i< contours.size(); i++ )
    {     
     std::vector<cv::Point>& c = contours[i];
     cv::Vec4i& hh = hierarchy[i];

     double d = cv::contourArea(c);
     qDebug() << "d = " << d;


//     if(d > 200)
//       continue;

     std::vector<cv::Point> ch;
     ch.resize(c.size());
     std::vector<cv::Point> ca;
     ca.resize(c.size());

     if(hh[3] == -1)
     {
      has_parent.push_back(0);
      cv::convexHull(c, ch);

      double epsilon = 0.03*cv::arcLength(c,true);
      cv::approxPolyDP(c, ca, epsilon, true);
     }
     else
     {

      has_parent.push_back(1);

     }

     hcontours.push_back(ch);
     acontours.push_back(ca);

     chierarchy.push_back(hh);
    }

//    cv::Scalar color = cv::Scalar( rng.uniform(0, 256), rng.uniform(0,256), rng.uniform(0,256) );
//    drawContours( poly, contours, (int)i, color, 2, cv::LINE_8, hierarchy, 0 );

//     fillPoly(poly, contours, cv::Scalar(100, 50, 200),8);

    QMap<int, int> contour_nesting;



    for( size_t i = 0; i< hcontours.size(); i++ )
    {
//        cv::Scalar color = cv::Scalar(255, 255, 255);  //;cv::Scalar( rng.uniform(0, 256), rng.uniform(0,256), rng.uniform(0,256) );
//        drawContours( drawing, contours, (int)i, color, 2, cv::FILLED,  //cv::LINE_8,
//                      hierarchy, 0 );

     std::vector<cv::Point>& c = contours[i];
     std::vector<cv::Point>& ch = hcontours[i];
     std::vector<cv::Point>& ca = acontours[i];

    int cc =  count_child_contours(i, hierarchy);
    qDebug() << "cc = " << cc;


    int cd =  get_contours_depth(i, hierarchy);
    qDebug() << "cd = " << cd;


//     float rad;

//     cv::minEnclosingCircle()

     int hc = has_parent[i];
     cv::Scalar color;
     if(hc)
       color = cv::Scalar(255, 40, 20);
     else
       color = cv::Scalar(100, 40, 200);

     drawContours( drawing, contours, i, color, 1, 8, chierarchy, INT_MAX, cv::Point(-1 ,-1) );

     double ms = cv::matchShapes(ch, ca, 1, 0);

     qDebug() << "ms = " << ms;

     ms *= 10;

     fillPoly(hpoly, {ch}, cv::Scalar(255, 255, 255),8);
//     fillPoly(icirc, {ch}, cv::Scalar(255, 255, 255),8);

     float radius;
     double max_val;
     cv::Point max_loc;


     {

      // Draw on mask
      cv::Mat1b mask(src.rows, src.cols, uchar(0));
      cv::drawContours(mask, contours, i, cv::Scalar(255), cv::FILLED);
  //    cv::cvtColor(src, out, cv::COLOR_GRAY2BGR);

      cv::Mat1f dt;
      cv::distanceTransform(mask, dt, cv::DIST_L2, 5, cv::DIST_LABEL_PIXEL);

      //    cv::Mat3b out;
      //    cv::cvtColor(src, out, cv::COLOR_GRAY2BGR);

      cv::minMaxLoc(dt, nullptr, &max_val, nullptr, &max_loc);

      // Output image
  //    cv::Mat3b out;
      cv::circle(icirc, max_loc, max_val, cv::Scalar(0, 155, 120));

      cv::Mat overlay;
      double alpha = 0.3;

      // copy the source image to an overlay
      icirc.copyTo(overlay);

      cv::circle(overlay, max_loc, max_val, cv::Scalar(250, 55, 20), cv::FILLED);

      cv::addWeighted(overlay, alpha, icirc, 1 - alpha, 0, icirc);
//      cv::addWeighted(icirc, 0.5,
//       , cv::FILLED), 0.5, 0.5, icirc);


     }


     cv::Point2f mcenter;

     {
      cv::Moments moments = cv::moments(c);
      float center_x = moments.m10/moments.m00;
      float center_y = moments.m01/moments.m00;

      mcenter = cv::Point2f(center_x, center_y);

      cv::Point2f center; //center_x, center_y);


      cv::minEnclosingCircle(c, center, radius);

      double c_to_mc = cv::norm(mcenter - center);
      double c_to_x = cv::norm( (cv::Point2f) max_loc - center);
      double mc_to_x = cv::norm( (cv::Point2f) max_loc - mcenter);

      qDebug() << "c_to_mc = " << c_to_mc;
      qDebug() << "c_to_x = " << c_to_x;
      qDebug() << "mc_to_x = " << mc_to_x;


      double ic_ratio = max_val / radius;
      qDebug() << "ic ratio = " << ic_ratio;

      if(ic_ratio > 1)
        cv::circle(icirc, center, radius, cv::Scalar(60, 235, 80));

      else
        cv::circle(icirc, center, radius, cv::Scalar(0, 0, 255 * ic_ratio));
//        cv::circle(icirc, center, radius, cv::Scalar(80, 60, 205));

  //center_x, center_y = (int(M[“m10”] / M[“m00”]), int(M[“m01”] / M[“m00”]))

     }


     {

//      cv::Mat1b contour_mask(canny_output.rows, canny_output.cols, uchar(0));
      cv::Mat contour_mask = cv::Mat::zeros(src.size(), CV_8UC1);
      cv::drawContours(contour_mask, acontours, i, cv::Scalar::all(255), cv::FILLED);

//      cv::Mat temp = cv::Mat::zeros( canny_output.size(), CV_8UC3 );
//      cv::Mat temp;
      //drawContours( temp, contours, i, cv::Scalar(255, 255, 255), 1, 8, hierarchy, INT_MAX, cv::Point(-1 ,-1) );
//      fillPoly(colorsh, {ch}, cv::Scalar(255, 255, 255), 8);

      cv::Scalar contour_mean = cv::mean(src, contour_mask);

      double B = contour_mean[0];
      double G = contour_mean[1];
      double R = contour_mean[2];

//      cv::Scalar_<double> mn = cv::mean(canny_output, mask);
      drawContours( colorsh, acontours, i, cv::Scalar(B, G, R), cv::FILLED);


//      fillPoly(colorsh, {ch}, mn, 8);


//      cv::Mat temp = cv::Mat::zeros( canny_output.size(), CV_8UC3 );
//      fillPoly(temp, {ch}, cv::Scalar(255, 255, 255),8);
//      cv::Scalar_<double> mn = cv::mean(temp, canny_output);
//      cv::Vec3b color = canny_output.at<cv::Vec3b>(mcenter);
//      fillPoly(colorsh, {ch}, color, 8);



     }


     if(ms > 1)
     {
      if(ms > 255)
         ms = 255;
      fillPoly(apoly, {ca}, cv::Scalar(ms, 255, 255),8);
     }
     else
     {
      fillPoly(apoly, {ca}, cv::Scalar(255, 255, 255 * ms),8);
     }



//     cv::Mat dist;
//     cv::distanceTransform(ch, ,dist, DIST_L2,5,CV_8U);

//     drawContours( poly, contours, i ,color, 1, 8, hierarchy, INT_MAX, cv::Point(-1 ,-1) );

    }




//    cv::Mat1b icirc(src.rows, src.cols, uchar(0));
//    cv::drawContours(icirc, hcontours, 0, cv::Scalar(255), cv::FILLED);

//    // Distance Trasnsform
//    cv::Mat1f dt;
//    cv::distanceTransform(icirc, dt, cv::DIST_L2, 5, cv::DIST_LABEL_PIXEL);

//    // Find max value
//    double max_val;
//    cv::Point max_loc;
//    cv::minMaxLoc(dt, nullptr, &max_val, nullptr, &max_loc);

//    // Output image
////    cv::Mat3b out;
////    cv::cvtColor(src, out, cv::COLOR_GRAY2BGR);
//    cv::circle(icirc, max_loc, max_val, cv::Scalar(0, 255, 0));

//    _imshow(icirc, {});

//     dilate1 = cv2.dilate(dilate,kernel,iterations = 1)

 //   dilate1 = cv2.morphologyEx(dilate1, cv2.MORPH_OPEN, kernel)


//      fillPoly(poly, contours, cv::Scalar(100, 40, 200),8);

    //imshow( drawing );
}

QLabel* _imshow_gray(const cv::Mat& src, QString title)
{
// cv::Mat mat;
// cv::cvtColor(src, mat, cv::COLOR_BGR2RGB);

 // image is created according to Mat dimensions
 QImage* image = new QImage(src.size().width, src.size().height, QImage::Format_Grayscale8);

 // Copy cv::Mat to QImage
 memcpy(image->scanLine(0), src.data, static_cast<size_t>(image->width() * image->height() * src.channels()));

 // Display the QImage in a QLabel
 QLabel* label = new QLabel;
 label->setPixmap(QPixmap::fromImage(*image));

// label->setText(title);

 //label->show();

 return label;
}


int main(int argc, char *argv[])
{
 QApplication qapp(argc, argv);

 cv::Mat src = cv::imread("../mask/img.jpg");

 QLabel* l1 = _imshow(src, "l1");

 l1->show();


// cv::cvtColor( src, src_gray, cv::COLOR_BGR2GRAY );
// blur( src_gray, src_gray, cv::Size(3,3) );

// QLabel* l2 = _imshow_gray(src_gray);

//  l1->show();
//  l2->show();


 cv::Mat drawing;
 cv::Mat hpoly;
 cv::Mat apoly;
 cv::Mat icirc;
 cv::Mat colorsh;

 thresh_callback(0, 0, src, drawing, hpoly, apoly, icirc, colorsh);

 QLabel* l2 = _imshow(colorsh, "l2");

 l2->show();



 QLabel* l3 = _imshow(icirc, "l3");

 l3->show();


// QLabel* l3 = _imshow(drawing, "l3");

// l3->show();

// cv::Mat drawing_gray;

//  cv::cvtColor( drawing, drawing_gray, cv::COLOR_BGR2GRAY );

  QLabel* l4 = _imshow(drawing, "l4");

  l4->show();

  QLabel* l5 = _imshow(hpoly, "l5");

  l5->show();

  QLabel* l6 = _imshow(apoly, "l5");

  l6->show();

 return qapp.exec();

// l1->show();
// l2->show();


// const int max_thresh = 255;
// //createTrackbar( "Canny thresh:", source_window, &thresh, max_thresh, thresh_callback );
// thresh_callback( 0, 0 );
// //cv::waitKey();

// imshow(src);

//// const char* source_window = "Source";

//// namedWindow( source_window );
//// imshow( source_window, src );


//// cv::cvtColor(img, img, cv::COLOR_BGR2GRAY); //..cv::COLOR_BGR2RGB);

//// cv::Mat img0;
//// cv::GaussianBlur(img, img0, {15,15}, 30);

//// cv::Mat img1;
//// cv::Canny(img0, img1, 50, 50);

//// int x;
////
// // cv::findContours(img1, x, x, x);

////   InputArray image, OutputArrayOfArrays contours,
////                               int mode, int method, Point offset = Point());

// return qapp.exec();

}
#endif // hide

