
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include <QDebug>

extern "C" {
void test_game()
{
 qDebug() << "Test ok!";
}

}


#include "game-token.h"

#include "game-player.h"

#include "token-group.h"


Game_Token::Game_Token(Game_Player* player, Token_Kind kind)
  :  kind_(kind), player_(player), current_cluster_(nullptr),
     capture_status_(0), current_position_(nullptr),
     move_option_count_(0), current_placement_order_(0),
     prior_position_(nullptr)
{

}

QString Game_Token::current_placement_order_label()
{
 static QString chars = "_sn";
 return "txt-%1%2"_qt.arg(chars[player_->play_order()]).arg(current_placement_order_);
}


void Game_Token::clear_neighbors()
{
 if(total_density() == 0)
   return; // nothing to do

 for(Game_Token* other : diagonal_neighbors_)
   other->clear_diagonal_neighbor(this);
 for(Game_Token* other : orthogonal_neighbors_)
   other->clear_orthogonal_neighbor(this);

 diagonal_neighbors_.clear();
 orthogonal_neighbors_.clear();
}

void Game_Token::hold_current_position()
{
 prior_position_ = current_position_;
}

bool Game_Token::check_hold_current_position()
{
 if(capture_status_ == -1)
 {
  hold_current_position();
  return true;
 }
 return false;
}


void Game_Token::update_neighbors(const QVector<Game_Token*>& d,
  const QVector<Game_Token*>& o)
{
 set_diagonal_neighbors(d);
 set_orthogonal_neighbors(o);
 for(Game_Token* other : d)
   other->update_diagonal_neighbor(this);
 for(Game_Token* other : o)
   other->update_orthogonal_neighbor(this);
}


u1 Game_Token::current_king_rank()
{
 if( (kind_ & Token_Kind::Clear_NS) == (u2) Token_Kind::King )
   return current_cluster_size() - total_density();

 return 0;
}


u1 Game_Token::current_cluster_size()
{
 if(current_cluster_)
   return current_cluster_->size();
 return 1;
}

QString Game_Token::current_cluster_status()
{
 if(current_cluster_)
 {
  if(current_cluster_->check_token_non_confirmed(this))
    return "just added (awaiting rebalance)";
  return "confirmed";
 }
 return "singleton";
}


bool Game_Token::south()
{
 return player_->play_order() == 1;
}

bool Game_Token::north()
{
 return player_->play_order() == 2;
}


