
//          Copyright Nathaniel Christen 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include "qmt-web-engine-view.h"

#include <QTimer>


//#include "context-menu-provider.h"
//#include "url-or-event-pattern.h"

#include <QDialog>


QMT_Web_Engine_View::QMT_Web_Engine_View(QDialog* parent_dialog)
  :  QWebEngineView(), parent_dialog_(parent_dialog), context_menu_provider_(nullptr)
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
     resize(qs.width(), height());
  }
 });

}

bool QMT_Web_Engine_View::eventFilter(QObject *object, QEvent *event)
{
 if (object->parent() == this && event->type() == QEvent::MouseButtonPress)
 {
  QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
  Qt::MouseButton mb = mouseEvent->button();

  if(mb == Qt::RightButton)
  {
   QPoint qp = mouseEvent->globalPos();

   QTimer::singleShot(250, [this, qp]
   {
    Context_Menu_Info* cmi = context_menu_info_.value({qp.x(), qp.y()});
    generate_context_menu(qp, (n8) this, cmi);
   });
   event->ignore();
  }
 }
 return false;

}

void QMT_Web_Engine_View::generate_context_menu(const QPoint& pos, n8 origin,
  Context_Menu_Info* cmi, QMouseEvent* mev)
{
 qDebug() << "pos = " << pos;
}

void QMT_Web_Engine_View::check_sec()
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

void QMT_Web_Engine_View::contextMenuEvent(QContextMenuEvent* event)
{
 //
 qDebug() << "event->reason()";
 qDebug() << event->reason();

 QWebEngineContextMenuData cd = page()->contextMenuData();

 QString url = page()->url().toString();

#ifdef HIDE
 QVector<Pattern_Matcher_Runtime::Action_Info> info;

 auto check = [this, &event](QString& args)
 {
  args.replace("$winid$", QString::number(parent_dialog_->winId()));
  args.replace("$gx$", QString::number(event->globalX()));
  args.replace("$gy$", QString::number(event->globalY()));
 };

 if(cd.linkUrl().isEmpty())
   pm_runtime_->check_url_patterns(
     URL_Or_Event_Pattern::Pattern_Contexts::Context_Menu_Formation, url, info, check);

 else
   pm_runtime_->check_url_patterns(
     URL_Or_Event_Pattern::Pattern_Contexts::Link_Context_Menu_Formation,
     cd.linkUrl().toString(), info, check, cd.linkText());

 QMenu* menu = new QMenu(this);//

 for(Pattern_Matcher_Runtime::Action_Info& ai : info)
 {
  menu->addAction(ai.option_label, [this, ai]
  {
   context_menu_provider_->run_callback(ai);
  });
  qDebug() << ai.option_label;
 }

// if(info.isEmpty())
// {
//  menu->addAction("Review Matterport Tags");
//  menu->addAction("Launch Tag Dialog");
//  menu->addAction("View Sensor Data");
//  menu->addAction("View Pattern Match Data");
// }


//   page()->createStandardContextMenu();

// for(QAction* a : menu->actions())
// {
//  qDebug()<< a->text();
// }

// QWebEngineContextMenuData cd = page()->contextMenuData();

// QUrl test = //cd.d->frameUrl();
//   cd.frameUrl();


 if(this->url().toString().contains("www.google.com/maps/place"))
 {
  qDebug() << "TU:" << this->url().toString();
  qDebug() << "TU:" << this->page()->url().toString();
 }


// qDebug() << "ST:" << cd.selectedText();

// if(!cd.linkText().isEmpty())
//   qDebug() << "LT:" << cd.linkText();

// if(!cd.linkUrl().isEmpty())
//   qDebug() << "LU:" << cd.linkUrl().toString();

// qDebug() << "mT:" << cd.mediaType();
// qDebug() << "mU:" << cd.mediaUrl().toString();


// menu->addAction("Test");

 menu->popup(event->globalPos());
#endif //def HIDE
}

