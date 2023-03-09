
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "page-and-search-frame.h"

#include "styles.h"

#include <QDebug>

#include <QStandardItemModel>
#include <QStandardItem>

#include "stash-signals.h"
#include "stash-signals-alt-base.h"
#include "self-connect.h"

#include "new-child.h"


Page_and_Search_Frame::Page_and_Search_Frame(QWidget* parent)
  :  QFrame(parent)
{
 main_layout_ = new QVBoxLayout;

 page_select_ = new QComboBox(this);
 page_select_->setMinimumWidth(50);
 //page_select_->setMaximumWidth(80);
 page_select_->setMaxVisibleItems(3);
 page_select_->setStyleSheet("combobox-popup: 0;");

// connect(page_select_, QOverload<s4>::of(&QComboBox::currentIndexChanged), [this](s4 index)

 page_select_
   >> lConnect(s4 overload_of QComboBox::currentIndexChanged)
   to_lambda[this](s4 index)
 {
  // //  we need to filter out spurious calls
   //    not caused by actual user actions ...
  if(index == -1)
   return;

  if(info_.total_pages() == 0)
    return;

  Q_EMIT page_select_requested((u4)index + 1);
 };


 page_select_->addItem("N/A");
 page_select_label_  = new QLabel("Page", this);

// page_max_label_text_ = QString("%1%%%1").arg(QChar(0x279C));

 page_max_label_text_ = QString("%1").prepend(QChar(0x279C));
 page_max_label_ = new QLabel(page_max_label_text_.arg(0));
 page_max_label_->setMinimumWidth(20);

 page_max_label_->setStyleSheet(color_label_style_sheet_orange_());
 page_max_label_->setToolTip("Total pages/images in the current document/image series");

 page_select_and_navigate_layout_ = new QHBoxLayout;
 page_select_and_navigate_layout_left_ = new QVBoxLayout;
 page_select_and_navigate_layout_right_ = new QVBoxLayout;

 page_select_layout_ = new QHBoxLayout;
 page_select_layout_->addWidget(page_select_label_);
 page_select_layout_->addSpacing(3);
 page_select_layout_->addWidget(page_select_);
 page_select_layout_->addWidget(page_max_label_);
 page_select_layout_->addStretch();
 page_select_and_navigate_layout_left_->addLayout(page_select_layout_);

 main_layout_->setMargin(0);
 main_layout_->setContentsMargins(QMargins(10,4,5,4));
 main_layout_->setSpacing(0);

// main_layout_->addLayout(page_select_layout_);

// main_layout_->addSpacing(4);

 page_navigate_layout_ = new QHBoxLayout;

 page_back_button_ = new QPushButton(this);
 page_back_button_->setToolTip("Page Back");

 page_forward_button_ = new QPushButton(this);
 page_forward_button_->setToolTip("Page Forward");

 page_first_button_ = new QPushButton(this);
 page_first_button_->setToolTip("First Page");

 page_last_button_ = new QPushButton(this);
 page_last_button_->setToolTip("Last Page");

 sigma(page_first_button_)->make_light_double_back_button();
 sigma(page_back_button_)->make_light_back_button();
 sigma(page_forward_button_)->make_light_forward_button();
 sigma(page_last_button_)->make_light_double_forward_button();

 page_navigate_layout_->addWidget(page_first_button_);
 page_navigate_layout_->addSpacing(2);
 page_navigate_layout_->addWidget(page_back_button_);
 page_navigate_layout_->addSpacing(1);
 page_navigate_layout_->addWidget(page_forward_button_);
 page_navigate_layout_->addSpacing(2);
 page_navigate_layout_->addWidget(page_last_button_);

 page_navigate_layout_->addStretch();
 page_select_and_navigate_layout_left_->addSpacing(4);
 page_select_and_navigate_layout_left_->addLayout(page_navigate_layout_);

 page_print_or_pdf_ = new QCheckBox(this);
 page_print_or_pdf_->setToolTip("When checled, uses print instead of PDF (raw) page numbers "
                                "(may use letters/symbols or not start at 1)");

 page_print_or_pdf_label_ = new QLabel("print");
 page_print_or_pdf_label_->setToolTip(page_print_or_pdf_->toolTip());

 page_select_and_navigate_layout_right_->setContentsMargins(0,0,0,0);
 page_select_and_navigate_layout_right_->setMargin(0);
 page_select_and_navigate_layout_right_->setSpacing(0);

 page_select_and_navigate_layout_right_->addStretch();
 page_select_and_navigate_layout_right_->addWidget(page_print_or_pdf_, Qt::AlignHCenter);
 page_select_and_navigate_layout_right_->addWidget(page_print_or_pdf_label_);
 page_select_and_navigate_layout_right_->setAlignment(page_print_or_pdf_, Qt::AlignRight);
 page_select_and_navigate_layout_right_->setAlignment(page_print_or_pdf_label_, Qt::AlignRight);

// QFrame* line = new QFrame(this);
// line->setFrameShape(QFrame::HLine); // Horizontal line
// line->setFrameShadow(QFrame::Sunken);
// line->setLineWidth(1);
// page_select_and_navigate_layout_right_->addWidget(line);

 cosigma(page_select_and_navigate_layout_right_)->add_horizontal_separator_line();


 page_select_and_navigate_layout_right_->addSpacing(2);

 page_select_and_navigate_layout_->addLayout(page_select_and_navigate_layout_left_);
 page_select_and_navigate_layout_->addLayout(page_select_and_navigate_layout_right_);

// main_layout_->addLayout(page_navigate_layout_);
 main_layout_->addLayout(page_select_and_navigate_layout_);

 main_layout_->addStretch();

 special_navigate_layout_ = new QHBoxLayout;
 special_select_ = new QComboBox(this);
 special_select_->addItem("Annotation");
 special_select_->addItem("Section");
 special_select_->addItem("Chapter");
 special_select_->addItem("Bookmarks");
 special_select_->setToolTip("When applicable, chooses which document or image-series feature is browsed via these forward/back buttons");

 special_back_button_ = new QPushButton(this);
 special_forward_button_ = new QPushButton(this);
 sigma(special_back_button_)->make_light_special_back_button();
 sigma(special_forward_button_)->make_light_special_forward_button();

 special_navigate_layout_->addWidget(special_select_);
 special_navigate_layout_->addSpacing(3);
 special_navigate_layout_->addWidget(special_back_button_);
 special_navigate_layout_->addSpacing(1);
 special_navigate_layout_->addWidget(special_forward_button_);

 main_layout_->addLayout(special_navigate_layout_);
 main_layout_->addStretch();


 search_layout_ = new QHBoxLayout;

 search_label_ = new QLabel("Search", this);
 search_line_edit_ = new QLineEdit(this);

 main_layout_->addWidget(search_line_edit_);

 search_layout_->addWidget(search_label_);
 search_layout_->addSpacing(3);

 search_up_button_ = new QPushButton(this);
 search_up_button_->setToolTip("Search Up");
 search_down_button_ = new QPushButton(this);
 search_down_button_->setToolTip("Search Down");
 search_from_top_button_ = new QPushButton(this);
 search_from_top_button_->setToolTip("Search From Top");

 sigma(search_up_button_)->make_up_button();
 sigma(search_down_button_)->make_down_button();
 sigma(search_from_top_button_)->make_top_down_button();

 search_layout_->addWidget(search_up_button_);
 search_layout_->addSpacing(2);
 search_layout_->addWidget(search_down_button_);
 search_layout_->addSpacing(2);
 search_layout_->addWidget(search_from_top_button_);

// search_case_sensitive_ = new QCheckBox(this);
// search_case_sensitive_->setToolTip("Case Sensitive Search");

 search_case_sensitive_button_ = new_child(QPushButton)("Aa");
 sigma(search_case_sensitive_button_)->set_multiline_tooltip("Case Sensitive Search",
   R"(When this button is "on" (via pressing the button
while in its normal state) PDF searches will be case-sensitive.
Turning the button "off" (by clicking it again) will revert to case-insensitive searching.)");

 //search_case_sensitive_button_->setToolTip("Case Sensitive Search");
 search_case_sensitive_button_->setCheckable(true);
 search_case_sensitive_button_->setChecked(false);

 search_case_sensitive_button_->setStyleSheet(light_checkable_button_style_sheet_orange_());
 sigma(search_case_sensitive_button_)->add_style_sheet(light_checkable_button_style_sheet_orange_hover_());


 search_case_sensitive_button_->setMaximumHeight(15);
 search_case_sensitive_button_->setMaximumWidth(22);

 search_layout_->addStretch();

 search_layout_->addWidget(search_case_sensitive_button_);

 main_layout_->addLayout(search_layout_);

 main_layout_->addStretch();

 setLayout(main_layout_);


 setMaximumHeight(140);

}


void Page_and_Search_Frame::reset_page_count(u4 last_page)
{
 // //  we want to signal that no user actions
  //    are triggering the page_select_ index
  //    while page_select_ itself is being updated
 info_.set_total_pages(0);

 page_max_label_->setText(page_max_label_text_.arg(last_page));
 page_select_->clear();
 for(u4 i = 1; i <= last_page; ++i)
 {
  page_select_->addItem(QString::number(i));
 }

 // //  only now can we set this value
  //    because the zero serves to
  //    prevent spurious page_select_
  //    actions as indicated above
 info_.set_total_pages(last_page);
}
