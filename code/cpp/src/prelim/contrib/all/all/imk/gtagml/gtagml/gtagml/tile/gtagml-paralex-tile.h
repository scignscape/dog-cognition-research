
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef GTAGML_PARALEX_TILE__H
#define GTAGML_PARALEX_TILE__H

#include <QString>
#include <QMap>

#include "accessors.h"
#include "flags.h"

#include "global-types.h"

#include "whitespace/gtagml-whitespace-holder.h"

#include "kans.h"

KANS_(GTagML)

class GTagML_HTXN_Node;

class GTagML_Paralex_Tile : public GTagML_Whitespace_Holder
{
public:
 enum Kind {
   N_A, Alt_Interpretation, Pipe_Escape,
   Numeric_Character_Reference
  };

private:

 Kind kind_;

 QString command_;
 QString raw_text_;
 
 u1 width_or_alt_;

 GTagML_HTXN_Node* GTagML_htxn_node_;


 template<Kind>
 void to_string(QString& result);

public:

 GTagML_Paralex_Tile(QString raw_text, Kind k, u1 w);

 ACCESSORS(GTagML_HTXN_Node* ,GTagML_htxn_node)

 QString to_string();
 
 u1 get_width();

 QString thumbnail(int max_characters = 7);
  // QString get_accent_as_html();

 template<typename T>
 void write_latex(T& t)
 {
 }

 template<typename T>
 void write_html(T& t)
 {
 }

};

_KANS(GTagML)

#endif
