
//          Copyright Nathaniel Christen 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef CLICKABLE_LABEL__H
#define CLICKABLE_LABEL__H

#include <QLabel>

#include "qsns.h"

#include "accessors.h"

#include <functional>

class Clickable_Label : public QLabel
{
 Q_OBJECT

 QString text_data_;

 QPair<std::function<void(QObject*, QString)>,
   std::function<void(QObject*, QMouseEvent*,
   Clickable_Label* scl, QString)>> cb_;

 typedef QPair<std::function<void(QObject*, QString)>,
   std::function<void(QObject*, QMouseEvent*,
   Clickable_Label* scl, QString)>> cb_type;

 QObject* cb_parent_;

public:

 explicit Clickable_Label(QWidget* parent = nullptr,
   Qt::WindowFlags f = Qt::WindowFlags());

 ~Clickable_Label();

 void unstyle();



 ACCESSORS(QString ,text_data)
 ACCESSORS(cb_type ,cb)
 ACCESSORS(QObject* ,cb_parent)


Q_SIGNALS:
 void clicked(QMouseEvent*);

protected:
  void mousePressEvent(QMouseEvent* event);

};

#endif  // CLICKABLE_LABEL__H
