
#include "qh-cpp-parser/qh-cpp-document.h"

USING_KANS(Qh)

int main()
{
 Qh_CPP_Document qhd(ROOT_FOLDER "/../qh/test.qh");
 qhd.parse();

 return 0;

}
