
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef NDS_PROJECT__H
#define NDS_PROJECT__H

#include "kans.h"
#include "accessors.h"

#include <QVector>
#include <QString>

#include "global-types.h"

#include "ntxh-parser/ntxh-document.h"

#include "nds-paragraph.h"
#include "nds-sentence.h"


class NGML_SDI_Document;

KANS_CLASS_DECLARE(DGH ,DGH_SDI_Document)
KANS_CLASS_DECLARE(DGH ,DGH_SDI_Paragraph)
KANS_CLASS_DECLARE(DGH ,DGH_SDI_Sentence)
USING_KANS(DGH)


KANS_(NGML)


class NDS_Project
{
 QString paper_short_name_;
 QString paper_root_folder_;
 QString paper_setup_folder_;

 QStringList prelatex_files_;
 QStringList marks_files_;
 QStringList htxn_files_;


 NGML_SDI_Document* ngml_;
 DGH_SDI_Document* dgh_;

 QString paper_sdi_file_; // /%1/sdi-merge.ntxh
 QString sdi_merge_file_;


public:

 NDS_Project();
 NDS_Project(QString paper_short_name, QString paper_root_folder,
   QString paper_setup_folder);


 ACCESSORS(NGML_SDI_Document* ,ngml)
 ACCESSORS(DGH_SDI_Document* ,dgh)
 ACCESSORS(QString ,paper_root_folder)

 QMap<QString, u2> locate_files();

 NDS_Paragraph get_paragraph_by_project_id(u4 id);
 NDS_Sentence get_sentence_by_project_id(u4 id);

 void init_ngml_document();
 void init_dgh_document();


};


_KANS(NGML)

#endif // NDS_PROJECT__H
