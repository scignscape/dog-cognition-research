
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef HGDM_STEPS__H
#define HGDM_STEPS__H

#include <QString>
#include <QVariant>


#include "global-types.h"

class HGDM_Traverser
{

public:

 virtual HGDM_Traverser& selto(QString cue) = 0;
 virtual QVariant read() = 0;

};


#endif // HGDM_STEPS__H

