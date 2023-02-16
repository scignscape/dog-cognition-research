
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef GLOBAL_TYPES__H
#define GLOBAL_TYPES__H

#include <QtGlobal>
#include <QString>
#include <QMap>

//?
//#ifndef HAVE_NO_QT_GUI_MODULE
//#include <QValidator>
//#endif

#include <QPair>

#include <functional>

#include "global-macros.h"
#include "enum-macros.h"


#define CLASS_NAME_FOLDER_FN_1(ty)  \
inline QString class_name_folder(QString pre) \
{ \
 return pre + "/_" #ty; \
} \



#define CLASS_NAME_FOLDER_FN_0  \
inline QString class_name_folder(QString pre) \
{ \
 return pre + "/_" + this->metaObject()->className(); \
} \



#define CLASS_NAME_FOLDER_FN(...) \
  _preproc_CONCAT(CLASS_NAME_FOLDER_FN_, _preproc_NUM_ARGS (__VA_ARGS__))(__VA_ARGS__)

#define _CLASS_NAME_FOLDER_FN  CLASS_NAME_FOLDER_FN_0



#define CLASS_NAME_FN_classname(ty)  \
inline QString class_name_folder(QString pre) \
{ \
 return pre + "/_" #ty; \
} \

#define CLASS_NAME_FN_auto  \
inline QString class_name_folder(QString pre) \
{ \
 return pre + "/_" + this->metaObject()->className(); \
} \


#define CLASS_NAME_FN_2(mode, arg)  CLASS_NAME_FN_##mode(arg)

#define CLASS_NAME_FN_1(mode)  CLASS_NAME_FN_##mode


#define CLASS_NAME_FN(...) \
  _preproc_CONCAT(CLASS_NAME_FN_, _preproc_NUM_ARGS (__VA_ARGS__))(__VA_ARGS__)


inline char* q_to_std(const QString& qs)
{
 return const_cast<char*>( qs.toStdString().c_str() );
 //return qs.toStdString().c_str();
}

inline char* q_to_std_(QString qs)
{
 return const_cast<char*>( qs.toStdString().c_str() );
 //return qs.toStdString().c_str();
}


#define Q_TO_STD(qs) const_cast<char*>( qs.toStdString().c_str() )

#define call_Stamp(ty) ty

//#define call_Stamp_u2 u2


#define NULL_CALL_STAMP 0

typedef quint8 u1;
typedef quint16 u2;
typedef quint32 u4;
typedef quint64 n8;

struct call_Stamp_u2
{
 u2 value;
 call_Stamp_u2(u2 v) : value(v){}
 operator u2() { return value; }
};

typedef qint8 s1;
typedef qint16 s2;
typedef qint32 s4;
typedef qint64 s8;

typedef qreal r8;
typedef float r4;


typedef quint8 un1;
typedef quint16 un2;
typedef quint32 un4;
typedef quint64 nn8;

typedef qint8 si1;
typedef qint16 si2;
typedef qint32 si4;
typedef qint64 si8;


typedef char i1;

// //  allows someone to to define 
 //    integer types either signed 
 //    by default.  Unless explicitly 
 //    set, takes signedness from 
 //    default char ...
#include <climits>
#if (CHAR_MIN==0)
typedef quint16 i2;
typedef quint32 i4;
typedef quint64 i8;
#else
typedef qint16 i2;
typedef qint32 i4;
typedef qint64 i8;
#endif

//static inline QString operator ""_qt(const char* cs, size_t size)
//{
// std::string ss(cs, size);
// return QString::fromStdString(ss);
//}

template<typename T>
struct Defaulting_To_Zero
{
 T the_t;
 Defaulting_To_Zero(T tt) : the_t(tt){}
 Defaulting_To_Zero() : the_t(0){}
 operator T() { return the_t; }

 bool operator*()
 {
  return !is_max();
 }

 static Defaulting_To_Zero<T> get_max()
 {
  return Defaulting_To_Zero(std::numeric_limits<T>::max());
 }

 bool is_max()
 {
  return the_t == std::numeric_limits<T>::max();
 }

// operator bool()
// {
//  return the_t != -1;
// }
};

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


//typedef Defaulting_To_Zero<u1> z1;
//typedef Defaulting_To_Zero<u2> z2;
//typedef Defaulting_To_Zero<u4> z4;
//typedef Defaulting_To_Zero<u8> z8;


//#define until(x) return ({x}).inv;


#endif // GLOBAL_TYPES__H
