
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef DH_RECORD__H
#define DH_RECORD__H

#include <QString>
#include <QVector>
#include <QMap>

#include "accessors.h"

#include "global-types.h"

#include "kans.h"

#include "flags.h"

//#include "dh-frame.h"


//KANS_(DGDB)

class DgDb_Database_Instance;

class DH_Instance;
class DH_Dominion;
class DH_Record;

class DgDb_Hypernode;



class DH_Record
{
 n8 record_id_;
 DgDb_Hypernode* node_;

public:

 DH_Record() : record_id_(0), node_(nullptr) {}
 DH_Record(QPair<n8, DgDb_Hypernode*> pr) : record_id_(pr.first), node_(pr.second) {}

 ACCESSORS(DgDb_Hypernode* ,node)
 ACCESSORS(n8 ,record_id)
};



#endif // DH_RECORD__H


