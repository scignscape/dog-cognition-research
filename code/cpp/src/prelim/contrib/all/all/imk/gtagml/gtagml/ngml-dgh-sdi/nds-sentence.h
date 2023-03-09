
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef NDS_SENTENCE__H
#define NDS_SENTENCE__H

#include "kans.h"
#include "accessors.h"

#include <QVector>
#include <QString>

#include "global-types.h"

#include "ntxh-parser/ntxh-document.h"


class NGML_SDI_Document;

KANS_CLASS_DECLARE(DGH ,DGH_SDI_Document)
KANS_CLASS_DECLARE(DGH ,DGH_SDI_Paragraph)
KANS_CLASS_DECLARE(DGH ,DGH_SDI_Sentence)
USING_KANS(DGH)


KANS_(NGML)

class NDS_Sentence
{
 DGH_SDI_Sentence* dgh_;


public:


 explicit NDS_Sentence(DGH_SDI_Sentence* dgh);


 ACCESSORS(DGH_SDI_Sentence* ,dgh)

};


_KANS(NGML)

#endif // NDS_SENTENCE__H
