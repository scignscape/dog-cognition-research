
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)



#ifndef CHTR_CARRIER__H
#define CHTR_CARRIER__H


#include "accessors.h"

#include "aqns.h"

#include "flags.h"

#include <QFile>
#include <QVector>

//?#include "tsl/ordered_map.h"

#include "global-types.h"

#include "flags.h"

AQNS_(Chasm_TR)


class ChTR_Carrier
{
 public:

  struct Literal_Info
  {
   flags_(2)
    bool known_symbol:1;
    bool signed_as_positive:1;
    bool signed_as_negative:1;
    bool unsigned_decimal:1;
    bool signed_decimal:1;
    bool unsigned_integer:1;
    bool qstring:1;
    bool xstring:1;
    bool keyword:1;
    bool base_10:1;
    bool base_8:1;
    bool base_16:1;
    bool base_32:1;
    bool base_64:1;
    bool base_2:1;
   _flags

   Literal_Info() : Flags(0) {}

   bool tbd() { return Flags == 0; }

   inline bool note_base_10();
   inline bool note_base_2();
   inline bool note_base_8();
   inline bool note_base_16();

  };

  Literal_Info literal_info;

private:

 QString symbol_;

 QString namespace_;

public:


 ChTR_Carrier(QString symbol = {});

 ACCESSORS(QString ,symbol)

 void check_literal();
 bool parse_literal_info();
 bool check_number_form(QStringView qsv);

 QString trimmed_symbol();


 QPair<QString, QString> literal_info_string();
 QString composite_symbol();

};

_AQNS(Chasm_TR)


#endif // CHTR_SOURCE__TOKEN__H




