
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef GAME_TOKEN__H
#define GAME_TOKEN__H

#include "accessors.h"

#include "flags.h"

#include <QString>

class Game_Token
{
public:

 enum class Token_Kind {
  N_A, South, South_Trap, North, North_Trap };

#undef enum_macro

private:
 Token_Kind kind_;

public:

 Game_Token(Token_Kind kind = Token_Kind::N_A);

 QString token_kind_string()
 {
  //std::string_view ee = magic_enum::enum_name(token_kind_);
  //return QString::fromStdString(ee);

  static QMap<Token_Kind, QString> static_map {
   {Token_Kind::South, "South"},
   {Token_Kind::South_Trap, "South (Trap)"},

   {Token_Kind::South, "North"},
   {Token_Kind::South_Trap, "North (Trap)"},
  };

  return static_map.value(kind_, "<error>");
 }




};



#endif // GAME_TOKEN__H
