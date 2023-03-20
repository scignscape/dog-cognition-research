
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "../au-game-variant.h"


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

 s1 r_neg = -1;
 s1 r_pos = 1;
 s1 c_neg = -1;
 s1 c_pos = 1;

 while(directions)
 {
  if(directions & r_neg_c_neg_mask)
  {
   if(check_move_option(token, start_position, {r_neg, c_neg}, move_options, count + 1))
     ++count;
  }
  if(directions & r_neg_c_pos_mask)
  {
   if(check_move_option(token, start_position, {r_neg, c_pos}, move_options, count + 1))
     ++count;
  }
  if(directions & r_pos_c_neg_mask)
  {
   if(check_move_option(token, start_position, {r_pos, c_neg}, move_options, count + 1))
     ++count;
  }
  if(directions & r_pos_c_pos_mask)
  {
   if(check_move_option(token, start_position, {r_pos, c_pos}, move_options, count + 1))
     ++count;
  }

  if(directions & r_neg_mask)
  {
   if(r_neg < 2)
     directions &= ~r_neg_mask;
   else
     r_neg -= 2;
  }
  if(directions & c_neg_mask)
  {
   if(c_neg < 2)
     directions &= ~c_neg_mask;
   else
     c_neg -= 2;
  }

  if(directions & r_pos_mask)
  {
   if(r_pos < 31)
     r_pos += 2;
   else
     directions &= ~r_pos_mask;
  }
  if(directions & c_pos_mask)
  {
   if(c_pos < 31)
     c_pos += 2;
   else
     directions &= ~c_pos_mask;
  }


 }

}







