
#ifndef QH_CONTEXT__H
#define QH_CONTEXT__H



#include "qj-callback.h"

class Qh_Context
{

 Qj_Callback qjc_;

public:

 Qh_Context();

 void set_qj_callback(Qj_Callback qjc);
 void run_qj_callback(QString content, int i);

 void read_line(QString line);

 void run_message(QString msg);

};

#endif // QH_CONTEXT__H
