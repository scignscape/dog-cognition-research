
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef TOKEN_GROUP__H
#define TOKEN_GROUP__H

#include "accessors.h"

#include "flags.h"

#include "global-types.h"


#include <QString>


class Game_Token;

class Token_Group
{
 QMap<Game_Token*, s1> tokens_;
 Game_Token* last_added_;
 u1 count_;

public:

 Token_Group();

 ACCESSORS__RGET(MACRO_PASTE(QMap<Game_Token*, s1>) ,tokens)

 ACCESSORS__GET(u1 ,count)

 u1 size()
 {
  return tokens_.size();
 }

 bool check_token_non_confirmed(Game_Token* token)
 {
  return (tokens_.value(token) == -1);
 }

 void add_token(Game_Token* token);
 void confirm_token(Game_Token* token);

 void add_and_confirm_token(Game_Token* token);

 void absorb(Token_Group* other);

 void update_densities();


};



#endif // GAME_TOKEN__H
