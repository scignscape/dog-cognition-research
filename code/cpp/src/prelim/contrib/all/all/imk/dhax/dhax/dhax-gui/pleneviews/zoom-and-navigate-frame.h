
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef ZOOM_AND_NAVIGATE_FRAME__H
#define ZOOM_AND_NAVIGATE_FRAME__H

#include <QFrame>

#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QComboBox>
#include <QCheckBox>
#include <QButtonGroup>
#include <QGroupBox>

#include <QDebug>
#include <QString>

//
#include "subwindows/range-slider.h"

#include "global-types.h"

#include "styles.h"

#include "self-connect.h"


//#define SIGMA_INCLUDES(inc) inc(sigma-multiline, sigma-test)

//#define SIGMA_INCLUDES \
//#include "sigma-multiline.h"\
//#include "sigma-test.h"\


//#define SIGMA_INC  "sigmas/sigma-multiline.h"

//#define SIGMA_INC(inc)  inc(sigma-multiline) //, sigma-test)
//#ifdef SIGMA_INC

//#define SIGMA_INC(sigma-multiline) //  inc(sigma-multiline) //, sigma-test)
//#endif

#include "accessors.h"


class AXFI_Annotation;
class QLabel;

class Zoom_and_Navigate_Frame : public QFrame
{
 Q_OBJECT

 #define _sigma_ns_(global)
 #define _my_sigma_(includes) \
 includes(tooltip, buttons)
 #include "sigma.h"

 QPushButton* zoom_in_button_;
 QPushButton* zoom_out_button_;

 QPushButton* reset_all_button_;

 QPushButton* reset_zoom_button_;
 QPushButton* repeat_zoom_button_;

 QPushButton* expand_window_button_;
 QPushButton* unexpand_window_button_;

 QPushButton* image_top_left_button_;
 QPushButton* center_image_button_;
 QPushButton* replace_center_image_button_;


 QPushButton* pan_mode_button_;
 QCheckBox* pan_mode_ckb_;

// QPushButton* pull_mode_button_;
 QCheckBox* pull_mode_ckb_;

 QCheckBox* margin_pull_mode_ckb_;
 QLabel* margin_pull_mode_ckb_label_;

 QCheckBox* multi_draw_ckb_;
 QLabel* multi_draw_ckb_label_;
//? QHBoxLayout* bottom_layout_;

 QSlider* zoom_slider_[3];

 QGroupBox* zoom_sliders_top_group_box_;
 QHBoxLayout* zoom_sliders_top_group_box_layout_;

 QGroupBox* zoom_sliders_group_box_;
 QVBoxLayout* zoom_sliders_group_box_layout_;

 QHBoxLayout* zoom_buttons_layout_;
 QVBoxLayout* main_layout_;

 //?QHBoxLayout* position_buttons_layout_;
 QGridLayout* position_buttons_layout_;

 void* image_data_;

 bool handle_zoom_ok_;
 u2 initial_zoom_position_;
 u2 initial_annotation_zoom_position_;

 u2 last_zoom_position_;
 u2 last_annotation_zoom_position_;

 AXFI_Annotation* current_selected_annotation_;

// QLabel* status_label_;
// QLabel* status_text_;

 void adjust_zoom(int z);
 void direct_adjust_zoom(int z);

 void recenter_image();

 void adjust_annotation_zoom_slider(s2 diff);


public:

 Zoom_and_Navigate_Frame(QWidget* parent);

 ACCESSORS(void* ,image_data)
 ACCESSORS(AXFI_Annotation* ,current_selected_annotation)

 USE_SELF_CONNECT(normal)
 USE_SELF_CONNECT(lambda)

 void reset_with_image_data(void* image_data);
 void reset_current_selected_annotation(AXFI_Annotation* axa);

 void indicate_temporary_pan_mode();
 void unindicate_temporary_pan_mode();

 void indicate_temporary_pull_mode();
 void unindicate_temporary_pull_mode();

 void unindicate_temporary_modes();

Q_SIGNALS:

 void zoom_factor_changed(r8 factor);

 void expand_window_button_clicked(bool);
 void unexpand_window_button_clicked(bool);

 void replace_center_image_button_clicked(bool);
 void center_image_button_clicked(bool);
 void image_top_left_button_clicked(bool);

 void reset_notes_zoom_requested(bool);
 void pan_mode_changed(bool);
 void pull_mode_changed(bool);

 void multi_draw_unset();
 void multi_draw_set();

public Q_SLOTS:

 void handle_zoom_minimum_value_changed(int val);
 void handle_zoom_maximum_value_changed(int val);

 void handle_top_zoom_minimum_value_changed(int val);
 void handle_top_zoom_maximum_value_changed(int val);

 void handle_zoom_in_discrete(bool);
 void handle_zoom_out_discrete(bool);

 void handle_reset_zoom(bool);
 void handle_repeat_zoom(bool);
 void handle_reset_all(bool);

 void handle_annotation_zoom_value_changed(int);


};


#endif
