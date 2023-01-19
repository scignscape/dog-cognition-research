//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef PIN__H
#define PIN__H

#include <functional>

template<typename T>
class _Pin_Holder
{
 T val_;
public:
 static T preinit_val(){ return -2; }
 _Pin_Holder(T v){val_ = v;}
 void preinit(){}
 void read(T v){val_ = v;}
 T& val(){ return val_; }
};

template<typename T, typename PH = _Pin_Holder<T>>
struct _pin_;

template<typename T, typename PH = _Pin_Holder<T>>
T& nip__(_pin_<T, PH>& _p);

template<typename T, typename PH>
struct _pin_
{
 PH ph;
 std::function<T()> expr;
 QVector<std::function<T(T&)>> exprs;
 T& nip(){ return nip__(*this); }
};

template<typename T, typename PH = _Pin_Holder<T>>
using pin = _pin_<T, PH>&;

#define pinned(ty ,sym) pin<ty> sym##_pinned

template<typename T, typename PH = _Pin_Holder<T>>
T& nip__(_pin_<T, PH>& _p)
{
 if(_p.exprs.isEmpty())
 {
  if(_p.expr)
  {
   _p.ph.read(_p.expr());
   _p.expr = nullptr;
  }
  return _p.ph.val();
 }
 else
 {
  T interim = _p.expr();
  _p.expr = nullptr;
  for(auto fn: _p.exprs)
  {
   interim = fn(interim);
  }
  _p.exprs.clear();
  _p.ph.read(interim);
  return _p.ph.val();
 }
}

//template<typename T, typename PH>
//T& nip__(_pin_<T, PH>& _p)
//{
// return nip(_p);
//}

#define nip(sym) nip__(sym##_pinned)

#define _pre(v) {v, {[&](){

#define _tobe(e) return e;}}}

#define _pre_(ty) _pre(_Pin_Holder<ty>::preinit_val())

#define _pin(ty, sym) _pin_<ty> sym##_pinned _pre_(ty)

#define _nip(sym) sym##_pinned <<= [&](decltype(nip__(sym##_pinned)) sym)

#define _repin(sym) sym##_pinned << [&](decltype(nip__(sym##_pinned)) sym) {

#define _as(e) return e;}

#define _unpin(sym) decltype(nip__(sym##_pinned)) sym = nip__(sym##_pinned)

template<typename T, typename F>
void operator <<= (_pin_<T>& _p, F fn)
{
 fn(nip__(_p));
}


template<typename T, typename F>
void operator << (_pin_<T>& _p, F fn)
{
 if(_p.expr)
   _p.exprs << fn;
 else
   _p.ph.read(fn(_p.ph.val()));
}

#endif // PIN__H


/*/ examples:

#include "pin.h"

void test(pinned(int ,x))
{
 _repin(x) _as(x + 8);
 qDebug() << "x = " << nip(x);
}

void demo1()
{
 int a = 9;
 _pin(int ,x) _tobe(a + 3);
 a += 20;
 test(PINNED_x);
}

void demo2()
{
 int a = 9;

 _pin(int ,x) _tobe(a + 3);

 int y = nip(x);
 _repin(x) _as(x + 5);

 qDebug() << "y = " << y;
 qDebug() << "x = " << nip(x);
}

void demo3()
{
 int a = 9;

 _pin(int ,x) _tobe(a + 3);
 _pin(int ,y) _tobe(a + 4);

 _repin(x) _as(x + 5);

 _repin(x)
   x += nip(y);
 _as(x);

 _nip(x)
 {
  _nip(y)
  {
   qDebug() << "y = " << y;
   qDebug() << "x = " << x;
  };
 };
}

void test1(pinned(int ,x))
{
 _unpin(x);
 x += 50;
 qDebug() << "x1 = " << x;
}

void demo4()
{
 int a = 9;
 _pin(int ,x) _tobe(a + 3);
 a += 20;
 test1(PINNED_x);

 qDebug() << "x = " << nip(x);
}

int main(int argc, char *argv[])
{
 demo1();
 demo2();
 demo3();
 demo4();

 return 0;
}

*/
