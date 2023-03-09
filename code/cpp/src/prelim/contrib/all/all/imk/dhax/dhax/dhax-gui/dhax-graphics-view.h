
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef DHAX_GRAPHICS_VIEW__H
#define DHAX_GRAPHICS_VIEW__H

#include <QGraphicsView>

#include <QMouseEvent>

#include <functional>

#include "accessors.h"

#include "global-types.h"

#include <QDebug>
//#include <QGadget>


class PDF_Document_Controller;
class Image_Document_Controller;



class DHAX_Mouse_Keyboard_Data //: public QGadget
{
 // // Q_GADGET

 u2 components_ : 16;
 s2 increment_ : 16;
 u2 prior_components_ : 16;
 u2 temp_components_ : 16;

 const QMetaObject* containing_metaobject_;

public:

 DHAX_Mouse_Keyboard_Data()
   :  components_(0), increment_(0), prior_components_(0),
      temp_components_(0), containing_metaobject_(nullptr)
 {}

 ACCESSORS(s2 ,increment)
 ACCESSORS(const QMetaObject* ,containing_metaobject)

 void read_qt_keyboard_modifiers(Qt::KeyboardModifiers ks)
 {
  if(ks.testFlag(Qt::ShiftModifier))
    components_ |= (u2) State_Components::Shift_Key_Pressed;

  if(ks.testFlag(Qt::MetaModifier))
    components_ |= (u2) State_Components::Meta_Key_Pressed;

  if(ks.testFlag(Qt::ControlModifier))
    components_ |= (u2) State_Components::Control_Key_Pressed;
 }

 void release_qt_keyboard_modifiers(Qt::KeyboardModifiers ks)
 {
  if(ks.testFlag(Qt::ShiftModifier))
    components_ ^= (u2) State_Components::Shift_Key_Pressed;

  if(ks.testFlag(Qt::MetaModifier))
    components_ ^= (u2) State_Components::Meta_Key_Pressed;

  if(ks.testFlag(Qt::ControlModifier))
    components_ ^= (u2) State_Components::Control_Key_Pressed;
 }

 void read_mouse_buttons(Qt::MouseButtons bs)
 {
  if(bs.testFlag(Qt::LeftButton))
    components_ |= (u2) State_Components::Mouse_Left_Button_Pressed;
 }

 void release_mouse_button(Qt::MouseButtons bs)
 {
  if(bs.testFlag(Qt::LeftButton))
    components_ ^= (u2) State_Components::Mouse_Left_Button_Pressed;
 }

 enum class State_Components {
   N_A,
   Mouse_Left_Button_Pressed = 1,  //0x01
   Mouse_Left_Button_Released = 2, //0x02
   Mouse_Right_Button_Pressed = 4, //0x04
   Mouse_Right_Button_Released = 8, //0x08
   Mouse_Center_Button_Pressed = 16, //0x10
   Mouse_Center_Button_Scrolled = 32, //0x20
   Mouse_Center_Button_Released = 64, //0x40
   Shift_Key_Pressed = 128, //0x80
   Shift_Key_Released = 256,  //0x0100
   Control_Key_Pressed = 512,  //0x0200
   Control_Key_Released = 1024, //0x0400
   Meta_Key_Pressed = 2048, //0x0800
   Meta_Key_Released = 4096, //0x1000
   Alt_Key_Pressed = 8192, //0x2000
   Alt_Key_Released = 16384, //0x4000
 };

 State_Components get_state()
 {
  return (State_Components) components_;
 }

 bool Shift_left()
 {
  static u2 mask = ((u2) State_Components::Mouse_Left_Button_Pressed) |
    ((u2) State_Components::Shift_Key_Pressed);
  return (components_ & mask) == mask;
 }

 bool Unshift_left()
 {
  static u2 mask = ((u2) State_Components::Mouse_Left_Button_Pressed) |
    ((u2) State_Components::Shift_Key_Released);
  return (components_ & mask) == mask;
 }

 bool Unshift_unleft()
 {
  static u2 mask = ((u2) State_Components::Mouse_Left_Button_Released) |
    ((u2) State_Components::Shift_Key_Released);
  return (components_ & mask) == mask;
 }

 bool Meta_left()
 {
  static u2 mask = ((u2) State_Components::Mouse_Left_Button_Pressed) |
    ((u2) State_Components::Meta_Key_Pressed);
  return (components_ & mask) == mask;
 }

 bool Unmeta_left()
 {
  static u2 mask = ((u2) State_Components::Mouse_Left_Button_Pressed) |
    ((u2) State_Components::Meta_Key_Released);
  return (components_ & mask) == mask;
 }

 bool Unmeta_unleft()
 {
  static u2 mask = ((u2) State_Components::Mouse_Left_Button_Released) |
    ((u2) State_Components::Meta_Key_Released);
  return (components_ & mask) == mask;
 }


 bool Unleft()
 {
  static u2 mask = (u2) State_Components::Mouse_Left_Button_Released;
  return (components_ & mask);
 }

 bool Ctrl_left()
 {
  static u2 mask = ((u2) State_Components::Mouse_Left_Button_Pressed) |
    ((u2) State_Components::Control_Key_Pressed);
  return (components_ & mask) == mask;
 }

 bool Unctrl_left()
 {
  static u2 mask = ((u2) State_Components::Mouse_Left_Button_Pressed) |
    ((u2) State_Components::Control_Key_Released);
  return (components_ & mask) == mask;
 }

 bool Unctrl_unleft()
 {
  static u2 mask = ((u2) State_Components::Mouse_Left_Button_Released) |
    ((u2) State_Components::Control_Key_Released);
  return (components_ & mask) == mask;
 }

 void check_update(Qt::MouseButtons bs, Qt::KeyboardModifiers ks,
   std::function<void(DHAX_Mouse_Keyboard_Data)> cb)
 {
  prior_components_ = components_;
  components_ = 0;
  read_mouse_buttons(bs);
  read_qt_keyboard_modifiers(ks);
  temp_components_ = components_;

  if((prior_components_ & (u2) State_Components::Shift_Key_Pressed)
   && !(components_ & (u2) State_Components::Shift_Key_Pressed))
  {
   components_ |= (u2) State_Components::Shift_Key_Released;
  }
  else if(!(prior_components_ & (u2) State_Components::Shift_Key_Pressed)
          && (components_ & (u2) State_Components::Shift_Key_Pressed))
  {
   temp_components_ = 0; // ^= (u2) State_Components::Shift_Key_Pressed;
  }

  if((prior_components_ & (u2) State_Components::Control_Key_Pressed)
   && !(components_ & (u2) State_Components::Control_Key_Pressed))
  {
   components_ |= (u2) State_Components::Control_Key_Released;
  }
  else if(!(prior_components_ & (u2) State_Components::Control_Key_Pressed)
          && (components_ & (u2) State_Components::Control_Key_Pressed))
  {
   temp_components_ = 0; // ^= (u2) State_Components::Shift_Key_Pressed;
  }


  if((prior_components_ & (u2) State_Components::Mouse_Left_Button_Pressed)
   && !(components_ & (u2) State_Components::Mouse_Left_Button_Pressed))
  {
   components_ |= (u2) State_Components::Mouse_Left_Button_Released;
  }
  else if(!(prior_components_ & (u2) State_Components::Mouse_Left_Button_Pressed)
          && (components_ & (u2) State_Components::Mouse_Left_Button_Pressed))
  {
   temp_components_ = 0; // ^= (u2) State_Components::Shift_Key_Pressed;
  }

  if(components_ != temp_components_)
  {
   cb(*this);
  }

 }

};


class DHAX_Graphics_View :  public QGraphicsView
{
 Q_OBJECT

 std::function<void(DHAX_Mouse_Keyboard_Data)>
   mouse_keyboard_modifiers_callback_;

 DHAX_Mouse_Keyboard_Data mouse_keyboard_data_;

 PDF_Document_Controller* pdf_document_controller_;
 Image_Document_Controller* image_document_controller_;


protected:

 void mousePressEvent(QMouseEvent* mev) Q_DECL_OVERRIDE;
 void mouseMoveEvent(QMouseEvent* mev) Q_DECL_OVERRIDE;
 void mouseReleaseEvent(QMouseEvent* mev) Q_DECL_OVERRIDE;


public:

 DHAX_Graphics_View(QWidget* parent = nullptr);

 ACCESSORS(std::function<void(DHAX_Mouse_Keyboard_Data)>
   ,mouse_keyboard_modifiers_callback)

 ACCESSORS(PDF_Document_Controller* ,pdf_document_controller)
 ACCESSORS(Image_Document_Controller* ,image_document_controller)

 void activate_hand_drag_mode();
 void deactivate_hand_drag_mode();

};

#endif //  DHAX_GRAPHICS_VIEW__H




