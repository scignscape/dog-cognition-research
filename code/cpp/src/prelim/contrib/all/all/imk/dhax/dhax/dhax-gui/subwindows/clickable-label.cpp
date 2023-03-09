
//          Copyright Nathaniel Christen 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include "clickable-label.h"

#include <QMouseEvent>
#include <QStyle>

#include "qsns.h"

USING_QSNS(ScignStage)


Clickable_Label::Clickable_Label(QWidget* parent, Qt::WindowFlags f)
    : QLabel(parent), cb_({nullptr, nullptr}), cb_parent_(nullptr)
{
 setProperty("styled_info", false);
}

Clickable_Label::~Clickable_Label() {}

void Clickable_Label::unstyle()
{
 setProperty("styled_info", false);
 style()->unpolish(this);
 style()->polish(this);
}

void Clickable_Label::mousePressEvent(QMouseEvent* event)
{
 if( (cb_.first) || (cb_.second) )
 {
  QObject* p = cb_parent_;
  if(!p)
  {
   p = parent();
   if(p)
   {
    while(p->parent())
    {
     p = p->parent();
    }
   }
  }
  if( (cb_.first) && (event->button() == Qt::LeftButton))
    (cb_.first)(p, text_data_);
  else if(cb_.second)
  {
   setProperty("styled_info", true);
   style()->unpolish(this);
   style()->polish(this);
   (cb_.second)(p, event, this, text_data_);
  }
 }
 else
   Q_EMIT(clicked(event));
}

