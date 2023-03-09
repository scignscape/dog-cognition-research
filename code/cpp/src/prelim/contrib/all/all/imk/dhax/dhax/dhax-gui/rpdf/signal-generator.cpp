
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "signal-generator.h"


Signal_Generator::Signal_Generator()
{

}

void Signal_Generator::emit_new_dialog_requested(const QPoint& pos, QUrl url)
{
 Q_EMIT new_dialog_requested(pos, url);
}

