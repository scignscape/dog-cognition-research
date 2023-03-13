
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef GAME_TOKEN__H
#define GAME_TOKEN__H

#include "accessors.h"

#include "flags.h"

#include "global-types.h"


#include <QString>

class Game_Token
{
public:

 enum class Token_Kind : u1 {
  N_A

#define enum_macro(x, y) ,x = y

  enum_macro(Singleton, 1)
  enum_macro(Paired, 2)
  enum_macro(Inner, 4)
  enum_macro(Buffer, 8)
  enum_macro(Outer, 16)
  enum_macro(Inner_Outer, Inner | Outer)
  enum_macro(South, 32)
  enum_macro(North, 64)

  enum_macro(South_Singleton, South | Singleton)
  enum_macro(South_Paired, South | Paired)
  enum_macro(South_Inner, South | Inner)
  enum_macro(South_Buffer, South | Buffer)
  enum_macro(South_Outer, South | Outer)
  enum_macro(South_Inner_Outer, South | Inner_Outer)

  enum_macro(North_Singleton, North | Singleton)
  enum_macro(North_Paired, North | Paired)
  enum_macro(North_Inner, North | Inner)
  enum_macro(North_Buffer, North | Buffer)
  enum_macro(North_Outer, North | Outer)
  enum_macro(North_Inner_Outer, North | Inner_Outer)

#undef enum_macro
 };

//  Singleton = 1, Paired = 2,  Inner = 4,
//    Buffer = 8, Outer = 16, Inner_Outer = Inner | Outer,

//  South = 32, North = 64,

//  South_Singleton = South | Singleton,
//  South_Paired = South | Paired,
//  South_Inner = South | Inner,
//  South_Buffer = South | Buffer,
//  South_Outer = South | Outer,
//  South_Inner_Outer = South | Inner_Outer,

//  North_Singleton = North | Singleton,
//  North_Paired = North | Paired,
//  North_Inner = North | Inner,
//  North_Buffer = North | Buffer,
//  North_Outer = North | Outer,
//  North_Inner_Outer = North | Inner_Outer,


private:
 Token_Kind kind_;

 u1 capture_rank_;
 u1 cluster_size_;

public:

 Game_Token(Token_Kind kind = Token_Kind::N_A);

 QString token_kind_string()
 {
  //std::string_view ee = magic_enum::enum_name(token_kind_);
  //return QString::fromStdString(ee);

  static QMap<Token_Kind, QString> static_map {
#define enum_macro(x, y)  {Token_Kind::x, #x},
   enum_macro(Singleton, 1)
   enum_macro(Paired, 2)
   enum_macro(Inner, 4)
   enum_macro(Buffer, 8)
   enum_macro(Outer, 16)
   enum_macro(Inner_Outer, Inner | Outer)
   enum_macro(South, 32)
   enum_macro(North, 64)

   enum_macro(South_Singleton, South | Singleton)
   enum_macro(South_Paired, South | Paired)
   enum_macro(South_Inner, South | Inner)
   enum_macro(South_Buffer, South | Buffer)
   enum_macro(South_Outer, South | Outer)
   enum_macro(South_Inner_Outer, South | Inner_Outer)

   enum_macro(North_Singleton, North | Singleton)
   enum_macro(North_Paired, North | Paired)
   enum_macro(North_Inner, North | Inner)
   enum_macro(North_Buffer, North | Buffer)
   enum_macro(North_Outer, North | Outer)
   enum_macro(North_Inner_Outer, North | Inner_Outer)
#undef enum_macro
  };

  return static_map.value(kind_, "<error>");
 }




};



#endif // GAME_TOKEN__H
