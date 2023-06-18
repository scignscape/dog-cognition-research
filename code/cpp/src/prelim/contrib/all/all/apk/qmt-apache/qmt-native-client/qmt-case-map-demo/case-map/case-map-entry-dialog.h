
//          Copyright Nathaniel Christen 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef CASE_MAP_ENTRY_DIALOG__H
#define CASE_MAP_ENTRY_DIALOG__H

#include <QObject>

#include <QMetaType>

#include <QList>

#include <QPoint>

#include <QDialog>
#include <QTableWidget>

#include <functional>

class QDialogButtonBox;
class QLabel;
class QLineEdit;
class QTabWidget;
class QTextEdit;
class QFrame;
class QHBoxLayout;
class QVBoxLayout;
class QSlider;
class QPlainTextEdit;
class QBoxLayout;
class QButtonGroup;
class QGroupBox;
class QScrollArea;
class QGridLayout;
class QMediaPlayer;
class QProcess;
class QTcpServer;

class ScignStage_Clickable_Label;

class XPDF_Bridge;

class QFormLayout;

class QComboBox;

class Case_Map_Entry_Dialog : public QDialog
{

 Q_OBJECT

 QDialogButtonBox* button_box_;
 QPushButton* button_ok_;
 QPushButton* button_cancel_;
 QPushButton* button_proceed_;


 //?QHBoxLayout* middle_layout_;
 QVBoxLayout* main_layout_;

 QVBoxLayout* entry_layout_;

 QGroupBox* info_group_box_;
 QGroupBox* location_group_box_;
 QGroupBox* children_group_box_;

 QHBoxLayout* info_group_box_layout_;
 QFormLayout* info_group_box_left_layout_;
 QFormLayout* info_group_box_right_layout_;

 QHBoxLayout* location_group_box_layout_;
 QFormLayout* location_group_box_left_layout_;
 QVBoxLayout* location_group_box_right_layout_;

 QVBoxLayout* children_group_box_layout_;

 QLineEdit* le_county_;
 QLineEdit* le_city_;
 QLineEdit* le_state_;


 QLineEdit* le_first_name_;
 QLineEdit* le_last_name_;
 QLineEdit* le_phone_number_;
 QLineEdit* le_email_;

 //QLabel* sentence_label_;

public:



 Case_Map_Entry_Dialog(QWidget* parent = nullptr);

 ~Case_Map_Entry_Dialog();

Q_SIGNALS:
 void canceled(QDialog*);
 void accepted(QDialog*);
 void take_screenshot_requested();

public Q_SLOTS:


 void accept();
 void cancel();


};

//_QSNS(ScignStage)


#endif //  CASE_MAP_ENTRY_DIALOG__H



