
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

#include <QGeoLocation>

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
class QGridLayout;

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

 QPushButton* button_do_map_;

 QHBoxLayout* bottom_layout_;

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
 QFormLayout* children_group_box_layout_top_;
 QGridLayout* children_grid_layout_;

 QComboBox* cb_number_of_children_;

 QLineEdit* le_county_;
 QLineEdit* le_city_;
 QComboBox* cb_state_or_province_;


 QLineEdit* le_first_name_;
 QLineEdit* le_last_name_;
 QLineEdit* le_phone_number_;
 QLineEdit* le_email_;

 //QLabel* sentence_label_;

 void add_children_line();


public:



 Case_Map_Entry_Dialog(QWidget* parent = nullptr);

 ~Case_Map_Entry_Dialog();

Q_SIGNALS:
 void canceled(QDialog*);
 void accepted(QDialog*);
 void take_screenshot_requested();

 void location_marker_requested(QGeoLocation loc);

public Q_SLOTS:


 void accept();
 void cancel();


};

//_QSNS(ScignStage)


#endif //  CASE_MAP_ENTRY_DIALOG__H



