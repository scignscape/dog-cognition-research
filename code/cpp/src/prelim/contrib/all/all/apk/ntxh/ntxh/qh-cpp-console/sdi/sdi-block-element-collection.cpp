
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)



#include "sdi-block-element-collection.h"

#include "sdi-block-element.h"

#include <QJsonArray>
#include <QJsonValue>

SDI_Block_Element_Collection::SDI_Block_Element_Collection()
{

}

SDI_Block_Element* SDI_Block_Element_Collection::read_json_end_object(QString kind, QJsonObject qjo)
{
 static QStringList kinds {"paragraph", "sentence", "named-entitity", "figure", "other"};
 s1 ix = kinds.indexOf(kind);
 if(ix == -1)
   return nullptr;

 QVector<SDI_Block_Element*>& vec = at(ix);
 if(u4 id = qjo.value("id").toInt())
 {
  if(SDI_Block_Element* result = vec.value(id - 1))
  {
   result->read_json_end_object(qjo);
   return result;
  }
 }

 return nullptr;
}
