
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef DW_QUERY_LAYER__H
#define DW_QUERY_LAYER__H

#include <QString>

#include <QMap>

#include "accessors.h"

#include "global-types.h"

#include "kans.h"

#include "flags.h"

#include "dw-record.h"

#include <functional>

KANS_(DGDB)


class DW_Instance;
class DW_Stage_Value;


class DW_Query_Layer
{
 struct single_field_query_holder
 {
  DW_Query_Layer& _this;
  QString key;
  DW_Stage_Value& dwsv;

  void operator << (std::function<n8(DW_Record)> fn)
  {
   _this.single_field_query(key, dwsv, fn);
  }
 };

 DW_Instance& dw_;

public:

 DW_Query_Layer(DW_Instance& dw);

 single_field_query_holder single_field_query(QString key, DW_Stage_Value& dwsv)
 {
  return {*this, key, dwsv};
 }

 void single_field_query(QString key, DW_Stage_Value& dwsv,
   std::function<n8(DW_Record)> dwr);

};

_KANS(DGDB)


#endif // DW_QUERY_LAYER__H


