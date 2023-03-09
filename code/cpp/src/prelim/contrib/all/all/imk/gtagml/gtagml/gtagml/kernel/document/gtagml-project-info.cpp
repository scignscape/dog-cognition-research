
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "gtagml-project-info.h"


// #include "gtagml-document-light-xml.h"

#include <QFile>
#include <QTextStream>

#include "kans.h"

USING_KANS(GTagML)


GTagML_Project_Info::GTagML_Project_Info(QString root_folder)
  :  Flags(0), root_folder_(root_folder), user_data_(nullptr)
{
}


void GTagML_Project_Info::finalize_post_processing_codes(QString path, QStringList& qsl)
{
 post_processing_codes_[path].append(qsl);
}


void GTagML_Project_Info::add_blocks(QString path, GTagML_Output_Blocks* gob)
{
 blocks_by_path_[path] = gob;
}




