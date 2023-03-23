
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

#include "game/variants/game-variant.h"


class Game_Driver;

class AU_Game_Variant : public Game_Variant
{
 void check_move_options_Generic(Direction_Codes dc,
   Game_Token* token, Game_Position* start_position,
   QVector<Move_Option>& move_options, s1 increment, s2 minimum_legal_move,
   s1 minimum_check);

 void check_move_options_JQK(Game_Token* token, Game_Position* start_position, QVector<Move_Option>& move_options);
 void check_move_options_Rook(Game_Token* token, Game_Position* start_position, QVector<Move_Option>& move_options);
 void check_move_options_Bishop(Game_Token* token, Game_Position* start_position, QVector<Move_Option>& move_options);
 void check_move_options_Knight(Game_Token* token, Game_Position* start_position, QVector<Move_Option>& move_options);

 void check_move_options_Knight_light_slot(Game_Position* gp,
   QVector<Move_Option>& move_options, u2& count);
 void check_move_options_Knight_dark_slot(Game_Position* gp,
   QVector<Move_Option>& move_options, u2& count);

 //void check_move_option(Game_Token* token, Game_Position* start_position, QPair<s1, s1> offsets, QVector<Move_Option>& move_options);

public:

 AU_Game_Variant(QString name, Game_Driver* parent_driver);

 void check_move_options(Game_Token* token, Game_Position* start_position,
   QVector<Move_Option>& move_options) Q_DECL_OVERRIDE;

//                         s2 minimum_legal_move = 5; // 2 steps ...
//                         s1 increment = 1; // stop at non-slot is possible

//                         // // check positions less than minimum move
//                          //   for tokens  that would block the move..
//                         s1 minimum_check = 2;

};

#endif // AU_GAME_VARIANT__H
