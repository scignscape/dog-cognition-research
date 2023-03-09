
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "dhax-float-location-2d.h"

#include <QDebug>


DHAX_Float_Location_2d::DHAX_Float_Location_2d(float c1, float c2)
 :  c1_(c1), c2_(c2)
{

}

void DHAX_Float_Location_2d::check_decode8(n8 compressed)
{
 DHAX_Float_Location_2d temp(0,0);
 temp.decode8(compressed);
 if(c1_ == temp.c1_ && c2_ == temp.c2_)
   qDebug() << "Decoded: OK";
 else
   qDebug() << "Decoded: Error";
}

void DHAX_Float_Location_2d::decode8(n8 compressed)
{
 unsigned const char* const pr = (unsigned const char*)&compressed;
 unsigned char* const pf1 = (unsigned char*)&c1_;
 unsigned char* const pf2 = (unsigned char*)&c2_;
 for(u1 i = 0; i < 4; ++i)
 {
  pf1[i] = pr[i];  pf2[i] = pr[i + 4];
 }

}


n8 DHAX_Float_Location_2d::encode8()
{
 n8 result;
 unsigned char* const pr = (unsigned char*)&result;
 unsigned char const* const pf1 = (unsigned char const *)&c1_;
 unsigned char const* const pf2 = (unsigned char const *)&c2_;
 for(u1 i = 0; i < 4; ++i)
 {
  pr[i] = pf1[i]; pr[i + 4] = pf2[i];
 }
 return result;
}


QString DHAX_Float_Location_2d::to_string()
{
 return QString("%1;%2").arg(c1_).arg(c2_);
}

QPoint DHAX_Float_Location_2d::to_qpoint()
{
 return { (int) c1_, (int) c2_ };
}

//void DHAX_Location_2d::read_string(QString str, QVector<n8>& locations)
//{
// QStringList parts = str.split(":");
// for(QString part : parts)
// {
//  QStringList subparts = part.split(";");
//  if(subparts.size() < 2)
//    continue; // malformed ...

//  DHAX_Location_2d* loc = new DHAX_Location_2d(subparts[0].toInt(), subparts[1].toInt());

//  locations.push_back((n8) loc);
// }
//}

