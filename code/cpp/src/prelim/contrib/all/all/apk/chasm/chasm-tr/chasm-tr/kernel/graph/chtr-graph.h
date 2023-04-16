
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef CHTR_GRAPH__H
#define CHTR_GRAPH__H


#include <QTextStream>

#include "accessors.h"

#include "aqns.h"


#include "chtr-node.h"

USING_AQNS(Chasm_TR)

#include "kernel/chtr-dominion.h"

AQNS_(Chasm_TR)


class ChTR_Graph : public phaong<pg_t>
{
 ChTR_Node* root_node_;

 QMap<QString, QPair<signed int,
   QPair<signed int, signed int> > > types_;

 QMap<QPair<QString, QString>, int> field_indices_;

public:
 typedef phaong<pg_t>::Hypernode hypernode_type;
 typedef phaong<pg_t>::numeric_index_type numeric_index_type;

private:
 QVector<hypernode_type*> hypernodes_;

public:

 ACCESSORS__CONST_RGET(QVector<hypernode_type*> ,hypernodes)

 ChTR_Graph(ChTR_Node* root_node = nullptr);


 hypernode_type* new_hypernode_by_type_name(QString ty);

};

_AQNS(Chasm_TR)


#endif
