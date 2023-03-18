
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef GAME_DRIVER__H
#define GAME_DRIVER__H

#include "accessors.h"

#include "flags.h"

#include "game-board.h"

class Game_Token;
class Game_Player;

class Token_Group;

class Game_Driver
{
 Game_Board board_;

 QMap<QString, Game_Token*> tokens_by_svg_id_;
 QMap<u2, Game_Player*> players_by_player_order_;

 Game_Token* current_selected_token_;

 Game_Player* current_player_;
 Game_Player* south_player_;
 Game_Player* north_player_;

 enum class Game_States { N_A, Neutral, North_to_Move, North_to_Move_2_of_2,
    North_to_Place, South_to_Move, South_to_Move_2_of_2, South_to_Place };

 Game_States current_state_;

 void _place(Game_Token* token, Game_Position* gp);
 void _place(Game_Token* token, Token_Group* cluster);
 void _place_confirmed(Game_Token* token, Token_Group* cluster);

 struct _surrounding {
  QVector<Token_Group*> clusters;
 // QVector<Game_Token*> cluster_tokens;
  QVector<Game_Token*> singletons;
  QVector<Game_Token*> diagonal;
  QVector<Game_Token*> orthogonal;
 };

 u1 check_cluster(Game_Token* token, _surrounding& s);


public:

 Game_Driver();

 ACCESSORS__RGET(Game_Board ,board)

 void start_game(QH_Web_View_Dialog& dlg);

 void handle_token_clicked(QH_Web_View_Dialog& dlg, QString token_id);
 void handle_position_clicked(QH_Web_View_Dialog& dlg, QString position_id);
 void handle_token_placement(QH_Web_View_Dialog& dlg, Game_Token* token, QString pos_id);

 void register_token(QString key, Game_Token* token);
 Game_Token* register_new_token(u1 player_order, QString key);

 void check_prepare_token_placement(QH_Web_View_Dialog& dlg);
 void switch_current_player();

 void run_js_for_current_player(QH_Web_View_Dialog& dlg, QString js);
 void highlight_current_player_sidebar(QH_Web_View_Dialog& dlg);


 Token_Group* merge_token_groups(const QVector<Token_Group*>& clusters);
 Token_Group* merge_token_groups(const QVector<Token_Group*>& clusters, const QVector<Game_Token*>& tokens);
 void merge_tokens_into_group(Token_Group* cluster, const QVector<Game_Token*>& tokens);
 Token_Group* merge_tokens_into_new_group(const QVector<Game_Token*>& tokens);
};



#endif // GAME_DRIVER__H
