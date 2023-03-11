
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef QUE1D__H
#define QUE1D__H


#include "accessors.h"

#include "hive-structure.h"
#include "_vec1d.h"

#include <QVector>
#include <QString>
#include <QMap>

#include <QDebug>

#include <functional>

KANS_(RdSC)

template<typename VAL_Type, typename INDEX_Types = index_types<s2>, typename PR_Type = _pr_break>
class Que1d : protected _Vec1d<VAL_Type, INDEX_Types, PR_Type>,
  public each_holders<Que1d<VAL_Type, INDEX_Types, PR_Type>, VAL_Type, typename INDEX_Types::Numeric_Index_type, PR_Type>
{
 using self_type = Que1d<VAL_Type, INDEX_Types, PR_Type>;

 u2 offset_;

public:

 Que1d(typename INDEX_Types::Numeric_Nested_Index_type layer_size = 15,
       typename INDEX_Types::Numeric_Nested_Index_type block_size = 17)
  :  _Vec1d<VAL_Type, INDEX_Types, PR_Type>(layer_size, block_size), offset_(0),
    each_holders<self_type, VAL_Type, typename INDEX_Types::Numeric_Index_type, PR_Type>({{*this}})
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

 void dequeue()
 {
  ++offset_;
  if(offset_ == this->hive_structure_->block_size())
  {
   this->hive_structure_->pop_first_block();
   offset_ = 0;
  }
 }

 void enqueue(const VAL_Type& v)
 {
  _Vec1d<VAL_Type, INDEX_Types, PR_Type>::push_back(v);
 }

 void _each(std::function<void(VAL_Type& v)> fn)
 {
  if(offset_ == 0)
    _Vec1d<VAL_Type, INDEX_Types, PR_Type>::_each(fn);
  else
    _Vec1d<VAL_Type, INDEX_Types, PR_Type>::_each_from_index(offset_, fn);
 }

 void _each(std::function<void(VAL_Type& v, const typename INDEX_Types::Numeric_Index_type& index)> fn)
 {
  if(offset_ == 0)
    _Vec1d<VAL_Type, INDEX_Types, PR_Type>::_each(fn);
  else
    _Vec1d<VAL_Type, INDEX_Types, PR_Type>::_each_from_index(offset_, fn);
 }

 PR_Type _pr_each(std::function<typename PR_Type::level_type(VAL_Type& v)> fn)
 {
  if(offset_ == 0)
    return _Vec1d<VAL_Type, INDEX_Types, PR_Type>::_pr_each(fn);
  else
    return _Vec1d<VAL_Type, INDEX_Types, PR_Type>::_pr_each_from_index(offset_, fn);
 }

 PR_Type _pr_each(std::function<typename PR_Type::level_type(VAL_Type& v,
   const typename INDEX_Types::Numeric_Index_type& index)> fn)
 {
  if(offset_ == 0)
    return _Vec1d<VAL_Type, INDEX_Types, PR_Type>::_pr_each(fn);
  else
    return _Vec1d<VAL_Type, INDEX_Types, PR_Type>::_pr_each_from_index(offset_, fn);
 }

 VAL_Type& tail()
 {
  return this->last();
 }

 VAL_Type& head()
 {
  return this->first();
 }

};

_KANS(RdSC)


#endif // QUE1D__H
