

//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "dhax-video-navigation-frame.h"


#include <QDebug>
#include <QLabel>

DHAX_Video_Navigation_Frame::DHAX_Video_Navigation_Frame(QWidget* parent)
  :  QFrame(parent), current_mode_(0)
{
 main_layout_ = new QHBoxLayout;

 top_layout_ = new QHBoxLayout;
 bottom_layout_ = new QHBoxLayout;

 main_layout_->setContentsMargins(0,0,0,0);
 main_layout_->setMargin(0);

 top_layout_->setContentsMargins(0,0,0,0);
 top_layout_->setMargin(0);

 bottom_layout_->setContentsMargins(0,0,0,0);
 bottom_layout_->setMargin(0);

 full_size_button_ = new QPushButton("*", this);
 full_size_button_->setToolTip("Enlarge video to full size");
 sigma(full_size_button_)->make_enlarge_button();
 full_size_button_->setMinimumWidth(22);

 smaller_size_button_ = new QPushButton("-", this);
 smaller_size_button_->setToolTip("Shrink video to prior smaller size");
 sigma(smaller_size_button_)->make_contract_button();
 smaller_size_button_->setMinimumWidth(26);

 QFrame* left = new QFrame(this);
 left->setFrameStyle(QFrame::Panel | QFrame::Raised);


 top_layout_->addWidget(full_size_button_);//, Qt::AlignBottom);
 top_layout_->addWidget(smaller_size_button_);//, Qt::AlignTop);
 left->setLayout(top_layout_);
 left->setMaximumHeight(full_size_button_->height() + smaller_size_button_->height());

 QFrame* right = new QFrame(this);
 right->setFrameStyle(QFrame::Panel | QFrame::Raised);

 restart_button_ = new QPushButton("<", this);
 restart_button_->setToolTip("Restart (from beginning)");
 sigma(restart_button_)->make_restart_button();

 pause_button_ = new QPushButton("=", this);
 pause_button_->setToolTip("Pause");
 sigma(pause_button_)->make_pause_button();

 resume_button_  = new QPushButton(">", this);
 resume_button_->setToolTip("Play/Resume (from current frame)");
 //?sigma(resume_button_)->make_resume_button();
 set_play_button_to_play();
// sigma(resume_button_)->make_play_button();

 bottom_layout_->addWidget(restart_button_);
 bottom_layout_->addWidget(pause_button_);
 bottom_layout_->addWidget(resume_button_);

 right->setLayout(bottom_layout_);

 main_layout_->addWidget(left);
 main_layout_->addStretch();

 grab_frame_button_ = new QPushButton("@", this);
 grab_frame_button_->setToolTip("Pause and view current frame (enlarged)");
 sigma(grab_frame_button_)->make_camera_button();
 grab_frame_button_->setMinimumWidth(25);

 main_layout_->addWidget(grab_frame_button_);
 main_layout_->addStretch();
 main_layout_->addWidget(right);

// main_layout_->addLayout(top_layout_);
// main_layout_->addLayout(bottom_layout_);
 setLayout(main_layout_);

 connect(pause_button_, &QPushButton::clicked,
   this, &DHAX_Video_Navigation_Frame::pause_requested);

 connect(resume_button_, &QPushButton::clicked,
   this, &DHAX_Video_Navigation_Frame::resume_requested);

 connect(restart_button_, &QPushButton::clicked,
   this, &DHAX_Video_Navigation_Frame::restart_requested);

 connect(full_size_button_, &QPushButton::clicked,
   this, &DHAX_Video_Navigation_Frame::full_size_requested);

 connect(smaller_size_button_, &QPushButton::clicked,
   this, &DHAX_Video_Navigation_Frame::smaller_size_requested);

 connect(grab_frame_button_, &QPushButton::clicked,
   this, &DHAX_Video_Navigation_Frame::grab_frame_requested);

}

void DHAX_Video_Navigation_Frame::enter_full_size_mode()
{
 current_mode_ = 1;
 full_size_button_->setEnabled(false);
 smaller_size_button_->setEnabled(true);
}

void DHAX_Video_Navigation_Frame::enter_smaller_size_mode()
{
 current_mode_ = -1;
 full_size_button_->setEnabled(true);
 smaller_size_button_->setEnabled(false);
}

bool DHAX_Video_Navigation_Frame::is_full_size_mode()
{
 return (current_mode_ == 1);
}


void DHAX_Video_Navigation_Frame::set_play_button_to_play()
{
 sigma(resume_button_)->make_play_button();
}

void DHAX_Video_Navigation_Frame::set_play_button_to_resume()
{
 sigma(resume_button_)->make_resume_button();
}
