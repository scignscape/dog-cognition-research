
#ifndef GTAGML_TOKEN__H
#define GTAGML_TOKEN__H

#include "kans.h"
#include "accessors.h"

#include "flags.h"

#include <QString>


KANS_(GTagML)

class GTagML_Token
{
public:

 flags_(1)
  bool is_string_literal:1;
  bool is_keyword:1;
 _flags

private:

 QString raw_text_;

public:

 ACCESSORS(QString ,raw_text)

 GTagML_Token(QString raw_text);

 QString to_string();

 QString thumbnail(int max_characters = 6);

};

_KANS(GTagML)

#endif
