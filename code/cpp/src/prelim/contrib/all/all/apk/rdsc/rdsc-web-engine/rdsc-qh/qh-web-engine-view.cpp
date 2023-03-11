
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "qh-web-engine-view.h"

//#include "context-menu-provider.h"
//#include "url-or-event-pattern.h"

#include "qh-web-view-dialog.h"

#include <QDialog>
#include <QTimer>

#include <QScreen>
#include <QWebEngineSettings>

#include <QAbstractScrollArea>
#include <QScrollBar>

#include <QOpenGLWidget>

// //  note: in case there is a need to inspect the QWebEngineView
 //    parent classes ...
 //    #include "render_widget_host_view_qt_delegate_widget.h"

#include <QLayout>

#include "qh-web-engine-page.h"


USING_KANS(RdSC)


QH_Web_Engine_View::QH_Web_Engine_View(QDialog* parent_dialog)
 :  QWebEngineView(), parent_dialog_(parent_dialog), context_menu_provider_(nullptr),
    scroll_container_(nullptr)
{
 sec  =  nullptr;

 QApplication::instance()->installEventFilter(this);
 setMouseTracking(true);

 connect(this, &QWebEngineView::loadFinished, [this](bool ok)
 {
  if(ok)
  {
   QSize qs = page()->contentsSize().toSize();
   if(!qs.isEmpty())
     resize(qs);
  }
 });
}

const QPoint QH_Web_Engine_View::get_last_click_position()
{
 if(positions_.isEmpty())
   return {};

 return positions_.top();
}


bool QH_Web_Engine_View::eventFilter(QObject *object, QEvent *event)
{
// if(page())
//   qDebug() << "current url = " << page()->url();


// if(page())
// {
//  if(page()->settings())
//    page()->settings()->setAttribute(QWebEngineSettings::ShowScrollBars, false);
// }

 if (object->parent() == this && event->type() == QEvent::MouseButtonPress)
 {
  QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
  Qt::MouseButton mb = mouseEvent->button();

  if(mb == Qt::RightButton)
  {
   QPoint qp = mouseEvent->globalPos();
   QPoint pos = mouseEvent->pos();

   QTimer::singleShot(250, [this, qp, pos]
   {
    Context_Menu_Info* cmi = context_menu_info_.value({qp.x(), qp.y()});
    generate_context_menu(qp, pos, (n8) this, cmi);
   });
   event->ignore();
  }

  if(mb == Qt::LeftButton)
  {
   QPoint qp = mouseEvent->globalPos();
   qDebug() << " lb = " << qp;
   positions_.push(qp);
//   return true;
  }

 }
 return false;
}

void QH_Web_Engine_View::grab_snapshot(QWidget* full_size)
{
 // //  full_size is only non-null if user explicitly requests
  //    complete image; otherwise assume user wants image
  //    from the visible part of the view, inside the
  //    scroll container's viewport.
 if(!full_size)
   full_size = scroll_container_->viewport();

 QPixmap pm = full_size->grab();

 QString path = SCREENSHOTS_FOLDER "/iat-chasm.png";
 qDebug() << "Saving to path: " << path;

 QFile file(path);
 if(file.open(QIODevice::WriteOnly))
 {
  pm.save(&file, "PNG");
 }
 file.close();

 Q_EMIT snapshot_saved(path);
}


void QH_Web_Engine_View::parse_zoom_and_coordinates(QUrl url, std::tuple<r8&, r8&, r8&, r8&, s1&>& result)
{
 parse_zoom_and_coordinates(url.fragment(), result);
}

void QH_Web_Engine_View::parse_zoom_and_coordinates(QString url_fragment, std::tuple<r8&, r8&, r8&, r8&, s1&>& result)
{
 QStringList qsl = url_fragment.split('/');

 r8 offset = 2;

//? qDebug() << "qsl = " << qsl;

#define NaN_Constant std::numeric_limits<r8>::quiet_NaN()

 if(qsl.size() < 3)
 {
  std::get<3>(result) = NaN_Constant;
 }
 else
 {
  std::get<0>(result) = qsl[1].toDouble();
  std::get<1>(result) = qsl[2].toDouble();
  std::get<2>(result) = qsl[0].toDouble();
  std::get<3>(result) = std::get<2>(result) + offset;
  std::get<4>(result) = (s1) std::get<2>(result);
 }
}


void QH_Web_Engine_View::generate_context_menu(const QPoint& gpos,
  const QPoint& pos, n8 origin, Context_Menu_Info* cmi, QMouseEvent* mev)
{
 QWidget* origin_widget = nullptr;

 if(origin != (n8) this)
 {
  origin_widget = (QWidget*) origin;
  // //
 }


 QH_Web_Engine_Page* rpage = qobject_cast<QH_Web_Engine_Page*>(this->page());

 QMenu* menu = new QMenu(this);
 menu->popup(gpos);
}

 void QH_Web_Engine_View::check_sec()
 {
  if(sec)
  {
   qDebug()  << "sec: "  <<   sec->page()->url().toString();
  }
  else
  {
   qDebug()  << "xsec";
  }
 }


 void QH_Web_Engine_View::mouseReleaseEvent(QMouseEvent* mouseEvent)
 {
  mouseEvent->ignore();
 }


 void QH_Web_Engine_View::mousePressEvent(QMouseEvent* mev)
 {
  Qt::MouseButton mb = mev->button();

  if(mb == Qt::RightButton)
  {
   qDebug() << "internal ... ";
   generate_context_menu(mev->globalPos(), mev->pos(), (n8) this, nullptr, mev);
   mev->accept();
  }
  else
  mev->ignore();

  // qDebug() << "mb = " << mb;

  // const QWebEngineContextMenuData& cd = page()->contextMenuData();

  // QString url = page()->url().toString();

  // if(url.isEmpty())
  // {
  //  QMenu* menu = new QMenu(this);//
  //  menu->addAction("Test ...");
  //  menu->popup(mouseEvent->globalPos());

  // }
  // else
  // {
  //  mouseEvent->ignore();
  // }

  // QMenu* menu = new QMenu(this);//
  // menu->popup(event->globalPos());

 }

 void QH_Web_Engine_View::contextMenuEvent(QContextMenuEvent* event)
 {
  const QWebEngineContextMenuData& cd = page()->contextMenuData();

  QPoint qp = event->globalPos();

  static QMap<QWebEngineContextMenuData::MediaType, QString> media_types {
   { QWebEngineContextMenuData::MediaTypeNone, "None" },
   { QWebEngineContextMenuData::MediaTypeVideo, "Video" },
   { QWebEngineContextMenuData::MediaTypeAudio, "Audio" },
   { QWebEngineContextMenuData::MediaTypeCanvas, "Canvas" },
   { QWebEngineContextMenuData::MediaTypeFile, "File" },
   { QWebEngineContextMenuData::MediaTypePlugin, "Plugin" },
  };

  Context_Menu_Info* cmi = new Context_Menu_Info({
   {{"selected-text", cd.selectedText()},
    {"link-text", cd.linkText()},
    {"link-url", cd.linkUrl().toString()},
    {"media-type", media_types.value(cd.mediaType())}
   },
   {
    {"media-flags", (n8) cd.mediaFlags()},
    {"edit-flags", (n8) cd.editFlags()},
    {"generic-flags", (n8) cd.isValid() + ((n8)cd.isContentEditable() << 1)}
   }});

  context_menu_info_[{qp.x(), qp.y()}] = cmi;
 }

