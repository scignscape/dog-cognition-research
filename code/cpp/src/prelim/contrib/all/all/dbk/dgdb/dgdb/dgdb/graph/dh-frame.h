
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef DH_FRAME__H
#define DH_FRAME__H

#include <QString>
#include <QVector>
#include <QMap>

#include "accessors.h"

#include "global-types.h"

#include "kans.h"

#include "flags.h"

#include "dh-record.h"

#include <QDataStream>


//KANS_(DGDB)

class DgDb_Database_Instance;

class DH_Instance;
class DH_Dominion;
class DH_Record;

class DgDb_Hypernode;


struct String_Label_Triple
{
 DH_Record source;
 DH_Record* annotation;
 QString connector_label;
 DH_Record target;
 DH_Dominion* dom;
 u1 multi_relation_kind;
};


struct Hyperedge_Data
{
 n8 hyperedge_id;
 n8 annotation_id;
 u4 connector_id;
 n8 target_id;
 u1 multi_relation_kind;
 u2 context_id;
 u1 flags; //  1 = out-edge, 2 = in-edge, 3 = bi-edge, etc.

 void supply_data(QByteArray& qba);
 void absorb_data(const QByteArray& qba);
};


class DH_Context
{
 u4 id_;

public:
 DH_Context(u4 id = 0)
   :  id_(id)
 {

 } 

};

class DH_Frame
{
 DH_Instance* dh_instance_;
 u4 id_;

 QVector<String_Label_Triple> new_string_label_triples_;

public:


 ACCESSORS(u4 ,id)
 ACCESSORS(QVector<String_Label_Triple> ,new_string_label_triples)

 DH_Frame(DH_Instance* dh_instance, u4 id = 0);

 DH_Record register_new_triple(DH_Record source, QString connector, DH_Record target,
   DH_Dominion* dom);

 DH_Context* new_context()
 {
  return new DH_Context;
 }

 QPair<u4, u4> commit();

};

struct _Frame_With_Source_and_Dominion_Connector
{
 DH_Frame* fr;
 DH_Dominion* dom;
 DH_Context* context;
 QString connector;
 DH_Record source;

// DH_Record& operator>>(DH_Record* rhs)
// {
//  return *fr->register_new_triple(source, connector, rhs, dom);
// }
// DH_Record& operator>>(DH_Record& rhs)
// {
//  return *fr->register_new_triple(source, connector, &rhs, dom);
// }

 DH_Record operator>>(DgDb_Hypernode* rhs);
// {
//  DH_Record dhr{{rhs->id(), rhs}};
//  return *fr->register_new_triple(source, connector, &dhr, dom);
// }

};


struct _Frame_With_Dominion_Connector
{
 DH_Frame* fr;
 DH_Dominion* dom;
 DH_Context* context;
 QString connector;
};

struct _Frame_With_Dominion
{
 DH_Frame* fr;
 DH_Dominion* dom;
 DH_Context* context;
 _Frame_With_Dominion_Connector operator[](QString qs)
 {
  return {fr, dom, context, qs};
 }
};

inline _Frame_With_Dominion operator/(DH_Frame& fr, DH_Dominion* dom)
{
 return {&fr, dom, nullptr};
}

inline _Frame_With_Dominion operator/(_Frame_With_Dominion fr, DH_Context* ctxt)
{
 fr.context = ctxt;
 return fr;
}

inline _Frame_With_Source_and_Dominion_Connector operator<<(DH_Record& lhs,
  const _Frame_With_Dominion_Connector& rhs)
{
 return {rhs.fr, rhs.dom, rhs.context, rhs.connector, lhs};
}

_Frame_With_Source_and_Dominion_Connector operator<<(DgDb_Hypernode* lhs,
  const _Frame_With_Dominion_Connector& rhs);


//?_KANS(DGDB)


#endif // DH_FRAME__H


