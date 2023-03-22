
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef GAME_VARIANT__H
#define GAME_VARIANT__H

#include "accessors.h"

#include "flags.h"

#include "global-types.h"

#include "game/game-token.h"
#include "game/game-position.h"

#include <QString>
#include <QQueue>

#include <QPair>

class Game_Driver;
class Game_Position;

class Game_Variant
{
public:

 struct Move_Option {
   Game_Position* position;
   s2 index; // //  negative index means capture
 };

private:

 QString name_;
 Game_Driver* parent_driver_;


protected:

 enum class Move_Option_Details {
  N_A, No_Captures, Allow_Captures, Look_for_Jump_Screen
 };

 Game_Token::Token_Kind get_underlying_token_kind(Game_Token* token)
 {
  return (Game_Token::Token_Kind) (token->kind() & Game_Token::Token_Kind::Clear_NS);
 }

 Game_Position* get_game_position_via_offset(Game_Position* starting, QPair<s2, s2> offsets);

 virtual Game_Position* check_move_option(Game_Token* token, Game_Position* start_position,
   QPair<s2, s2> offsets, Game_Position::Occupiers& os);

 virtual s2 check_move_option(Game_Token* token, Game_Position* start_position,
   QPair<s2, s2> offsets, Game_Position::Occupiers& os,
   QVector<Move_Option>& move_options, u2 index, Move_Option_Details details,
   Game_Token** blocking_token = nullptr, s2 minimum_legal_move = 0);

//   , u2 index,
//   Game_Token** indirect_blocking_token = nullptr, Game_Token** blocking_token = nullptr);

// virtual Game_Position* check_move_option(Game_Token* token, Game_Position* start_position,
//   QPair<s2, s2> offsets, s2& index,
//   Game_Token** indirect_blocking_token = nullptr, Game_Token** blocking_token = nullptr);

// virtual s2 check_move_option(Game_Token* token, Game_Position* start_position,
//   QPair<s2, s2> offsets, QVector<Move_Option>& move_options, u2 index,
//   Game_Token** indirect_blocking_token = nullptr, Game_Token** blocking_token = nullptr);

// virtual Game_Position* check_move_option(Game_Token* token, Game_Position* start_position,
//   QPair<s2, s2> offsets, s2& index,
//   Game_Token** indirect_blocking_token = nullptr, Game_Token** blocking_token = nullptr);

public:

 Game_Variant(QString name, Game_Driver* parent_driver);

 ACCESSORS(QString ,name)

 virtual void check_move_options(Game_Token* token, Game_Position* start_position,
   QVector<Move_Option>& move_options);

 virtual void check_dislodge(Game_Token* token, Game_Position* gp,
   QVector<Game_Position::Dislodge_Info>& affected_tokens);
 virtual void check_secondary_dislodge(Game_Position* prior_gp, Game_Token* token, Game_Position* gp,
   QVector<Game_Position::Dislodge_Info>& affected_tokens, u1 prior_direction);

};


#endif // GAME_VARIANT__H
