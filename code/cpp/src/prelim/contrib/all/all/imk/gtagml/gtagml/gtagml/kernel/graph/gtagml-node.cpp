
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "gtagml-node.h"

#include "kans.h"
USING_KANS(GTagML)

QString GTagML_Node::debug_connectors() const
{
 QString result;
 targets_iterator_type it(targets_);
 while(it.hasNext())
 {
  it.next();
  QString connector = it.key()->label();
  caon_ptr<GTagML_Node> target = it.value();
  CAON_PTR_DEBUG(GTagML_Node ,target)
  result += QString("\n |%1| %2").arg(connector).arg(target->label());

 }
 return result;
}
