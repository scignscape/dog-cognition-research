
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "gt-module-ir/gt-module-ir.h"


#include <QDebug>

#include "textio.h"

#include "get-cmdl.h"

USING_KANS(TextIO)
USING_KANS(Util)

USING_KANS(DGH)


int main1(int argc, char *argv[])
{
 for(quint8 i = 0, ok = true; ok; ok = ((quint16) i) + 1 < 256, ++i)
 {
  //ok = (((quint16) i) + 1) < 256;
  // //  loop body ...
  //ok = ;
  qDebug() << "i = " << i;


 }
}


int main(int argc, char *argv[])
{
 GT_Module_IR mir;

 QString paper_name;

 QStringList cmds = get_cmdl(argc, argv);

// mir.read_lines(QString(R"(
//   .; the folder is just outside the archive
//      but it is copied in @/dev/documents/ctg ...
//    ;.

//  gt-compile-file  $  %1/test/src/t1.gt
//    ;.
//    )").arg(DEMO_DOCUMENT_FOLDER) );

 if(cmds.size() >= 3)
 {
  paper_name = cmds.at(2);
 }
 else
 {
  paper_name = "ctg";
  // paper_name = "icg";
  // paper_name = "itm";
 }

 // //  Here in case need to override the cmdline ...
 // paper_name = "ctg";
 // paper_name = "icg";
 // paper_name = "itm";

 // //  special for i4
 //QString folder = DEMO_DOCUMENT_FOLDER "/i4";
 //?

 QString folder = DEMO_DOCUMENT_FOLDER "/pjos";

 //?
//paper_name = "ch20";
 //?paper_name = "ch21";
 // paper_name = "ch22";
 //paper_name = "ch23";
 //
 // paper_name = "ch24";
 //  paper_name = "ch2";

 paper_name = "chomsky";


 mir.read_lines(QString(R"(
  .; the folder is just outside the archive
     but it is copied in @/dev/documents/" + paper_name ...
   ;.

 gt-compile-manuscript  $  :no-first  :info-path
    :setup-once  :setup-sdi
      %1/%2/src/%2.tex
    :manuscript  %1/%2/manuscript
    :gt-copy-folder  %1/%2/gt-copy
    :do-first  intro.gt
   ;.
   )").arg(folder).arg(paper_name) );

 mir.run_lines();
 return 0;
}


