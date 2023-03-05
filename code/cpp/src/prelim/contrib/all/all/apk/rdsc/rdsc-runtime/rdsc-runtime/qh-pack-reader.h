
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef QH_PACK_READER__H
#define QH_PACK_READER__H

#include <QByteArray>

#include <QVariant>

#include <functional>

#include "global-types.h"

#include "qh-pack-code.h"

#include "accessors.h"

KANS_(RdSC)

class Qh_Node_Data;
class Qh_Hypernode;

class Qh_Pack_Reader
{
 Qh_Pack_Code& pack_code_;
 Qh_Node_Data* node_data_;
 Qh_Node_Data* proxy_data_;

 QVector<u1> data_;

 u2 current_index_;
 u4 current_byte_index_;

public:

 Qh_Pack_Reader(Qh_Pack_Code& pack_code, const QVector<u1>& data,
   Qh_Node_Data* node_data = nullptr);

 Qh_Pack_Reader(Qh_Pack_Code& pack_code, const Qh_Hypernode& qhn);

 ACCESSORS(Qh_Node_Data* ,proxy_data)

 QVariant read_value();

 u1 read_data_1(u4 index);
 u2 read_data_2(u4 index);
 u4 read_data_4(u4 index);
 n8 read_data_8(u4 index);
};

_KANS(RdSC)

#endif // QH_PACK_READER__H


