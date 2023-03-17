
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "game-driver.h"

#include "game-token.h"

#include "game-player.h"


#include "rdsc-qh/qh-web-view-dialog.h"

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


void Game_Driver::highlight_current_player_sidebar(QH_Web_View_Dialog& dlg)
{
 run_js_for_current_player(dlg, "highlight_%1_sidebar()");
}


void Game_Driver::start_game(QH_Web_View_Dialog& dlg)
{
 current_state_ = Game_States::Neutral;
 current_player_ = south_player_;
 highlight_current_player_sidebar(dlg);

 //?board_.set_next_token_number(-1);
}


void Game_Driver::check_prepare_token_placement(QH_Web_View_Dialog& dlg)
{
 Game_Token* token = current_player_->pull_recycled_token();
 if(!token)
 {
  if(u2 c = current_player_->current_token_count_for_entry())
  {
   static QString chars = "_sn";
   QString id = "token-%1%2"_qt.arg(chars[current_player_->play_order()]).arg(c);
   token = tokens_by_svg_id_.value(id);
  }
 }
 if(token)
 {
  current_selected_token_ = token;
  run_js_for_current_player(dlg, "show_%1_adding_group()");
//    dlg->run_js_in_current_web_page("show_south_adding_group()");
//  else if(current_player_ == north_player_)
//    dlg->run_js_in_current_web_page("show_north_adding_group()");
 }
}


void Game_Driver::run_js_for_current_player(QH_Web_View_Dialog& dlg, QString js)
{
 if(current_player_ == south_player_)
   dlg.run_js_in_current_web_page(js.arg("south"));
 else if(current_player_ == north_player_)
   dlg.run_js_in_current_web_page(js.arg("north"));
}


void Game_Driver::handle_token_clicked(QH_Web_View_Dialog& dlg, QString token_id)
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
     check_prepare_token_placement(dlg);


  }

  //board_.handle_token_clicked(dlg, token);
 }

}

void Game_Driver::switch_current_player()
{
 if(current_player_ == south_player_)
   current_player_ = north_player_;
 else
   current_player_ = south_player_;
}

void Game_Driver::handle_token_placement(QH_Web_View_Dialog& dlg, Game_Token* token, QString pos_id)
{
 Game_Position* gp = board_.get_game_position_by_label_code(pos_id);

 if(gp)
 {
  // //  first check the placement is legal ...

  token->set_current_position(gp);
  token->set_capture_status(-1);

  QString token_id = token->svg_id();
  s2 token_mid_offset_x = 25, token_mid_offset_y = 25;
  s2 x = gp->svg_x() + token_mid_offset_x, y = gp->svg_y() + token_mid_offset_y;
  dlg.run_js_in_current_web_page("show_token_at_position('%1', %2, %3);"_qt.arg(token_id).arg(x).arg(y));

  current_player_->increment_entry_token_count();

  u2 remaining = current_player_->get_remaining_entry_token_count();
  run_js_for_current_player(dlg,
    "update_#1_entry_token_count(%1)"_qt.arg(remaining).replace('#', '%'));
 }
}


void Game_Driver::handle_position_clicked(QH_Web_View_Dialog& dlg, QString position_id)
{
 if(current_selected_token_)
 {
  handle_token_placement(dlg, current_selected_token_, position_id);

  current_selected_token_ = nullptr;
  run_js_for_current_player(dlg, "hide_%1_adding_group()");
  switch_current_player();
  highlight_current_player_sidebar(dlg);
 }

// if(Game_Token* token = tokens_by_svg_id_.value(token_id))
// {
//  qDebug() << "token: " << token->svg_id();
//  //board_.handle_token_clicked(dlg, token);
// }

}


////   u2 r = gp->position_row();
////   u2 c = gp->position_column();

////  s2 tn = next_token_number();
//  QString token_id = token->svg_id();
//  QString hide_group;
//  QString show_group;
//  if(token->south())
//  {
//   hide_group = "south-adding-text-group";
//   show_group = "north-adding-text-group";
//  }
//  else
//  {
//   hide_group = "north-adding-text-group";
//   show_group = "south-adding-text-group";
//  }

//  s2 token_mid_offset_x = 25, token_mid_offset_y = 25;

//  s2 x = gp->svg_x() + token_mid_offset_x, y = gp->svg_y() + token_mid_offset_y;

//  //c * 100, y = r * 100;
//  //runJavaScript("position_token('%1', %2, %3);"_qt.arg(id).arg(x).arg(y));

//  dlg->run_js_in_current_web_page("show_token_at_position('%1', %2, %3);"_qt.arg(token_id).arg(x).arg(y));

//  increment_next_token_number();
