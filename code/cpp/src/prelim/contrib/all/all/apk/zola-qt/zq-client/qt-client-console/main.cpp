
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)



#include "qt-ember-hybrid/qh-web-view-dialog.h"

//?#include "zq-client/zq-web-view-dialog.h"

int main(int argc, char *argv[])
{
 QApplication qapp(argc, argv);

// ZQ_Web_View_Dialog dlg(nullptr);
 QH_Web_View_Dialog dlg(nullptr);

 dlg.show();

 return qapp.exec();

}

