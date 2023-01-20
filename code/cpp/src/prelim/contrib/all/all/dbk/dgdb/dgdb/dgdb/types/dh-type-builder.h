
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef DH_TYPE_BUILDER__H
#define DH_TYPE_BUILDER__H

#include <functional>

#include "global-types.h"

//#include "_whitedb/_whitedb.h"

#include "accessors.h"

#include "kans.h"

 //?KANS_(DgDb)

class DH_Type;

class DH_Type_Builder
{

public:


 DH_Type_Builder();

 virtual void build(QMap<QString, DH_Type*>* type_map, 
   std::function<void(QString, DH_Type*)> cb);

 virtual void build(QMap<QString, DH_Type*>* type_map)
 {
  build(type_map, nullptr);
 }
 
 virtual void build(std::function<void(QString, DH_Type*)> cb)
 {
  build(nullptr, cb);
 }

};


 //?_KANS(DgDb)

#endif // DH_TYPE_BUILDER__H


