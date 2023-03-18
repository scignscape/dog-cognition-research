
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef AU_GAME_VARIANT__H
#define AU_GAME_VARIANT__H

#include "accessors.h"

#include "flags.h"

#include "global-types.h"

#include <QString>
#include <QQueue>

#include "game/game-variant.h"


class Game_Driver;

class AU_Game_Variant : public Game_Variant
{

public:

 AU_Game_Variant(QString name, Game_Driver* parent_driver);


};


#endif // AU_GAME_VARIANT__H
