
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)



#ifndef MAIN_WINDOW__H
#define MAIN_WINDOW__H

#include <QMainWindow>

#include "accessors.h"

class Lanternfly_Frame;


class Lanternfly_Main_Window : public QMainWindow
{
 Q_OBJECT

 Lanternfly_Frame* lanternfly_frame_;


public:
 explicit Lanternfly_Main_Window(QWidget *parent = 0);
 ~Lanternfly_Main_Window();

 ACCESSORS(Lanternfly_Frame* ,lanternfly_frame)

private slots:
 void on_actionExit_triggered();

 //private:
 //    Ui::MainWindow *ui;
};

#endif // MAIN_WINDOW_H
