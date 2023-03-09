
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef SHAPE_SELECT_FRAME__H
#define SHAPE_SELECT_FRAME__H

#include <QFrame>

#include <QPushButton>
#include <QVBoxLayout>
#include <QComboBox>
#include <QCheckBox>
#include <QButtonGroup>

#include <QTabWidget>

#include "global-types.h"

#include "combobox-data.h"

#include "self-connect.h"

#include "styles.h"

class QLabel;


class Shape_Select_Frame : public QFrame
{
 Q_OBJECT

#define _sigma_ns_(global)
#define _my_sigma_(includes) \
includes(tooltip, layout, buttons, stylesheet)
#include "sigma.h"

 QFrame* main_tab_;

 QFrame* clear_last_all_tab_;
 QFrame* image_setup_tab_;

 QTabWidget* main_tab_widget_;

 QPushButton* margin_mode_button_;
 QPushButton* margin_mode_view_button_;

 QLabel* clear_label_;
 QPushButton* clear_selected_button_;
 QPushButton* clear_last_button_;
 QPushButton* clear_all_button_;

 QVBoxLayout* main_layout_;

 QVBoxLayout* main_tab_layout_;
 QHBoxLayout* main_tab_layout1_;
 QHBoxLayout* main_tab_layout2_;

 QVBoxLayout* clear_last_all_tab_layout_;

 QLabel* scene_label_;
 QPushButton* scene_color_button_;

 QLabel* back_label_;
 QPushButton* back_color_button_;

 QPushButton* border_visible_button_;
 QPushButton* edit_transform_button_;

 QHBoxLayout* clear_last_all_layout_1_;
 QHBoxLayout* clear_last_all_layout_2_;
 QHBoxLayout* clear_last_all_layout_3_;

 QHBoxLayout* clear_last_all_layout_23_;
 QVBoxLayout* clear_last_all_layout_23_left_;
 QVBoxLayout* clear_last_all_layout_23_right_;


 QVBoxLayout* image_setup_tab_layout_;

 QLabel* image_path_label_;
 QLineEdit* image_path_line_edit_;
 QPushButton* image_path_show_folder_button_;
 QHBoxLayout* image_path_layout_;

 QLabel* vertical_margin_label_;

 QCheckBox* vertical_margin_percent_check_box_;
 QLabel* vertical_margin_percent_check_box_label_;

 QComboBox* vertical_margin_combo_box_;
 QHBoxLayout* vertical_margin_layout_;

 ComboBox_Data vertical_margin_combo_box_data_;

 QCheckBox* sides_margin_check_box_;
 QLabel* sides_margin_check_box_label_;
 QComboBox* sides_margin_combo_box_;

 ComboBox_Data sides_margin_combo_box_data_;

 QHBoxLayout* border_layout_;
 QLabel* border_label_;
 QComboBox* border_combo_box_;
 ComboBox_Data border_combo_box_data_;

 QLabel* border_color_label_;
 QPushButton* border_color_button_;

 QCheckBox* domain_shape_ckb_;
 QComboBox* domain_shape_options_;

 QCheckBox* generic_shape_ckb_;
 QComboBox* generic_shape_options_;

 QButtonGroup* shape_ckb_group_;

 // QString current_shape_selection_;
 //QCheckBox* highlight_ckb_;

 QPushButton* image_pen_visible_button_;
 QPushButton* image_pen_color_button_;


 QHBoxLayout* save_button_layout_;
 QCheckBox* auto_store_check_box_;
 QPushButton* store_button_;
 QPushButton* save_button_;
 QPushButton* close_button_;

 QPushButton* auto_store_config_button_;
 QPushButton* cloud_store_button_;
 QCheckBox* cloud_store_check_box_;

 QHBoxLayout* save_and_close_layout_;
 QVBoxLayout* save_layout_;
 QLabel* auto_store_label_;


public:

 Shape_Select_Frame(QWidget* parent);

 USE_SELF_CONNECT(normal)
 USE_SELF_CONNECT(lambda)


 QString current_shape_selection();

 void update_shape_selection();

 void update_border_color_button_color(QColor c);
 void update_scene_color_button_color(QColor c);
 void update_back_color_button_color(QColor c);
 void update_image_pen_color_button_color(QColor c);

 void switch_to_margins_percent();
 void switch_to_margins_non_percent();
 void populate_margins_non_percent(bool clear = false);

 void set_clear_selected_button_disabled()
 {
  clear_selected_button_->setDisabled(true);
 }
 void set_clear_selected_button_enabled()
 {
  clear_selected_button_->setEnabled(true);
 }

 void set_clear_last_button_disabled()
 {
  clear_last_button_->setDisabled(true);
 }
 void set_clear_last_button_enabled()
 {
  clear_last_button_->setDisabled(false);
 }

 void set_clear_all_button_disabled()
 {
  clear_last_button_->setDisabled(true);
 }
 void set_clear_all_button_enabled()
 {
  clear_last_button_->setDisabled(false);
 }

 void set_highlight_ckb_disabled()
 {
//  highlight_ckb_->setDisabled(true);
 }
 void set_highlight_ckb_enabled()
 {
//  highlight_ckb_->setDisabled(false);
 }

 bool clear_selected_button_is_enabled()
 {
  return clear_selected_button_->isEnabled();
 }

 bool clear_last_button_is_enabled()
 {
  return clear_last_button_->isEnabled();
 }

 bool clear_all_button_is_enabled()
 {
  return clear_all_button_->isEnabled();
 }

 void update_image_path(QString path, u4 page_number = 0);

Q_SIGNALS:

 void shape_selection_changed(QString new_selection);
 void save_requested(bool);
 void close_requested(bool);

 void edit_transform_open_automatically_requested(bool);

 void image_path_show_folder_requested(bool);
 void change_border_color_requested(bool);
 void change_scene_color_requested(bool);
 void change_back_color_requested(bool);
 void change_image_pen_color_requested(bool);

 void change_border_visible_state_requested(bool);
 void change_image_pen_visible_state_requested(bool);

 void change_border_width_requested(u1 width);

 void change_vertical_margin_percent_requested(u1, bool);
 void change_vertical_margin_requested(u1, bool);
 void new_vertical_margin_value_rescinded(u1);


};


#endif
