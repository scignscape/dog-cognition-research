
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef DH_TYPE__H
#define DH_TYPE__H


#include <functional>

#include <QMap>

#include "global-types.h"

#include "dh-type-field-info-state.h"

//#include "dw-stage-value.h"
//#include "stage/dw-stage-queue.h"

// #include "_whitedb/_whitedb.h"

#include "accessors.h"

#ifndef RTTI_READ
#define RTTI_READ(tn) \
rtti_read<tn>(#tn)
#endif

#ifndef RTTI_READ_2_1
#define RTTI_READ_2_1(ho_tname ,tn) \
rtti_read<ho_tname<tn>>("(" #ho_tname \
  " " #tn ")")
#endif

#include "kans.h"

#include "dh-subvalue-field.h"


#include <QtXml>


 //?KANS_(DgDb)

//class DgDb_Node;

//class DH_Node;
//class DH_Stage_Value;
//struct DH_Stage_Queue;


class DgDb_Hypernode;

class DH_Subvalue_Field;


class DH_Type
{
 QString name_;
 QString cname_;

 u4 byte_length_;
 u1 byte_length_code_;

 s2 stash_id_;

 u2 default_query_column_;
 QString default_query_path_;

 void* meta_object_;

 size_t shm_block_size_;

 u2 shm_block_column_;
 s1 shm_message_column_;

 QStringList field_name_serialization_order_;

 std::function<void*(DgDb_Hypernode*,
   std::function<void*(u4)> )> raw_binary_encoder_;

 std::function<void(void*, QByteArray& qba)> binary_encoder_;
 std::function<void(void*, const QByteArray& qba)> binary_decoder_;

 std::function<void(void*, QByteArray& qba)> opaque_encoder_;
 std::function<void(void*, const QByteArray& qba)> opaque_decoder_;


 template<typename T> struct _Class_Of_Member_Function {};

 template<typename RETURN_Type, typename CLASS_Type>
 struct _Class_Of_Member_Function<RETURN_Type (CLASS_Type::*)>
 {  
  using type = CLASS_Type;    
 };

 template< typename T> 
 using Class_Of_Member_Function = typename _Class_Of_Member_Function<T>::type;


 QMap<QString, QPair<u2, DH_Stage_Code>> subvalue_fields_index_map_;
 QMap<u2, DH_Subvalue_Field*> subvalue_fields_;

 QVector<DH_Subvalue_Field*>* subvalue_fields_serialization_vector_;


public:


 ACCESSORS__GET(std::function<void(void*, QByteArray&)> ,binary_encoder)
 ACCESSORS__GET(std::function<void(void*, const QByteArray&)> ,binary_decoder)

 ACCESSORS__GET(std::function<void(void*, QByteArray&)> ,opaque_encoder)
 ACCESSORS__GET(std::function<void(void*, const QByteArray&)> ,opaque_decoder)

 ACCESSORS(MACRO_PASTE(std::function<void*(DgDb_Hypernode*,
   std::function<void*(u4)> )>) ,raw_binary_encoder)


 ACCESSORS(u4 ,byte_length)
 ACCESSORS(u1 ,byte_length_code)

 ACCESSORSR(size_t ,shm_block_size)
 ACCESSORSR(u2 ,shm_block_column)
 ACCESSORSR(s1 ,shm_message_column)

 ACCESSORS(s2 ,stash_id)

 ACCESSORS(QString ,name)
 ACCESSORS(QString ,cname)

 u2 get_shm_message_column(u2 block_column)
 {
  if(shm_message_column_ == -2)
    return block_column + 1;
  return shm_message_column_;
 }

 u2 get_shm_message_column()
 {
  return get_shm_message_column(shm_block_column_);
 }

 QStringList get_subvalue_field_names()
 {
  return subvalue_fields_index_map_.keys();
 }

 void get_subvalue_fields_as_vector(QVector<DH_Subvalue_Field*>& sfs);


 void note_field_block_offset(DH_Subvalue_Field* sf, u4 start, u4 end);
 void note_field_index(DH_Subvalue_Field* sf, u2 index);
 void note_field_query_path(DH_Subvalue_Field* sf, QString path, DH_Stage_Code::Query_Typecode qtc);
 void note_field_query_column(DH_Subvalue_Field* sf, u2 qyc);

 DH_Subvalue_Field* note_field_block_offset(QString field_name, u4 start, u4 end);
 DH_Subvalue_Field* note_field_index(QString field_name, u2 index);
 DH_Subvalue_Field* note_field_query_path(QString field_name, QString path, DH_Stage_Code::Query_Typecode qtc);

 void note_field_query_partner(DH_Subvalue_Field* sf,
   QString partner,
   QMap<DH_Subvalue_Field*, QVector<QPair<DH_Subvalue_Field*, u2>>>& query_partners);


//? DH_Subvalue_Field* check_note_field_name(QString field_name);

 void note_field_signed(DH_Subvalue_Field* sf);

 void note_write_mode(DH_Subvalue_Field* sf, DH_Subvalue_Field::Write_Mode wm);
 DH_Subvalue_Field* note_write_mode(QString field_name, DH_Subvalue_Field::Write_Mode wm);

 DH_Subvalue_Field::Write_Mode get_write_mode(QString field_name);
 DH_Subvalue_Field* get_subvalue_field_by_field_name(QString field_name);
 DH_Subvalue_Field* get_subvalue_field_by_index(u2 ix);

 u2 get_max_declared_field_column();
 u2 get_internal_field_column_requirements();

 void note_field_target_byte_length(DH_Subvalue_Field* sf, u1 len);
 void note_record_column_index(DH_Subvalue_Field* sf, DH_Stage_Code::Query_Typecode qtc, u2 rci);
 void note_record_column_index(DH_Subvalue_Field* sf, u2 rci);

 void note_field_qtc(DH_Subvalue_Field* sf, DH_Stage_Code::Query_Typecode qtc);


// DH_Subvalue_Field* note_field_column_in_record(QString field_name,
//   DH_Stage_Code::Query_Typecode qtc, u2 qyc);


 DH_Type_Field_Info_State sf(QVector<QPair<QString, DH_Stage_Code>> nqtc)
 {
  //qtc_serialization_order_.resize(nqtc.size());
  //int i = 0;
  std::transform(nqtc.begin(), nqtc.end(), std::back_inserter(field_name_serialization_order_),
   [this](auto pr) { subvalue_fields_index_map_[pr.first].second = pr.second; return pr.first; });

  subvalue_fields_serialization_vector_ = new QVector<DH_Subvalue_Field*>();
  return DH_Type_Field_Info_State(*this,
    DH_Type_Field_Info_State::Wide_Input_State::Field_Map);
 }
////  subvalue_fields_qtc_vector_ = new QVector<DH_Stage_Code::Query_Typecode>();

//  //check_note_field_name(field_name);
//  //
//  DH_Type_Field_Info_State result(*this);
//  //result.set_field_name()
//  //return {{}, *this, (u4) -1, nullptr};
//  return result;
// }


 DH_Type_Field_Info_State sf(QStringList field_names)
 {
  field_name_serialization_order_ = field_names;
  subvalue_fields_serialization_vector_ = new QVector<DH_Subvalue_Field*>();
  return DH_Type_Field_Info_State(*this,
    DH_Type_Field_Info_State::Wide_Input_State::Field_Vecotor);
 }
  //check_note_field_name(field_name);
  //
//  return {{}, *this, (u4) -1, nullptr};

//  DH_Type_Field_Info_State result(*this);
//  //result.set_field_name()
//  //return {{}, *this, (u4) -1, nullptr};
//  return result;

// }

 DH_Type_Field_Info_State sf(QString field_name)
 {
  return DH_Type_Field_Info_State(*this, field_name);
  //check_note_field_name(field_name);
  //return {field_name, *this, (u4) -1, nullptr};
 }

 template<typename T>
 static std::function<void(void*, QByteArray&)> default_binary_encoder(void (T::*fn)(QByteArray&))
 {
  return [fn](void* v, QByteArray& qba)
  {
   (((T*) v)->*fn)(qba);
  };
 }


 template<typename T>
 static std::function<void(void*, const QByteArray&)> 
   default_binary_decoder(void (T::*fn)(const QByteArray&))
 {
  return [fn](void* v, const QByteArray& qba)
  {
   (((T*) v)->*fn)(qba);
  };
 }


 template<typename PROC_Type>
 DH_Type& set_binary_encoder(PROC_Type pt)
 {
  binary_encoder_ = pt;
  return *this;
 }  

 template<typename VALUE_Type, typename PROC_Type>
 DH_Type& _set_default_binary_encoder(PROC_Type pt)
 {
  return set_binary_encoder(default_binary_encoder
     <VALUE_Type>(pt) );
  return *this;
 }  

 template<typename PROC_Type>
 DH_Type& set_default_binary_encoder(PROC_Type pt)
 {
  return _set_default_binary_encoder<
    Class_Of_Member_Function<PROC_Type>, PROC_Type>(pt);
 }  


 template<typename PROC_Type>
 DH_Type& _set_static_opaque_encoder(PROC_Type pt)
 {
  opaque_encoder_ = pt;
  return *this;
 }

 template<typename PROC_Type>
 DH_Type& set_static_opaque_encoder(PROC_Type pt)
 {
  static s2 stash_id = 0;
  --stash_id;
  opaque_encoder_ = pt;
  stash_id_ = stash_id;
  return *this;
 }

 template<typename VALUE_Type, typename PROC_Type>
 DH_Type& _set_opaque_encoder(PROC_Type pt)
 {
  return set_static_opaque_encoder(default_binary_encoder
     <VALUE_Type>(pt) );
  //return *this;
 }


 template<typename PROC_Type>
 DH_Type& set_opaque_encoder(PROC_Type pt)
 {
  return _set_opaque_encoder<
    Class_Of_Member_Function<PROC_Type>, PROC_Type>(pt);
 }



 template<typename PROC_Type>
 DH_Type& set_binary_decoder(PROC_Type pt)
 {
  binary_decoder_ = pt;
  return *this;
 }  

 template<typename VALUE_Type, typename PROC_Type>
 DH_Type& _set_default_binary_decoder(PROC_Type pt)
 {
  return set_binary_decoder(default_binary_decoder
     <VALUE_Type>(pt) );
  return *this;
 }  

 template<typename PROC_Type>
 DH_Type& set_default_binary_decoder(PROC_Type pt)
 {
  return _set_default_binary_decoder<
    Class_Of_Member_Function<PROC_Type>, PROC_Type>(pt);
 }  


 template<typename PROC_Type>
 DH_Type& set_static_opaque_decoder(PROC_Type pt)
 {
  opaque_decoder_ = pt;
  return *this;
 }

 template<typename VALUE_Type, typename PROC_Type>
 DH_Type& _set_opaque_decoder(PROC_Type pt)
 {
  return set_static_opaque_decoder(default_binary_decoder
     <VALUE_Type>(pt) );
  return *this;
 }

 template<typename PROC_Type>
 DH_Type& set_opaque_decoder(PROC_Type pt)
 {
  return _set_opaque_decoder<
    Class_Of_Member_Function<PROC_Type>, PROC_Type>(pt);
 }


 template<typename CType>
 void rtti_read(QString name)
 {
  name_ = name;
  cname_ = QString::fromStdString(typeid(CType).name());
  byte_length_ = sizeof(CType);
  if( (byte_length_ == 1) || (byte_length_ == 2)
    || (byte_length_ == 4) || (byte_length_ == 8) )
    byte_length_code_ = byte_length_; 
 } 


 DH_Type();

 DH_Type& default_object_layout();
 
 QPair<u4, u4> get_field_block_offset(QString field_name);

};


#ifndef UNEXPECTED_INPUT_PATTERN
#define UNEXPECTED_INPUT_PATTERN \
  qDebug() << "Unexpected input pattern in field info (line " << __LINE__ << " )";
#endif


// //   this goes here to avoid #including
 //     dh-type.h in dh-field-info-state.h ...
template<typename T>
DH_Type_Field_Info_State& DH_Type_Field_Info_State::query(QString path)
{
 if(field_)
   _this.note_field_query_path(field_, path, DH_Stage_Code::get_qtc_code<T>());
 else
   field_ = _this.note_field_query_path(field_name_, path, DH_Stage_Code::get_qtc_code<T>());
 wide_ = Wide_Input_State::Query;
 narrow_ = Narrow_Input_State::N_A;
 return *this;
}

template<typename T>
DH_Type_Field_Info_State& DH_Type_Field_Info_State::record(u2 column_index)
{
 if(wide_ != Wide_Input_State::Field_Name)
 {
  UNEXPECTED_INPUT_PATTERN
  return *this;
 }

 note_write_mode(DH_Subvalue_Field::Write_Mode::Redirect_In_Record);

 DH_Stage_Code::Query_Typecode qtc = DH_Stage_Code::get_qtc_code<T>();

 if(column_index)
   _this.note_record_column_index(field_, qtc, column_index - 1);
 else
   _this.note_field_qtc(field_, qtc);

 wide_ = Wide_Input_State::Record;
 narrow_ = Narrow_Input_State::N_A;
 return *this;
}


template<typename T>
DH_Type_Field_Info_State& DH_Type_Field_Info_State::encode()
{
 if(wide_ != Wide_Input_State::Field_Name)
 {
  UNEXPECTED_INPUT_PATTERN
  return *this;
 }

 note_write_mode(DH_Subvalue_Field::Write_Mode::Redirect_In_Block);

 DH_Stage_Code::Query_Typecode qtc = DH_Stage_Code::get_qtc_code<T>();
 _this.note_field_qtc(field_, qtc);

 wide_ = Wide_Input_State::Encode;
 narrow_ = Narrow_Input_State::N_A;
 return *this;
}

 //?_KANS(DgDb)

#endif // DH_TYPE__H












#ifdef HIDE
 template<typename T>
 struct Note_Field_Query_intermediary;

 struct Note_Field_intermediary
 {
  QString field_name;
  DH_Type& _this;
  u4 held_start;
  DH_Subvalue_Field* field;

  Note_Field_intermediary& note_field_block_offset(u4 start, u4 end, u1 qtc = 255)
  {
   if(field)
     _this.note_field_block_offset(field, start, end);
   else
     field = _this.note_field_block_offset(field_name, start, end);
   if(qtc != 255)
     _this.note_field_qtc(field, (DH_Stage_Code::Query_Typecode) qtc);
   return *this;
  }

  Note_Field_intermediary& operator()(u4 start, u4 end)
  {
   note_field_block_offset(start, end, (u1)DH_Stage_Code::get_qtc_code<int>());
  }

  Note_Field_intermediary& _signed_(u4 start, u4 end)
  {
   note_field_block_offset(start, end, (u1)DH_Stage_Code::get_qtc_code<int>());
   _this.note_field_signed(field);
   return *this;
  }
  Note_Field_intermediary& _date_(u4 start, u4 end)
  {
   note_field_block_offset(start, end, (u1)DH_Stage_Code::get_qtc_code<QDate>());
   return *this;
  }

  Note_Field_intermediary& _time_(u4 start, u4 end)
  {
   note_field_block_offset(start, end, (u1)DH_Stage_Code::get_qtc_code<QTime>());
   return *this;
  }

  Note_Field_intermediary& _datetime_(u4 start, u4 end)
  {
   note_field_block_offset(start, end, (u1)DH_Stage_Code::get_qtc_code<QDateTime>());
   return *this;
  }

  Note_Field_intermediary& operator()(DH_Subvalue_Field::Write_Mode wm)
  {
   if(field)
     _this.note_write_mode(field, wm);
   else
     field = _this.note_write_mode(field_name, wm);
   return *this;
  }

  Note_Field_intermediary& operator()(QPair<DH_Subvalue_Field::Write_Mode, u2> pr)
  {
   auto [wm, column_index] = pr;
   if(field)
     _this.note_write_mode(field, wm);
   else
     field = _this.note_write_mode(field_name, wm);

   _this.note_record_column_index(field, column_index);
   return *this;
  }

  Note_Field_intermediary& operator()(QPair<
    QPair<DH_Subvalue_Field::Write_Mode, DH_Stage_Code::Query_Typecode>, u2> pr)
  {
   auto [pr1, column_index] = pr;
   auto [wm, qtc] = pr1;
   if(field)
     _this.note_write_mode(field, wm);
   else
     field = _this.note_write_mode(field_name, wm);

   _this.note_record_column_index(field, qtc, column_index);
   return *this;
  }

  Note_Field_intermediary& operator()(u4 start)
  {
   held_start = start;
   //_this._note_field_block_offset(field_name, start, start);
   return *this;
  }

  Note_Field_intermediary& operator[](u2 index)
  {
   if(field)
     _this.note_field_index(field, index);
   else
     field = _this.note_field_index(field_name, index);
   return *this;
  }

  Note_Field_intermediary& operator()(QString another_field_name)
  {
   field = nullptr;
   //_this.check_note_field_name(another_field_name);
   if(held_start != -1)
   {

   }
   field_name = another_field_name;
   return *this;
  }
  DH_Type* operator->()
  {
   return &_this;
  }

  template<typename T>
  Note_Field_Query_intermediary<T> query(QString path)
  {
   if(field)
     _this.note_field_query_path(field, path, DH_Stage_Code::get_qtc_code<T>());
   else
     field = _this.note_field_query_path(field_name, path, DH_Stage_Code::get_qtc_code<T>());
   return {*this};
  }

//  template<typename T>
//  Note_Field_intermediary column(u2 c)
//  {
//   if(field)
//     _this.note_field_column_in_record(field, c, DH_Stage_Code::get_qtc_code<T>());
//   else
//     field = _this.note_field_column_in_record(field_name, c, DH_Stage_Code::get_qtc_code<T>());
//   return {*this};
//  }

 };

 template<typename T>
 struct Note_Field_Query_intermediary
 {
  Note_Field_intermediary& surrounding;

  Note_Field_intermediary& operator[](u2 column)
  {
   surrounding._this.note_field_query_column(surrounding.field, column);
   return surrounding;
  }
  Note_Field_Query_intermediary& operator()(u1 target_byte_len)
  {
   surrounding._this.note_field_target_byte_length(surrounding.field, target_byte_len);
   return *this;
  }
 };

 Note_Field_intermediary sf(QVector<QPair<QString, DH_Stage_Code>> nqtc)
 {
  //qtc_serialization_order_.resize(nqtc.size());
  //int i = 0;
  std::transform(nqtc.begin(), nqtc.end(), std::back_inserter(field_name_serialization_order_),
   [this](auto pr) { subvalue_fields_index_map_[pr.first].second = pr.second; return pr.first; });


  //field_name_serialization_order_.resize(nqtc.size());

  // = field_names;
  subvalue_fields_serialization_vector_ = new QVector<DH_Subvalue_Field*>();
//  subvalue_fields_qtc_vector_ = new QVector<DH_Stage_Code::Query_Typecode>();

  //check_note_field_name(field_name);
  //
  return {{}, *this, (u4) -1, nullptr};
 }


 Note_Field_intermediary sf(QStringList field_names)
 {
  field_name_serialization_order_ = field_names;
  subvalue_fields_serialization_vector_ = new QVector<DH_Subvalue_Field*>();

  //check_note_field_name(field_name);
  //
  return {{}, *this, (u4) -1, nullptr};
 }

 Note_Field_intermediary sf(QString field_name)
 {
  //check_note_field_name(field_name);
  return {field_name, *this, (u4) -1, nullptr};
 }

#endif // HIDE
