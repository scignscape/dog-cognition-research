
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "gtagml-output-bundle.h"

#include "kans.h"
USING_KANS(GTagML)

GTagML_Output_Bundle GTagML_Output_Bundle::with(QTextStream& new_qts) const
{
 return {new_qts, index, node, nullptr, connection_descriptor, cb, prior_cross_node};
}


GTagML_Output_Bundle GTagML_Output_Bundle::with(GTagML_Connection_Descriptor descriptor) const
{
 return {qts, index, node, nullptr, descriptor, cb, prior_cross_node};
}

GTagML_Output_Bundle GTagML_Output_Bundle::with(caon_ptr<tNode> n, GTagML_Connection_Descriptor descriptor) const
{
 return {qts, index, n, nullptr, descriptor, cb, prior_cross_node};
}

GTagML_Output_Bundle GTagML_Output_Bundle::with(caon_ptr<tNode> sn,
  caon_ptr<tNode> n, GTagML_Connection_Descriptor descriptor) const
{
 return {qts, index, n, sn, descriptor, cb, prior_cross_node};
}


GTagML_Output_Bundle GTagML_Output_Bundle::with(caon_ptr<tNode> n,
  GTagML_Connection_Descriptor descriptor, caon_ptr<tNode> pcn) const
{
 return {qts, index, n, nullptr, descriptor, cb, pcn};
}

GTagML_Output_Bundle GTagML_Output_Bundle::with(caon_ptr<tNode> sn,
  caon_ptr<tNode> n, GTagML_Connection_Descriptor descriptor, caon_ptr<tNode> pcn) const
{
 return {qts, index, n, sn, descriptor, cb, pcn};
}



GTagML_Output_Bundle GTagML_Output_Bundle::with_node(caon_ptr<tNode> n) const
{
 return {qts, index, n, nullptr, connection_descriptor, cb, nullptr}; //?prior_cross_node};
}

GTagML_Output_Bundle GTagML_Output_Bundle::with_nodes(caon_ptr<tNode> sn, caon_ptr<tNode> n) const
{
 return {qts, index, n, sn, connection_descriptor, cb, nullptr}; //?;
}

GTagML_Output_Bundle GTagML_Output_Bundle::with_callback(caon_ptr<GTagML_Tag_Command_Callback> c) const
{
 return {qts, index, node, prior_node, connection_descriptor, c, prior_cross_node};
}



