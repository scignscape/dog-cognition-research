
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include "mat2d.h"

#include <QFile>
#include <QDataStream>

template<typename COLL_Type>
Mat2d<COLL_Type>::Mat2d(nx r, nx c, nnx layer_size, nnx block_size)
  : n_rows_(r << 1), n_cols_(c << 1), elems_((r && c)?
    new COLL_Type(layer_size, block_size) : nullptr)
{
 if(elems_)
   elems_->declare_size(r * c + 1);

}

template<typename COLL_Type>
Mat2d<COLL_Type>::Mat2d(nx r, nx c, Layer_Options layer_option)
  : n_rows_(r << 1), n_cols_(c << 1)
{
 if(layer_option == Layer_Options::Fixed_Preinit)
 {
  elems_ = new COLL_Type(c, r);
  elems_->declare_size(r * c);
  elems_->preinit_all_layers();
 }
 else if(layer_option == Layer_Options::Fixed)
 {
  elems_ = new COLL_Type(c, r);
  elems_->declare_size(r * c);
 }

}



template<typename COLL_Type>
typename COLL_Type::Numeric_Index_type Mat2d<COLL_Type>::n_rows() const
{
 return n_rows_ >> 1;
}

template<typename COLL_Type>
void Mat2d<COLL_Type>::set_n_rows(nx n_rows)
{
 n_rows_ = n_rows << 1;
}

template<typename COLL_Type>
typename COLL_Type::Numeric_Index_type
Mat2d<COLL_Type>::n_cols() const
{
 if(n_cols_ <= 1)
   return n_rows();
 return n_cols_ >> 1;
}

template<typename COLL_Type>
void Mat2d<COLL_Type>::set_n_cols(nx n_cols)
{
 n_cols_ = n_cols << 1;
}

//template<typename OBJ_Type,
//  typename Test = std::enable_if<std::is_default_constructible<OBJ_Type>::value>>
//void _construct_(OBJ_Type* obj);



template<typename COLL_Type>
typename COLL_Type::Value_type*
Mat2d<COLL_Type>::_defaultv(val_t** reset)
{
 static val_t* result = nullptr;
 if(reset)
   result = *reset;
 else
   COLL_Type::default_construct_if_needed_and_possible(&result);
  //_check_construct<COLL_Type::Value_type>(result);
 return result;
}


template<typename COLL_Type>
void Mat2d<COLL_Type>::set_default_value(val_t defaultv)
{
 elems_->first() = defaultv;
}


template<typename COLL_Type>
typename Mat2d<COLL_Type>::nx Mat2d<COLL_Type>::_get_normal_index(nx r, nx c)
{
 if(is_cmajor())
   return ((c - 1) * n_rows()) + r;
 return ((r - 1) * n_cols()) + c;
}


template<typename COLL_Type>
typename Mat2d<COLL_Type>::_one_opbracket
  Mat2d<COLL_Type>::operator[](nx r)
{
 return {*this, r};
}


template<typename COLL_Type>
typename Mat2d<COLL_Type>::val_t&
  Mat2d<COLL_Type>::_one_opbracket::operator[](nx c)
{
 return *_this.get(row, c);
}

template<typename COLL_Type>
typename Mat2d<COLL_Type>::val_t
  Mat2d<COLL_Type>::_one_opbracket::operator()(nx c)
{
 return _this.get_value(row, c);
}

template<typename COLL_Type>
typename Mat2d<COLL_Type>::val_t
  Mat2d<COLL_Type>::_one_opbracket::operator()(nx c, const val_t& defaultv)
{
 return _this.value(row, c, defaultv);
}




template<typename COLL_Type>
void Mat2d<COLL_Type>::data_to_qvector(QVector<val_t>& result)
{
 result.resize(total_size() + 1);
 Action_scan(std::copy, result, (*elems_), 0, total_size());
}

template<typename COLL_Type>
void Mat2d<COLL_Type>::data_from_qvector(const QVector<val_t>& source)
{
 Action_span(std::copy, source, (*elems_), 0, total_size());
}



//QVector_Matrix_val_t::QVector_Matrix_val_t(nx r, nx c, val_t defaultv)
// : n_rows_(r << 1), n_cols_(c << 1),
//   elems_( (r && c)? new QVector<val_t>((r * c) + 1) : nullptr)
//{
// if(elems_)
//   (*elems_)[0] = defaultv;
//}


template<typename COLL_Type>
void Mat2d<COLL_Type>::resize(nx r, nx c)
{
 set_n_rows(r);
 set_n_cols(c);
 resize(r * c);
}

template<typename COLL_Type>
void Mat2d<COLL_Type>::resize(nx total)
{
 if(!elems_)
 {
  elems_ = new COLL_Type();
 }

 elems_->resize(total + 1);
}


template<typename VALUE_Type>
inline VALUE_Type _get_zero()
{
 return 0;
}

template<>
inline QString _get_zero<QString>()
{
 return {};
}



template<typename COLL_Type>
void Mat2d<COLL_Type>::fill(val_t value, val_t default_value,
  nnx layer_size, nnx block_size, bool force)
{
 if(elems_)
 {
  nx s = elems_->size();
  elems_->resize(total_size() + 1);
  if( (value != _get_zero<val_t>()) || force )
  {
   if(force)
   {
    for(nx i = 0; i < elems_->size(); ++i)
    {
     // //  there should really be a separate process
      //    for the operator new here, not just
      //    calling this function with "force" ...
     val_t* v = elems_->get(i);
     val_t* vv = new (v) val_t(value);
    }
   }
   else
   {
    for(nx i = s; i < elems_->size(); ++i)
    {
     elems_->at_index(i) = value;
     //(*elems_)[s] = value;
    }
   }
  }
 }
 else
 {
  elems_ = new COLL_Type(layer_size, block_size);
    //new QVector<val_t>(total_size() + 1, value);
  elems_->first() = default_value;
  auto it = elems_->iterator_at(1);
  elems_->fill(it, value, it._end());
 }
}

template<typename COLL_Type>
void Mat2d<COLL_Type>::get_extrema(QPair<val_t, val_t>& result)
{
 QVector<QPair<val_t, val_t>> extrema;
 if(is_rmajor())
   get_row_extrema(extrema);
 else
   get_column_extrema(extrema);

 result = std::accumulate(extrema.begin(), extrema.end(),
   QPair<val_t, val_t> {std::numeric_limits<val_t>::max(), std::numeric_limits<val_t>::min()},
   [](QPair<val_t, val_t> pr1, QPair<val_t, val_t> pr2) -> QPair<val_t, val_t>
 {
  return {qMin(pr1.first, pr2.first), qMax(pr2.second, pr2.second)};
 });
}

template<typename COLL_Type>
Mat2d<COLL_Type>* Mat2d<COLL_Type>::percentile_breakdown(u1 max)
{
 QPair<val_t, val_t> extrema;
 get_extrema(extrema);

 Mat2d<COLL_Type>* result = new Mat2d<COLL_Type>;
 result->set_n_rows(max + 1);
 result->set_n_cols(n_cols());
 result->fill();

  // // for each column, aggregate all entries into percentiles.
   //   Currently not optimized for data access at all ...
 for(nx c = 1; c <= n_cols(); ++c)
 {
  for(nx r = 1; r <= n_rows(); ++r)
  {
   val_t rr = get_at(r, c);
   val_t _percentile = (rr - extrema.first) / (extrema.second - extrema.first);
   u1 percentile = (_percentile * max) + 1;
   //?
   ++(*result)[percentile][c];
  }
 }
 return result;
}

template<typename COLL_Type>
Mat2d<COLL_Type>* Mat2d<COLL_Type>::percentile_rescale(u1 max)
{
 QPair<val_t, val_t> extrema;
 get_extrema(extrema);

 Mat2d<COLL_Type>* result = new_from_dimensions();

  // // for each column, aggregate all entries into percentiles.
   //   Currently not optimized for data access at all ...
 for(nx c = 1; c <= n_cols(); ++c)
 {
  for(nx r = 1; r <= n_rows(); ++r)
  {
   val_t rr = get_at(r, c);
   val_t _percentile = (rr - extrema.first) / (extrema.second - extrema.first);
   u1 percentile = (_percentile * max) + 1;
   //?
   (*result)[r][c] = percentile;
  }
 }
 return result;
}

template<typename COLL_Type>
void Mat2d<COLL_Type>::merge_row(const QVector<val_t>& vec, nx row)
{
 if(is_diagonal())
 {
  if(row <= n_cols())
    (*this)[row][row] = vec.value(row - 1);
  return;
 }
 if(is_symmetric() || is_skew_symmetric())
 {
  for(nx c = 1; c <= n_cols(); ++c)
  {
   (*this)[row][c] = vec.value(c - 1);
  }
  return;
 }
 if(is_cmajor())
 {
  //?for(nx c = 1; c <= n_cols(); ++c)
  for(nx index = row, i = 0; i < n_cols(); ++i, index += n_rows())
  {
   //?nx index = r + (c - 1) * n_rows();
   (*elems_)[index] = vec.value(i);
  }
  return;
 }

 nx index = 1 + ((row - 1) * n_cols());

 // //  maybe a macro here?

// Contiguous_breakdown(std::copy, vec, (*elems_), index, index + vec.size());
 Action_scan(std::copy, vec, (*elems_), index, index + vec.size());

// QVector<QPair<int*, s2>> breakdown;
// if(int* it = vec.contiguous(index, index + vec.size(), breakdown))
// {
//  std::copy(vec.begin(), vec.end(), it);
// }
// else
// {
//  auto it1 = vec.begin();
//  for(QPair<int*, s2> pr : breakdown)
//  {
//   std::copy(it1, it1 + pr.second, pr.first);
//   it1 += pr.second;
//  }
// }

 //? std::copy(vec.begin(), vec.end(), elems_->begin() + index);

// for(nx i = 0; i < n_cols(); ++i, ++index)
// {
//  (*elems_)[index] = vec[i];
// }
}

template<typename COLL_Type>
void Mat2d<COLL_Type>::get_column_extrema(QVector<QPair<val_t, val_t>>& result)
{
 result.resize(n_cols());
 for(nx c = 1; c <= n_cols(); ++c)
 {
  result[c - 1] = get_extrema_in_column(c);
 }
}

template<typename COLL_Type>
void Mat2d<COLL_Type>::get_row_extrema(QVector<QPair<val_t, val_t>>& result)
{
 result.resize(n_rows());
 for(nx r = 1; r <= n_rows(); ++r)
 {
  result[r - 1] = get_extrema_in_row(r);
 }
}

template<typename COLL_Type>
void Mat2d<COLL_Type>::get_column_minima(QVector<val_t>& result)
{
 result.resize(n_cols());
 for(nx c = 1; c <= n_cols(); ++c)
 {
  result[c - 1] = get_minimum_in_column(c);
 }
}

template<typename COLL_Type>
void Mat2d<COLL_Type>::get_row_minima(QVector<val_t>& result)
{
 result.resize(n_rows());
 for(nx r = 1; r <= n_rows(); ++r)
 {
  result[r - 1] = get_minimum_in_column(r);
 }
}

template<typename COLL_Type>
void Mat2d<COLL_Type>::get_column_maxima(QVector<val_t>& result)
{
 result.resize(n_cols());
 for(nx c = 1; c <= n_cols(); ++c)
 {
  result[c - 1] = get_maximum_in_column(c);
 }
}

template<typename COLL_Type>
void Mat2d<COLL_Type>::get_row_maxima(QVector<val_t>& result)
{
 result.resize(n_rows());
 for(nx r = 1; r <= n_rows(); ++r)
 {
  result[r - 1] = get_maximum_in_column(r);
 }
}

template<typename COLL_Type>
void Mat2d<COLL_Type>::multiply(const QVector<val_t>& vec, QVector<val_t>& result)
{
 result.resize(vec.size());
 nx r = 1;
 std::transform(vec.begin(), vec.end(), result.begin(), [&r, &vec, this](val_t rr) -> val_t
 {
  val_t result = 0;
  for(nx c = 1; c <= (nx) vec.size(); ++c)
  {
   result += (rr * get_at(r, c));
  }
  ++r;
  return result;
 });
}

template<typename COLL_Type>
void Mat2d<COLL_Type>::retire()
{
 delete elems_;
 elems_ = nullptr;
}

template<typename COLL_Type>
void Mat2d<COLL_Type>::reset_no_retire(const Mat2d<COLL_Type>& rhs)
{
 n_rows_ = rhs.n_rows_;
 n_cols_ = rhs.n_cols_;
 elems_ = rhs.elems_;
}

template<typename COLL_Type>
void Mat2d<COLL_Type>::reset(const Mat2d<COLL_Type>& rhs)
{
 delete elems_;
 n_rows_ = rhs.n_rows_;
 n_cols_ = rhs.n_cols_;
 elems_ = rhs.elems_;
}

template<typename COLL_Type>
void Mat2d<COLL_Type>::fill_diagonal(val_t diag_value, val_t other_value, val_t default_value)
{
 fill(other_value, default_value);
 nx qm = qMin(n_rows(), n_cols());
 for(nx u = 1; u <= qm; ++u)
 {
  (*this)[u][u] = diag_value;
 }
}

template<typename COLL_Type>
void Mat2d<COLL_Type>::fill_diagonal_only(val_t val)
{
 nx len = qMin(n_rows(), n_cols());
 nx elen = 1 + (len * len);
 if(!elems_)
   elems_ = new QVector<val_t>(elen);
 else if((nx) elems_->size() < elen)
   elems_->resize(elen);

 for(nx i = 1; i <= len; ++i)
 {
  val_t* rr = get(i, i);
  if(rr)
    *rr = val;
  else
    qDebug() << "Unexpected condition at " << __FILE__ << ", line " << __LINE__;
 }
}

template<typename COLL_Type>
typename Mat2d<COLL_Type>::val_t Mat2d<COLL_Type>::get_minimum_in_column(nx c)
{
 if(is_diagonal())
   return qMin(get_at(c, c), 0.);

 val_t result = 0;
 if(is_symmetric_or_skew_symmetric())
 {
  // just brute force ...
  for(nx r = 1; r <= n_rows(); ++r)
  {
   val_t rr = get_at(r, c);
   if(rr < result)
     result = rr;
  }
 }

 else if(is_cmajor())
 {
  nx index = (n_rows() * (c - 1)) + 1;
  for(nx i = 0; i < n_rows(); ++i, ++index)
  {
   val_t rr = get_at_index(index);
   if(rr < result)
     result = rr;

   // just brute force ...
   //val_t rr = get_at(i + 1, c);
   //if(rr < result)
   //  result = rr;

  }
 }

 else
 {
  nx nc = n_cols();
  nx nr = n_rows();
  nx index = c;
  for(nx r = 0; r < nr; ++r, index += nc)
  {
   val_t rr = get_at_index(index);
   if(rr < result)
     result = rr;
  }
 }
 return result;
}

template<typename COLL_Type>
typename Mat2d<COLL_Type>::val_t Mat2d<COLL_Type>::get_maximum_in_column(nx c)
{
 if(is_diagonal())
   return qMax(get_at(c, c), 0.);

 val_t result = 0;
 if(is_symmetric_or_skew_symmetric())
 {
  // just brute force ...
  for(nx r = 1; r <= n_rows(); ++r)
  {
   val_t rr = get_at(r, c);
   if(rr > result)
     result = rr;
  }
 }

 else if(is_cmajor())
 {
  nx index = (n_rows() * (c - 1)) + 1;
  for(nx i = 0; i < n_rows(); ++i, ++index)
  {
   val_t rr = get_at_index(index);
   if(rr > result)
     result = rr;
  }
 }

 else
 {
  nx nc = n_cols();
  nx nr = n_rows();
  nx index = c;
  for(nx r = 0; r < nr; ++r, index += nc)
  {
   val_t rr = get_at_index(index);
   if(rr > result)
     result = rr;
  }
 }
 return result;
}

template<typename COLL_Type>
typename Mat2d<COLL_Type>::val_t
Mat2d<COLL_Type>::get_minimum_in_row(nx r)
{
 if(is_diagonal())
   return qMin(get_at(r, r), 0.);

 val_t result = 0;
 if(is_symmetric_or_skew_symmetric())
 {
  // just brute force ...
  for(nx c = 1; c <= n_cols(); ++c)
  {
   val_t rr = get_at(r, c);
   if(rr < result)
     result = rr;
  }
 }

 else if(is_cmajor())
 {
  nx nc = n_cols();
  nx nr = n_rows();
  nx index = r;
  for(nx c = 0; c < nc; ++c, index += nr)
  {
   val_t rr = get_at_index(index);
   if(rr < result)
     result = rr;
  }
 }

 else
 {
  nx index = (n_cols() * (r - 1)) + 1;
  for(nx i = 0; i < n_cols(); ++i, ++index)
  {
   val_t rr = get_at_index(index);
   if(rr < result)
     result = rr;
  }
 }
 return result;
}

template<typename COLL_Type>
typename Mat2d<COLL_Type>::val_t Mat2d<COLL_Type>::get_maximum_in_row(nx r)
{
 if(is_diagonal())
   return qMin(get_at(r, r), 0.);

 val_t result = 0;
 if(is_symmetric_or_skew_symmetric())
 {
  // just brute force ...
  for(nx c = 1; c <= n_cols(); ++c)
  {
   val_t rr = get_at(r, c);
   if(rr > result)
     result = rr;
  }
 }

 else if(is_cmajor())
 {
  nx nc = n_cols();
  nx nr = n_rows();
  nx index = r;
  for(nx c = 0; c < nc; ++c, index += nr)
  {
   val_t rr = get_at_index(index);
   if(rr > result)
     result = rr;
  }
 }

 else
 {
  nx index = (n_cols() * (r - 1)) + 1;
  for(nx i = 0; i < n_cols(); ++i, ++index)
  {
   val_t rr = get_at_index(index);
   if(rr > result)
     result = rr;
  }
 }
 return result;
}

template<typename COLL_Type>
void Mat2d<COLL_Type>::get_row(nx r, QVector<val_t>& row)
{
 row.resize(n_cols());
 if(is_diagonal())
 {
  row.fill(0);
  if(r <= n_cols())
    row[r - 1] = at(r, r);
  return;
 }
 if(is_symmetric() || is_skew_symmetric())
 {
  for(nx c = 1; c <= n_cols(); ++c)
  {
   row[c - 1] = get_at(r, c);
  }
  return;
 }
 if(is_cmajor())
 {
  //for(nx c = 1; c <= n_cols(); ++c)
  for(nx index = r, i = 0; i < n_cols(); ++i, index += n_rows())
  {
   //nx index = r + (c - 1) * n_rows();
   row[i] = elems_->value(index);
  }
  return;
 }

 nx index = 1 + ((r - 1) * n_cols());

// std::copy(elems_->begin() + index, elems_->begin() + index + n_cols(), row.begin());
// Contiguous_breakdown(std::copy, vec, index, index + vec.size());

 Action_span(std::copy, row, (*elems_), index, index + n_cols());


//  QVector<QPair<typename decltype(&elems_)::Element_type*,
//    typename decltype(&elems_)::Numeric_Index_type>> breakdown;
//  if(int* it = (&elems_).contiguous(index, index + n_cols(), breakdown))
//  {
//   std::copy(it, index + n_cols(), row.begin());
//  }
//  else
//  {
//   auto it1 = row.begin();
//   for(QPair<int*, s2> pr : breakdown)
//   {
//    std::copy(pr.first, pr.first + pr.second, it1);
//    it1 += pr.second;
//   }
//  }


// for(nx i = 0; i < n_cols(); ++i, ++index)
// {
//  row[i] = elems_->value(index);
// }
}

template<typename COLL_Type>
Mat2d<COLL_Type>* Mat2d<COLL_Type>::new_from_dimensions()
{
 return new Mat2d(n_rows(), n_cols());
}

template<typename COLL_Type>
void Mat2d<COLL_Type>::save_to_datastream(QDataStream& qds)
{
 QVector<val_t> elems_vector;
 data_to_qvector(elems_vector);
 qds << n_rows_ << n_cols_ << elems_vector;
}

template<typename COLL_Type>
void Mat2d<COLL_Type>::load_from_datastream(QDataStream& qds)
{
 //elems_ = new QVector<r8>;
 QVector<val_t> elems_vector;
 qds >> n_rows_ >> n_cols_ >> elems_vector;
 data_from_qvector(elems_vector);
}

template<typename COLL_Type>
void Mat2d<COLL_Type>::save_to_file(QString path)
{
 QFile qf(path);
 if(!qf.open( QIODevice::WriteOnly ))
   return;
 QDataStream qds(&qf);
 save_to_datastream(qds);
 qf.close();
}

template<typename COLL_Type>
void Mat2d<COLL_Type>::load_from_file(QString path)
{
 QFile qf(path);
 if(!qf.open( QIODevice::ReadOnly ))
   return;
 QDataStream qds(&qf);
 load_from_datastream(qds);
 qf.close();
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

#include "mat2d.templates.special-modes.h"

template<typename COLL_Type>
void Mat2d<COLL_Type>::set_dimensions(nx r, nx c)
{
 set_n_rows(r);
 set_n_cols(c);
}

template<typename COLL_Type>
typename COLL_Type::Numeric_Index_type
Mat2d<COLL_Type>::total_size()
{
 if(is_symmetric())
   return typename _Mat2d_special_mode<COLL_Type>::_Sym{this}._total_size();
 if(is_skew_symmetric())
   return typename _Mat2d_special_mode<COLL_Type>::_Skew{this}._total_size();
 if(is_diagonal())
   return typename _Mat2d_special_mode<COLL_Type>::_Diag{this}._total_size();

 return n_rows() * n_cols();
}


#define FETCH_VARIANT_PROCEDURE_NAME_2D fetch
#define FETCH_VARIANT_PROCEDURE_NAME_2D_SPECIAL _fetch
#define FETCH_VARIANT_PROCEDURE_NAME_1D get
#define FETCH_VARIANT_RETURN_TYPE typename COLL_Type::Value_type*
#include "mat2d.templates_fetch.h"
#undef RETURN_TYPE
#undef FETCH_VARIANT_PROCEDURE_NAME_1D
#undef FETCH_VARIANT_PROCEDURE_NAME_2D

#define FETCH_VARIANT_PROCEDURE_NAME_2D fetch_raw
#define FETCH_VARIANT_PROCEDURE_NAME_2D_SPECIAL _fetch_raw
#define FETCH_VARIANT_PROCEDURE_NAME_1D fetch_raw
#define FETCH_VARIANT_RETURN_TYPE void*
#include "mat2d.templates_fetch.h"
#undef RETURN_TYPE
#undef FETCH_VARIANT_PROCEDURE_NAME_1D
#undef FETCH_VARIANT_PROCEDURE_NAME_2D_SPECIAL
#undef FETCH_VARIANT_PROCEDURE_NAME_2D




//template<typename COLL_Type>
//typename COLL_Type::Value_type*
//Mat2d<COLL_Type>::fetch(nx r, nx c)
//{
// if(is_symmetric())
//   return typename _Mat2d_special_mode<COLL_Type>::_Sym{this}._fetch(r, c);
// if(is_skew_symmetric())
//   return typename _Mat2d_special_mode<COLL_Type>::_Skew{this}._fetch(r, c);
// if(is_diagonal())
//   return typename _Mat2d_special_mode<COLL_Type>::_Diag{this}._fetch(r, c);

// if(elems_)
// {
//  nx nix = 0;
//  if(r <= n_rows())
//  {
//   if(c <= n_cols())
//   {
//    nix = _get_normal_index(r, c); // ((r - 1) * n_cols()) + c;
//    if(nix >= (nx) elems_->size())
//      nix = 0;
//   }
//  }
//  return elems_->get(nix);
// }
//// elems_ = new QVector<r8>(1);
//// (*elems_)[0] = *_defaultv();
//// return &(*elems_)[0];
//}

//template<typename COLL_Type>
//typename COLL_Type::Value_type*
//Mat2d<COLL_Type>::fetch(nx r, nx c)
//{
// val_t* fetch_raw(nx r, nx c);

//}


template<typename COLL_Type>
const typename COLL_Type::Value_type&
Mat2d<COLL_Type>::at(nx r, nx c)
{
 if(is_symmetric())
   return typename _Mat2d_special_mode<COLL_Type>::_Sym{this}._at(r, c);
 if(is_skew_symmetric())
   return typename _Mat2d_special_mode<COLL_Type>::_Skew{this}._at(r, c);
 if(is_diagonal())
   return typename _Mat2d_special_mode<COLL_Type>::_Diag{this}._at(r, c);

 return *fetch(r, c);
}

// // keep this?
template<typename COLL_Type>
typename COLL_Type::Value_type
Mat2d<COLL_Type>::get_value(nx r, nx c)
{
if(is_skew_symmetric() && (c < r))
  return (val_t)  -(signed long) at(c, r);
return at(r, c);
}

template<typename COLL_Type>
typename COLL_Type::Value_type
Mat2d<COLL_Type>::get_at(nx r, nx c)
{
if(is_skew_symmetric() && (c < r))
  return -at(c, r);
return at(r, c);
}

template<typename COLL_Type>
typename COLL_Type::Value_type
Mat2d<COLL_Type>::get_at_index(nx nix)
{
 if(elems_)
 {
  if(nix < elems_->total_size())
    return elems_->get(nix);
  if(elems_->is_empty())
    return *_defaultv();
  return elems_->first();
 }
 return *_defaultv();
}


template<typename COLL_Type>
typename COLL_Type::Value_type*
Mat2d<COLL_Type>::get(nx r, nx c)
{
 if(is_symmetric())
   return typename _Mat2d_special_mode<COLL_Type>::_Sym{this}._get(r, c);
 if(is_skew_symmetric())
   return typename _Mat2d_special_mode<COLL_Type>::_Skew{this}._get(r, c);
 if(is_diagonal())
   return typename _Mat2d_special_mode<COLL_Type>::_Diag{this}._get(r, c);

 if(elems_)
 {
  if(r > n_rows())
    return nullptr;
  if(c > n_cols())
    return nullptr;

  nx nix = _get_normal_index(r, c); // ((r - 1) * n_cols()) + c;
  if(nix >= (nx) elems_->size())
    return nullptr;

  return elems_->get(nix);
 }
 return nullptr;
}

