
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef DGDB_HYPERNODE__H
#define DGDB_HYPERNODE__H

#include <QByteArray>

#include <functional>

#include "global-types.h"

#include "accessors.h"

// //  pattern
//     0b 0000'0000'0000'0000 0000'0000'0000'1000 0000'0000'0000'0000 0000'0000'0000'1000


class DH_Type;


class DgDb_Hypernode
{
 n8 id_;

 DH_Type* dh_type_;

 char* shm_block_;

 //u4 shm_block_length_;

public:

 DgDb_Hypernode(n8 id);

 ACCESSORS(n8 ,id)

 ACCESSORS(DH_Type* ,dh_type)
 ACCESSORS(char* ,shm_block)
 //ACCESSORS(

 u4 get_shm_block_size();


};


#endif // DGDB_HYPERNODE__H


