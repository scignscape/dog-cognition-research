
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "nds-sentence.h"

#include "dgh-sdi/dgh-sdi-paragraph.h"
#include "dgh-sdi/dgh-sdi-sentence.h"


USING_KANS(NGML)


#include <QDebug>


NDS_Sentence::NDS_Sentence(DGH_SDI_Sentence* dgh)
  :  dgh_(dgh)
{

}



