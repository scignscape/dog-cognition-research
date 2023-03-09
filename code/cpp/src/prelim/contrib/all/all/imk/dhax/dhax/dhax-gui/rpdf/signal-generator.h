
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef SIGNAL_GENERATOR__H
#define SIGNAL_GENERATOR__H


#include <QVector>
#include <QMap>
#include <QString>
#include <QUrl>
#include <QObject>


#include "accessors.h"

#include "global-types.h"

#include "chasm-lib/chasm/chasm-runtime.h"

#include "url-or-event-pattern.h"

#include "pattern-matcher-runtime.h"


class Signal_Generator : public QObject
{
 Q_OBJECT


public:

 Signal_Generator();

 void emit_new_dialog_requested(const QPoint& pos, QUrl url);

Q_SIGNALS:

 void new_dialog_requested(const QPoint& pos, QUrl url);

};


#endif //  SIGNAL_GENERATOR__H
