
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef COMBOBOX_DATA__H
#define COMBOBOX_DATA__H


#include "global-types.h"


#ifndef HAVE_NO_QT_GUI_MODULE
struct ComboBox_Data
{
 u1 max_index;
 u1 current_selected_index;
 u1 temp_in_process_index;
 u1 current_alt_selected_index;
 void* extra_items;

 enum Status {
  Pre_Init = 1, Editable = 2, Insertable = 4,
  Processing_Non_Standard_Item = 8,
  Extra_Items_Are_Texts = 16
 };

 Status status;

 bool status_Pre_Init() { return status & Status::Pre_Init; }
 bool status_Editable() { return status & Status::Editable; }
 bool status_Processing_Non_Standard_Item() { return status & Status::Processing_Non_Standard_Item; }

 void mark_initialized()
 {
  //   if(status & Status::Pre_Init)
  //     status ^= Status::Pre_Init;
  status ,+ Status::Pre_Init;
 }
 void mark_processing_non_standard() { status |= Status::Processing_Non_Standard_Item; }
 void clear_processing_non_standard()
 {
  //   if(status & Status::Processing_Non_Standard_Item)
  //     status ^= Status::Processing_Non_Standard_Item;
  status ,+ Status::Processing_Non_Standard_Item;
 }

 ENUM_FLAGS_OP_MACROS(Status)

 ComboBox_Data():
   max_index(0), current_selected_index(-1),
   temp_in_process_index(-1), current_alt_selected_index(-1),
   status(Pre_Init | Editable | Insertable), extra_items(nullptr)
 {}

 QMap<u1, u2>* extra_numbers()
 {
  if(!extra_items)
   extra_items = new QMap<u1, u2>;
  return (QMap<u1, u2>*) extra_items;
 }

 QMap<u1, QString>* extra_texts()
 {
  if(!extra_items)
   extra_items = new QMap<u1, QString>;
  return (QMap<u1, QString>*) extra_items;
 }

 void clear_temp_in_process_index() {temp_in_process_index = -1;}

 void reset() { *this = ComboBox_Data(); }

 template<typename WIDGET_Type, typename VALUE_Type,
          VALUE_Type nothing = (VALUE_Type) -1>
 QPair<VALUE_Type, VALUE_Type> callback_over_increment_data(WIDGET_Type* w, int index, VALUE_Type increment)
 {
  VALUE_Type result = (VALUE_Type) w->currentText().toInt();
  VALUE_Type old = nothing;

  if(status_Processing_Non_Standard_Item())
  {
   if(index > max_index)
   {
    const QSignalBlocker bl(w);
    old = w->itemText(temp_in_process_index).toInt();
    w->removeItem(temp_in_process_index);
    clear_temp_in_process_index();
    --index;
   }
   else
   {
    clear_processing_non_standard();
    return {result, nothing};
   }
  }

  if(index > max_index)
  {
   mark_processing_non_standard();
   u1 new_value = (u1) w->currentText().toUInt();
   u1 insert = (new_value / increment) + 1;
   (*extra_numbers())[insert] = new_value;
   const QSignalBlocker bl(w);
   w->removeItem(index);
   w->insertItem(insert, QString::number(new_value));
   temp_in_process_index = insert;
   current_selected_index = insert;
   w->setCurrentIndex(insert);
  }
  else
  {
   current_selected_index = index;
  }

  return {result, old};
 }

 static const QIntValidator* int_validator(int bottom, int top)
 {
  static QMap<QPair<int, int>, const QIntValidator*> cached;
  auto it = cached.find({bottom, top});
  if(it == cached.end())
  {
   const QIntValidator* result = new QIntValidator(bottom, top);
   cached[{bottom, top}] = result;
   return result;
  }
  return it.value();
 }
};
#endif //HAVE_NO_QT_GUI_MODULE


#endif // COMBOBOX_DATA__H

