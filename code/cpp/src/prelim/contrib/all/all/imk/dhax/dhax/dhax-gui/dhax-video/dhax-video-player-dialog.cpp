

//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "dhax-video-player-dialog.h"

#include "dhax-video-player-frame.h"

#include "styles.h"


DHAX_Video_Player_Dialog::DHAX_Video_Player_Dialog(Annotation_Settings s,
  QWidget* parent)
  :  QDialog(parent), annotation_settings_(s),
     scene_camera_view_geometry_rubber_band_(nullptr)
{
// setLayout(new QVBoxLayout);
// layout()->setContentsMargins(0, 0, 0, 0);


 main_layout_ = new QVBoxLayout;

 main_layout_->setContentsMargins(0, 0, 0, 0);
 main_layout_->setMargin(0);


 player_ = new DHAX_Video_Player_Frame(this);

 main_layout_->addWidget(player_);
 button_box_ = new QDialogButtonBox(this);

 button_save_ok_ = new QPushButton("Save/OK");
 button_suspend_ = new QPushButton("Suspend");
 button_cancel_close_ = new QPushButton("Close");

 button_save_ok_->setDefault(true);

 button_save_ok_->setStyleSheet(basic_button_style_sheet_());
 button_suspend_->setStyleSheet(basic_button_style_sheet_());
 button_cancel_close_->setStyleSheet(basic_button_style_sheet_());


 button_cancel_close_->setDefault(true);

 button_box_->addButton(button_save_ok_, QDialogButtonBox::AcceptRole);
 button_box_->addButton(button_suspend_, QDialogButtonBox::ActionRole);
 button_box_->addButton(button_cancel_close_, QDialogButtonBox::RejectRole);

 button_box_->setContentsMargins(2,0,0,4);

 //?connect(button_proceed_, SIGNAL(clicked()), this, SLOT(proceed()));
// connect(button_box_, SIGNAL(accepted()), this, SLOT(accept()));
// connect(button_box_, SIGNAL(rejected()), this, SLOT(close()));

 connect(button_suspend_, &QPushButton::clicked, [this]()
 {
  player_->pause();
  setWindowState(windowState() | Qt::WindowState::WindowMinimized);
 });

 connect(button_box_, &QDialogButtonBox::accepted, this,
   &QDialog::accepted);

 connect(button_box_, &QDialogButtonBox::rejected, this,
   &QDialog::rejected);

 main_layout_->addWidget(button_box_);

 setLayout(main_layout_);

 connect(player_, &DHAX_Video_Player_Frame::show_video_frame_requested,
  this, &DHAX_Video_Player_Dialog::show_video_frame_requested);

 connect(player_, &DHAX_Video_Player_Frame::video_size_established,
  [this](QSize sz)
 {
  check_adjust_size(sz, 20);

//  QSize ns = player_->get_navigation_size();
//  int h = sz.height() + button_box_->height() + ns.height();
//  int w = qMax(sz.width(), button_box_->width());
//  w = qMax(w, ns.width());

//  this->resize(w, h + 20);

  reset_scene_camera_view_geometry(nullptr, nullptr);
 });

 connect(player_, &DHAX_Video_Player_Frame::full_video_size_requested,
  [this](QSize sz)
 {
  if(last_full_size_.isEmpty())
  {
   last_smaller_screen_position_ = pos();
   last_smaller_size_ = size();

   qDebug() << "full!!: " << sz;
   check_adjust_size(sz, 20);

   last_full_size_ = size();
   qDebug() << "lfs1" << last_full_size_;

  }
  else
  {
   qDebug() << "lfs" << last_full_size_;
    resize(last_full_size_);
  }

//?  reset_scene_camera_view_geometry();

 });

 connect(player_, &DHAX_Video_Player_Frame::smaller_video_size_requested,
  [this](QSize sz)
 {
  move(last_smaller_screen_position_);
  resize(last_smaller_size_);
  qDebug() << " small: " << sz;

//?  reset_scene_camera_view_geometry();
//  check_adjust_size(sz, 20);
 });

//  QMediaPlaylist *playList = new QMediaPlaylist(this);
//  playList->addMedia(QUrl::fromLocalFile("/home/nlevisrael/gits/ctg-temp/stella/videos/test.webm"));
//  playList->setPlaybackMode(QMediaPlaylist::Loop);
//  media_player_->setPlaylist(playList);


//  current_path_ = "/home/nlevisrael/gits/ctg-temp/stella/videos/test.mp4";


}

void DHAX_Video_Player_Dialog::halt()
{
 player_->halt();
}

void DHAX_Video_Player_Dialog::reset_scene_camera_view_geometry(QResizeEvent* resize_event,
  QMoveEvent* move_event)
{
 if(resize_event || move_event)
 {
  if(!scene_camera_view_geometry_rubber_band_)
    return;
 }

 current_scene_camera_view_geometry_ = player_->get_scene_camera_view_geometry();

//? qDebug() << "current wvg: " << current_scene_camera_view_geometry_;

 if(!scene_camera_view_geometry_rubber_band_)
 {
  // //  one purpose of the rubber band is for dev/debugging,
   //    to visualize the on-screen video area.
   //    Using this for actual users presumably
   //    requires subclassing QRubberBand so there's
   //    transparent or semi-transparent style options.
  scene_camera_view_geometry_rubber_band_ = new QRubberBand(QRubberBand::Rectangle);
  QPalette palette;
  palette.setColor(QPalette::Active, QPalette::Highlight, QColor(60, 100, 90, 30));
  scene_camera_view_geometry_rubber_band_->setPalette(palette);
  // //  Don't show unless as a temporary source-code change
   //    to visualize what's going on.
   //  scene_camera_view_geometry_rubber_band_->show();
 }

 scene_camera_view_geometry_rubber_band_->setGeometry(current_scene_camera_view_geometry_); //.adjusted(5, 5, -5, -5));

 Q_EMIT scene_camera_view_geometry_updated();
}

void DHAX_Video_Player_Dialog::resizeEvent(QResizeEvent* resize_event)
{
 reset_scene_camera_view_geometry(resize_event, nullptr);
 Q_EMIT scene_camera_view_geometry_updated();
}

void DHAX_Video_Player_Dialog::moveEvent(QMoveEvent* move_event)
{
 reset_scene_camera_view_geometry(nullptr, move_event);
 if(this->isVisible())
   Q_EMIT scene_camera_view_geometry_updated();
}

void DHAX_Video_Player_Dialog::check_adjust_size(QSize sz, int height_margin)
{
 qDebug() << " sz: " << sz;

 QSize ns = player_->get_navigation_size();
 qDebug() << " ns: " << ns;


 int h = sz.height() + button_box_->height() + ns.height();
 int w = qMax(sz.width(), button_box_->width());
 w = qMax(w, ns.width());

 this->resize(w, h + height_margin);
 recenter();

}

void DHAX_Video_Player_Dialog::recenter()
{
 player_->recenter();
}


void DHAX_Video_Player_Dialog::play_local_videos(QStringList paths, QString annotations_template_file)
{
 QList<QPair<QString, QString>> new_paths;

 std::transform(paths.begin(), paths.end(), std::back_inserter(new_paths),
                [](QString p) -> QPair<QString, QString>
 {
  return {p, {}};
 });

 play_local_videos(new_paths, annotations_template_file);
}

void DHAX_Video_Player_Dialog::play_local_videos(QList<QPair<QString, QString>> paths, QString annotations_template_file)
{
 if(!annotations_template_file.isEmpty())
   player_->set_annotations_template_file(annotations_template_file);
 player_->play_local_videos(paths);
}


void DHAX_Video_Player_Dialog::play_local_video(QString file_path,
  QString annotations_file)
{
 player_->play_local_video(file_path, annotations_file);
}
