

//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)



#include "chtr-channel-object.h"

#include "chtr-carrier.h"


USING_AQNS(Chasm_TR)


ChTR_Channel_Object::ChTR_Channel_Object(QString channel_kind)
  :  channel_kind_(channel_kind)
{

}


void ChTR_Channel_Object::add_carrier(QString carrier_string)
{
 ChTR_Carrier* ccr = new ChTR_Carrier(carrier_string);
 carriers_.push_back(ccr);
}

