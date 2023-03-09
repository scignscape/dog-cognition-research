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

#include <QtGui>

#include "multiline-rubber-band.h"

//#include <QRubberBand>

#include <QAction>
#include <QMenu>

#include <QScrollBar>

#include <QScrollArea>

#include <QMessageBox>

#include <poppler-qt5.h>

#include <QDataStream>

#include "subwindows/pdf-document-widget.h"

#include "paraviews/dhax-pdf-view-dialog.h"

#include "rotateable-arrow-annotation.h"

#include "multiline-rubber-band.h"

USING_QSNS(Cy_Mesh)

PDF_Document_Widget::PDF_Document_Widget(QWidget *parent)
 : QGraphicsView(parent), //QLabel(parent),
   surrounding_scroll_area_(nullptr),
   context_menu_rubber_band_(nullptr),
   current_multistep_annotation_(nullptr)
{
 parent_dialog_ = qobject_cast<DHAX_PDF_View_Dialog*>(parent);

 //scene_ = new QGraphicsScene(this);


 //?this->setVerticalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );

 //setScene(scene_);

 currentPage = 0; //?-1;
 doc = 0;
 rubberBand = 0;
 scaleFactor = 1.0;
 setAlignment(Qt::AlignCenter);


 rubber_band_context_menu_ = new QMenu(this);
 rubber_band_delete_action_ = new QAction("Delete", this);
 rubber_band_context_menu_->addAction(rubber_band_delete_action_);

 rubber_band_select_action_ = new QAction("Select", this);
 rubber_band_context_menu_->addAction(rubber_band_select_action_);

 rubber_band_field_label_action_ = new QAction("Field Label", this);
 rubber_band_context_menu_->addAction(rubber_band_field_label_action_);

 connect(rubber_band_delete_action_, &QAction::triggered, [this]
 {
  if(context_menu_rubber_band_)
  {
   context_menu_rubber_band_->setVisible(false);
   visible_rubber_bands_[currentPage].removeOne(context_menu_rubber_band_);

   QRectF r = context_menu_rubber_band_->data(1).toRectF();
   rubber_band_rectangles_[currentPage].removeOne(r);

   context_menu_rubber_band_ = nullptr;
  }
 });

 connect(rubber_band_field_label_action_, &QAction::triggered, [this]
 {
  if(context_menu_rubber_band_)
  {
   QString label = context_menu_rubber_band_->data(0).toString();
   if(label.isEmpty())
   {

   }
   context_menu_rubber_band_ = nullptr;
  }
 });

 connect(rubber_band_select_action_, &QAction::triggered, [this]
 {
  if(context_menu_rubber_band_)
  {
   for(QGraphicsItem* si : scenes_[currentPage]->selectedItems())
   {
    si->setSelected(false);
   }

   context_menu_rubber_band_->setSelected(true);
   context_menu_rubber_band_ = nullptr;
  }

 });


 non_word_context_menu_ = new QMenu(this);
 word_context_menu_ = new QMenu(this);
 add_field_action_ = new QAction("Add Field", this);
 connect(add_field_action_ , &QAction::triggered,
         [this]
 {
  Q_EMIT (add_field_action_triggered(highlight_word_) );
  if(!scenes_[currentPage]->selectedItems().isEmpty())
  {
   QString hw = highlight_word_.simplified();
   hw.remove("_");
   QGraphicsItem* si = scenes_[currentPage]->selectedItems().first();
   si->setData(0, hw);
  }
 }
 );
 add_field_action_ ->setData( (int) Word_Context_Actions::Add_Field);
 word_context_menu_->addAction(add_field_action_);

 QAction* a1 = word_context_menu_->addAction("Save Stencil",
                                             [this]
 {
  Q_EMIT(save_stencil_to_file_requested());
 });
 non_word_context_menu_->addAction(a1);

 QAction* a2 = word_context_menu_->addAction("Open Stencil",
                                             [this]
 {
  Q_EMIT(open_stencil_from_file_requested());
 });
 non_word_context_menu_->addAction(a2);

 QAction* a3 = word_context_menu_->addAction("Remove Stencil",
                                             [this]
 {
  clear_stencil_geometry();
  //     context_menu_rubber_band_ = nullptr;
  //     visible_rubber_bands_.clear();
  //     rubber_band_rectangles_.clear();
 });
 non_word_context_menu_->addAction(a3);

 QAction* a4 = word_context_menu_->addAction("OCR Conversion",
                                             [this]
 {
  Q_EMIT(ocr_conversion_requested());
 });
 non_word_context_menu_->addAction(a4);


 //                                  SIGNAL(save_stencil_to_file_requested()));

 //save_stencil_to_file_action_ = new QAction("Save Stencil", this);
 //connect(add_field_action_ , &QAction::triggered,

 //    search_action_ = new QAction("Search", this);
 //    connect(search_action_, &QAction::triggered,
 //            [this]{ emit (search_action_triggered(highlight_word_) ); }
 //            );
 //    search_action_->setData( (int) Word_Context_Actions::Search);
 //    api_search_action_ = new QAction("Api Search", this);
 //    connect(api_search_action_, &QAction::triggered,
 //            [this]{ emit (api_search_action_triggered(highlight_word_) ); }
 //            );
 //    api_search_action_->setData( (int) Word_Context_Actions::Search);
 //    edit_artist_action_ = new QAction("Edit Artist", this);
 //    edit_artist_action_->setData( (int)  Word_Context_Actions::Edit_Artist);
 //    edit_author_action_ = new QAction("Edit Author", this);
 //    edit_author_action_->setData( (int)  Word_Context_Actions::Edit_Author);
 //    view_calendar_action_ = new QAction("View Calendar", this);
 //    view_calendar_action_->setData( (int)  Word_Context_Actions::View_Calendar);
 //    word_context_menu_->addAction(search_action_);
 //    word_context_menu_->addAction(api_search_action_);
 //    word_context_menu_->addAction(edit_artist_action_);
 //    word_context_menu_->addAction(edit_author_action_);
 //    word_context_menu_->addAction(view_calendar_action_);

 connect(word_context_menu_, SIGNAL(triggered(QAction*)),
         this, SLOT(word_context_menu_triggered(QAction*)));

}

PDF_Document_Widget::~PDF_Document_Widget()
{
 delete doc;
}

Poppler::Document* PDF_Document_Widget::document()
{
 return doc;
}

int PDF_Document_Widget::init_images(
  QMap<int, QMap<QImage*, QString> >& images)
{
 int result = 0;
 int c_page = currentPage;
 QMapIterator<int, QList<QGraphicsRectItem*> > it(visible_rubber_bands_);
 while(it.hasNext())
 {
  it.next();
  int key = it.key();
  const QList<QGraphicsRectItem*>& gis = it.value();
  result += gis.size();
  for(QGraphicsItem* gi : gis)
  {
   gi->setVisible(false);
   QRectF r = gi->boundingRect();
   QImage* qimage = new QImage(r.width(), r.height(), QImage::Format_Grayscale8);
   QPainter qpainter; //(&qimage);
   qpainter.begin(qimage);

   QRectF r1(0, 0, r.width(), r.height());
   qpainter.fillRect(r1, QColor(0, 0, 0, 32));

   if(!images_.contains(scenes_[key]))
   {
    showPage(key + 1);
   }

   scenes_[key]->render(&qpainter, r1, r);

   qpainter.end();

   int scale = 8;

   *qimage = qimage->scaled(qimage->width() * scale, qimage->height() * scale, Qt::KeepAspectRatio);

   images[key][qimage] = gi->data(0).toString();
  }
 }

 if(currentPage != c_page)
 {
  //currentPage = c_page;
  showPage(c_page + 1);
 }

 QMapIterator<int, QList<QGraphicsRectItem*> > it1(visible_rubber_bands_);
 while(it.hasNext())
 {
  it1.next();
  const QList<QGraphicsRectItem*>& ql = it1.value();
  for(QGraphicsItem* gi : ql)
  {
   gi->setVisible(true);
  }
 }
 return result;
 // pixmap = pixmap_;
 // for(QGraphicsItem* gi : visible_rubber_bands_)
 // {
 //  gi->setVisible(false);
 // }
 // pixmap = grab();
 // for(QGraphicsItem* gi : visible_rubber_bands_)
 // {
 //  gi->setVisible(true);
 // }

 //pixMap.save(fileName);
}



void PDF_Document_Widget::clear_stencil_geometry()
{
 QMapIterator<int, QList<QGraphicsRectItem*> > it(visible_rubber_bands_);
 while(it.hasNext())
 {
  it.next();
  const QList<QGraphicsRectItem*>& ql = it.value();
  for(QGraphicsItem* gi : ql)
  {
   gi->setVisible(false);
  }
 }
 context_menu_rubber_band_ = nullptr;
 rubber_band_rectangles_.clear();
 visible_rubber_bands_.clear();
}

void PDF_Document_Widget::load_stencil_geometry(const QByteArray& qba)
{
 clear_stencil_geometry();

 //?
 // rubber_band_rectangles_.clear();
 // visible_rubber_bands_.clear();
 //scenes_.clear();

 QDataStream qds(qba);

 QMap<int, QVector<QPair<QRectF, QString> > > mvp;

 qds >> mvp;

 QMapIterator<int, QVector<QPair<QRectF, QString> > > it(mvp);

 while(it.hasNext())
 {
  it.next();
  int key = it.key();

  //? visible_rubber_bands_[key].clear();

  const QVector<QPair<QRectF, QString> >& vp = it.value();
  for(QPair<QRectF, QString> pr : vp)
  {
   QRectF r1 = pr.first;

   //  QPolygonF poly = mapFromScene(r1);
   //  QRectF r = poly.boundingRect();


   rubber_band_rectangles_[key].push_back(r1);

   QBrush qbr = QBrush(QColor(255, 240, 255, 240));
   QPen qpen = QPen(QColor(25, 25, 25, 200));

   //  QPolygonF r1f = mapToScene(r.toRect());
   //  QRectF r1 = r1f.boundingRect();
   QGraphicsScene* scene = scenes_.value(key);
   if(!scene)
   {
    scene = new QGraphicsScene(this);
    scenes_[key] = scene;
   }
   QGraphicsRectItem* qgri = scene->addRect(r1, qpen, qbr);
   qgri->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);

   qgri->setData(0, pr.second);

   qgri->setData(1, r1);
   //  qgri->setData(2, r.y());
   //  qgri->setData(3, r.width());
   //  qgri->setData(4, r.height());


   //rb->setGeometry(qr);
   visible_rubber_bands_[key].push_back(qgri);
  }
 }

}

QMatrix PDF_Document_Widget::matrix() const
{
 return QMatrix(scaleFactor * physicalDpiX() / 72.0, 0,
                0, scaleFactor * physicalDpiY() / 72.0,
                0, 0);
}


void PDF_Document_Widget::get_stencil_geometry(QByteArray& qba)
{
 QDataStream qds(&qba, QIODevice::WriteOnly);

 QMap<int, QVector<QPair<QRectF, QString> > > mvp;

 //mvp.resize(rubber_band_rectangles_.size());

 QMapIterator<int, QList<QRectF> > it(rubber_band_rectangles_);

 while(it.hasNext())
 {
  it.next();
  int key = it.key();
  const QList<QRectF>& ql = it.value();


  mvp[key].resize(ql.size());

  int i = 0;
  for(QRectF r : ql)
  {
   //  QPolygonF r1f = mapToScene(r.toRect());
   //  QRectF r1 = r1f.boundingRect();
   mvp[key][i] = {r, QString()};
   ++i;
  }
 }

 QMapIterator<int, QGraphicsScene*> it1(scenes_);

 while(it1.hasNext())
 {
  it1.next();
  int key = it1.key();
  QGraphicsScene* scene = it1.value();

  for(auto it : scene->items())
  {
   QString str = it->data(0).toString();
   if(!str.isEmpty())
   {
    QRectF r = QRectF(it->data(1).toRectF());

    if(r.isValid())
    {
     for(QPair<QRectF, QString>& pr : mvp[key])
     {
      if(pr.first == r)
      {
       pr.second = str;
       break;
      }
     }
    }
   }
  }
 }

 qds << mvp;

}

//#ifdef HIDE
void PDF_Document_Widget::mousePressEvent(QMouseEvent *event)
{

 if (!doc)
  return;

 const QPointF posf = event->pos();

 qDebug() << "MPE: " << posf;

//? qDebug() << "EB: " << event->button();

 if(event->button() == (Qt::MouseButton::RightButton | Qt::MouseButton::LeftButton))
 {
//?  qDebug() << " sEB: " << event->button();

 }


 if(event->button() == Qt::MouseButton::RightButton)
 {
  if(active_left_mouse_drag_origin_.isNull())
  {
   // context menu?
  }
  else
  {
   //?current_arrow_annotation_->init_tip_phase(posf);
   current_multistep_annotation_->init_second_phase(posf);
   active_right_mouse_drag_origin_ = posf;

//   rubberBand->init_double_band(posf);
//   active_right_mouse_drag_origin_ = posf;
  }

 }
 else if(event->button() == Qt::MouseButton::LeftButton)
 {

  active_left_mouse_drag_origin_ = posf;

//  if(current_arrow_annotation_)
//  {
//   current_arrow_annotation_->reset_geometry(posf);
//  }
//  else
//  {
//   current_arrow_annotation_ = new Arrow_Annotation(posf, this);
//   dragPosition = event->pos();
//   current_arrow_annotation_->show();
////   return;
//  }

  if(current_multistep_annotation_)
  {
   current_multistep_annotation_->reset_geometry(posf);
  }
  else
  {
   //current_multistep_annotation_ = new MultiLine_Rubber_Band(QRubberBand::Rectangle, posf, this);
   current_multistep_annotation_ = new Rotateable_Arrow_Annotation(posf, this);
   dragPosition = event->pos();
   current_multistep_annotation_->show();
//   return;
  }


//? rb
//  if(rubberBand)
//    rubberBand->reset_geometry(posf);
//  else
//  {
//   rubberBand = new PDF_Rubber_Band(QRubberBand::Rectangle, posf, this);
//   dragPosition = event->pos();
//   rubberBand->show();
//  }

 }

 //  return;
 // return;


 //    if(!visible_rubber_bands_.isEmpty())
 //    {
 //     QPoint qp = event->pos();
 //     for(QGraphicsRectItem* rb : visible_rubber_bands_)
 //     {
 //      QRect qr = rb->rect().toRect();
 //      QPoint global_qp = mapToGlobal(qp);
 //      if(rb->rect().contains(qp))
 //      {
 //       raise_rubber_band_context_menu(global_qp);
 //       rubberBand->hide();
 //      }
 //     }
 //    }



// dragPosition = event->pos();
// if (!rubberBand)
//  rubberBand = new PDF_Rubber_Band(QRubberBand::Rectangle, this);
// rubberBand->setGeometry(QRect(dragPosition, QSize()));
// rubberBand->show();
}


void PDF_Document_Widget::wheelEvent(QWheelEvent* event)
{
 qDebug() << "Ad: " << event->angleDelta();
}

void PDF_Document_Widget::mouseMoveEvent(QMouseEvent *event)
{
 //? return;

 if (!doc)
  return;

 if(current_multistep_annotation_)
 {
  current_multistep_annotation_->adjust_geometry(event->pos());
  current_multistep_annotation_->repaint();
 }

//? if(rubberBand)
//? {
//?  rubberBand->adjust_geometry(event->pos());

//?  qDebug() << "event geometry = " << dragPosition;
//?  qDebug() << "event pos = " << event->pos();
//?  rubberBand->set_double_bottom_corner(event->pos());
 //? rubberBand->set_outer_end_corner(event->pos());

  //?rubberBand->setGeometry(QRect(dragPosition, event->pos()).normalized());

//?  rubberBand->repaint();

//  QRect qr = rubberBand->geometry();
//?  qDebug() << "qqr = "  << qr;
//? }

 event->ignore();

// if (!rubberBand)
//  return;

 //rubberBand->setGeometry(QRect(dragPosition, event->pos()).normalized());
}
//#endif

void PDF_Document_Widget::mouseReleaseEvent(QMouseEvent* qme)
{
// qme->ignore();
// return;

 if (!doc)
  return;

 if(qme->button() == Qt::MiddleButton)
 {
  qDebug() << "middle ...";
 }

 if(qme->button() == Qt::RightButton &&
   !active_left_mouse_drag_origin_.isNull())
 {
  active_right_mouse_drag_origin_ = {};

  if(current_multistep_annotation_)
    current_multistep_annotation_->finish_second_phase(qme->pos());

//?  if(rubberBand)
//?    rubberBand->finish_double_band(qme->pos());
  return;
 }


 if(qme->button() == Qt::LeftButton &&
   !active_left_mouse_drag_origin_.isNull())
 {

  if(current_multistep_annotation_)
    current_multistep_annotation_->finish_third_phase(qme->pos());

//?  if(rubberBand)
//?    rubberBand->complete_band(qme->pos());
 }

 //    if(!visible_rubber_bands_.isEmpty())
 //    {
 //     QPoint qp = qme->pos();
 //     for(QGraphicsRectItem* rb : visible_rubber_bands_)
 //     {
 //      QRect qr = rb->rect().toRect();
 //      QPoint global_qp = mapToGlobal(qp);
 //      if(rb->rect().contains(qp))
 //      {
 //       raise_rubber_band_context_menu(global_qp);
 //       rubberBand->hide();
 //      }
 //     }
 //    }

//??
 return;

 if(qme->button() == Qt::RightButton)
 {
  QPoint qp = qme->pos();

  for(QGraphicsRectItem* rb : visible_rubber_bands_[currentPage])
  {
   QPoint global_qp = mapToGlobal(qp);
   QPointF local_qp = mapToScene(qp);
   if(rb->rect().contains(local_qp))
   {
    context_menu_rubber_band_ = rb;

    QString label = context_menu_rubber_band_->data(0).toString();
    if(label.isEmpty())
    {
     rubber_band_field_label_action_->setText("No Field Set (undo)");
    }
    else
    {
     rubber_band_field_label_action_->setText(QString("Field: %1 (undo)").arg(label));
    }



    raise_rubber_band_context_menu(global_qp);
    rubberBand->hide();
    return;
   }

  }

  QRectF rect = QRectF(qp.rx(), qp.ry(), 1, 1);
  QString txt = get_selected_text(rect);
  if(!txt.isEmpty())
  {
   raise_context_menu(txt, qp);
  }
  else
  {
   raise_non_word_context_menu(qp);
  }
 }

 else if (rubberBand->size().isEmpty())
 {

 }
 else
 {
  QRectF rect = QRectF(rubberBand->pos(), rubberBand->size());

  //        rect.moveLeft(rect.left() - (width() - pixmap().width()) / 2.0);
  //        rect.moveTop(rect.top() - (height() - pixmap().height()) / 2.0);
  if(parent_dialog_)
  {
   if(parent_dialog_->wants_box())
   {
    QBrush qbr = QBrush(QColor(255, 240, 255, 240));
    QPen qpen = QPen(QColor(25, 25, 25, 200));

    QPolygonF r1f = mapToScene(rect.toRect());
    QRectF r1 = r1f.boundingRect();
    rubber_band_rectangles_[currentPage].push_back(r1);
    QGraphicsRectItem* qgri = scenes_[currentPage]->addRect(r1, qpen, qbr);
    qgri->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
    //rb->setGeometry(qr);
    qgri->setData(1, r1);
    visible_rubber_bands_[currentPage].push_back(qgri);
    //rb->show();
   }
   else
   {
    //        rect.moveLeft(rect.left() - (width() - pixmap().width()) / 2.0);
    //        rect.moveTop(rect.top() - (height() - pixmap().height()) / 2.0);

    QPolygonF r1f = mapToScene(rect.toRect());
    QRectF r1 = r1f.boundingRect();
    selectedText(r1, rect);
   }
  }
 }

 rubberBand->hide();
}


//#endif

void PDF_Document_Widget::word_context_menu_triggered(QAction* action)
{
 Word_Context_Actions wca = (Word_Context_Actions) action->data().toInt();

 Q_EMIT(word_context_action_requested(wca, highlight_word_));

 // switch(wca)
 // {
 // case Word_Context_Actions::Search:
 //  QMessageBox::information(this, "?", "search");
 //  break;

 // case Word_Context_Actions::Edit_Artist:
 //  QMessageBox::information(this, "?", "edit artisr");
 //  break;


 // }

}


void PDF_Document_Widget::raise_rubber_band_context_menu(QPoint qp)
{
 rubber_band_context_menu_->exec(qp);
}

void PDF_Document_Widget::raise_non_word_context_menu(QPoint qp)
{
 non_word_context_menu_->exec(mapToGlobal(qp));
}

void PDF_Document_Widget::raise_context_menu(QString text, QPoint qp)
{
 text = text.simplified();

 text.replace(QRegularExpression("[^\\w\\s-]+"), "");

 //search_action_->setText(QString("Search %1").arg(text));

 add_field_action_->setText(QString("Add Field: %1 ").arg(text));


 //      QAction* search_action = new QAction(QString("Search for %1").arg(txt), this);
 highlight_word_ = text;
 if(surrounding_scroll_area_)
 {
  //word_context_menu_->popup(qp);
  word_context_menu_->exec(
     surrounding_scroll_area_->viewport()->mapToGlobal(qp)
     -
     QPoint(surrounding_scroll_area_->horizontalScrollBar()->value(), surrounding_scroll_area_->verticalScrollBar()->value())
     );
 }
 else
 {
  word_context_menu_->exec(mapToGlobal(qp));

  //?word_context_menu_->exec(qp);
 }

}

//#ifdef HIDE

qreal PDF_Document_Widget::scale() const
{
 return scaleFactor;
}

void PDF_Document_Widget::showPage(int page, bool scale_changed)
{
 if (page != -1 && page != currentPage + 1)
 {
  currentPage = page - 1;
  //?emit pageChanged(page);
 }

 QGraphicsScene* scene = scenes_.value(currentPage, nullptr);

 QImage image;

 // scene could be initialized without the image if
 // user loads a stencil covering as-yet-unseen pages.
 if((!scale_changed) && scene && images_.contains(scene))
 {
  image = images_[scene];
  set_pixmap(QPixmap::fromImage(image));
 }
 else
 {
  if(!scene)
   scene = new QGraphicsScene(this);

  image = doc->page(currentPage)
    ->renderToImage(scaleFactor * physicalDpiX(), scaleFactor * physicalDpiY());

  images_[scene] = image;

  //setPixmap(QPixmap::fromImage(image))
  set_pixmap(QPixmap::fromImage(image));
  QGraphicsItem* gi = scene->addPixmap(pixmap_);
  gi->setZValue(-1);
  gi->setFlag(QGraphicsItem::ItemIsMovable);
  scenes_[currentPage] = scene;
 }

 if (!searchLocation.isEmpty())
 {
  QRect highlightRect = matrix().mapRect(searchLocation).toRect();
  highlightRect.adjust(-2, -2, 2, 2);
  QImage highlight = image.copy(highlightRect);
  QPainter painter;
  painter.begin(&image);
  painter.fillRect(image.rect(), QColor(0, 0, 0, 32));
  painter.drawImage(highlightRect, highlight);
  painter.end();
 }

 setScene(scene);

 //scene_->addPixmap(pixmap_);

 QRect rcontent = contentsRect();
 setSceneRect(0, 0, pixmap_.width() + 10, pixmap_.height() + 10);

 //?
 //
 verticalScrollBar()->setValue(1);

}

QRectF PDF_Document_Widget::searchBackwards(const QString &text)
{
 QRectF oldLocation = searchLocation;

 int page = currentPage;
 if (oldLocation.isNull())
  page -= 1;

 while (page > -1) {

  QList<QRectF> locations;
  searchLocation = QRectF();

  //?
  //        while (doc->page(page)->search(text, searchLocation,
  //            Poppler::Page::NextResult, Poppler::Page::CaseInsensitive)) {

  //            if (searchLocation != oldLocation)
  //                locations.append(searchLocation);
  //            else
  //                break;
  //        }

  int index = locations.indexOf(oldLocation);
  if (index == -1 && !locations.isEmpty()) {
   searchLocation = locations.last();
   showPage(page + 1);
   return searchLocation;
  } else if (index > 0) {
   searchLocation = locations[index - 1];
   showPage(page + 1);
   return searchLocation;
  }

  oldLocation = QRectF();
  page -= 1;
 }

 if (currentPage == doc->numPages() - 1)
  return QRectF();

 oldLocation = QRectF();
 page = doc->numPages() - 1;

 while (page > currentPage) {

  QList<QRectF> locations;
  searchLocation = QRectF();

  //?
  //        while (doc->page(page)->search(text, searchLocation,
  //            Poppler::Page::NextResult, Poppler::Page::CaseInsensitive)) {

  //            locations.append(searchLocation);
  //        }

  if (!locations.isEmpty()) {
   searchLocation = locations.last();
   showPage(page + 1);
   return searchLocation;
  }
  page -= 1;
 }

 return QRectF();
}

QRectF PDF_Document_Widget::searchForwards(const QString &text)
{
 int page = currentPage;
 while (page < doc->numPages()) {

  //?
  //if (doc->page(page)->search(text))
  qreal top = searchLocation.top();
  qreal right = searchLocation.right();
  qreal bottom = searchLocation.bottom();
  qreal left = searchLocation.left();

  if (doc->page(page)->search(text,
                              top,
                              right,
                              bottom,
                              left,
                              Poppler::Page::NextResult,
                              Poppler::Page::CaseSensitive,
                              Poppler::Page::Rotate0
                              //                        ,
                              //Poppler::Page::IgnoreCase, //searchLocation,
                              //Poppler::Page::NextResult //?, Poppler::Page::CaseInsensitive
                              ))
  {
   searchLocation.setTop(top);
   searchLocation.setBottom(bottom);
   searchLocation.setLeft(left);
   searchLocation.setRight(right);
   if (!searchLocation.isNull()) {
    showPage(page + 1);
    return searchLocation;
   }
  }

  page += 1;
  searchLocation = QRectF();
 }

 page = 0;

 while (page < currentPage) {

  searchLocation = QRectF();

  qreal top = searchLocation.top();
  qreal right = searchLocation.right();
  qreal bottom = searchLocation.bottom();
  qreal left = searchLocation.left();

  if (doc->page(page)->search(text,
                              top,
                              right,
                              bottom,
                              left,
                              Poppler::Page::NextResult,
                              Poppler::Page::CaseSensitive,
                              Poppler::Page::Rotate0
                              //                        ,
                              //Poppler::Page::IgnoreCase, //searchLocation,
                              //Poppler::Page::NextResult //?, Poppler::Page::CaseInsensitive
                              ))
  {
   searchLocation.setTop(top);
   searchLocation.setBottom(bottom);
   searchLocation.setLeft(left);
   searchLocation.setRight(right);
   if (!searchLocation.isNull()) {
    showPage(page + 1);
    return searchLocation;
   }
  }

  //?
  //        if (doc->page(page)->search(text, searchLocation,
  //            Poppler::Page::NextResult, Poppler::Page::CaseInsensitive)) {
  //            if (!searchLocation.isNull()) {
  //                showPage(page + 1);
  //                return searchLocation;
  //            }
  //        }

  page += 1;
 }

 return QRectF();
}

//QString PDF_Document_Widget::get_selected_text(const QRectF &rect)
//{


//}

void PDF_Document_Widget::selectedText(const QRectF& text_rect, const QRectF& screen_rect)
{
 QRectF selectedRect = matrix().inverted().mapRect(text_rect);
 // QString text = doc->page(currentPage)->text(selectedRect);

 QString summary;

 QString text;
 bool hadSpace = false;
 QPointF center;
 for (Poppler::TextBox *box : doc->page(currentPage)->textList())
 {
  //     summary += QString("[%1 %2 %3 %4] %5\n")
  //       .arg(box->boundingBox().left())
  //       .arg(box->boundingBox().top())
  //       .arg(box->boundingBox().right())
  //       .arg(box->boundingBox().bottom())
  //       .arg(box->text());


  if (selectedRect.intersects(box->boundingBox())) {
   if (hadSpace)
    text += " ";
   if (!text.isEmpty() && box->boundingBox().top() > center.y())
    text += "\n";
   text += box->text();
   hadSpace = box->hasSpaceAfter();
   center = box->boundingBox().center();
  }
 }

 //    QFile outfile("C:/ndpapp/docs/summary.txt");
 //    if(outfile.open(QIODevice::WriteOnly))
 //    {
 //     QTextStream outstream(&outfile);
 //     outstream << summary;
 //     outfile.close();
 //    }

 if (!text.isEmpty())
 {
  QPoint tr = screen_rect.topRight().toPoint();
  raise_context_menu(text, tr);

 }

 //   emit textSelected(text);
}

QString PDF_Document_Widget::get_selected_text(const QRectF &rect)
{
 QRectF selectedRect = matrix().inverted().mapRect(rect);
 // QString text = doc->page(currentPage)->text(selectedRect);

 QString result;
 bool hadSpace = false;
 QPointF center;
 for (Poppler::TextBox *box : doc->page(currentPage)->textList())
 {
  if (selectedRect.intersects(box->boundingBox())) {
   if (hadSpace)
    result += " ";
   if (!result.isEmpty() && box->boundingBox().top() > center.y())
    result += "\n";
   result += box->text();
   hadSpace = box->hasSpaceAfter();
   center = box->boundingBox().center();
  }
 }
 return result;
}

bool PDF_Document_Widget::setDocument(const QString &filePath)
{
 Poppler::Document *oldDocument = doc;

 doc = Poppler::Document::load(filePath);
 if (doc)
 {
  scenes_.clear();
  for(int i = 0;i < doc->numPages(); i++)
  {
   Poppler::Page *p = doc->page(i);
   for(Poppler::Link *li : p->links())
   {
    if(li->linkType() == Poppler::Link::Browse)
    {
     Poppler::LinkBrowse *link = static_cast<Poppler::LinkBrowse*>(li);
     url_list_.append(QUrl(link->url()));
    }
   }
  }

  delete oldDocument;
  doc->setRenderHint(Poppler::Document::Antialiasing);
  doc->setRenderHint(Poppler::Document::TextAntialiasing);
  searchLocation = QRectF();
  currentPage = -1;
  setPage(1);
 }
 return doc != 0;
}

int PDF_Document_Widget::number_of_pages()
{
 if(doc)
 {
  return doc->numPages();
 }
 return 0;
}


void PDF_Document_Widget::setPage(int page)
{
 if (page != currentPage + 1)
 {
  searchLocation = QRectF();
  showPage(page);
 }
}

void PDF_Document_Widget::setScale(qreal scale)
{
 if(scaleFactor != scale)
 {
  scaleFactor = scale;
  showPage();
 }
}

void PDF_Document_Widget::reset_scale(qreal scale)
{
 if(scaleFactor != scale)
 {
  scaleFactor = scale;
  showPage(-1, true);
 }
}
