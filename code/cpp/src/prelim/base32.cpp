
////           Copyright Nathaniel Christen 2019.
////  Distributed under the Boost Software License, Version 1.0.
////     (See accompanying file LICENSE_1_0.txt or copy at
////           http://www.boost.org/LICENSE_1_0.txt)

//#include "base32.h"

//#include "global-types.h"

//#include <QRegularExpression>


////?KANS_(Base32)

////typedef quint64 u64;

//void base32_encode_qba(const QByteArray& qba, QString& result)
//{
// int s = qba.size();
// //?QString result;
// // 170 2 1 240 4

// int remainder = s % 5;
// if(remainder != 0)
// {
//  remainder = 5 - remainder;
// }

// for(int i = 0; i < s; i += 5)
// {
//  u8 val = 0;
//  memcpy(&val, qba.data() + i, 5);
//  QString v1 = QString::number(val, 32);
//  QString vb1 = QString::number(val, 2);
////  val = qToBigEndian(val);
////  val >>= 24;
////  val = qFromBigEndian(val);
//  QString v2 = QString::number(val, 32);
//  QString vb2 = QString::number(val, 2);


//  QByteArray check (5, 0);
//  memcpy(check.data(), &val, 5);

//  QByteArray check1 (5, 0);
//  memcpy(check1.data(), (void*)((size_t)&val + 3), 5);


////?  result += QString::number(val, 32);
//  result += QString("%1").arg(val, 8, 32, QChar('0')); //?QString::number(val, 32);


// }
// switch(remainder)
// {
// case 0: result += "w"; break;
// case 1: result += "x"; break;
// case 2: result += "y"; break;
// case 3: result += "z"; break;
// case 4: result += "_"; break;
// }
//}

//void base32_decode_qstring(QString text, QByteArray& result)
//{
// int index = text.indexOf(QRegularExpression("[_wxyz]"));
// if(index == -1)
// {
//  return;
// }
// QString str = text.left(index);
// QChar remainder_code = text.at(index);
// int s = str.size();
// for(int i = 0; i < s; i += 8)
// {
//  QString c = str.mid(i, 8).toUpper();
//  bool conversion_ok = false;
//  QByteArray conv = c.toLatin1();
//  u8 val = conv.toULongLong(&conversion_ok, 32);
//  //val = qToBigEndian(val);
//  QByteArray qba(5, 0);
//  memcpy(qba.data(), &val, 5); //(void*)(((size_t)&val) + 3), 5);
//  result.append(qba);
// }
// // 170 2 1 240 4

// int remainder;
// switch(remainder_code.toLatin1())
// {
// case 'w': remainder = 0; break;
// case 'x': remainder = 1; break;
// case 'y': remainder = 2; break;
// case 'z': remainder = 3; break;
// case '_': remainder = 4; break;
// default: remainder = 0; // error?
// }

// result.chop(remainder);

//}

////_KANS(Base32)


