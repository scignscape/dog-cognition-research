

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


QString ChTR_Channel_Object::get_proc_name()
{
 if(carriers_.size() == 1)
 {
  ChTR_Carrier* car = carriers_.first();
  car->check_literal();
  if(car->literal_info.flags.known_symbol)
    return car->composite_symbol();
 }
 return {};
}

void ChTR_Channel_Object::add_carrier(QString carrier_string)
{
 ChTR_Carrier* ccr = new ChTR_Carrier(carrier_string);
 carriers_.push_back(ccr);
}

