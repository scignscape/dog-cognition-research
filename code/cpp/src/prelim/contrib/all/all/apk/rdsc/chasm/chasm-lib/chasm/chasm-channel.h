
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef CHASM_CHANNEL__H
#define CHASM_CHANNEL__H

#include <QString>

#include "accessors.h"
#include "flags.h"

#include "global-types.h"

#include <functional>

#include "kans.h"

#include "chasm-carrier.h"

#include <deque>


//KANS_(GTagML)

class Chasm_Channel
{
 QString name_;

 QVector<Chasm_Carrier> carriers_;


public:

 Chasm_Channel(QString name);

 ACCESSORS(QString ,name)
 ACCESSORS(QVector<Chasm_Carrier> ,carriers)

 void add_carrier(const Chasm_Carrier& cc)
 {
  carriers_.push_back(cc);
 }

 void add_carriers(const QVector<Chasm_Carrier>& ccs)
 {
  carriers_.append(ccs);
 }

 void add_carriers(std::deque<Chasm_Carrier>& ccs);


 Chasm_Carrier first_carrier();

 void pasn8vector(QVector<n8>& result, u1 size);

 n8 pasn8(s4 index)
 {
  if(index > carriers_.size())
    return 0;

  Chasm_Carrier& cc = carriers_[index - 1];
  return cc.pasn8();
 }

};

// _KANS(GTagML)

#endif // CHASM_CHANNEL__H

