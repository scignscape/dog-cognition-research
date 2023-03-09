
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include <QDebug>
#include <QFile>


#include "ngml-sdi/ngml-sdi-document.h"

#include <QDir>
#include <QDebug>

#include <QCommandLineParser>


#include "dgh-sdi/dgh-sdi-document.h"

USING_KANS(DGH)


#include "textio.h"
#include "get-cmdl.h"

USING_KANS(TextIO)
USING_KANS(Util)


int main(int argc, char* argv[])
{
 QString folder, file, outfile, pagesf, pfile, czfile;

// QStringList cmdl = get_cmdl(argc, argv, 2, {
//   {&folder, DEFAULT_SDI_FOLDER},
//   {&file, DEFAULT_SDI_FOLDER "/t1/t1.gt.sdi.ntxh"},
//   {&pfile, DEFAULT_SDI_FOLDER "/t1/t1.gt.sdi-prelatex.ntxh"},
//   {&czfile, {}}
//   });


// QStringList cmdl = get_cmdl(argc, argv, 2, {
//   {&folder, DEFAULT_SDI_FOLDER "/ctg/src/setup"},
//   {&file, DEFAULT_SDI_FOLDER "/ctg/out/ctg.sdi.ntxh"},
//   {&outfile, DEFAULT_SDI_FOLDER "/ctg/sdi-merge.ntxh"},
//   {&pagesf, DEFAULT_SDI_FOLDER "/ctg/out/pages"},
//   {&pfile, {}},
//   {&czfile, {}}
//   });

//
//
//
 QString paper_name; //= "ctg";
// QString paper_name = "icg";
// QString paper_name = "itm";

 if(argc >= 3)
 {
  paper_name = QString::fromLatin1(argv[2]);
 }
 else
 {
  paper_name = "ctg";
  // paper_name = "icg";
  // paper_name = "itm";
 }

 QStringList cmdl = get_cmdl(argc, argv, 3, {
   {&folder, QString(DEFAULT_SDI_FOLDER "/%1/src/setup").arg(paper_name)},
   {&file, QString(DEFAULT_SDI_FOLDER "/%1/out/%1.sdi.ntxh").arg(paper_name)},
   {&outfile, QString(DEFAULT_SDI_FOLDER "/%1/sdi-merge.ntxh").arg(paper_name)},
   {&pagesf, QString(DEFAULT_SDI_FOLDER "/%1/out/pages").arg(paper_name)},
   {&pfile, {}},
   {&czfile, {}}
   });



 QStringList prelatex_files;
 QStringList marks_files;
 QStringList htxn_files;

 QString cs;

 QDir qd(folder);
 if(!qd.cd("sdi"))
   qd.cd("sdi-prelatex");

 QStringList qsl = qd.entryList(QDir::Files);

 for(QString file : qsl)
 {
  if(file.endsWith("sdi-prelatex.ntxh"))
    prelatex_files.push_back(qd.absoluteFilePath(file));

  else if(file.endsWith("marks-summary.txt"))
    marks_files.push_back(qd.absoluteFilePath(file));

  else if(file.endsWith("htxn.txt"))
    htxn_files.push_back(qd.absoluteFilePath(file));

 }

 NGML_SDI_Document nsd(file, folder);

 nsd.set_pages_folder(pagesf);

 nsd.load_prelatex_files(prelatex_files);

 nsd.parse();

 nsd.merge_dgh();

 nsd.review_dgh();

 nsd.output_dgh(outfile);

 DGH_SDI_Document dsd;
 dsd.load_from_ntxh(outfile);

 dsd.review_dgh();

 nsd.output_pages(htxn_files, marks_files, outfile);

 QString zp = nsd.zip_path();

 if(!zp.isEmpty())
 {
  // // we've generated the zip file, now
   //   copy it for embedding ...
  copy_binary_file_to_folder(zp, folder);
 }

#ifdef HIDE

 nsd.set_copy_path(czfile);

 nsd.parse();

 nsd.output_pages();
#endif // HIDE

 return 0;
}

