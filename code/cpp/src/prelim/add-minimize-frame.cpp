
//          Copyright Nathaniel Christen 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <QHBoxLayout>
#include <QFrame>
#include <QButtonGroup>
#include <QPushButton>
#include <QLabel>
#include <QDialogButtonBox>
#include <QApplication>
#include <QMessageBox>
#include <QDebug>

#include <functional>

#include "styles.h"

QHBoxLayout* add_minimize_frame(QDialogButtonBox* bb, std::function<void()> fn)
{
 QPushButton* minimize_button = new QPushButton(QChar(0x2735), bb->parentWidget());
 QLabel* minimize_label = new QLabel(bb->parentWidget());
 QHBoxLayout* result = new QHBoxLayout;
 minimize_label->setText("Minimize");
 minimize_button->setStyleSheet(colorful_small_button_style_sheet_());

 QApplication::connect(minimize_button, &QPushButton::clicked, fn);

 QFrame* fr = new QFrame;

 fr->setFrameStyle(QFrame::Sunken);
 fr->setFrameShape(QFrame::Panel);

 QHBoxLayout* fr_layout = new QHBoxLayout;
 fr_layout->addWidget(minimize_button);
 fr_layout->addWidget(minimize_label);

 fr->setLayout(fr_layout);

 result->addWidget(fr);
 result->addStretch();
 result->addWidget(bb);
 return result;
}

QHBoxLayout* add_minimize_frame(QMessageBox* qmb, std::function<void()> fn)
{
 for(QAbstractButton* qab: qmb->buttons())
 {
  if (qmb->buttonRole(qab) == QMessageBox::ActionRole)
  {
   qab->click();
   break;
  }
 }

 QPushButton* minimize_button = new QPushButton(QChar(0x2735), qmb);
 QLabel* minimize_label = new QLabel(qmb);
 QHBoxLayout* result = new QHBoxLayout;
 minimize_label->setText("Minimize");
 minimize_button->setStyleSheet(colorful_small_button_style_sheet_());

 QApplication::connect(minimize_button, &QPushButton::clicked, fn);

 QFrame* fr = new QFrame;

 fr->setFrameStyle(QFrame::Sunken);
 fr->setFrameShape(QFrame::Panel);

 QHBoxLayout* fr_layout = new QHBoxLayout;
 fr_layout->addWidget(minimize_button);
 fr_layout->addWidget(minimize_label);

 fr->setLayout(fr_layout);

 result->addWidget(fr);
 result->addStretch();

 if(QGridLayout* gl = dynamic_cast<QGridLayout*>(qmb->layout()))
 {
  gl->addLayout(result, gl->rowCount(), 0, 1, gl->columnCount());
 }
 else
 {
  qDebug() << "Unexpected Message Box Layout: " << __FILE__;
 }

 return result;
}

