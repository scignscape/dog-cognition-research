
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "game-driver.h"

#include "game-token.h"

#include "game-player.h"


//#include "rdsc-qh/qh-web-view-dialog.h"


Game_Driver::Game_Driver()
  :  board_(this), current_selected_token_(0), current_player_(nullptr),
     south_player_(nullptr), north_player_(nullptr)
{
 south_player_ = new Game_Player(1, 30);
 north_player_ = new Game_Player(2, 30);

 players_by_player_order_[1] = south_player_;
 players_by_player_order_[2] = north_player_;
}



Game_Token* Game_Driver::register_new_token(u1 player_order, QString key)
{
 Game_Token* result = new Game_Token(players_by_player_order_.value(player_order));
 result->set_svg_id(key);
 register_token(key, result);
 return result;
}

void Game_Driver::register_token(QString key, Game_Token* token)
{
 tokens_by_svg_id_[key] = token;
}

void Game_Driver::start_game()
{
 current_state_ = Game_States::Neutral;
 current_player_ = south_player_;
 board_.set_next_token_number(-1);
}


void Game_Driver::check_prepare_token_placement()
{
 Game_Token* token = current_player_->pull_recycled_token();
 if(!token)
 {
  if(u2 c = current_player_->next_token_count())
  {
   static QString chars = "_sn";
   QString id = "token-%1%2"_qt.arg(chars[current_player_->play_order()]).arg(c);
   token = tokens_by_svg_id_.value(id);
  }
 }
 if(token)
 {
  current_selected_token_ = token;
 }
}

void Game_Driver::handle_token_clicked(QH_Web_View_Dialog* dlg, QString token_id)
{
 if(Game_Token* token = tokens_by_svg_id_.value(token_id))
 {
  qDebug() << "token: " << token->svg_id();

  Game_Player* player = token->player();
  if(player != current_player_)
  {
   // // maybe intending a capture ...
  }
  else
  {
   if(token->capture_status() == 0)
     check_prepare_token_placement();


  }

  //board_.handle_token_clicked(dlg, token);
 }

}

void Game_Driver::handle_position_clicked(QH_Web_View_Dialog* dlg, QString position_id)
{
 if(current_selected_token_)
 {
  board_.handle_token_placement(dlg, current_selected_token_, position_id);
  current_selected_token_ = nullptr;
 }

// if(Game_Token* token = tokens_by_svg_id_.value(token_id))
// {
//  qDebug() << "token: " << token->svg_id();
//  //board_.handle_token_clicked(dlg, token);
// }

}
