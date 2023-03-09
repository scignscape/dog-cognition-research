
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "gtagml-paralex-tile.h"

#include "kans.h"

#include <QDebug>

USING_KANS(GTagML)


GTagML_Paralex_Tile::GTagML_Paralex_Tile(QString raw_text, Kind k, u1 w)
 :  kind_(k), width_or_alt_(w), raw_text_(raw_text), 
    GTagML_htxn_node_(nullptr)
{
}


// QString GTagML_Paralex_Tile::get_accent_as_html()
// {
// return parse_accent_code_xml(command_ + " " + argument_);
// }

#ifdef HIDE
GTagML_Paralex_Tile::Kind GTagML_Paralex_Tile::check_kind(QString key)
{
 if(key.startsWith('&'))
 {
  switch(key[1].toLatin1())
  {
  case '-':
   command_ = key[2];
   argument_ = key.mid(4);
   return Accent_With_Argument;
  case ':':
   argument_ = key.mid(2);
   argument_.chop(1);
   return Character_Entity_Reference;
  case '#':
   argument_ = key.mid(2);
   argument_.chop(1);
   return Numeric_Character_Reference;
  }
 }
 return parse_kind(key);
}
#endif //def HIDE


KANS_(GTagML)

template<>
void GTagML_Paralex_Tile::to_string<
  GTagML_Paralex_Tile::Pipe_Escape>(QString& result)
{

}

template<>
void GTagML_Paralex_Tile::to_string<
  GTagML_Paralex_Tile::Alt_Interpretation>(QString& result)
{
 qDebug() << "WA: " << width_or_alt_;

 switch(width_or_alt_)
 {
 case 1:
  result = QString("`(%1)").arg(raw_text_);
  break;
 case 2:
   result = QString("`{%1}").arg(raw_text_);
   break;
 case 3:
   result = QString("`[%1]").arg(raw_text_);
   break;
 case 4:
   result = QString("`<%1>").arg(raw_text_);
   break;
 default:
   break;
 }
}
_KANS(GTagML)

u1 GTagML_Paralex_Tile::get_width()
{
 if(kind_ == Alt_Interpretation)
   return 1;
 return width_or_alt_;
}

QString GTagML_Paralex_Tile::thumbnail(int max_characters)
{
 QString result = to_string();
 if(result.size() > max_characters)
 {
  result = result.mid(0, max_characters - 3);
  result += "...";
 }
 return result;
}

QString GTagML_Paralex_Tile::to_string()
{
 qDebug() << "K: " << kind_;

 QString result;
 if(!command_.isEmpty())
 {
  //?
  return QString();
 }
 
 switch(kind_)
 {
 case Alt_Interpretation:
   to_string<Alt_Interpretation>(result);
   break;
 case Pipe_Escape:
   to_string<Pipe_Escape>(result);
   break;
 }

 return result;
}


