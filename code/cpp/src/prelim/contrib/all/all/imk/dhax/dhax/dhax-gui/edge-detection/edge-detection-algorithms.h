#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "global-types.h"

#include <QImage>


void gaussian_kernel(float);
void magnitude(QImage&, const QImage&, const QImage&);

QImage convolution(const auto&, const QImage&, QImage::Format out_format,
  u1 blur_factor, QPair<QColor, QColor>* poles);

QImage canny(const QImage&, float, float, float, QImage::Format out_format, u1 blur_factor, QPair<QColor, QColor>* poles);

QImage sobel(const QImage&, QImage::Format out_format, u1 blur_factor, QPair<QColor, QColor>* poles);
QImage prewitt(const QImage&, QImage::Format out_format, u1 blur_factor, QPair<QColor, QColor>* poles);
QImage roberts(const QImage&,QImage::Format out_format,  u1 blur_factor, QPair<QColor, QColor>* poles);
QImage scharr(const QImage&, QImage::Format out_format, u1 blur_factor, QPair<QColor, QColor>* poles);

QImage hysteresis(const QImage&, float, float);

#endif // ALGORITHMS_H
