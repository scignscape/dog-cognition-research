
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "../au-game-variant.h"

#include "game/game-position.h"

void AU_Game_Variant::check_move_options_Bishop(Game_Token* token, Game_Position* start_position, QVector<Move_Option>& move_options)
{
 u1 directions = 0b1010'1010;
 u2 count = 0;

 static u1 r_neg_c_neg_mask = 0b1000'0000;
 static u1 r_pos_c_neg_mask = 0b0010'0000;
 static u1 r_neg_c_pos_mask = 0b0000'1000;
 static u1 r_pos_c_pos_mask = 0b0000'0010;

 static u2 r_neg_mask =  r_neg_c_neg_mask | r_neg_c_pos_mask;
 static u2 c_neg_mask =  r_neg_c_neg_mask | r_pos_c_neg_mask;

 static u2 r_pos_mask =  r_pos_c_neg_mask | r_pos_c_pos_mask;
 static u2 c_pos_mask =  r_neg_c_pos_mask | r_pos_c_pos_mask;

 s2 r_neg_max =  1 - start_position->position_row();
 s2 c_neg_max =  1 - start_position->position_column();

 s2 r_pos_max = 31 - start_position->position_row();
 s2 c_pos_max = 31 - start_position->position_column();


#define clear_r_neg_direction  directions &= ~r_neg_mask
#define clear_c_neg_direction  directions &= ~c_neg_mask
#define clear_r_pos_direction  directions &= ~r_pos_mask
#define clear_c_pos_direction  directions &= ~c_pos_mask

#define check_clear_r_neg_max  if(r_neg <= r_neg_max) clear_r_neg_direction;
#define check_clear_c_neg_max  if(c_neg <= c_neg_max) clear_c_neg_direction;
#define check_clear_r_pos_max  if(r_pos >= r_pos_max) clear_r_pos_direction;
#define check_clear_c_pos_max  if(c_pos >= c_pos_max) clear_c_pos_direction;

 s2 minimum_legal_move = 5; // 2 steps ...
 s1 increment = 1; // stop at non-slot is possible

 // // check positions less than minimum move
  //   for tokens  that would block the move..
 s1 minimum_check = 2;


 s1 r_neg = -minimum_check;
 s1 r_pos = minimum_check;
 s1 c_neg = -minimum_check;
 s1 c_pos = minimum_check;

 check_clear_r_neg_max
 check_clear_c_neg_max
 check_clear_r_pos_max
 check_clear_c_pos_max

 Game_Token* blocking_token = nullptr;
 Game_Token* indirect_blocking_token = nullptr;

 while(directions)
 {
  Game_Position::Occupiers os;
  if(directions & r_neg_c_neg_mask)
  {
   if(check_move_option(token, start_position, {r_neg, c_neg}, os, move_options,
       count + 1, Move_Option_Details::No_Captures, &blocking_token, minimum_legal_move))
     ++count;
   else if(blocking_token || indirect_blocking_token)
     clear_r_neg_direction;
  }
  if(directions & r_neg_c_pos_mask)
  {
   if(check_move_option(token, start_position, {r_neg, c_pos}, os, move_options,
       count + 1, Move_Option_Details::No_Captures, &blocking_token, minimum_legal_move))
     ++count;
   else if(blocking_token || indirect_blocking_token)
     clear_c_neg_direction;
  }
  if(directions & r_pos_c_neg_mask)
  {
   if(check_move_option(token, start_position, {r_pos, c_neg}, os, move_options,
       count + 1, Move_Option_Details::No_Captures, &blocking_token, minimum_legal_move))
     ++count;
   else if(blocking_token || indirect_blocking_token)
     clear_r_pos_direction;
  }
  if(directions & r_pos_c_pos_mask)
  {
   if(check_move_option(token, start_position, {r_pos, c_pos}, os, move_options,
       count + 1, Move_Option_Details::No_Captures, &blocking_token, minimum_legal_move))
     ++count;
   else if(blocking_token || indirect_blocking_token)
     clear_c_pos_direction;
  }


  if(directions & r_neg_mask)
  {
   check_clear_r_neg_max
   else r_neg -= increment;
  }
  if(directions & c_neg_mask)
  {
   check_clear_c_neg_max
   else c_neg -= increment;
  }

  if(directions & r_pos_mask)
  {
   check_clear_r_pos_max
   else r_pos += increment;
  }
  if(directions & c_pos_mask)
  {
   check_clear_c_pos_max
   else c_pos += increment;
  }


 }

}







