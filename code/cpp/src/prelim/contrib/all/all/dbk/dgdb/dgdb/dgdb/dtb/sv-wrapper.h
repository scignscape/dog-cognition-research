
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef SV_WRAPPER__H
#define SV_WRAPPER__H

#include <QByteArray>

#include <functional>

#include "_sv-wrapper.h"

#include "tkrzw/tkrzw_dbm.h"
#include "tkrzw/tkrzw_str_util.h"

#include <string_view>

#include "global-types.h"

struct SV_Wrapper
{
 std::string_view value;
 QByteArray* qba;

 QString qstring();
 n8 to_n8();
 void from_n8(n8 v);

 void from_qstring(QString str);
 QString qstring_utf8();

 void noop();

 void confirm();
};


#endif // SV_WRAPPER__H


