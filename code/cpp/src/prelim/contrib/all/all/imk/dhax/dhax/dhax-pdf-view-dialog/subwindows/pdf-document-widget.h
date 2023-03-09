/****************************************************************************
**
** Copyright (C) 2008 Nokia Corporation and/or its subsidiary(-ies).
** Contact: Qt Software Information (qt-info@nokia.com)
**
** This file is part of the documentation of Qt. It was originally
** published as part of Qt Quarterly.
**
** Commercial Usage
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Nokia.
**
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License versions 2.0 or 3.0 as published by the Free
** Software Foundation and appearing in the file LICENSE.GPL included in
** the packaging of this file.  Please review the following information
** to ensure GNU General Public Licensing requirements will be met:
** http://www.fsf.org/licensing/licenses/info/GPLv2.html and
** http://www.gnu.org/copyleft/gpl.html.  In addition, as a special
** exception, Nokia gives you certain additional rights. These rights
** are described in the Nokia Qt GPL Exception version 1.3, included in
** the file GPL_EXCEPTION.txt in this package.
**
** Qt for Windows(R) Licensees
** As a special exception, Nokia, as the sole copyright holder for Qt
** Designer, grants users of the Qt/Eclipse Integration plug-in the
** right for the Qt/Eclipse Integration to link to functionality
** provided by Qt Designer and its related libraries.
**
** If you are unsure which license is appropriate for your use, please
** contact the sales department at qt-sales@nokia.com.
**
****************************************************************************/

#ifndef PDF_DOCUMENT_WIDGET__H
#define PDF_DOCUMENT_WIDGET__H

#include <QLabel>
#include <QRectF>

#include <poppler-qt5.h>

#include <QMenu>
#include <QAction>
#include <QRubberBand>

#include <QPixmap>

#include <QGraphicsView>
#include <QGraphicsRectItem>

#include "accessors.h"

#include "qsns.h"

class MultiLine_Rubber_Band;
class Arrow_Annotation;

class MultiStep_Annotation_Base;

class QScrollArea;

//?
//QSNS_CLASS_DECLARE(Cy_Mesh ,dhax_PDF_View_Dialog)
//USING_QSNS(Cy_Mesh)

class DHAX_PDF_View_Dialog;


class PDF_Document_Widget : public QGraphicsView //QLabel
{
 Q_OBJECT

public:
 enum class Word_Context_Actions {
  N_A, Add_Field, Search,  Edit_Author, View_Calendar
 };

private:

 QPointF active_right_mouse_drag_origin_;
 QPointF active_left_mouse_drag_origin_;

 QScrollArea* surrounding_scroll_area_;
 QMenu* word_context_menu_;
 QMenu* non_word_context_menu_;
 QAction* add_field_action_;
// QAction* search_action_;
// QAction* edit_artist_action_;
// QAction* edit_author_action_;
// QAction* view_calendar_action_;
// QAction* api_search_action_;


 QMenu* rubber_band_context_menu_;
 QAction* rubber_band_delete_action_;
 QAction* rubber_band_select_action_;
 QAction* rubber_band_field_label_action_;

 QString highlight_word_;

 QGraphicsRectItem* context_menu_rubber_band_;

 QMap<int, QList<QGraphicsRectItem*> > visible_rubber_bands_;

 QMap<int, QList<QRectF> > rubber_band_rectangles_;

 DHAX_PDF_View_Dialog* parent_dialog_;

 QMap<int, QGraphicsScene*> scenes_;

 QMap<QGraphicsScene*, QImage> images_;

 QPixmap pixmap_;

// Arrow_Annotation* current_arrow_annotation_;
 MultiStep_Annotation_Base* current_multistep_annotation_; // current_arrow_annotation_;



public:

    PDF_Document_Widget(QWidget *parent = 0);
    ~PDF_Document_Widget();

    ACCESSORS(QScrollArea* ,surrounding_scroll_area)
    ACCESSORS(QPixmap ,pixmap)

    Poppler::Document* document();
    QMatrix matrix() const;
    qreal scale() const;

    void get_stencil_geometry(QByteArray& qba);
    void load_stencil_geometry(const QByteArray& qba);
    void clear_stencil_geometry();


    int init_images(QMap<int, QMap<QImage*, QString> >& images);

    int number_of_pages();


public Q_SLOTS:
    QRectF searchBackwards(const QString &text);
    QRectF searchForwards(const QString &text);
    bool setDocument(const QString &filePath);
    void setPage(int page = -1);
    void setScale(qreal scale);
    void reset_scale(qreal scale);

    void word_context_menu_triggered(QAction*);

protected:
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

    void wheelEvent(QWheelEvent *event) Q_DECL_OVERRIDE;

Q_SIGNALS:
    void pageChanged(int currentPage);
    void textSelected(const QString &text);

    void add_field_action_triggered(QString search_text);

    void api_search_action_triggered(QString search_text);
    void search_action_triggered(QString search_text);
    void word_context_action_requested(PDF_Document_Widget::Word_Context_Actions, QString);

    void save_stencil_to_file_requested();
    void open_stencil_from_file_requested();

    void ocr_conversion_requested();

private:


    QList<QUrl> url_list_;

    QString get_selected_text(const QRectF &rect);

    void selectedText(const QRectF& text_rect, const QRectF& screen_rect);
    void showPage(int page = -1, bool scale_changed = false);

    void raise_non_word_context_menu(QPoint qp);

    void raise_context_menu(QString text, QPoint p);
    void raise_rubber_band_context_menu(QPoint p);

    Poppler::Document *doc;
    int currentPage;
    QPoint dragPosition;
    MultiLine_Rubber_Band* rubberBand;

    QRectF searchLocation;
    qreal scaleFactor;
};

#endif
