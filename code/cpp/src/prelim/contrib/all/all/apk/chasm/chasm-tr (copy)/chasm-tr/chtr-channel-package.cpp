

//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)



#include "chtr-channel-package.h"


USING_AQNS(Chasm_TR)

void* (*ChTR_Channel_Package::channel_object_encoder_)(ChTR_Channel_Object*) = nullptr;
ChTR_Channel_Object* (*ChTR_Channel_Package::channel_object_decoder_)(void*) = nullptr;

//auto ChTR_Channel_Package::channel_object_encoder_ = nullptr;
//auto ChTR_Channel_Package::channel_object_decoder_ = nullptr;

ChTR_Channel_Package::ChTR_Channel_Package()
 // :  channel_object_encoder_(nullptr), channel_object_decoder_(nullptr)
{

}

void ChTR_Channel_Package::add_channel_object(ChTR_Channel_Object* cco)
{
 void* pv = channel_object_encoder_(cco);
 channel_objects_.push_back(pv);
}




