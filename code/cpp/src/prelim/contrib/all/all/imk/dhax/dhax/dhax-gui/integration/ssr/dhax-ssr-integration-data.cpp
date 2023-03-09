
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "dhax-ssr-integration-data.h"

#include <QDebug>

DHAX_SSR_Integration_Data::DHAX_SSR_Integration_Data()
  :  ssr_read_count_(nullptr), ssr_write_count_(nullptr)
{

}

void DHAX_SSR_Integration_Data::init_read_write_count()
{
 if(ssr_read_count_)
 {
  qDebug() << "Re-initializing SSR import count!";
 }
 if(ssr_write_count_)
 {
  qDebug() << "Re-initializing SSR write count!";
 }
 static u4 static_u4_read = 0;
 ssr_read_count_ = &static_u4_read;
 static u4 static_u4_write = 0;
 ssr_write_count_ = &static_u4_write;
}
