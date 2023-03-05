
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef QH_HYPERNODE__H
#define QH_HYPERNODE__H

#include <QByteArray>

#include <QVariant>

#include <functional>

#include "global-types.h"

#include "accessors.h"
//class Qh_Bundle_Code;

#include "qh-pack-code.h"

KANS_(RdSC)

class Qh_Node_Data;
class Qh_Type_Info;


class Qh_Hypernode
{
 QVector<u1> data_;

 Qh_Node_Data* node_data_;
 Qh_Type_Info* type_info_;

public:

 Qh_Hypernode(QVector<u1>& data, Qh_Node_Data* node_data = nullptr);

 ACCESSORS(Qh_Type_Info* ,type_info)

 ACCESSORS__CONST_RGET(QVector<u1> ,data)
 ACCESSORS(Qh_Node_Data* ,node_data)

 //void add_

};

_KANS(RdSC)

#endif // QH_HYPERNODE__H


