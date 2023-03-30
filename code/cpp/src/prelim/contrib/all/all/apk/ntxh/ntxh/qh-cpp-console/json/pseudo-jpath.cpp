
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "pseudo-jpath.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>


#include <QRegularExpression>
#include <QRegularExpressionMatchIterator>

#include "scoping-if.h"

#include "textio.h"

USING_KANS(RdSC)
USING_KANS(TextIO)

Pseudo_JPath::Pseudo_JPath(QJsonDocument document)
  :  document_(document)
{

}


//#define _if(arg) if(_scoped_bool_test arg)

QVariant Pseudo_JPath::evaluate(QString expression)
{
 static u1 alt_count = 0;

 // $ = 1  -> = 2  > = 3  w = 4  | = 5  : = 6   ;; = 7   ; = 8  ~ = 9

 expression.replace(".", "|0");

 static QStringList qsl {"\\$", "->", ">", "(?:\\w|-(?!>))+", "\\|", ":", ";;", ";", "~" };

 static QRegularExpression rx;

 if(!alt_count)
 {
  QString rx_string;
  alt_count = qsl.size();
  for(u1 i = 0; i < alt_count; ++i)
  {
   if(i)
     rx_string += "|";
   rx_string += "(%1)"_qt.arg(qsl[i]);
  }
  rx = QRegularExpression(rx_string);
 }

 //static QRegularExpression rx("(\\$)|(->)|(>)|((?:\\w|-(?!>))+)|(\\|)|(:)|(;;)|(;)|(~)");
 QRegularExpressionMatchIterator it = rx.globalMatch(expression);

// QVector<QPair<s4, QStringView>> components;
 QVector<QPair<QString, QPair<s4, s4>>> components;

// switch (i)
// {
//  case 1: break; // $
//  case 2: break; // :
// }

 u1 held_left = 0;
 u1 held_mid = 0;


 while(it.hasNext())
 {
  QRegularExpressionMatch match = it.next();
  //qDebug() << "\nglobal: " << match.captured();
  for(u1 i = 1; i <= alt_count; ++i)
  {
   QString sstr = match.captured(i);
   _if(<QString> str = match.captured(i))
   {
//    if(i == 1)
//      components.push_back({0, str});
     //?else if(i == )
    if(held_mid)
    {
     components.last().second = {held_left, i};
     held_mid = 0;
     held_left = i;
    }
    else
    {
     held_mid = i;
     components.push_back({str, {0, 0}});
    }
    break;
   }
  }
 }

 //QJsonDocument current_document = document_;
 QJsonValue current_value;

 // $ = 1  -> = 2  > = 3  w = 4  | = 5  : = 6  ;; = 7  ; = 8  ~ = 9

 auto _check_array_first_element = [&current_value](const QPair<QString, QPair<s4, s4>>& pr)
 {
  if(pr.second.second == 7 || pr.second.second == 2)
    current_value = current_value.toArray().first();

 };

 auto _object = [&current_value, _check_array_first_element](const QPair<QString, QPair<s4, s4>>& pr)
 {
  current_value = current_value.toObject().value(pr.first);
  _check_array_first_element(pr);
 };

 auto _array = [&current_value, _check_array_first_element](const QPair<QString, QPair<s4, s4>>& pr)
 {
  s4 index = pr.first.toInt();
  if(index < 0)
    index += current_value.toArray().size();
  current_value = current_value.toArray()[index];
  _check_array_first_element(pr);
 };


 for(const QPair<QString, QPair<s4, s4>>& pr : components)
 {
  //u1 pr_code = pr.second.first * 10 + pr.second.second;
  switch (pr.second.first)
  {
  case 0: // :
   {
    if(pr.second.second == 6)
      current_value = document_.object();
    else
      current_value = document_.array();
   }
   break;
  case 6: case 3: case 2://case 65: case 35: // >
   {
    if(!current_value.isObject())
      goto break_outer;
    _object(pr);
   }
   break;
  case 5: //7: case 53: case 55: // |
   {
    if(!current_value.isArray())
      goto break_outer;
    _array(pr);
   }
   break;
  default: break;
  }
 }

break_outer:

 return current_value.toVariant();

 //qDebug() << components;
}

