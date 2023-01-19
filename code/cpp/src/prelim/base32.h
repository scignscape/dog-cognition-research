
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef BASE32__H
#define BASE32__H

#include <QFile>
#include <QTextStream>

//extern void base32_encode_qba(const QByteArray& qba, QString& result);
//extern void base32_decode_qstring(QString text, QByteArray& result);


#include "global-types.h"

#include <QRegularExpression>


//?KANS_(Base32)

//typedef quint64 u64;

static inline void base32_encode_qba(const QByteArray& qba, QString& result)
{
 int s = qba.size();

 int remainder = s % 5;
 if(remainder != 0)
 {
  remainder = 5 - remainder;
 }

 for(int i = 0; i < s; i += 5)
 {
  n8 val = 0;
  memcpy(&val, qba.data() + i, 5);
  result += QString("%1").arg(val, 8, 32, QChar('0')); //?QString::number(val, 32);
 }
 switch(remainder)
 {
 case 0: result += "w"; break;
 case 1: result += "x"; break;
 case 2: result += "y"; break;
 case 3: result += "z"; break;
 case 4: result += "_"; break;
 }
}

static inline void base32_decode_qstring(QString text, QByteArray& result)
{
 int index = text.indexOf(QRegularExpression("[_wxyz]"));
 if(index == -1)
 {
  return;
 }
 QStringRef str = text.midRef(0, index);
 QChar remainder_code = text.at(index);
 int s = str.size();
 for(int i = 0; i < s; i += 8)
 {
  QStringRef c = str.mid(i, 8);
  bool conversion_ok = false;
  n8 val = c.toULongLong(&conversion_ok, 32);
  QByteArray qba(5, 0);
  memcpy(qba.data(), &val, 5);
  result.append(qba);
 }
 int remainder;
 switch(remainder_code.toLatin1())
 {
 case 'w': remainder = 0; break;
 case 'x': remainder = 1; break;
 case 'y': remainder = 2; break;
 case 'z': remainder = 3; break;
 case '_': remainder = 4; break;
 default: remainder = 0; // error?
 }

 result.chop(remainder);

}

static inline void base32_decode_qstringref(QStringRef text, QByteArray& result)
{
 QRegularExpression rx("[_wxyz]");
 QRegularExpressionMatch rxm = rx.match(text); //text.indexOf(QRegularExpression("[_wxyz]"));
 if(!rxm.hasMatch())
 {
  return;
 }
 QStringRef str = text.mid(0, rxm.capturedStart());
 QChar remainder_code = text.at(rxm.capturedStart());
 int s = str.size();
 for(int i = 0; i < s; i += 8)
 {
  QStringRef c = str.mid(i, 8);
  bool conversion_ok = false;
  QByteArray conv = c.toLatin1();
  n8 val = conv.toULongLong(&conversion_ok, 32);
  QByteArray qba(5, 0);
  memcpy(qba.data(), &val, 5);
  result.append(qba);
 }
 int remainder;
 switch(remainder_code.toLatin1())
 {
 case 'w': remainder = 0; break;
 case 'x': remainder = 1; break;
 case 'y': remainder = 2; break;
 case 'z': remainder = 3; break;
 case '_': remainder = 4; break;
 default: remainder = 0; // error?
 }

 result.chop(remainder);

}


#endif

