
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef BIM_SELECT_DIALOG__H
#define BIM_SELECT_DIALOG__H

#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QDialog>

#include <QTableWidget>
#include <QFrame>


class BIM_Select_Dialog : public QDialog
{
 Q_OBJECT

 QDialogButtonBox* button_box_;
 QPushButton* button_ok_;
 QPushButton* button_cancel_;

 QVBoxLayout* main_layout_;
 QGridLayout* labels_layout_;


public:


 BIM_Select_Dialog(QWidget* parent);
 ~BIM_Select_Dialog();

 void dg_label_cb(QString text);
 void dg_info_cb(QString text);


Q_SIGNALS:

 void text_chosen(QString text);


};




#endif
