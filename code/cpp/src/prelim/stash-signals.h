
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef STASH_SIGNALS__H
#define STASH_SIGNALS__H


#include "global-macros.h"

#include <QString>
#include <QPair>
#include <QSet>

#include <QObject>

#include <QAbstractButton>
#include <QPushButton>

#include <functional>
#include <type_traits>

template <typename> struct _signal_class;

template <typename OBJECT_Type, typename ...Args>
struct _signal_class<void (OBJECT_Type::*)(Args...)>
{
 typedef OBJECT_Type _type;
};


struct no_alt_base
{

};

template<typename OBJECT_Type>
struct _alt_base
{
 using _type = no_alt_base;
};

#define STASH_SIGNALS_ALT_BASE(x, y) \
template<> struct _alt_base<x> { \
 using _type = y; };


//template<>
//struct _alt_base<QPushButton>
//{
// using _type = QAbstractButton;
//};


template<typename OBJECT_Type>
struct _saved_mfn_connector
{
 template<typename SIGNAL_OBJECT_Type, typename ...SIGNAL_Args>
 struct signal_type
 {
  typedef void (SIGNAL_OBJECT_Type::*SIGNAL_Type)(SIGNAL_Args...);
  typedef SIGNAL_Type (*get_signal_type)(QString, SIGNAL_Type);
  static SIGNAL_Type get_signal(QString fname, SIGNAL_Type add = nullptr)
  {
   static QMap<QString, SIGNAL_Type> static_map;
   SIGNAL_Type result = static_map.value(fname);
   if(add)
   {
    static_map[fname] = add;
   }
   return result;
  }

  static get_signal_type get_alt() //get_signal_type alt = nullptr)
  {
   static get_signal_type result = nullptr;
   if(!result)
   {
    //typedef QAbstractButton Alt_base;
    typedef typename _alt_base<OBJECT_Type>::_type Alt_base;
    result = (get_signal_type) &_saved_mfn_connector<Alt_base>::template signal_type<Alt_base, SIGNAL_Args...>::get_signal;;
   }
   return result;
  }
 };
 OBJECT_Type* obj;

 template<typename SOBJECT_Type, typename ...Args>
 static void add_signal(QString name, void (SOBJECT_Type::*add)(Args...))
 {
  //typedef void (SOBJECT_Type::*ft)(Args...);
  // signal_type<void (OBJECT_Type::*)(Args...)>::get_signal(name, add);
  signal_type<OBJECT_Type, Args...>::get_signal(name, add);

 }

 //template<typename THIS_Type, typename FN_Type> //, typename ...ARGS>
 template<typename THIS_Type, typename ...Args>
 void resolve_connection(QString mfn, THIS_Type* _this, void(THIS_Type::*fn)(Args...) )
 {
 // auto _mfn = signal_type<void(OBJECT_Type::*)(Args...)>::get_signal(mfn);
  auto _mfn = signal_type<OBJECT_Type, Args...>::get_signal(mfn);


  //typename signal_type<bool>::pmfn _mfn
  //  = signal_type<bool>::get_pmfn(mfn);

  if(_mfn)
    obj->connect(obj, _mfn, _this, fn);

  else
  {
   auto alt = signal_type<OBJECT_Type, Args...>::get_alt();
   //auto alt = signal_type<void(OBJECT_Type::*)(Args...)>::get_alt();
   //auto _mfn1 = signal_type<void(OBJECT_Type::*)(Args...)>::get_alt()(mfn, nullptr);
   auto _mfn1 = alt(mfn, nullptr);
   if(_mfn1)
     obj->connect(obj, _mfn1, _this, fn);
  }
 }

// template<typename LAMBDA_Arg, typename LAMBDA_Type,
//   typename CONV_Type, bool conv_ok>
// bool resolve_lambda_connection(QString mfn, CONV_Type conv);

 template<typename ...LAMBDA_Args>
 bool _resolve_lambda_connection(QString mfn, std::function<void(LAMBDA_Args...)> fn)
 {
  auto _mfn = signal_type<OBJECT_Type, LAMBDA_Args...>::get_signal(mfn);

  if(_mfn)
  {
   obj->connect(obj, _mfn, fn);
   return true;
  }
  else
  {
   auto alt = signal_type<OBJECT_Type, LAMBDA_Args...>::get_alt();
   //auto alt = signal_type<void(OBJECT_Type::*)(Args...)>::get_alt();
   //auto _mfn1 = signal_type<void(OBJECT_Type::*)(Args...)>::get_alt()(mfn, nullptr);
   auto _mfn1 = alt(mfn, nullptr);
   if(_mfn1)
   {
    obj->connect(obj, _mfn1, fn);
    return true;
   }
  }
  return false;
 }

// template<typename LAMBDA_Type, typename LAMBDA_Arg,
//   typename = typename std::enable_if<std::is_convertible<LAMBDA_Type,
//   std::function<void(LAMBDA_Arg)>>::value>::type>
// bool resolve_lambda_connection(QString mfn, std::function<void(LAMBDA_Arg)> fn)
// {
//  return _resolve_lambda_connection(mfn, fn);
// }

// template<typename LAMBDA_Type, typename LAMBDA_Arg,
//   typename = typename std::enable_if<!std::is_convertible<LAMBDA_Type,
//   std::function<void(LAMBDA_Arg)>>::value>::type>
// bool resolve_lambda_connection(QString mfn, LAMBDA_Type fn)
// {
//  return false;
// }

#ifndef MACRO_PASTE
#define MACRO_PASTE(...) __VA_ARGS__
#endif

#define TEMP_MACRO(num, typename_args, args) \
 template<typename LAMBDA_Type, typename_args, \
   typename = typename std::enable_if<std::is_convertible<LAMBDA_Type, \
   std::function<void(args)>>::value>::type> \
 bool resolve_lambda_connection_##num(QString mfn, std::function<void(args)> fn) \
 { \
  return _resolve_lambda_connection(mfn, fn); \
 } \
 template<typename LAMBDA_Type, typename_args, \
   typename = typename std::enable_if<!std::is_convertible<LAMBDA_Type, \
   std::function<void(args)>>::value>::type> \
 bool resolve_lambda_connection_##num(QString, LAMBDA_Type) \
 { \
  return false; \
 } \

TEMP_MACRO(1, typename a1, a1)
TEMP_MACRO(2, MACRO_PASTE(typename a1, typename a2), MACRO_PASTE(a1, a2))
TEMP_MACRO(3, MACRO_PASTE(typename a1, typename a2, typename a3),
           MACRO_PASTE(a1, a2, a3))
TEMP_MACRO(4, MACRO_PASTE(typename a1, typename a2, typename a3, typename a4),
           MACRO_PASTE(a1, a2, a3, a4))

#undef TEMP_MACRO


 template<typename LAMBDA_Type, typename = typename std::enable_if<std::is_convertible<LAMBDA_Type,
   std::function<void()>>::value>::type>
 bool resolve_lambda_connection_0(QString mfn, std::function<void()> fn)
 {
  return _resolve_lambda_connection(mfn, fn);
 }

 template<typename LAMBDA_Type, typename = typename std::enable_if<!std::is_convertible<LAMBDA_Type,
   std::function<void()>>::value>::type>
 bool resolve_lambda_connection_0(QString, LAMBDA_Type)
 {
  return false;
 }

};

//void signal_baseclass()

template<typename THIS_Type, typename ...Args> //, typename FN_Type>
struct _saved_mfn_connector_triple
{
 //typedef
 QString signal_name;
 THIS_Type* _this;
 //FN_Type fn;
 void(THIS_Type::*fn)(Args...);

 _saved_mfn_connector_triple& operator-()
 {
  return *this;
 }

 template<typename OBJECT_Type>
 friend void operator > (OBJECT_Type* lhs, const _saved_mfn_connector_triple& rhs)
 {
  _saved_mfn_connector<OBJECT_Type> smc{lhs};
  smc.resolve_connection//<THIS_Type, Args...>
    (rhs.signal_name, rhs._this, rhs.fn);
 }

 template<typename OBJECT_Type>
 friend void operator >> (OBJECT_Type* lhs, const _saved_mfn_connector_triple& rhs)
 {
  _saved_mfn_connector<OBJECT_Type> smc{lhs};
  smc.resolve_connection//<THIS_Type, Args...>
    (rhs.signal_name, rhs._this, rhs.fn);
 }
};

template<typename FPtr>
struct arg1_traits_impl;

template<typename A1>
struct arg1_traits_impl<void (*)(A1)>{typedef A1 arg1_type;};


template<typename OBJECT_Type, typename ...Args> //, typename FN_Type>
struct _saved_fn_connector_double
{
 OBJECT_Type* obj;
 QString signal_name;

 template<typename ...LAMBDA_Args>
 void operator << (std::function<void(LAMBDA_Args...)> rhs)
 {
  _saved_mfn_connector<OBJECT_Type> smc{obj};
  smc.resolve_lambda_connection//<THIS_Type, Args...>
    (signal_name, rhs);
 }

 template<typename LAMBDA_Type>
 bool resolve_lambda_connection(LAMBDA_Type fn)
 {
  _saved_mfn_connector<OBJECT_Type> smc{obj};
  return smc.template resolve_lambda_connection_0<LAMBDA_Type>(signal_name, fn);
 }

#define TEMP_MACRO(num, typename_args, args) \
  template<typename LAMBDA_Type, typename_args>  \
  bool resolve_lambda_connection(LAMBDA_Type fn) \
  { \
   _saved_mfn_connector<OBJECT_Type> smc{obj}; \
   return smc.template resolve_lambda_connection_##num<LAMBDA_Type, \
     args>(signal_name, fn); \
  } \

TEMP_MACRO(1, typename a1, a1)
TEMP_MACRO(2, MACRO_PASTE(typename a1, typename a2), MACRO_PASTE(a1, a2))
TEMP_MACRO(3, MACRO_PASTE(typename a1, typename a2, typename a3), MACRO_PASTE(a1, a2, a3))
TEMP_MACRO(4, MACRO_PASTE(typename a1, typename a2, typename a3, typename a4), MACRO_PASTE(a1, a2, a3, a4))

#define STASH_SIGNAL_ARG_TYPES(...) \
   _preproc_CONCAT(STASH_SIGNAL_ARG_TYPES_, _preproc_NUM_ARGS (__VA_ARGS__))(__VA_ARGS__)

#define STASH_SIGNAL_ARG_TYPES_1(a1) else if(resolve_lambda_connection<LAMBDA_Type, a1>(rhs));
#define STASH_SIGNAL_ARG_TYPES_2(a1, a2) \
   else if(resolve_lambda_connection<LAMBDA_Type, a1, a2>(rhs));
#define STASH_SIGNAL_ARG_TYPES_3(a1, a2, a3) \
   else if(resolve_lambda_connection<LAMBDA_Type, a1, a2, a3>(rhs));
#define STASH_SIGNAL_ARG_TYPES_4(a1, a2, a3, a4) \
   else if(resolve_lambda_connection<LAMBDA_Type, a1, a2, a3, a4>(rhs));
#define STASH_SIGNAL_ARG_TYPES_5(a1, a2, a3, a4, a5) \
   else if(resolve_lambda_connection<LAMBDA_Type, a1, a2, a3, a4, a5>(rhs));

 template<typename LAMBDA_Type>
 void operator << (LAMBDA_Type rhs)
 {
  if(resolve_lambda_connection<LAMBDA_Type>(rhs));

  // //  this file should have lines like
   //      STASH_SIGNAL_ARG_TYPES(bool)
   //      STASH_SIGNAL_ARG_TYPES(QString)
   //      STASH_SIGNAL_ARG_TYPES(QString, QString)
   //    which expand to e.g.
   //      else if(resolve_lambda_connection<LAMBDA_Type, bool>(rhs));
   //      else if(resolve_lambda_connection<LAMBDA_Type, QString>(rhs));
   //      else if(resolve_lambda_connection<LAMBDA_Type, QString, QString>(rhs));
  #include "stash-signal-arg-types.h"
 }
};


struct _saved_mfn_connector_precursor
{
 QString signal_name;
 _saved_mfn_connector_precursor* operator->()
 {
  return this;
 }

 template<typename THIS_Type, typename ...Args> //, typename FN_Type>
 _saved_mfn_connector_triple<THIS_Type, Args...> _to_this(THIS_Type* _this,
   void (THIS_Type::*fn)(Args...))
 {
  return {signal_name, _this, fn};
 }

 template<typename OBJECT_Type>
 friend _saved_fn_connector_double<OBJECT_Type> operator>>(OBJECT_Type* lhs,
   _saved_mfn_connector_precursor rhs)
 {
  return {lhs, rhs.signal_name};
 }
};


template<typename MEMBER_Fn, typename THIS_Type, typename FN_Type>
struct _Connect_triple
{
 MEMBER_Fn _mfn;
 THIS_Type* _this;
 FN_Type _fn;

 _Connect_triple& operator--()
 {
  return *this;
 }

 _Connect_triple& operator-()
 {
  return *this;
 }

 _Connect_triple& operator!()
 {
  return *this;
 }

 template<typename OBJECT_Type>
 friend void operator- (OBJECT_Type* lhs,
   _Connect_triple<MEMBER_Fn, THIS_Type, FN_Type> triple)
 {
  lhs->connect(lhs, triple._mfn, triple._this, triple._fn);
 }

 template<typename OBJECT_Type>
 friend void operator/ (OBJECT_Type* lhs,
   _Connect_triple<MEMBER_Fn, THIS_Type, FN_Type> triple)
 {
  lhs->connect(lhs, triple._mfn, triple._this, triple._fn);
 }

 template<typename OBJECT_Type>
 friend void operator> (OBJECT_Type* lhs,
   _Connect_triple<MEMBER_Fn, THIS_Type, FN_Type> triple)
 {
  lhs->connect(lhs, triple._mfn, triple._this, triple._fn);
 }

 template<typename OBJECT_Type>
 friend void operator< (OBJECT_Type* lhs,
   _Connect_triple<MEMBER_Fn, THIS_Type, FN_Type> triple)
 {
  lhs->connect(lhs, triple._mfn, triple._this, triple._fn);
 }

 template<typename OBJECT_Type>
 friend void operator>> (OBJECT_Type* lhs,
   _Connect_triple<MEMBER_Fn, THIS_Type, FN_Type> triple)
 {
  if(triple._this)
    lhs->connect(lhs, triple._mfn, triple._this, triple._fn);
  else
    lhs->connect(lhs, triple._mfn, triple._fn);
 }

 template<typename OBJECT_Type>
 friend void operator| (OBJECT_Type* lhs,
   _Connect_triple<MEMBER_Fn, THIS_Type, FN_Type> triple)
 {
  lhs->connect(lhs, triple._mfn, triple._this, triple._fn);
 }

};

template<typename MEMBER_Fn, typename FN_Type>
struct _Connect_double
{
 MEMBER_Fn _mfn;
 FN_Type _fn;

 _Connect_double& operator--()
 {
  return *this;
 }

 _Connect_double& operator-()
 {
  return *this;
 }

 _Connect_double& operator!()
 {
  return *this;
 }

 template<typename OBJECT_Type>
 friend void operator- (OBJECT_Type* lhs,
   _Connect_double<MEMBER_Fn, FN_Type> triple)
 {
  lhs->connect(lhs, triple._mfn, triple._fn);
 }

 template<typename OBJECT_Type>
 friend void operator/ (OBJECT_Type* lhs,
   _Connect_double<MEMBER_Fn, FN_Type> triple)
 {
  lhs->connect(lhs, triple._mfn, triple._fn);
 }

 template<typename OBJECT_Type>
 friend void operator> (OBJECT_Type* lhs,
   _Connect_double<MEMBER_Fn, FN_Type> triple)
 {
  lhs->connect(lhs, triple._mfn, triple._fn);
 }

 template<typename OBJECT_Type>
 friend void operator< (OBJECT_Type* lhs,
   _Connect_double<MEMBER_Fn, FN_Type> triple)
 {
  lhs->connect(lhs, triple._mfn, triple._fn);
 }

 template<typename OBJECT_Type>
 friend void operator>> (OBJECT_Type* lhs,
   _Connect_double<MEMBER_Fn, FN_Type> triple)
 {
  lhs->connect(lhs, triple._mfn, triple._fn);
 }

 template<typename OBJECT_Type>
 friend void operator| (OBJECT_Type* lhs,
   _Connect_double<MEMBER_Fn, FN_Type> triple)
 {
  lhs->connect(lhs, triple._mfn, triple._fn);
 }

};

template<typename OBJECT_Type, typename MEMBER_Fn, typename THIS_Type, typename FN_Type>
struct _Connect_quad
{
 OBJECT_Type* _lhs;
 MEMBER_Fn _mfn;
 THIS_Type* _this;
 FN_Type _fn;

 void operator--()
 {
  _lhs->connect(_lhs, _mfn, _this, _fn);
 }
};

template<typename OBJECT_Type, typename MEMBER_Fn>
struct _Connect_precursor
{
 OBJECT_Type* _lhs;
 MEMBER_Fn _mfn;

 _Connect_precursor* operator ->()
 {
  return this;
 }

 template<typename THIS_Type, typename FN_Type>
 _Connect_quad<OBJECT_Type, MEMBER_Fn, THIS_Type, FN_Type> _to_this(THIS_Type* _this, FN_Type fn)
 {
  return {_lhs, _mfn, _this, fn};
 }

};

template<typename MEMBER_Fn>
struct _Connect
{
 MEMBER_Fn _mfn;

 _Connect* operator ->()
 {
  return this;
 }

 template<typename THIS_Type, typename FN_Type>
 _Connect_triple<MEMBER_Fn, THIS_Type, FN_Type> _to_this(THIS_Type* _this, FN_Type fn)
 {
  return {_mfn, _this, fn};
 }

 template<typename FN_Type>
 _Connect_double<MEMBER_Fn, FN_Type> operator<<(FN_Type fn)
 {
  return {_mfn, fn};
 }


};


#define to_this_1(x) \
  _to_this(this, &std::remove_reference<decltype(*this)>::type::x)


#define to_this(...) \
  _preproc_CONCAT(to_this_, _preproc_NUM_ARGS (__VA_ARGS__))(__VA_ARGS__)


template<typename MEMBER_Fn>
_Connect<MEMBER_Fn> _Connect_(MEMBER_Fn mfn)
{
 return {mfn};
}

template<typename OBJECT_Type, typename MEMBER_Fn>
_Connect_precursor<OBJECT_Type, MEMBER_Fn> _pre_Connect_(OBJECT_Type* obj, MEMBER_Fn mfn)
{
 return {obj, mfn};
}


template<typename OBJECT_Type, typename SIGNAL_Type>
void _stash_signal(QString name, SIGNAL_Type signal)
{
 _saved_mfn_connector<OBJECT_Type>::add_signal(name, signal);
}

template<typename OBJECT_Type, typename SIGNAL_Type>
void _stash_signal(QString class_name, QString name, SIGNAL_Type signal)
{
 static QSet<QPair<QString, QString>> already_stashed;
 if(already_stashed.contains({class_name, name}))
   return;
 already_stashed.insert({class_name, name});

 _saved_mfn_connector<OBJECT_Type>::add_signal(name, signal);
}


template<typename OBJECT_Type, typename SIGNAL_Type>
void _stash_signal_strip_name(//QString hint,
                              QString name, SIGNAL_Type signal)
{
 static QSet<QString> already_stashed;
 if(already_stashed.contains(name))
   return;
 already_stashed.insert(name);
 int i = name.lastIndexOf(':');
 if(i != -1)
 {
  name = name.mid(i + 1);
 }
 _stash_signal<OBJECT_Type, SIGNAL_Type>(name, signal);
}


#define stash_signal_1(x) \
  _stash_signal_strip_name<_signal_class<decltype(&x)>::_type, decltype(&x)>(#x, &x) \


#define stash_signal_2(x, y) \
  _stash_signal<x, decltype(&x::y)>(#x, #y, &x::y)

#define stash_signal(...) \
  _preproc_CONCAT(stash_signal_, _preproc_NUM_ARGS (__VA_ARGS__))(__VA_ARGS__)



template<typename OBJECT_Type, typename SIGNAL_Type>
struct lConnect_precursor
{
 OBJECT_Type* obj;
 SIGNAL_Type signal;

 template<typename LAMBDA_Type>
 void operator <<(LAMBDA_Type l)
 {
  obj->connect(obj, signal, l);
 }
};

template<typename SIGNAL_Type>
struct lConnect_signal
{
 SIGNAL_Type signal;

 template<typename OBJECT_Type>
 friend lConnect_precursor<OBJECT_Type, SIGNAL_Type>
   operator>>(OBJECT_Type* obj, lConnect_signal rhs)
 {
  return {obj, rhs.signal};
 }
};

template<typename SIGNAL_Type>
lConnect_signal<SIGNAL_Type> _lConnect(SIGNAL_Type s)
{
 return {s};
}

template<typename OBJECT_Type, typename SIGNAL_Type>
lConnect_precursor<OBJECT_Type, SIGNAL_Type> _lConnect_(OBJECT_Type* obj, SIGNAL_Type signal)
{
 return {obj, signal};
}

#define  to_lambda_this << [this]
#define  to_lambda <<

#define overload_of ,,,

#define lConnect_4(x, dummy1, dummy2, y) _lConnect(QOverload<x>::of(&y))

#define lConnect(...) \
  _preproc_CONCAT(lConnect_, _preproc_NUM_ARGS (__VA_ARGS__))(__VA_ARGS__)

#define _Connect_4(x, dummy1, dummy2, y) _lConnect(QOverload<x>::of(&y))


#define _Connect_3(dummy1,_1,dummy2) _Connect_(_1)


#define _Connect_2(_1, _2) \
  _pre_Connect_(_1, &std::remove_reference<decltype(*_1)>::type::_2)



#define _Connect_1(_1) _saved_mfn_connector_precursor{#_1}

#define Connect(...) \
  _preproc_CONCAT(_Connect_, _preproc_NUM_ARGS (__VA_ARGS__))(__VA_ARGS__)


#endif // STASH_SIGNALS__H
