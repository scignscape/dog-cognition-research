
#ifndef QH_CONTEXT__H
#define QH_CONTEXT__H

#include "accessors.h"

#include "global-types.h"

#include "qj-callback.h"

class Qh_Context
{

 Qj_Callback qjc_;

 QString held_text_;

 QString output_file_;
 QString output_text_;


public:

 Qh_Context();

 ACCESSORS(QString ,output_file)

 void enter_context(QString context_string, u2 line_number);
 void enter_context(u2 line_number);

 void leave_context(QString context_string, u2 line_number);
 void leave_context(u2 line_number);

 void set_qj_callback(Qj_Callback qjc);
 void run_qj_callback(QString content, QString rest_of_line, int i);

 void output(QString text);
 void save_output();

 void read_line(QString text, u2 line_number);
 void read_line(u2 line_number);

 void hold_text(QString text);
 QString held_text();
 void unhold_text();

 void run_message(QString msg);

};

#endif // QH_CONTEXT__H
