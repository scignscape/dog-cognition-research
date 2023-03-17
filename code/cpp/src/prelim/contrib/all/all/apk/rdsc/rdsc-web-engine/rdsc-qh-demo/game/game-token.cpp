
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "game-token.h"

#include "game-player.h"


Game_Token::Game_Token(Game_Player* player, Token_Kind kind)
  :  kind_(kind), player_(player), current_cluster_(nullptr),
     capture_status_(0), current_position_(nullptr)
{

}


bool Game_Token::south()
{
 return player_->play_order() == 1;
}

bool Game_Token::north()
{
 return player_->play_order() == 2;
}


