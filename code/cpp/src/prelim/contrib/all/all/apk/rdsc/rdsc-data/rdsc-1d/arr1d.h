
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef ARR1D__H
#define ARR1D__H


#include "_vec1d.h"

#include "accessors.h"

KANS_(RdSC)

template<typename VAL_Type, typename INDEX_Types = index_types<s2>, typename PR_Type = _pr_break>
class Arr1d : public _Vec1d<VAL_Type, INDEX_Types, PR_Type>,
  public each_holders<Arr1d<VAL_Type, INDEX_Types, PR_Type>,
    VAL_Type, typename INDEX_Types::Numeric_Index_type, PR_Type>
{
 using self_type = Arr1d<VAL_Type, INDEX_Types, PR_Type>;
 using base_type = _Vec1d<VAL_Type, INDEX_Types, PR_Type>;

 using nnx = typename INDEX_Types::Numeric_Nested_Index_type;
 using nx = typename INDEX_Types::Numeric_Nested_Index_type;
 using val_t = VAL_Type;

 u4 length_;

public:

 Arr1d(std::initializer_list<nx> length, typename INDEX_Types::Numeric_Nested_Index_type layer_size,
       typename INDEX_Types::Numeric_Nested_Index_type block_size = 17)
  :  _Vec1d<VAL_Type>(layer_size, block_size),
    each_holders<self_type, VAL_Type, typename INDEX_Types::Numeric_Index_type, PR_Type>({{*this}})
    //length_(length)
 {
  if(length.size() > 0)
    length_ = *length.begin();
 }

 Arr1d(std::initializer_list<nx> length)
  :  _Vec1d<VAL_Type, INDEX_Types, PR_Type>({0}),
    each_holders<self_type, VAL_Type, typename INDEX_Types::Numeric_Index_type, PR_Type>({{*this}})
    //length_(length)
 {
  if(length.size() > 0)
  {
   length_ = *length.begin();
   this->init_static_hive(length_);
  }
 }


 u4 push_back(const VAL_Type& v)
 {
  u4 sz = this->size();
  if(sz >= length_)
    return 0;
  u4 result = sz - length_;
  base_type::push_back(v);
  return result;
 }

 void init_raw_data(u4 start_index, u4 length, VAL_Type const* source)
 {
  n8* start = this->get(start_index);
  memcpy(start, source, length * this->hive_structure_->value_size());
 }

 void fetch_raw_data(u4 start_index, u4 length, VAL_Type* target)
 {
  n8* start = this->get(start_index);
  memcpy(target, start, length * this->hive_structure_->value_size());
 }

};

_KANS(RdSC)

#endif // ARR1D__H
