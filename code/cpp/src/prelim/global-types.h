
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef GLOBAL_TYPES__H
#define GLOBAL_TYPES__H

#include <QtGlobal>
#include <QString>
#include <QMap>

//?
//#ifndef HAVE_NO_QT_GUI_MODULE
//?#include <QValidator>
//#endif

#include <QPair>

#include <functional>

#include "global-macros.h"
#include "enum-macros.h"


#define _auto_new(obj) \
  new std::remove_pointer<decltype(obj)>::type


#define CLASS_NAME_FOLDER_FN_1(ty)  \
inline QString class_name_folder(QString pre) \
{ \
 return pre + "/_" #ty; \
} \



#define CLASS_NAME_FOLDER_FN_0  \
inline QString class_name_folder(QString pre) \
{ \
 return pre + "/_" + this->metaObject()->className(); \
} \



#define CLASS_NAME_FOLDER_FN(...) \
  _preproc_CONCAT(CLASS_NAME_FOLDER_FN_, _preproc_NUM_ARGS (__VA_ARGS__))(__VA_ARGS__)

#define _CLASS_NAME_FOLDER_FN  CLASS_NAME_FOLDER_FN_0



#define CLASS_NAME_FN_classname(ty)  \
inline QString class_name_folder(QString pre) \
{ \
 return pre + "/_" #ty; \
} \

#define CLASS_NAME_FN_auto  \
inline QString class_name_folder(QString pre) \
{ \
 return pre + "/_" + this->metaObject()->className(); \
} \


#define CLASS_NAME_FN_2(mode, arg)  CLASS_NAME_FN_##mode(arg)

#define CLASS_NAME_FN_1(mode)  CLASS_NAME_FN_##mode


#define CLASS_NAME_FN(...) \
  _preproc_CONCAT(CLASS_NAME_FN_, _preproc_NUM_ARGS (__VA_ARGS__))(__VA_ARGS__)


inline char* q_to_std(const QString& qs)
{
 return const_cast<char*>( qs.toStdString().c_str() );
 //return qs.toStdString().c_str();
}

inline char* q_to_std_(QString qs)
{
 return const_cast<char*>( qs.toStdString().c_str() );
 //return qs.toStdString().c_str();
}


#define Q_TO_STD(qs) const_cast<char*>( qs.toStdString().c_str() )

#define call_Stamp(ty) ty

//#define call_Stamp_u2 u2


#define NULL_CALL_STAMP 0

typedef quint8 u1;
typedef quint16 u2;
typedef quint32 u4;
typedef quint64 n8;

struct call_Stamp_u2
{
 u2 value;
 call_Stamp_u2(u2 v) : value(v){}
 operator u2() { return value; }
};

typedef qint8 s1;
typedef qint16 s2;
typedef qint32 s4;
typedef qint64 s8;

typedef qreal r8;
typedef float r4;


typedef quint8 un1;
typedef quint16 un2;
typedef quint32 un4;
typedef quint64 nn8;

typedef qint8 si1;
typedef qint16 si2;
typedef qint32 si4;
typedef qint64 si8;


typedef char i1;

// //  allows someone to to define 
 //    integer types either signed 
 //    by default.  Unless explicitly 
 //    set, takes signedness from 
 //    default char ...
#include <climits>
#if (CHAR_MIN==0)
typedef quint16 i2;
typedef quint32 i4;
typedef quint64 i8;
#else
typedef qint16 i2;
typedef qint32 i4;
typedef qint64 i8;
#endif

static inline QString operator ""_q(const char* cs, size_t size)
{
 std::string ss(cs, size);
 return QString::fromStdString(ss);
}

static inline QString operator ""_qt(const char* cs, size_t size)
{
 std::string ss(cs, size);
 return QString::fromStdString(ss);
}

inline bool _cut(const QString to_cut, QString& original)
{
 if(original.startsWith(to_cut))
 {
  original = original.mid(to_cut.size());
  return to_cut.size();
 }
 return 0;
}

template<typename T>
struct Defaulting_To_Zero
{
 T the_t;
 Defaulting_To_Zero(T tt) : the_t(tt){}
 Defaulting_To_Zero() : the_t(0){}
 operator T() { return the_t; }

 bool operator*()
 {
  return !is_max();
 }

 static Defaulting_To_Zero<T> get_max()
 {
  return Defaulting_To_Zero(std::numeric_limits<T>::max());
 }

 bool is_max()
 {
  return the_t == std::numeric_limits<T>::max();
 }

// operator bool()
// {
//  return the_t != -1;
// }
};



#endif // GLOBAL_TYPES__H
