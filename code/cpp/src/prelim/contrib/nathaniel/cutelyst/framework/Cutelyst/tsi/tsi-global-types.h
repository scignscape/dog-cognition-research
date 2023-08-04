
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef TSI_GLOBAL_TYPES__H
#define TSI_GLOBAL_TYPES__H

#include <QString>

static inline QString operator ""_qt(const char* cs, size_t size)
{
 std::string ss(cs, size);
 return QString::fromStdString(ss);
}


typedef qint8 s1;
typedef qint16 s2;
typedef qint32 s4;
typedef qint64 s8;

typedef qreal r8;
typedef float r4;

typedef quint8 u1;
typedef quint16 u2;
typedef quint32 u4;
typedef quint64 n8;



#endif // TSI_GLOBAL_TYPES__H

