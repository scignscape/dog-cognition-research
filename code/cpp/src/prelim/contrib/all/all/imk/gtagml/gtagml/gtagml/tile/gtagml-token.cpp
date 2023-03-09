
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "gtagml-token.h"

#include "kans.h"
USING_KANS(GTagML)


GTagML_Token::GTagML_Token(QString raw_text)
 : Flags(0), raw_text_(raw_text)
{

}


QString GTagML_Token::thumbnail(int max_characters)
{
 QString result;
 if(flags.is_keyword)
 {
  result += ':';
  --max_characters;
 }
 if(flags.is_string_literal)
 {
  result += '"';
  max_characters -= 2;
 }
 if(raw_text_.size() > max_characters)
 {
  result += raw_text_.left(max_characters - 3) + "...";
 }
 else
 {
  result += raw_text_;
 }
 if(flags.is_string_literal)
 {
  result += '"';
 }
 return result;
}

QString GTagML_Token::to_string()
{
 QString result = raw_text_;
 if(flags.is_string_literal)
 {
  result.replace('"', "\\\"");
  result.prepend('"');
  result.append('"');
 }
 if(flags.is_keyword)
  result.prepend(':');
 return result;
}


