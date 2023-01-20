
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "dh-stage-queue.h"


//USING_KANS(DGDB)

//QQueue<void*> DH_Stage_Queue::xvalues = QQueue<void*>();

DH_Stage_Queue::DH_Stage_Queue()
  : callback(nullptr) 
{
 
}

void* DH_Stage_Queue::head()
{
 return values.head();
}

void DH_Stage_Queue::reverse()
{ 
 void* obj = values.dequeue();
 std::reverse(std::begin(values), std::end(values));
 values.prepend(obj);
}


void DH_Stage_Queue::enqueue_void(void* v)
{
 values.enqueue(v);
}

