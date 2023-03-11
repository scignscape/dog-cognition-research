
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)



#include "rdsc-qh/qh-web-view-dialog.h"

#include "kans.h"

USING_KANS(RdSC)

int main(int argc, char *argv[])
{
 QApplication qapp(argc, argv);

 QH_Web_View_Dialog dlg(nullptr);

 dlg.show();

 return qapp.exec();

}

