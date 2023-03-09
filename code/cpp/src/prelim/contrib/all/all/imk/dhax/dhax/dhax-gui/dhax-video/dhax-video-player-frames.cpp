

//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "dhax-video-player-frame.h"
#include "dhax-video-navigation-frame.h"

#include "dhax-video-annotation-set.h"
#include "dhax-video-annotation.h"

#include <QGraphicsVideoItem>

#include <QMenu>
#include <QStyle>
#include <QDir>

#include <QScrollBar>

#include "styles.h"

#include "aforms/rotateable-arrow-annotation.h"

#define INIT_SHOW_HIDE(ty) \
DHAX_Video_Player_Frame::_show_hide* ty##_show_hide \
  = DHAX_Video_Player_Frame::init_show_hide<ty>();


void show_hide_hide(DHAX_Video_Annotation* dva)
{
 DHAX_Video_Player_Frame::_show_hide* sh =
   dva->scene_type_data_as<DHAX_Video_Player_Frame::_show_hide>();
 sh->hide(dva->scene_data());
}

void show_hide_show(DHAX_Video_Annotation* dva)
{
 DHAX_Video_Player_Frame::_show_hide* sh =
   dva->scene_type_data_as<DHAX_Video_Player_Frame::_show_hide>();
 sh->show(dva->scene_data());
}


INIT_SHOW_HIDE(QGraphicsTextItem)
INIT_SHOW_HIDE(QGraphicsEllipseItem)
INIT_SHOW_HIDE(QGraphicsPolygonItem)
INIT_SHOW_HIDE(QGraphicsPixmapItem)



DHAX_Video_Player_Frame::DHAX_Video_Player_Frame(QWidget* parent)
  :  QFrame(parent), annotation_set_(nullptr),
     full_size_rect_item_(nullptr), current_pause_timer_(nullptr),
     smaller_size_rect_item_(nullptr), current_reffed_annotations_index_(0),
     replay_count_(0), current_frame_count_(0),
     graphics_view_(nullptr), current_playlist_index_(0)
{
// setLayout(new QVBoxLayout);
// layout()->setContentsMargins(0, 0, 0, 0);

//? video_widget_ = new QVideoWidget(this);

 //        btn = new QPushButton(this);
 //        btn->setText("tux.jpeg");
 //        btn->resize(QSize(128, 128));
 //        btn->setIconSize(QSize(128, 128));


 navigation_ = new DHAX_Video_Navigation_Frame;
 navigation_->setFrameStyle(QFrame::Panel | QFrame::Sunken);

 main_layout_ = new QVBoxLayout;

 main_layout_->setContentsMargins(0, 0, 0, 0);
 main_layout_->setMargin(0);

 graphics_view_ = new QGraphicsView(this);
 graphics_scene_ = new QGraphicsScene(this);
 graphics_view_->setScene(graphics_scene_);
 video_item_ = new QGraphicsVideoItem;
 graphics_scene_->addItem(video_item_);

//? video_item_->setFlags(QGraphicsItem::ItemIsMovable);

//? graphics_view_->setAlignment(Qt::AlignHCenter | Qt::AlignBaseline);

 frame_number_text_ = nullptr;


 graphics_view_->setContextMenuPolicy(Qt::CustomContextMenu);

 connect(graphics_view_, &QGraphicsView::customContextMenuRequested, [this](const QPoint& pos)
 {
  QMenu* menu = new QMenu(this);
  menu->addAction("Load annotations", this, &DHAX_Video_Player_Frame::load_annotations);
  menu->popup(mapToGlobal(pos));
 });


 connect(video_item_,
   &QGraphicsVideoItem::nativeSizeChanged, [this]()
 {
//?  QSize sz = media_player_->media().canonicalResource().resolution();
//?  QSize sz = media_player_->metaData("Resolution").value<QSize>();
  QSizeF szf = video_item_->nativeSize();

  if(szf == QSize(0,0))
  {
   ++replay_count_;
   current_frame_count_ = 0;
  }
  else if(replay_count_ > 0)
  {
   graphics_view_->centerOn(video_item_);
  }


 });

// main_layout_->addWidget(video_widget_);
 main_layout_->addWidget(graphics_view_);
 main_layout_->addWidget(navigation_);

//  video_frame_grabber_ = new VideoFrameGrabber(this);

 media_player_ = new QMediaPlayer(this);
 media_player_->setVideoOutput(video_item_);
// media_player_->setVideoOutput(video_widget_);
//  media_player_->setVideoOutput(video_frame_grabber_);

// connect(media_player_, &QMediaPlayer::metaDataChanged,
//   []()
// {

// });

 connect(media_player_, &QMediaPlayer::stateChanged, [this](QMediaPlayer::State state)
 {
  if(state == QMediaPlayer::StoppedState)
  {
   qDebug() << "stopped";
//   media_player_->setPosition(0);
//   media_player_->play();
   //video_probe_->
  }
 });

 video_probe_ = new QVideoProbe;

 if(video_probe_->setSource(media_player_))
 {
  qDebug() << "probe ok";
 }
 else
 {
  qDebug() << "probe bad";
 }

 connect_video_probe();


 connect(navigation_, &DHAX_Video_Navigation_Frame::grab_frame_requested, [this]()
 {
  pause();

  qDebug() << "pos: " << media_player_->position();
  QImage frame_image = current_video_frame_.image();
  QLabel* l = new QLabel;
  l->setPixmap(QPixmap::fromImage(frame_image));

  l->setContextMenuPolicy(Qt::CustomContextMenu);

  connect(l, &QLabel::customContextMenuRequested, [this, l](QPoint pos)
  {
   QMenu* m = new QMenu;
   m->addAction("Send video frame to main window", [this, l]()
   {
    handle_send_video_frame_to_main_window(l);
   });
   m->popup(pos + l->pos() + QPoint(0,
     QApplication::style()->pixelMetric(QStyle::PM_TitleBarHeight)));
  });

  l->show();
 });

// connect(navigation_, &DHAX_Video_Navigation_Frame::pause_requested, [this]()
// {
//  pause();
//  //      qDebug()<<"p clicked";
// });

 connect(navigation_, &DHAX_Video_Navigation_Frame::pause_requested, this,
   &DHAX_Video_Player_Frame::pause);

 connect(navigation_, &DHAX_Video_Navigation_Frame::resume_requested, this,
   &DHAX_Video_Player_Frame::resume);

 connect(navigation_, &DHAX_Video_Navigation_Frame::restart_requested, [this]()
 {
//      qDebug()<<"r clicked";
  media_player_->setPosition(0);
  current_frame_count_ = 0;
  update_frame_number_text();
  media_player_->play();
 });

 connect(navigation_, &DHAX_Video_Navigation_Frame::full_size_requested, [this]()
 {
  reset_to_full_size();
//      qDebug()<<"r clicked";
 });

 connect(navigation_, &DHAX_Video_Navigation_Frame::smaller_size_requested, [this]()
 {
  reset_to_smaller_size();
 });

 setLayout(main_layout_);

//  QMediaPlaylist *playList = new QMediaPlaylist(this);
//  playList->addMedia(QUrl::fromLocalFile("/home/nlevisrael/gits/ctg-temp/stella/videos/test.webm"));
//  playList->setPlaybackMode(QMediaPlaylist::Loop);
//  media_player_->setPlaylist(playList);


//  current_path_ = "/home/nlevisrael/gits/ctg-temp/stella/videos/test.mp4";


}


void DHAX_Video_Player_Frame::handle_pause_annotation(DHAX_Video_Annotation* dva)
{
 pause();

 QSet<DHAX_Video_Annotation*> qset = annotation_set_->get_anchored_ref_annotations(dva);

 u4 rt = 0;
 u4 rt_pos = 0;

 current_reffed_annotations_index_ = 0;
 current_reffed_annotations_list_.clear();

 if(!qset.isEmpty())
 {
  QList<DHAX_Video_Annotation*> list = qset.toList();

  std::sort(list.begin(), list.end(), [](const DHAX_Video_Annotation* lhs,
    const DHAX_Video_Annotation* rhs) //-> bool
  { return lhs->ref_time_offset() < rhs->ref_time_offset(); });

  for(DHAX_Video_Annotation* dva1 : list)
  {
   make_scene_text_annotation(dva1);
   current_paused_annotations_.push_back(dva1);
   u4 rt = dva1->ref_time_offset();
   if(rt)
   {
    show_hide_hide(dva1);
    current_reffed_annotations_list_.push_back(dva1);
   }
  }
 }

 if(u4 pt = dva->pause_time())
 {
  if(current_reffed_annotations_list_.isEmpty())
    this_reset_current_pause_timer(pt,
     &DHAX_Video_Player_Frame::resume_from_pause_timer);
//?    QTimer::singleShot(pt, this, &DHAX_Video_Player_Frame::resume);
  else
    run_pause_reffed_annotations(nullptr, 0, 0);
 }
}

//pt -= rt;
//QTimer::singleShot(rt, [this, pt]()
//{
// DHAX_Video_Annotation* dva1 = current_reffed_annotations_list_ [current_reffed_annotations_index_];
// show_hide_show(dva1);
////    QTimer::singleShot(pt, this, &DHAX_Video_Player_Frame::resume);
//});

//void DHAX_Video_Player_Frame::reset_current_pause_timer()
//{
// if(current_pause_timer_)
//   delete current_pause_timer_;

// QTimer::singleShot()
//}

void DHAX_Video_Player_Frame::run_pause_reffed_annotations(DHAX_Video_Annotation* prior,
  u2 current_ellapsed_time, u2 index)
{
 if(prior)
 {
  current_ellapsed_time += prior->ref_time_offset();
 }
 if(index == current_reffed_annotations_list_.size())
 {
  DHAX_Video_Annotation* dva0 = prior->ref_annotation();
//  QTimer::singleShot(dva0->pause_time() - current_ellapsed_time, this, &DHAX_Video_Player_Frame::resume);

  this_reset_current_pause_timer(dva0->pause_time() - current_ellapsed_time,
    &DHAX_Video_Player_Frame::resume_from_pause_timer);

 }
 else
 {
  DHAX_Video_Annotation* dva = current_reffed_annotations_list_[index];
  u4 rto = dva->ref_time_offset();

  //?QTimer::singleShot(rto, [this, dva, current_ellapsed_time, index, prior]()

  reset_current_pause_timer(rto, [this, dva, current_ellapsed_time, index, prior]()
  {
   if(prior)
     show_hide_hide(prior);
   show_hide_show(dva);
   run_pause_reffed_annotations(dva, current_ellapsed_time, index + 1);
//?   graphics_view_->update();

 //    QTimer::singleShot(pt, this, &DHAX_Video_Player_Frame::resume);
  });

 }


}


template<typename T>
T* DHAX_Video_Player_Frame::make_or_show_scene_annotation(DHAX_Video_Annotation* dva)
{
 T* result;
 if(dva->scene_data_as(result))
 {
  show_hide_show(dva);
 }
 else
 {
  qDebug() << "inserting annotation for frame " << current_frame_count_;
  qDebug() << *dva;
  result = (T*) make_scene_annotation(dva);
 }
 return result;
}



void DHAX_Video_Player_Frame::handle_video_frame(const QVideoFrame& qvf)
{
 if(need_video_size_)
 {
  --need_video_size_;
  if(media_player_->isMetaDataAvailable())
  {
   video_size_ = media_player_->metaData("Resolution").value<QSize>();
   if(video_size_.isValid())
   {
    need_video_size_ = 0;
    confirm_video_size();

    // //  for setting up the capture ...
    if(current_playlist_index_ == 0)
      pause();

   }
  }
 }

 qint64 st = qvf.startTime();
 qint64 seconds = st/1000;
 qint64 fn = st/40000;


 if(annotation_set_)
 {
  QPair<void*, void*> pr = annotation_set_->get_data_by_end_frame(current_frame_count_);
  if(pr.second)
  {
   ((_show_hide*)pr.first)->hide(pr.second);
  }

//  pr = annotation_set_->get_carried_item_at_frame(current_frame_count_);
//  if(pr.second)
//  {
//   ((_show_hide*)pr.first)->hide(pr.second);
//  }


  DHAX_Video_Annotation* dva = annotation_set_->get_annotation_by_start_frame(current_frame_count_);
  if(dva)
  {
   QGraphicsItem* qgi;
   if(dva->kind() == "text")
   {
//?
//    QString png = dva->get_pdflatex_png();

//    if(png.isEmpty())
      qgi = make_or_show_scene_annotation<QGraphicsTextItem>(dva);
//?
//    else
//      qgi = make_or_show_scene_annotation<QGraphicsPixmapItem>(dva);
   }
   else if(dva->kind() == "pause")
   {
    handle_pause_annotation(dva);
   }
   else //if(dva->kind() == "arrow")
   {
    qgi = make_or_show_scene_annotation<QGraphicsItem>(dva);
   }
//   graphics_scene_->update();
//   graphics_view_->repaint();
//   update();
  }
 }

 ++current_frame_count_;

 static constexpr u2 frame_count_update_rate = 20;
 if((current_frame_count_ % frame_count_update_rate) == 0)
 {
  if(frame_number_text_)
    update_frame_number_text();
 }


//  qDebug() << fn;
 current_video_frame_ = qvf;

//    QSize sz = media_player_->media().canonicalResource().resolution();
//    qDebug() << "size = " << sz;
//    QSize sz1 = media_player_->metaData("Resolution").value<QSize>();
//    qDebug() << "size1 = " << sz1;

//   QImage frame_image = qvf.image();

//   QLabel* l = new QLabel;
//   l->setPixmap(QPixmap::fromImage(frame_image));
//   l->show();

}


void* DHAX_Video_Player_Frame::make_scene_pixmap_annotation(DHAX_Video_Annotation* dva)
{
 QPixmap pxm(dva->get_pdflatex_png());
 QGraphicsPixmapItem* result = graphics_scene_->addPixmap(pxm);
 result->setParentItem(annotations_rect_item_);
 result->setPos(dva->corner_position());
 dva->set_scene_data(result);
 dva->set_scene_type_data(QGraphicsPixmapItem_show_hide);

 if(dva->ending_frame_number() != -1)
   annotation_set_->set_end_frame_data(dva->ending_frame_number(),
   //QGraphicsTextItem_show_hide,
   *dva);

 return result;
}


void* DHAX_Video_Player_Frame::make_scene_text_annotation(DHAX_Video_Annotation* dva)
{
 QGraphicsTextItem* result = graphics_scene_->addText(dva->text());
 result->setParentItem(annotations_rect_item_);
 result->setPos(dva->corner_position());
 result->setHtml(dva->html_text());
 dva->set_scene_data(result);
 dva->set_scene_type_data(QGraphicsTextItem_show_hide);

 if(dva->ending_frame_number() != -1)
   annotation_set_->set_end_frame_data(dva->ending_frame_number(),
   //QGraphicsTextItem_show_hide,
   *dva);

 return result;
}

void* DHAX_Video_Player_Frame::make_scene_circled_text_annotation(DHAX_Video_Annotation* dva)
{
 QGraphicsSimpleTextItem* ti = graphics_scene_->addSimpleText(dva->text());
 ti->setPos(dva->corner_position());
 ti->setText(dva->text());

 QRectF qrf(0, 0, annotation_set_->circled_text_default_width(),
   annotation_set_->circled_text_default_width());

 qrf.moveCenter(dva->corner_position());

 QBrush qbr(annotation_set_->circled_text_default_background_color());
 QPen qpen(QBrush(annotation_set_->circled_text_default_outline_color()),
   annotation_set_->circled_text_default_width());

 QGraphicsEllipseItem* result = graphics_scene_->addEllipse(qrf, qpen, qbr);

 ti->setParentItem(result);
 result->setParentItem(annotations_rect_item_);

 dva->set_scene_data(result);
 dva->set_scene_type_data(QGraphicsEllipseItem_show_hide);

 annotation_set_->set_end_frame_data(dva->ending_frame_number(),
   //?QGraphicsEllipseItem_show_hide,
   *dva);

 return result;
}

void* DHAX_Video_Player_Frame::make_scene_arrow_annotation(DHAX_Video_Annotation* dva)
{
 QByteArray qba = QByteArray::fromBase64(dva->data64().trimmed().toLatin1());
 QString kv_text = dva->kv_text();

 Rotateable_Arrow_Annotation raa = kv_text.isEmpty()?
   Rotateable_Arrow_Annotation(qba) : Rotateable_Arrow_Annotation(kv_text);

//? const QPolygonF& qpf = raa.rendered_polygon();
 QPolygonF qpf = raa.rendered_polygon();

// QPolygonF qpf = raa.rendered_polygon();

 QBrush qbr(raa.fill_color());

  qDebug() << "\n\n\n===============\n\n";

 qDebug() << raa.fill_color();
 qDebug() << raa.get_xscale();
 qDebug() << raa.get_yscale();
 qDebug() << qpf;

 qDebug() << "\n\n===============\n\n\n";

 QColor pen_color = raa.fill_color();

 pen_color.setGreen(qMax(pen_color.green() - 40, 0));
 pen_color.setRed(qMax(pen_color.red() - 40, 0));
 pen_color.setBlue(qMax(pen_color.blue() - 40, 0));

 pen_color.setAlpha(140);

 QPen pen;
 pen.setColor(pen_color);
 pen.setWidth(2);
 pen.setCapStyle(Qt::FlatCap);


 QGraphicsPolygonItem* result = new QGraphicsPolygonItem(qpf, annotations_rect_item_);
 result->setPen(pen);
 result->setBrush(qbr);

   //graphics_scene_->addPolygon(qpf, pen, qbr);
// result->setScale(raa.get_scale());

 dva->set_scene_data(result);
 dva->set_scene_type_data(QGraphicsPolygonItem_show_hide);

 annotation_set_->set_end_frame_data(dva->ending_frame_number(),
   //?QGraphicsEllipseItem_show_hide,
   *dva);


 return result;
}

void* DHAX_Video_Player_Frame::make_scene_annotation(DHAX_Video_Annotation* dva)
{

// static QGraphicsPixmapItem* gpi = nullptr;

// if(!gpi)
// {
//  QPixmap pm("/home/nlevisrael/gits/ctg-temp/dev/documents/out/test.png");

//  gpi = graphics_scene_->addPixmap(pm);

//// gpi->setZValue(100);

//  gpi->setPos(40, 40);

// }
// pause();

// return nullptr;

 if(dva->kind() == "text")
   return make_scene_text_annotation(dva);
// {
//  QString png = dva->get_pdflatex_png();
//  if(png.isEmpty())
//    return make_scene_text_annotation(dva);
//  return make_scene_pixmap_annotation(dva);
// }
 else if(dva->kind() == "circled")
   return make_scene_circled_text_annotation(dva);
 else if(dva->kind() == "Rotateable_Arrow_Annotation")
   return make_scene_arrow_annotation(dva);

 return nullptr;
}

void DHAX_Video_Player_Frame::connect_video_probe()
{
 connect(video_probe_, &QVideoProbe::videoFrameProbed, this,
   &DHAX_Video_Player_Frame::handle_video_frame);
}


void DHAX_Video_Player_Frame::init_annotations()
{
 annotation_set_ = new DHAX_Video_Annotation_Set;
//? annotation_set_->load_sample_annotations();
 qDebug() << "annotation_st" << *annotation_set_;

 annotations_rect_item_ = graphics_scene_->addRect(0,0,0,0,Qt::NoPen, Qt::NoBrush);
 annotations_rect_item_->setZValue(1);

// annotations_rect_item_->setPen(Qt::NoPen);
// annotations_rect_item_->setBrush(Qt::NoBrush);

// annotations_rect_item_->setScale(1.3);
}


void DHAX_Video_Player_Frame::reset_annotation()
{
// //  this would by Qt 6 ...
// for (auto [key, value]: annotation_set_->asKeyValueRange())
// {
//     // ...
// }

 for(DHAX_Video_Annotation& dva : annotation_set_->values())
 {
  show_hide_show(&dva);
 }
}

void DHAX_Video_Player_Frame::load_annotations()
{
 pause();

 QString annotations_file = QFileDialog::getOpenFileName(this,
   "Select annotation file (.ntxh format)", ROOT_FOLDER "/..",
   "*.ntxh");

 if(!annotations_file.isEmpty())
   load_annotations_file(annotations_file);
}


void DHAX_Video_Player_Frame::load_annotations_file(QString annotations_file)
{
 if(annotation_set_)
 {
  //delete annotation_set_;
  annotation_set_ = annotation_set_->reinit_and_delete(); //new DHAX_Video_Annotation_Set;
 }

 annotation_set_->load_annotation_file(annotations_file);

 if( navigation_->is_full_size_mode() )
   reposition_larger_annotations_rect_item();
 else
   reposition_smaller_annotations_rect_item();

}

void DHAX_Video_Player_Frame::update_frame_number_text()
{
 QString text = QString::number(current_frame_count_);
//      "%1\n%2"_qt.arg(current_frame_count_).arg(seconds);
 frame_number_text_->setPlainText(text);
}


void DHAX_Video_Player_Frame::pause()
{
 if(current_pause_timer_)
 {
  current_pause_timer_->stop();
  return;
 }

 media_player_->pause();

 if(frame_number_text_)
   update_frame_number_text();

 navigation_->set_play_button_to_resume();
}

void DHAX_Video_Player_Frame::resume_from_pause_timer()
{
 if(current_pause_timer_)
   current_pause_timer_->deleteLater();

 current_pause_timer_ = nullptr;
 resume();
}


void DHAX_Video_Player_Frame::resume()
{
 if(current_pause_timer_)
 {
  current_pause_timer_->start();
  return;
 }

 for(DHAX_Video_Annotation* dva : current_paused_annotations_)
 {
  show_hide_hide(dva);
 }

 media_player_->play();
 navigation_->set_play_button_to_play();
}

void DHAX_Video_Player_Frame::handle_send_video_frame_to_main_window(QLabel* l)
{
 QString cnf = class_name_folder(DEFAULT_DHAX_TEMP_FOLDER "/_proc");

 QDir qd(cnf);
 if(!qd.exists())
   qd.mkpath(".");

 cnf += "/temp.png";
 l->pixmap()->save(cnf);

 qDebug() << "saving pixmap: " << cnf;

 Q_EMIT show_video_frame_requested(cnf);
}


void DHAX_Video_Player_Frame::halt()
{
 media_player_->stop();
}

void DHAX_Video_Player_Frame::play_local_video(QString file_path, QString annotations_file)
{
 play_local_videos({{file_path, annotations_file}});
}

void DHAX_Video_Player_Frame::play_local_videos(QList<QPair<QString, QString>> paths)
{
 init_annotations();

 if(paths.isEmpty())
   return;

 QString annotations_file = paths.first().second;

 annotations_files_.push_back(annotations_file);
 if(!annotations_file.isEmpty())
 {
  load_annotations_file(annotations_file);
 }

 current_path_ = paths.first().first;
//
// current_path_ = "/home/nlevisrael/gits/ctg-temp/stella/videos/test.mkv";
// current_path_ = "/home/nlevisrael/gits/ctg-temp/video-annotations/back/bus.mkv";

 current_url_ =  QUrl::fromLocalFile(current_path_);

 QMediaPlaylist* play_list = new QMediaPlaylist();
 media_player_->setPlaylist(play_list);
 play_list->addMedia(QMediaContent(current_url_));

 if(paths.size() == 1)
   play_list->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);

 else
 {
  play_list->setPlaybackMode(QMediaPlaylist::Sequential);
  for(auto it = paths.begin() + 1; it != paths.end(); ++it)
  {
   play_list->addMedia(QMediaContent(QUrl::fromLocalFile(it->first)));
   annotations_files_.push_back(it->second);
  }

  connect(play_list, &QMediaPlaylist::currentIndexChanged, [this](int position)
  {
   if( (position == 0) && (current_playlist_index_ == 0) )
     return;

   current_playlist_index_ = position;

   qDebug() << "new playlist position: " << position;
   QString annotations_file = annotations_files_.value(position);

   //?
   current_paused_annotations_.clear();
   current_reffed_annotations_index_ = 0;

   if(annotations_rect_item_)
   {
    graphics_scene_->removeItem(annotations_rect_item_);
   }
   annotations_rect_item_ = graphics_scene_->addRect(0,0,0,0,Qt::NoPen, Qt::NoBrush);
   annotations_rect_item_->setZValue(1);

   if(annotations_file.isEmpty())
     annotation_set_->clear();
   else
     load_annotations_file(annotations_file);
  });
 }


// media_player_->setMedia(current_url_);

 // //  give it a bit of time
 //??? need_video_size_ = 10; //
 if(current_playlist_index_ == 0)
   need_video_size_ = 5;

// ?check_adjust_size();

 media_player_->play();



// qDebug() << " SR1: " << graphics_scene_->sceneRect();
// qDebug() << " IBR1: " << graphics_scene_->itemsBoundingRect();

// QSizeF sz = video_item_->size(); //.grownBy(QMargins(5,5,5,5));
// qDebug() << " SZ1: " << sz;


// navigation_->show();
}

QSize DHAX_Video_Player_Frame::get_navigation_size()
{
 return navigation_->size();
}

QRectF DHAX_Video_Player_Frame::graphics_view_visible_rect()
{
    QPointF tl(graphics_view_->horizontalScrollBar()->value(),
      graphics_view_->verticalScrollBar()->value());
    QPointF br = tl + graphics_view_->viewport()->rect().bottomRight();
    QMatrix mat = graphics_view_->matrix().inverted();
    return mat.mapRect(QRectF(tl,br));
}

QRect DHAX_Video_Player_Frame::get_scene_camera_view_geometry()
{
 if(!graphics_view_)
   return {};

 r8 vleft = scene_camera_view_geometry_.left();
 r8 vtop = scene_camera_view_geometry_.top();

 QPointF A = graphics_view_->mapToScene( QPoint(0, 0) );
 QPointF B = graphics_view_->mapToScene( QPoint(
         graphics_view_->viewport()->width(),
         graphics_view_->viewport()->height() ));

 QRectF ab( A, B );

 QRect rr = graphics_view_->viewport()->rect();
 QPoint tl = QPoint(vleft - ab.left(), vtop - ab.top());
 QPoint tl_global =  graphics_view_->mapToGlobal(tl);

 QPoint rr_global =  graphics_view_->mapToGlobal(rr.topLeft());

 QRect tl_rect (tl_global, QSize(scene_camera_view_geometry_.width(),
                                 scene_camera_view_geometry_.height()));
 QRect rr_rect (rr_global, QSize(rr.width(), rr.height()));

 QRect intersection = tl_rect.intersected(rr_rect);

 return intersection;
}



void DHAX_Video_Player_Frame::confirm_video_size()
{

 if(current_playlist_index_ > 0)
   return;

 QColor c (200, 100, 10, 100);

// {
//  QBrush qbr(c);
//  QGraphicsEllipseItem* el1 = graphics_scene_->addEllipse(0, 0, 20, 20, QPen(), qbr);
//  el1->setParentItem(annotations_rect_item_);
//  QGraphicsEllipseItem* el2 = graphics_scene_->addEllipse(40, 40, 20, 20, QPen(), qbr);
//  el2->setParentItem(annotations_rect_item_);
//  QGraphicsEllipseItem* el3 = graphics_scene_->addEllipse(80, 80, 20, 20, QPen(), qbr);
//  el3->setParentItem(annotations_rect_item_);
//  QGraphicsEllipseItem* el4 = graphics_scene_->addEllipse(120, 120, 20, 20, QPen(), qbr);
//  el4->setParentItem(annotations_rect_item_);

//  QGraphicsEllipseItem* el5 = graphics_scene_->addEllipse(120, 220, 20, 20, QPen(), qbr);
//  el5->setParentItem(annotations_rect_item_);


// }


 qDebug() << " SR2: " << graphics_scene_->sceneRect();
 qDebug() << " IBR2: " << graphics_scene_->itemsBoundingRect();

 QSizeF sz = video_item_->size(); //.grownBy(QMargins(5,5,5,5));
 qDebug() << " SZ2: " << sz;


 double ratio, new_width, new_height, left, top;

 if(video_size_.width() > video_size_.height())
 {
  ratio = (double) video_size_.height() / video_size_.width();
  new_width = sz.width();
  new_height = new_width * ratio;
  left = video_item_->pos().x();
  top = (sz.height() / 2) - (new_height / 2);
 }
 else
 {
  ratio = (double) video_size_.width() / video_size_.height();
  new_height = sz.height();
  new_width = new_height * ratio;
  left = (sz.width() / 2) - (new_width / 2);
  top = video_item_->pos().y();
 }

// double h_center = sz.width() / 2;

 annotation_set_->set_smaller_video_size(QSizeF(new_width, new_height));
 annotation_set_->set_larger_video_size(video_size_);
 annotation_set_->check_ratios();

 annotation_set_->compile_latex(QSizeF(new_width, new_height));

 qDebug() << "larger video size: " << video_size_;

 //QRectF
 video_rect_ = QRectF(left, top, new_width, new_height);
 //video_top_left_ = video_rect.topLeft();

 scene_camera_view_geometry_ = video_rect_.toRect();

 annotations_rect_item_->setRect(video_rect_.adjusted(2,2,-2,-2));

// smaller_size_rect_item_ = graphics_scene_->addRect(left,
//   video_item_->pos().y(),new_width,sz.height(),QPen(QBrush(c), 4));

 smaller_size_rect_item_ = graphics_scene_->addRect(video_rect_, QPen(QBrush(c), 4),
   Qt::NoBrush);


 smaller_size_rect_item_->setParentItem(video_item_);

 QRectF framed_scene_rect = graphics_scene_->sceneRect();

 QColor text_bkg_color (110, 80, 20, 40);
 QColor text_color (10, 80, 20, 255);

// u1 frame_number_text_background_extra_height = 10;

// frame_number_text_background_ = graphics_scene_->addRect(
//   QRect(smaller_size_rect_item_->rect().bottomRight().toPoint() - QPoint(120, 2),
//   smaller_size_rect_item_->rect().bottomRight().toPoint() + QPoint(-100, frame_number_text_background_extra_height)));

// frame_number_text_background_ = graphics_scene_->addRect(
//   QRect(smaller_size_rect_item_->rect().center().toPoint() - QPoint(20, 2),
//   smaller_size_rect_item_->rect().center().toPoint()));

  frame_number_text_background_ = graphics_scene_->addRect(
    QRect(smaller_size_rect_item_->rect().topLeft().toPoint() + QPoint(-20, 5),
    smaller_size_rect_item_->rect().topLeft().toPoint() + QPoint(3, 20)));

 frame_number_text_background_->setParentItem(smaller_size_rect_item_);

 frame_number_text_background_->setBrush(QBrush(text_bkg_color));
 frame_number_text_background_->setPen(Qt::NoPen);

 frame_number_text_ = graphics_scene_->addText("0000");
 frame_number_text_->setParentItem(frame_number_text_background_);
 frame_number_text_->setPos(frame_number_text_background_->rect().topLeft());

 frame_number_text_->setDefaultTextColor(text_color);
 QFont font = frame_number_text_->font();
 font.setPointSize(5);
 frame_number_text_->setFont(font);

 reset_graphics_scene_rect();

 graphics_scene_->setSceneRect(framed_scene_rect);
 initial_smaller_scene_rect_ = framed_scene_rect;

 reposition_smaller_annotations_rect_item();

 qDebug() << " SR4: " << graphics_scene_->sceneRect();
 qDebug() << " IBR4: " << graphics_scene_->itemsBoundingRect();

// double left_half = h_center - graphics_scene_->sceneRect().left();
// double right_half = h_center - graphics_scene_->sceneRect().right();

// qDebug() << " left half: " << left_half;
// qDebug() << " right half: " << right_half;

 Q_EMIT video_size_established(QSize(new_width, new_height ));


}


#ifdef HIDE
void DHAX_Video_Player_Frame::confirm_video_size()
{
 QColor c (200, 100, 10, 100);

 navigation_->enter_smaller_size_mode();

// {
//  QBrush qbr(c);
//  QGraphicsEllipseItem* el1 = graphics_scene_->addEllipse(0, 0, 20, 20, QPen(), qbr);
//  el1->setParentItem(annotations_rect_item_);
//  QGraphicsEllipseItem* el2 = graphics_scene_->addEllipse(40, 40, 20, 20, QPen(), qbr);
//  el2->setParentItem(annotations_rect_item_);
//  QGraphicsEllipseItem* el3 = graphics_scene_->addEllipse(80, 80, 20, 20, QPen(), qbr);
//  el3->setParentItem(annotations_rect_item_);
//  QGraphicsEllipseItem* el4 = graphics_scene_->addEllipse(120, 120, 20, 20, QPen(), qbr);
//  el4->setParentItem(annotations_rect_item_);

//  QGraphicsEllipseItem* el5 = graphics_scene_->addEllipse(120, 220, 20, 20, QPen(), qbr);
//  el5->setParentItem(annotations_rect_item_);


// }


 qDebug() << " SR2: " << graphics_scene_->sceneRect();
 qDebug() << " IBR2: " << graphics_scene_->itemsBoundingRect();

 QSizeF sz = video_item_->size(); //.grownBy(QMargins(5,5,5,5));
 qDebug() << " SZ2: " << sz;


 double ratio = (double) video_size_.width() / video_size_.height();

 double new_width = sz.height() * ratio;

 double left = (sz.width() / 2) - (new_width / 2);

 double h_center = sz.width() / 2;

 annotation_set_->set_smaller_video_size(QSizeF(new_width, sz.height()));
 annotation_set_->set_larger_video_size(video_size_);
 annotation_set_->check_ratios();


 //QRectF
 video_rect_ = QRectF(left, video_item_->pos().y(), new_width, sz.height());
 //video_top_left_ = video_rect.topLeft();

 scene_camera_view_geometry_ = video_rect_.toRect();

 annotations_rect_item_->setRect(video_rect_.adjusted(2,2,-2,-2));

// smaller_size_rect_item_ = graphics_scene_->addRect(left,
//   video_item_->pos().y(),new_width,sz.height(),QPen(QBrush(c), 4));

 smaller_size_rect_item_ = graphics_scene_->addRect(video_rect_, QPen(QBrush(c), 4),
   Qt::NoBrush);


 smaller_size_rect_item_->setParentItem(video_item_);

 QRectF framed_scene_rect = graphics_scene_->sceneRect();

 QColor text_bkg_color (110, 80, 20, 40);
 QColor text_color (10, 80, 20, 255);

// u1 frame_number_text_background_extra_height = 10;

// frame_number_text_background_ = graphics_scene_->addRect(
//   QRect(smaller_size_rect_item_->rect().bottomRight().toPoint() - QPoint(120, 2),
//   smaller_size_rect_item_->rect().bottomRight().toPoint() + QPoint(-100, frame_number_text_background_extra_height)));

// frame_number_text_background_ = graphics_scene_->addRect(
//   QRect(smaller_size_rect_item_->rect().center().toPoint() - QPoint(20, 2),
//   smaller_size_rect_item_->rect().center().toPoint()));

  frame_number_text_background_ = graphics_scene_->addRect(
    QRect(smaller_size_rect_item_->rect().topLeft().toPoint() + QPoint(-20, 5),
    smaller_size_rect_item_->rect().topLeft().toPoint() + QPoint(3, 20)));

 frame_number_text_background_->setParentItem(smaller_size_rect_item_);

 frame_number_text_background_->setBrush(QBrush(text_bkg_color));
 frame_number_text_background_->setPen(Qt::NoPen);

 frame_number_text_ = graphics_scene_->addText("0000");
 frame_number_text_->setParentItem(frame_number_text_background_);
 frame_number_text_->setPos(frame_number_text_background_->rect().topLeft());

 frame_number_text_->setDefaultTextColor(text_color);
 QFont font = frame_number_text_->font();
 font.setPointSize(5);
 frame_number_text_->setFont(font);

 reset_graphics_scene_rect();

 graphics_scene_->setSceneRect(framed_scene_rect);
 initial_smaller_scene_rect_ = framed_scene_rect;

 reposition_smaller_annotations_rect_item();

 qDebug() << " SR4: " << graphics_scene_->sceneRect();
 qDebug() << " IBR4: " << graphics_scene_->itemsBoundingRect();

 double left_half = h_center - graphics_scene_->sceneRect().left();
 double right_half = h_center - graphics_scene_->sceneRect().right();

 qDebug() << " left half: " << left_half;
 qDebug() << " right half: " << right_half;


 Q_EMIT video_size_established(QSize(new_width, sz.height() ));


}
#endif

void DHAX_Video_Player_Frame::reset_graphics_scene_rect()
{
 QRectF rect = graphics_scene_->itemsBoundingRect();
 graphics_scene_->setSceneRect(rect);
}

void DHAX_Video_Player_Frame::reset_to_smaller_size()
{
 navigation_->enter_smaller_size_mode();

// annotations_rect_item_->setScale(1);
 reposition_smaller_annotations_rect_item();

 if(full_size_rect_item_)
   graphics_scene_->removeItem(full_size_rect_item_);
 if(smaller_size_rect_item_)
 {
  graphics_scene_->addItem(smaller_size_rect_item_);
  smaller_size_rect_item_->setParentItem(video_item_);
 }

// frame_number_text_background_->show();
// frame_number_text_->show();


 video_item_->setSize(last_smaller_size_);
// scene_camera_view_geometry_ = last_smaller_size_;

 scene_camera_view_geometry_ = video_rect_.toRect();

 reset_graphics_scene_rect();

 graphics_scene_->setSceneRect(initial_smaller_scene_rect_);

 Q_EMIT smaller_video_size_requested(last_smaller_size_.toSize());
}

void DHAX_Video_Player_Frame::reset_to_full_size()
{
 navigation_->enter_full_size_mode();

 qDebug() << " ==== " << annotation_set_->sizes_ratio_x()
           << " --- " << annotation_set_->sizes_ratio_y() ;


// annotations_rect_item_->setTransform(annotation_set_->sizes_ratio_y());

// annotations_rect_item_->setScale(annotation_set_->sizes_ratio_y());
 reposition_larger_annotations_rect_item();


// QColor c1 (250, 100, 210, 200);
// {
//  QBrush qbr(c1);
//  QGraphicsEllipseItem* el1 = graphics_scene_->addEllipse(20, 20, 20, 20, QPen(), qbr);
//  el1->setParentItem(annotations_rect_item_);
//  QGraphicsEllipseItem* el2 = graphics_scene_->addEllipse(60, 60, 20, 20, QPen(), qbr);
//  el2->setParentItem(annotations_rect_item_);
//  QGraphicsEllipseItem* el3 = graphics_scene_->addEllipse(100, 100, 20, 20, QPen(), qbr);
//  el3->setParentItem(annotations_rect_item_);
//  QGraphicsEllipseItem* el4 = graphics_scene_->addEllipse(140, 140, 20, 20, QPen(), qbr);
//  el4->setParentItem(annotations_rect_item_);

//  QGraphicsEllipseItem* el5 = graphics_scene_->addEllipse(140, 220, 20, 20, QPen(), qbr);
//  el5->setParentItem(annotations_rect_item_);

//  QGraphicsEllipseItem* el6 = graphics_scene_->addEllipse(160, 1270, 20, 20, QPen(), QBrush(Qt::red));

// }


// annotations_rect_item_->setScale(annotation_set_->sizes_ratio_x());
// qDebug() << " ===== MATRIX =====\n" << annotations_rect_item_->transform();

// qDebug() << "new size: " << video_size_;
// QSize sza = video_size_.grownBy(QMargins(5,5,5,5));
// setMaximumWidth(sza.width());
// setMaximumHeight(sza.height());
// graphics_view_->resize(video_size_);
// graphics_view_->update();

// video_item_->setSize(video_size_);

 QColor c (200, 100, 10, 100);

 if(smaller_size_rect_item_)
   graphics_scene_->removeItem(smaller_size_rect_item_);

 if(full_size_rect_item_)
   graphics_scene_->addItem(full_size_rect_item_);
 else
 {
  QSizeF szs = video_size_.grownBy(QMargins(3,3,3,3));

  full_size_rect_item_ = graphics_scene_->addRect(0, 0, szs.width(), szs.height(),
   QPen(QBrush(c), 10), Qt::NoBrush);
 }

 scene_camera_view_geometry_ = QRect(0, 0, video_size_.width(), video_size_.height());

 if(true) //last_larger_video_size_.isEmpty())
 {
//  frame_number_text_background_->hide();
//  frame_number_text_->hide();

  last_smaller_size_ = video_item_->size();

  video_item_->setSize(video_size_);

  QSizeF sza = video_size_.grownBy(QMargins(5,5,5,5));

  last_larger_video_size_ = video_size_;
  last_larger_graphics_view_size_ = sza;

  graphics_view_->resize(sza.toSize());
  QRectF rect = graphics_scene_->itemsBoundingRect();
  graphics_scene_->setSceneRect(rect);

  Q_EMIT full_video_size_requested(sza.toSize());
 }

}

void DHAX_Video_Player_Frame::reposition_smaller_annotations_rect_item()
{
 QTransform tr; tr.scale(1, 1);
 annotations_rect_item_->setTransform(tr);

 annotations_rect_item_->setPos(video_rect_.topLeft() +
   QPoint(annotation_set_->smaller_size_x_translation(),
          annotation_set_->smaller_size_y_translation()));

 graphics_view_->update();

}

void DHAX_Video_Player_Frame::reposition_larger_annotations_rect_item()
{
 QTransform tr; tr.scale(annotation_set_->sizes_ratio_x() *
   annotation_set_->sizes_ratio_x_adjustment(),
   annotation_set_->sizes_ratio_y() *
   annotation_set_->sizes_ratio_y_adjustment());

 annotations_rect_item_->setTransform(tr);

 annotations_rect_item_->setPos(
   annotation_set_->larger_size_x_translation(), annotation_set_->larger_size_y_translation());

 graphics_view_->update();
}


void DHAX_Video_Player_Frame::recenter()
{
 graphics_view_->centerOn(video_item_);
}

void DHAX_Video_Player_Frame::resizeEvent(QResizeEvent* event)
{
 graphics_view_->centerOn(video_item_);

//? setMaximumWidth(video_widget_->width() + 12);
//? navigation_->move(p.x(), p.y() - 20);
//? navigation_->move(rect().bottomRight() - navigation_->rect().bottomRight());// + QPoint(-40,-40));
// navigation_->move(video_widget_->rect().bottomRight() - navigation_->rect().bottomRight() + QPoint(0,10));
 QWidget::resizeEvent(event);
}
