

//          Copyright Nathaniel Christen 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef STYLES__H
#define STYLES__H


#include <QString>
#include <QPushButton>
#include <QColor>
#include <QFrame>
#include <QLabel>

#include "global-types.h"

template<typename WIDGET_Type>
inline void add_style_sheet(WIDGET_Type* w, QString ss)
{
 w->setStyleSheet(w->styleSheet() + ss);
}

inline QString back_forward_button_style_sheet_()
{
 return R"(
   QPushButton{font-size: 12pt;
   font-weight: bold;
   color: brown;})";
}

inline QString light_checkable_button_style_sheet_()
{
 return R"(
   QPushButton{font-size: %1pt;
   font-weight: %2;
   color: %3;})";
}

inline QString light_checkable_button_style_sheet_ul_()
{
 return R"(
   QPushButton{font-size: %1pt;
   font-weight: %2;
   text-decoration: underline;
   color: %3;})";
}

inline QString light_checkable_button_style_sheet_hover_()
{
 return R"(QPushButton{}
   QPushButton:hover{border: %2px %1 %3; })";
}


inline QString color_label_style_sheet_()
{
 return R"(
   QLabel{font-size: %1pt;
   font-weight: %2;
   color: %3;})";
}

inline QString checkable_button_orange()
{
 return "#E55B2C";
}

inline QColor checkable_button_orange_color()
{
 return QColor(checkable_button_orange());
}

inline QString checkable_button_dark_orange()
{
 return "#A51B09";
}

inline QColor checkable_button_dark_orange_color()
{
 return QColor(checkable_button_dark_orange());
}

inline QString light_checkable_button_style_sheet_orange_()
{
 return light_checkable_button_style_sheet_().arg(9).arg("bold").arg("#E55B2C");
}

inline QString light_checkable_button_style_sheet_orange_hover_()
{
 return light_checkable_button_style_sheet_hover_().arg("ridge").arg(2).arg(checkable_button_dark_orange());
}

inline QString light_checkable_button_style_sheet_thick_orange_()
{
 return light_checkable_button_style_sheet_().arg(10).arg("bold").arg("#E55B2C");
}

inline QString light_checkable_button_style_sheet_thick_orange_ul_()
{
 return light_checkable_button_style_sheet_ul_().arg(10).arg("normal").arg("#E55B2C");
}

inline QString light_checkable_button_style_sheet_orange_ul_()
{
 return light_checkable_button_style_sheet_ul_().arg(9).arg("bold").arg("#E55B2C");
}

inline QString dark_checkable_button_style_sheet_thick_orange_()
{
 return light_checkable_button_style_sheet_ul_().arg(12).arg("bold").arg("#A51B09");
}

inline QString light_checkable_button_style_sheet_thin_orange_()
{
 return light_checkable_button_style_sheet_().arg(8).arg("normal").arg("#E55B2C");
}

inline QString color_label_style_sheet_orange_()
{
 return color_label_style_sheet_().arg(8).arg("normal").arg("#B52B1A");
}

inline QString light_back_forward_button_style_sheet_()
{
 return R"(
   QPushButton{font-size: %1pt;
   font-weight: %2;
   color: %3;})";
}

inline QString light_back_forward_button_style_sheet_blue_()
{
 return light_back_forward_button_style_sheet_().arg(13).arg("bold").arg("#3366cf");
}

inline QString light_back_forward_button_style_sheet_red_()
{
 return light_back_forward_button_style_sheet_().arg(9).arg("bold").arg("#af3f73");
}

inline QString light_back_forward_button_style_sheet_red_darker_()
{
 return light_back_forward_button_style_sheet_().arg(11).arg("bold").arg("#9f4f43");
}

inline QString light_back_forward_button_style_sheet_red_darker_smaller_()
{
 return light_back_forward_button_style_sheet_().arg(8).arg("bold").arg("#9f4f43");
}

inline QString light_back_forward_button_style_sheet_red_darker_larger_(u1 font_size)
{
 return light_back_forward_button_style_sheet_().arg(font_size).arg("bold").arg("#9f4f43");
}

inline QString light_back_forward_button_style_sheet_red_darker_larger_non_bold_(u1 font_size)
{
 return light_back_forward_button_style_sheet_().arg(font_size).arg("normal").arg("#9f4f43");
}

inline QString light_back_forward_button_style_sheet_light_blue_larger_(u1 font_size)
{
 return light_back_forward_button_style_sheet_().arg(font_size).arg("normal").arg("#126fa3");
}


inline QString light_back_forward_button_style_sheet_green_()
{
 return light_back_forward_button_style_sheet_().arg(13).arg("normal").arg("#116f63");
}

template<typename WIDGET1_Type, typename WIDGET2_Type>
inline void share_tooltip(WIDGET1_Type* w1, WIDGET2_Type* w2)
{
 w2->setToolTip(w1->toolTip());
}

//template<typename WIDGET1_Type, typename WIDGET2_Type>
//inline void share_tooltip(WIDGET1_Type* w1, WIDGET2_Type* w2)
//{
// w2->setToolTip(w1->toolTip());
//}

//template<typename WIDGET1_Type, typename WIDGET2_Type>
//inline void share_tooltip(QPair<WIDGET1_Type*, WIDGET2_Type*>* ws)
//{
// share_tooltip(ws->first, ws->second);
//}

template<typename WIDGET_Type, typename LAYOUT_Type>
inline void add_vertical_separator_line(WIDGET_Type* w, LAYOUT_Type* layout)
{
 QFrame* line = new QFrame(w);
 line->setFrameShape(QFrame::VLine); // Horizontal line
 line->setFrameShadow(QFrame::Sunken);
 line->setLineWidth(1);
 layout->addWidget(line);
}

template<typename WIDGET_Type, typename LAYOUT_Type>
inline void add_horizontal_separator_line(WIDGET_Type* w, LAYOUT_Type* layout)
{
 QFrame* line = new QFrame(w);
 line->setFrameShape(QFrame::HLine); // Horizontal line
 line->setFrameShadow(QFrame::Sunken);
 line->setLineWidth(1);
 layout->addWidget(line);
}


//template<typename LAYOUT_Type>
//inline void add_vertical_separator_line(LAYOUT_Type* layout)
//{
// QFrame* line = new QFrame(nullptr);
// line->setFrameShape(QFrame::VLine); // Horizontal line
// line->setFrameShadow(QFrame::Sunken);
// line->setLineWidth(1);
// layout->addWidget(line);
//}

template<typename LAYOUT_Type>
inline void constrict_spacing(LAYOUT_Type* layout)
{
 layout->setMargin(0);
 layout->setContentsMargins(0,0,0,0);
 layout->setSpacing(0);
}

template<typename WIDGET_Type>
inline void set_multiline_tooltip(WIDGET_Type* w, QString top, QString bottom)
{
 w->setToolTip(QString(R"(
<b>%1</b><hr>
%2
)").arg(top).arg(bottom));
}


template<typename WIDGET_Type>
inline void make_unicode_text(WIDGET_Type* w, u4 code_point)
{
 u2 low = code_point & 0x0000FFFF;
 if(low == code_point)
 {
  // // only two bytes
  QString unicode = QString(QChar(low));
  w->setText(unicode);
 }
 else
 {
  code_point >>= 16;
  const u1 array[4]  {(u1)(code_point >> 8), (u1)(code_point & 0xFF), (u1)(low >> 8), (u1)(low & 0xFF)};
  QString unicode = QString::fromUtf8((const char*)array, 4);

//?  const char16_t array[2] {code_point, low};
//?  const char16_t array[2] {0xD83D, 0xDCF7};

//  QString unicode = QString::fromUtf16(array, 2);
  w->setText(unicode);



 }
}

template<typename WIDGET_Type>
inline void make_unicode_text(WIDGET_Type* w, u4 code_point, QString style_sheet)
{
 make_unicode_text(w, code_point);
 w->setStyleSheet(style_sheet);
}

template<typename WIDGET_Type>
inline void make_unicode_text(WIDGET_Type* w, u4 code_point,
  QString style_sheet, u1 width, u1 height, u1 repeat = 0)
{
 make_unicode_text(w, code_point);
 w->setStyleSheet(style_sheet);
 w->setMaximumWidth(width);
 w->setMaximumHeight(height);
 if(repeat)
 {
  QString txt = w->text().repeated(repeat + 1);
  w->setText(txt);
 }
}

template<typename WIDGET_Type>
inline void make_pause_button(WIDGET_Type* w)
{
//? make_unicode_text(w, 0x27F1, light_back_forward_button_style_sheet_red_darker_(), 20, 15);
// make_unicode_text(w, 0x2385, //0x22AA,
//   light_back_forward_button_style_sheet_red_darker_larger_non_bold_(15), 20, 15);

 make_unicode_text(w, 0x2980,  // 2385
   light_back_forward_button_style_sheet_red_darker_larger_(15), 20, 15);

}

template<typename WIDGET_Type>
inline void make_restart_button(WIDGET_Type* w)
{
 make_unicode_text(w, 0x21BA, light_back_forward_button_style_sheet_red_darker_(), 20, 15);
}

template<typename WIDGET_Type>
inline void make_enlarge_button(WIDGET_Type* w)
{
 make_unicode_text(w, 0x26F6, light_back_forward_button_style_sheet_red_darker_larger_(14), 24, 17);
}


template<typename WIDGET_Type>
inline void make_contract_button(WIDGET_Type* w)
{
 make_unicode_text(w, 0x2798,
  light_back_forward_button_style_sheet_red_darker_smaller_(), 20, 15, /*repeated*/ 2);
}

template<typename WIDGET_Type>
inline void make_resume_button(WIDGET_Type* w)
{
 make_unicode_text(w, 0x21F4,
   light_back_forward_button_style_sheet_red_darker_larger_non_bold_(15), 20, 15);
}

template<typename WIDGET_Type>
inline void make_play_button(WIDGET_Type* w)
{
 make_unicode_text(w, 0xF09FA0B6,
   light_back_forward_button_style_sheet_red_darker_larger_non_bold_(16), 20, 15);
}

template<typename WIDGET_Type>
inline void make_camera_button(WIDGET_Type* w)
{
 make_unicode_text(w, 0xF09F93B7, light_back_forward_button_style_sheet_light_blue_larger_(16),
   28, 16);

// make_unicode_text(w, 0xF09F93B7, light_back_forward_button_style_sheet_light_blue_larger_(16),
//   28, 16);

// make_unicode_text(w, 0xF09F93B7, 2385 light_back_forward_button_style_sheet_red_larger_(),
//   24, 17);
}

//template<typename WIDGET_Type>
//inline void make_pause_button(WIDGET_Type* w)
//{
// make_unicode_text(w, 0x21FB, light_back_forward_button_style_sheet_red_(), 20, 15);
//}

template<typename WIDGET_Type>
inline void make_up_button(WIDGET_Type* w)
{
 make_unicode_text(w, 0x219F, light_back_forward_button_style_sheet_red_(), 20, 15);
// QString unicode = QString(QChar(0x219F));
// w->setText(unicode);
// w->setStyleSheet(light_back_forward_button_style_sheet_red_());
// w->setMaximumWidth(20);
// w->setMaximumHeight(15);
}

template<typename WIDGET_Type>
inline void make_down_button(WIDGET_Type* w)
{
 make_unicode_text(w, 0x21A1);
// QString unicode = QString(QChar(0x21A1));
// w->setText(unicode);
 w->setStyleSheet(light_back_forward_button_style_sheet_red_());
 w->setMaximumWidth(20);
 w->setMaximumHeight(15);
}

template<typename WIDGET_Type>
inline void make_top_down_button(WIDGET_Type* w)
{
 make_unicode_text(w, 0x21A7);
// QString unicode = QString(QChar(0x21A7));
// w->setText(unicode);
 w->setStyleSheet(light_back_forward_button_style_sheet_red_());
 w->setMaximumWidth(20);
 w->setMaximumHeight(15);
}


template<typename WIDGET_Type>
inline void make_back_button(WIDGET_Type* w)
{
 //QString unicode = QString("%1").arg(QChar(5189));
 make_unicode_text(w, 0x27F8);
// QString unicode = QString(QChar(0x27F8));
// w->setText(unicode);
 w->setStyleSheet(back_forward_button_style_sheet_());
 w->setMaximumWidth(25);
 w->setMaximumHeight(15);
}

template<typename WIDGET_Type>
inline void make_light_back_button(WIDGET_Type* w)
{
 make_unicode_text(w, 0xF09FA0B8);
// QString unicode = QString::fromUtf8(QByteArray::fromHex("F09FA0B8"));
// w->setText(unicode);
 w->setStyleSheet(light_back_forward_button_style_sheet_blue_());
 w->setMaximumWidth(20);
 w->setMaximumHeight(15);
}

template<typename WIDGET_Type>
inline void make_light_special_back_button(WIDGET_Type* w)
{
 make_unicode_text(w, 0x21E0);
// QString unicode = QString(QChar(0x21E0));
// w->setText(unicode);
 w->setStyleSheet(light_back_forward_button_style_sheet_green_());
 w->setMaximumWidth(19);
 w->setMaximumHeight(15);
}

template<typename WIDGET_Type>
inline void make_light_double_back_button(WIDGET_Type* w)
{
 make_unicode_text(w, 0x219E);
// QString unicode = QString(QChar(0x219E));
// w->setText(unicode);
 w->setStyleSheet(light_back_forward_button_style_sheet_blue_());
 w->setMaximumWidth(20);
 w->setMaximumHeight(15);
}

template<typename WIDGET_Type>
inline void make_forward_button(WIDGET_Type* w)
{
// QString unicode = QString("%1").arg(QChar(5184));

 make_unicode_text(w, 0x27F9);
// QString unicode = QString(QChar(0x27F9));
// w->setText(unicode);
 w->setStyleSheet(back_forward_button_style_sheet_());
 w->setMaximumWidth(25);
 w->setMaximumHeight(15);
}

template<typename WIDGET_Type>
inline void make_light_forward_button(WIDGET_Type* w)
{
 make_unicode_text(w, 0xF09FA0BA);
// QString unicode = QString::fromUtf8(QByteArray::fromHex("F09FA0BA"));
// w->setText(unicode);
 w->setStyleSheet(light_back_forward_button_style_sheet_blue_());
 w->setMaximumWidth(20);
 w->setMaximumHeight(15);
}

template<typename WIDGET_Type>
inline void make_light_special_forward_button(WIDGET_Type* w)
{
 make_unicode_text(w, 0x21E2);
// QString unicode = QString(QChar(0x21E2));
// w->setText(unicode);
 w->setStyleSheet(light_back_forward_button_style_sheet_green_());
 w->setMaximumWidth(19);
 w->setMaximumHeight(15);
}

template<typename WIDGET_Type>
inline void make_light_double_forward_button(WIDGET_Type* w)
{
 make_unicode_text(w, 0x21A0);
// QString unicode = QString(QChar(0x21A0));
// w->setText(unicode);
 w->setStyleSheet(light_back_forward_button_style_sheet_blue_());
 w->setMaximumWidth(20);
 w->setMaximumHeight(15);
}

inline QString qmessagebox_button_style_sheet()
{
 return
 "QPushButton#Yes { width:70px; "
 "background-color: qlineargradient("
 "x1:0, y1:0, x2:0, y2:1,"
 "stop:0 #C5D8FA,"
 "stop:0.03 #F5E4FA,"
 "stop:0.04 #F5E6FA,"
 "stop:1 #F5E8FA"
 ");"
 "background-image: none;"
 "border-image: none;"
 "border-radius: 6px;"
 "border-left: 1px ridge #3AFFAB;"
 "border-right: 1px ridge #3AFFAB;"
 "border-top: 2px solid #618281;"
 "border-bottom: 2px solid #618281;"
 "}"

 "QPushButton  { width:70px; "
 "background-color: qlineargradient("
 "x1:0, y1:0, x2:0, y2:1,"
 "stop:0 #C5D8FA,"
 "stop:0.03 #F5E0FA,"
 "stop:0.04 #F5E8FA,"
 "stop:1 #F5E8BE"
 ");"
 "background-image: none;"
 "border-image: none;"
 "border-radius: 6px;"
 "border-left: 2px ridge #3AFFAB;"
 "border-right: 2px ridge #3AFFAB;"
 "border-top: 2px ridge #C5D8FA;"
 "border-bottom: 2px ridge #C5D8FA;"
 "}"

 "QPushButton#Ok { width:90px;"
 "background-color: qlineargradient("
 "x1:0, y1:0, x2:0, y2:1,"
 "stop:0 #C5D8FA,"
 "stop:0.01 #F182F1,"
 "stop:0.02 #EDEDED,"
 "stop:0.07 #EDEDED,"
 "stop:0.09 #F4EAF2,"
 "stop:1 #F1E1F1"
 ");"
 "background-image: none;"
 "border-image: none;"
 "border: 1px solid #364767;"
 "}"

 "QPushButton:pressed, QPushButton#Yes:pressed, QPushButton#Ok:pressed {"
 "background-color: qlineargradient("
 "x1:0, y1:0, x2:0, y2:1,"
 "stop:0 #445A82,"
 "stop:0.03 #6182BD,"
 "stop:0.04 #6182BD,"
 "stop:1 #C5D8FA"
 ");"
 "background-image: none;"
 "border-image: none;"
 "border: 1px solid #364767;"
 "}"

 "QPushButton:hover, QPushButton#Yes:hover, QPushButton#Ok:hover  {"
 "border:1px solid #EFE7F7;"
 "background-color: qlineargradient("
 "x1:0, y1:0, x2:0, y2:1,"
 "stop:0 #C5D8FA,"
 "stop:0.03 #E95289,"
 "stop:0.04 #E95289,"
 "stop:1 #A64166"
 ");"
 "}"
 ;
}


inline QString basic_button_style_sheet_()
{
 return
 "QPushButton:default { qproperty-icon: url(\"\"); "
 "background-color: qlineargradient("
 "x1:0, y1:0, x2:0, y2:1,"
 "stop:0 #C5D8FA,"
 "stop:0.03 #F5E4FA,"
 "stop:0.04 #F5E6FA,"
 "stop:1 #F5E8FA"
 ");"
 "background-image: none;"
 "border-image: none;"
 "border-radius: 6px;"
 "border-left: 1px ridge #3AFFAB;"
 "border-right: 1px ridge #3AFFAB;"
 "border-top: 2px solid #618281;"
 "border-bottom: 2px solid #618281;"
 "}"

 "QPushButton {"
 "background-color: qlineargradient("
 "x1:0, y1:0, x2:0, y2:1,"
 "stop:0 #C5D8FA,"
 "stop:0.03 #F5E0FA,"
 "stop:0.04 #F5E8FA,"
 "stop:1 #F5E8BE"
 ");"
 "background-image: none;"
 "border-image: none;"
 "border-radius: 6px;"
 "border-left: 2px ridge #3AFFAB;"
 "border-right: 2px ridge #3AFFAB;"
 "border-top: 2px ridge #C5D8FA;"
 "border-bottom: 2px ridge #C5D8FA;"
 "}"

 "QPushButton:disabled {"
 "background-color: qlineargradient("
 "x1:0, y1:0, x2:0, y2:1,"
 "stop:0 #C5D8FA,"
 "stop:0.01 #618281,"
 "stop:0.02 #EDEDED,"
 "stop:0.07 #EDEDED,"
 "stop:0.09 #445A82,"
 "stop:1 #616161"
 ");"
 "background-image: none;"
 "border-image: none;"
 "border: 1px solid #364767;"
 "}"

 "QPushButton:pressed {"
 "background-color: qlineargradient("
 "x1:0, y1:0, x2:0, y2:1,"
 "stop:0 #445A82,"
 "stop:0.03 #6182BD,"
 "stop:0.04 #6182BD,"
 "stop:1 #C5D8FA"
 ");"
 "background-image: none;"
 "border-image: none;"
 "border: 1px solid #364767;"
 "}"

 "QPushButton:hover {"
 "border:1px solid #EFE7F7;"
 "background-color: qlineargradient("
 "x1:0, y1:0, x2:0, y2:1,"
 "stop:0 #C5D8FA,"
 "stop:0.03 #E95289,"
 "stop:0.04 #E95289,"
 "stop:1 #A64166"
 ");"
 "}"
 ;
}

inline void fill_solid_color_button(QPushButton* b, QColor c,
  int width = 20, int height = 12)
{
 QPixmap pixmap(width, height);
 pixmap.fill(c);
 QIcon icon(pixmap);
 b->setIcon(icon);
}

inline void fill_solid_color_label(QLabel* lbl, QColor c,
  int width = 20, int height = 12)
{
 //lbl->setText(QString("<span style='border-radius: 15px;background-color: #%1>%1</span>").arg(QString::number(c.rgb(), 16)));


 lbl->setText(QString("%1").arg(QString::number(c.rgb(), 16)));

 lbl->setStyleSheet(QString("QLabel { background-color: #%1; color:white }").arg(QString::number(c.rgb(), 16)));
}

inline QString colorful_toggle_button_quiet_style_sheet_()
{
 return
   "QPushButton {"
   "background-color: qlineargradient("
   "x1:0, y1:0, x2:0, y2:1,"
   "stop:0 #C5D8FA,"
   "stop:0.03 #F5E0FA,"
   "stop:0.04 #F5E8FA,"
   "stop:1 #F5E8BE"
   ");"
   "background-image: none;"
   "border-image: none;"
   "border-radius: 6px;"
   "border-left: 2px ridge #3AFFAB;"
   "border-right: 2px ridge #3AFFAB;"
   "border-top: 2px ridge #C5D8FA;"
   "border-bottom: 2px ridge #C5D8FA;"
   "}"


 "QPushButton:disabled {"
 "background-color: qlineargradient("
 "x1:0, y1:0, x2:0, y2:1,"
 "stop:0 #C5D8FA,"
 "stop:0.01 #618281,"
 "stop:0.02 #EDEDED,"
 "stop:0.07 #EDEDED,"
 "stop:0.09 #445A82,"
 "stop:1 #616161"
 ");"
 "background-image: none;"
 "border-image: none;"
 "border: 1px solid #364767;"
 "}"

 "QPushButton:hover {"
 "background-color: qlineargradient("
 "x1:0, y1:0, x2:0, y2:1,"
 "stop:0 #445A82,"
 "stop:0.03 #6182BD,"
 "stop:0.04 #6182BD,"
 "stop:1 #C5D8FA"
 ");"
 "background-image: none;"
 "border-image: none;"
 "border: 1px solid #364767;"
 "}"

 "QPushButton:checked {"
 "border:1px solid #EFE7F7;"
 "background-color: qlineargradient("
 "x1:0, y1:0, x2:0, y2:1,"
 "stop:0 #C5D8FA,"
 "stop:0.03 #E95289,"
 "stop:0.04 #E95289,"
 "stop:1 #A64166"
 ");"
 "}"

 "QPushButton:checked:hover {"
 "border:1px solid #EFE7F7;"
 "background-color: qlineargradient("
 "x1:0, y1:0, x2:0, y2:1,"
 "stop:0 #C5D8FA,"
 "stop:0.5 #E95289,"
 "stop:1 #A64166"
 ");"
 "}"
 ;
}



//?QPushButton:hover,
//"QPushButton[checked=true] { background:#B13240; }"
//"QPushButton[checked=false] { background:white; }"

//"QPushButton[checked=false] {"
//"background-color: qlineargradient("
//"x1:0, y1:0, x2:0, y2:1,"
//"stop:0 #C5D8FA,"
//"stop:0.03 #F5E0FA,"
//"stop:0.04 #F5E8FA,"
//"stop:1 #F5E8BE"
//");"
//"background-image: none;"
//"border-image: none;"
//"border-radius: 6px;"
//"border-left: 2px ridge #3AFFAB;"
//"border-right: 2px ridge #3AFFAB;"
//"border-top: 2px ridge #C5D8FA;"
//"border-bottom: 2px ridge #C5D8FA;"
//"}"

// "QPushButton:default {"
//"background-color: qlineargradient("
//"x1:0, y1:0, x2:0, y2:1,"
//"stop:0 #C5D8FA,"
//"stop:0.03 #F5E4FA,"
//"stop:0.04 #F5E6FA,"
//"stop:1 #F5E8FA"
//");"
//"background-image: none;"
//"border-image: none;"
//"border-radius: 6px;"
//"border-left: 1px ridge #3AFFAB;"
//"border-right: 1px ridge #3AFFAB;"
//"border-top: 2px solid #618281;"
//"border-bottom: 2px solid #618281;"
//"}"




inline QString tab_style_sheet_()
{
 return "QTabBar::tab {"
        "background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
        "                            stop: 0 #E1E1E1, stop: 0.4 #DDDDDD,"
        "                            stop: 0.5 #D8D8D8, stop: 1.0 #D30000);"
        "border: 2px solid #C4C4C3;"
        "border-bottom-color: #C2C7CB; /* same as the pane color */"
        "border-top-left-radius: 4px;"
        "border-top-right-radius: 4px;"
        "min-width: 20ex;"
        "padding: 2px;"
        "color:rgb(145,50,70)"
        "}"

        "QTabBar::tab:selected, QTabBar::tab:hover {"
        "background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
        "                            stop: 0 #fafafa, stop: 0.4 #f4f4f4,"
        "                            stop: 0.5 #e7e7e7, stop: 1.0 #fafadd);"
        "border-color: #5BAB9B;"
        "border-bottom-color: #C2C7CB; /* same as pane color */"
        "color:rgb(85,10,10)"
        "}"

        "QTabBar::tab:hover { border-color: #ABABCB; }"

        "QTabBar::tab:selected {"
        "border-color: #1B9B9B;"
        "border-bottom-color: #C2C7CB; /* same as pane color */"
        "}"

        "QTabBar::tab:!selected {"
        "margin-top: 2px; /* make non-selected tabs look smaller */"
        "}"

        "QTabBar::tab::disabled {"
        "width: 0; height: 0; margin: 0; padding: 0; border: none;"
        "}"
   ;

//        "QTabWidget{border:solid white 3px; background:white}"
}

inline QString soft_group_box_style_sheet_()
{
 return R"(
        QGroupBox {
            border: 1px solid silver;
            border-radius: 6px;
            margin-top: 13px;
        }
        QGroupBox::title {
        subcontrol-origin:  margin;
            subcontrol-position: top left;
            padding: -1 12px 0 %1px;        }

        )";
}

inline QString tight_soft_group_box_style_sheet_()
{
 return R"(
        QGroupBox {
            border: 1px solid silver;
            border-radius: 3px;
            margin-top: 13px; padding:-1px -1px -1px -1px;
        }
        QGroupBox::title {
        subcontrol-origin:  margin;
            subcontrol-position: top left;
            padding: -1px 2px 0 %1px;        }

        )";
}

inline QString tight_left_soft_group_box_style_sheet_()
{
 return R"(
        QGroupBox {
            border: 1px solid silver;
            border-radius: 3px;
            margin-bottom: 3px; padding:-1px -1px 7px -1px;
        }
        QGroupBox::title { font-size:9pt;
        subcontrol-origin:  margin;
            subcontrol-position: bottom left;
            padding: 0px 2px -6px %1px;        }

        )";
}


inline QString mini_tab_style_sheet_()
{
 return "QTabBar::tab {"
        "background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
        "                            stop: 0 #E1E1E1, stop: 0.4 #DDDDDD,"
        "  stop: 0.5 #D8D8D8, stop: 0.8 #A8D8A9,  stop: 1.0 #A030D0);"
        "border: 2px solid #C4C4C3;"
        "border-bottom-color: #C2C7CB; /* same as the pane color */"
        "border-top-left-radius: 1px;"
        "border-top-right-radius: 1px;"
        "min-width: 10ex;"
        "padding: 1px;"
        "color:rgb(45,50,17)"
        "}"

        "QTabBar::tab:selected, QTabBar::tab:hover {"
        "background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
        "                            stop: 0 #fafafa, stop: 0.4 #f4f4f4,"
        "                            stop: 0.8 #e7e7e7, stop: 1.0 #A030D0);"
        "border-color: rgb(15,10,90);"
        "border-bottom-color: #C2C7CB; /* same as pane color */"
        "color: rgb(15,10,90);"
        "}"

        "QTabBar::tab:hover { border-color: #ABABCB; }"

        "QTabBar::tab:selected {"
        "border-color: #1B9B9B;"
        "border-bottom-color: #C2C7CB; /* same as pane color */"
        "}"

        "QTabBar::tab:!selected {"
        "margin-top: 2px; /* make non-selected tabs look smaller */"
        "}"

        "QTabBar::tab::disabled {"
        "width: 0; height: 0; margin: 0; padding: 0; border: none;"
        "}"
   ;

//        "QTabWidget{border:solid white 3px; background:white}"
}

inline QString mini_tab_style_sheet_inverted_()
{
 return "QTabBar::tab {"
        "background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
        "                            stop: 1 #E1E1E1, stop: 0.6 #DDDDDD,"
        "  stop: 0.5 #D8D8D8, stop: 0.2 #A8D8A9,  stop: 0 #A030D0);"
        "border: 2px solid #C4C4C3;"
        "border-top-color: #C2C7CB; /* same as the pane color */"
        "border-bottom-left-radius: 1px;"
        "border-bottom-right-radius: 1px;"
        "min-width: 10ex;"
        "padding: 1px;"
        "color:rgb(45,50,17)"
        "}"

        "QTabBar::tab:selected, QTabBar::tab:hover {"
        "background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
        "                            stop: 1 #fafafa, stop: 0.6 #f4f4f4,"
        "                            stop: 0.2 #e7e7e7, stop: 0 #A030D0);"
        "border-color: rgb(15,10,90);"
        "border-top-color: #C2C7CB; /* same as pane color */"
        "color: rgb(15,10,90);"
        "}"

        "QTabBar::tab:hover { border-color: #ABABCB; }"

        "QTabBar::tab:selected {"
        "border-color: #1B9B9B;"
        "border-top-color: #C2C7CB; /* same as pane color */"
        "}"

        "QTabBar::tab:!selected {"
        "margin-bottom: 2px; /* make non-selected tabs look smaller */"
        "}"

        "QTabBar::tab::disabled {"
        "width: 0; height: 0; margin: 0; padding: 0; border: none;"
        "}"
   ;

//        "QTabWidget{border:solid white 3px; background:white}"
}



inline QString colorful_button_style_sheet_()
{
 return
   "QPushButton:hover {background:rgb(240,190,150);"
   " border-left: 4px groove rgb(240,190,150); "
   " border-right: 4px ridge rgb(240,190,150); "
   "}\n"
   "QPushButton{color:black;  padding:1px;  border: 2px solid rgb(240,190,150); "
   "  border-bottom: 1px solid #CEF51D; "
   " border-radius: 6px; "
   " background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, "
   "  stop: 0 white, stop: 0.1 #C0C0C0, stop: 0.6 #CCC6BC,"
   "  stop: 0.8 #ECCFA0, stop: 0.9 darkred,  stop: 1 brown"
   "); min-width: 80px; }";
}

inline QString soft_small_colorful_button_style_sheet_()
{
 return
   "QPushButton:hover {background:rgb(240,190,150);"
   " border-left: 4px groove rgb(240,190,150); "
   " border-right: 4px ridge rgb(240,190,150); "
   "}\n"
   "QPushButton{color:black;  padding:1px;  border: 1px solid rgb(180,60,15); "
   " font-size:%1pt; "
   "  border-bottom: 1px solid #0E15CD; "
   " border-radius: 3px; "
   " background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, "
   "  stop: 0 red,  stop: 0.08 white,  stop: 0.2 #E0E0C0, stop: 0.6 #EEE6CC"
   "  stop: 0.8 #FCEFE0, stop: 0.95 white,  stop: 1 brown"
   "); }";
}

inline QString soft_colorful_button_style_sheet_()
{
 return soft_small_colorful_button_style_sheet_().arg(10);
}


//"QPushButton:hover {"
//"background-color: qlineargradient("
//"x1:0, y1:0, x2:0, y2:1,"
//"stop:0 #C5D8FA,"
//"stop:0.03 #F5E0FA,"
//"stop:0.04 #F5E8FA,"
//"stop:1 #F5E8BE"
//");"
//"background-image: none;"
//"border-image: none;"
//"border-radius: 6px;"
//"border-left: 2px ridge #3AFFAB;"
//"border-right: 2px ridge #3AFFAB;"
//"border-top: 2px ridge #C5D8FA;"
//"border-bottom: 2px ridge #C5D8FA;"
//"}"

//"QPushButton:disabled {"
//"background-color: qlineargradient("
//"x1:0, y1:0, x2:0, y2:1,"
//"stop:0 #C5D8FA,"
//"stop:0.01 #618281,"
//"stop:0.02 #EDEDED,"
//"stop:0.07 #EDEDED,"
//"stop:0.09 #445A82,"
//"stop:1 #616161"
//");"
//"background-image: none;"
//"border-image: none;"
//"border: 1px solid #364767;"
//"}"



inline QString colorful_toggle_button_mixed_style_sheet_()
{
 return

   "QPushButton{color:black;  padding:1px;  border: 2px solid rgb(240,190,150); "
   "  border-bottom: 1px solid #CEF51D; "
   " border-radius: 6px; "
   " background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, "
   "  stop: 0 white, stop: 0.1 #C0C0C0, stop: 0.6 #CCC6BC "
   "  stop: 0.8 #ECCFA0, stop: 0.9 darkred,  stop: 1 brown "
   ");} "


   "QPushButton[ckb-state=\"1\"]{ color:black; padding:1px;  border: 1px solid rgb(150,240,190); "
   "  border-bottom: 1px solid #CEF51D; "
   "  border-top: 2px inset #CEF51D; "
   " border-radius: 2px; "
   " background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, "
   "  stop: 0 white, stop: 0.1 #C0C0C0, stop: 0.6 #C6CCBC "
   "  stop: 0.8 #A0ECCF, stop: 0.9 darkseagreen,  stop: 1 blue"
   "); }"

   "QPushButton:checked{"
   "border:1px solid #EFE7F7;"
   "background-color: qlineargradient("
   "x1:0, y1:0, x2:0, y2:1,"
   "stop:0 #C5D8FA,"
   "stop:0.5 #E95289,"
   "stop:1 #A64166"
   ");"
   "}"


   "QPushButton:hover {"
   "border:1px solid #EFE7F7;"
   "background-color: qlineargradient("
   "x1:0, y1:0, x2:0, y2:1,"
   "stop:0 #C5D8FA,"
   "stop:0.03 #E95289,"
   "stop:0.04 #E95289,"
   "stop:1 #A64166"
   ");"
   "}"



   "QPushButton:hover:pressed {background:rgb(150,240,190); "
   " border-left: 4px groove rgb(150,240,190); "
   " border-right: 4px ridge rgb(150,240,190); "
   "}\n"

 "QPushButton:checked:hover {"
 "border:1px solid #EFE7F7;"
 "background-color: qlineargradient("
 "x1:0, y1:0, x2:0, y2:1,"
 "stop:0 #C5D8FA,"
 "stop:0.03 #E95289,"
 "stop:0.04 #E95289,"
 "stop:1 #A64166"
 ");"
 "}"

   "QPushButton[ckb-state=\"2\"] {"
   " border:none; "
      "background-color: qlineargradient("
      "x1:0, y1:0, x2:0, y2:1,"
      "stop:0 #C0C0C0,"
      "stop:0.03 #A0ECCF,"
      "stop:0.04 #A0ECCF,"
      "stop:1 #C6CCBC"
      ");"
   " border-left: 4px groove #C5D8FA; "
   " border-right: 4px ridge #C5D8FA; "
   "}\n"

   "QPushButton[ckb-state=\"3\"] {"
   " border:none; "
      "background-color: qlineargradient("
      "x1:0, y1:0, x2:0, y2:1,"
      "stop:0 #A64166,"
      "stop:0.03 #E95289,"
      "stop:0.04 #E95289,"
      "stop:1 #A64166"
      ");"
   " border-left: 4px groove #F6F1F6; "
   " border-right: 4px ridge #F6F1F6; "
   "}\n"




//   " border:none;"
//   " border-left: 4px groove #A64166; "
//   " border-right: 4px ridge #A64166; "
//   "background-color: qlineargradient("
//   "x1:0, y1:0, x2:0, y2:1,"
//   "stop:0 #C5D8FA,"
//   "stop:0.03 #E95289,"
//   "stop:0.04 #E95289,"
//   "stop:1 #A64166"
//   ");"
//   "}"


   "QPushButton:checked:hover:pressed{"
   "background-color: qlineargradient("
   "x1:0, y1:0, x2:0, y2:1,"
   "stop:0 #C5D8FA,"
   "stop:0.03 #F5E0FA,"
   "stop:0.04 #F5E8FA,"
   "stop:1 #F5E8BE"
   ");"
   "background-image: none;"
   "border-image: none;"
   "border-radius: 6px;"
   "border-left: 2px ridge #3AFFAB;"
   "border-right: 2px ridge #3AFFAB;"
   "border-top: 2px ridge #C5D8FA;"
   "border-bottom: 2px ridge #C5D8FA;"
   "}"


 ;
}




inline QString colorful_button_style_sheet_down_()
{
 return
   "QPushButton {background:rgb(190,190,230);padding-left:20;padding-right:20;padding-top:0;padding-bottom:0;"
   " border-left: 4px groove rgb(240,190,150); "
   " border-right: 4px ridge rgb(240,190,150); "
   "}\n";
}

inline QString group_box_style_sheet_()
{
 return 
  "QGroupBox"
  "{ border: 2px ridge %3; "
  "  border-radius: 7px; "
  "  background-color: %1; "
  "  font-size: 11px; "
  "  font-weight: bold;"
  "  margin-top: 15px;"
  "} \n"

  "QGroupBox::title"
  "{ subcontrol-origin: margin;"
  "  subcontrol-position: top left;"
  "  background-color: %2;"
  "  padding: 2 15px 2 15px ;"
  "} \n";

}

inline QString colorful_small_button_style_sheet_()
{
 return
   "QPushButton {background:rgb(190,190,230);min-width: 11px;"
   " font-size: %1pt; "
   " padding-left:2;padding-right:2;padding-top:0;padding-bottom:0;"
   " border-left: 4px groove rgb(240,190,150); "
   " border-right: 4px ridge rgb(240,190,150); "
   "}\n"

   "QPushButton:hover {background:rgb(0,190,230);min-width:11px;"
   " border-radius: 4px;padding-left:2;padding-right:2;padding-top:0;padding-bottom:0;"
   " border-left: 4px groove rgb(240,190,0); "
   " border-right: 4px ridge rgb(240,190,0); "
   "}\n"

   "QPushButton:disabled {background:rgb(200,200,204);min-width: 11px;"
   " color:rgb(160,190,230); "
   " padding-left:2;padding-right:2;padding-top:0;padding-bottom:0;"
   " border-left: 4px groove rgb(240,190,150); "
   " border-right: 4px ridge rgb(240,190,150); "
   "}\n"

   "QPushButton:pressed {background:rgb(190,0,230);min-width:11px;"
   " border-radius: 4px;padding-left:2;padding-right:2;padding-top:0;padding-bottom:0;"
   " border-left: 4px groove rgb(240,90,240); "
   " border-right: 4px ridge rgb(240,90,240); "
   "}\n"

   ;
}

inline QString light_small_button_style_sheet_()
{
 return
   "QPushButton {"
   " background:rgb(160,190,230);min-width: 11px;"
   " font-size: %1pt; "
   " padding-left:2;padding-right:2;padding-top:0;padding-bottom:0;"
   " border-left: 4px groove rgb(240,190,150); "
   " border-right: 4px ridge rgb(240,190,150); "
   "}\n"

   "QPushButton:hover {background:rgb(190,0,230);min-width:11px;"
   " border-radius: 4px;padding-left:2;padding-right:2;padding-top:0;padding-bottom:0;"
   " border-left: 4px groove rgb(240,90,240); "
   " border-right: 4px ridge rgb(240,90,240); "
   "}\n"
   ;
}

inline QString light_small_thin_button_style_sheet_()
{
 return
   "QPushButton {"
   " background:rgb(204,210,230);min-width: 11px;"
   " font-size: %1pt; "
   " padding-left:2;padding-right:2;padding-top:0;padding-bottom:0;"
   " border-top:1px solid white; "
   " border-bottom:none; "
   " border-left: 2px groove rgb(240,190,150); "
   " border-right: 2px ridge rgb(240,190,150); "
   "}\n"

   "QPushButton:hover {background:rgb(190,0,230);min-width:11px;"
   " border-radius: 4px;padding-left:2;padding-right:2;padding-top:0;padding-bottom:0;"
   " border-left: 2px groove rgb(240,90,240); "
   " border-right: 2px ridge rgb(240,90,240); "
   "}\n"
   ;
}

inline QString light_small_thin_white_button_style_sheet_()
{
 return
   "QPushButton {"
   " color:blue; "
   " background:rgb(214,230,250);min-width: 11px;"
   " font-size: %1pt; "
   " padding-left:2;padding-right:2;padding-top:0;padding-bottom:0;"
   " border-top:1px solid white; "
   " border-bottom:none; "
   " border-left: 1px groove rgb(240,190,10); "
   " border-right: 1px ridge rgb(240,190,10); "
   "}\n"

   "QPushButton:hover {background:rgb(190,0,230);min-width:11px;"
   " border-radius: 4px;padding-left:2;padding-right:2;padding-top:0;padding-bottom:0;"
   " border-left: 2px groove rgb(240,90,240); "
   " border-right: 2px ridge rgb(240,90,240); "
   "}\n"

   "QPushButton[suppressed=true]:hover {background:rgb(140,135,140);min-width:11px;"
   " border-radius: 14px;padding-left:2;padding-right:2;padding-top:0;padding-bottom:0;"
   " border-left: 2px groove rgb(190,233,230); "
   " border-right: 2px ridge rgb(190,233,230); "
   "}\n"

   "QPushButton[suppressed=true] {background:rgb(227,222,227);min-width:11px;"
   " border-radius: 14px;padding-left:2;padding-right:2;padding-top:0;padding-bottom:0;"
   " border-left: 2px groove rgb(190,233,230); "
   " border-right: 2px ridge rgb(190,233,230); "
   "}\n"

   ;
}


inline QString colorful_small_button_style_sheet_alt_()
{
 return light_small_button_style_sheet_().arg(10);
}


inline QString make_basic_style_sheet_()
{
 QString result = "QMainWindow{background:coral}"
                  "QWidget{background:none;color:black}"
                  "QMenu::item{color:black}"
                  "QMenu::item:selected{ "
                  " background-color: rgb(66, 206, 244); "
                  " } "
   ;

 result += basic_button_style_sheet_();
 result += tab_style_sheet_();

 return result;

}

inline QString basic_style_sheet_()
{
 static QString result = make_basic_style_sheet_();
 return result;
}

inline QString button_close_style_sheet_()
{
 return
   "QPushButton:hover {background:rgb(150,240,190);"
   " border-left: 4px groove rgb(150,240,190); "
   " border-right: 4px ridge rgb(150,240,190); "
   "}\n"

     "QPushButton {background:rgb(160,190,230);padding-left:20;padding-right:20;padding-top:0;padding-bottom:0;"
     " border-left: 4px groove rgb(240,190,150); "
     " border-right: 4px ridge rgb(240,190,150); "
     "}\n"


   "QPushButton:pressed{ color:black; padding:1px;  border: 1px solid rgb(150,240,190);"
   "  border-bottom: 1px solid #CEF51D; "
   " border-radius: 0px; "
   " background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, "
   "  stop: 0 white, stop: 0.1 #C0C0C0, stop: 0.6 #C6CCBC "
   "  stop: 0.8 #A0ECCF, stop: 0.9 darkseagreen,  stop: 1 blue"
   "); min-width: 80px; }";
}

inline  QString colorful_toggle_button_style_sheet_()
{
 return

 // "QPushButton{max-width: 25px;}"


   "QPushButton:hover {background:rgb(150,240,190); "
   " border-left: 4px groove rgb(150,240,190); "
   " border-right: 4px ridge rgb(150,240,190); "
   "}\n"
   "QPushButton:checked {color:black; background:rgb(200,10,100); "
   " border-left: 4px groove rgb(200,10,100); "
   " border-right: 4px ridge rgb(200,10,100); "
   "}\n"

   "QPushButton:checked:hover {background:rgb(250,240,190); "
   " border-left: 4px groove rgb(50,240,10); "
   " border-right: 4px ridge rgb(50,240,10); "
   "}\n"

   "QPushButton{ color:black; padding:1px;  border: 1px solid rgb(150,240,190); "
   "  border-bottom: 1px solid #CEF51D; "
   " border-radius: 0px; "
   " background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, "
   "  stop: 0 white, stop: 0.1 #C0C0C0, stop: 0.6 #C6CCBC "
   "  stop: 0.8 #A0ECCF, stop: 0.9 darkseagreen,  stop: 1 blue"
   "); }";
}


inline  QString tight_button_style_sheet_()
{
 return


" QPushButton:hover {background:rgb(150,240,190);"
"  border-left: 4px groove rgb(150,240,190); "
"  border-right: 4px ridge rgb(150,240,190); "
" }\n "

" QPushButton { background:rgb(220,220,230); "
"  border: 2px groove rgb(0,90,50); "
"  font-family:\"Comic Sans MS\", cursive, sans-serif; "
"  border-bottom: 2px groove rgb(240,190,150); "
"  border-top: 2px groove rgb(240,90,150); "
"  border-radius: 10px; font-weight:600; color:rgb(0, 90, 105); "
"  padding-left:16px;padding-right:16px;padding-top:2px;padding-bottom:2px; "

//   " border-left: 4px groove rgb(0,190,150);   "
//   " border-right: 4px ridge rgb(240,190,150); "

" }\n"

" QPushButton[enabled=false] { color:grey; } "



" QPushButton:pressed{ color:black; padding:1px; "
"  border: 1px solid rgb(150,240,190); "
"  border-bottom: 1px solid #CEF51D; "
"  border-radius: 0px; "
"  background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, "
"   stop: 0 white, stop: 0.1 #C0C0C0, stop: 0.6 #C6CCBC "
"   stop: 0.8 #A0ECCF, stop: 0.9 darkseagreen,  stop: 1 blue"
"  ); min-width: 80px; } ";

}


inline  QString toggle_button_style_sheet_()
{
 return


" QPushButton:hover {background:rgb(150,240,190);"
"  border-left: 4px groove rgb(150,240,190); "
"  border-right: 4px ridge rgb(150,240,190); "
" }\n "

 " QPushButton{ background:rgb(220,220,230); "
 "  border: 2px groove rgb(0,90,50); "
 "  font-family:\"Comic Sans MS\", cursive, sans-serif; "
 "  border-bottom: 2px groove rgb(240,190,150); "
 "  border-top: 2px groove rgb(240,90,150); "
 "  border-radius: 3px; font-weight:600; color:rgb(0, 90, 105); "
 "  padding-left:16px;padding-right:16px;padding-top:2px;padding-bottom:2px; "
 " }\n"


 " QPushButton[checked=false] {background:rgb(250,250,190);"
 "  border-left: 4px groove rgb(150,240,190); "
 "  border-right: 4px ridge rgb(150,240,190); "
 " }\n "

 " QPushButton[checked=true] { background:#B13240; " //background:rgb(10,10,190);"
 "  color:rgb(210,220,190); "
 "  border-left: 4px groove rgb(150,240,190); "
 "  border-right: 4px ridge rgb(150,240,190); "
 " }\n "


//   " border-left: 4px groove rgb(0,190,150);   "
//   " border-right: 4px ridge rgb(240,190,150); "
//" }\n"

" QPushButton[enabled=false] { color:grey; } "



" QPushButton:pressed{ color:black; padding:1px; "
"  border: 1px solid rgb(150,240,190); "
"  border-bottom: 1px solid #CEF51D; "
"  border-radius: 0px; "
"  background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, "
"   stop: 0 white, stop: 0.1 #C0C0C0, stop: 0.6 #C6CCBC "
"   stop: 0.8 #A0ECCF, stop: 0.9 darkseagreen,  stop: 1 blue"
"  ); min-width: 80px; } ";

}



#endif
