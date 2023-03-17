
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "game-driver.h"

#include "game-token.h"

#include "game-player.h"

#include "token-group.h"

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


u1 Game_Driver::check_cluster(Game_Token* token, QVector<Token_Group*>& surrounding_clusters,
  QVector<Game_Token*>& surrounding_tokens)
{
 Game_Position* gp = token->current_position();

 QSet<Token_Group*> _surrounding_clusters;
 QSet<Game_Token*> _surrounding_tokens;


 for(s2 r = -2; r <= 2; r += 2)
 {
  for(s2 c = -2; c <= 2; c += 2)
  {
   if((r == 0) && (c == 0))
     continue;
   Game_Position* gp1 = board_.get_game_position_by_coords(gp->position_row() + r, gp->position_column() + c);
   if(Game_Token* token1 = gp1->current_occupier())
   {
    if(token1->player() == token->player())
    {
     if(token1->current_cluster())
       _surrounding_clusters.insert(token1->current_cluster());
     else
       _surrounding_tokens.insert(token1);
    }
   }
  }
 }

 u1 result = 0;
 // 1 = clusters
 // 2 = tokens
 // 3 - clusters and tokens

 if(!_surrounding_clusters.isEmpty())
 {
  surrounding_clusters = _surrounding_clusters.values().toVector();
  ++result;
 }

 if(!surrounding_tokens.isEmpty())
 {
  surrounding_tokens = _surrounding_tokens.values().toVector();
  result += 2;
 }

 return result;
}

void Game_Driver::_place(Game_Token* token, Game_Position* gp)
{
 token->set_current_position(gp);
 gp->set_current_occupier(token);
}

void Game_Driver::_place(Game_Token* token, Token_Group* cluster)
{
 token->set_current_cluster(cluster);
 cluster->add_token(token);
}

void Game_Driver::_place_confirmed(Game_Token* token, Token_Group* cluster)
{
 token->set_current_cluster(cluster);
 cluster->add_and_confirm_token(token);
}


Token_Group* Game_Driver::merge_token_groups(const QVector<Token_Group*>& clusters)
{
 Token_Group* result = new Token_Group;
 for(Token_Group* c : clusters)
 {
  result->absorb(c);
  delete c;
 }
 return result;
}


void Game_Driver::merge_tokens_into_group(Token_Group* cluster, const QVector<Game_Token*>& tokens)
{
 for(Game_Token* token : tokens)
 {
  cluster->add_and_confirm_token(token);
 }
}


Token_Group* Game_Driver::merge_tokens_into_new_group(const QVector<Game_Token*>& tokens)
{
 Token_Group* result = new Token_Group;
 merge_tokens_into_group(result, tokens);
 return result;
}



Token_Group* Game_Driver::merge_token_groups(const QVector<Token_Group*>& clusters, const QVector<Game_Token*>& tokens)
{
 Token_Group* result = merge_token_groups(clusters);
 merge_tokens_into_group(result, tokens);
 return result;
}


void Game_Driver::handle_token_placement(QH_Web_View_Dialog& dlg, Game_Token* token, QString pos_id)
{
 Game_Position* gp = board_.get_game_position_by_label_code(pos_id);

 if(gp)
 {
  // //  first check the placement is legal ...
  if(gp->position_kind() != Game_Position::Position_Kind::Slot)
  {
   // //  one issue is no non-slots ...
   return;
  }

  _place(token, gp);

  QVector<Token_Group*> surrounding_clusters;
  QVector<Game_Token*> surrounding_tokens;

  switch(check_cluster(token, surrounding_clusters, surrounding_tokens))
  {
  case 0: break; // // token will be singleton

  case 1: // // check merge ...
   if(surrounding_clusters.size() == 1)
   {
    _place(token, surrounding_clusters.first());
//    _place_confirmed(token, surrounding_clusters.first());
    break;
   }
   // //  otherwise need to merge ...
   {
    Token_Group* new_cluster = merge_token_groups(surrounding_clusters);
    _place(token, new_cluster);
    //    _place_confirmed(token, new_cluster);
    //

//    new_cluster->add_token(token);
//    token->set_current_cluster(new_cluster);
//     // // this is if placement ...
//    new_cluster->confirm_token(token);
   }
   break;

  case 2: // // only previous singletons ...
   {
    Token_Group* new_cluster = merge_tokens_into_new_group(surrounding_tokens);
    _place(token, new_cluster);
    //    _place_confirmed(token, new_cluster);
    //

//    new_cluster->add_token(token);
//    token->set_current_cluster(new_cluster);
//     // // this is if placement ...
//    new_cluster->confirm_token(token);
   }
   break;

  case 3: // // check merge ...
   if(surrounding_clusters.size() == 1)
   {
    merge_tokens_into_group(surrounding_clusters.first(), surrounding_tokens);
    _place(token, surrounding_clusters.first());
     // _place_confirmed(token, surrounding_clusters.first());

    break;
   }
   // //  otherwise need to merge ...
   {
    Token_Group* new_cluster = merge_token_groups(surrounding_clusters);
    merge_tokens_into_group(new_cluster, surrounding_tokens);
    _place(token, new_cluster);
    //    _place_confirmed(token, new_cluster);
    //
//    new_cluster->add_token(token);
//    token->set_current_cluster(new_cluster);
//     // // this is if placement ...
//    new_cluster->confirm_token(token);
   }
   break;


  default: break;
  }


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
