
#ifndef DHAX_PDF_VIEW_DIALOG__H
#define DHAX_PDF_VIEW_DIALOG__H


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

//?QSNS_(Cy_Mesh)
//?namespace QScign{ namespace Cy_Mesh{


//?
//class NDP_Antemodel;
//class NDP_Project;
//class NDP_Project_Initial;


class DHAX_PDF_View_Dialog : public QDialog
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

 QDialogButtonBox* button_box_;
// QPushButton* button_ok_;
// QPushButton* button_cancel_;
// QPushButton* button_proceed_;
 QPushButton* button_close_;

 QLabel* url_label_;
 QLineEdit* url_line_edit_;

 PDF_Document_Widget* pdf_document_widget_;

 QHBoxLayout* url_layout_;
 QVBoxLayout* main_layout_;
 //?NDP_Antemodel* antemodel_;
 QScrollArea* pdf_document_scroll_area_;

// QHBoxLayout* go_button_layout_;
 QPushButton* go_button_;
 QPushButton* open_button_;

// QHBoxLayout* close_button_layout_;
// QPushButton* close_button_;

 void read_file(QString path, QPlainTextEdit* qpte);

 void retranslate_ui();

public:

 DHAX_PDF_View_Dialog(QWidget* parent, QString pdf_file_path); //, NDP_Antemodel* antemodel);
 ~DHAX_PDF_View_Dialog();

 ACCESSORS(QString ,pdf_file_path)


 void activate_search(QString text);

 bool wants_box();

 //int get_vertical_scroll();

Q_SIGNALS:
 void canceled(QDialog*);
 void accepted(QDialog*);

public Q_SLOTS:
 void accept();
 void cancel();

 //?void proceed();
 //void go_button_clicked();

};

//?} } //_QSNS(Cy_Mesh)


#endif //  VIEW_PDF_DIALOG__H
