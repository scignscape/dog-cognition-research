
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "qh-web-engine-page.h"

#include "qh-web-engine-view.h"

#include "global-types.h"

NavigationRequestInterceptor::NavigationRequestInterceptor(QWebEnginePage*
                                                           parent)
 : QWebEnginePage(parent)
{
 target = parent;
}

bool NavigationRequestInterceptor::acceptNavigationRequest(const QUrl
                                                           &url, NavigationType type, bool isMainFrame)
{
 qDebug() << "acceptNavigationRequest called. type=" << type <<
             "isMainFrame=" << isMainFrame;

 qDebug() << "acceptNavigationRequest called. url=" << url.toString();

 //    MyWebPage *page = dynamic_cast<MyWebPage*>(target);
 //    if (/*isMainFrame && */type == NavigationTypeLinkClicked && page)
 //        Q_EMIT page->urlClicked(url);
 //    else
 //        target->load(url);

 QH_Web_Engine_Page* wep = dynamic_cast<QH_Web_Engine_Page*>(target);

 wep->emit_navRequest(url);

 return false;
}

//and then you return an instance of that in createWindow

//QWebEngineView*WebEngineView::createWindow(QWebEnginePage::WebWindowType type)
//{
//    Q_UNUSED(type);

//    qDebug() << "createWindow called, returning NavigationRequestInterceptor";
//    WebEngineView *result = new WebEngineView();
//    result->setPage(new NavigationRequestInterceptor(this->page()));
//    return result;
//}



QH_Web_Engine_Page::QH_Web_Engine_Page(QH_Web_Engine_View* view) : QWebEnginePage(),
  view_(view)

{

}

QH_Web_Engine_Page::QH_Web_Engine_Page(QH_Web_Engine_Page* parent) : QWebEnginePage(parent)
{

}

//QH_Web_Engine_Page::QH_Web_Engine_Page():QWebEngineView()
//{
// sec  =  nullptr;
//}
//class MyPage : public QObject
//{
//public:
// MyPage();


//};
//MyPage::MyPage():QObject()
//{

//}

//MyWebPage* MyWebPage::createWindow(WebWindowType type)
//{
//    qDebug()  << "WebWindowType" << type;

// return nullptr;
//}

NavigationRequestInterceptor*
QH_Web_Engine_Page::createWindow(QWebEnginePage::WebWindowType type)
{
 qDebug()  << "WebWindowType" << type;

 qDebug() << "createWindow called, returningNavigationRequestInterceptor";

 NavigationRequestInterceptor *result = new NavigationRequestInterceptor(this);
 //result->setPage(new NavigationRequestInterceptor(this->page()));
 return result;

}

//MyWebView* MyWebView::createWindow(QWebEnginePage::WebWindowType type)
//{
//    qDebug()  << "WebWindowType" << type;

//        qDebug() << "createWindow called, returningNavigationRequestInterceptor";

//        qDebug()  << "r" << this->page()->requestedUrl().toString();


//        MyWebView *result = new MyWebView();
//        result->setPage(new NavigationRequestInterceptor(this->page()));
//        return result;

////    sec = new MyWebView;

////    connect(sec, &QWebEngineView::loadFinished, [this](bool b)
////    {
////        qDebug()  << "Web::: " << sec->page()->url();
////    });

////check_sec();
//// return sec;
//}

void QH_Web_Engine_Page::emit_navRequest(const QUrl &url)
{
 const QPoint pos = view_->get_last_click_position();
 Q_EMIT navRequest(url, pos);
}

QString QH_Web_Engine_Page::last_youtube_link_as_non_embed()
{
 if(last_youtube_link_.isEmpty())
  return {};

 static QString prelim = "https://www.youtube.com/watch?v=";
 return prelim + last_youtube_link_;
}

void QH_Web_Engine_Page::reset_last_youtube_link(const QUrl &url)
{
 // qDebug() << "p = " << url.path();
 if(url.path().startsWith("/embed/"))
 {
  if(int index = url.path().indexOf('?'))
   last_youtube_link_ = url.path().mid(7, index - 7);
 }

 // qDebug() << "l = " << last_youtube_link_;
 // qDebug() << "l = " << last_youtube_link_as_non_embed();

}

bool QH_Web_Engine_Page::acceptNavigationRequest(const QUrl &url,
                                                 NavigationType type, bool isMainFrame)
{
 QString host = url.host();
 if(host == "www.youtube.com")
  reset_last_youtube_link(url);

 //?

 QString url_string = url.toString();
 QString path = url.path();

 qDebug()  << "!url" << url_string;

 if(_cut("/_qhr-" ,path))
 {
  QString fragment = url.fragment();
  QString query = url.query(QUrl::FullyDecoded);
  qDebug() << "!!query" << query;
  qDebug() << "f?url" << path;

  const QPoint pos = view_->get_last_click_position();

  Q_EMIT qh_link_request(url, pos, view_->size(), path, type);

  return false;
 }

 return true;

#ifdef HIDE
 if (type == QWebEnginePage::NavigationTypeLinkClicked)
 {
  qDebug() << "?url" << url;
//  QString cut = "/_qhr-";
//  if(path.startsWith("/_qhr-"))

  if(_cut("/_qhr-" ,path))
  {
   QString fragment = url.fragment();
   QString query = url.query(QUrl::FullyDecoded);

   qDebug() << "!!path" << path;
   qDebug() << "!!fragment" << fragment;
   qDebug() << "!!query" << query;

   return false;
  }
 }

 else if (type == QWebEnginePage::NavigationTypeFormSubmitted)
 {
  if(_cut("/_qhr-" ,path))
  {
   qDebug() << "!!query" << query;

   qDebug() << "f?url" << path;
   return false;
  }
 }

 else if (type == QWebEnginePage::NavigationTypeRedirect)
 {
  qDebug() << "r?url" << url;
 }
 return true;
 // return false;

#endif
}


