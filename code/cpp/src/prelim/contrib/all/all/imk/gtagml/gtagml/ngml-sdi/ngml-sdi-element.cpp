
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "ngml-sdi-element.h"

//#include "ntxh-parser/ntxh-document.h"

#include "global-types.h"

//typedef NTXH_Graph::hypernode_type hypernode_type;

NGML_SDI_Element::NGML_SDI_Element()
  :  NGML_SDI_Mark_Base()
{
}

QChar NGML_SDI_Element::get_command_cue()
{
 return '@';
}

QChar NGML_SDI_Element::get_command_end_cue()
{
 return '*';
}

/*
\title>From \cq-tech>Naturalizing Phenomenology/> to Cognitive Grammar
/title>

<sentence-examples: id=''|
\sentence-ex: id=''>{clo}[45]<John called mary>/>
|sentence-examples>

*/





