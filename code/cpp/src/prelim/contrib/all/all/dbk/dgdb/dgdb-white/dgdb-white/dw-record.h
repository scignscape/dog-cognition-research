
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef DW_RECORD__H
#define DW_RECORD__H

#include <QString>
#include <QDebug>
#include <QMap>

#include "dw-frame.h"

#include "accessors.h"

#include "global-types.h"

#include "kans.h"

#include "flags.h"


KANS_(DGDB)

//class WDB_Instance;


class DW_Record
{
 u4 id_;
 void* wg_record_;

public:


 ACCESSORS(u4 ,id)
 ACCESSORS(void* ,wg_record)

 DW_Record(u4 id, void* wg_record);
 DW_Record();
 
 template<typename VALUE_Type>
 VALUE_Type* cast_to()
 {
  return static_cast<VALUE_Type*>(wg_record_);
 }

};

inline _Frame_With_Source_and_Dominion_Connector operator<<(DW_Record& lhs, 
  const _Frame_With_Dominion_Connector& rhs)
{
 return {rhs.fr, rhs.dom, rhs.context, rhs.connector, &lhs};
}


_KANS(DGDB)

#endif // DW_RECORD__H


