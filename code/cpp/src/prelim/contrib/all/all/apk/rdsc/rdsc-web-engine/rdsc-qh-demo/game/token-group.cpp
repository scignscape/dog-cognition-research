
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "token-group.h"

#include "game-token.h"

#include <set>


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

void Token_Group::update_densities()
{
 std::vector<u1> _densities(tokens_.keys().size());
 std::transform(tokens_.keys().begin(), tokens_.keys().end(), _densities.begin(),
   [](Game_Token* token)
  {
   return token->total_density();
  });

 std::set<u1> densities(_densities.begin(), _densities.end());

 if(densities.size() == 1)
 {
  for(Game_Token* token : tokens_.keys())
    token->set_as_ace();
 }
 else
 {
  u1 max_density = *std::max_element(densities.begin(), densities.end());
  u1 min_density = *std::min_element(densities.begin(), densities.end());

  for(Game_Token* token : tokens_.keys())
    token->qjk_from_densities(min_density, max_density);
 }
}

