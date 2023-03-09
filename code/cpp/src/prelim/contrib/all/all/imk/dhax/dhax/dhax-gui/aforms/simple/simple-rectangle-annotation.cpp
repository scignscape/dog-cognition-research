
#include "simple-rectangle-annotation.h"

#include <QPainter>

#include <QDebug>

#include <QWheelEvent>

#include "global-types.h"


Simple_Rectangle_Annotation::Simple_Rectangle_Annotation(DHAX_Mouse_Interaction_Data& mouse_interaction_data,
   const QPointF& sc, QWidget* p)
 : Simple_Annotation_Base(mouse_interaction_data, sc, p), measurements_(nullptr)
{
 scaffold_.setTopLeft(sc);
 scaffold_.setBottomRight(sc);
}

u2 _diag(QRectF& r)
{
 return (u2) (((r.width() * r.width()) + (r.height() * r.height())) / 2);
}

Simple_Rectangle_Annotation::Measurements& Simple_Rectangle_Annotation::get_measurements()
{
 if(!measurements_)
 {
  QRectF imn = containing_image_->rect().normalized();
  QRectF tl = imn, tr = imn, bl = imn, br = imn;

  QRectF sn = scaffold_.normalized();
  u2 idiag = _diag(imn) + 1;

  u2 sw = sn.width();
  u2 sh = sn.height();
  u2 iw = imn.width();
  if(iw < sw) iw = sw;
  u2 ih = imn.height();
  if(ih < sh) ih = sh;

  tl.setBottomRight(sn.topLeft());
  tr.setBottomLeft(sn.topRight());
  bl.setTopRight(sn.bottomLeft());
  br.setTopLeft(sn.bottomRight());

  u2 margins [8] {
    (u2) tl.width(),  // left
    _diag(tl), // tl
    (u2) tl.height(),  // top
    _diag(tr), // tr
    (u2) tr.width(),  // right
    _diag(br), // br
    (u2) bl.height(),  // bottom
    _diag(bl), // bl
  };

  if(sw == 0)
    measurements_ = new Measurements{
      sw, sh, (u2) (sh + sh), // perimeter
      iw, ih, (u2) (iw + iw + ih + ih), // image perimeter
      0, // area
      (u4) (iw * ih), // image area
      0, // wh
      0, // hw
      ((r8) iw / ih), // wh image
      ((r8) ih / iw), // hw image
      0, // width against image
      ((r8) sh / ih), // height against image
      0, 0, // perimeter and area against image
      {margins[0],margins[1],margins[2],margins[3],margins[4],margins[5],margins[6],margins[7]},
      {
       ((r8) margins[0] / (iw + 1)),
       ((r8) margins[1] / idiag),
       ((r8) margins[2] / (ih + 1)),
       ((r8) margins[3] / idiag),
       ((r8) margins[4] / (iw + 1)),
       ((r8) margins[5] / idiag),
       ((r8) margins[6] / (ih + 1)),
       ((r8) margins[7] / idiag)
      }
    };
    //measurements_->margins = margins;
  else if(sh == 0)
    measurements_ = new Measurements{
      sw, sh, (u2) (sw + sw), // perimeter
      iw, ih, (u2) (iw + iw + ih + ih), // image perimeter
      0, // area
      (u4) (iw * ih), // image area
      0, // wh
      0, // hw
      ((r8) iw / ih), // wh image
      ((r8) ih / iw), // hw image
      ((r8) sw / iw), // width against image
      0, // height against image
      0, 0, // perimeter and area against image
      {margins[0],margins[1],margins[2],margins[3],margins[4],margins[5],margins[6],margins[7]},
      {
       ((r8) margins[0] / (iw + 1)),
       ((r8) margins[1] / idiag),
       ((r8) margins[2] / (ih + 1)),
       ((r8) margins[3] / idiag),
       ((r8) margins[4] / (iw + 1)),
       ((r8) margins[5] / idiag),
       ((r8) margins[6] / (ih + 1)),
       ((r8) margins[7] / idiag)
      }
    };
  else
    measurements_ = new Measurements{
      sw, sh, (u2) (sw + sw + sh + sh), // perimeter
      iw, ih, (u2) (iw + iw + ih + ih), // image perimeter
      (u4) (sw * sh), // area
      (u4) (iw * ih), // image area
      ((r8) sw / sh), // wh
      ((r8) sh / sw), // hw
      ((r8) iw / ih), // wh image
      ((r8) ih / iw), // hw image
      ((r8) sw / iw), // width against image
      ((r8) sh / ih), // height against image
      0, 0, // area and perimeter against image
      {margins[0],margins[1],margins[2],margins[3],margins[4],margins[5],margins[6],margins[7]},
      {
       ((r8) margins[0] / (iw + 1)),
       ((r8) margins[1] / idiag),
       ((r8) margins[2] / (ih + 1)),
       ((r8) margins[3] / idiag),
       ((r8) margins[4] / (iw + 1)),
       ((r8) margins[5] / idiag),
       ((r8) margins[6] / (ih + 1)),
       ((r8) margins[7] / idiag)
      }
     };

  if(measurements_->image_perimeter > 0)
    measurements_->perimeter_against_image = (r8) measurements_->perimeter / measurements_->image_perimeter;

  if(measurements_->image_area > 0)
    measurements_->area_against_image = (r8) measurements_->area / measurements_->image_area;
 };

 return *measurements_;
}

QRectF Simple_Rectangle_Annotation::against_image_coords()
{
 Simple_Rectangle_Annotation::Measurements& ms = get_measurements();
 return {ms.margins_against_image[Directions::Left], ms.margins_against_image[Directions::Top],
   ms.width_against_image, ms.height_against_image};
}

template<typename COUNTS_Type, typename INDICES_Type, typename RET_Type = u1>
RET_Type _maxes_averaged(COUNTS_Type& counts, INDICES_Type& indices)
{
 auto it = std::max_element(counts.begin(), counts.end());
 while (it != counts.end())
 {
  indices.push_back(std::distance(counts.begin(), it));
  it = std::find(std::next(it), counts.end(), *it);
 }

 RET_Type count = indices.size();
 if(count == 0)
   return 0;
 if(count == 1)
   return indices[0];
 n8 result = std::accumulate(indices.begin(), indices.end(), 0);
 return (RET_Type) result / count;
}

QColor Simple_Rectangle_Annotation::get_occurant_color_mean(u1 number_of_iterations, u1 rounding_factor)
{
 QVector<u4> red_counts(256);
 QVector<u4> green_counts(256);
 QVector<u4> blue_counts(256);

 QVector<u4> rgb[3]{red_counts, green_counts, blue_counts};

 get_occurants_vectors(rgb);

 return get_occurant_color_mean(rgb, number_of_iterations, rounding_factor);
}

void Simple_Rectangle_Annotation::get_occurants_vectors(QVector<u4> (&result) [3])
{
 QRectF ai = against_image_coords();

 u2 x1 = ai.topLeft().x() * containing_image_->width();
 u2 y1 = ai.topLeft().y() * containing_image_->height();

 u2 x2 = ai.bottomRight().x() * containing_image_->width();
 u2 y2 = ai.bottomRight().y() * containing_image_->height();

 QRgb* image_line;


 for(u2 y = y1 ; y < y2 ; ++y)
 {
  image_line = (QRgb *) containing_image_->scanLine(y);
  for(u2 x = x1; x < x2 ; ++x)
  {
   QColor c(image_line[x]);
//   qDebug() << "x = " << x << ", y = " << y << ": " << qRed(image_line[x]) << " | "
//     << qGreen(image_line[x]) << "|" << qBlue(image_line[x]);
   ++result[0][qRed(image_line[x])];
   ++result[1][qGreen(image_line[x])];
   ++result[2][qBlue(image_line[x])];
  }
 }
}

QVector<u4> _simplify_by_rounding(const QVector<u4>& original, u1 rounding_factor)
{
 if(rounding_factor <= 1)
   return original;

 u1 size = original.size() / rounding_factor + (bool) original.size() % rounding_factor;
 QVector<u4> result(size);

 auto it = original.begin();
 s2 rest = 255;
 for(u1 index = 0; //oindex = 0,
      //rest = 255;
   rest > 0; //oindex += rounding_factor,
     rest -= rounding_factor, ++index)
 {
  u1 gap = qMin(rounding_factor, (u1) rest);
  if(index > 0)
    it = std::next(it, gap);
  result[index] = std::accumulate(it, std::next(it, gap), (u4) 0);
 }
 return result;
}

QColor Simple_Rectangle_Annotation::get_occurant_color_mean(QVector<u4> rgb[3], u1 number_of_iterations, u1 rounding_factor)
{
 //QVector<int> MainWindow::get_mean_rgb_for_img(const QImage img){

 static QVector<u1> maxes;

 static auto cut = [](QVector<u4>& source)
 {
  for(u1 index : maxes)
  {
   source[index] = 0;
  }
 };

 QVector<u1> red_max_occurants(number_of_iterations);
 QVector<u1> green_max_occurants(number_of_iterations);
 QVector<u1> blue_max_occurants(number_of_iterations);

 QVector<u4> red_counts = _simplify_by_rounding(rgb[0], rounding_factor);
 QVector<u4> green_counts = _simplify_by_rounding(rgb[1], rounding_factor);
 QVector<u4> blue_counts = _simplify_by_rounding(rgb[2], rounding_factor);

 for(u1 i = 0; i < number_of_iterations; ++i)
 {
  u1 red_max_occurant = _maxes_averaged(red_counts, maxes);
  red_max_occurants[i] = red_max_occurant;
  cut(red_counts);
  maxes.clear();
  u1 green_max_occurant = _maxes_averaged(green_counts, maxes);
  green_max_occurants[i] = green_max_occurant;
  cut(green_counts);
  maxes.clear();
  u1 blue_max_occurant = _maxes_averaged(blue_counts, maxes);
  blue_max_occurants[i] = blue_max_occurant;
  cut(blue_counts);
  maxes.clear();
 }

 u1 red_mean =
   (std::accumulate(red_max_occurants.begin(), red_max_occurants.end(), (u4) 0) / number_of_iterations) * rounding_factor;
 u1 green_mean =
   (std::accumulate(green_max_occurants.begin(), green_max_occurants.end(), (u4) 0) / number_of_iterations) * rounding_factor;
 u1 blue_mean =
   (std::accumulate(blue_max_occurants.begin(), blue_max_occurants.end(), (u4) 0) / number_of_iterations) * rounding_factor;

 return QColor(red_mean, green_mean, blue_mean);
}

QColor Simple_Rectangle_Annotation::get_additive_color_mean(QVector<u4> rgb[3])
{
 n8 sums [3] {0};
 n8 counts [3] {0};

 for(u2 index = 0; index < 256; ++index)
   for(u1 c = 0; c < 3; ++c)
   {
    sums[c] += rgb[c][index] * index;
    counts[c] += rgb[c][index];
   }

 return QColor((int) sums[0] / counts[0], (int) sums[1] / counts[1], (int) sums[2] / counts[2]);
}
