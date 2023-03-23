
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef GAME_POSITION__H
#define GAME_POSITION__H

#include "accessors.h"

#include "flags.h"

#include "global-types.h"

#include "enum-macros.h"

//#include "magic-enum/include/magic_enum.hpp"

class Game_Token;
class Game_Board;

class Game_Position
{
public:

 flags_(1)
  bool is_non_slot:1;
  bool is_south_capture:1;
  bool is_north_capture:1;
  bool sw:1;
  bool se:1;
  bool nw:1;
  bool ne:1;
 _flags


 #define Position_Kind_Enumerate(labels) \
  labels(Slot, Intersection, Center, Side, Edge)

 #define enum_macro(x) ,x

 enum class Position_Kind {
  N_A
  Position_Kind_Enumerate(enum_macros)
   //  Slot, Intersection, Center,  Side, Edge
 };

 #undef enum_macro

//Position_Kind_Enumerate(_enum_macro)

 struct Occupiers {
   Game_Token* current_occupier;
   Game_Token* adjacent_occupier;
   u1 adjacent_occupier_index;
   bool blocks_direction(const QPair<s2, s2>& offsets);
   void reset() { current_occupier = nullptr;
     adjacent_occupier = nullptr; adjacent_occupier_index = 0;}
   bool all_clear() { return current_occupier == nullptr
     && adjacent_occupier == nullptr; }
 };

 struct Dislodge_Info {
   Game_Token* adjacent_occupier;
   Game_Position* new_position;
   s1 direction;
   operator bool()
   {
    return adjacent_occupier;
   }
 };

private:

 Game_Token* current_occupier_;

 Game_Position* adjacent_positions_[4];

 u1 position_row_;
 u1 position_column_;

 u1 board_row_;
 u1 board_column_;

 u2 svg_x_;
 u2 svg_y_;

 u1 board_area_number_;

 QString label_code_;

 Position_Kind position_kind_;


 void init();

public:

 Game_Position(u1 position_row, u1 position_column);
 Game_Position();

 ACCESSORS(u1 ,position_row)
 ACCESSORS(u1 ,position_column)

 ACCESSORS(u1 ,board_row)
 ACCESSORS(u1 ,board_column)

 ACCESSORS(u1 ,board_area_number)

 ACCESSORS(s2 ,svg_x)
 ACCESSORS(s2 ,svg_y)

 ACCESSORS(QString ,label_code)

 ACCESSORS(Position_Kind ,position_kind)
 ACCESSORS(Game_Token* ,current_occupier)

 void set_adjacent_positions(u1 index, Game_Position* gp)
 {
  adjacent_positions_[index] = gp;
 }


 Game_Position* get_adjacent_center_position();
 u2 distance(Game_Position* other);
 Game_Position* find_common_adjacent(Game_Position* other, Game_Position* exclude);

 std::array<Game_Position*, 4> get_half_step_adjacents();

 Occupiers occupiers();

 s1 get_dislodge_info(Game_Token*& adjacent_occupier, Game_Position*& adjacent_position);

 Dislodge_Info get_dislodge_info();
 Dislodge_Info get_secondary_dislodge_info(Game_Position* curl_position,
   Game_Position* prior_position, Game_Position* secondary_curl_position, s1 former_direction);

 QString summary();

 QString position_kind_string()
 {
  //std::string_view ee = magic_enum::enum_name(position_kind_);
  //return QString::fromStdString(ee);

  static QMap<Position_Kind, QString> static_map {
   #define enum_macro(x) {Position_Kind::x, #x},
   Position_Kind_Enumerate(enum_macros)
   #undef enum_macro
  };

  return static_map.value(position_kind_, "N_A");
 }

 static Game_Position& north_capture()
 {
  static Game_Position result;
  if(result.Flags == 0)
  {
   result.flags.is_north_capture = true;
  }
  return result;
 }

 static Game_Position& south_capture()
 {
  static Game_Position result;
  if(result.Flags == 0)
  {
   result.flags.is_south_capture = true;
  }
  return result;
 }



};



#endif // GAME_POSITION__H
