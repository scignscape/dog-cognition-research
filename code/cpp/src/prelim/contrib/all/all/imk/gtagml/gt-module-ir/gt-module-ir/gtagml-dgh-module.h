
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef GTAGML_DGH_MODULE__H
#define GTAGML_DGH_MODULE__H

#include <QString>
#include <QMap>
#include <QMultiMap>
#include <QStack>

#include <QSet>

#include <functional>

#include "accessors.h"

#include "global-types.h"

#include "kans.h"

KANS_CLASS_DECLARE(GTagML ,GTagML_Folder)
KANS_CLASS_DECLARE(GTagML ,GTagML_Project_Info)


USING_KANS(GTagML)
//?#define MACRO_PASTE(...) __VA_ARGS__

KANS_(DGH)

class GTagML_DGH_Module
{

 static void process_gtagml_file(QString path,
   GTagML_Project_Info* gpi, GTagML_Folder* fld);

 QString read_args(QString args); //, QMap<QString, u1>& flagset,
  // QMap<QString, QString>& flagpairs, QSet<QString>& fs);

 QSet<QString> current_flagset_;
 QMap<QString, QString> current_flagpairs_;
 QMap<QString, u1> current_flagset_pos_;

 QString ppc_text_;

 void read_discourse_markup(GTagML_Project_Info& gpi,
   QString mode, QString path, QString code);

 void check_post_processing_codes(GTagML_Project_Info& gpi);
 void check_main_block_text_commands(GTagML_Project_Info& gpi);

public:

 GTagML_DGH_Module();

 void compile_gt_file(QString args);
 void compile_gt_folder(QString args);
 void compile_gt_manuscript(QString args);
 void compile_gt_manuscript_file(QString args);


};

_KANS(DGH)

#endif // GTAGML_DGH_MODULE__H
