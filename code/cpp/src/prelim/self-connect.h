
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef SELF_CONNECT__H
#define SELF_CONNECT__H

#include <QtGlobal>
#include <QString>
#include <QMap>

//? #include <QValidator>


#include <QPair>

#include <functional>

#include "global-macros.h"


#define _AUTO_OBJECT_NAME_(x) x->setObjectName(QString::fromUtf8(#x).chopped(1));


#define USE_SELF_CONNECT_normal \
 template<typename ... ARGS> \
 void self_connect(ARGS ... args) \
 { \
  connect(this, args...); \
 } \


#define USE_SELF_CONNECT_lambda \
template<typename MFN_Type> \
auto _self_connect(MFN_Type mfn) \
{ \
 return _self_connect_package<decltype (this), MFN_Type>{this, mfn}; \
} \


#define USE_SELF_CONNECT_1(x) USE_SELF_CONNECT_##x
#define USE_SELF_CONNECT_2(x, y) USE_SELF_CONNECT_##x USE_SELF_CONNECT_##y

#define USE_SELF_CONNECT(...) \
  _preproc_CONCAT(USE_SELF_CONNECT_, _preproc_NUM_ARGS (__VA_ARGS__))(__VA_ARGS__)


template<typename OBJ_Type, typename MFN_Type>
struct _self_connect_package
{
 OBJ_Type _this;
 MFN_Type mfn;
 template<typename LAMBDA_Type>
 void operator<<(LAMBDA_Type lam)
 {
  _this->self_connect(mfn, lam);
 }

 template<typename T1, typename T2>
 void operator()(T1 t1, T2 t2)
 {
  _this->self_connect(mfn, t1, t2);
 }

};

#ifndef _to_this_
#define _to_this_(x) \
 (this, &std::remove_pointer<decltype(this)>::type::x)
#endif

#define _self_connect_(x, y) \
  x->_self_connect(&std::remove_pointer<decltype(x)>::type::y)

#define _bind_0_(x, y) \
  std::bind(&std::remove_reference<decltype(*x)>::type::y, x)

#define _std_placeholders_1 std::placeholders::_1
#define _std_placeholders_2 std::placeholders::_1, std::placeholders::_2
#define _std_placeholders_3 std::placeholders::_1, std::placeholders::_2, \
  std::placeholders::_3

#define _std_placeholders_4 std::placeholders::_1, std::placeholders::_2, \
  std::placeholders::_3, std::placeholders::_4
#define _std_placeholders_5 std::placeholders::_1, std::placeholders::_2, \
  std::placeholders::_3, std::placeholders::_4, std::placeholders::_5
#define _std_placeholders_6 std::placeholders::_1, std::placeholders::_2, \
  std::placeholders::_3, std::placeholders::_4, std::placeholders::_5, \
  std::placeholders::_6
#define _std_placeholders_7 std::placeholders::_1, std::placeholders::_2, \
  std::placeholders::_3, std::placeholders::_4, std::placeholders::_5, \
  std::placeholders::_6, std::placeholders::_7
#define _std_placeholders_8 std::placeholders::_1, std::placeholders::_2, \
  std::placeholders::_3, std::placeholders::_4, std::placeholders::_5, \
  std::placeholders::_6, std::placeholders::_7, std::placeholders::_8
#define _std_placeholders_9 std::placeholders::_1, std::placeholders::_2, \
  std::placeholders::_3, std::placeholders::_4, std::placeholders::_5, \
  std::placeholders::_6, std::placeholders::_7, std::placeholders::_8, \
  std::placeholders::_9

#define _bind_1_(x, y) \
  std::bind(&std::remove_reference<decltype(*x)>::type::y, x, _std_placeholders_1)

#define _bind_2_(x, y) \
  std::bind(&std::remove_reference<decltype(*x)>::type::y, x, \
  _std_placeholders_2)

#define _bind_3_(x, y) \
  std::bind(&std::remove_reference<decltype(*x)>::type::y, x, \
  _std_placeholders_3)

#define _bind_4_(x, y) \
  std::bind(&std::remove_reference<decltype(*x)>::type::y, x, \
  _std_placeholders_4)

#define _bind_5_(x, y) \
  std::bind(&std::remove_reference<decltype(*x)>::type::y, x, \
  _std_placeholders_5)

#define _bind_6_(x, y) \
  std::bind(&std::remove_reference<decltype(*x)>::type::y, x, \
  _std_placeholders_6)

#define _bind_7_(x, y) \
  std::bind(&std::remove_reference<decltype(*x)>::type::y, x, \
  _std_placeholders_7)

#define _bind_8_(x, y) \
  std::bind(&std::remove_reference<decltype(*x)>::type::y, x, \
  _std_placeholders_8)

#define _bind_9_(x, y) \
  std::bind(&std::remove_reference<decltype(*x)>::type::y, x, \
  _std_placeholders_9)


#define _to_bind_0_(...) << _bind_0_(__VA_ARGS__)
#define _to_bind_1_(...) << _bind_1_(__VA_ARGS__)
#define _to_bind_2_(...) << _bind_2_(__VA_ARGS__)

#define _to_bind_3_(...) << _bind_3_(__VA_ARGS__)
#define _to_bind_4_(...) << _bind_4_(__VA_ARGS__)
#define _to_bind_5_(...) << _bind_5_(__VA_ARGS__)

#define _to_bind_6_(...) << _bind_6_(__VA_ARGS__)
#define _to_bind_7_(...) << _bind_7_(__VA_ARGS__)
#define _to_bind_8_(...) << _bind_8_(__VA_ARGS__)

#ifndef to_lambda
#define to_lambda <<
#endif

#ifndef to_lambda_this
#define to_lambda_this << [this]
#endif

#define _to_bind_0_with_callstamp _to_bind_1_
#define _to_bind_0(x) _to_bind_0_##x

#define _to_bind_1_with_callstamp _to_bind_2_
#define _to_bind_1(x) _to_bind_1_##x

#define _to_bind_2_with_callstamp _to_bind_3_
#define _to_bind_2(x) _to_bind_2_##x

#define _to_bind_3_with_callstamp _to_bind_4_
#define _to_bind_3(x) _to_bind_3_##x

#define _to_bind_4_with_callstamp _to_bind_5_
#define _to_bind_4(x) _to_bind_4_##x

#define _to_bind_5_with_callstamp _to_bind_6_
#define _to_bind_5(x) _to_bind_5_##x

#define _to_bind_6_with_callstamp _to_bind_7_
#define _to_bind_6(x) _to_bind_6_##x

#define _to_bind_7_with_callstamp _to_bind_8_
#define _to_bind_7(x) _to_bind_8_##x

#define connect_to_this(x, y, z) \
  connect(x, y, this, &std::remove_reference<decltype(*this)>::type::z)


#define make_default_signal_name(x)  x##_requested
#define make_default_slot_name(x)  handle_##x

#define minimal_self_connect_0(x) \
  _self_connect_(self_connect_sender, make_default_signal_name(x)) \
     _to_bind_0_(self_connect_receiver, make_default_slot_name(x))

#define minimal_self_connect_1(x) \
  _self_connect_(self_connect_sender, make_default_signal_name(x)) \
     _to_bind_1_(self_connect_receiver, make_default_slot_name(x))

#define minimal_self_connect_2(x) \
  _self_connect_(self_connect_sender, make_default_signal_name(x)) \
     _to_bind_2_(self_connect_receiver, make_default_slot_name(x))

#define minimal_self_connect__with_callstamp_(x) \
  minimal_self_connect_1(x)

#define minimal_self_connect_with_callstamp_1(x) \
  minimal_self_connect_2(x)


#define minimal_self_connect_ARGS_2(n, note) minimal_self_connect_##note##_##n

#define minimal_self_connect_ARGS_1(n) minimal_self_connect_##n


#define minimal_self_connect(...) \
  _preproc_CONCAT(minimal_self_connect_ARGS_, _preproc_NUM_ARGS (__VA_ARGS__))(__VA_ARGS__)




#ifndef coemit
#define coemit(x){x();}
#endif

#ifndef to_coemit_signature_and_signal
#define to_coemit_signature_and_signal(x, ...) \
to_lambda_this (x) coemit(__VA_ARGS__)
#endif

#ifndef to_coemit_2
#define to_coemit_2(x, y) \
 to_coemit_signature_and_signal(x, y)
#endif

#ifndef to_coemit_1
#define to_coemit_1(x) \
 to_coemit_TYPE_##x
#endif

#ifndef to_coemit_TYPE_bool
#define to_coemit_TYPE_bool(...) \
to_coemit_signature_and_signal(bool, __VA_ARGS__)
#endif

#ifndef to_coemit_TYPE_void
#define to_coemit_TYPE_void(...) \
to_coemit_signature_and_signal(, __VA_ARGS__)
#endif

#ifndef to_coemit_TYPE_
#define to_coemit_TYPE_(...) \
to_coemit_signature_and_signal(, __VA_ARGS__)
#endif

#ifndef to_coemit
#define to_coemit(...) \
 _preproc_CONCAT(to_coemit_, _preproc_NUM_ARGS (__VA_ARGS__))(__VA_ARGS__)
#endif


//to_lambda_this (bool) coemit(x)

//#ifndef to_coemit_bool
//#define to_coemit_bool to_coemit_(bool, x)
//#endif



#endif // SELF_CONNECT__H
