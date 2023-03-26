
#include <QString>

#include <functional>

class Qh_Context
{
 using Qj_Callback = std::function<void(int)>;

 Qj_Callback qjc_;

public:

 Qh_Context();

 void set_qj_callback(Qj_Callback qjc);
 void run_qj_callback(int i);


};
