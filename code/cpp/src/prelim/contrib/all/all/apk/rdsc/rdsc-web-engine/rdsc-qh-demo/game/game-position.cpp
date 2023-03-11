
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "game-position.h"

#include "game-token.h"


Game_Position::Game_Position(u1 position_row, u1 position_column)
  :  position_row_(position_row), position_column_(position_column),
     board_row_(0), board_column_(0), board_area_number_(0),
     position_kind_(Position_Kind::N_A)
{
 init();
}


Game_Position::Game_Position()
  : position_row_(0), position_column_(0),
     board_row_(0), board_column_(0), board_area_number_(0),
     position_kind_(Position_Kind::N_A)
{

}

void Game_Position::init()
{
// u1 combined_switch = (position_row_ % 4) * 10 + position_column_;
// if(position_row_ % 4)
// {
//  if(position_column_ % )
// }

 static QMap<QPair<u1, u1>, QPair<Position_Kind, u1>> static_map {

  {{0, 0}, {Position_Kind::Intersection, 0}},
  {{0, 2}, {Position_Kind::Edge, 0}},
  {{2, 0}, {Position_Kind::Side, 0}},
  {{2, 2}, {Position_Kind::Center, 0}},

  {{1, 1}, {Position_Kind::Slot, 1}},
  {{1, 3}, {Position_Kind::Slot, 2}},
  {{3, 1}, {Position_Kind::Slot, 3}},
  {{3, 3}, {Position_Kind::Slot, 4}},
 };

 auto pr = static_map.value({position_row_ % 4, position_column_ % 4},
   {Position_Kind::N_A, 0});

 if(pr.first == Position_Kind::N_A) // // an invalid pair; should not occur
   return;

 position_kind_ = pr.first;

 QString slot_code;

 switch (pr.second)
 {
 case 0: flags.is_non_slot = true; break;
 case 1: flags.sw = true; slot_code = "sw"; break;
 case 2: flags.se = true; slot_code = "se"; break;
 case 3: flags.nw = true; slot_code = "nw"; break;
 case 4: flags.ne = true; slot_code = "ne"; break;
 default: break; // // should not occur
 }

 u1 r_4 = position_row_ / 4 + 1;
 u1 c_4 = position_column_ / 4 + 1;

 u1 r_a = r_4 < 4? 1: r_4 < 6? 4: 7;
 u1 c_a = c_4 < 4? 0: c_4 < 6? 1: 2;

 static QString column_labels_code = "_abcdefgh"_qt;

 QString base_position_code;

 QString extra_square_code;

 s1 board_row_offset = 0;

 switch(position_kind_)
 {
 case Position_Kind::Center:
  slot_code = "c";
  [[fallthrough]];
 case Position_Kind::Slot:
  board_row_ = r_4;
  board_column_ = c_4;
  base_position_code = column_labels_code.mid(c_4, 1);
  board_area_number_ = r_a + c_a;
  break;

 case Position_Kind::Side:
  board_row_ = r_4;
  board_column_ = 100 + (c_4 - 1) * 10 + c_4;
  base_position_code = column_labels_code.mid(c_4 - 1, 1);
  extra_square_code = column_labels_code.mid(c_4, 1) + QString::number(board_row_);
  break;

 case Position_Kind::Edge:
  board_row_offset = -1;
  board_row_ = 100 + (r_4 - 1) * 10 + r_4;
  board_column_ = c_4;
  base_position_code = column_labels_code.mid(c_4, 1);
  extra_square_code = base_position_code + QString::number(r_4);
  break;

 case Position_Kind::Intersection:
  board_row_offset = -1;
  board_row_ = 100 + (r_4 - 1) * 10 + r_4;
  board_column_ = 100 + (c_4 - 1) * 10 + c_4;
  base_position_code = column_labels_code.mid(c_4 - 1, 1);
  extra_square_code = column_labels_code.mid(c_4, 1) + QString::number(r_4);
  break;
 }

 label_code_ = "%1%2%3%4"_qt.arg(base_position_code)
   .arg(r_4 + board_row_offset).arg(slot_code).arg(extra_square_code);

}


QString Game_Position::summary()
{
 QVector<QString> adj(4);
 std::transform(adjacent_positions_, adjacent_positions_ + 4, adj.begin(), [](Game_Position* gp)
 {
  if(gp)
    return gp->label_code();
  return "<none>"_qt;
 });

 QString occupied;
 if(current_occupier_)
   occupied = current_occupier_->token_kind_string();
 else
  occupied = "<empty>";


 return R"(Label Code: %1,
Position: %2, %3,
Board: %4, %5,
Area: %6,
Kind: %7
Adjacent: %8
Ocuupied: %9
)"_qt.arg(label_code_).arg(position_row_).arg(position_column_)
  .arg(board_row_).arg(board_column_).arg(board_area_number_)
  .arg(position_kind_string()).arg(adj.toList().join(", "))
  .arg(occupied);
}



