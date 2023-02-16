
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef ZQ_WEB_VIEW_DIALOG__H
#define ZQ_WEB_VIEW_DIALOG__H

#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QDialog>

#include <QTableWidget>
#include <QFrame>

#include <QTabWidget>

#include "zq-web-engine-view.h"
#include "zq-web-engine-page.h"
#include "zq-web-page.h"

#include "global-types.h"

#include "accessors.h"

//?#include "url-or-event-pattern.h"

#include <QScrollArea>

#include <QWebEngineUrlRequestInterceptor>

class Context_Menu_Provider;


class WebUrlRequestInterceptor : public QWebEngineUrlRequestInterceptor
{
    Q_OBJECT

public:
    WebUrlRequestInterceptor(QObject *p = Q_NULLPTR);
    void interceptRequest(QWebEngineUrlRequestInfo &info);
};


class ZQ_Web_View_Dialog : public QDialog
{
 Q_OBJECT

// Context_Menu_Provider* context_menu_provider_;
// Pattern_Matcher_Runtime* pm_runtime_;

 //Fore_Geometric1D_Panel fore_panel_;
 QDialogButtonBox* button_box_;
 QPushButton* button_ok_;
 QPushButton* button_cancel_;
 QVBoxLayout* main_layout_;

 QScrollArea* wev_scroll_area_;

 QFrame* wev_scroll_area_frame_;

 ZQ_Web_Engine_View* wev_;
 //wev->setGeometry(0,0,700,600);

 QWebEngineView* iwev_;

//?
 ZQ_Web_Engine_Page* wep_;
 ZQ_Web_Page* zqwp_;

 QTabWidget* qtw_;

 QFrame* url_patterns_frame_;
 QTableWidget* url_patterns_table_;
 QVBoxLayout* url_patterns_layout_;

// QVector<URL_Or_Event_Pattern> url_patterns_;

// void add_fixed_url_pattern(QString context, QString sec, QString pattern,
//   QString procedure, QString arguments);

//? QMap<u2, URL_Or_Event_Pattern*> patterns_by_row_;
 QRect first_video_capture_position_;

 void process_new_url_geo_fragment(QString fragment);

 r8 current_zoom_;
 r8 current_latitude_;
 r8 current_longitude_;

 std::function<void(r8, r8, r8)> zoom_or_coordinates_changed_callback_;

public:


 ZQ_Web_View_Dialog(QWidget* parent);
 ~ZQ_Web_View_Dialog();

// ACCESSORS__RGET(QVector<URL_Or_Event_Pattern> ,url_patterns)

//? ACCESSORS__SDECLARE(Context_Menu_Provider* ,context_menu_provider)

//? ACCESSORS__GET(Pattern_Matcher_Runtime* ,pm_runtime)

 ACCESSORS__RGET(QRect ,first_video_capture_position)

 ACCESSORS(ZQ_Web_Engine_View* ,wev)

 ACCESSORS(r8 ,current_zoom)
 ACCESSORS(r8 ,current_latitude)
 ACCESSORS(r8 ,current_longitude)

 ACCESSORS(MACRO_PASTE(std::function<void(r8, r8, r8)>) ,zoom_or_coordinates_changed_callback)

 void add_url_pattern(QUrl url);


// void handle_edit_url_patterns_row(int rc);
// void handle_save_url_patterns_row(int rc);
// void handle_cancel_remove_url_patterns_row(int rc);
// void handle_add_url_patterns_row();
// void check_url_patterns(QString url);

 void mouseReleaseEvent(QMouseEvent* mouseEvent) Q_DECL_OVERRIDE;
 void mousePressEvent(QMouseEvent* mouseEvent) Q_DECL_OVERRIDE;

 void resizeEvent(QResizeEvent* resize_event) Q_DECL_OVERRIDE;
 void moveEvent(QMoveEvent* move_event) Q_DECL_OVERRIDE;


 void reset_tab_selection();

 QRect get_web_view_geometry();

Q_SIGNALS:

// void url_patterns_changed();
 void web_view_geometry_updated(QRect);

// void url_pattern_match(QString procedure_name, QString arguments);

 void snapshot_saved(QString file_path);
 void youtube_download_requested(QString url);

 void zoom_or_coordinates_changed(r8, r8, r8);


};

#endif
