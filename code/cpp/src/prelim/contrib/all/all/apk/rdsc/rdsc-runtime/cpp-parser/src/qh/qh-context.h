
#ifndef QH_CONTEXT__H
#define QH_CONTEXT__H



#include "qj-callback.h"

class Qh_Context
{

 Qj_Callback qjc_;

 QString held_text_;

public:

 Qh_Context();

 void set_qj_callback(Qj_Callback qjc);
 void run_qj_callback(QString content, QString rest_of_line, int i);

 void read_line(QString line);

 void hold_text(QString text);
 QString held_text();
 void unhold_text();

 void run_message(QString msg);

};

#endif // QH_CONTEXT__H
