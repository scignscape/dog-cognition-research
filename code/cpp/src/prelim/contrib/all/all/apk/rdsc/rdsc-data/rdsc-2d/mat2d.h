
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef MAT2D__H
#define MAT2D__H


#include "rdsc-1d/_vec1d.h"

#include "coords2d.h"

//#include "rdsc-1d/vec1d.h"


#include "accessors.h"

XCNS_(XCSD)

// template<typename VAL_Type, typename = index_types<s2>,
//typename = _pr_break> class

enum class Mat2d_special_mode {
 Sym, Skew, Diag
};

enum class Mat2d_special_mode_x {
 N_A, Sym, Skew, Diag, ED, Sym_ED, Skew_ED, Diag_ED,
};

enum class Mat2d_special_mode_for_raw_data {
 Normal, ED, CM, ED_CM
};

template<typename COLL_Type>
struct _Mat2d_special_mode;


template<typename COLL_Type>
class Mat2d
{
 using nnx = typename COLL_Type::Numeric_Nested_Index_type;
 using nx = typename COLL_Type::Numeric_Index_type;
 using val_t = typename COLL_Type::Value_type;

 nx n_rows_;
 nx n_cols_;

 struct _one_opbracket
 {
  Mat2d& _this;
  nx row;
  val_t& operator[](nx c);
  val_t operator()(nx c);
  val_t operator()(nx c, const val_t& defaultv);
 };


 struct _from_raw_data_special
 {
  Mat2d& _this;
  Mat2d_special_mode_for_raw_data mfrd;

  _from_raw_data_special cmajor()
  {
   return ( (mfrd == Mat2d_special_mode_for_raw_data::ED)
       || (mfrd == Mat2d_special_mode_for_raw_data::ED_CM) )
     ? _from_raw_data_special{_this, Mat2d_special_mode_for_raw_data::ED_CM}
     : _from_raw_data_special{_this, Mat2d_special_mode_for_raw_data::CM};
  }

  void cmajor(const QByteArray& qba, QPair<nx, nx> dims = {0, 0}, val_t defaultv = 0);
  void _diagonal(const QByteArray& qba, QPair<nx, nx> dims = {0, 0}, val_t defaultv = 0);
  void _symmetric(const QByteArray& qba, QPair<nx, nx> dims = {0, 0}, val_t defaultv = 0);
  void _skew_symmetric(const QByteArray& qba,
    QPair<nx, nx> dims = {0, 0}, val_t defaultv = 0);

  void diagonal(const QByteArray& qba, QVector<nx> dims = {0, 0}, val_t defaultv = 0)
  {
   _diagonal(qba, {dims.value(0), dims.value(1, dims.value(0))}, defaultv);
  }

  void symmetric(const QByteArray& qba, QVector<nx> dims = {0, 0}, val_t defaultv = 0)
  {
   _symmetric(qba, {dims.value(0), dims.value(1, dims.value(0))}, defaultv);
  }

  void skew_symmetric(const QByteArray& qba,
    QVector<nx> dims = {0, 0}, val_t defaultv = 0)
  {
   _skew_symmetric(qba, {dims.value(0), dims.value(1, dims.value(0))}, defaultv);
  }

 };

//?
// template<special_mode>
// const val_t& _at(nx r, nx c);

// template<special_mode>
// val_t* _get(nx r, nx c);

// template<special_mode>
// val_t* _fetch(nx r, nx c);

// template<special_mode>
// val_t _value(nx r, nx c);

// template<special_mode>
// val_t _value(nx r, nx c, val_t defaultv);

// template<special_mode>
// nx _total_size();

// template<special_mode>
// nx _get_index(nx r, nx c);

 nx _get_normal_index(nx r, nx c);

 nx get_sym_index(nx r, nx c);

 void default_init(nx len);

 static val_t* _defaultv(val_t** reset = nullptr);

 void _to_raw_data(QByteArray& qba, nx offset, nx count);

 void _from_raw_data(const QByteArray& qba, QPair<nx, nx> dims, val_t defaultv,
   nx total_size = 0);

 void _from_raw_data_with_encoded_default(const QByteArray& qba,
   QPair<nx, nx> dims, nx total_size = 0);

 void _from_raw_data(const QByteArray& qba, QPair<nx, nx> dims,
   val_t defaultv, Mat2d_special_mode_x smx);

 COLL_Type* elems_;

 friend struct _Mat2d_special_mode<COLL_Type>;

public:

 enum Layer_Options {
   Fixed, Fixed_Preinit, Specified, Resizable
 };

 Mat2d(nx r = 0, nx c = 0, nnx layer_size = 15, nnx block_size = 17);
 Mat2d(nx r, nx c, Layer_Options layer_option);

 void set_default_value(val_t defaultv);

 ACCESSORS__DECLARE(nx ,n_rows)
 ACCESSORS__DECLARE(nx ,n_cols)

 Mat2d* new_from_dimensions();

 Mat2d* percentile_breakdown(u1 max = 100);
 Mat2d* percentile_rescale(u1 max = 100);

 void fill(val_t value, val_t default_value, nnx layer_size = 15, nnx block_size = 17,
   bool force = false);
 void fill_with_default(val_t value, nnx layer_size = 15, nnx block_size = 17)
 {
  fill(value, value, layer_size, block_size, true);
 }

 void fill(val_t value = 0, nnx layer_size = 15, nnx block_size = 17)
 {
  fill(value, value, layer_size, block_size);
 }

 void retire();
 void reset_no_retire(const Mat2d& rhs);
 void reset(const Mat2d& rhs);

 void data_to_qvector(QVector<val_t>& result);
 void data_from_qvector(const QVector<val_t>& source);


 void get_row(nx r, QVector<val_t>& row);

 template<typename T>
 void _show(T& tt, u1 digits = 8)
 {
  for(nx r = 1; r <= n_rows(); ++r)
  {
   for(nx c = 1; c <= n_cols(); ++c)
   {
    tt << QString("%1").arg(value(r, c), -digits);
   }
   tt << '\n';
  }
 }

 template<typename T>
 void show(T& tt, u1 digits = 8)
 {
  _show(tt, digits);
 }

 template<typename T>
 void show(T tt, u1 digits = 8)
 {
  _show(tt, digits);
 }

 val_t get_minimum_in_column(nx c);
 val_t get_maximum_in_column(nx c);

 void get_extrema(QPair<val_t, val_t>& result);

 void get_column_extrema(QVector<QPair<val_t, val_t>>& result);
 void get_row_extrema(QVector<QPair<val_t, val_t>>& result);
 void get_column_maxima(QVector<val_t>& result);
 void get_row_maxima(QVector<val_t>& result);
 void get_column_minima(QVector<val_t>& result);
 void get_row_minima(QVector<val_t>& result);

 QPair<val_t, val_t> get_extrema_in_column(nx c)
 {
  return {get_minimum_in_column(c), get_maximum_in_column(c)};
 }

 QPair<val_t, val_t> get_extrema_in_row(nx r)
 {
  return {get_minimum_in_row(r), get_maximum_in_row(r)};
 }

 val_t get_minimum_in_row(nx r);
 val_t get_maximum_in_row(nx r);

 void symmetric(nx n_rows);
 void skew_symmetric(nx n_rows);
 void diagonal(nx n_rows);
 void diagonal(nx n_rows, nx n_cols);
 void diagonal();
 void rmajor();
 void cmajor();

 void save_to_file(QString path);
 void load_from_file(QString path);

 void save_to_datastream(QDataStream& qds);
 void load_from_datastream(QDataStream& qds);



 nx covers(nx r, nx c);
 nx get_index(nx r, nx c);

 nx operator %(QPair<nx, nx> pos)
 {
  return covers(pos.first, pos.second);
 }

 bool is_diagonal()
 {
  return (n_cols_ & 1) && (n_cols_ > 1);
 }

 bool is_cmajor()
 {
  return (n_rows_ & 1) && !is_diagonal();
 }

 bool is_cmajor_not_symmetric()
 {
  return (n_rows_ & 1) &&
    ( ((n_cols_ & 1) == 0) && (n_cols_ > 1) );
 }

 bool is_rmajor()
 {
  return (n_rows_ & 1) == 0;
 }

 nx get_diagonal_length()
 {
  if(n_rows_ & 1)
    return n_cols();
  return n_rows();
 }


 bool is_symmetric()
 {
  return n_cols_ == 0;
 }

 bool is_skew_symmetric()
 {
  return n_cols_ == 1;
 }

 bool is_symmetric_or_skew_symmetric()
 {
  return (n_cols_ == 1) || (n_cols_ == 0);
 }

 static constexpr nx value_byte_size() { return 8; }

 _one_opbracket operator[](nx r);
// {
//  return {*this, r};
// }

 void to_raw_data(QByteArray& qba);
 void to_raw_data_with_encoded_default(QByteArray& qba);

 void from_raw_data(const QByteArray& qba, QPair<nx, nx> dims, val_t defaultv = 0);
 void from_raw_data(const QByteArray& qba, val_t defaultv = 0);
 void from_raw_data_with_encoded_default(const QByteArray& qba);
 void from_raw_data_with_encoded_default(const QByteArray& qba, QPair<nx, nx> dims);

 void fill_diagonal_only(val_t val = 1);
 void fill_diagonal(val_t diag_value = 1, val_t other_value = 0, val_t default_value = 0);

 _from_raw_data_special from_raw_data()
 {
  return {*this, Mat2d_special_mode_for_raw_data::Normal};
 }

 void multiply(const QVector<val_t>& vec, QVector<val_t>& result);
 void merge_row(const QVector<val_t>& vec, nx row);

 void patterned_fill_row(nx row)
 {
  QVector<val_t> vec = QVector<val_t>(n_cols());
  nx nix = 1;
  for(val_t& rr: vec)
  {
   rr = (10 * row) + nix;
   ++nix;
  }
  merge_row(vec, row);
 }

 void patterned_fill()
 {
  for(nx r = 1; r <= n_rows(); ++r)
  {
   patterned_fill_row(r);
  }
 }

 const val_t& at(nx r, nx c);
 val_t* get(nx r, nx c);
 val_t* fetch(nx r, nx c);
 val_t value(nx r, nx c);
 val_t value(nx r, nx c, val_t defaultv);

 void* fetch_raw(nx r, nx c);

 val_t get_value(nx r, nx c);
 val_t get_at(nx r, nx c);

 val_t get_at_index(nx pos);

 nx total_size();

 void resize(nx r, nx c);
 void resize(nx total);
 void resize()
 {
  resize(n_rows_, n_cols_);
 }

 void set_dimensions(nx r, nx c);

#define TEMP_MACRO(ty) \
 void resize(ty pr) \
 { resize(pr.first, pr.second); } \
 void set_dimensions(ty pr) \
 { set_dimensions(pr.first, pr.second); }

 TEMP_MACRO(pr1)
 TEMP_MACRO(pr1s)
 TEMP_MACRO(pr2)
 TEMP_MACRO(pr2s)
 TEMP_MACRO(pr4)
 TEMP_MACRO(pr4s)


};

//template<typename COLL_Type>
//template<special_mode>
//const val_t& _at(nx r, nx c);

// template<special_mode>
// val_t* _get(nx r, nx c);

// template<special_mode>
// val_t* _fetch(nx r, nx c);

// template<special_mode>
// val_t _value(nx r, nx c);

// template<special_mode>
// val_t _value(nx r, nx c, val_t defaultv);

 // typename Mat2d<COLL_Type>::special_mode sm>

template<typename COLL_Type>
struct _Mat2d_special_mode
{
 using nx = typename COLL_Type::Numeric_Index_type;
 using val_t = typename COLL_Type::Value_type;
 struct _Sym
 {
  Mat2d<COLL_Type>* _this;
  nx _total_size();
  nx _get_index(nx r, nx c);
  val_t* _fetch(nx r, nx c);
  val_t* _get(nx r, nx c);
  val_t& _at(nx r, nx c);
 };
 struct _Skew
 {
  Mat2d<COLL_Type>* _this;
  nx _total_size();
  nx _get_index(nx r, nx c);
  val_t* _fetch(nx r, nx c);
  val_t* _get(nx r, nx c);
  val_t& _at(nx r, nx c);
 };
 struct _Diag
 {
  Mat2d<COLL_Type>* _this;
  nx _total_size();
  nx _get_index(nx r, nx c);
  val_t* _fetch(nx r, nx c);
  val_t* _get(nx r, nx c);
  val_t& _at(nx r, nx c);
 };

};

// template<special_mode>
// nx _get_index(nx r, nx c);


_XCNS(XCSD)

#endif // MAT2D__H
