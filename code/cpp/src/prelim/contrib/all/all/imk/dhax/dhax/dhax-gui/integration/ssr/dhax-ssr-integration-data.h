
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef DHAX_SSR_INTEGRATION_DATA__H
#define DHAX_SSR_INTEGRATION_DATA__H

#include "accessors.h"
#include "global-types.h"

#include <QVector>



class DHAX_SSR_Integration_Data
{
 friend class DHAX_SSR_Integration_Controller;

 QString ssr_file_path_;

 u4* ssr_read_count_;
 u4* ssr_write_count_;


public:

 DHAX_SSR_Integration_Data();

 ACCESSORS(u4* ,ssr_read_count)
 ACCESSORS(u4* ,ssr_write_count)
 ACCESSORS(QString ,ssr_file_path)

 void init_read_write_count();

};


#endif //  DHAX_SSR_INTEGRATION_DATA__H


