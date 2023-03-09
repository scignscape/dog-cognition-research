
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef DSK1D__H
#define DSK1D__H

#include "accessors.h"

#include "hive-structure.h"
#include "_vec1d.h"

#include <QVector>
#include <QString>
#include <QMap>

#include <QDebug>

#include <functional>

XCNS_(XCSD)

template<typename VAL_Type, typename INDEX_Types = index_types<s2>, typename PR_Type = _pr_break>
class Dsk1d :
  public each_holders<Dsk1d<VAL_Type, INDEX_Types, PR_Type>, VAL_Type, typename INDEX_Types::Numeric_Index_type, PR_Type>
{
 using self_type = Dsk1d<VAL_Type, INDEX_Types, PR_Type>;

protected:

 _Vec1d<VAL_Type, INDEX_Types, PR_Type> front_vec_;
 _Vec1d<VAL_Type, INDEX_Types, PR_Type> back_vec_;

public:


 Dsk1d()
  :  front_vec_(_Vec1d<VAL_Type, INDEX_Types, PR_Type>()),
     back_vec_(_Vec1d<VAL_Type, INDEX_Types, PR_Type>()),
     each_holders<self_type, VAL_Type, typename INDEX_Types::Numeric_Index_type, PR_Type>({{*this}})
 {

 }

 Dsk1d(u1 bsz)
  :  front_vec_(_Vec1d<VAL_Type, INDEX_Types, PR_Type>(bsz)),
     back_vec_(_Vec1d<VAL_Type, INDEX_Types, PR_Type>(bsz)),
     each_holders<self_type, VAL_Type, typename INDEX_Types::Numeric_Index_type, PR_Type>({{*this}})
 {

 }

 Dsk1d(u1 bsz, u1 fbsz)
  :  front_vec_(_Vec1d<VAL_Type, INDEX_Types, PR_Type>(bsz)),
     back_vec_(_Vec1d<VAL_Type, INDEX_Types, PR_Type>(fbsz)),
     each_holders<self_type, VAL_Type, typename INDEX_Types::Numeric_Index_type, PR_Type>({{*this}})
 {

 }

 void set_default_fn(std::function<void(VAL_Type**)> fn)
 {
  front_vec_.set_default_fn(fn);
  back_vec_.set_default_fn(fn);
 }

 void _set_default(std::function<void(VAL_Type**)> fn)
 {
  set_default_fn(fn);
 }

 void push_back(const VAL_Type& v)
 {
  back_vec_.push_back(v);
 }

 void push_front(const VAL_Type& v)
 {
  front_vec_.push_back(v);
 }

 void pop_back()
 {
  back_vec_.hive_structure_->pop_back();
 }

 void pop_front()
 {
  front_vec_.hive_structure_->pop_back();
 }

 VAL_Type& back()
 {
  return back_vec_.last();
 }

 VAL_Type& front()
 {
  return front_vec_.last();
 }

 void _each(std::function<void(VAL_Type& v)> fn)
 {
  front_vec_._reach(fn);
  back_vec_._each(fn);
 }

 void _each(std::function<void(VAL_Type& v, const typename INDEX_Types::Numeric_Index_type& index)> fn)
 {
  front_vec_._reach(fn);
  back_vec_._each(fn, front_vec_.size());
 }

 PR_Type _pr_each(std::function<typename PR_Type::level_type(VAL_Type& v)> fn)
 {
  PR_Type result = front_vec_._pr_reach(fn);
  if(result.level >= 0)
    return result;
  return back_vec_._pr_each(fn);
 }

 PR_Type _pr_each(std::function<typename PR_Type::level_type(VAL_Type& v, const
   typename INDEX_Types::Numeric_Index_type& index)> fn)
 {
  PR_Type result = front_vec_._pr_reach(fn);
  if(result.level >= 0)
    return result;
  return back_vec_._pr_each(fn, front_vec_.size());
 }

 void _reach(std::function<void(VAL_Type& v)> fn)
 {
  back_vec_._reach(fn);
  front_vec_._each(fn);
 }

 void _reach(std::function<void(VAL_Type& v, const typename INDEX_Types::Numeric_Index_type& index)> fn)
 {
  back_vec_._reach(fn);
  front_vec_._each(fn, back_vec_.size());
 }

 PR_Type _pr_reach(std::function<typename PR_Type::level_type(VAL_Type& v)> fn)
 {
  PR_Type result = back_vec_._pr_reach(fn);
  if(result.level >= 0)
    return result;
  return front_vec_._pr_each(fn);
 }

 PR_Type _pr_reach(std::function<typename PR_Type::level_type(VAL_Type& v,
   const typename INDEX_Types::Numeric_Index_type& index)> fn)
 {
  PR_Type result = back_vec_._pr_reach(fn);
  if(result.level >= 0)
    return result;
  return front_vec_._pr_each(fn, back_vec_.size());
 }
};

_XCNS(XCSD)

#endif // DSK1D__H
