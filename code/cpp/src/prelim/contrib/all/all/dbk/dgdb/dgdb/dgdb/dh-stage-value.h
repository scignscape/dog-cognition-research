
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef DH_STAGE_VALUE__H
#define DH_STAGE_VALUE__H

#include <QVector>
#include <QQueue>

#include <QDateTime>
#include <QDate>

#include <QDebug>

#include <functional>

#include "accessors.h"

#include "global-types.h"

#include "types/stage/dh-stage-code.h"

#include "kans.h"

KANS_(DGDB)

//?
static constexpr u1 C_STRING_DECODING_Flag = 4;
static constexpr u1 XSD_TYPE_DECODING_Flag = 8;
static constexpr u1 URI_PREFIX_DECODING_Flag = 8;

class DH_Stage_Queue;

//class DgDb_Node;

/*
struct DH_Stage_Queue
{
 QQueue<void*> values;
 std::function<void(QQueue<void*>&)> callback;
 DH_Stage_Queue() : callback(nullptr) {}
 void operator=(std::initializer_list<void*> vs) 
 { 
  values.append(QList<void*>(vs)); 
 }
 void operator<<(std::function<void(QQueue<void*>&)> cb)
   { callback = cb; }
};

template<typename T>
std::function<void(QQueue<void*>&)> stage_queue_memfnptr(void (T::*fn)(QQueue<void*>&))
{
 return [fn](QQueue<void*>& qq)
 {
  (((T*) qq.dequeue())->*fn)(qq);
 };
}
*/

class DH_Stage_Value
{
 DH_Stage_Code info_;
 n8 data_;

 void enqueue_in(DH_Stage_Queue& sw);

public:

 typedef std::function<void(u4, QString, DH_Stage_Value*)> Callback_type;

 struct Package {
  QByteArray qba;
  QMap<QString, DH_Stage_Value> single_indexed;
  QMap<u4, DH_Stage_Value> multi_indexed;
 };

private:

//temp
public:
 struct _run_result
 {
  DH_Stage_Code info;
  u1 extra;
  u1 collapse_wg_encoding_type() const;
  operator u1() const;  
  _run_result operator [](u1 x)
  {
   return { info, extra | x };
  }
 };

 struct _run_hold
 {
  struct _run
  {
   DH_Stage_Value* _this;
   u4 index;
   QString col;   
   _run_result operator()(DH_Stage_Value::Callback_type cb);
  };
  DH_Stage_Value* _this;
  _run operator[](u4 field_index)
  {
   return {_this, field_index, {}};
  }
  _run operator[](QString col)
  {
   return {_this, 0, col};
  }
  _run_result operator()(DH_Stage_Value::Callback_type cb);
 };

 struct _sq_hold
 {
  DH_Stage_Value& _this;


  _sq_hold operator()(DH_Stage_Queue& sq)
  {
   _this.enqueue_in(sq);
   return *this;
  }

//  u1& operator()(DH_Stage_Queue& sq)
//  {
//   _this.enqueue_in(sq);
//   return _this.info_;
//  }


  operator u1&()
  {
   return _this.info_.ref();
  }
 };

public:

 DH_Stage_Value();

 ~DH_Stage_Value();

 ACCESSORS(n8 ,data)
 ACCESSORS(DH_Stage_Code ,info)

 DH_Stage_Value& set_ptr_data(void* ptr);

 DH_Stage_Code::Query_Typecode get_qtc_code()
 {
  return info_.get_qtc_code();
 }

 void check_confirm_byte_length(u1 len, bool is_signed);

 u1 get_wg_encoding_type() const;
 u1 get_byte_length() const;

 DH_Stage_Code::String_Kind get_string_kind() const;

 u1 get_prelim_encoding_code() const;
 u1 get_read_encoding_type() const;

 u1 get_prelim_decoding_code() const;
 u1 get_prelim_decoding_flag() const;


 void aborb_data(QDataStream& qds, DH_Stage_Code sc);

 bool is_uninit() const
 {
  return info_.code() == 0;
 }

 _sq_hold operator()(void* pv)
 {
  //qDebug() << "pv = " << pv;
  data_ = (n8) pv;
  return {*this};
 }

 template<typename PTR_Type>
 _sq_hold queue()
 {
  PTR_Type* ptr = new PTR_Type;
  return operator()(ptr);
 } 

 template<typename PTR_Type>
 _sq_hold queue(DH_Stage_Queue& sq)
 {
  PTR_Type* ptr = new PTR_Type;
  //return operator()(operator()(ptr))(sq);
  return (*this)(ptr)(sq);
 } 

//DH_Stage_Queue& sq

 _run_result _run(Callback_type cb, u4 field_index = 0, QString col = {});

 _run_hold run;

 template<typename T>
 T& data_to_ref()
 {
  return *((T*) data_);
 }

 operator void*()
 {
  return (void*) data_;
 }


 template<typename T>
 DH_Stage_Value& set_data(const T& data)
 {
  set_ptr_data(new T(data));
  return *this;
 }

 template<typename T>
 DH_Stage_Value& set_raw_data(const T& data)
 {
  data_ = data;
  return *this;
 }

 template<typename T>
 void cleanup()
 {
  if(check_no_delete())
    return;
  delete (T*) data_;
  data_ = 0;
 }


 void to_qba(QByteArray& result, u1 qtc = 255);

 void generic_int(n8 data);
 void generic_null();

 DH_Stage_Value& note_unspec();
 DH_Stage_Value& note_enum();
 DH_Stage_Value& note_signed_enum();
 DH_Stage_Value& note_char_enum();
 DH_Stage_Value& note_qstring(DH_Stage_Code::String_Kind sk);
 DH_Stage_Value& note_uint();
 DH_Stage_Value& note_null();
 DH_Stage_Value& note_rec();
 DH_Stage_Value& note_int();
 DH_Stage_Value& note_dbl();
 DH_Stage_Value& note_str();
 DH_Stage_Value& note_xml();
 DH_Stage_Value& note_uri();
 DH_Stage_Value& note_blob();
 DH_Stage_Value& note_char();
 DH_Stage_Value& note_fixp();
 DH_Stage_Value& note_date();
 DH_Stage_Value& note_time();
 DH_Stage_Value& note_tbd();

 DH_Stage_Value& note_byte_length(u1 len);

//?
 DH_Stage_Value& note_unspec_or_data_has_type();
 DH_Stage_Value& clear_unspec_or_data_has_type();
 bool check_data_has_type()
 {
  return info_.check_unspec_or_data_has_type();
 }

 DH_Stage_Value& note_no_delete();
 DH_Stage_Value& clear_no_delete();

 bool check_no_delete() { return info_.check_no_delete(); }
 bool check_signed() { return info_.check_signed(); }

 DH_Stage_Value& new_qstring(const QString& qs, DH_Stage_Code::String_Kind sk);
 DH_Stage_Value& new_qstring_pair(const QString& qs, DH_Stage_Code::String_Kind sk);
 DH_Stage_Value& new_qstring_pair(const QString& qs1, const QString& qs2, DH_Stage_Code::String_Kind sk);

 DH_Stage_Value& new_qstring_xml_pair(const QString& qs1, const QString& qs2);
 DH_Stage_Value& new_qstring_uri_pair(const QString& qs1, const QString& qs2);

 template<typename T>
 DH_Stage_Value& set_uint_data(T t)
 {
  note_uint();
  set_raw_data(t);
  return *this;
 }

 template<typename T>
 DH_Stage_Value& set_u1_data(T t)
 {
  return set_uint_data(t).note_byte_length(1);
 }

 template<typename T>
 DH_Stage_Value& set_u2_data(T t)
 {
  return set_uint_data(t).note_byte_length(2);
 }

 template<typename T>
 DH_Stage_Value& set_u4_data(T t)
 {
  return set_uint_data(t).note_byte_length(4);
 }

 template<typename T>
 DH_Stage_Value& set_n8_data(T t)
 {
  return set_uint_data(t).note_byte_length(8);
 }

 template<typename T>
 DH_Stage_Value& set_int_data(T t)
 {
  note_int();
  set_raw_data(t);
  return *this;
 }

 template<typename T>
 DH_Stage_Value& set_s1_data(T t)
 {
  return set_int_data(t).note_byte_length(1);
 }

 template<typename T>
 DH_Stage_Value& set_s2_data(T t)
 {
  return set_int_data(t).note_byte_length(2);
 }

 template<typename T>
 DH_Stage_Value& set_s4_data(T t)
 {
  return set_int_data(t).note_byte_length(4);
 }

 template<typename T>
 DH_Stage_Value& set_s8_data(T t)
 {
  return set_int_data(t).note_byte_length(8);
 }

 DH_Stage_Value& set_null_data()
 {
  note_null();
  set_raw_data(0);
  return *this;
 }

 template<typename T>
 DH_Stage_Value& set_null_data(T t)
 {
  note_null();
  set_raw_data(t);
  return *this;
 }

 DH_Stage_Value& set_char_data(char chr)
 {
  note_char();
  set_raw_data(chr);
  return *this;
 }

 DH_Stage_Value& set_char_data(QChar chr)
 {
  return set_char_data(chr.toLatin1());
 }

 DH_Stage_Value& set_rec_data(void* rec)
 {
  note_rec();
  set_ptr_data(rec);
  return *this;
 }

 template<typename T>
 DH_Stage_Value& set_double_data(T t)
 {
  T* tt = new T(t);
  note_dbl();
  set_ptr_data(tt);
  return *this;
 }

 template<typename T>
 DH_Stage_Value& set_float_data(T t)
 {
  return set_double_data(t).set_byte_length(4);
 }

 template<typename T>
 DH_Stage_Value& set_fixpoint_data(T t)
 {
  u4 lft = (u4) t;
  u4 rgt = (u4) 10000 * (t - lft);
  
  note_fixp();
  set_raw_data( ((n8) (lft << 32)) | rgt);
  return *this;
 }

 DH_Stage_Value& set_date_data(QDate qdt)
 {
  note_date();
  set_raw_data(qdt.toJulianDay());
  return *this;
 }

 DH_Stage_Value& set_date_data(QDateTime qdt)
 {
  return set_date_data(qdt.date());
 }

 DH_Stage_Value& set_time_data(QTime qtm)
 {
  note_time();
  set_raw_data(qtm.msecsSinceStartOfDay());
  return *this;
 }

 DH_Stage_Value& set_time_data(QDateTime qdt)
 {
  return set_time_data(qdt.time());
 }

 DH_Stage_Value& set_str_data(char* cs, u4 len = 0)
 {
  if(len == 0) len = strlen(cs) + 1;
  char* ncs = (char*) malloc(len);
  strcpy(ncs, cs);
  note_str();
  set_ptr_data(ncs);
  return *this;
 }

 DH_Stage_Value& set_str_data(QString qs)
 {
  return set_str_data(qs.toLatin1().data());
 }

 DH_Stage_Value& set_xml_data(QString str, u4 len = 0) //, QString xsd = {})
 {
  const char* cs = str.toLatin1().constData();
  if(len == 0) len = strlen(cs) + 1;
  char* ncs = (char*) malloc(len);
  strcpy(ncs, cs);
  note_xml();
  set_ptr_data(ncs);
  return *this;
 }

 DH_Stage_Value& set_xml_data(QString str, QString xsdt)
 {
  return new_qstring_xml_pair(str, xsdt);
 }

 DH_Stage_Value& set_uri_data(QString str, u4 len = 0)
 {
  const char* cs = str.toLatin1().constData();
  if(len == 0) len = strlen(cs) + 1;
  char* ncs = (char*) malloc(len);
  strcpy(ncs, cs);
  note_uri();
  set_ptr_data(ncs);
  return *this;
 }

 DH_Stage_Value& set_uri_data(QString str, QString ns) //, QString xsd = {})
 {
  return new_qstring_uri_pair(str, ns);
 }

 DH_Stage_Value& set_blob_data(char* blob, u4 len) //, QString xsd = {})
 {
  note_blob();
  QPair<u4, char*>* pr = new QPair<u4, char*>(len, blob);
  set_ptr_data(pr);
  return *this;
 }

};


_KANS(DGDB)

#endif // DH_STAGE_VALUE__H


