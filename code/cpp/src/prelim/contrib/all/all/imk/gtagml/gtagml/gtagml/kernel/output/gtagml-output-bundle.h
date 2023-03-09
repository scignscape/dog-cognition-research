
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef GTAGML_OUTPUT_BUNDLE__H
#define GTAGML_OUTPUT_BUNDLE__H

#include "relae-graph/relae-caon-ptr.h"
#include "gtagml-connection-descriptor.h"

#include "global-types.h"

class QTextStream;

#include "kans.h"
KANS_CLASS_DECLARE(HTXN ,HTXN_Document_8b)
USING_KANS(HTXN)


#include "kans.h"

KANS_(GTagML)

class GTagML_Node;
class GTagML_Connection_Descriptor;
class GTagML_Tag_Command_Callback;



struct GTagML_Output_Bundle
{
 typedef GTagML_Node tNode;

 QTextStream& qts;
 u4& index;

 caon_ptr<tNode> node;
 caon_ptr<tNode> prior_node;
 GTagML_Connection_Descriptor connection_descriptor;
 caon_ptr<GTagML_Tag_Command_Callback> cb;
 caon_ptr<tNode> prior_cross_node;

 GTagML_Output_Bundle with(QTextStream& new_qts) const;

 GTagML_Output_Bundle with(caon_ptr<tNode> n, GTagML_Connection_Descriptor descriptor) const;
 GTagML_Output_Bundle with(caon_ptr<tNode> sn,
   caon_ptr<tNode> n, GTagML_Connection_Descriptor descriptor) const;

 GTagML_Output_Bundle with(caon_ptr<tNode> n,
   GTagML_Connection_Descriptor descriptor, caon_ptr<tNode> pcn) const;

 GTagML_Output_Bundle with(caon_ptr<tNode> sn,
   caon_ptr<tNode> n, GTagML_Connection_Descriptor descriptor, caon_ptr<tNode> pcn) const;

 GTagML_Output_Bundle with(GTagML_Connection_Descriptor descriptor) const;
 GTagML_Output_Bundle with_node(caon_ptr<tNode> n) const;
 GTagML_Output_Bundle with_nodes(caon_ptr<tNode> sn, caon_ptr<tNode> n) const;
 GTagML_Output_Bundle with_callback(caon_ptr<GTagML_Tag_Command_Callback> c) const;
};

struct GTagML_Output_Partial_Bundle
{
 typedef GTagML_Node tNode;

 QTextStream& qts;
 u4& index;
 caon_ptr<tNode> node;

 operator GTagML_Output_Bundle()
 {
  return {qts, index, node, nullptr, GTagML_Connection_Descriptor(),
    caon_ptr<GTagML_Tag_Command_Callback> ( nullptr ) };
 }
};



_KANS(GTagML)


#endif
