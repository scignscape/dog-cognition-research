

#include "qh-context.h"

#include <QDebug>

Qh_Context::Qh_Context()
 : qjc_(nullptr)
{

}


void Qh_Context::run_message(QString msg)
{
 qDebug() << "msg = " << msg;
}


void Qh_Context::read_line(QString line)
{
 qDebug() << "line = " << line;
}


void Qh_Context::set_qj_callback(Qj_Callback qjc)
{
 qjc_ = qjc;
}


void Qh_Context::run_qj_callback(QString content, int i)
{
 qjc_(content, i);
}
