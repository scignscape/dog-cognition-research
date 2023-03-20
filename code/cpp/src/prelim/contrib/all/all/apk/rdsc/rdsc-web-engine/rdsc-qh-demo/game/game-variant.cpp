
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "game-variant.h"

#include "game-position.h"

#include "game-driver.h"


Game_Variant::Game_Variant(QString name, Game_Driver* parent_driver)
  :  name_(name), parent_driver_(parent_driver)
{

}

void Game_Variant::check_move_options(Game_Token* token, Game_Position* start_position, QVector<Move_Option>& move_options)
{

}

Game_Position* Game_Variant::get_game_position_via_offset(Game_Position* starting, QPair<s2, s2> offsets)
{
 return parent_driver_->get_game_position_via_offset(starting, offsets);
}


s2 Game_Variant::check_move_option(Game_Token* token, Game_Position* start_position,
  QPair<s2, s2> offsets, QVector<Move_Option>& move_options, u2 index)
{
 s2 result = index;
 Game_Position* gp = check_move_option(token, start_position, offsets, result);
 if(gp)
 {
  move_options.push_back({gp, result});
 }
 return result;
}

Game_Position* Game_Variant::check_move_option(Game_Token* token, Game_Position* start_position,
  QPair<s2, s2> offsets, s2& index)
{
 Game_Position* gp = get_game_position_via_offset(start_position, offsets);
 if(gp)
 {
  if(gp->current_occupier())
    index = -index;

  // //  need also to check "dislodge" ...
  return gp;
 }
 return nullptr;
}



