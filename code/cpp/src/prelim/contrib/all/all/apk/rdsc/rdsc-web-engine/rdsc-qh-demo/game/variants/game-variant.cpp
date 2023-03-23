
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "game-variant.h"

#include "game/game-position.h"

#include "game/game-driver.h"


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


void Game_Variant::check_dislodge(Game_Token* token, Game_Position* gp,
  QVector<Game_Position::Dislodge_Info>& affected_tokens)
{
 Game_Position::Dislodge_Info info = gp->get_dislodge_info();
 if(info)
 {
  affected_tokens.push_back(info);
  check_secondary_dislodge(info.adjacent_occupier->current_position(), info.adjacent_occupier, info.new_position, affected_tokens, info.direction);
 }
}

void Game_Variant::check_secondary_dislodge(Game_Position* prior_gp, Game_Token* token, Game_Position* gp,
  QVector<Game_Position::Dislodge_Info>& affected_tokens, u1 prior_direction)
{
 // //  note the gp here should always be a slot, so this always returns something ...
 Game_Position* center = gp->get_adjacent_center_position();

 Game_Position::Dislodge_Info info = gp->get_secondary_dislodge_info(prior_gp, prior_gp, center, prior_direction);
 if(info)
 {
  if(info.direction == -1)
  {
   affected_tokens.push_back(info);
   return;
  }
  u1 c = 3;
  while( (info.direction == -2) && (c--) )
  {
   affected_tokens.push_back(info);
   info = info.new_position->get_secondary_dislodge_info(nullptr, info.adjacent_occupier->current_position(), center, -2);
  }
 }
}

void Game_Variant::check_double_step_path(Game_Position* start_position,
  u1 path, Double_Step_Path_Details& details)
{
 // //  path codes:
  //    6 5 4
  //    7   3
  //    8 1 2

 u1 first_direction = path >> 4, second_direction = path & 15;

 details.first_position = parent_driver_->board().get_game_position_by_path_code(
   start_position, first_direction);

 if(details.first_position)
 {
  details.first_occupier = details.first_position->current_occupier();
  details.last_position = parent_driver_->board().get_game_position_by_path_code(
    details.first_position, second_direction);

  details.last_occupier = details.last_position->current_occupier();

  s1 dislodge_direction = details.last_position->get_dislodge_info(
    details.last_adj_occupier, details.last_adj_position);

  auto invert = [] (s1 d)
  {
   if (d < 0) return d;
   return (s1) ((4 - d) % 4);
  };
  // //  path codes:
   //    6 5 4            1 x 2
   //    7   3     <-     x   x
   //    8 1 2            0 x 3
   //      inverted ...
   //    6 5 4            3 x 0
   //    7   3     <-     x   x
   //    8 1 2            2 x 1


//  if( (8 - second_direction) / 2 == invert(dislodge_direction) )
  if( invert(dislodge_direction) * 2 + second_direction == 8)
  {
   details.intermediate_occupier = details.last_adj_occupier;
   details.intermediate_position = details.last_adj_position;
  }
  else
  {
   details.intermediate_occupier = nullptr;
   details.intermediate_position = nullptr;
  }
 }
 else
 {
  details.reset();
 }

}

s2 Game_Variant::check_move_option(Game_Token* token, Game_Position* start_position,
   QPair<s2, s2> offsets, Game_Position::Occupiers& os,
   QVector<Move_Option>& move_options, u2 index, Move_Option_Details details,
   Game_Token** blocking_token, s2 minimum_legal_move)
{
 if(blocking_token)
   *blocking_token = nullptr;
 s2 result = index;
 Game_Position* gp = check_move_option(token, start_position, offsets, os);

 if(os.current_occupier == token)
 {
  // //  normally this test might not be needed
   //    because minimum check would be set at 2
 }
 else if(os.current_occupier)
 {
  if(blocking_token)
    *blocking_token = os.current_occupier;

  if(details == Move_Option_Details::Allow_Captures)
    result = -index;
  else
    result = 0;
 }
 else if(os.adjacent_occupier)
 {
  if(blocking_token)
    *blocking_token = os.adjacent_occupier;

  if(gp->flags.is_non_slot)
  {
   if(os.blocks_direction(offsets))
     result = 0;
  }
 }

 if(result == index)
 {
  if(qMin(qAbs(offsets.first), qAbs(offsets.second)) < minimum_legal_move)
    result = 0;
 }

 if(result)
   move_options.push_back({gp, result});

 return result;
}

Game_Position* Game_Variant::check_move_option(Game_Token* token, Game_Position* start_position,
   QPair<s2, s2> offsets, Game_Position::Occupiers& os)
{
 Game_Position* gp = get_game_position_via_offset(start_position, offsets);
 if(gp)
   os = gp->occupiers();
 else
 {
  qDebug() << "missing gp ";
  os.reset();

 }

 return gp;
}


#ifdef HIDE
s2 Game_Variant::check_move_option(Game_Token* token, Game_Position* start_position,
  QPair<s2, s2> offsets, QVector<Move_Option>& move_options, u2 index,
  Game_Token** indirect_blocking_token, Game_Token** blocking_token)
{
 s2 result = index;
 Game_Position* gp = check_move_option(token, start_position, offsets, result, indirect_blocking_token, blocking_token);
 if(gp)
 {
  move_options.push_back({gp, result});
  return result;
 }
 return 0;
}

Game_Position* Game_Variant::check_move_option(Game_Token* token, Game_Position* start_position,
  QPair<s2, s2> offsets, s2& index, Game_Token** indirect_blocking_token, Game_Token** blocking_token)
{
 Game_Position* gp = get_game_position_via_offset(start_position, offsets);
 if(gp)
 {
  Game_Position::Occupiers os = gp->occupiers();
  if(os.current_occupier)
  {
   if(blocking_token)
   {
    *blocking_token = gp->current_occupier();
    return nullptr;
   }
   index = -index;
  }
  else if(os.adjacent_occupier)
  {
   if(gp->flags.is_non_slot)
   {
    if(os.blocks_direction(offsets))
    {
     *indirect_blocking_token = os.adjacent_occupier;
     return nullptr;
    }
   }
  }
  return gp;
 }
 return nullptr;
}

#endif
