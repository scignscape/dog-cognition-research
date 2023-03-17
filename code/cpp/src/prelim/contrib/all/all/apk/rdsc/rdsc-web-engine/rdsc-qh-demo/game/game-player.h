
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef GAME_PLAYER__H
#define GAME_PLAYER__H

#include "accessors.h"

#include "flags.h"

#include "global-types.h"

#include <QString>
#include <QQueue>


class Game_Token;

class Game_Player
{
 QString name_;

 u2 play_order_;
 u2 current_token_count_for_entry_;
 u2 max_token_count_for_entry_;

 QQueue<Game_Token*> recycled_tokens_;

public:

 Game_Player(u2 play_order,
   u2 max_token_count_for_entry, u2 current_token_count_for_entry = 1);

 ACCESSORS(u2 ,play_order)

 ACCESSORS(u2 ,current_token_count_for_entry)
 ACCESSORS(u2 ,max_token_count_for_entry)

 void push_recycled_token(Game_Token* token)
 {
  recycled_tokens_.enqueue(token);
 }

 Game_Token* pull_recycled_token()
 {
  if(recycled_tokens_.isEmpty())
    return nullptr;
  return recycled_tokens_.dequeue();
 }

 void increment_entry_token_count()
 {
  if(current_token_count_for_entry_)
  {
   if(current_token_count_for_entry_ < max_token_count_for_entry_)
     ++current_token_count_for_entry_;
   else
     current_token_count_for_entry_ = 0;
  }
 }

 u2 get_remaining_entry_token_count()
 {
  if(current_token_count_for_entry_)
    return max_token_count_for_entry_ - current_token_count_for_entry_ + 1;
  return 0;
 }

};



#endif // GAME_PLAYER__H
