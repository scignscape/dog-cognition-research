
#include "dhax-pdf-view-dialog/paraviews/dhax-pdf-view-dialog.h"
#include "dhax-pdf-view-dialog/pleneviews/view-pdf-frame.h"
#include "dhax-pdf-view-dialog/subwindows/pdf-document-widget.h"

#include <QApplication>

//USING_QSNS(Cy_Mesh)

int main(int argc, char *argv[])
{
 QApplication qapp(argc, argv);
 DHAX_PDF_View_Dialog* pvd = new DHAX_PDF_View_Dialog(nullptr,
   ROOT_FOLDER "/../docs/ch6.pdf");
 pvd->show();
 qapp.exec();
 return 0;
}
