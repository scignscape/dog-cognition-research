
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef DH_INSTANCE__H
#define DH_INSTANCE__H

#include <QString>

#include <QMap>

#include "accessors.h"

#include "global-types.h"

#include "kans.h"

#include "flags.h"

#include "graph/dh-frame.h"


#include "tkrzw/tkrzw_index.h"
#include "tkrzw/tkrzw_str_util.h"

KANS_(DGDB)

class DgDb_Database_Instance;
class DgDb_Hypernode;


class DH_Instance
{
 DgDb_Database_Instance* ddi_;

 n8* current_inedges_record_count_;
 n8* current_outedges_record_count_;
 n8* current_multi_relation_record_count_;

 n8 inedges_floor_;
 n8 outedges_floor_;
 n8 multi_relation_floor_;

 QMap<u4, QPair<DH_Dominion*, QString>> connector_ids_;

public:


 ACCESSORS(DgDb_Database_Instance* ,ddi)

 ACCESSORS(n8* ,current_inedges_record_count)
 ACCESSORS(n8* ,current_outedges_record_count)
 ACCESSORS(n8* ,current_multi_relation_record_count)

 ACCESSORS(n8 ,inedges_floor)
 ACCESSORS(n8 ,outedges_floor)
 ACCESSORS(n8 ,multi_relation_floor)

 QPair<DH_Dominion*, QString> get_connector_label_from_id(u4 id)
 {
  return connector_ids_.value(id);
 }

 DH_Instance(DgDb_Database_Instance* ddi);

 u4 get_connector_id(DH_Dominion* dom, QString connector_label);



 u4 new_inedges_record_id();
 u4 new_outedges_record_id();
 u4 new_multi_relation_record_id();

 DH_Record find_outedge(DgDb_Hypernode* dh, QString connector_label);

 DH_Frame* new_frame();

 DH_Record new_outedges_or_multi_relation_record(DH_Record base,
   u4 col, u4 (DH_Instance::*cb)(),
   QVector<QPair<QPair<QString, DH_Record>, DH_Record>>& targets);

 DH_Record new_outedges_record(DH_Record base,
   QVector<QPair<QPair<QString, DH_Record>, DH_Record>>& targets);

 DH_Record new_multi_relation_record(DH_Record base,
   QVector<QPair<QPair<QString, DH_Record>, DH_Record>>& targets);


 QPair<u4, u4> commit_new_triples(QVector<String_Label_Triple>& triples);

 DH_Record add_hyperedge_or_multi_relation(DH_Record& source, QString connector,
   const DH_Record* annotation,
   DH_Record& target, u4 multi_relation_code = 0);

 DH_Record add_hyperedge(DH_Record& source, QString connector, const DH_Record& annotation,
   DH_Record& target);
 DH_Record add_hyperedge(DH_Record& source, QString connector, DH_Record& target);

 DH_Record add_multi_relation(DH_Record& source, QString connector, const DH_Record& annotation,
   DH_Record& target, u4 multi_relation_code);
 DH_Record add_multi_relation(DH_Record& source, QString connector, DH_Record& target, u4 multi_relation_code);


};

_KANS(DGDB)


#endif // DH_DOMINION__H


