
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

#include "xcsd-1d/hive-structure.h"


#include <QDebug>

#include <QVector>

USING_XCNS(XCSD)

int main1(int argc , char **argv)
{
 Vec1d<int> vec(6, 3);

 QVector<int> test {2, 3, 4, 5, 6, 7};

 vec.resize(11);

 vec.each <<= [](int& i, s2 ix)
 {
  i = ix - 1;
  return-1;
 };
 qDebug() << vec.to_qstring(QString_number(int));

 QVector<QPair<int*, s2>> breakdown;
 if(int* it = vec.contiguous(4, 9, breakdown))
 {
  std::copy(test.begin(), test.end(), it);
 }
 else
 {
  auto it1 = test.begin();
  for(QPair<int*, s2> pr : breakdown)
  {
   std::copy(it1, it1 + pr.second, pr.first);
   it1 += pr.second;
  }
 }

 qDebug() << vec.to_qstring(QString_number(int));

 return 0;
}

int main01(int argc , char **argv)
{
 Vec1d<int> vec(10, 7);

 QVector<int> test1 {104, 105, 106, 107, 108, 109};
 QVector<int> test2 {219, 220};
 QVector<int> test3 {330, 331};
 QVector<int> test3a {1330, 1331, 1332, 1333, 1334, 1335, 1336, 1337, 1338, 1339, 1340};
 QVector<int> test4 {438, 439, 440, 441, 442, 443, 444,
                     445, 446, 447, 448, 449, 450, 451};
 QVector<int> test5 ;

 vec.resize(60);

 vec.each <<= [](int& i, s2 ix)
 {
  i = ix - 1;
  return-1;
 };
 qDebug() << vec.to_qstring(QString_number(int));

 if(int* it = vec.contiguous(4, 9))
 {
  std::copy(test1.begin(), test1.end(), it);
 }
 qDebug() << "test 1: " << vec.to_qstring(QString_number(int));

 {
  QVector<QPair<int*, s2>> breakdown;
  if(int* it = vec.contiguous(19, 20, breakdown))
  {
   //std::copy(test.begin(), test.end(), it);
  }
  else
  {
   auto it1 = test2.begin();
   for(QPair<int*, s2> pr : breakdown)
   {
    std::copy(it1, it1 + pr.second, pr.first);
    it1 += pr.second;
   }
  }
 }
 qDebug() << "test 2: " << vec.to_qstring(QString_number(int));

 {
  QVector<QPair<int*, s2>> breakdown;
  if(int* it = vec.contiguous(30, 31, breakdown))
  {
   std::copy(test3.begin(), test3.end(), it);
  }
  else
  {
   auto it1 = test3.begin();
   for(QPair<int*, s2> pr : breakdown)
   {
    std::copy(it1, it1 + pr.second, pr.first);
    it1 += pr.second;
   }
  }
 }
 qDebug() << "test 3: " <<  vec.to_qstring(QString_number(int));

 {
  QVector<QPair<int*, s2>> breakdown;
  if(int* it = vec.contiguous(38, 51, breakdown))
  {
   //std::copy(test.begin(), test.end(), it);
  }
  else
  {
   auto it1 = test4.begin();
   for(QPair<int*, s2> pr : breakdown)
   {
    std::copy(it1, it1 + pr.second, pr.first);
    it1 += pr.second;
   }
  }
 }
 qDebug() << "test 4: " <<  vec.to_qstring(QString_number(int));


 {
  QVector<QPair<int*, s2>> breakdown;
  if(int* it = vec.contiguous(30, 40, breakdown))
  {
   //std::copy(test.begin(), test.end(), it);
  }
  else
  {
   auto it1 = test3a.begin();
   for(QPair<int*, s2> pr : breakdown)
   {
    std::copy(it1, it1 + pr.second, pr.first);
    it1 += pr.second;
   }
  }
 }
 qDebug() <<  "test 3a: " << vec.to_qstring(QString_number(int));

 test5.resize(17);

 {
  QVector<QPair<int*, s2>> breakdown;
  if(int* it = vec.contiguous(5, 21, breakdown))
  {
   std::copy(it, it + 21, test1.begin());
  }
  else
  {
   auto it1 = test5.begin();
   for(QPair<int*, s2> pr : breakdown)
   {
    std::copy(pr.first, pr.first + pr.second, it1);
    it1 += pr.second;
   }
  }
 }
 qDebug() << "test5 = " << test5;
}

enum class t_e { s1, s2, s3 };

class t_c
{
public:

 int s1, s2, s3;

 t_c(int ss) : s1(1), s2(2), s3(ss) {}


};

int main08(int argc , char **argv)
{
 u2 enc = encode_fallback_mitigation_flags(
   Out_of_Bounds_Resolution_Flags::Call_Default_Constructor_if_Possible);

//   Out_of_Bounds_Resolution_Flags::Call_Default_Constructor_if_Possible);

 qDebug() << "enc = " << enc;

 Out_of_Bounds_Resolution_Flags f1;
 Out_of_Bounds_Resolution_Flags f2;
 Out_of_Bounds_Resolution_Flags f3;
 Out_of_Bounds_Resolution_Flags f4;

 u1 count = decode_fallback_mitigation_flags(enc, f1, f2, f3, f4);

 qDebug() << "f1 = " << (u2) f1;
 qDebug() << "f2 = " << (u2) f2;
 qDebug() << "f3 = " << (u2) f3;
 qDebug() << "f4 = " << (u2) f4;

 return 0;
}

int main(int argc , char **argv)
{
 Vec1d<int> vec(5, 2);


 int d = 56;

 Vec1d<int>::static_default_value(&d);

 vec.set_default <= [](int** def)
 {
  static int _def = 44;
  *def = &_def;
 };

 //vec.first() = 7;
// vec.push_back(76);

 u2 enc = on_out_of_bounds(//
  // Out_of_Bounds_Resolution_Flags::Use_Default_Value_Pointer //,
   //_oob_Call_Default_Value_Function
    // _oob_Call_Default_Constructor_if_Possible
                           //,
                           _oob_Use_Alternate_Fallback_Index
                           )
   (
    _oob_Use_Default_Value_Pointer
//    _oob_Call_Default_Value_Function
    )
   [_oob_Automatic_Rebound
//   |
//    _oob_Fallback_Automatic_Rebound
//    |
//    _oob_Accept_Initialize_to_Zero
   ]
   ;

 _On_Out_of_Bounds_Pack p = decode_out_of_bounds(enc);

// Out_of_Bounds_Resolution_Flags f1;
// Out_of_Bounds_Resolution_Flags f2;
// Out_of_Bounds_Resolution_Flags f3;
// Out_of_Bounds_Resolution_Flags f4;

// u1 count = decode_mitigation_flags(0, f1, f2, f3, f4);


 int* x = vec.fetch(2, p, 10);

 void* vx = x;

 qDebug() << "x = " << *x;

// *x = 66;

//  int* x1 = vec.fetch(2, p);

//  qDebug() << "x1 = " << *x1;

//  void* vx1 = x1;


  u2 enc1 = on_out_of_bounds(//
   // Out_of_Bounds_Resolution_Flags::Use_Default_Value_Pointer //,
    //_oob_Call_Default_Value_Function
     // _oob_Call_Default_Constructor_if_Possible
                            //,
                            _oob_Use_Alternate_Fallback_Index
                            )
    (
//     _oob_Use_Default_Value_Pointer
     _oob_Call_Default_Value_Function
     );
  _On_Out_of_Bounds_Pack p1 = decode_out_of_bounds(enc1);


  int* x2 = vec.fetch(14, p1, 10);

  qDebug() << "x2 = " << *x2;

  void* vx2 = x2;


  int* x3 = vec.fetch(15, p1, 10);

  qDebug() << "x2 = " << *x2;

  void* vx3 = x3;



  int* x4 = vec.get(10);

  qDebug() << "x4 = " << *x4;

  void* vx4 = x4;


// int* x1 = vec.get(2);

// qDebug() << "x1 = " << *x1;

 return 0;
}

int main111(int argc , char **argv)
{
 Vec1d<int> vec(10, 7);

 vec.set_default <= [](int** def)
 {
  static int _def = 44;
  *def = &_def;
 };

 u2 enc = on_out_of_bounds(Out_of_Bounds_Resolution_Flags::Use_Default_Value_Pointer,
   Out_of_Bounds_Resolution_Flags::Call_Default_Value_Function)
   [Out_of_Bounds_Resolution_Flags::Automatic_Rebound | Out_of_Bounds_Resolution_Flags::Accept_Initialize_to_Zero]
   ;

 _On_Out_of_Bounds_Pack p = decode_out_of_bounds(enc);


 int* x = vec.fetch(2, p);

 qDebug() << "x = " << *x;




 u2 enc1 = on_out_of_bounds(_oob_Call_Default_Value_Function, _oob_Use_Alternate_Fallback_Index)
   (_oob_Call_Default_Value_Function)
   [_oob_Delay_Mitigation_on_Fallback];

 _On_Out_of_Bounds_Pack p1 = decode_out_of_bounds(enc1);

 int* x1 = vec.fetch(5, p1, 2);

 qDebug() << "x1 = " << *x1;

 return 0;
}

int main09(int argc , char **argv)
{
 u2 enc = on_out_of_bounds(Out_of_Bounds_Resolution_Flags::Use_Alternate_Fallback_Index,
   Out_of_Bounds_Resolution_Flags::Call_Default_Value_Function);

//   [Out_of_Bounds_Resolution_Flags::Use_Exceptions | Out_of_Bounds_Resolution_Flags::Automatic_Rebound];

 //    (Out_of_Bounds_Resolution_Flags::Call_Default_Constructor_if_Possible)


// u2 enc = encode_double_mitigation_flags(1, Out_of_Bounds_Resolution_Flags::Use_Alternate_Fallback_Index,
//    Out_of_Bounds_Resolution_Flags::Call_Default_Value_Function,
//    Out_of_Bounds_Resolution_Flags::Call_Default_Constructor_if_Possible);

// u2 enc = encode_double_mitigation_flags(0, Out_of_Bounds_Resolution_Flags::Use_Alternate_Fallback_Index);

// u2 enc = encode_double_mitigation_flags(1, Out_of_Bounds_Resolution_Flags::Use_Alternate_Fallback_Index,
//    Out_of_Bounds_Resolution_Flags::Use_Default_Value_Pointer,
//    Out_of_Bounds_Resolution_Flags::Call_Default_Constructor_if_Possible);

// u2 enc = 0;

 qDebug() << "enc = " << enc;

 Out_of_Bounds_Resolution_Flags f11;
 Out_of_Bounds_Resolution_Flags f12;
 Out_of_Bounds_Resolution_Flags f13;
 Out_of_Bounds_Resolution_Flags f14;

 Out_of_Bounds_Resolution_Flags f21;
 Out_of_Bounds_Resolution_Flags f22;
 Out_of_Bounds_Resolution_Flags f23;
 Out_of_Bounds_Resolution_Flags f24;

 Out_of_Bounds_Resolution_Flags supplement;


// std::pair<u1, u1> pr = decode_double_mitigation_flags(enc, supplement,
//   f11, f12, f13, f14, f21, f22, f23, f24);

 _On_Out_of_Bounds_Pack p = decode_out_of_bounds(enc);

 std::pair<u1, u1> pr = p.unpack(supplement, f11, f12, f13, f14, f21, f22, f23, f24);

 qDebug() << "supplement = " << (u1) supplement;

 qDebug() << "f11 = " << (u2) f11;
 qDebug() << "f12 = " << (u2) f12;
 qDebug() << "f13 = " << (u2) f13;
 qDebug() << "f14 = " << (u2) f14;

 qDebug() << "f21 = " << (u2) f21;
 qDebug() << "f22 = " << (u2) f22;
 qDebug() << "f23 = " << (u2) f23;
 qDebug() << "f24 = " << (u2) f24;

 qDebug() << "pr = " << pr;
 return 0;
}


int main06(int argc , char **argv)
{
 u1 enc = encode_mitigation_flags(Out_of_Bounds_Resolution_Flags::Use_Alternate_Fallback_Index);
 u1 enc1 = encode_mitigation_flags(
    Out_of_Bounds_Resolution_Flags::Call_Default_Value_Function,
    Out_of_Bounds_Resolution_Flags::Call_Default_Constructor_if_Possible);

 //  Out_of_Bounds_Resolution_Flags::Use_Default_Value_Pointer;
//    Out_of_Bounds_Resolution_Flags::Call_Default_Constructor_if_Possible);

 //   Out_of_Bounds_Resolution_Flags::Use_Exceptions);

 // Call_Default_Constructor_if_Possible
// Out_of_Bounds_Resolution_Flags::Call_Default_Value_Function,

 qDebug() << "enc = " << enc;

// enc = 59;

 Out_of_Bounds_Resolution_Flags f1;
 Out_of_Bounds_Resolution_Flags f2;
 Out_of_Bounds_Resolution_Flags f3;
 Out_of_Bounds_Resolution_Flags f4;

 u1 count = decode_mitigation_flags(enc, f1, f2, f3, f4);

 qDebug() << "f1 = " << (u2) f1;
 qDebug() << "f2 = " << (u2) f2;
 qDebug() << "f3 = " << (u2) f3;
 qDebug() << "f4 = " << (u2) f4;

 return 0;

}

int main05(int argc , char **argv)
{
 u1 mask1;
 s1 pc1 = get_permutation_code(mask1,
   Out_of_Bounds_Resolution_Flags::Call_Default_Value_Function,
   Out_of_Bounds_Resolution_Flags::Use_Exceptions,
   Out_of_Bounds_Resolution_Flags::Use_Default_Value_Pointer,
   Out_of_Bounds_Resolution_Flags::Call_Default_Constructor_if_Possible);

 qDebug() << "pc1 = " << pc1;


 u1 mask2;
 s1 pc2 = get_permutation_code(mask2,
   Out_of_Bounds_Resolution_Flags::Call_Default_Value_Function,
   Out_of_Bounds_Resolution_Flags::Call_Default_Constructor_if_Possible,
   Out_of_Bounds_Resolution_Flags::Use_Default_Value_Pointer);

 qDebug() << "pc2 = " << pc2;

 Out_of_Bounds_Resolution_Flags pc11, pc12, pc13, pc14, pc21, pc22, pc23, pc24;

 parse_permutation_code(pc1, mask1, pc11, pc12, pc13, pc14);
 parse_permutation_code(pc2, mask2, pc21, pc22, pc23, pc24);

 return 0;

}

int main03(int argc , char **argv)
{
// Vec1d<t_e> vec1(10, 7);
// t_e* te = vec1.fetch_at(1, 0);
// qDebug() << "te = " << (int) *te;

// Vec1d<t_c> vec2(10, 7);
// t_c* tc = vec2.fetch_at(1, 0);
// qDebug() << "tc = " << tc->s2;

 Vec1d<int> vec(10, 7);

 //vec.set_default <= deffn(int, 9);

 vec.static_default_value(81);

 vec.resize(60);

 vec.each <<= [](int& i, s2 ix)
 {
  i = ix - 1;
  return-1;
 };

 //qDebug() << vec.to_qstring(QString_number(int));

// int* x = vec.fetch(65, 60,
//   Out_of_Bounds_Resolution_Flags::Automatic_Rebound
//   | Out_of_Bounds_Resolution_Flags::Prefer_Initialize_to_Zero
//   | Out_of_Bounds_Resolution_Flags::Defer_to_Alternate_Fallback_Index);

 int* x = 0; //?vec.fetch(65, Out_of_Bounds_Resolution_Flags::Call_Default_Constructor_if_Possible, 60);

 if(x)
   qDebug() << "x = " << *x;

 else
   qDebug() << "out of bounds ...";

 int* y = 0;//?vec.fetch(65, 60, Out_of_Bounds_Resolution_Flags::Use_Alternate_Fallback_Index);

 if(y)
   qDebug() << "y = " << *y;

 else
   qDebug() << "out of bounds ...";


 return 0;
}

int main02(int argc , char **argv)
{
 Vec1d<int> vec(10, 7);

 QVector<int> test1 {104, 105, 106, 107, 108, 109};
 QVector<int> test2 {219, 220};
 QVector<int> test3 {330, 331};
 QVector<int> test3a {1330, 1331, 1332, 1333, 1334, 1335, 1336, 1337, 1338, 1339, 1340};
 QVector<int> test4 {438, 439, 440, 441, 442, 443, 444,
                     445, 446, 447, 448, 449, 450, 451};
 QVector<int> test5 ;
 QVector<int> test6 ;

 vec.resize(60);

 vec.each <<= [](int& i, s2 ix)
 {
  i = ix - 1;
  return-1;
 };
 qDebug() << vec.to_qstring(QString_number(int));

 Action_scan(std::copy, test1, vec, 4, 9);
 qDebug() << "test 1: " << vec.to_qstring(QString_number(int));

 Action_scan(std::copy, test2, vec, 19, 20);
 qDebug() << "test 2: " << vec.to_qstring(QString_number(int));

 Action_scan(std::copy, test3, vec, 30, 31);
 qDebug() << "test 3: " <<  vec.to_qstring(QString_number(int));

 Action_scan(std::copy, test4, vec, 38, 51);
 qDebug() << "test 4: " <<  vec.to_qstring(QString_number(int));


 Action_scan(std::copy, test3a, vec, 30, 40);  // vec is target
 qDebug() <<  "test 3a: " << vec.to_qstring(QString_number(int));

 test5.resize(7);
 Action_span(std::copy, test5, vec, 1, 7); // vec is source
 qDebug() << "test5 = " << test5;

 test6.resize(17);
 Action_span(std::copy, test6, vec, 5, 21);
 qDebug() << "test6 = " << test6;
}


void test1()
{
 //Hive_Structure<hive_galaxy<int>> hs(16, 16);

 Hive_Structure_s2 hs(16, 16);
 hs.set_value_size(4);

 int& x = *(int*) hs.get_indexed_location_unchecked(8);

 x = 55;

 int y = *(int*) hs.get_location(8);

 qDebug() << "y = " << y;
}


void test2()
{
 Que1d<int> q1d;

 q1d.set_default <= defzfn(int);

 qDebug() << q1d.head();
 qDebug() << q1d.tail();


}

void test3()
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

}

void test4()
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

}


void test5()
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

}

void test6()
{
 Dsk1d<int> d1d;

 d1d.push_back(7);
 d1d.push_back(9);

 d1d.push_front(17);
 d1d.push_front(23);
 d1d.push_front(45);

 d1d.reach <<= [](int& i, s2 ix)
 {
  qDebug() << ix << ": " << i;
  return-1;
 };

 qDebug() << "ok";


}


void test7()
{
 Deq1d<int> d1d;

 d1d.push_back(7);
 d1d.push_back(9);

 d1d.pop_front();
 d1d.push_front(17);

 d1d.reach <<= [](int& i, s2 ix)
 {
  qDebug() << ix << ": " << i;
  return-1;
 };

 qDebug() << "ok";


}

void test8()
{
 Que1d<int> q1d;

 q1d.enqueue(7);
 q1d.enqueue(9);
 q1d.enqueue(17);

 q1d.each <<= [](int& i, s2 ix)
 {
  qDebug() << i;
  return-1;
 };

 qDebug() << "ok";

 qDebug() << q1d.head();
 qDebug() << q1d.tail();


}

void test9()
{
 Stk1d<int> s1d;
 s1d.set_default <= defzfn(int);

 s1d.push(7);
 s1d.push(9);
 s1d.push(17);

 s1d.each <<= [](int& i, s2 ix)
 {
  qDebug() << i;
  return-1;
 };

 qDebug() << s1d.top();
 qDebug() << s1d.bottom();

 qDebug() << "ok";

}


void test10()
{
 Arr1d<int> a1d({4});

 a1d.set_default <= defzfn(int);

 qDebug() << a1d.first();


 a1d.push_back(7);
 a1d.push_back(9);
 a1d.push_back(17);
 a1d.push_back(27);
 a1d.push_back(29);
 a1d.push_back(37);

 a1d.each <= [](int& i, s2 index)
 {
  qDebug() << index;
  qDebug() << i;
 };

 a1d.reach <<= [](int& i, s2 index)
 {
  if(index == 3)
    return-0;
  qDebug() << i;
  return-1;
 };

 qDebug() << "ok";

 qDebug() << a1d.last();
 qDebug() << a1d.first();
}

void test11()
{
 Vec1d<u1> vec(5, 5);
  // vec.default_to(0);
 vec.set_default_fn(defzfn(u1));
 vec.at_index(67) = 111;
 u1 x11 = vec.get_element(67);
 qDebug() << "x11 = " << x11;

 Vec1d<u1>::pre_iterator pre = vec.parse_location(67);

 qDebug() << "pre= " << pre.to_qstring();

}


void test12()
{
 Vec1d<int> v1d;

 v1d.set_default <= defzfn(int);

 qDebug() << v1d.first();

 v1d.push_back(7);
 v1d.push_back(9);
 v1d.push_back(17);

 v1d.each <= [](int& i, s2 index)
 {
  qDebug() << index;
  qDebug() << i;
 };

 v1d.reach <<= [](int& i, s2 index)
 {
  if(index == 3)
    return-0;
  qDebug() << i;
  return-1;
 };

 qDebug() << "ok";

 qDebug() << v1d.last();
 qDebug() << v1d.first();
}

void test13()
{
 Vec1d<u1> vec;
  // vec.default_to(0);
 vec.set_default_fn(defzfn(u1));
 vec.push_back(15);
 u1 x = vec.get_element(0);
 qDebug() << "x = " << x;
}

int main2(int argc , char **argv)
{
 qDebug() << "\n\ntest 1";
 test1();

 qDebug() << "\n\ntest 2";
 test2();

 qDebug() << "\n\ntest 3";
 test3();

 qDebug() << "\n\ntest 4";
 test4();

 qDebug() << "\n\ntest 5";
 test5();

 qDebug() << "\n\ntest 6";
 test6();

 qDebug() << "\n\ntest 7";
 test7();

 qDebug() << "\n\ntest 8";
 test8();

 qDebug() << "\n\ntest 9";
 test9();

 qDebug() << "\n\ntest 10";
 test10();

 qDebug() << "\n\ntest 11";
 test11();

 qDebug() << "\n\ntest 12";
 test12();

 qDebug() << "\n\ntest 13";
 test13();
// test1();
// test1();
// test1();

 return 0;
}
