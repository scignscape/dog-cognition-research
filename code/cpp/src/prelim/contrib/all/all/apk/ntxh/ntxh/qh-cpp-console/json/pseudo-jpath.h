
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef PSEUDO_JPATH__H
#define PSEUDO_JPATH__H

#include <QByteArray>

#include <functional>

#include "global-types.h"

#include "accessors.h"

class QJsonDocument;
class QJsonParseError;

#include "kans.h"

#include <QJsonDocument>

KANS_(RdSC)

class Qh_Type;
class Qh_Type_System;

class Pseudo_JPath
{
 QJsonDocument document_;

public:

 explicit Pseudo_JPath(QJsonDocument document);

 ACCESSORS(QJsonDocument ,document)

 QVariant evaluate(QString expression);


};

_KANS(RdSC)


#endif // PSEUDO_JPATH__H


