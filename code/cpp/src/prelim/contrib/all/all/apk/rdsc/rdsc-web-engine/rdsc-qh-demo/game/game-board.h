
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


#include "kans.h"
KANS_CLASS_DECLARE(RdSC ,QH_Web_View_Dialog)

USING_KANS(RdSC)

class Game_Driver;

class Game_Board
{
 Game_Driver* driver_;

 Mat2d< Vec1d<Game_Position> > slot_positions_;
 Mat2d< Vec1d<Game_Position> > non_slot_positions_;

 QMap<QString, Game_Position*> game_positions_by_label_code_;

 QMap<QPair<u1, u1>, Game_Position*> game_positions_by_coords_;

 s2 next_token_number_;

public:

 Game_Board(Game_Driver* driver);

 ACCESSORS(s2 ,next_token_number)

 void debug_board(QString file);
 void to_svg(QString in_folder, QString out_file);

 Game_Position* get_game_position_by_label_code(QString lc);

 void handle_token_placement(QH_Web_View_Dialog* dlg, Game_Token* token, QString pos_id);

// void increment_next_token_number()
// {
//  if(next_token_number_ < 0)
//    next_token_number_ = -next_token_number_;
//  else
//    next_token_number_ = -1 - next_token_number_;
// }

};



#endif // GAME_DRIVER__H
