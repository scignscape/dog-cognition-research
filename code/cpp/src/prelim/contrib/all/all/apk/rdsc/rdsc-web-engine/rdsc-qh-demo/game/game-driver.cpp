
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "game-driver.h"

#include "game-token.h"

#include "game-player.h"

#include "token-group.h"

#include "rdsc-qh/qh-web-view-dialog.h"

#include "message-display-window.h"

//#include "rdsc-qh/qh-web-view-dialog.h"

#include <QMessageBox>

#include "game/variants/game-variant.h"
#include "variants/au/au-game-variant.h"

#include "global-macros.h"


Game_Driver::Game_Driver()
  :  board_(this), current_selected_token_(0), current_player_(nullptr),
     south_player_(nullptr), north_player_(nullptr),
     message_display_window_(nullptr),
     move_indicators_capture_count_(0),
     move_indicators_count_(0),
     current_indicator_status_(Indicator_Status::N_A)
{
 current_variant_ = new AU_Game_Variant("A/U", this);

 south_player_ = new Game_Player(1, 30);
 north_player_ = new Game_Player(2, 30);

 players_by_player_order_[1] = south_player_;
 players_by_player_order_[2] = north_player_;
}

void Game_Driver::display_message(QString msg, QH_Web_View_Dialog* dlg)
{
 if(message_display_window_)
   message_display_window_->add_message(msg);

 if(dlg)
 {
  run_js_for_current_player(*dlg,
    "update_#1_messages('\\n%1')"_qt.arg(msg).replace('#', '%'));
 }

}


Game_Token* Game_Driver::register_new_token(u1 player_order, QString key)
{
 Game_Token* result = new Game_Token(players_by_player_order_.value(player_order));
 result->set_svg_id(key);

 if(player_order == 1)
   result->set_as_south();
 else if(player_order == 2)
   result->set_as_north();

 register_token(key, result);
 return result;
}

void Game_Driver::register_token(QString key, Game_Token* token)
{
 tokens_by_svg_id_[key] = token;
}


void Game_Driver::highlight_current_player_sidebar(const QH_Web_View_Dialog& dlg)
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


void Game_Driver::check_prepare_token_placement(Game_Token* token, QH_Web_View_Dialog& dlg)
{
 current_selected_token_ = token;

 run_js_for_current_player(dlg, "show_%1_adding_group()");

 display_message("Adding token ...", &dlg);
}

Game_Token* Game_Driver::confirm_token_placement(QH_Web_View_Dialog& dlg)
{
 Game_Token* result = current_player_->pull_recycled_token();
 if(!result)
 {
  result = get_token_for_placement();
  current_player_->increment_entry_token_count();
  u2 remaining = current_player_->get_remaining_entry_token_count();
  run_js_for_current_player(dlg,
    "update_#1_entry_token_count(%1)"_qt.arg(remaining).replace('#', '%'));
 }

 u2 dc = current_player_->increment_current_display_count();
 result->set_current_placement_order(dc);
 return result;
}


void Game_Driver::run_js_code(const QH_Web_View_Dialog& dlg, QString js)
{
 dlg.run_js_in_current_web_page(js);
}


void Game_Driver::run_js_for_current_player(const QH_Web_View_Dialog& dlg, QString js)
{
 if(current_player_ == south_player_)
   run_js_code(dlg, js.arg("south"));
 else if(current_player_ == north_player_)
   run_js_code(dlg, js.arg("north"));
}


void Game_Driver::finalize_token_move(Game_Token* token, Move_Indicator* mi, QH_Web_View_Dialog& dlg)
{
 Game_Position* gp = mi->current_position;

 token->hold_current_position();
 handle_token_move_or_placement(dlg, token, gp);

 js_unhighlight_token(token, dlg);
 check_reset_move_indicators(dlg);

 finalize_token_move_or_placement(dlg, token, gp);

 switch_players(dlg);
}

void Game_Driver::handle_move_indicator_clicked(QH_Web_View_Dialog& dlg, QString id)
{
 // //  all ids start with "mi" ...
 u2 count = id.mid(2).toUInt();

 Move_Indicator* mi = move_indicators_.value(count - 1);

 if(!mi)
   //  //  something's wrong here ...
   return;

 finalize_token_move(current_selected_token_, mi, dlg);

}


void Game_Driver::handle_text_indicator_clicked(QH_Web_View_Dialog& dlg, QString token_id)
{
 if(Game_Token* token = tokens_by_text_indicator_.value(token_id))
 {
  handle_token_clicked(dlg, token);
 }
}

void Game_Driver::handle_token_clicked(QH_Web_View_Dialog& dlg, QString token_id)
{
 if(Game_Token* token = tokens_by_svg_id_.value(token_id))
 {
  handle_token_clicked(dlg, token);
 }
}

void Game_Driver::handle_token_clicked(QH_Web_View_Dialog& dlg, Game_Token* token)
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
    check_prepare_token_placement(token, dlg);
  else if(token->capture_status() == -1)
    prepare_move_option_indicators(token, dlg);
 }

  //board_.handle_token_clicked(dlg, token);

}


void Game_Driver::prepare_move_option_indicators(Game_Token* token, QH_Web_View_Dialog& dlg)
{
 if(current_selected_token_)
 {
  if(current_selected_token_->capture_status() == -1)
    js_unhighlight_token(current_selected_token_, dlg);

  if(token == current_selected_token_)
  {
   token->clear_move_option_counts();
   check_reset_move_indicators(dlg);
   current_selected_token_ = nullptr;
   return;
  }
  else
  {
   if(current_selected_token_->move_option_count() != 0)
   {
    if(current_selected_token_->move_option_count() == -1)
    {
     move_indicators_count_ = 0;
     move_indicators_capture_count_ = current_selected_token_->move_option_capture_count();
     if(move_indicators_capture_count_)
       js_hide_move_indicators(dlg);
    }
    else
    {
     move_indicators_count_ = current_selected_token_->move_option_count();
     move_indicators_capture_count_ = current_selected_token_->move_option_capture_count();
     js_hide_move_indicators(dlg);
    }
   }
   current_selected_token_->clear_move_option_counts();
  }

 }

 Game_Position* gp = token->current_position();
 if(!gp)
   return;

 current_selected_token_ = token;
 js_highlight_token(token, dlg);

 Game_Variant::Move_Option_Vector position_options;

 current_variant_->check_move_options(token, gp, position_options);

 u1 count = 0;
 u1 capture_count = 0;
 for(const Game_Variant::Move_Option& mo : position_options)
 {
  Move_Indicator* mi;
  if(mo.index < 0)
    mi = capture_move_indicators_.value(capture_count++);
  else
    mi = move_indicators_.value(count++);
  mi->current_position = mo.position;
 }

 token->set_move_option_count(count?count:-1);

 if(count | capture_count)
 {
  token->set_move_option_capture_count(capture_count);
  move_indicators_count_ = count;
  move_indicators_capture_count_ = capture_count;

  js_show_move_indicators(dlg);
 }

}

QString Game_Driver::current_player_string()
{
 if(current_player_ == south_player_)
   return "south";
 else if(current_player_ == north_player_)
   return "north";

 return {};
}

void Game_Driver::js_highlight_token(Game_Token* token, QH_Web_View_Dialog& dlg)
{
 QString js_code = "highlight_%1_token('%2');"_qt.arg(current_player_string()).arg(token->svg_id());

 run_js_code(dlg, js_code);
}

void Game_Driver::js_unhighlight_token(Game_Token* token, QH_Web_View_Dialog& dlg)
{
 QString js_code = "unhighlight_%1_token('%2');"_qt.arg(current_player_string()).arg(token->svg_id());

 run_js_code(dlg, js_code);
}


void Game_Driver::js_show_move_indicators(QH_Web_View_Dialog& dlg)
{
 QVector<QString> js_args(move_indicators_count_);
 QVector<QString> js_cargs(move_indicators_capture_count_);

 s2 token_mid_offset_x = 25, token_mid_offset_y = 25;

 auto fn = [token_mid_offset_x, token_mid_offset_y](Move_Indicator* mi) -> QString
 {
  return "['%1', %2, %3]"_qt.arg(mi->id)
    .arg(mi->current_position->svg_x() + token_mid_offset_x).arg(mi->current_position->svg_y() + token_mid_offset_y);
 };

 if(move_indicators_count_)
 {
  std::transform(move_indicators_.begin(), move_indicators_.begin() + move_indicators_count_,
    js_args.begin(), fn);

  QString js_code = "show_move_indicators([%1]);"_qt.arg(js_args.toList().join(','));

  run_js_code(dlg, js_code);
 }

 if(move_indicators_capture_count_)
 {
  std::transform(capture_move_indicators_.begin(), capture_move_indicators_.begin() + move_indicators_capture_count_,
    js_cargs.begin(), fn);

  QString js_ccode = "show_capture_move_indicators([%1]);"_qt.arg(js_cargs.toList().join(','));

 }


// qDebug() << "js_code = " << js_code;
// qDebug() << "js_ccode = " << js_ccode;

}


Game_Position* Game_Driver::get_game_position_via_offset(Game_Position* starting, QPair<s2, s2> offsets)
{
 s2 r = starting->position_row() + offsets.first;
 s2 c = starting->position_column() + offsets.second;

 Game_Position* gp = board_.get_game_position_by_coords(r, c);

 if(!gp)
   qDebug() << "missing gp ";

 return gp;
 //return board_.get_game_position_by_coords(r, c);
}


void Game_Driver::switch_current_player()
{
 if(current_player_ == south_player_)
   current_player_ = north_player_;
 else
   current_player_ = south_player_;
}


u1 Game_Driver::check_cluster(Game_Token* token, _surrounding& s)
{
 Game_Position* gp = token->current_position();

 QSet<Token_Group*> surrounding_clusters;
 QSet<Game_Token*> surrounding_singletons;


 for(s2 r = -2; r <= 2; r += 2)
 {
  for(s2 c = -2; c <= 2; c += 2)
  {
   if((r == 0) && (c == 0))
     continue;
   Game_Position* gp1 = board_.get_game_position_by_coords(gp->position_row() + r, gp->position_column() + c);
   unless(gp1) // //  could happen if we're at the edge of the board ...
     continue;
   if(Game_Token* token1 = gp1->current_occupier())
   {
    if(token1->player() == token->player())
    {
     if((r == 0) || (c == 0))
       s.orthogonal.push_back(token1);
     else
       s.diagonal.push_back(token1);
     if(token1->current_cluster())
       surrounding_clusters.insert(token1->current_cluster());
     else
       surrounding_singletons.insert(token1);
    }
   }
  }
 }

 u1 result = 0;
 // 1 = clusters
 // 2 = tokens
 // 3 - clusters and tokens

 if(!surrounding_clusters.isEmpty())
 {
  s.clusters = surrounding_clusters.values().toVector();
  ++result;
 }

 if(!surrounding_singletons.isEmpty())
 {
  s.singletons = surrounding_singletons.values().toVector();
  result += 2;
 }

 return result;
}

void Game_Driver::_place(Game_Token* token, Game_Position* gp)
{
 if(token->prior_position())
   token->prior_position()->set_current_occupier(nullptr);

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

void Game_Driver::check_token_chess_icon(Game_Token* token)
{
 Chess_Icon* icon = nullptr;


// if(gp->flags.is_non_slot)
// {
// }

 switch(token->kind())
 {
 case Game_Token::Token_Kind::North_Ace:
   icon = north_chess_icons_.value("ace-n%1"); break;
 case Game_Token::Token_Kind::North_Jack:
   icon = north_chess_icons_.value("jack-n%1"); break;
 case Game_Token::Token_Kind::North_Queen:
   icon = north_chess_icons_.value("queen-n%1"); break;
 case Game_Token::Token_Kind::North_King:
   icon = north_chess_icons_.value("king-n%1"); break;


 case Game_Token::Token_Kind::North_Singleton:
  {
   Game_Position* gp = token->current_position();
   switch(gp->position_kind())
   {
   case Game_Position::Position_Kind::Center:
    icon = north_chess_icons_.value("bishop-n%1"); break;
   case Game_Position::Position_Kind::Intersection:
    icon = north_chess_icons_.value("knight-n%1"); break;
   case Game_Position::Position_Kind::Side:
   case Game_Position::Position_Kind::Edge:
    icon = north_chess_icons_.value("rook-n%1"); break;
   case Game_Position::Position_Kind::Slot:
    icon = north_chess_icons_.value("pawn-n%1"); break;
   default: break;
   }
  }
  break;

 case Game_Token::Token_Kind::South_Ace:
   icon = south_chess_icons_.value("ace-n%1"); break;
 case Game_Token::Token_Kind::South_Jack:
   icon = south_chess_icons_.value("jack-n%1"); break;
 case Game_Token::Token_Kind::South_Queen:
   icon = south_chess_icons_.value("queen-n%1"); break;
 case Game_Token::Token_Kind::South_King:
   icon = south_chess_icons_.value("king-n%1"); break;


 case Game_Token::Token_Kind::South_Singleton:
  {
   Game_Position* gp = token->current_position();
   switch(gp->position_kind())
   {
   case Game_Position::Position_Kind::Center:
    icon = south_chess_icons_.value("bishop-s%1"); break;
   case Game_Position::Position_Kind::Intersection:
    icon = south_chess_icons_.value("knight-s%1"); break;
   case Game_Position::Position_Kind::Side:
   case Game_Position::Position_Kind::Edge:
    icon = south_chess_icons_.value("rook-s%1"); break;
   case Game_Position::Position_Kind::Slot:
    icon = south_chess_icons_.value("pawn-s%1"); break;
   default: break;
   }
  }
 default: break;
 }

 tokens_on_board_[token] = icon;

// if(icon)
// {
//  //QString tid = token->svg_id();
// }

}

Game_Token* Game_Driver::get_token_for_placement()
{
 if(u2 c = current_player_->current_token_count_for_entry())
 {
  static QString chars = "_sn";
  QString id = "token-%1%2"_qt.arg(chars[current_player_->play_order()]).arg(c);
  return tokens_by_svg_id_.value(id);
 }
 return nullptr;
}


Game_Token* Game_Driver::handle_non_slot_token_placement(QH_Web_View_Dialog& dlg, Game_Token* token, Game_Position* gp)
{
 Game_Token* result;
 if(token->check_hold_current_position())
   result = token;
 else
   result = confirm_token_placement(dlg);
 if(result)
 {
  _place(result, gp);

//  Game_Token::Token_Kind kind;
//  if(token->player() == north_player_)
//    kind = Game_Token::Token_Kind::North_Singleton;
//  else if(token->player() == south_player_)
//    kind = Game_Token::Token_Kind::South_Singleton;

  result->set_as_singleton();

//  check_token_chess_icon(token);

// //? dlg.run_js_in_current_web_page("show_chess_icon('%1','%2')"_qt.arg(mid).arg(tid));

//  show_token_at_position(dlg, token, gp);
 }

 return result;
}


void Game_Driver::finalize_token_move(QH_Web_View_Dialog& dlg, Game_Token* token, Game_Position* gp)
{
 check_token_chess_icon(token);
 show_token_at_position(dlg, token, gp);
}


void Game_Driver::finalize_token_move_or_placement(QH_Web_View_Dialog& dlg, Game_Token* token, Game_Position* gp)
{
 current_selected_token_ = nullptr;
 token->set_capture_status(-1);
 finalize_token_move(dlg, token, gp);
}


void Game_Driver::handle_token_move_or_placement(QH_Web_View_Dialog& dlg, Game_Token* token, Game_Position* gp)
{
 QVector<Game_Position::Dislodge_Info> dislodge_info;

 current_variant_->check_dislodge(token, gp, dislodge_info);

 _place(token, gp);

 update_token_move_or_placement(dlg, token, gp);

 if(!dislodge_info.isEmpty())
 {
  for(Game_Position::Dislodge_Info info : dislodge_info)
  {
   _place(info.adjacent_occupier, info.new_position);
   update_token_move_or_placement(dlg, info.adjacent_occupier, info.new_position);
   finalize_token_move(dlg, info.adjacent_occupier, info.new_position);
  }
 }
}

void Game_Driver::update_token_move_or_placement(QH_Web_View_Dialog& dlg, Game_Token* token, Game_Position* gp)
{
 _surrounding s;

 switch(check_cluster(token, s))
 {
 case 0: break; // // token will be singleton

 case 1: // // check merge ...
  if(s.clusters.size() == 1)
  {
   _place(token, s.clusters.first());
   break;
  }
  // //  otherwise need to merge ...
  {
   Token_Group* new_cluster = merge_token_groups(s.clusters);
   _place(token, new_cluster);
  }
  break;

 case 2: // // only previous singletons ...
  {
   Token_Group* new_cluster = merge_tokens_into_new_group(s.singletons);
   _place(token, new_cluster);
  }
  break;

 case 3:
  if(s.clusters.size() == 1)
  {
   merge_tokens_into_group(s.clusters.first(), s.singletons);
   _place(token, s.clusters.first());
   break;
  }
  // //  otherwise need to merge ...
  {
   Token_Group* new_cluster = merge_token_groups(s.clusters);
   merge_tokens_into_group(new_cluster, s.singletons);
   _place(token, new_cluster);
  }
  break;
 default: break;
 }

//   token->set_capture_status(-1);
 token->update_neighbors(s.diagonal, s.orthogonal);

 if(token->current_cluster())
   token->current_cluster()->update_densities();
 else
   token->set_as_pawn();

}


void Game_Driver::handle_token_placement(QH_Web_View_Dialog& dlg, Game_Token* token, QString pos_id)
{
 Game_Position* gp = board_.get_game_position_by_label_code(pos_id);

 if(token->player() != current_player_)
   // // clicked by mistake?
   return;


 Game_Token* placed_token = nullptr;

 if(gp)
 {
  // //  first check the placement is legal ...
  if(gp->position_kind() != Game_Position::Position_Kind::Slot)
  {
   // //  one issue is no non-slots ...
   placed_token = handle_non_slot_token_placement(dlg, token, gp);
  }
  else
  {
   if(token->check_hold_current_position())
     placed_token = token;
   else
     placed_token = confirm_token_placement(dlg);

   handle_token_move_or_placement(dlg, placed_token, gp);
  }

  if(placed_token)
  {
   finalize_token_move_or_placement(dlg, placed_token, gp);
  }
 }
}

void Game_Driver::show_token_at_position(QH_Web_View_Dialog& dlg, Game_Token* token, Game_Position* gp)
{
 QString token_id = token->svg_id();
 static s2 token_mid_offset_x = 25, token_mid_offset_y = 25;
 s2 x = gp->svg_x() + token_mid_offset_x, y = gp->svg_y() + token_mid_offset_y;
 dlg.run_js_in_current_web_page("show_token_at_position('%1', %2, %3);"_qt.arg(token_id).arg(x).arg(y));

 // //  the style sheet tries to center the text when seen in a browser;
  //    this adjusts it for the native front-end (is there a small
  //    discrepancy in the text placement between the two environments?)
 static s2 txt_offset_x = 2, txt_offset_y = -2;

 QString txt_id = token->current_placement_order_label();

 tokens_by_text_indicator_[txt_id] = token;

// QString js = "activate_text_indicator('%1', %2, %3);"_qt.arg(txt_id)
//   .arg(x + txt_offset_x).arg(y + txt_offset_y);

 dlg.run_js_in_current_web_page("activate_text_indicator('%1', %2, %3, %4);"_qt.arg(txt_id)
   .arg(x - txt_offset_x).arg(y - txt_offset_y)
   .arg(current_indicator_status_ == Indicator_Status::Text? "true" : "false"));

 show_chess_icon(dlg, token);
}


void Game_Driver::get_token_info(Game_Token* token)
{
 QMessageBox* mbox = new QMessageBox(QMessageBox::Information,
   "Token %1"_qt.arg(token->svg_id().mid("token-"_qt.size())),
   "Token at position %2                                                      \n"
   "Click \"details\" for all available data."_qt
     .arg(token->current_position()->label_code()));


 mbox->setDetailedText(R"(Kind: %1
Total Density: %2
Diagonal Rank: %3
Orthogonal Rank: %4
Cluster Size: %5
Cluster Status: %6
King Rank: %7)"_qt
 .arg(token->token_kind_string())
 .arg(token->total_density())
 .arg(token->diagonal_neighbors().size())
 .arg(token->orthogonal_neighbors().size())
 .arg(token->current_cluster_size())
 .arg(token->current_cluster_status())
 .arg(token->current_king_rank())
);

 mbox->show();

}


void Game_Driver::register_north_chess_icon(QString file_path, QString svg_id)
{
 north_chess_icons_[svg_id] = new Chess_Icon {file_path, svg_id};
}

void Game_Driver::register_south_chess_icon(QString file_path, QString svg_id)
{
 south_chess_icons_[svg_id] = new Chess_Icon {file_path, svg_id};
}

void Game_Driver::register_move_indicator(QString id)
{
 move_indicators_.push_back(new Move_Indicator {id, nullptr});
}

void Game_Driver::register_capture_move_indicator(QString id)
{
 capture_move_indicators_.push_back(new Move_Indicator {id, nullptr});
}


void Game_Driver::show_text_indicators(const QH_Web_View_Dialog& dlg)
{
 if(current_indicator_status_ == Indicator_Status::Chess_Icons)
   run_js_code(dlg, "hide_chess_icons()");

 current_indicator_status_ = Indicator_Status::Text;
 run_js_code(dlg, "show_text_indicators()");
}

void Game_Driver::hide_text_indicators(const QH_Web_View_Dialog& dlg)
{
 current_indicator_status_ = Indicator_Status::N_A;
 run_js_code(dlg, "hide_text_indicators()");
}


void Game_Driver::show_chess_icon(const QH_Web_View_Dialog& dlg,
  Game_Token* token)
{
 if(Game_Driver::Chess_Icon* icon = tokens_on_board_.value(token))
   show_chess_icon(dlg, token, icon);
}

void Game_Driver::show_chess_icon(const QH_Web_View_Dialog& dlg,
  Game_Token* token, Game_Driver::Chess_Icon* icon)
{
 QString tid = token->svg_id();
 QString id = tid.mid("token-_"_qt.size());

 id = icon->svg_id.arg(id);
 dlg.run_js_in_current_web_page("show_chess_icon('%1','%2', %3)"_qt
   .arg(id).arg(tid)
   .arg(current_indicator_status_ == Indicator_Status::Chess_Icons? "true" : "false"));

// qDebug() << "show_chess_icon('%1','%2')"_qt.arg(id).arg(tid);
}


void Game_Driver::hide_chess_icons(const QH_Web_View_Dialog& dlg)
{
 current_indicator_status_ = Indicator_Status::N_A;
 run_js_code(dlg, "hide_chess_icons()");
}


void Game_Driver::show_chess_icons(const QH_Web_View_Dialog& dlg)
{
 if(current_indicator_status_ == Indicator_Status::Text)
   run_js_code(dlg, "hide_text_indicators()");

 current_indicator_status_ = Indicator_Status::Chess_Icons;

 for(auto [token, icon] : tokens_on_board_.toStdMap())
 {
  if(icon)
  {
   show_chess_icon(dlg, token, icon);
  }
 }
 //QMapIterator<> it()
 // tokens_on_board_
 //tokens_on_board_
}


void Game_Driver::handle_position_context_menu(QH_Web_View_Dialog& dlg,  QString position_id, const QPoint& global_position)
{
 QMenu* menu = new QMenu;
 menu->addAction("Show Chess Icons", [this, &dlg]()
 {
  show_chess_icons(dlg);
 });

 menu->addAction("Hide Chess Icons", [this, &dlg]()
 {
  hide_chess_icons(dlg);
 });

 menu->addAction("Show Text Indicators", [this, &dlg]()
 {
  show_text_indicators(dlg);
 });

 menu->addAction("Hide Text Indicators", [this, &dlg]()
 {
  hide_text_indicators(dlg);
 });

 menu->addAction("Rewind (undo move)");
 menu->popup(global_position);

}

void Game_Driver::handle_token_context_menu(QH_Web_View_Dialog& dlg, QString token_id, const QPoint& global_position)
{
 QMenu* menu = new QMenu;
 menu->addAction("Get Token Info", [this, token_id]()
 {
  if(Game_Token* token = tokens_by_svg_id_.value(token_id))
    get_token_info(token);
 });
 menu->addAction("Rewind (undo move)");
 menu->popup(global_position);
}


void Game_Driver::js_hide_move_indicators(QH_Web_View_Dialog& dlg)
{
 run_js_code(dlg, "hide_move_indicators()");
}


void Game_Driver::check_reset_move_indicators(QH_Web_View_Dialog& dlg)
{
 if(move_indicators_count_ | move_indicators_capture_count_)
 {
  move_indicators_count_ = move_indicators_capture_count_ = 0;
  js_hide_move_indicators(dlg);
 }
}


void Game_Driver::switch_players(QH_Web_View_Dialog& dlg)
{
 check_reset_move_indicators(dlg);

 run_js_for_current_player(dlg, "hide_%1_adding_group()");
 switch_current_player();
 highlight_current_player_sidebar(dlg);
}


void Game_Driver::handle_position_clicked(QH_Web_View_Dialog& dlg, QString position_id)
{
 // //  this is for placement ... and for move?
 if(current_selected_token_)
 {
  handle_token_placement(dlg, current_selected_token_, position_id);

  current_selected_token_ = nullptr;
  switch_players(dlg);
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
