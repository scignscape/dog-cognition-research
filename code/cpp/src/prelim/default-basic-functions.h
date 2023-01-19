
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef DEFAULT_BASIC_FUNCTIONS__H
#define DEFAULT_BASIC_FUNCTIONS__H


#include "accessors.h"

#include "kans.h"

#include <QString>
#include <QStringList>

#include <QMap>


KANS_(Phaon)

class PHR_Channel_Group_Table;
class PHR_Symbol_Scope;
class PHR_Code_Model;

class PHR_Channel_System;
class PhaonIR;

_KANS(Phaon)

USING_KANS(Phaon)


void init_basic_functions(PhaonIR& phr, PHR_Code_Model& pcm,
  PHR_Channel_Group_Table& table, PHR_Symbol_Scope& pss);

#endif // DEFAULT_BASIC_FUNCTIONS__H
