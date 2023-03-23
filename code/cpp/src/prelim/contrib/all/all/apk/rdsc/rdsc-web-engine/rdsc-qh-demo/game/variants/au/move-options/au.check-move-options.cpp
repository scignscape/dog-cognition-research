
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "../au-game-variant.h"

#include "game/game-position.h"

#include "global-macros.h"

void AU_Game_Variant::check_move_options_Generic(Direction_Codes dc,
   Game_Token* token,
   Game_Position* start_position, QVector<Move_Option>& move_options,
   s1 increment, s2 minimum_legal_move, s1 minimum_check)
{

 // // directions
  //     +-  . . .  ++       11  10 9 8  7
  //      .         .        12          6
  //      .         .        13          5
  //      .         .        14          4
  //     --  . . .  -+       15   0 1 2  3


// static u2 r_neg_c_neg_mask = 0b1000'0000'0000'0000;
// static u2 r_pos_c_neg_mask = 0b0000'1000'0000'0000;
// static u2 r_neg_c_pos_mask = 0b0000'0000'1000'0000;
// static u2 r_pos_c_pos_mask = 0b0000'0000'0000'1000;

 static std::array<u2, 16> block_init(d_mask)
   for(u1 i = 0; i < 16; ++i)
     _[i] = 1 << i;
   block_result


// static u2 r_neg_c_neg_mask = d_mask[15];
// static u2 r_pos_c_neg_mask = d_mask[11];
// static u2 r_pos_c_pos_mask = d_mask[7];
// static u2 r_neg_c_pos_mask = d_mask[3];

// static u2 d15_mask = 1 << 15;
// static u2 d11_mask = 1 << 11;
// static u2 d7_mask = 1 << 7;
// static u2 d3_mask = 1 << 3;


 static u2 r_neg_mask =  d_mask[0] | d_mask[1] | d_mask[2]
   | d_mask[3] | d_mask[15];

 static u2 r_pos_mask =  d_mask[7] | d_mask[8] | d_mask[9]
   | d_mask[10] | d_mask[11];

 static u2 c_neg_mask =  d_mask[15] | d_mask[14] | d_mask[13]
   | d_mask[12] | d_mask[11];

 static u2 c_pos_mask =  d_mask[3] | d_mask[4] | d_mask[5]
   | d_mask[6] | d_mask[7];


// static u2 c_neg_mask =  r_neg_c_neg_mask | r_pos_c_neg_mask;
// static u2 r_pos_mask =  r_pos_c_neg_mask | r_pos_c_pos_mask;
// static u2 c_pos_mask =  r_neg_c_pos_mask | r_pos_c_pos_mask;

 s2 r_neg_max =  1 - start_position->position_row();
 s2 c_neg_max =  1 - start_position->position_column();

 s2 r_pos_max = 31 - start_position->position_row();
 s2 c_pos_max = 31 - start_position->position_column();


 // // directions
  //     +-  . . .  ++       11  10 9 8  7
  //      .         .        12          6
  //      .         .        13          5
  //      .         .        14          4
  //     --  . . .  -+       15   0 1 2  3

 u2 block_init(directions)
   switch(dc)
   {
   case Direction_Codes::Diagonals:
     return d_mask[15] | d_mask[11] | d_mask[7] | d_mask[3];
   case Direction_Codes::Double_Vertical:
     return d_mask[10] | d_mask[8] | d_mask[2] | d_mask[0];
   case Direction_Codes::Double_Horizontal:
     return d_mask[14] | d_mask[12] | d_mask[6] | d_mask[4];
   default: _= 0;
   }
  block_result

 u2 count = 0;



#define clear_r_neg  directions &= ~r_neg_mask
#define clear_c_neg  directions &= ~c_neg_mask
#define clear_r_pos  directions &= ~r_pos_mask
#define clear_c_pos  directions &= ~c_pos_mask

//#define clear_r_neg_c_neg  directions &= ~r_neg_c_neg_mask
//#define clear_r_pos_c_neg  directions &= ~r_pos_c_neg_mask
//#define clear_r_pos_c_pos  directions &= ~r_pos_c_pos_mask
//#define clear_r_neg_c_pos  directions &= ~r_neg_c_pos_mask

#define clear_d(dir) directions &= ~d_mask[dir]
//  #define clear_r_neg_c_neg  directions &= ~r_neg_c_neg_mask
//  #define clear_r_pos_c_neg  directions &= ~r_pos_c_neg_mask
//  #define clear_r_pos_c_pos  directions &= ~r_pos_c_pos_mask
//  #define clear_r_neg_c_pos  directions &= ~r_neg_c_pos_mask

#define check_clear_r_neg_max  if(r_neg <= r_neg_max) clear_r_neg;
#define check_clear_c_neg_max  if(c_neg <= c_neg_max) clear_c_neg;
#define check_clear_r_pos_max  if(r_pos >= r_pos_max) clear_r_pos;
#define check_clear_c_pos_max  if(c_pos >= c_pos_max) clear_c_pos;

// s2 minimum_legal_move = 5; // 2 steps ...
// s1 increment = 1; // stop at non-slot is possible

// // // check positions less than minimum move
//  //   for tokens  that would block the move..
// s1 minimum_check = 2;


 s1 r_neg = -minimum_check;
 s1 r_pos = minimum_check;
 s1 c_neg = -minimum_check;
 s1 c_pos = minimum_check;

 check_clear_r_neg_max
 check_clear_c_neg_max
 check_clear_r_pos_max
 check_clear_c_pos_max

 auto offsets = [&] (u1 i) -> QPair<s2, s2>
 {
  switch (i)
  {
   // // Diagonals
  case 15: return {r_neg, c_neg};
  case 11: return {r_pos, c_neg};
  case 7: return {r_pos, c_pos};
  case 3: return {r_neg, c_pos};

   // // Double Vertical
  case 10: return {r_pos, -1};
  case 8: return {r_pos, 1};
  case 2: return {r_neg, 1};
  case 0: return {r_neg, -1};

   // // Double Horizontal
  case 14: return {-1, c_neg};
  case 12: return {1, c_neg};
  case 6: return {1, c_pos};
  case 4: return {-1, c_pos};

   // // Single Orthogonal
  case 13: return {0, c_neg};
  case 9: return {r_pos, 0};
  case 5: return {0, c_pos};
  case 1: return {r_neg, 0};

  default: return {0, 0};
  }
 };

 std::vector<u2> block_init(possible_directions)
   switch (dc)
   {
   case Direction_Codes::Diagonals: return {15, 11, 7, 3};
   case Direction_Codes::Double_Vertical: return {10, 8, 2, 0};
   case Direction_Codes::Double_Horizontal: return {14, 12, 6, 4};
   case Direction_Codes::Single_Orthogonal: return {13, 9, 5, 1};
   default: return {};
   }
   block_result


 Game_Token* blocking_token = nullptr;
 Game_Token* indirect_blocking_token = nullptr;

 while(directions)
 {
  Game_Position::Occupiers os;

//  for(u1 i = 0; i <= 15; ++i)
  for(u1 i : possible_directions)
  {
   if(directions & d_mask[i])
   {
    if(check_move_option(token, start_position, offsets(i), os, move_options,
        count + 1, Move_Option_Details::No_Captures, &blocking_token, minimum_legal_move))
      ++count;
    else if(blocking_token || indirect_blocking_token)
      clear_d(i); // clear_r_neg_c_neg;
   }
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









