
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "dhax-graphics-view.h"

#include <QDebug>

#include <QGuiApplication>



DHAX_Graphics_View::DHAX_Graphics_View(QWidget* parent)
  :  QGraphicsView(parent),
     pdf_document_controller_(nullptr),
     image_document_controller_(nullptr)

{
 mouse_keyboard_data_.set_containing_metaobject(this->metaObject());

 //?activate_hand_drag_mode();
}


void DHAX_Graphics_View::activate_hand_drag_mode()
{
 setDragMode(ScrollHandDrag);
 setInteractive(false);
}


void DHAX_Graphics_View::deactivate_hand_drag_mode()
{
 setDragMode(NoDrag);
 setInteractive(true);
}


void DHAX_Graphics_View::mousePressEvent(QMouseEvent* mev)
{
 Qt::KeyboardModifiers ks = QGuiApplication::keyboardModifiers();
 Qt::MouseButtons bs = mev->buttons();
 mouse_keyboard_data_.check_update(bs, ks, mouse_keyboard_modifiers_callback_);
 this->QGraphicsView::mousePressEvent(mev);
}

void DHAX_Graphics_View::mouseReleaseEvent(QMouseEvent* mev)
{
 Qt::KeyboardModifiers ks = QGuiApplication::keyboardModifiers();
 Qt::MouseButtons bs = mev->buttons();
 mouse_keyboard_data_.check_update(bs, ks, mouse_keyboard_modifiers_callback_);

 this->QGraphicsView::mouseReleaseEvent(mev);

 //mev->ignore();
 //return;
}


void DHAX_Graphics_View::mouseMoveEvent(QMouseEvent* mev)
{
 Qt::KeyboardModifiers ks = QGuiApplication::keyboardModifiers();
 Qt::MouseButtons bs = mev->buttons();
 mouse_keyboard_data_.check_update(bs, ks, mouse_keyboard_modifiers_callback_);

 this->QGraphicsView::mouseMoveEvent(mev);
 //mev->ignore();
 //return;


// if(ks != Qt::NoModifier)
// {
//   mouse_move_modifiers_callback_(this->metaObject(), ks);
// }

 //this->metaObject();


// static int count = 0;

// qDebug() << " ... " << ++count;
}

