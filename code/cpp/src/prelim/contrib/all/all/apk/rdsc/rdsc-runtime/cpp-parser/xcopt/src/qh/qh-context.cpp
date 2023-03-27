

#include "qh-context.h"

Qh_Context::Qh_Context()
 : qjc_(nullptr)
{

}

void Qh_Context::set_qj_callback(Qj_Callback qjc)
{
 qjc_ = qjc;
}


void Qh_Context::run_qj_callback(int i)
{
 qjc_(i);
}
