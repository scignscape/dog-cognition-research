
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef GAME_BOARD__H
#define GAME_BOARD__H

#include "accessors.h"

#include "flags.h"

#include "game-position.h"

#include "rdsc-2d/mat2d.h"

USING_KANS(RdSC)


class Game_Board
{
 Mat2d< Vec1d<Game_Position> > slot_positions_;
 Mat2d< Vec1d<Game_Position> > non_slot_positions_;

 QMap<QString, Game_Position*> game_positions_by_label_code_;

 QMap<QPair<u1, u1>, Game_Position*> game_positions_by_coords_;

public:

 Game_Board();

 void debug_board(QString file);
 void to_svg(QString in_folder, QString out_file);

};



#endif // GAME_DRIVER__H
