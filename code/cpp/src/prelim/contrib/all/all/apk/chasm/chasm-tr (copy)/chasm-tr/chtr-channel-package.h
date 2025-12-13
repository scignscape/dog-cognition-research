
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)



#ifndef CHTR_CHANNEL_PACKAGE__H
#define CHTR_CHANNEL_PACKAGE__H


#include "accessors.h"

#include "aqns.h"

#include "flags.h"

#include <QFile>
#include <QVector>

//?#include "tsl/ordered_map.h"

#include "global-types.h"

#include "chtr-channel-object.h"

AQNS_(Chasm_TR)


class ChTR_Channel_Object;


class ChTR_Channel_Package
{

private:

 static void* (*channel_object_encoder_)(ChTR_Channel_Object*);
 static ChTR_Channel_Object* (*channel_object_decoder_)(void*);

 QVector<void*> channel_objects_;

public:


 ChTR_Channel_Package();

 ACCESSORS__FNP__STATIC(void*, ChTR_Channel_Object* ,channel_object_encoder)
 ACCESSORS__FNP__STATIC(ChTR_Channel_Object*, void* ,channel_object_decoder)

// void* (*)(ChTR_Channel_Object*) channel_object_encoder();
// void set_channel_object_encoder(void* (*)(ChTR_Channel_Object*));

 //ACCESSORS(QString ,channel_kind)

 void add_channel_object(ChTR_Channel_Object* cco);

 void get_channel_objects(QVector<ChTR_Channel_Object*>& result)
 {
  result.resize(channel_objects_.size());
  std::transform(channel_objects_.begin(), channel_objects_.end(),
    result.begin(), channel_object_decoder_);
 }

 //template<typename FN_Type>
 // QVector<FN_Type>
 typedef void (*callback_type)(ChTR_Channel_Object&);

 void all_channel_objects(std::map<QString, std::function<void (ChTR_Channel_Object&)>> fns)
 {
  QVector<ChTR_Channel_Object*> ccos;
  get_channel_objects(ccos);
  for(ChTR_Channel_Object* cco : ccos)
  {
   auto it = fns.find(cco->channel_kind());
   if(it != fns.end())
   {
    it->second(*cco);
   }
  }
 }


};

_AQNS(Chasm_TR)


#endif // CHTR_CHANNEL_PACKAGE__H




