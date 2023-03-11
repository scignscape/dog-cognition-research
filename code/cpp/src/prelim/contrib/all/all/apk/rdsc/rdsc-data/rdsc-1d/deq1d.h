
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef DEQ1D__H
#define DEQ1D__H

#include "accessors.h"

#include "hive-structure.h"
#include "_vec1d.h"

#include <QVector>
#include <QString>
#include <QMap>

#include <QDebug>

#include <functional>

KANS_(RdSC)

template<typename VAL_Type, typename INDEX_Types = index_types<s2>, typename PR_Type>
class Deq1d : protected _Vec1d<VAL_Type, INDEX_Types, PR_Type>,
  public each_holders<Deq1d<VAL_Type, INDEX_Types, PR_Type>, VAL_Type, typename INDEX_Types::Numeric_Index_type, PR_Type>
{
 using self_type = Deq1d<VAL_Type, INDEX_Types, PR_Type>;
 using base_type = _Vec1d<VAL_Type, INDEX_Types, PR_Type>;

 u2 offset_;

public:

 Deq1d(typename INDEX_Types::Numeric_Nested_Index_type layer_size = 15,
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

 void pop_front()
 {
  ++offset_;
  if(offset_ == this->hive_structure_->block_size())
  {
   this->hive_structure_->pop_first_block();
   offset_ = 0;
  }
 }

 void push_back(const VAL_Type& v)
 {
  base_type::push_back(v);
 }

 void push_front(const VAL_Type& v)
 {
  if(offset_ == 0)
  {
   this->hive_structure_->push_first_block();
   offset_ = this->hive_structure_->block_size() - 1;
  }
  else
  {
   --offset_;
  }
  void* spot = this->hive_structure_->get_indexed_location(offset_);
  memcpy(spot, &v, this->hive_structure_->value_size());
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

 void _reach(std::function<void(VAL_Type& v)> fn)
 {
  if(offset_ == 0)
    _Vec1d<VAL_Type, INDEX_Types, PR_Type>::_reach(fn);
  else
    _Vec1d<VAL_Type, INDEX_Types, PR_Type>::_reach_to_index(offset_, fn);
 }

 void _reach(std::function<void(VAL_Type& v,
   const typename INDEX_Types::Numeric_Index_type& index)> fn)
 {
  if(offset_ == 0)
    _Vec1d<VAL_Type, INDEX_Types, PR_Type>::_reach(fn);
  else
    _Vec1d<VAL_Type, INDEX_Types, PR_Type>::_reach_to_index(offset_, fn);
 }

 PR_Type _pr_reach(std::function<typename PR_Type::level_type(VAL_Type& v)> fn)
 {
  if(offset_ == 0)
    return _Vec1d<VAL_Type, INDEX_Types, PR_Type>::_pr_reach(fn);
  else
    return _Vec1d<VAL_Type, INDEX_Types, PR_Type>::_pr_reach_to_index(fn, offset_);
 }

 PR_Type _pr_reach(std::function<typename PR_Type::level_type(VAL_Type& v,
   const typename INDEX_Types::Numeric_Index_type& index)> fn)
 {
  if(offset_ == 0)
    return _Vec1d<VAL_Type, INDEX_Types, PR_Type>::_pr_reach(fn);
  else
    return _Vec1d<VAL_Type, INDEX_Types, PR_Type>::_pr_reach_to_index(fn, offset_);
 }

 VAL_Type& back()
 {
  return this->last();
 }

 VAL_Type& front()
 {
  return this->at_index(offset_);
 }

};

_KANS(RdSC)

#endif // DEQ1D__H
