
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "gtagml-dgh-module.h"

#include "gt-module-ir.h"

#include <QDebug>

#include "gtagml/kernel/document/gtagml-document.h"

#include "gtagml/output/gtagml-output-latex.h"
#include "gtagml/output/gtagml-output-blocks.h"
#include "gtagml/output/gtagml-output-sdi-infoset.h"
#include "gtagml/kernel/document/gtagml-folder.h"

#include "gtagml/gh/gh-block-writer.h"
#include "gtagml/gh/gh-block-base.h"


#include "gtagml/sdi/gh-sdi-document.h"

#include "gtagml/kernel/document/gtagml-project-info.h"
#include "gtagml/output/gtagml-output-blocks.h"


#include "textio.h"

USING_KANS(TextIO)

USING_KANS(DGH)
USING_KANS(SDI)


GTagML_DGH_Module::GTagML_DGH_Module()
{

}

void GTagML_DGH_Module::process_gtagml_file(QString path,
  GTagML_Project_Info* gpi, GTagML_Folder* fld)
{
 GTagML_DGH_Module* _this = (GTagML_DGH_Module*) gpi->user_data();
 QSet<QString>& flagset = _this->current_flagset_;
 QMap<QString, QString>& flagpairs = _this->current_flagpairs_;

 GTagML_Document* gdoc = new GTagML_Document(gpi);

 if(!gpi)
   gdoc->init_project_info();

 if(fld)
   gdoc->set_man_folder_path(fld->man_path());

 if(flagpairs.contains(":top-level"))
   gdoc->set_top_level_path(flagpairs[":top-level"]);

 gdoc->load_and_parse(path);

 if(flagset.contains(":info-path"))
 {
  QString info_fldr = gdoc->use_info_path();
  QDir ip_qdir(info_fldr);
  if(!ip_qdir.exists())
    if(ip_qdir.mkpath("."))
      qDebug() << "Made path: " << ip_qdir.absolutePath();
 }

 GH_Block_Writer* blw = new GH_Block_Writer;

// QString divert;
// QTextStream qts(&divert);
// gdoc->set_divert(&qts);

 GTagML_Output_Blocks* gob = new GTagML_Output_Blocks(*gdoc, blw);
 gob->init_standard_8bit();
 gob->export_blocks();

 gpi->add_blocks(path, gob);

 GTagML_Output_SDI_Infoset* gsi = new GTagML_Output_SDI_Infoset(*gdoc, blw);

 QString fnc = gdoc->file_job_name();
 gsi->set_file_job_name(fnc);

 //goi->init_standard_8bit();

 gsi->export_infoset(gdoc->local_or_info_path() + ".info.txt"); // export_blocks(); //(path + ".");


 QString cpy = gsi->copy_path();
 QString setup = gsi->setup_path();

 if(!setup.isEmpty())
 {
  gpi->set_gtagml_setup(setup);
  if(cpy.isEmpty())
    cpy = setup;
 }

 QString ffolder;

 if(gpi->gtagml_setup().isEmpty())
 {
  if(flagset.contains(":archive"))
    ffolder = make_folder_from_file_name(path, DEFAULT_SDI_FOLDER);
  else
    ffolder = make_inner_folder_from_file_name("sdi", path);
  //
 }
 else
   ffolder = make_folder_from_file_name(path, gpi->gtagml_setup());


 GH_SDI_Document* gsd = gsi->sdi_document();


 QString sdi_path = get_path_with_different_folder(path, ffolder);

 gsd->finalize_sentence_boundaries(*blw->current_main_text_block(), sdi_path + ".sdi-prelatex.ntxh");

 QString mark_path = gob->export_marks(); //(path + ".");
// gob->load_marks(mark_path);


 GTagML_Output_Latex* gol = new GTagML_Output_Latex(*gdoc, gsd);
 gol->export_latex(path + ".tex");

 QString cp = copy_file_to_folder(path + ".tex", ffolder);
 qDebug() << "Copied " << path + ".tex" << " to " << cp;

 // // By now the sentence swaps are all done ...
 QString mb_file = gob->export_main_block();
// QString mb_cp = copy_file_to_folder(mb_file, ffolder);
// qDebug() << "Copied " << mb_file << " to " << mb_cp;


 if(!cpy.isEmpty())
 {
  QString cp;

  if(setup.isEmpty())
  {
   cp = copy_file_to_folder(path + ".tex", cpy);
   qDebug() << "Copied " << path + ".tex" << " to " << cp;
  }

  cpy += "/sdi";

  QDir sdi_dir(cpy);
  if(!sdi_dir.exists())
    if(sdi_dir.mkpath("."))
      qDebug() << "Made path: " << sdi_dir.absolutePath();

  cp = copy_file_to_folder(mark_path, cpy);
  qDebug() << "Copied " << mark_path << " to " << cp;

  cp = copy_file_to_folder(sdi_path + ".sdi-prelatex.ntxh", cpy);
  qDebug() << "Copied " << sdi_path + ".sdi-prelatex.ntxh" << " to " << cp;


 }

 QString gcf = gpi->gt_copy_folder();

 if(!gcf.isEmpty())
 {
  QDir gcf_dir(gcf);
  if(!gcf_dir.exists())
    if(gcf_dir.mkpath("."))
      qDebug() << "Made path: " << gcf;
  copy_file_to_folder(path, gcf);
 }


// if(flagset.contains(":setup-sdi"))
// {
//   prepend_template_to_file(cp, DEFAULT_SDI_FOLDER "/prepend",
//   {
//    { "%CONSOLE", ROOT_FOLDER "/code/cpp/qmake-console/projects/gtagml/ngml-sdi-console"},
//    { "%FILE", cp },
//    { "%SDI-FILE", sdi_path + ".sdi.ntxh" },
//    { "%SDI-PFILE", sdi_path + ".sdi-prelatex.ntxh" }
//   });
// }


 if(flagset.contains(":setup"))
 {
  if(gdoc->top_level_path().isEmpty())
  {
   prepend_template_to_file(cp, DEFAULT_SDI_FOLDER "/prepend",
   {
    { "%CONSOLE", ROOT_FOLDER "/code/cpp/qmake-console/projects/gtagml/ngml-sdi-console"},
    { "%FILE", cp },
    { "%SDI-FILE", sdi_path + ".sdi.ntxh" },
    { "%SDI-PFILE", sdi_path + ".sdi-prelatex.ntxh" }
   });
  }

  GH_SDI_Document::setup_folder_from_template(gdoc->local_file_name() + ".tex",
    {},
    DEFAULT_SDI_FOLDER "/template", ffolder, gdoc->top_level_path());

  if(!gdoc->top_level_path().isEmpty())
  {
   QString full = gdoc->get_full_top_level_path();
   QString cptl = copy_file_to_folder(full, ffolder);
   qDebug() << "Copied " << full << " to " << cptl;
  }
 }
 else if(!setup.isEmpty())
 {
  prepend_template_to_file(cp, DEFAULT_SDI_FOLDER "/prepend",
  {
   { "%CONSOLE", ROOT_FOLDER "/code/cpp/qmake-console/projects/gtagml/ngml-sdi-console"},
   { "%FILE", cp },
   { "%SDI-FILE", sdi_path + ".sdi.ntxh" },
   { "%SDI-PFILE", sdi_path + ".sdi-prelatex.ntxh" }
  });

  QFileInfo qfi(gdoc->local_file_name());

  GH_SDI_Document::setup_folder_from_template(gdoc->local_file_name() + ".tex",
    {}, DEFAULT_SDI_FOLDER "/template", qfi.absolutePath(), ffolder);
 }

 gpi->finalize_post_processing_codes(path, gsi->post_processing_codes());
}


void GTagML_DGH_Module::read_discourse_markup(GTagML_Project_Info& gpi,
  QString mode, QString path, QString code)
{

 s4 index = code.indexOf(':');
 if(index == -1)
   return;

 QString ref = code.mid(0, index);

 s4 index0 = code.indexOf(':', index + 1);
 if(index0 == -1)
   return;

 u4 layer_code = code.mid(index + 1, index0 - index - 1).toUInt();


 s4 index1 = code.indexOf('-', index0 + 1);
 if(index1 == -1)
   return;

 //QString ss = code.mid(index + 1, index1 - index - 1);
 u4 start = code.mid(index0 + 1, index1 - index0 - 1).toUInt();

 u4 end = code.mid(index1 + 1).toUInt();

 QString arg = code.mid(index1 + 1);

 GTagML_Output_Blocks* gob = gpi.blocks_by_path()[path];

 GH_Block_Base* gbb = gob->get_current_mandatory_argument_block();

 QString text = gbb->get_latex_out({start, end});

 if(!ref.isEmpty())
   text.prepend(QString(":%1 ").arg(ref));

 ppc_text_ += text + "\n===\n";
}


void GTagML_DGH_Module::compile_gt_file(QString args)
{
// QMap<QString, u1> flagset;
// QMap<QString, QString> flagpairs;
 QString file_path = read_args(args);
//           current_flagset_pos_,
//           flagpairs, fs);
// if(flagset.contains(":setup"))
// {
//  qDebug() << "setup = " << args;
// }

 GTagML_Project_Info gpi({});

 gpi.set_user_data(this);

 process_gtagml_file(file_path, &gpi, nullptr);

 check_post_processing_codes(gpi);
}


void GTagML_DGH_Module::check_main_block_text_commands(GTagML_Project_Info& gpi)
{
 auto& main_block_text_commands = gpi.main_block_text_commands();
 QString f = gpi.main_block_text_commands_file();
 if(f.isEmpty())
   return;
 f += ".counts";

 QString text;
 QMapIterator<QString, QPair<QString, u4>> it(main_block_text_commands);
 while (it.hasNext())
 {
  it.next();
  text += QString("%1 %2\n").arg(it.key(), 25).arg(it.value().second);
 }
 save_file(f, text);
}


void GTagML_DGH_Module::check_post_processing_codes(GTagML_Project_Info& gpi)
{
 QString ppc_file;
 if(!gpi.root_folder().isEmpty())
   ppc_file = gpi.root_folder() + "/ppc.txt";

// QFile f(file);
// if (f.open(QIODevice::WriteOnly | QIODevice::Append))
// {
//  f.write()
// }


 QMap<QString, QStringList>& ppc = gpi.post_processing_codes();

 QMapIterator<QString, QStringList> it(ppc);

 while(it.hasNext())
 {
  it.next();
  QString path = it.key();

  // // assume if there's no root folder that there's only one file ...
  if(ppc_file.isEmpty())
    ppc_file = path + ".ppc.txt";

  QStringList codes = it.value();

  for(QString code : codes)
  {
   s4 index = code.indexOf(':');
   if(index == -1)
     continue;

   QString cat = code.mid(0, index);
   QString arg = code.mid(index + 1);
   if(cat.startsWith("discourse-markup"))
   {
    s4 index = cat.indexOf('=');
    if(index == -1)
      continue;

    QString mode = cat.mid(index + 1);

    read_discourse_markup(gpi, mode, path, arg);
    // only category of post-processing used here ...
   }
  }
 }

 if(!ppc_text_.isEmpty())
 {
  save_file(ppc_file, ppc_text_);
 }

}


void GTagML_DGH_Module::compile_gt_folder(QString args)
{
 qDebug() << "args = " << args;
}

//  QMap<QString, u1>& flagset,
//  QMap<QString, QString>& flagpairs, QSet<QString>& fs
QString GTagML_DGH_Module::read_args(QString args) //, QString& main_arg //,
{
 QStringList qsl = args.simplified().split(' ');
 QString result = GT_Module_IR::first_non_flag_arg(qsl,
   &current_flagset_pos_, &current_flagpairs_);

 QStringList keys = current_flagset_pos_.keys();

 current_flagset_ = QSet<QString>(keys.begin(), keys.end());

 //qDebug() << "args = " << args;
 return result;
}


void GTagML_DGH_Module::compile_gt_manuscript(QString args)
{
// QMap<QString, u1> flagset;
// QMap<QString, QString> flagpairs;
 QString file_path = read_args(args);

 // QSet<QString> fs;
 //, flagset, flagpairs, fs);

 QFileInfo qfi(file_path);
 QString suffix = qfi.suffix();

 QString folder = qfi.absolutePath();

 GTagML_Project_Info* gpi = new GTagML_Project_Info(folder);

 if(suffix == "gt")
 {
  gpi->flags.manuscript_top_level_is_gt = true;
 }

 QString mt = current_flagpairs_.value(":manuscript");

 auto it = current_flagpairs_.find(":gt-copy-folder");
 if(it != current_flagpairs_.end())
   gpi->set_gt_copy_folder(it.value());


 GTagML_Folder fld(folder); //, file_path, mt);

 if(!mt.isEmpty())
   fld.set_man_path(mt);

 auto it1 = current_flagpairs_.find(":do-first");

 if(it1 != current_flagpairs_.end())
 {
  QString ff = it1.value();
  fld.set_first_file_path(ff);
 }
 else if(!current_flagset_.contains(":no-first"))
   fld.set_first_file_path(file_path);

 fld.set_project_info(gpi);

 gpi->set_user_data(this);

 fld.convert_all_files( &GTagML_DGH_Module::process_gtagml_file );

 check_post_processing_codes(*gpi);
 check_main_block_text_commands(*gpi);

 if(current_flagset_.contains(":setup-once"))
 {
  QString newfolder = make_inner_folder_from_file_name("setup", file_path);

  QString cp = copy_file_with_preliminary_suffix(file_path, "prep");

  GH_SDI_Document::setup_folder_from_template(cp, qfi.completeBaseName(),
    DEFAULT_SDI_FOLDER "/template", folder, newfolder);

  if(current_flagset_.contains(":setup-sdi"))
  {
   QDir new_sdi_dir(newfolder + "/sdi-prelatex");
   if(!new_sdi_dir.exists())
     if(new_sdi_dir.mkpath("."))
       qDebug() << "Made path: " << new_sdi_dir.absolutePath();

   QDir old_sdi_dir(newfolder + "/../sdi");
   {
    QFileInfoList qfil = old_sdi_dir.entryInfoList({"*.sdi-prelatex.ntxh"});
    for(QFileInfo qfi : qfil)
    {
     copy_file_to_folder(qfi.absoluteFilePath(), new_sdi_dir.absolutePath());
    }
   }

   QDir old_info_dir(newfolder + "/../info");
   {
    QFileInfoList qfil = old_info_dir.entryInfoList({"*.marks-summary.txt", "*.htxn.txt"});
    for(QFileInfo qfi : qfil)
    {
     copy_file_to_folder(qfi.absoluteFilePath(), new_sdi_dir.absolutePath());
    }
   }


   prepend_template_to_file(cp, DEFAULT_SDI_FOLDER "/prepend-once",
   {
    { "%CONSOLE", ROOT_FOLDER "/code/cpp/qmake-console/projects/gtagml/ngml-sdi-console"},
    { "%FILE", cp },
    { "%SDI-FOLDER", newfolder + "/sdi" },
    { "%SDI-PFOLDER", newfolder + "/sdi-prelatex" }
   });
  }
 }
}

void GTagML_DGH_Module::compile_gt_manuscript_file(QString args)
{
 qDebug() << "args = " << args;
 // // TODO ...
}

