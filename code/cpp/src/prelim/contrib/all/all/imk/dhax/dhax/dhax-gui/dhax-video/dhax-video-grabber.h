

//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef DHAX_VIDEO_GRABBER__H
#define DHAX_VIDEO_GRABBER__H

#include <QtWidgets>

#include <QVideoFrame>
#include <QVideoSurfaceFormat>
#include <QAbstractVideoSurface>


class DHAX_Video_Grabber : public QAbstractVideoSurface
{
 Q_OBJECT

public:

 DHAX_Video_Grabber(QWidget *widget, QObject *parent = 0);

 QList<QVideoFrame::PixelFormat> supportedPixelFormats(
   QAbstractVideoBuffer::HandleType handleType = QAbstractVideoBuffer::NoHandle) const;
 bool isFormatSupported(const QVideoSurfaceFormat &format) const;

 bool start(const QVideoSurfaceFormat &format);
 void stop();

 bool present(const QVideoFrame &frame);

 QRect videoRect() const { return targetRect; }
 void updateVideoRect();

 void paint(QPainter *painter);

private:
 QWidget *widget;
 QImage::Format imageFormat;
 QRect targetRect;
 QSize imageSize;
 QRect sourceRect;
 QVideoFrame currentFrame;

Q_SIGNALS:
 void frameAvailable(QImage frame);
};

#endif //DHAX_VIDEO_GRABBER__H
