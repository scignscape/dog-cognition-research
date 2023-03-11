
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


// //  this file is designed to be included multiple times.
 //    The tokens "FETCH_VARIANT_PROCEDURE_NAME" (1d and d2)
 //    and "FETCH_VARIANT_RETURN_TYPE" are redefined at least once,
 //    to generate a series of otherwise-identifcal procedures.


template<typename COLL_Type>
FETCH_VARIANT_RETURN_TYPE
_Mat2d_special_mode<COLL_Type>::_Sym::FETCH_VARIANT_PROCEDURE_NAME_2D(nx r, nx c)
{
 if(_this->elems_)
 {
  _this->elems_->rebound(0, *_this->_defaultv());
//  if(_this->elems_->isEmpty())
//    elems_->push_back(*_defaultv());

  nx pos = 0;
  if( (r <= _this->n_rows()) && (c <= _this->n_rows()) )
  {
   pos = _this->get_sym_index(r, c);
   if(pos >= (nx) _this->elems_->size())
     pos = 0;
  }
  return _this->elems_->FETCH_VARIANT_PROCEDURE_NAME_1D(pos); // &(*elems_)[pos];
 }
 //?elems_ = new QVector<r8>(1);
 //?_this->elems_->rebound_first(*_this->_defaultv());
 //(*elems_)[0] = *_defaultv();
 //?return &(*elems_)[0];

}

template<typename COLL_Type>
FETCH_VARIANT_RETURN_TYPE
_Mat2d_special_mode<COLL_Type>::_Skew::FETCH_VARIANT_PROCEDURE_NAME_2D(nx r, nx c)
{
 // //  note: have to negate by client code  ...
 return _Mat2d_special_mode<COLL_Type>::_Sym{_this}.FETCH_VARIANT_PROCEDURE_NAME_1D(r, c);
}

template<typename COLL_Type>
FETCH_VARIANT_RETURN_TYPE
_Mat2d_special_mode<COLL_Type>::_Diag::FETCH_VARIANT_PROCEDURE_NAME_2D(nx r, nx c)
{
 nx nix = 0;

 if(r <= _this->n_rows())
 {
  if(c <= _this->n_cols())
  {
   if(r == c)
     nix = r;
  }
 }
 if(_this->elems_)
   return _this->elems_->FETCH_VARIANT_PROCEDURE_NAME_1D(nix);

//?
// elems_ = new QVector<r8>(1);
// (*elems_)[0] = *_defaultv();
// return &(*elems_)[0];
}




_XCNS(RdSC)

//typename COLL_Type::Numeric_Index_type
//_total_size<COLL_Type, Mat2d<COLL_Type>::special_mode::Sym>(Mat2d<COLL_Type>& _this)
//{
// typename COLL_Type::Numeric_Index_type n = _this.n_rows();
// return (n * (n + 1)) / 2;
//}



#ifdef HIDE

template<typename COLL_Type>
template<typename Mat2d<COLL_Type>::special_mode>
typename COLL_Type::Numeric_Index_type
Mat2d<COLL_Type>::_total_size<Mat2d<COLL_Type>::special_mode::Sym>()
{
 nx n = n_rows();
 return (n * (n + 1)) / 2;
}

template<typename COLL_Type>
template<typename Mat2d<COLL_Type>::special_mode>
typename COLL_Type::Numeric_Index_type
Mat2d<COLL_Type>::_total_size<Mat2d<COLL_Type>::special_mode::Skew>()
{
 return _total_size<Mat2d<COLL_Type>::special_mode::Sym>();
}

template<typename COLL_Type>
template<>
typename COLL_Type::Numeric_Index_type
Mat2d<COLL_Type>::_total_size<Mat2d<COLL_Type>::special_mode::Diag>()
{
 return get_diagonal_length();
}

template<typename COLL_Type>
typename COLL_Type::Numeric_Index_type
Mat2d<COLL_Type>::get_sym_index(nx r, nx c)
{
 // // assumes r, c are in bounds
 nx result = 0;

 if(is_cmajor())
 {
  if(c < r)
    // //  treat them as if they're flipped
    result = ( (r * (r - 1)) / 2 ) + c;
  else
    result = ( (c * (c - 1)) / 2 ) + r;
 }
 else
 {
  if(c < r)
    // //  treat them as if they're flipped
    result = ( (c - 1)*n_cols() ) - ( (c - 2)*(c - 1) )/2 + (r - (c - 1));
  else
    result = ( (r - 1)*n_cols() ) - ( (r - 2)*(r - 1) )/2 + (c - (r - 1)) ;
 }
 return result;

}

template<typename COLL_Type>
template<>
typename COLL_Type::Numeric_Index_type
Mat2d<COLL_Type>::_get_index<Mat2d<COLL_Type>::special_mode::Sym>(nx r, nx c)
{
 if(r > n_rows())
   return 0;
 if(c > n_rows())
   return 0;

 return get_sym_index(r, c);
}

template<typename COLL_Type>
template<>
typename COLL_Type::Numeric_Index_type
Mat2d<COLL_Type>::_get_index<Mat2d<COLL_Type>::special_mode::Skew>(nx r, nx c)
{
 return _get_index<QVector_Matrix_R8::special_mode::Sym>(r, c);
}

template<typename COLL_Type>
template<>
typename COLL_Type::Numeric_Index_type
Mat2d<COLL_Type>::_get_index<Mat2d<COLL_Type>::special_mode::Diag>(nx r, nx c)
{
 if(r > n_rows())
   return 0;
 if(c > n_cols())
   return 0;
 return r;
}

#endif
