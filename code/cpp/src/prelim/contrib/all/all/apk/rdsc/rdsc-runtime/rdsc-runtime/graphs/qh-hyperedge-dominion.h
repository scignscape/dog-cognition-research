
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef QH_HYPEREDGE_DOMINION__H
#define QH_HYPEREDGE_DOMINION__H

#include <QByteArray>

#include <QVariant>

#include <functional>

#include "global-types.h"

#include "accessors.h"
//class Qh_Bundle_Code;

#include "qh-pack-code.h"


KANS_(RdSC)

class Qh_Hypernode;
class Qh_Node_Frame;
class Qh_Node_Data;

class Qh_Hyperedge_Dominion
{
 QMap<QString, QStringList*> labels_;
 QString description_;

 QMap<QString, QString> aliases_;

public:

 Qh_Hyperedge_Dominion(QString description = {});

 struct Label
 {
  Qh_Hyperedge_Dominion* _this;
  QString _label;
 };

 ACCESSORS(QString ,description)

 void add_label(QString label);
 void add_label(QString label, QString alias);

 Label operator()(QString lbl)
 {
  if(labels_.contains(lbl))
    return {this, lbl};
  auto it = aliases_.find(lbl);
  if(it == aliases_.end())
    return {nullptr, lbl};

  return operator()(it.value());
 }

};

_KANS(RdSC)



#endif // QH_HYPEREDGE_DOMINION__H


