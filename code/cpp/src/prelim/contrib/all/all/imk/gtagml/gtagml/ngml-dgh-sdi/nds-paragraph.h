
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef NDS_PARAGRAPH__H
#define NDS_PARAGRAPH__H

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

class NDS_Paragraph
{
 DGH_SDI_Paragraph* dgh_;


public:


 explicit NDS_Paragraph(DGH_SDI_Paragraph* dgh);


 ACCESSORS(DGH_SDI_Paragraph* ,dgh)

};


_KANS(NGML)

#endif // NDS_PARAGRAPH__H
