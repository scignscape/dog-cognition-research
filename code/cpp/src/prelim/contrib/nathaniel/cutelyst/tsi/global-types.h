
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef GLOBAL_TYPES__H
#define GLOBAL_TYPES__H

static inline QString operator ""_qt(const char* cs, size_t size)
{
 std::string ss(cs, size);
 return QString::fromStdString(ss);
}


#endif // GLOBAL_TYPES__H
