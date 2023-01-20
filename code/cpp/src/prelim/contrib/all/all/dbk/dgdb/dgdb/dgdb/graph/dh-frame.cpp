//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "dh-frame.h"

#include "dgdb-database-instance.h"

#include "dgdb-hypernode.h"

#include "dh-instance.h"


//? USING_KANS(DGDB)


DH_Frame::DH_Frame(DH_Instance* dh_instance, u4 id)
  :  dh_instance_(dh_instance),  id_(id)
{

} 

void Hyperedge_Data::supply_data(QByteArray& qba)
{
 QDataStream qds(&qba, QIODevice::WriteOnly);
 qds << hyperedge_id << annotation_id << connector_id << target_id
   << multi_relation_kind << context_id << flags;
}

void Hyperedge_Data::absorb_data(const QByteArray& qba)
{
 QDataStream qds(qba);
 qds >> hyperedge_id >> annotation_id >> connector_id >> target_id
   >> multi_relation_kind >> context_id >> flags;
}


QPair<u4, u4> DH_Frame::commit()
{
 return dh_instance_->commit_new_triples(new_string_label_triples_);
}

_Frame_With_Source_and_Dominion_Connector operator<<(DgDb_Hypernode* lhs,
  const _Frame_With_Dominion_Connector& rhs)
{
 DH_Record dhr{{lhs->id(), lhs}};
 return {rhs.fr, rhs.dom, rhs.context, rhs.connector, dhr};
}


DH_Record _Frame_With_Source_and_Dominion_Connector::operator>>(DgDb_Hypernode* rhs)
{
 DH_Record dhr{{rhs->id(), rhs}};
 return fr->register_new_triple(source, connector, dhr, dom);
}

DH_Record DH_Frame::register_new_triple(DH_Record source, QString connector, DH_Record target,
  DH_Dominion* dom)
{
 // // not using dom here ...
 u1 multi_relation_kind = 0;

// if(target->id() < 1024)
// {
//  if(target->id() < 1000)
//    property_kind = 255; // error?  Would be ever connect to an index label?
//  else
//    property_kind = target->id() - 1000;
// }

 new_string_label_triples_.push_back({source, nullptr, connector, target, dom, multi_relation_kind});
 return source;
}


