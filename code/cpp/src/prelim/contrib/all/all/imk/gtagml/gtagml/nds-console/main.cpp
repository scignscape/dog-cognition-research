
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include <QDebug>
#include <QFile>


#include "ngml-dgh-sdi/nds-project.h"

#include <QDir>
#include <QDebug>

#include <QCommandLineParser>


#include "dgh-sdi/dgh-sdi-document.h"

USING_KANS(NGML)


#include "textio.h"
#include "get-cmdl.h"

USING_KANS(TextIO)
USING_KANS(Util)


int main(int argc, char* argv[])
{
 QString paper_short_name; //= "ctg";
// QString paper_short_name = "icg";
// QString paper_short_name = "itm";

 if(argc >= 3)
 {
  paper_short_name = QString::fromLatin1(argv[2]);
 }
 else
 {
  paper_short_name = "ctg";
  // paper_short_name = "icg";
  // paper_short_name = "itm";
 }

 QString project_folder = QString(DEFAULT_SDI_FOLDER "/%1").arg(paper_short_name);
 QString setup_folder = QString("%1/src/setup").arg(project_folder);


 NDS_Project nsp(paper_short_name, project_folder, setup_folder);

 nsp.locate_files();
 nsp.init_ngml_document();
 nsp.init_dgh_document();


 return 0;
}

