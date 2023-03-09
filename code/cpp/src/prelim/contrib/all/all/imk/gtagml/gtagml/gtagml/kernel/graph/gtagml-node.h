
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef GTAGML_NODE__H
#define GTAGML_NODE__H

#include "relae-graph/relae-node-ptr.h"

#include "kernel/gtagml-dominion.h"

#include "kernel/frame/gtagml-frame.h"

#include "kans.h"

KANS_(GTagML)

class GTagML_Whitespace_Holder;

class GTagML_Node : public node_ptr<GTagML_Dominion>
{
public:
 #define DOMINION_TYPE DOMINION_NODE_CONSTRUCTOR
 #include "kernel/dominion/types.h"
 #undef DOMINION_TYPE


 QString debug_connectors() const;

 GTagML_Whitespace_Holder* wsh()
 {
  return reinterpret_cast<GTagML_Whitespace_Holder*>(vertex_.raw_pointer());
 }

 template<typename T>
 caon_ptr<T> as()
 {
  #ifdef NO_CAON
  //?return reinterpret_cast<T*>(vertex_);
  return caon_ptr<T> (reinterpret_cast<T*>(vertex_));
  #else //NO_CAON
  return vertex_.template caon_cast<T>();
  #endif

 }


};

_KANS(GTagML)


#endif
