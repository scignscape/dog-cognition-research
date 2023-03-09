

//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef DHAX_VIDEO_PLAYER_DIALOG__H
#define DHAX_VIDEO_PLAYER_DIALOG__H



//#include "OpenShot.h"
//#include "FFmpegReader.h"

#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QVideoWidget>

#include <QApplication>

#include <QApplication>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QPushButton>
#include <QUrl>
#include <QVBoxLayout>
#include <QVideoWidget>

#include <QVideoProbe>
#include <QVideoFrame>

#include <QDebug>

#include <QLabel>


#include <QFrame>
#include <QDialog>
#include <QPushButton>
#include <QHBoxLayout>

#include <QDialogButtonBox>

#include <QRubberBand>

#include "accessors.h"
#include "global-types.h"


class DHAX_Video_Player_Frame;



class DHAX_Video_Player_Dialog : public QDialog
{
 Q_OBJECT

 QVBoxLayout* main_layout_;

 QDialogButtonBox* button_box_;
 QPushButton* button_suspend_;
 QPushButton* button_save_ok_;
 QPushButton* button_cancel_close_;

 QPoint last_smaller_screen_position_;
 QSize last_smaller_size_;
 QSize last_full_size_;


 DHAX_Video_Player_Frame* player_;

 QRubberBand* scene_camera_view_geometry_rubber_band_;

 void check_adjust_size(QSize sz, int height_margin);

 QRect first_video_capture_position_;
 QRect current_scene_camera_view_geometry_;

 u1 annotation_settings_;

 void reset_scene_camera_view_geometry(QResizeEvent* resize_event, QMoveEvent* move_event);

 void resizeEvent(QResizeEvent* resize_event) Q_DECL_OVERRIDE;
 void moveEvent(QMoveEvent* move_event) Q_DECL_OVERRIDE;


public:

 enum Annotation_Settings { No_Annotations, Load_Annotations,
   Load_Annotations_With_Pause, Load_Annotations_Manually,
   Video_Series
 };

 DHAX_Video_Player_Dialog(Annotation_Settings s, QWidget* parent = nullptr);


 ACCESSORS__RGET(QRect ,first_video_capture_position)
 ACCESSORS__RGET(QRect ,current_scene_camera_view_geometry)


 Annotation_Settings get_annotation_settings()
 {
  return (Annotation_Settings) annotation_settings_;
 }

 void play_local_video(QString file_path, QString annotations_file = {});

 void play_local_videos(QStringList paths, QString annotations_template_file = {});
 void play_local_videos(QList<QPair<QString, QString>> paths, QString annotations_template_file = {});

 void halt();
 void halt_and_close()
 {
  halt(); close();
 }

 void recenter();

//public Q_SLOTS:

// void scene_camera_view_geometry_updated();

Q_SIGNALS:

 void show_video_frame_requested(QString file_path);

 void scene_camera_view_geometry_updated();

// void accept();
// void reject();


// void restart_requested();
// void pause_requested();
// void resume_requested();


};


#endif // DHAX_VIDEO_PLAYER_DIALOG__H


//#include "ve-frame.h"


//#include <QDebug>

//VE_Frame::VE_Frame(QWidget* parent)
//  :  QFrame(parent)
//{
// main_layout_ = new QHBoxLayout;

// restart_button_ = new QPushButton("<", this);
// pause_button_ = new QPushButton("=", this);
// resume_button_  = new QPushButton(">", this);

// main_layout_->addStretch();
// main_layout_->addWidget(restart_button_);
// main_layout_->addWidget(pause_button_);
// main_layout_->addWidget(resume_button_);

// setLayout(main_layout_);

// connect(pause_button_, &QPushButton::clicked,
//   this, &VE_Frame::pause_requested);

// connect(resume_button_, &QPushButton::clicked,
//   this, &VE_Frame::resume_requested);

// connect(restart_button_, &QPushButton::clicked,
//   this, &VE_Frame::restart_requested);


//}

#ifdef HIDE

#include "ve-frame.h"

#include "video-frame-grabber.h"

class VideoWidgetButton: public QWidget
{
 //    QPushButton *btn;
 VE_Frame* ve_frame_;

 QVideoWidget *vw;
 QMediaPlayer *player;

 QVideoProbe* video_probe_;

 QVideoFrame current_qvf_;

// VideoFrameGrabber* video_frame_grabber_;

// openshot::FFmpegReader* reader_;//("/home/nlevisrael/gits/ctg-temp/stella/videos/test.mp4");

 QUrl current_url_;
 QString current_path_;

// r.Open(); // Open the reader
// // Get frame number 1 from the video

// std::shared_ptr<openshot::Frame> f = r.GetFrame(1);




public:

 VideoWidgetButton(QWidget *parent=Q_NULLPTR):QWidget(parent)
 {
  setLayout(new QVBoxLayout);
  layout()->setContentsMargins(0, 0, 0, 0);

  vw = new QVideoWidget(this);

  //        btn = new QPushButton(this);
  //        btn->setText("tux.jpeg");
  //        btn->resize(QSize(128, 128));
  //        btn->setIconSize(QSize(128, 128));

  ve_frame_ = new VE_Frame;

  layout()->addWidget(vw);
  layout()->addWidget(ve_frame_);

//  video_frame_grabber_ = new VideoFrameGrabber(this);

  player = new QMediaPlayer(this);
  player->setVideoOutput(vw);
//  player->setVideoOutput(video_frame_grabber_);

  video_probe_ = new QVideoProbe;

  if(video_probe_->setSource(player))
  {
   qDebug() << "probe ok";
  }
  else
  {
   qDebug() << "probe bad";
  }


  connect(video_probe_, &QVideoProbe::videoFrameProbed, [this](QVideoFrame qvf)
//  connect(video_frame_grabber_, &VideoFrameGrabber::frameAvailable, [this](QImage frame_image)
  {
   qint64 st = qvf.startTime();

   qint64 fn = st/40000;

   qDebug() << fn;

   current_qvf_ = qvf;

//   QImage frame_image = qvf.image();

//   QLabel* l = new QLabel;
//   l->setPixmap(QPixmap::fromImage(frame_image));
//   l->show();

  });

  connect(ve_frame_, &VE_Frame::pause_requested, [this]()
  {
//      qDebug()<<"p clicked";
   player->pause();

   qDebug() << "pos: " << player->position();

   QImage frame_image = current_qvf_.image();

   QLabel* l = new QLabel;
   l->setPixmap(QPixmap::fromImage(frame_image));
   l->show();


//   video_frame_grabber_->p

//   video_probe_->startTimer();

//   f->Display();

  });

  connect(ve_frame_, &VE_Frame::resume_requested, [this]()
  {
//      qDebug()<<"r clicked";
   player->play();
  });

  connect(ve_frame_, &VE_Frame::restart_requested, [this]()
  {
//      qDebug()<<"r clicked";
   player->setPosition(0);
   player->play();
  });


//  QMediaPlaylist *playList = new QMediaPlaylist(this);
//  playList->addMedia(QUrl::fromLocalFile("/home/nlevisrael/gits/ctg-temp/stella/videos/test.webm"));
//  playList->setPlaybackMode(QMediaPlaylist::Loop);
//  player->setPlaylist(playList);


//  current_path_ = "/home/nlevisrael/gits/ctg-temp/stella/videos/test.mp4";
  current_path_ = "/home/nlevisrael/gits/ctg-temp/stella/videos/test.mkv";

  current_url_ =  QUrl::fromLocalFile(current_path_);

  ve_frame_->show();


  player->setMedia(current_url_);
  player->play();





 }

protected:

 void resizeEvent(QResizeEvent *ev)
 {
//  btn->move(rect().bottomRight()-btn->rect().bottomRight());
  ve_frame_->move(rect().bottomRight() - ve_frame_->rect().bottomRight());
  return QWidget::resizeEvent(ev);
 }
};

#include "ZmqLogger.h"

int main(int argc, char *argv[])
{
// openshot::ZmqLogger* zmql = openshot::ZmqLogger::Instance();

// zmql->Path("/home/nlevisrael/gits/ctg-temp/stella/videos/log.txt");

// zmql->Enable(true);

 QApplication a(argc, argv);
 VideoWidgetButton w;
 w.resize(640, 480);
 w.show();
 return a.exec();
}

int main1()
{
 // Create a reader for a video
}




int main2(int argc, char* argv[])
{
 QApplication* app = new QApplication(argc, argv);
 QMediaPlayer* player = new QMediaPlayer(nullptr, QMediaPlayer::VideoSurface);

 // QMediaPlaylist* playlist = new QMediaPlaylist(player);
 // playlist->addMedia(QUrl("/home/nlevisrael/gits/ctg-temp/stella/videos/test.mp4"));
 // playlist->addMedia(QUrl("http://example.com/myclip2.mp4"));

 QVideoWidget* videoWidget = new QVideoWidget;
 player->setVideoOutput(videoWidget);

 videoWidget->show();
 player->setMedia(QUrl::fromLocalFile("/home/nlevisrael/gits/ctg-temp/stella/videos/test.mp4"));
 player->play();

 app->exec();

}


//reader_->Open(); // Open the reader
////   // Get frame number 1 from the video

////   std::shared_ptr<openshot::Frame> f = reader_->GetFrame(player->position());
//std::shared_ptr<openshot::Frame> f = reader_->GetFrame(3);

//std::shared_ptr<QImage> frame_image = f->GetImage();

#endif // hide
