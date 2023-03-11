
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)



// //  this file is designed to be included multiple times.
 //    The tokens "FETCH_VARIANT_PROCEDURE_NAME [SPECIAL]" (1d and d2)
 //    and "FETCH_VARIANT_RETURN_TYPE" are redefined at least once,
 //    to generate a series of otherwise-identifcal procedures.


template<typename COLL_Type>
FETCH_VARIANT_RETURN_TYPE
Mat2d<COLL_Type>::FETCH_VARIANT_PROCEDURE_NAME_2D(nx r, nx c)
{
// if(is_symmetric())
//  return nu
////?   return typename _Mat2d_special_mode<COLL_Type>::_Sym{this}.FETCH_VARIANT_PROCEDURE_NAME_2D_SPECIAL(r, c);
// if(is_skew_symmetric())
//   return typename _Mat2d_special_mode<COLL_Type>::_Skew{this}.FETCH_VARIANT_PROCEDURE_NAME_2D_SPECIAL(r, c);
// if(is_diagonal())
//   return typename _Mat2d_special_mode<COLL_Type>::_Diag{this}.FETCH_VARIANT_PROCEDURE_NAME_2D_SPECIAL(r, c);

 if(elems_)
 {
  nx nix = 0;
  if(r <= n_rows())
  {
   if(c <= n_cols())
   {
    nix = _get_normal_index(r, c); // ((r - 1) * n_cols()) + c;
    if(nix >= (nx) elems_->size())
      nix = 0;
   }
  }
  return elems_->FETCH_VARIANT_PROCEDURE_NAME_1D(nix);
 }
}


