
#ifndef RPDF_WEB_ENGINE_VIEW__H
#define RPDF_WEB_ENGINE_VIEW__H

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

class RPDF_Web_Engine_View : public QWebEngineView
{
 Context_Menu_Provider* context_menu_provider_;
 Pattern_Matcher_Runtime* pm_runtime_;

 QDialog* parent_dialog_;

public:

 RPDF_Web_Engine_View(QDialog* parent_dialog);

 ACCESSORS(Context_Menu_Provider* ,context_menu_provider)
 ACCESSORS(Pattern_Matcher_Runtime* ,pm_runtime)

 RPDF_Web_Engine_View* sec;

 void contextMenuEvent(QContextMenuEvent *event) override;
 //?    MyWebView* createWindow(QWebEnginePage::WebWindowType type) override;
 void check_sec();

 void check_url_patterns(QString url);


};


#endif
