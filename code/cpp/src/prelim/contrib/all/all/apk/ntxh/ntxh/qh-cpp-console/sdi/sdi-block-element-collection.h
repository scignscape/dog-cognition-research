
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef SDI_BLOCK_ELEMENT_COLLECTION__H
#define SDI_BLOCK_ELEMENT_COLLECTION__H

#include <QString>
#include <QPointF>
#include <QVector>

#include "accessors.h"

#include "global-types.h"

#include <array>

#include <QJsonObject>

class SDI_Block_Element;

class SDI_Block_Element_Collection : private std::array<QVector<SDI_Block_Element*>, 5>
{
public:

 SDI_Block_Element_Collection();


 QVector<SDI_Block_Element*>& paragraphs()
 {
  return this->at(0);
 }

 QVector<SDI_Block_Element*>& sentences()
 {
  return this->at(1);
 }

 QVector<SDI_Block_Element*>& named_entities()
 {
  return this->at(2);
 }

 QVector<SDI_Block_Element*>& figures()
 {
  return this->at(3);
 }

 QVector<SDI_Block_Element*>& others()
 {
  return this->at(4);
 }

 SDI_Block_Element* read_json_end_object(QString kind, QJsonObject qjo);


};

#endif // SDI_BLOCK_ELEMENT_COLLECTION__H

