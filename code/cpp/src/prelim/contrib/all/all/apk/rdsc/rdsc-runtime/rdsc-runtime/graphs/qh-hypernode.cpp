
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "qh-hypernode.h"

USING_KANS(RdSC)

Qh_Hypernode::Qh_Hypernode(QVector<u1>& data, Qh_Node_Data* node_data)
  :  data_(data), node_data_(node_data)
{

}

