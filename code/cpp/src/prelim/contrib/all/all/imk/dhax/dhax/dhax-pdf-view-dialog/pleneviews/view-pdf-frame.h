
#ifndef VIEW_PDF_FRAME__H
#define VIEW_PDF_FRAME__H


#include <QString>
#include <QMainWindow>

#include <QTextEdit>
//?#include <QWebView>

#include <QWebEngineView>
#include <QLabel>
#include <QPushButton>

#include <QDialog>
#include <QSpinBox>
#include <QComboBox>
#include <QRubberBand>

#include "accessors.h"

#include "flags.h"

#include "qsns.h"

#include "subwindows/reverse-spinbox.h"

//?#include "view-ocr-fields-dialog.h"

class PDF_Document_Widget;

//#include "incident-form-dialog.h"

class QPushButton;
class QTextEdit;
class QPlainTextEdit;
class QLineEdit;
class QTabWidget;
class QDialogButtonBox;
class QVBoxLayout;
class QHBoxLayout;
class QCheckBox;
class QFormLayout;
class QSplitter;
class QGridLayout;
class QListWidget;
class QTableWidget;
class QScrollArea;
class QGroupBox;
class QTableWidgetItem;

//QSNS_(ScignSeer)
//namespace QScign{ namespace ScignSeer{


class NDP_Antemodel;
class NDP_Project;
class NDP_Project_Initial;


class View_PDF_Frame : public QFrame
{
 Q_OBJECT

 QString pdf_file_path_;

 QList<QRubberBand*> rubber_bands_;


// QFrame* controls_frame_;
 QVBoxLayout* controls_layout_;
 //QDockWidget* controls_dock_widget_;
 Reverse_Spin_Box* page_spin_box_;
 QLineEdit* search_line_edit_;
 QLabel* search_label_;
 QLabel* page_label_;
 QLabel* scale_label_;
 QComboBox* scale_combo_box_;
 QComboBox* search_combo_box_;
 QPushButton* find_button_;
 QPushButton* clear_button_;

 QPushButton* box_button_;


 QLabel* url_label_;
 QLineEdit* url_line_edit_;

 PDF_Document_Widget* pdf_document_widget_;

 QHBoxLayout* url_layout_;
 QVBoxLayout* main_layout_;
 NDP_Antemodel* antemodel_;
 QScrollArea* pdf_document_scroll_area_;

// QHBoxLayout* go_button_layout_;
 QPushButton* go_button_;
 QPushButton* open_button_;

// QHBoxLayout* close_button_layout_;
// QPushButton* close_button_;

 void read_file(QString path, QPlainTextEdit* qpte);

 void retranslate_ui();

public:

 View_PDF_Frame(QWidget* parent, QString pdf_file_path); //, NDP_Antemodel* antemodel);
 ~View_PDF_Frame();

 ACCESSORS(QString ,pdf_file_path)

 void load_file(QString path);


 void activate_search(QString text);

 bool wants_box();


// Q_SIGNALS:

// public Q_SLOTS:

};

//} } //_QSNS(ScignSeer)


#endif //  VIEW_PDF_DIALOG__H
