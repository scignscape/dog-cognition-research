
//           Copyright Nathaniel Christen 2021.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef DGVM_RUNTIME_ENVIRONMENT__H
#define DGVM_RUNTIME_ENVIRONMENT__H


#include "kans.h"

#include "global-types.h"

#include "tagged-ptr/mz/tagged_ptr.hpp"

#include <QString>
#include <QVector>
#include <QVariant>

#include <deque>
#include <vector>

#include <QDebug>

KANS_CLASS_DECLARE(DGDB ,DgDb_Database_Instance)
KANS_CLASS_DECLARE(DGDB ,DgDb_Hypernode)

USING_KANS(DGDB)

Q_DECLARE_METATYPE(DgDb_Hypernode*)





KANS_(DGVM)


class DGVM_Runtime;

class DGVM_Runtime_Environment
{
 DGVM_Runtime* dgr_;
 DgDb_Database_Instance* database_;

 QVector<QString> known_flags_;

public:
 struct One_Byte_Deque {


  template <typename T, std::size_t N>
  struct _binder {
    std::vector<T> vec;

    template <std::size_t I>
    T &get() { return vec.at(I); }
  };



   u1 bytes [15];
   u1 low_active:4;
   u1 high_active:4;

   One_Byte_Deque() : low_active(0), high_active(15) {}

   void push(u1 value) { bytes[low_active++] = value; }
   u1 pull() { return bytes[--low_active]; }

   void push_opt(u1 value) { bytes[--high_active] = value; }
   u1 pull_opt(u1 default_value) { return high_active < 15? bytes[high_active++] : default_value; }

   std::vector<u1> pull(u1 count)
   {
    std::vector<u1> result(count);
    std::reverse_copy(&bytes[low_active - count], &bytes[low_active], result.begin());
    low_active -= count;
    return result;
   }

   std::vector<u1> pull_opt(u1 count, u1 default_value)
   {
    std::vector<u1> result(count);

    if(high_active + count <= 15)
    {
     std::copy(&bytes[high_active], &bytes[high_active + count], result.begin());
     high_active += count;
    }
    else
    {
     std::copy(&bytes[high_active], &bytes[15], result.begin());
     std::fill(result.begin() + high_active - 15 + count, result.end(), default_value);
     high_active = 15;
    }
    return result;
   }

   template<std::size_t N, class T>
   static auto binding_rhs(const std::vector<T>& vec);

   template<std::size_t N>
   _binder<u1, N> _pull()
   {
    return binding_rhs<N, u1>(pull(N));
   }

   template<std::size_t N>
   _binder<u1, N> _pull_opt(u1 default_value)
   {
    return binding_rhs<N, u1>(pull_opt(N, default_value));
   }

 };

private:

 One_Byte_Deque one_byte_deque_;
 std::deque<QVariant> qvariant_deque_;

public:

 DGVM_Runtime_Environment(DGVM_Runtime* dgr);
 DGVM_Runtime_Environment();
 DGVM_Runtime_Environment(DgDb_Database_Instance* db);

 void init_database(QString folder);
 void init_runtime();

 void init_flags(QString flags_list);
 void new_hypernode();

 void push_byte_value(u1 value);
 void push_opt_byte_value(u1 value);

 u1 pull_byte_value();

 template<typename VALUE_Type>
 void push_ptr_value(VALUE_Type* pVal);

 template<typename VALUE_Type>
 void push_raw_value(VALUE_Type val);

 template<typename VALUE_Type = void**>
 void get_ptr_tag();

 template<typename VALUE_Type = void**>
 void detag_ptr();


 template<typename VALUE_Type>
 VALUE_Type yield();

 template<typename VALUE_Type>
 VALUE_Type preyield();

 template<typename VALUE_Type>
 VALUE_Type* pull_ptr_value()
 {
  return yield<VALUE_Type*>();
 }

 template<typename VALUE_Type>
 VALUE_Type pull_raw_value()
 {
  return yield<VALUE_Type>();
 }



// template<typename VALUE_Type>
// n8 tag_ptr_value();


 template<typename VALUE_Type>
 void tag_ptr_value();
// {
//  auto [align_size, tag_value] = one_byte_deque_._pull<2>();

//  qDebug() << "align_size = " << align_size;
//  qDebug() << "tag_value = " << tag_value;

//  return 0;
// }




};

_KANS(DGVM)

#include "dgvm-runtime-environment.templates.h"

#endif // DGVM_RUNTIME_ENVIRONMENT__H
