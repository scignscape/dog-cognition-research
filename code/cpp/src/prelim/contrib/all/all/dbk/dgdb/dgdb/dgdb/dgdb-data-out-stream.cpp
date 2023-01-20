
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "dgdb-data-out-stream.h"


DgDb_Data_Out_Stream::DgDb_Data_Out_Stream(const QByteArray& device)
  :  device_(device), index_(0)
{

}


