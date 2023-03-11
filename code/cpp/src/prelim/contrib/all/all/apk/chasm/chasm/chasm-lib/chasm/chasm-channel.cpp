
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "chasm-channel.h"


#include <QDebug>

//#include "compilation-unit-object.h"
//#include "unified-runtime-object.h"
//#include "metatype-object.h"


Chasm_Channel::Chasm_Channel(QString name)
 :  name_(name)
{

}

void Chasm_Channel::pasn8vector(QVector<n8>& result, u1 size)
{
 result.resize(size);
 for(s1 i = 0; i < size; ++i)
   result[i] = pasn8(i + 1);
}

void Chasm_Channel::add_carriers(std::deque<Chasm_Carrier>& ccs)
{
 for(Chasm_Carrier& cc : ccs)
   carriers_.push_back(cc);
}


Chasm_Carrier Chasm_Channel::first_carrier()
{
 //static Chasm_Carrier fallback;
 if(carriers_.isEmpty())
   return {};
//  return fallback;

 return carriers_.first();
}
