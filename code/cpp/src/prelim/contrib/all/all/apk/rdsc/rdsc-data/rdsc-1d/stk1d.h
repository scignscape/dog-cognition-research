
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef STK1D__H
#define STK1D__H


#include "accessors.h"

#include "hive-structure.h"
#include "vec1d.h"

#include <QVector>
#include <QString>
#include <QMap>

#include <QDebug>

#include <functional>

KANS_(RdSC)

template<typename VAL_Type, typename INDEX_Types = index_types<s2>, typename PR_Type = _pr_break>
class Stk1d : protected _Vec1d<VAL_Type, INDEX_Types, PR_Type>,
  public each_holders<Stk1d<VAL_Type, INDEX_Types, PR_Type>, VAL_Type, typename INDEX_Types::Numeric_Index_type, PR_Type>
{
 using self_type = Stk1d<VAL_Type, INDEX_Types, PR_Type>;

public:

 Stk1d(typename INDEX_Types::Numeric_Nested_Index_type layer_size = 15,
       typename INDEX_Types::Numeric_Nested_Index_type block_size = 17)
  :  _Vec1d<VAL_Type, INDEX_Types, PR_Type>(layer_size, block_size), each_holders<self_type, VAL_Type, typename INDEX_Types::Numeric_Index_type, PR_Type>({{*this}})
 {
 }


 void set_default_fn(std::function<void(VAL_Type**)> fn)
 {
  _Vec1d<VAL_Type, INDEX_Types, PR_Type>::set_default_fn(fn);
 }

 void _set_default(std::function<void(VAL_Type**)> fn)
 {
  set_default_fn(fn);
 }

 void push(const VAL_Type& v)
 {
  _Vec1d<VAL_Type, INDEX_Types, PR_Type>::push_back(v);
 }

 void _each(std::function<void(VAL_Type& v)> fn)
 {
  _Vec1d<VAL_Type, INDEX_Types, PR_Type>::_reach(fn);
 }

 void _each(std::function<void(VAL_Type& v, const typename INDEX_Types::Numeric_Index_type& index)> fn)
 {
  _Vec1d<VAL_Type, INDEX_Types, PR_Type>::_reach(fn);
 }

 PR_Type _pr_each(std::function<typename PR_Type::level_type(VAL_Type& v)> fn)
 {
  return _Vec1d<VAL_Type, INDEX_Types, PR_Type>::_pr_reach(fn);
 }

 PR_Type _pr_each(std::function<typename PR_Type::level_type(VAL_Type& v,
   const typename INDEX_Types::Numeric_Index_type& index)> fn)
 {
  return _Vec1d<VAL_Type, INDEX_Types, PR_Type>::_pr_reach(fn);
 }

 void pop()
 {
  this->hive_structure_->pop_back();
 }


 VAL_Type& top()
 {
  return this->last();
 }

 VAL_Type& bottom()
 {
  return this->first();
 }


};

_KANS(RdSC)


#endif // STK1D__H
