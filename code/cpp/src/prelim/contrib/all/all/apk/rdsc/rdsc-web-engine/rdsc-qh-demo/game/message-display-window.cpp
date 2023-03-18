
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)



#include "message-display-window.h"

#include <QScrollBar>
#include <QStatusBar>

Message_Display_Window::Message_Display_Window()
{
 status_bar_ = new QStatusBar(this);
 main_layout_ = new  QVBoxLayout;
 text_edit_ = new QPlainTextEdit;
 main_layout_->addWidget(text_edit_);
 main_layout_->addWidget(status_bar_);
 setLayout(main_layout_);

}

void Message_Display_Window::add_message(QString msg)
{
 messages_.push_back(msg);
 if(status_bar_)
 {
  status_bar_->showMessage("(%1 messages)"_qt.arg(messages_.count()));
 }

 text_edit_->appendPlainText(msg);
 text_edit_->verticalScrollBar()->setValue(text_edit_->verticalScrollBar()->maximum()); // Scrolls to the bottom
}



