
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef MESSAGE_DISPLAY_WINDOW__H
#define MESSAGE_DISPLAY_WINDOW__H

#include "accessors.h"

#include "flags.h"

#include "global-types.h"

#include <QString>
#include <QQueue>

#include <QObject>
#include <QPlainTextEdit>
#include <QVBoxLayout>
#include <QDialog>

#include <QStatusBar>


class Game_Token;

class Message_Display_Window : public QDialog
{
 Q_OBJECT

 QPlainTextEdit* text_edit_;
 QVBoxLayout* main_layout_;

 QStatusBar* status_bar_;

 QStringList messages_;

public:

 Message_Display_Window();

 ACCESSORS(QStatusBar* ,status_bar)

 void add_message(QString msg);

};



#endif // MESSAGE_DISPLAY_WINDOW__H
