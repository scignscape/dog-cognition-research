
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "zq-web-engine-page.h"

#include "zq-web-engine-view.h"

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

 ZQ_Web_Engine_Page* wep = dynamic_cast<ZQ_Web_Engine_Page*>(target);

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



ZQ_Web_Engine_Page::ZQ_Web_Engine_Page(ZQ_Web_Engine_View* view) : QWebEnginePage(),
  view_(view)

{

}

ZQ_Web_Engine_Page::ZQ_Web_Engine_Page(ZQ_Web_Engine_Page* parent) : QWebEnginePage(parent)
{

}

//ZQ_Web_Engine_Page::ZQ_Web_Engine_Page():QWebEngineView()
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
ZQ_Web_Engine_Page::createWindow(QWebEnginePage::WebWindowType type)
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

void ZQ_Web_Engine_Page::emit_navRequest(const QUrl &url)
{
 const QPoint pos = view_->get_last_click_position();
 Q_EMIT navRequest(url, pos);
}

QString ZQ_Web_Engine_Page::last_youtube_link_as_non_embed()
{
 if(last_youtube_link_.isEmpty())
   return {};

 static QString prelim = "https://www.youtube.com/watch?v=";
 return prelim + last_youtube_link_;
}

void ZQ_Web_Engine_Page::reset_last_youtube_link(const QUrl &url)
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

bool ZQ_Web_Engine_Page::acceptNavigationRequest(const QUrl &url,
                                                   NavigationType type, bool isMainFrame)
{
 QString host = url.host();
 if(host == "www.youtube.com")
   reset_last_youtube_link(url);

 //?
 qDebug()  << "!url" << url;
 if (type == QWebEnginePage::NavigationTypeLinkClicked)
 {
          qDebug() << "?url" << url;
 }
 return true;
 // return false;
}


