
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "../au-game-variant.h"

#include "game/game-position.h"


#include <QDebug>

// //  path codes:
 //    6 5 4
 //    7   3
 //    8 1 2


u1 operator ""_l(const char* arg)
{
 u1 result = strtoul(arg, nullptr, 16);
 if(result == 1)
   return (result << 4) | 8;
 return (result << 4) | (result - 1);
}

u1 operator ""_r(const char* arg)
{
 u1 result = strtoul(arg, nullptr, 16);
 if(result == 8)
   return (result << 4) | 1;
 return (result << 4) | (result + 1);
}

u1 operator ""_x(const char* arg)
{
 u1 result = strtoul(arg, nullptr, 16);
 return result;
}


#define ty2 std::array<u1, 2>
#define ty4 std::array<u1, 4>


template<typename OBJECT_Type, typename PATHS_Type>
void _check_move_options(OBJECT_Type* _this, PATHS_Type& paths, Game_Position* gp,
  QVector<typename OBJECT_Type::Move_Option>& move_options, u2& count)
{
 for(u1 path : paths)
 {
  Game_Variant::Double_Step_Path_Details details;
  _this->check_double_step_path(gp, path, details);
  if(details.intermediate_occupier)
    continue;
  if(details.last_occupier)
    continue;
  move_options.push_back({details.last_position, (s2) ++count, -2});
 }
}

void AU_Game_Variant::check_move_options_Knight_light_slot(Game_Position* gp,
  Move_Option_Vector& move_options, u2& count)
{
 // //  path codes:
  //    6 5 4
  //    7   3
  //    8 1 2
 #define ty (ty2)
 ty2 paths = gp->flags.ne? ty{8_l, 8_r}
   : gp->flags.se? ty{6_l, 6_r}
   : gp->flags.sw? ty{4_l, 4_r}
   : gp->flags.nw? ty{2_l, 2_r} : ty{0,0};
 #undef ty

 _check_move_options(this, paths, gp, move_options, count);
}


void AU_Game_Variant::check_move_options_Knight_dark_slot(Game_Position* gp,
  Move_Option_Vector& move_options, u2& count)
{
// static QVector<u1> paths;
// if(paths.isEmpty())
// {
//  paths.resize(4);
//  memcpy(paths.data(), gp->flags.sw? (u1[4]) {7_l, 7_r, 1_l, 1_r} :
//   (u1[4]) {0,0,0,0}, sizeof(*paths.data()));
// }

 // //  path codes:
  //    6 5 4
  //    7   3
  //    8 1 2
 #define ty (ty4)
 ty4 paths = gp->flags.ne? ty{7_l, 7_r, 1_l, 1_r} :
   gp->flags.se? ty{5_l, 5_r, 7_l, 7_r} :
   gp->flags.sw? ty{3_l, 3_r, 5_l, 5_r} :
   gp->flags.nw? ty{1_l, 1_r, 3_l, 3_r} : ty{0,0,0,0};
 #undef ty

 _check_move_options(this, paths, gp, move_options, count);

// for(u1 path : paths)
// {
//  Game_Variant::Double_Step_Path_Details details;
//  check_double_step_path(gp, path, details);
//  if(details.intermediate_occupier)
//    continue;
//  if(details.last_occupier)
//    continue;
//  move_options.push_back({details.last_position, (s2) ++count});
// }

}

//   : gp->flags.nw? QPair<u1, u1>{7_l, 1_r}
//   : gp->flags.ne? QPair<u1, u1>{4_l, 4_r}
//   : gp->flags.se? QPair<u1, u1>{2_l, 2_r} : QPair<u1, u1>{0,0} };

 // static QVector<u1> paths {0x}
 // #define modeq(x, y, m) ((x) % m) == ((y) % m)

void AU_Game_Variant::check_move_options_Knight(Game_Token* token,
  Game_Position* start_position, Move_Option_Vector& move_options)
{
 u2 count = 0;
 std::array<Game_Position*, 4> slot_positions = start_position->get_half_step_adjacents();
 for(Game_Position* gp : slot_positions)
 {
    // //  qDebug() << "gp = " << gp->label_code();
  if( (gp->board_row() % 2) == (gp->board_column() % 2) )
    check_move_options_Knight_dark_slot(gp, move_options, count);
  else
    check_move_options_Knight_light_slot(gp, move_options, count);
 }

 // // Move_Option_Sequence_Details: increment, first_increment, minimum_legal_move, first_check
  //   increment = 2 (no stop at non-slot)

 // //  now check for jump options
 check_move_options_Generic(Direction_Codes::Single_Orthogonal, token, start_position,
   move_options, {2, 2, 2, 2, 1, 0});
}







