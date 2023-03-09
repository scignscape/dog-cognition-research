

//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "gh-block-parse-mode.h"

GH_Block_Parse_Mode::GH_Block_Parse_Mode(u1 null_code)
 : hold_state_(0), length_with_hold_state_(0),
   null_code_(null_code), acc_length_(0)

{

}

QPair<u1, u1> GH_Block_Parse_Mode::get_diacritic_length(u1 cue)
{
 // // multi-character codes:
  //    + double elevated
  //    > double
  //    & triple
  //    \ external
  //   e.g.
  //     |:t (TM as one character)
  //     |+t (TM as two characters)
  //     |fl (fl ligature as one character)
  //     |Fl (ffl ligature as one character)
  //     |>fl. (fl ligature as two character)
  //     |&Fl.. (ffl ligature as three characters)

 switch (cue)
 {
 case '+': return {2, ':'};
 case '>': return {2, 0};
 case '&': return {3, 0};

 case '`':
 case '\'': // grave
 case  '^': // // circ
 case '"': // // uml
 case '~': // // tilde
 case '=': // // macr
 case '.': // // dot
 case 'u': // // breve
 case 'v': // // caron
 case 'H': // // dbl acute
 case 'b': // // bar-under
 case 'c': // // cedil
 case 'k': // // ogon
 case 'r': // // ring over ...
 case 'R': // // ring over (alt), e.g. aa instead of ra ...
 case 'K': // // stroke
 case 't': // // tie-after
 case '/': // // slash
 case 'm': // // midot
 case 'g': // // eng, kgreen, ital &  ...
 case 'G': // // eng, ital & with more space

 case 'h': // // eth, thorn, Thorn
 case 'z': // // eszat i.e. ss ...

 case 'e': // // ae, oe
 case 'E': // // AE, OE

 case 'f': // // fi, fj, fl, ff, FI, FJ, FL, FF

 case 'F': // // fi, ffj, ffl, FFI, FFJ, FFL

 case 'n': // // no ligature
 case 'N': // // no ligature
 case 'C': // // italic correction

 case '@': // // special circled
 case ')': // // circled
 case '%': // // circle left
 case 'o': // // circle ring
 case 'O': // // circle ring (larger)

 case '$': // // strike
 case '-': // // strike

 case 'D': // // dieresis
  return {1, cue};

 return {0, 0};
 }

}


void GH_Block_Parse_Mode::release_cancel_or_alt_char(QPair<u1, u1>& result)
{
 result = cancel_or_alt_chars_.dequeue();
}

n8 GH_Block_Parse_Mode::release_glyph_point()
{
 return ready_glyph_points_.dequeue();
}

u1 GH_Block_Parse_Mode::finalize_glyph_points_1(u1 cue)
{
 static QMap<QPair<u1, u1>, u1> static_map
 {{
   {{2, 'A'}, 192}, // // Capital a with grave accent
   {{3, 'A'}, 193}, // Capital a with acute accent
   {{4, 'A'}, 194}, // Capital a with circumflex accent
   {{5, 'A'}, 195}, // Capital a with tilde
   {{5, 'A'}, 196}, // Capital a with umlaut
   {{15, 'A'}, 197}, // Capital a with ring
   {{25, 'A'}, 198}, // Capital ae
   {{3, 'C'}, 199}, // Capital c with cedilla
   {{2, 'E'}, 200}, // Capital e with grave accent
   {{3, 'E'}, 201}, // Capital e with acute accent
   {{4, 'E'}, 202}, // Capital e with circumflex accent
   {{5, 'E'}, 203}, // Capital e with umlaut
   {{2, 'I'}, 204}, // Capital i with grave accent
   {{3, 'I'}, 205}, // Capital i with accute accent
   {{4, 'I'}, 206}, // Capital i with circumflex accent
   {{5, 'I'}, 207}, // Capital i with umlaut
   {{5, 'E'}, 208}, // Capital i with umlaut
     // {1, }, 208}, // Capital eth (Icelandic)
   {{6, 'N'}, 209}, // Capital n with tilde
   {{2, 'O'}, 210}, // Capital o with grave accent
   {{3, 'O'}, 211}, // Capital o with accute accent
   {{4, 'O'}, 212}, // Capital o with circumflex accent
   {{6, 'O'}, 213}, // Capital o with tilde
   {{5, 'O'}, 214}, // Capital o with umlaut
   {{19, 'O'}, 216}, // Capital o with slash
   {{2, 'U'}, 217}, // Capital u with grave accent
   {{3, 'U'}, 218}, // Capital u with acute accent
   {{4, 'U'}, 219}, // Capital u with circumflex accent
   {{5, 'U'}, 220}, // Capital u with umlaut
   {{3, 'Y'}, 221}, // Capital y with acute accent
   {{3, 'T'}, 222}, // Capital thorn (Icelandic)
   {{24, 's'}, 223}, // Lowercase sharp s (German) //?
   {{2, 'a'}, 224}, // Lowercase a with grave accent
   {{3, 'a'}, 225}, // Lowercase a with acute accent
   {{4, 'a'}, 226}, // Lowercase a with circumflex accent
   {{6, 'a'}, 227}, // Lowercase a with tilde
   {{5, 'a'}, 228}, // Lowercase a with umlaut
   {{15, 'a'}, 229}, // Lowercase a with ring
   {{25, 'a'}, 230}, // Lowercase ae
   {{3, 'c'}, 231}, // Lowercase c with cedilla
   {{2, 'e'}, 232}, // Lowercase e with grave accent
   {{3, 'e'}, 233}, // Lowercase e with acute accent
   {{4, 'e'}, 234}, // Lowercase e with circumflex accent
   {{5, 'e'}, 215}, // Lowercase e with umlaut
   {{2, 'i'}, 236}, // Lowercase i with grave accent
   {{3, 'i'}, 237}, // Lowercase i with acute accent
   {{4, 'i'}, 238}, // Lowercase i with circumflex accent
   {{5, 'i'}, 239}, // Lowercase i with umlaut
   {{5, 'h'}, 240}, // Lowercase i with umlaut
      //{1, "&eth}, //   //  { }, 240}, // Lowercase eth (Icelandic)
   {{6, 'n'}, 241}, // Lowercase n with tilde
   {{2, 'o'}, 242}, // Lowercase o with grave accent
   {{3, 'o'}, 243}, // Lowercase o with acute accent
   {{4, 'o'}, 244}, // Lowercase o with circumflex accent
   {{6, 'o'}, 245}, // Lowercase o with tilde
   {{5, 'o'}, 246}, // Lowercase o with umlaut
   {{19, 'o'}, 248}, // Lowercase o with slash
   {{2, 'u'}, 249}, // Lowercase u with grave accent
   {{3, 'u'}, 250}, // Lowercase u with acute accent
   {{4, 'u'}, 251}, // Lowercase u with circumflex accent
   {{5, 'u'}, 252}, // Lowercase u with umlaut
   {{3, 'y'}, 253}, // Lowercase y with acute accent
   {{3, 'h'}, 254}, // Lowercase thorn (Icelandic)
   {{5, 'y'}, 255}, //"&yuml}, //     // &#255; Lowercase y with umlaut

  }};

 ready_glyph_points_.enqueue(static_map.value({held_diacritic_code_, cue}, null_code_));
 return 1;
}

u1 GH_Block_Parse_Mode::finalize_glyph_points(u1 cue)
{
 if(held_diacritic_code_ < 100)
   return finalize_glyph_points_1(cue);

}

u1 GH_Block_Parse_Mode::check_hold(u1 cue)
{
 // returns
 //  0 = nothing special
 //  1 - 9 = length expected
 //  80 = possible special flag
 //  90 = special flag confirmed
 //  101-109 = holding cancel ...
 //  10 = waiting to see if alt ...
 //  200 = waiting to determine length
 //  201+ - holding glyph points to consume

// if(cue == '|')
// {
//  if(hold_state_ == 20)
//    hold_state_ = 0; // // || escape; no diacritic
//  // //  inside the offset_acc | is just a normal character
//  else if( (hold_state_ == 0) ) // && !(boundary_count > 1) )
//  {
//   hold_state_ = 20;
//   return 0;
//  }
// }


 switch(hold_state_)
 {
 case 0:
  if(cue == '^')
  {
   hold_state_ = 80;
   return 80;
  }
  if(cue == '|')
  {
   hold_state_ = 20;
   return 200;
  }
  if(cue == '`')
  {
   hold_state_ = 10;
   return 100;
  }
  return 0;
 case 1:
  if(cue == ')')
  {
   u1 result = acc_length_ + 100;
   acc_length_ = 0;
   hold_state_ = 0;
   return result;
  }
  cancel_or_alt_chars_.enqueue({1, cue});
  ++acc_length_;
  return 11;
 case 2:
  if(cue == '}')
  {
   u1 result = acc_length_ + 100;
   acc_length_ = 0;
   hold_state_ = 0;
   return result;
  }
  cancel_or_alt_chars_.enqueue({2, cue});
  ++acc_length_;
  return 21;
 case 3:
  if(cue == ']')
  {
   u1 result = acc_length_ + 100;
   acc_length_ = 0;
   hold_state_ = 0;
   return result;
  }
  cancel_or_alt_chars_.enqueue({3, cue});
  ++acc_length_;
  return 31;
 case 4:
  if(cue == '>')
  {
   u1 result = acc_length_ + 100;
   acc_length_ = 0;
   hold_state_ = 0;
   return result;
  }
  if(cue == '\'')
  {
   hold_state_ = 5;
   return 50;
  }
  if(cue == '\"')
  {
   hold_state_ = 6;
   return 60;
  }
  cancel_or_alt_chars_.enqueue({4, cue});
  ++acc_length_;
  return 41;
 case 5:
  if(cue == '>')
  {
   u1 result = acc_length_ + 100;
   acc_length_ = 0;
   hold_state_ = 0;
   return result;
  }
  cancel_or_alt_chars_.enqueue({5, cue});
  ++acc_length_;
  return 51;

 case 6:
  if(cue == '>')
  {
   u1 result = acc_length_ + 100;
   acc_length_ = 0;
   hold_state_ = 0;
   return result;
  }
  cancel_or_alt_chars_.enqueue({6, cue});
  ++acc_length_;
  return 61;

 case 10:
  if(cue == '(')
  {
   hold_state_ = 1;
   return 10;
  }
  if(cue == '{')
  {
   hold_state_ = 2;
   return 20;
  }
  if(cue == '[')
  {
   hold_state_ = 3;
   return 30;
  }
  if(cue == '<')
  {
   hold_state_ = 4;
   return 40;
  }
  cancel_or_alt_chars_.enqueue({0, '`'}); // maybe not 0?
  cancel_or_alt_chars_.enqueue({0, cue});
  return 102;

  // //  part of a diacritic ...

  //    20 -- diacritic start
  //    22-4 -- diacritic scope 2-4
  //    201 -- 0 of 1
  //    202 -- 0 of 2
  //    203 -- 0 of 3
  //    212 -- 1 of 2
  //    213 -- 1 of 3
  //    223 -- 2 of 3

 case 20:
  {
   QPair<u1, u1> pr = get_diacritic_length(cue); //_or_code(cue, dcode);
   if(pr.first == 1)
   {
    held_diacritic_code_ = get_diacritic_code(pr.second, 1);
    hold_state_ = 201;
   }
   else if(pr.first > 1)
   {
    if(pr.second > 0)
    {
     //diacritic_code = dcode;
     held_diacritic_code_ = get_diacritic_code(pr.second, pr.first);
     hold_state_ = 210 + pr.first;
    }
    else
    {
     hold_state_ = 20 + pr.first;
    }
   }
  }
  return 1; //  continue; // overall loop
 case 22:
  {
   held_diacritic_code_ = get_diacritic_code(cue, 2);
   hold_state_ = 202;
   return 0; // overall loop
  }
 case 23:
  {
   held_diacritic_code_ = get_diacritic_code(cue, 3);
   hold_state_ = 203;
   return 0; // overall loop
  }
 case 80:
  {
   if(cue == '%')
   {
    hold_state_ = 90;
    return 90;
   }
   hold_state_ = 0;
   return 89;
  }
 case 90:
  {
   u1 digit = cue - 48; // 1 - 9
   hold_state_ = 0;
   return 90 + digit;
  }
 case 201:
  {
   finalize_glyph_points(cue);
   hold_state_ = 0;
   return 201;
  }
  break;


// default:
//  {
//   code = get_diacritic_cue_code(cue);
//   code |= 64; // set dia bit ...
//   break;
//  }
 }
}

u1 GH_Block_Parse_Mode::get_diacritic_code(u1 cue, u1 length)
{
 u1 result = 0;
 switch(cue)
 {
 case '_': result = 1; break;
 case '`': result = 2; break;
 case '\'': result = 3; break;
 case '^': result = 4; break;
 case '"': result = 5; break;
 case '~': result = 6; break;
 case '=': result = 7; break;
 case '.': result = 8; break;
 case 'u': result = 9; break;

 case 'v': result = 10; break;
 case 'H': result = 11; break;
 case 'b': result = 12; break;
 case 'c': result = 13; break;
 case 'k': result = 14; break;
 case 'r': result = 15; break;
 case 'R': result = 16; break;
 case 'K': result = 17; break;
 case 't': result = 18; break;

 case '/': result = 19; break;
 case 'm': result = 20; break;
 case 'g': result = 21; break;
 case 'G': result = 22; break;
 case 'h': result = 23; break;
 case 'z': result = 24; break;
 case 'e': result = 25; break;
 case 'E': result = 26; break;
 case 'f': result = 27; break;

 case 'F': result = 28; break;
 case 'n': result = 29; break;
 case 'N': result = 30; break;
 case 'C': result = 31; break;
 case '@': result = 32; break;
 case ')': result = 33; break;
 case '%': result = 34; break;
 case 'o': result = 35; break;
 case 'O': result = 36; break;

 case '$': result = 37; break;
 case '-': result = 38; break;
 case 'D': result = 39; break;
 case '[': result = 40; break;
 case ']': result = 41; break;
 case '{': result = 42; break;
 case '}': result = 43; break;
 case ',': result = 44; break;
 case ';': result = 45; break;

 case ':': result = 46; break;
 case '<': result = 47; break;
 case '+': result = 48; break;
 case '>': result = 49; break;
 case '0': result = 50; break;
 case '1': result = 51; break;
 case '2': result = 52; break;
 case '3': result = 53; break;
 case '4': result = 54; break;

 case '5': result = 55; break;
 case '6': result = 56; break;
 case '7': result = 57; break;
 case '8': result = 58; break;
 case '9': result = 59; break;
 case '#': result = 60; break;
 case '*': result = 61; break;
 case 'V': result = 62; break;
 case '?': result = 63; break;
 default: break;
 }

 switch(length)
 {
 default:
 case 1: return result;
 case 2: return result + 64;
 case 3: return result + 128;
 case 4: return result + 192;
 }
}
