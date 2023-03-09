

//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)



#ifndef GH_SDI_DOCUMENT__H
#define GH_SDI_DOCUMENT__H

#include "global-types.h"

#include "accessors.h"

#include <QPair>
#include <QMap>
#include <QString>

class GH_Block_Base;

#include "kans.h"

KANS_CLASS_DECLARE(GTagML, GTagML_Output_SDI_Infoset)
USING_KANS(GTagML)

KANS_(SDI)

class GH_SDI_Document
{
 GTagML_Output_SDI_Infoset* sdi_infoset_output_;

public:

 GH_SDI_Document();

 ACCESSORS(GTagML_Output_SDI_Infoset* ,sdi_infoset_output)

 void finalize_sentence_boundaries(GH_Block_Base& bl, QString path);

 void clear_end_boundary_space(GH_Block_Base& bl, u4& end);

 u4 scan_for_sentence_start(GH_Block_Base& bl, u4 start, u4 end, u4& result);
 u4 scan_for_sentence_end(GH_Block_Base& bl, u4 start, u4 end, u4& result, u4& space);

 u4 scan_for_sentence_start_resume(GH_Block_Base& bl, u4 start, u4 end);

 bool check_letter(GH_Block_Base& bl, u4 pos);
 bool check_sentence_start_resume(GH_Block_Base& bl, u4 pos);
 bool check_sentence_end_suspend(GH_Block_Base& bl, u4 pos);

 static void setup_folder_from_template(QString file_name, QString job_name, QString template_folder,
   QString input_folder, QString setup_folder, QString topl = {});
};

_KANS(SDI)


#endif // GH_SDI_DOCUMENT__H


