

//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef DHAX_VIDEO_PLAYER_FRAME__H
#define DHAX_VIDEO_PLAYER_FRAME__H



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

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QTimer>

#include "global-types.h"

#include "accessors.h"

class DHAX_Video_Navigation_Frame;
class DHAX_Video_Annotation_Set;
class DHAX_Video_Annotation;


class DHAX_Video_Player_Frame : public QFrame
{
 Q_OBJECT

 CLASS_NAME_FN (auto)

 QVBoxLayout* main_layout_;


 DHAX_Video_Navigation_Frame* navigation_;

 DHAX_Video_Annotation_Set* annotation_set_;

// QVideoWidget *video_widget_;

 QGraphicsVideoItem* video_item_;
 QGraphicsView* graphics_view_;
 QGraphicsScene* graphics_scene_;

 QGraphicsTextItem* frame_number_text_;
 QGraphicsRectItem* frame_number_text_background_;


 QMediaPlayer* media_player_;

 QVideoProbe* video_probe_;

 QVideoFrame current_video_frame_;

 u2 current_frame_count_;

 QUrl current_url_;
 QString current_path_;

 QSize video_size_;
 QSizeF last_smaller_size_;

 int need_video_size_;

 QGraphicsRectItem* full_size_rect_item_;
 QGraphicsRectItem* smaller_size_rect_item_;

 QGraphicsRectItem* annotations_rect_item_;

 u2 replay_count_;

 QSize last_larger_video_size_;
 QSizeF last_larger_graphics_view_size_;

 QRectF initial_smaller_scene_rect_;

 QRect scene_camera_view_geometry_;

 QVector<DHAX_Video_Annotation*> current_paused_annotations_;

 QList<DHAX_Video_Annotation*> current_reffed_annotations_list_;
 u2 current_reffed_annotations_index_;

 QTimer* current_pause_timer_;

 QStringList annotations_files_;

 u2 current_playlist_index_;

 QString annotations_template_file_;

//?protected:

 void run_pause_reffed_annotations(DHAX_Video_Annotation* prior,
   u2 current_ellapsed_time, u2 index);

 void resizeEvent(QResizeEvent* event);
 void reset_graphics_scene_rect();
 void update_frame_number_text();

 void init_annotations();

 void connect_video_probe();

 void* make_scene_annotation(DHAX_Video_Annotation* dva);
 void* make_scene_text_annotation(DHAX_Video_Annotation* dva);
 void* make_scene_arrow_annotation(DHAX_Video_Annotation* dva);
 void* make_scene_circled_text_annotation(DHAX_Video_Annotation* dva);
 void* make_scene_pixmap_annotation(DHAX_Video_Annotation* dva);

 void handle_pause_annotation(DHAX_Video_Annotation* dva);


 template<typename T>
 T* make_or_show_scene_annotation(DHAX_Video_Annotation* dva);

 QRectF video_rect_;
 void reposition_larger_annotations_rect_item();
 void reposition_smaller_annotations_rect_item();

 QRectF graphics_view_visible_rect();

// template <typename ...Params>
// void reset_current_pause_timer(Params&& ...params)
// {
//  if(current_pause_timer_)
//    delete current_pause_timer_;
// }

// template<typename FN_Type>

 void reset_current_pause_timer(u4 interval)
 {
  current_pause_timer_ = new QTimer(this);
  current_pause_timer_->setInterval(interval);
  current_pause_timer_->setSingleShot(true);
 }

 template<typename FN_Type>
 void this_reset_current_pause_timer(u4 interval, FN_Type fn)
 {
  reset_current_pause_timer(interval);
  connect(current_pause_timer_, &QTimer::timeout, this, fn);
  current_pause_timer_->start();
 }

 template<typename FN_Type>
 void reset_current_pause_timer(u4 interval, FN_Type fn)
 {
  reset_current_pause_timer(interval);
  connect(current_pause_timer_, &QTimer::timeout, fn);
  current_pause_timer_->start();
 }

 void resume_from_pause_timer();

public:

 DHAX_Video_Player_Frame(QWidget* parent = nullptr);

 ACCESSORS(QRect ,scene_camera_view_geometry)
 ACCESSORS(QString ,annotations_template_file)

 QRect get_scene_camera_view_geometry();

 struct _show_hide {
  void (*show)(void*);
  void (*hide)(void*);
 };

 template<typename GRAPHICS_Type>
 static _show_hide* init_show_hide()
 {
  return new _show_hide { [](void* ptr)
   {
    ((GRAPHICS_Type*) ptr) -> show();
   }, [] (void* ptr)
   {
    ((GRAPHICS_Type*) ptr) -> hide();
   }
  };
 }


 void play_local_video(QString file_path, QString annotations_file);
 void play_local_videos(QList<QPair<QString, QString>> paths);

 void reset_to_full_size();
 void reset_to_smaller_size();

 void confirm_video_size();

 void pause();
 void resume();

 void recenter();

 QSize get_navigation_size();

 void handle_send_video_frame_to_main_window(QLabel* l);

 void halt();

//public Q_SLOTS:

 void load_annotations();
 void load_annotations_file(QString annotations_file);


 void reset_annotation();

//public Q_SLOTS:

 void handle_video_frame(const QVideoFrame& qvf);

Q_SIGNALS:

 void video_size_established(QSize);
 void full_video_size_requested(QSize);
 void smaller_video_size_requested(QSize);
 void show_video_frame_requested(QString file_path);

// void restart_requested();
// void pause_requested();
// void resume_requested();


};


#endif // DHAX_VIDEO_PLAYER_FRAME__H


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
