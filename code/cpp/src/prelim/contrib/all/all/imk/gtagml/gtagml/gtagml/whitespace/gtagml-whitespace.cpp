
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "gtagml-whitespace.h"

#include <QDebug>

//?#include <bitset>

#include "global-types.h"

#include "kans.h"

USING_KANS(GTagML)


GTagML_Whitespace::GTagML_Whitespace()
 : raw_text_(nullptr)
{

}


GTagML_Whitespace::GTagML_Whitespace(QString raw_text)
{
 parse(raw_text);
}

void GTagML_Whitespace::set_left_code(Left_Right_Codes c)
{
 set_lr_code(c, 2);
}

void GTagML_Whitespace::set_right_code(Left_Right_Codes c)
{
 set_lr_code(c, 5);
}

void GTagML_Whitespace::set_lr_code(Left_Right_Codes c, u1 shift)
{
 if(raw_text_)
 {
  if(raw_text_.is_fixnum())
  {
   u1 code = (u1) c;
   code <<= shift;
   raw_text_ |= code;
  }
 }
}


GTagML_Whitespace::Left_Right_Codes GTagML_Whitespace::get_left_code()
{
 if(raw_text_)
 {
  if(raw_text_.is_fixnum())
  {
   size_t v = raw_text_.get_fixnum();
   return (Left_Right_Codes) (v | 7);
  }
 }
}

GTagML_Whitespace::Left_Right_Codes GTagML_Whitespace::get_right_code()
{
 if(raw_text_)
 {
  if(raw_text_.is_fixnum())
  {
   size_t v = raw_text_.get_fixnum();
   v >>= 3;
   return (Left_Right_Codes) (v | 7);
  }
 }
}


void GTagML_Whitespace::get_counts(u1* result)
{
 result[0] = 0;
 result[1] = 0;

 if(raw_text_)
 {
  if(raw_text_.is_fixnum())
  {
   size_t v = raw_text_.get_fixnum();

   // // discard codes
   v >>= 6;

   while(v > 0)
   {
    u1 encode = v & 7;
    Space_Codes sc = (Space_Codes) encode;
    switch(sc)
    {
    case Space_Codes::N_A:
    case Space_Codes::Tab:
    case Space_Codes::CR:
    case Space_Codes::Other:
     result[0] = 255;
     result[1] = 255;
     return;
    case Space_Codes::Line:
     ++result[0];
     break;
    case Space_Codes::Space:
     ++result[1];
     break;
    case Space_Codes::Comment:
    case Space_Codes::Comment_Pad:
     break;
    }
    v >>= 3;
   }
  }
 }
}

void GTagML_Whitespace::get_counts_as_inherited(u1* result)
{
  // //  offset into the array ...
 get_counts(result + 2);
}


u1 GTagML_Whitespace::get_length()
{
 int result = 0;
 if(raw_text_)
 {
  #ifdef NO_CAON
  result = raw_text_->size();
  #else //NO_CAON
  if(raw_text_.is_fixnum())
  {
   size_t v = raw_text_.get_fixnum();

   // // discard codes
   v >>= 6;

   while(v > 0)
   {
    u1 encode = v & 7;
    if(encode > 0)
      ++result;
    v >>= 3;
   }
   return (u1) result;
  }
  else
   result = raw_text_->size();
  #endif //NO_CAON
  return (u1) qMin<int>(result, 255);
 }
 return 0;
}


QString GTagML_Whitespace::to_string()
{
 if(raw_text_)
 {
  #ifdef NO_CAON
  return *raw_text_;
  #else //NO_CAON
  if(raw_text_.is_fixnum())
  {
   size_t v = raw_text_.get_fixnum();

   // // discard codes
   v >>= 6;

   QString result;

   while(v > 0)
   {
    u1 encode = v & 7;
    Space_Codes sc = (Space_Codes) encode;
    switch(sc)
    {
    case Space_Codes::CR:
     result += '\r'; break;

    case Space_Codes::Space:
     result += ' '; break;

    case Space_Codes::Tab:
     result += '\t'; break;

    case Space_Codes::Line:
     result += '\n'; break;

    default: break;
    }
    v >>= 3;
   }
   return result;
  }
  else
   return *raw_text_;
  #endif //NO_CAON
 }
 return QString();
}

//is_fixnum()

void GTagML_Whitespace::parse(QString raw_text)
{
 size_t code = 0;
 int size = raw_text.size();
 if(size > 8)
 {
  raw_text_ = caon_ptr<QString>( new QString(raw_text) );
  return;
 }
 for(int i = 0; i < size; ++i)
 {
  QChar qc = raw_text[i];

  Space_Codes sc = Space_Codes::N_A;

  switch(qc.toLatin1())
  {
  case ' ': sc = Space_Codes::Space; break;
  case '\n': sc = Space_Codes::Line; break;
  case '\t': sc = Space_Codes::Tab; break;
  case '\r': sc = Space_Codes::CR; break;
  default:
   raw_text_ = caon_ptr<QString>( new QString(raw_text) );
   return;
  }

  size_t encode = (size_t) sc;

  encode <<= (6 + (i*3));
  code |= encode;
 }
 #ifdef NO_CAON
 #else //NO_CAON
 raw_text_.set_fixnum(code);
 #endif //NO_CAON
}
