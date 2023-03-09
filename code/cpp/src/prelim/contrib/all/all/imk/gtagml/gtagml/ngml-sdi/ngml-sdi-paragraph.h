
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef NGML_SDI_PARAGRAPH__H
#define NGML_SDI_PARAGRAPH__H

#include "global-types.h"


#include <QDebug>

#include <QTextStream>

//#include "ntxh-parser/ntxh-document.h"

#include "kans.h"

#include "accessors.h"

//KANS_CLASS_DECLARE(HGDMCore ,NTXH_Graph)
//USING_KANS(HGDMCore)

#include "ngml-sdi-mark-base.h"

//class hypernode_type;

class NGML_SDI_Page;


class NGML_SDI_Paragraph : public NGML_SDI_Mark_Base
{
 QString current_jobname_;

 NGML_SDI_Page* page_object_;

public:
 
 NGML_SDI_Paragraph();

 ACCESSORS(QString ,current_jobname)

 ACCESSORS(NGML_SDI_Page* ,page_object)

 QChar get_command_cue()
 {
  return ':';
 }

 QChar get_command_end_cue()
 {
  return '<';
 }

 QString get_kind_string() Q_DECL_OVERRIDE
 {
  return "\\:";
 }


};


#endif // NGML_SDI_SENTENCE__H
