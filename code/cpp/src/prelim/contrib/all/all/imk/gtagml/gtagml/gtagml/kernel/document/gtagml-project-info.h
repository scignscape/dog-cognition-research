
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef GTAGML_PROJECT_INFO__H
#define GTAGML_PROJECT_INFO__H

#include "relae-graph/relae-node-ptr.h"

#include "accessors.h"

#include "global-types.h"

#include "flags.h"

#include "kans.h"

#include <QStringList>

KANS_(GTagML)


class GTagML_Parser;
class GTagML_Output_Blocks;


class GTagML_Project_Info
{
public:

 flags_(1)
  bool manuscript_top_level_is_gt:1;
 _flags

private:

 QString root_folder_;
 QString sdi_template_file_;
 QString sdi_template_target_;

 QString gt_copy_folder_;
 QString main_block_text_commands_file_;

 QString gtagml_setup_;
 void* user_data_;

 QMap<QString, QStringList> post_processing_codes_;

 QMap<QString, GTagML_Output_Blocks*> blocks_by_path_;

 QMap<QString, QPair<QString, u4>> main_block_text_commands_;


public:

 GTagML_Project_Info(QString root_folder);

 ACCESSORS(QString ,gtagml_setup)
 ACCESSORS(void* ,user_data)

 ACCESSORS(QString ,gt_copy_folder)
 ACCESSORS(QString ,root_folder)

 ACCESSORS(QString ,main_block_text_commands_file)


 ACCESSORS__RGET(MACRO_PASTE(QMap<QString, QStringList>) ,post_processing_codes)

 ACCESSORS__RGET(MACRO_PASTE(QMap<QString, GTagML_Output_Blocks*>) ,blocks_by_path)

 ACCESSORS__RGET(MACRO_PASTE(QMap<QString, QPair<QString, u4>>) ,main_block_text_commands)


 void finalize_post_processing_codes(QString path, QStringList& qsl);
 void add_blocks(QString path, GTagML_Output_Blocks* gob);


};

_KANS(GTagML)


#endif
