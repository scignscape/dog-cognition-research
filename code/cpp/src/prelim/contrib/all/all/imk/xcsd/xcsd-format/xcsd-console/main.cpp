
//          Copyright Nathaniel Christen 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include "xcsd-1d/vec1d.h"
#include "xcsd-1d/stk1d.h"
#include "xcsd-1d/que1d.h"
#include "xcsd-1d/deq1d.h"
#include "xcsd-1d/dsk1d.h"
#include "xcsd-1d/arr1d.h"

#include "xcsd/mat2sd3x3.h"


#include <QDebug>

USING_XCNS(XCSD)

int main9(int argc, char **argv)
{

}

int main8(int argc, char **argv)
{
 Que1d<int> q1d;

 q1d.set_default <= defzfn(int);

 qDebug() << q1d.head();
 qDebug() << q1d.tail();

 return 0;
}

int main7(int argc, char **argv)
{
 Deq1d<int> d1d;

 d1d.push_back(7);
 d1d.push_back(9);

 d1d._each([](int& i)
 {
  qDebug() << i;
 });

 d1d.pop_front();

 d1d._each([](int& i)
 {
  qDebug() << i;
 });



 qDebug() << "ok";
 return 0;
}

int main6(int argc, char **argv)
{
 Que1d<int> q1d;

 q1d.enqueue(7);
 q1d.enqueue(9);
 q1d.enqueue(17);

 q1d._each([](int& i)
 {
  qDebug() << i;
 });

 q1d.dequeue();

 q1d._each([](int& i)
 {
  qDebug() << i;
 });

 qDebug() << "ok";
 return 0;
}


int main5(int argc, char **argv)
{
 Stk1d<int> s1d(5);

 s1d.push(7);
 s1d.push(9);
 s1d.push(27);
 s1d.push(37);
 s1d.push(39);
 s1d.push(47);
 s1d.push(9);
 s1d.push(27);
 s1d.push(37);
 s1d.push(39);
 s1d.push(47);

 s1d._each([](int& i)
 {
  qDebug() << i;
 });

 qDebug() << "...";

 for(int i  = 0; i < 6; ++i)
  s1d.pop();

 s1d._each([](int& i)
 {
  qDebug() << i;
 });

 qDebug() << "ok";
 return 0;
}

int main4a(int argc, char **argv)
{
 Dsk1d<int> d1d;

 d1d.push_back(7);
 d1d.push_back(9);

 d1d.push_front(17);
 d1d.push_front(23);
 d1d.push_front(45);

 d1d.reach <<= [](int& i, quint16 ix)
 {
  qDebug() << ix << ": " << i;
  return-1;
 };

 qDebug() << "ok";

 return 0;
}


int main4(int argc, char **argv)
{
 Deq1d<int> d1d;

 d1d.push_back(7);
 d1d.push_back(9);

 d1d.pop_front();
 d1d.push_front(17);

 d1d.reach <<= [](int& i, quint16 ix)
 {
  qDebug() << ix << ": " << i;
  return-1;
 };

 qDebug() << "ok";

 return 0;
}

int main3(int argc, char **argv)
{
 Que1d<int> q1d;

 q1d.enqueue(7);
 q1d.enqueue(9);
 q1d.enqueue(17);

 q1d.each <<= [](int& i, quint16 ix)
 {
  qDebug() << i;
  return-1;
 };

 qDebug() << "ok";

 qDebug() << q1d.head();
 qDebug() << q1d.tail();

 return 0;
}

int main2(int argc, char **argv)
{
 Stk1d<int> s1d;
 s1d.set_default <= defzfn(int);

 s1d.push(7);
 s1d.push(9);
 s1d.push(17);

 s1d.each <<= [](int& i, quint16 ix)
 {
  qDebug() << i;
  return-1;
 };

 qDebug() << s1d.top();
 qDebug() << s1d.bottom();

 qDebug() << "ok";
 return 0;
}

#include <QColor>


int main13(int argc, char **argv)
{

 u2 min = 0;
 u2 max = 256;

 u2 hue = 0;

 for(u2 s = min; s < max; ++s)
 {
  for(u2 v = min; v < max; ++v)
  {
   QColor color;
   color.setHsv(hue, s, v);

//   QColor color1(color.red(), color.green(), color.blue());

   int _h, _s, _v;

   color.getHsv(&_h, &_s, &_v);

   qDebug() << "s = " << s << ", _s = " << _s << ", v = " << v << ", _v = " << _v;


  }
 }
}


int main(int argc, char **argv)
{

 u2 min = 0;
 u2 max = 256;


 u2 target_hue = 0;

 QMap<u2, QMap<QVector<s1>, u4>> dh;
 QMap<u1, QMap<QVector<s1>, u4>> ds;
 QMap<u1, QMap<QVector<s1>, u4>> dv;

 QMap<s1, u4> rcount, gcount, bcount;

// QMap<s1, u4> rcount, gcount, bcount;
// QMap<u2, u4> hcounts;
// QMap<u1, QMap<u1, u2> > outsv;
// QMap<u1, QMap<u1, u2> > outvs;

 u4 diff_count = 0;
 u1 diff_max = 0;

 for(u2 r = min; r < max; ++r)
 {
  for(u2 g = min; g < max; ++g)
  {
   for(u2 b = min; b < max; ++b)
   {
    QColor color(r, g, b);
    int h, s, v;
    color.getHsv(&h, &s, &v);

    u1 sv = qRound((s * v)/255.);

    //double ss = sv * part;
    double ss = (255. * sv) / v;
    u1 sss = qRound(ss);

    QColor color2;
    color2.setHsv(h, sss, v);

    if( (color.red() != color2.red()) || (color.green() != color2.green())
        || (color.blue() != color2.blue()) )
    {
     s1 diff = color.red() - color2.red() + color.green()
       - color2.green() + color.blue() != color2.blue();

     s1 rdiff = color.red() - color2.red();
     if(rdiff != 0)
       ++rcount[rdiff];

     s1 gdiff = color.green() - color2.green();
     if(gdiff != 0)
       ++gcount[gdiff];

     s1 bdiff = color.blue() - color2.blue();
     if(bdiff != 0)
       ++bcount[bdiff];

     QVector<s1> diffs {rdiff, gdiff, bdiff};

     ++dh[h][diffs];
     ++ds[s][diffs];
     ++dv[v][diffs];

//     ++dh[h][0];
//     ++ds[s][0];
//     ++dv[v][0];
    }



    if(sss != s)
    {
     ++diff_count;
     if(diff_max < qAbs(sss - s))
       diff_max = qAbs(sss - s);

     QColor c1;
     c1.setHsv(target_hue, s, v);
     QColor c2;
     c2.setHsv(target_hue, sss, v);

     if( (c1.red() != c2.red()) || (c1.green() != c2.green()) || (c1.blue() != c2.blue()) )
     {
      qDebug() << "\nr = " << c1.red() << "  g = " << c1.green() << "  b = " << c1.blue();
      qDebug() << "r = " << c2.red() << "  g = " << c2.green() << "  b = " << c2.blue();
     }


    }


   }
  }
 }

 for(u2 h = 0; h < 360; ++h)
 {
  qDebug() << "\nh = " << h;
  QMapIterator<QVector<s1>, u4> it(dh[h]);
  while(it.hasNext())
  {
   it.next();
   qDebug() << " d = " << it.value()
            << " (" << it.key()[0] << "," << it.key()[1]
            << "," << it.key()[2] << ")";
  }
 }

 for(u2 s = 0; s < 256; ++s)
 {
  qDebug() << "\ns = " << s;
  QMapIterator<QVector<s1>, u4> it(ds[s]);
  while(it.hasNext())
  {
   it.next();
   qDebug() << " d = " << it.value()
            << " (" << it.key()[0] << "," << it.key()[1]
            << "," << it.key()[2] << ")";
  }
//  for(s1 d = -5; d <= 5; ++d)
//  {
//   qDebug() << " d = " << d << " (" << ds[s][d] << ")";
//  }
 }

 for(u2 v = 0; v < 256; ++v)
 {
  qDebug() << "\nv = " << v;
  QMapIterator<QVector<s1>, u4> it(dv[v]);
  while(it.hasNext())
  {
   it.next();
   qDebug() << " d = " << it.value()
            << " (" << it.key()[0] << "," << it.key()[1]
            << "," << it.key()[2] << ")";
  }

 }

 qDebug() << "rcount = " << rcount;
 qDebug() << "gcount = " << gcount;
 qDebug() << "bcount = " << bcount;

}


int main15(int argc, char **argv)
{

 u2 min = 0;
 u2 max = 256;


 u2 target_hue = 0;

// QMap<s1, u4> rcount, gcount, bcount;
// QMap<u2, u4> hcounts;
// QMap<u1, QMap<u1, u2> > outsv;
// QMap<u1, QMap<u1, u2> > outvs;

 u4 diff_count = 0;
 u1 diff_max = 0;

 for(u2 r = min; r < max; ++r)
 {
  for(u2 g = min; g < max; ++g)
  {
   for(u2 b = min; b < max; ++b)
   {
    QColor color(r, g, b);
    int h, s, v;
    color.getHsv(&h, &s, &v);

    u1 sv = qRound((s * v)/255.);

    //double ss = sv * part;
    double ss = (255. * sv) / v;
    u1 sss = qRound(ss);

    if(sss != ss)
    {
     ++diff_count;
     if(diff_max < qAbs(sss - s))
       diff_max = qAbs(sss - s);

     QColor c1;
     c1.setHsv(target_hue, s, v);
     QColor c2;
     c2.setHsv(target_hue, sss, v);

     if( (c1.red() != c2.red()) || (c1.green() != c2.green()) || (c1.blue() != c2.blue()) )
     {
      qDebug() << "\nr = " << c1.red() << "  g = " << c1.green() << "  b = " << c1.blue();
      qDebug() << "r = " << c2.red() << "  g = " << c2.green() << "  b = " << c2.blue();
     }


    }


   }
  }
 }

 qDebug() << "diff count = " << diff_count;
 qDebug() << "diff max = " << diff_max;

}


int main14(int argc, char **argv)
{

 u2 min = 0;
 u2 max = 256;


 u2 target_hue = 0;

 QMap<s1, u4> rcount, gcount, bcount;

 QMap<u2, u4> hcounts;

 QMap<u1, QMap<u1, u2> > outsv;
 QMap<u1, QMap<u1, u2> > outvs;

 for(u2 r = min; r < max; ++r)
 {
  for(u2 g = min; g < max; ++g)
  {
   for(u2 b = min; b < max; ++b)
   {
    QColor color(r, g, b);
    int h, s, v;
    color.getHsv(&h, &s, &v);

    ++hcounts[h];

    if(h == target_hue)
    {
     ++outsv[s][v];
     ++outvs[v][s];
    }

   }
  }
 }

// for(u2 s = 0; s < 256; ++s)
// {
//  if(!outsv.contains(s))
//    continue;
//  qDebug() << "\ns = " << s;
//  bool last_in = false;
//  for(u2 v = 0; v < 256; ++v)
//  {
//   if(!outsv[s].contains(v))
//   {
//    last_in = false;
//    continue;
//   }
//   if(!last_in)
//   {
//    last_in = true;
//    qDebug() << "\n";
//   }
//   qDebug() << "  v = " << v << "(" << outsv[s][v] << ")";
//  }
// }

// for(u2 v = 4; v < 5; ++v)


 u4 ecount = 0;

 for(u2 v = 0; v < 256; ++v)
 {
  if(!outvs.contains(v))
    continue;
  qDebug() << "\nv = " << v;
  u1 count = 0;

//  double part = (255. / v);
//  u1 p = qRound(part);

//  qDebug() << "part = " << part;

  for(u2 s = 0; s < 256; ++s)
  {
   if(!outvs[v].contains(s))
     continue;
   ++count;
//   double dsv =  (((double)(s * v)) / 255);
//   u1 sv = qRound(dsv);

//   double dsv =  (((double)(s * v)) / 255);
   u1 sv = qRound((s * v)/255.);

   //double ss = sv * part;
   double ss = (255. * sv) / v;
   u1 sss = qRound(ss);

   s1 diff = sss - s;
   if(diff != 0)
   {
     ++ecount;
     qDebug() << " ! ";

    QColor c1;
    c1.setHsv(target_hue, s, v);
    QColor c2;
    c2.setHsv(target_hue, sss, v);

    qDebug() << "r = " << c1.red() << "  g = " << c1.green() << "  b = " << c1.blue();
    qDebug() << "r = " << c2.red() << "  g = " << c2.green() << "  b = " << c2.blue();

   }

//   double vv = (255.) * ((double)sv / v);
//   u1 vvv = qRound(vv);

//   s1 vvdiff = vvv - s;
//   if(vvdiff != 0)
//     qDebug() << " ? ";


   qDebug() << " " << count << "-  s = " << s << "(" << outvs[v][s] << ")";
   qDebug() << "    sv = " << sv << " - ss = "
            << ss << " - sss = " << sss << " - d = " << diff;
//            << " - vvv = " << vvv << " - vvdiff = " << vvdiff;
  }
 }

 qDebug() << "\n\necount = " << ecount;

// for(u2 h = 0; h < 360; ++h)
// {
//  qDebug() << "h = " << h << ": " << hcounts[h];
// }


}


int main12(int argc, char **argv)
{


 //QMap<QColor, QVector<quint8>> res;

 u2 min = 0;
 u2 max = 256;

 QMap<s1, u4> rcount, gcount, bcount;

 for(u2 r = min; r < max; ++r)
 {
  for(u2 g = min; g < max; ++g)
  {
   for(u2 b = min; b < max; ++b)
   {
    u1 diffs = 0;

    QColor color(r, g, b);
    int h, s, v;
    color.getHsv(&h, &s, &v);

    QColor color1;
    color1.setHsv(h, s, v);

    s1 rdiff = color.red() - color1.red();
    if(rdiff != 0)
    {
      ++rcount[rdiff];
      ++diffs;
    }

    s1 gdiff = color.green() - color1.green();
    if(gdiff != 0) { ++diffs;
      ++gcount[gdiff]; }

    s1 bdiff = color.blue() - color1.blue();
    if(bdiff != 0){ ++diffs;
      ++bcount[bdiff]; }

    if(diffs > 1)
      qDebug() << "diffs: " << diffs;
   }
  }
 }

 qDebug() << "rcount = " << rcount;
 qDebug() << "gcount = " << gcount;
 qDebug() << "bcount = " << bcount;



}

int main11(int argc, char **argv)
{
 mArr1d<int> a1d(4);

 a1d.set_default <= defzfn(int);

 qDebug() << a1d.first();


 a1d.push_back(7);
 a1d.push_back(9);
 a1d.push_back(17);
 a1d.push_back(27);
 a1d.push_back(29);
 a1d.push_back(37);

 a1d.each <= [](int& i, quint16 index)
 {
  qDebug() << index;
  qDebug() << i;
 };

 a1d.reach <<= [](int& i, quint16 index)
 {
  if(index == 3)
    return-0;
  qDebug() << i;
  return-1;
 };

 qDebug() << "ok";

 qDebug() << a1d.last();
 qDebug() << a1d.first();

 return 0;
}


int main1(int argc, char **argv)
{
 Vec1d<int> v1d;

 v1d.set_default <= defzfn(int);

 qDebug() << v1d.first();

 v1d.push_back(7);
 v1d.push_back(9);
 v1d.push_back(17);

 v1d.each <= [](int& i, quint16 index)
 {
  qDebug() << index;
  qDebug() << i;
 };

 v1d.reach <<= [](int& i, quint16 index)
 {
  if(index == 3)
    return-0;
  qDebug() << i;
  return-1;
 };

 qDebug() << "ok";

 qDebug() << v1d.last();
 qDebug() << v1d.first();

 return 0;
}
