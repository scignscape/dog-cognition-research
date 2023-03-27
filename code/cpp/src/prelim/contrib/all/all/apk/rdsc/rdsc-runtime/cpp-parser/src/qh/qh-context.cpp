

#include "qh-context.h"

#include <QDebug>

Qh_Context::Qh_Context()
 : qjc_(nullptr)
{

}

void Qh_Context::unhold_text()
{
 held_text_.clear();
}

void Qh_Context::hold_text(QString text)
{
 held_text_ += text;
}

QString Qh_Context::held_text()
{
 return held_text_;
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


void Qh_Context::run_qj_callback(QString content, QString rest_of_line, int i)
{
 qjc_(content, rest_of_line, i);
}
