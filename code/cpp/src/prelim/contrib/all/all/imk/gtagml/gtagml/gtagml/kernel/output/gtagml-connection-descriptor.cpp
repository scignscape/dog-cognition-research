
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "gtagml-connection-descriptor.h"

#include "kans.h"
USING_KANS(GTagML)

GTagML_Connection_Descriptor::GTagML_Connection_Descriptor(Descriptors descriptor)
 : descriptor_(descriptor)
{

}

QString GTagML_Connection_Descriptor::to_string(QString left, QString right)
{
 QString result = left;
 if(right.isEmpty())
  right = left;
 switch(descriptor_)
 {
// case Call_Entry: result += "CE"; break;
// case Call_Sequence: result += "CS"; break;
// case Cross_Sequence: result += "CX"; break;
// case Call_Continue: result += "CC"; break;
 }
 result += right;
 return result;
}
