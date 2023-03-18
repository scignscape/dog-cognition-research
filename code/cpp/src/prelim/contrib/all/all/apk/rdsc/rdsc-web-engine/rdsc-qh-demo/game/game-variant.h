
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef GAME_VARIANT__H
#define GAME_VARIANT__H

#include "accessors.h"

#include "flags.h"

#include "global-types.h"

#include <QString>
#include <QQueue>


class Game_Driver;

class Game_Variant
{
 QString name_;
 Game_Driver* parent_driver_;


public:

 Game_Variant(QString name, Game_Driver* parent_driver);

 ACCESSORS(QString ,name)

};


#endif // GAME_VARIANT__H
