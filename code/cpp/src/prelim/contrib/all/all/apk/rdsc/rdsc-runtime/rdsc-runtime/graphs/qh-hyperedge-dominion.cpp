
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "qh-hyperedge-dominion.h"

#include "qh-node-frame.h"

#include "qh-pack-code.h"
#include "qh-pack-builder.h"

USING_KANS(RdSC)

Qh_Hyperedge_Dominion::Qh_Hyperedge_Dominion(QString description)
  :  description_(description)
{
 if(description_.isEmpty())
   description_ = "default";
}

void Qh_Hyperedge_Dominion::add_label(QString label)
{
 labels_[label] = new QStringList;
}

void Qh_Hyperedge_Dominion::add_label(QString label, QString alias)
{
 add_label(label);
 aliases_[alias] = label;
}

