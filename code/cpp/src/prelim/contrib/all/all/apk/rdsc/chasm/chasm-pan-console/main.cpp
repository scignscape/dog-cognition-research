
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include <QDebug>

#include <QDirIterator>

#include "chasm-lib/test-class.h"

#include "chasm-lib/unified-runtime-object.h"

#include "chasm-lib/metatype-object.h"

#include "textio.h"
USING_KANS(TextIO)

#include "chasm-lib/chasm/chasm-runtime.h"
#include "chasm-lib/chasm/chasm-call-package.h"










#include <QWebEngineView>
#include <QMainWindow>
#include <QApplication>
#include <QTabWidget>
#include <QWebChannel>
#include <QWebEnginePage>
#include <QContextMenuEvent>
#include <QMenu>
#include <QWebEngineContextMenuData>

#include "rpdf/webgl-view-dialog/rpdf-web-engine-page.h"
#include "rpdf/webgl-view-dialog/rpdf-web-engine-view.h"

#include "rpdf/webgl-view-dialog/webgl-view-dialog.h"

#include "rpdf/webgl-view-dialog/context-menu-provider.h"
#include "rpdf/webgl-view-dialog/pattern-matcher-runtime.h"

#include "rpdf/webgl-view-dialog/signal-generator.h"


int main(int argc, char *argv[])
{
 QApplication a(argc, argv);

 WebGL_View_Dialog* dlg = new WebGL_View_Dialog(nullptr);

 dlg->setWindowTitle("Matterport/Google Console");

 Pattern_Matcher_Runtime* pm_runtime = dlg->pm_runtime();

 QVector<URL_Or_Event_Pattern*>* url_patterns;

 Signal_Generator sg;

 QApplication::connect(&sg, &Signal_Generator::new_dialog_requested,
   [](const QPoint& pos, QUrl url)
 {
  WebGL_View_Dialog* dlg1 = new WebGL_View_Dialog(nullptr);

  dlg1->move(pos);

  dlg1->show();

 });

 Context_Menu_Provider cmp(pm_runtime, &sg);
 pm_runtime->set_context_menu_provider(&cmp);
 url_patterns = &pm_runtime->url_patterns();
 dlg->set_context_menu_provider(&cmp);

 QApplication::connect(dlg, &WebGL_View_Dialog::url_patterns_changed,
   [dlg, &url_patterns]()
 {
  //? *url_patterns = dlg->url_patterns();
 });

 QApplication::connect(dlg, &WebGL_View_Dialog::url_pattern_match,
   [dlg, &url_patterns](QString procedure_name, QString arguments)
 {
  qDebug() << "Proc: " << procedure_name;
  qDebug() << "arguments: " << arguments;
 });

 dlg->show();

 return a.exec();
}

