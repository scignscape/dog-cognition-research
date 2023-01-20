
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef PHAONG_TYPES__H
#define PHAONG_TYPES__H


#include "phaong.h"

#include <QString>
#include <QPair>


typedef phaong_galaxy<QPair<QString, void*>> pg_t;
typedef phaong<pg_t> phg_t;



#define PHAONG_DATA(x ,y) \
   set_data(this, phaong_data_index++, {#x, &y##_})



#endif //  PHAONG_TYPES__H
