
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "game-board.h"

#include "textio.h"
USING_KANS(TextIO)

#include "rdsc-2d/mat2d.templates.h"
#include "rdsc-1d/vec1d.h"


Game_Board::Game_Board()
  :  slot_positions_(16, 16, decltype(slot_positions_) ::Fixed_Preinit),
     non_slot_positions_(15, 15, decltype(slot_positions_) ::Fixed_Preinit)
{
 for(u1 r = 1, _r = 1; r <= 16; ++r, _r += 2)
  for(u1 c = 0, _c = 1; c < 16; ++c, _c += 2)
  {
   void* pv = slot_positions_.fetch_raw(r, c);
   Game_Position* gp = new (pv) Game_Position(_r, _c);
   game_positions_by_coords_[{_r, _c}] = gp;
   game_positions_by_label_code_[gp->label_code()] = gp;
  }

 for(u1 r = 1, _r = 2; r <= 15; ++r, _r += 2)
  for(u1 c = 1, _c = 2; c <= 15; ++c, _c += 2)
  {
   void* pv = non_slot_positions_.fetch_raw(r, c);
   Game_Position* gp = new (pv) Game_Position(_r, _c);
   game_positions_by_coords_[{_r, _c}] = gp;
   game_positions_by_label_code_[gp->label_code()] = gp;
  }

 // //  init the adjacents

 for(Game_Position* gp : game_positions_by_label_code_.values())
 {
  u1 r = gp->position_row();
  u1 c = gp->position_column();

  gp->set_adjacent_positions(0, game_positions_by_coords_.value({r-1, c-1}));
  gp->set_adjacent_positions(1, game_positions_by_coords_.value({r+1, c-1}));
  gp->set_adjacent_positions(2, game_positions_by_coords_.value({r+1, c+1}));
  gp->set_adjacent_positions(3, game_positions_by_coords_.value({r-1, c+1}));
 }

}

void Game_Board::debug_board(QString file)
{
 QString summary;

 for(auto [key, gp] : game_positions_by_label_code_.toStdMap())
 //for(Game_Position* gp : game_positions_by_label_code_.values())
 {
  if(key != gp->label_code())
    qDebug() << "Unexpected problem in label code";
  summary += "\n==== "_qt + gp->label_code() + "\n" + gp->summary() + "-----\n";
 }

 save_file(file, summary);

}

