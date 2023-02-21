
//          Copyright Nathaniel Christen 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef E_DESIGNATION_DIALOG__H
#define E_DESIGNATION_DIALOG__H

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

class QCalendarWidget;

class ScignStage_Clickable_Label;

class XPDF_Bridge;

class QFormLayout;

class QComboBox;

class E_Designation_Dialog : public QDialog
{

 Q_OBJECT

 QDialogButtonBox* button_box_;
 QPushButton* button_ok_;
 QPushButton* button_cancel_;
 QPushButton* button_proceed_;


 //?QHBoxLayout* middle_layout_;
 QVBoxLayout* main_layout_;

 QFormLayout* form_layout_;

 QLineEdit* ed_number_line_edit_;


 QComboBox* ed_classification_combo_box_;
 QComboBox* zoning_classification_combo_box_;
 QComboBox* borough_combo_box_;

 QCalendarWidget* start_date_calendar_;

 QLineEdit* lot_number_line_edit_;
 QLineEdit* block_number_line_edit_;


 //QLabel* sentence_label_;

public:



 E_Designation_Dialog(QWidget* parent = nullptr, QString number = "(test)");

 ~E_Designation_Dialog();

Q_SIGNALS:
 void canceled(QDialog*);
 void accepted(QDialog*);
 void take_screenshot_requested();

public Q_SLOTS:


 void accept();
 void cancel();


};

//_QSNS(ScignStage)


#endif  // E_DESIGNATION_DIALOG__H





#ifdef HIDE

// //  "Pseudo" Toolbar ...
QHBoxLayout* top_buttons_layout_;

QPushButton* activate_tcp_button_;

QPushButton* take_screenshot_button_;


QScrollArea* grid_scroll_area_;
QFrame* main_frame_;
QGridLayout* main_grid_layout_;

QMap<Test_Sample*, QPair<QLabel*, int> > sample_to_label_map_;

Test_Sample* last_sample_;

QMediaPlayer* player_;

int current_index_;

int max_index_;

QWidget* last_highlight_;

int current_volume_;

QProcess* xpdf_process_;

quint64 current_tcp_msecs_;

int xpdf_port_;

QTcpServer* tcp_server_;

QString held_xpdf_msg_;

Phaon_Runner* phr_;

std::function<void(Phaon_Runner&)> phr_init_function_;
std::function<void()> screenshot_function_;

bool xpdf_is_ready();
void check_phr();

void run_msg(QString msg, QByteArray qba);
void run_kph(const QByteArray& qba);

void play_file_at_current_index();

void open_pdf_file(QString name, int page);

void check_launch_xpdf(std::function<void()> fn,
  std::function<void()> waitfn);
void send_xpdf_msg(QString msg);

QString load_about_file(QString name);

bool ask_pdf_proceed(QString name);

void run_smos_message(const QPoint& p, int col);
void run_nmos_message(const QPoint& p, int col);
void run_gmos_message(const QPoint& p, int col);

void run_test_with_load_message(const QPoint& p, int col);
void run_test_no_load_message(const QPoint& p, int col);

void run_about_context_menu(const QPoint& p, int col, std::function<void()> about_fn,
   std::function<void()> copy_fn, std::function<void()> save_fn);

void run_sample_context_menu(const QPoint& p, std::function<void()> play_fn,
   std::function<void()> copy_fn);


void run_message_by_grid_position(const QPoint& p, int r, int c);


#endif
