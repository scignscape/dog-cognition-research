
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "sv-wrapper.h"

#include "conversions.h"

#include "tkrzw/tkrzw_dbm.h"

USING_KANS(DGDB)


QString SV_Wrapper::qstring()
{
 return QString::fromStdString(std::string{value});
}

void SV_Wrapper::noop()
{
 value = tkrzw::DBM::RecordProcessor::NOOP;
}

n8 SV_Wrapper::to_n8()
{
 QByteArray qba(value.data(), value.size());
 return qba_to_n8(qba); //tkrzw::StrToIntBigEndian(value);
}

void SV_Wrapper::confirm()
{
 value = std::string_view(qba->data(), qba->size());
}

void SV_Wrapper::from_qstring(QString str)
{
 *qba = str.toUtf8(); confirm();
}

QString SV_Wrapper::qstring_utf8()
{
 QByteArray qba(value.data(), value.size());
 return QString::fromUtf8(qba);
}

void SV_Wrapper::from_n8(n8 v)
{
 *qba = n8_to_qba(v); confirm();
 //value = std::string_view(qba.data(), qba.size());// tkrzw::IntToStrBigEndian(v);
// QByteArray qba1 = n8_to_qba(v);
// QByteArray qba2 = n8_to_qba(v);

}
