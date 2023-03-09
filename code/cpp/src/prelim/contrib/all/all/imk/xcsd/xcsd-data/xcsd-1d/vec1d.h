
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef VEC1D__H
#define VEC1D__H


#include "_vec1d.h"

XCNS_(XCSD)

template<typename VAL_Type, typename INDEX_Types = index_types<s2>, typename PR_Type = _pr_break>
class Vec1d : public _Vec1d<VAL_Type, INDEX_Types, PR_Type>,
   public each_holders<Vec1d<VAL_Type, INDEX_Types, PR_Type>, VAL_Type, typename INDEX_Types::Numeric_Index_type, PR_Type>
{
 using self_type = Vec1d<VAL_Type, INDEX_Types, PR_Type>;

 using nnx = typename INDEX_Types::Numeric_Nested_Index_type;
 using nx = typename INDEX_Types::Numeric_Nested_Index_type;
 using val_t = VAL_Type;

public:

 using Value_type = VAL_Type;

 Vec1d(nnx layer_size = 15, nnx block_size = 17)
  :  _Vec1d<VAL_Type, INDEX_Types, PR_Type>(layer_size, block_size),
    each_holders<self_type, VAL_Type, typename INDEX_Types::Numeric_Index_type, PR_Type>({{*this}})
 {
 }

 Vec1d(std::initializer_list<nx> initial_size, nnx layer_size, nnx block_size)
  :  _Vec1d<VAL_Type, INDEX_Types, PR_Type>(layer_size, block_size),
    each_holders<self_type, VAL_Type, typename INDEX_Types::Numeric_Index_type, PR_Type>({{*this}})
 {
  if(initial_size.size() > 0)
    this->resize(*initial_size.begin());
 }

 Vec1d(std::initializer_list<nx> initial_size)
  :  _Vec1d<VAL_Type, INDEX_Types, PR_Type>(initial_size),
    each_holders<self_type, VAL_Type, typename INDEX_Types::Numeric_Index_type, PR_Type>({{*this}})
 {
  if(initial_size.size() > 0)
  {
   this->resize(*initial_size.begin());
  }
 }


};

_XCNS(XCSD)

#endif // VEC1D__H
