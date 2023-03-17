
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "token-group.h"

#include "game-token.h"


Token_Group::Token_Group()
  :  last_added_(nullptr), count_(0)
{

}

void Token_Group::add_token(Game_Token* token)
{
 tokens_[token] = -1;
}

void Token_Group::confirm_token(Game_Token* token)
{
 tokens_[token] = ++count_;
}

void Token_Group::add_and_confirm_token(Game_Token* token)
{
 tokens_[token] = ++count_;
}

void Token_Group::absorb(Token_Group* other)
{
 for(Game_Token* token : other->tokens_.keys())
 {
  add_and_confirm_token(token);
  token->set_current_cluster(this);
 }
}


