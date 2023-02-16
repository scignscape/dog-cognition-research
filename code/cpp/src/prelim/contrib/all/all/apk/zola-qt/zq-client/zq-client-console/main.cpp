
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "zq-client/zq-web-view-dialog.h"

#include "qmt-client/main-window.h"

int main(int argc, char *argv[])
{
 QApplication qapp(argc, argv);

 ZQ_Web_View_Dialog dlg(nullptr);

 Lanternfly_Main_Window w;
 w.show();



 dlg.set_zoom_or_coordinates_changed_callback([&w](r8 z, r8 lat, r8 lon)
   {
    qDebug() << "z = " << z << "lat = " << lat << " long = " << lon;
    w.center_on(lon, lat, (u1) z + 2);
   });


// dlg.connect(&dlg, &ZQ_Web_View_Dialog::zoom_or_coordinates_changed, [&w](r8 z, r8 lat, r8 lon)
// {
//  qDebug() << "z = " << z << "lat = " << lat << " long = " << lon;

//  w.center_on(lon, lat, (u1) z + 2);
// });

 dlg.show();



 return qapp.exec();
}
