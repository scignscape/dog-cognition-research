
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef _SV_WRAPPER__H
#define _SV_WRAPPER__H

#include <QByteArray>

#include <functional>

#include "global-types.h"

#include "accessors.h"

// //   put this here for now ...

struct SV_Wrapper;

struct SV_Wrapper_3
{
 SV_Wrapper& key;
 SV_Wrapper& value;
 SV_Wrapper& result;
};

typedef SV_Wrapper_3& Sv_3;

struct SV_Wrapper_2
{
 SV_Wrapper& key;
 SV_Wrapper& result;
};

typedef SV_Wrapper_2& Sv_2;

typedef void(*create_cb)(Sv_2 svs);
typedef void(*update_cb)(Sv_3 svs);

#endif // _SV_WRAPPER__H


