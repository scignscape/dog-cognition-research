
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef DW_STAGE_QUEUE__H
#define DW_STAGE_QUEUE__H

#include <QVector>
#include <QQueue>

#include <QDateTime>
#include <QDate>

#include <QDebug>

#include <functional>

#include "accessors.h"

#include "global-types.h"

#include "kans.h"

KANS_(DGDB)

//struct void*
//{
// void* value;
//};

struct DW_Stage_Queue  
{
 //typedef void(*callback_type)(QQueue<void*>&);

 QQueue<void*> values;
 std::function<void(QQueue<void*>&)> callback;

 DW_Stage_Queue();

 void* head();

// void* dequeue()
// {
//  return values.dequeue();
// }

 void operator=(std::initializer_list<void*> vs) 
 { 
  values.append(QList<void*>(vs)); 
 }
 void operator<<(std::function<void(QQueue<void*>&)> cb)
   { callback = cb; }

 void enqueue_void(void* v);

 u1& skip()
 {
  static u1 result = 0;
  return result;
 }
 
 template<typename T>
 T* enqueue(T* tt)
 {
  values.enqueue((void*) tt);
  return tt;
 }

 void reverse();

 template<typename T>
 T& enqueue_new()
 {
  T* result = new T;
  values.enqueue(result);
  return *result;
 } 

};

template<typename T>
std::function<void(QQueue<void*>&)> default_stage_queue_reader(void (T::*fn)(QQueue<void*>&))
{
 return [fn](QQueue<void*>& qq)
 {
  (((T*) qq.dequeue())->*fn)(qq);
 };
}




_KANS(DGDB)

#endif // DW_STAGE_QUEUE__H


