
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)




#include "game-player.h"


Game_Player::Game_Player(u2 play_order, u2 max_token_count_for_entry, u2 current_token_count_for_entry)
  :  play_order_(play_order), current_token_count_for_entry_(current_token_count_for_entry),
     max_token_count_for_entry_(max_token_count_for_entry), current_display_count_(0)
{

}





