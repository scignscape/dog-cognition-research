
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "au-game-variant.h"

#include "game/game-position.h"

#include "game/game-driver.h"

#include <QDebug>


AU_Game_Variant::AU_Game_Variant(QString name, Game_Driver* parent_driver)
  :  Game_Variant(name, parent_driver)
{

}


void AU_Game_Variant::check_move_options(Game_Token* token,
  Game_Position* start_position, QVector<Move_Option>& move_options)
{
 Game_Token::Token_Kind kind = get_underlying_token_kind(token);
 switch(kind)
 {
 case Game_Token::Token_Kind::Singleton:
  {
   switch(start_position->position_kind())
   {
   case Game_Position::Position_Kind::Center:
     check_move_options_Bishop(token, start_position, move_options); break;
   case Game_Position::Position_Kind::Intersection:
     check_move_options_Knight(token, start_position, move_options); break;
     //qDebug() << "knight"; break;
   case Game_Position::Position_Kind::Edge:
   case Game_Position::Position_Kind::Side:
     check_move_options_Rook(token, start_position, move_options); break;
   case Game_Position::Position_Kind::Slot:
     check_move_options_JQK(token, start_position, move_options); break;


    // qDebug() << "pawn"; break;
   default: break;
   }
   break;
  }
  break;

 case Game_Token::Token_Kind::Ace:
   qDebug() << "ace"; break;

 case Game_Token::Token_Kind::Queen:
   qDebug() << "queen"; break;

 case Game_Token::Token_Kind::Jack:
   qDebug() << "jack"; break;

 case Game_Token::Token_Kind::King:
   qDebug() << "king"; break;

 default: break;

 }



}






