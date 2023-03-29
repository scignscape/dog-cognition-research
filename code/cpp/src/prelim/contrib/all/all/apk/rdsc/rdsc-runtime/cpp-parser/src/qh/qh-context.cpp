

#include "qh-context.h"

#include <QDebug>

#include "textio.h"

Qh_Context::Qh_Context()
 : qjc_(nullptr)
{

}

void Qh_Context::enter_context(QString context_string, u2 line_number)
{
 output("@at %1: %2\n"_qt.arg(line_number).arg(context_string));
}

void Qh_Context::enter_context(u2 line_number)
{
 enter_context(held_text_, line_number);
}


void Qh_Context::leave_context(QString context_string, u2 line_number)
{
 output("@lv %1: %2\n"_qt.arg(line_number).arg(context_string));
}

void Qh_Context::leave_context(u2 line_number)
{
 leave_context(held_text_, line_number);
}


void Qh_Context::save_output()
{
 KA::TextIO::save_file(output_file_, output_text_);
}

void Qh_Context::output(QString text)
{
 output_text_ += text;
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


void Qh_Context::read_line(QString text, u2 line_number)
{
 output("@ln %1: %2\n"_qt.arg(line_number).arg( text));
 //qDebug() << "line = " << line;
}

void Qh_Context::read_line(u2 line_number)
{
 read_line(held_text_, line_number);
}


void Qh_Context::set_qj_callback(Qj_Callback qjc)
{
 qjc_ = qjc;
}


void Qh_Context::run_qj_callback(QString content, QString rest_of_line, int i)
{
 qjc_(content, rest_of_line, i);
}
