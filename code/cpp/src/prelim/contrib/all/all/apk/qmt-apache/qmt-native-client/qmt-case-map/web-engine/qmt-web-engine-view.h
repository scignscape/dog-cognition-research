
//          Copyright Nathaniel Christen 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef QMT_WEB_ENGINE_VIEW__H
#define QMT_WEB_ENGINE_VIEW__H


#include <QWebEngineView>
#include <QMainWindow>
#include <QApplication>
#include <QTabWidget>
#include <QWebChannel>
#include <QWebEnginePage>
#include <QContextMenuEvent>
#include <QMenu>
#include <QWebEngineContextMenuData>

#include "accessors.h"

#include "global-types.h"

////class NavigationRequestInterceptor;
//class NavigationRequestInterceptor : public QWebEnginePage
//{
// QWebEnginePage* target;
//public:
// NavigationRequestInterceptor(QWebEnginePage* parent);
// bool acceptNavigationRequest(const QUrl &url, NavigationType type,
//                              bool isMainFrame) Q_DECL_OVERRIDE;
//};

class Context_Menu_Provider;
class Pattern_Matcher_Runtime;

class QMT_Web_Engine_View : public QWebEngineView
{
 Context_Menu_Provider* context_menu_provider_;
 Pattern_Matcher_Runtime* pm_runtime_;

 QDialog* parent_dialog_;

 struct Context_Menu_Info
 {
  QMap<QString, QString> string_info_;
  QMap<QString, n8> flags_info_;
 };

 QMap<QPair<int, int>, Context_Menu_Info*> context_menu_info_;

 void generate_context_menu(const QPoint& pos, n8 origin,
   Context_Menu_Info* cmi, QMouseEvent* mev = nullptr);


public:

 QMT_Web_Engine_View(QDialog* parent_dialog);

 ACCESSORS(Context_Menu_Provider* ,context_menu_provider)
 ACCESSORS(Pattern_Matcher_Runtime* ,pm_runtime)

 QMT_Web_Engine_View* sec;

 void contextMenuEvent(QContextMenuEvent *event) Q_DECL_OVERRIDE;
 bool eventFilter(QObject *object, QEvent *event) Q_DECL_OVERRIDE;

 //?    MyWebView* createWindow(QWebEnginePage::WebWindowType type) override;
 void check_sec();

 void check_url_patterns(QString url);


};



#endif // QMT_WEB_ENGINE_VIEW__H
