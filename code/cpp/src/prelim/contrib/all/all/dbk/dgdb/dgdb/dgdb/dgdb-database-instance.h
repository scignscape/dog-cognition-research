
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef DGDB_DATABASE_INSTANCE__H
#define DGDB_DATABASE_INSTANCE__H

#include <QByteArray>
#include <QDir>

#include <functional>

#include "global-types.h"

#include "accessors.h"

#include "flags.h"

#include "types/dh-type.h"

#include "types/stage/dh-stage-code.h"

#include "dh-location-structure.h"
#include "dtb/_sv-wrapper.h"


#include <QVariant>


KANS_(DGDB)

class DgDb_Hypernode;
class DWB_Instance;
class DH_Type;

class DH_Type_System; //* dht = ddi.type_system()

class DTB_Package;
class DH_Subvalue_Field;
class DH_Stage_Value;

class DH_Instance;
class DH_Record;

struct Hyperedge_Data;


class DgDb_Database_Instance
{
 QString private_folder_path_;
 QString confirmed_private_folder_path_;
 QString dwb_folder_path_;

 s4 hypernode_count_status_;
// u2 pinterns_count_;
// u2 finterns_count_;

 DTB_Package* dtb_package_;

 DWB_Instance* blocks_dwb_;

 DH_Type_System* type_system_;

 DH_Instance* dh_instance_;


 typedef void* (*get_shm_field_ptr_type)(DgDb_Database_Instance&,
   DgDb_Hypernode&, u2, QString, size_t*, n8*);

 get_shm_field_ptr_type get_shm_field_ptr_;

 QMap<QString, DWB_Instance*> query_dwbs_;

 QMap<u4, DgDb_Hypernode*> active_hypernodes_;

 QMap<n8, n8*> max_record_ids_;

 QMap<QString, n8> category_floors_;

 void* default_get_shm_field_ptr(DH_Location_Structure dls,
   DgDb_Hypernode* dh, u2 index_code, QString field_name,
   size_t* size, n8* shm_path_code);

public:

 struct _Config
 {
  flags_(2)
   bool scratch_mode:1;
   bool local_scratch_mode:1;
   bool auto_stage:1;
   bool auto_commit:1;
   bool avoid_record_pointers:1;
   bool temp_reinit:1;
   bool reset_tkrzw:1;
   bool whitedb_auto_commit:1;
   bool tkrzw_auto_commit:1;
  _flags

  _Config() : Flags(0) {}
 };

 _Config Config;


 struct Call_Operator_package {
  DgDb_Database_Instance& _this;
  DgDb_Hypernode* dh;

  Call_Operator_package* operator->() { return this; };

  inline DH_Location_Structure property_site(QString label)
  {
   return _this.property_site(*dh, label);
  }

  inline void set_property(QString key, QVariant value)
  {
   return _this.set_property(dh, key, value);
  }

  inline QVariant get_property(QString key)
  {
   return _this.get_property(dh, key);
  }

  template<typename VALUE_type>
  inline VALUE_type get_property(QString key)
  {
   return _this.get_property(dh, key).value<VALUE_type>();
  }

 };

 DH_Location_Structure property_site(DgDb_Hypernode& dh, QString label);


 Call_Operator_package operator ()(DgDb_Hypernode* _dh) { return {*this, _dh}; }



 static constexpr s4 _unknown = -1;
 static constexpr s4 _file_create_failed = -2;
 static constexpr s4 _folder_create_failed = -3;
 static constexpr s4 _dwb_folder_create_failed = -4;
 static constexpr s4 _dwb_file_create_failed = -5;
 static constexpr s4 _dwb_subfolder_create_failed = -6;

 static constexpr n8 _blocks_rec_id_category_floor = 1000;
 static constexpr n8 _queries_rec_id_category_floor = 2000;


 DgDb_Database_Instance(QString private_folder_path = {});

 enum class Block_Options {
   N_A = 0, Write_WhiteDB_Record = 1, Write_Max_Fixed = 2,
   Init_to_0 = 4, Write_Type_Code = 8,
   Write_Forward_Pointer = 16, Write_Backward_Pointer = 32
 };

 friend constexpr Block_Options operator|(Block_Options lhs, Block_Options rhs)
 {
  return (Block_Options) ( (u1) lhs | (u1) rhs );
 }

 friend constexpr u1 operator&(Block_Options lhs, Block_Options rhs)
 {
  return (u1) lhs & (u1) rhs;
 }


 ACCESSORS(QString ,private_folder_path)
 ACCESSORS(get_shm_field_ptr_type ,get_shm_field_ptr)
 ACCESSORS(DH_Type_System* ,type_system)

 DH_Instance* dh_instance();

 n8 new_record_id(n8 category_floor);

 void init_indices();

 char* allocate_shm_block(DH_Type* dht, u4 dh_id,
   QString init_message = {}, u1 Max_Fixed = 0, u2 total_columns = 0, Block_Options options =
   Block_Options::Write_WhiteDB_Record | Block_Options::Write_Max_Fixed | Block_Options::Init_to_0);

 char* allocate_shm_block(size_t size, u2 block_column, u2 message_column,
   u4 dh_id, QString init_message = {}, u1 Max_Fixed = 0,
   u2 total_columns = 0, Block_Options options =
   Block_Options::Write_WhiteDB_Record | Block_Options::Write_Max_Fixed | Block_Options::Init_to_0);

 void store_outedge(DgDb_Hypernode* dh,
   u4 edge_id, const QByteArray& data); //, Hyperedge_Data& hd);

 void find_outedge(DgDb_Hypernode* dh, QString connector_label, DH_Record& result);


 void fetch_outedges(DgDb_Hypernode* dh, QByteArray& data);

 DgDb_Hypernode* new_hypernode();

 DgDb_Hypernode* _new_hypernode(DH_Type* dh_type);
 DgDb_Hypernode* _new_hypernode(DH_Type* dh_type, void* obj);

 DH_Type* get_type_by_name(QString tn, QString* res = nullptr);

 DWB_Instance* get_query_dwb(DH_Type* dht, DH_Subvalue_Field* sf); //query_dwbs_)

 template<typename HYPERNODE_Type>
 DgDb_Hypernode* new_hypernode()
 {
  QString tn = QString::fromStdString(typeid(HYPERNODE_Type).name());
  QString res;
  DH_Type* dht = get_type_by_name(tn, &res);
  return _new_hypernode(dht);
 }

 template<typename HYPERNODE_Type>
 DgDb_Hypernode* new_hypernode(HYPERNODE_Type* obj)
 {
  QString tn = QString::fromStdString(typeid(HYPERNODE_Type).name());
  QString res;
  DH_Type* dht = get_type_by_name(tn, &res);
  return _new_hypernode(dht, obj);
 }



// template<typename HYPERNODE_Type>
// DgDb_Hypernode* new_hypernode(HYPERNODE_Type** object)
// {
//  QString tn = QString::fromStdString(typeid(HYPERNODE_Type).name());
//  QString res;
//  DH_Type* dht = get_type_by_name(tn, &res);
//  return _new_hypernode(dht);
// }


// {
//  QString tn = QString::fromStdString(typeid(HYPERNODE_Type).name());
//  tn = type_system_ type_name_resolutions_.value(tn, tn);

// }

 DH_Stage_Code get_stage_code(DH_Type* dht, QString field_name);
 DH_Stage_Code get_stage_code(DgDb_Hypernode* dh, QString field_name);
 DH_Stage_Code get_stage_code(DH_Type* dht, DH_Subvalue_Field* sf);


 void init_dtb_package();
 void init_type_system();

 void init_hypernode_from_shm_block(DgDb_Hypernode* dh, const QByteArray& qba, void* rec,
   void* obj, std::function<void(void*, const QByteArray&)> cb);

 void init_hypernode_from_shm_block(DgDb_Hypernode* dh, void* rec,
   void* obj, std::function<void(void*, const QByteArray&)> cb);
// {
//  init_hypernode_from_shm_block(dh, QByteArray(dh->shm_block()))
// }

 void store_subvalue_to_external_record(DgDb_Hypernode* dh,
   DH_Subvalue_Field* sf, char* mem, DH_Stage_Value& sv);// const QByteArray& value);

 void store_subvalue_to_external_record(DH_Subvalue_Field* sf,
   DWB_Instance* dwb, void* rec, char* mem, DH_Stage_Value& sv);// const QByteArray& value);

 void store_subvalue_to_record(DH_Subvalue_Field* sf, char* mem, DH_Stage_Value& sv);//const QByteArray& value);

 void store_subvalue_to_block(DH_Subvalue_Field* sf, char* mem, DH_Stage_Value& sv);

 void init_hypernode_from_object(DgDb_Hypernode* dh, void* obj,
   std::function<void(void*, QByteArray&)> cb);

 void init_object_from_hypernode(DgDb_Hypernode* dh, void* obj,
   std::function<void(void*, const QByteArray&)> cb);

 template<typename OBJECT_Type>
 void init_hypernode_from_object(DgDb_Hypernode* dh, OBJECT_Type* obj)
 {
  std::function<void(void*, QByteArray&)> cb = get_binary_encoder(dh);// dht->binary_encoder();
  init_hypernode_from_object(dh, obj, cb);
  //init_hypernode_from_shm_block(result, rec, obj, cb);
 }

 template<typename OBJECT_Type>
 void init_object_from_hypernode(DgDb_Hypernode* dh, OBJECT_Type*& obj)
 {
  obj = new OBJECT_Type;
  std::function<void(void*, const QByteArray&)> cb = get_binary_decoder(dh);// dht->binary_encoder();
  init_object_from_hypernode(dh, obj, cb);
  //init_hypernode_from_shm_block(result, rec, obj, cb);
 }

 std::function<void(void*, QByteArray&)> get_binary_encoder(DgDb_Hypernode* dh);
 std::function<void(void*, const QByteArray&)> get_binary_decoder(DgDb_Hypernode* dh);

 void store_(DgDb_Hypernode* dh, QString field_or_property_name, DH_Stage_Value& sv); //const QByteArray& value);
 void store(DgDb_Hypernode* dh, QString field_or_property_name, DH_Stage_Value& sv)
 {
  store_(dh, field_or_property_name, sv);
 }
 void store(DgDb_Hypernode* dh, QString field_or_property_name, DH_Stage_Value sv);
 void store(DgDb_Hypernode* dh, QString field_or_property_name, QString value);
// {
//  store(dh, field_or_property_name, sv);
// }//const QByteArray& value);

 void store_subvalue(DgDb_Hypernode* dh, DH_Subvalue_Field* sf, DH_Stage_Value& sv);
   //const QByteArray& value);

 void store_subvalue(DgDb_Hypernode* dh,
   DH_Subvalue_Field* sf, DH_Location_Structure& dls,
   DH_Location_Structure::Data_Options opts, DH_Stage_Value& sv);
   //const QByteArray& value);

 void store_indexed_field(DgDb_Hypernode* dh, u2 index,
   DH_Stage_Value& sh, //const QByteArray& value,
   DH_Location_Structure::Data_Options opts, QString field_name);
 void store_indexed_field(DgDb_Hypernode* dh, u2 index,
   DH_Stage_Value sh, //const QByteArray& value,
   DH_Location_Structure::Data_Options opts, QString field_name);

 void store_indexed_field_(DgDb_Hypernode* dh, u2 index,
   DH_Stage_Value& sh, //const QByteArray& value,
   DH_Location_Structure::Data_Options opts, QString field_name);

 template<DH_Location_Structure::Data_Options OPTS>
 void store_subvalue_(DH_Location_Structure dls,
   DgDb_Hypernode* dh, DH_Subvalue_Field* sf, DH_Stage_Value& sv,//const QByteArray& value,
   QString field_name);



 template<DH_Location_Structure::Data_Options OPTS>
 void store_indexed_field_(DH_Location_Structure dls,
   DgDb_Hypernode* dh, DH_Stage_Value& sv, QString field_name);


 //ddi.fetch_subvalue(dh, "a_number", qba, pv);
 void fetch_subvalue(DgDb_Hypernode* dh, QString field_name,
   QByteArray& value, void*& pv);


 DgDb_Hypernode* find_hypernode(DH_Type* dht, QString field_name, DH_Stage_Value& sv, void** rec = nullptr);
 DgDb_Hypernode* find_hypernode(DH_Type* dht, DH_Subvalue_Field* sf, DH_Stage_Value& sv, void** rec = nullptr);


 DgDb_Hypernode* find_hypernode(DH_Type* dht, QString field_name, QString test, void** rec = nullptr);
 DgDb_Hypernode* find_hypernode(DH_Type* dht, DH_Subvalue_Field* sf, QString test, void** rec = nullptr);

 template<typename OBJECT_Type>
 DgDb_Hypernode* find_hypernode(QString field_name,
   QString test, OBJECT_Type** object)
 {
  QString tn = QString::fromStdString(typeid(OBJECT_Type).name());
  QString res;
  DH_Type* dht = get_type_by_name(tn, &res);
  void* rec;
  DgDb_Hypernode* result = find_hypernode(dht, field_name, test, &rec);
  if(object)
  {
   OBJECT_Type* obj = new OBJECT_Type;
   std::function<void(void*, const QByteArray&)> cb = dht->binary_decoder();
   init_hypernode_from_shm_block(result, rec, obj, cb);
   *object  = obj;
  }
  return result;
 }

 void fetch_subvalue(DgDb_Hypernode* dh, DH_Subvalue_Field* sf,
   QByteArray& value, void*& pv);


 void process_info_record(QString dbm_key, QString key,
   create_cb(empty), update_cb(full));

 void process_info_record(QString key,
   create_cb(empty), update_cb(full))
 {
  process_info_record("info", key, empty, full);
 }

 struct process_info_record_temporary
 {
  static constexpr u1 need_cbs = 2;
  DgDb_Database_Instance* _this;
  QString dbm_key;
  QString key;
  create_cb create;
  update_cb update;
  u1 cb_count;

  void check_ready()
  {
   if(cb_count >= need_cbs)
   {
    if(dbm_key.isEmpty())
      _this->process_info_record(key, create, update);
    else
      _this->process_info_record(dbm_key, key, create, update);
   }
  }

  process_info_record_temporary& operator<<(create_cb c)
  {
   create = c;
   ++cb_count;
   check_ready();
   return *this;
  }

  process_info_record_temporary& operator<<(update_cb u)
  {
   update = u;
   ++cb_count;
   check_ready();
   return *this;
  }
 };

 process_info_record_temporary process_info_record(QString key)
 {
  return {this, {}, key, nullptr, nullptr, 0};
 }

 process_info_record_temporary process_info_record(QString dbm_key, QString key)
 {
  return {this, dbm_key, key, nullptr, nullptr, 0};
 }

  // DH_Location_Structure::Data_Options opts);

 void fetch_indexed_field(DgDb_Hypernode* dh, u2 index,
   QByteArray& value,
   DH_Location_Structure::Data_Options opts);

 void fetch_indexed_field(DgDb_Hypernode* dh, u2 index,
   DH_Location_Structure::Field_Id_Options fio,
   QByteArray& value,
   DH_Location_Structure::Data_Options opts);

 void fetch_indexed_field(DgDb_Hypernode* dh, u2 index,
   DH_Location_Structure::Field_Id_Options fio,
   QByteArray& value, void*& pv,
   DH_Location_Structure::Data_Options opts);

 u2 check_field_id(QString key);

 u2 check_property_id(QString key);
 void set_property(DgDb_Hypernode* hypernode, QString key, QVariant value);

 void check_construct_files();
 u1 check_construct_dwb_files(QDir qdir);

 u1 check_construct_dwb_files(QString folder_path);

 void read_hypernode_count_status();
 void read_interns_count_status();


 void init_dwb_blocks();

 void check_interns_dbm();

 QVariant get_property(DgDb_Hypernode* hypernode, QString key);

 void check_info_dbm();
 void check_nodes_dbm();

 void store_hypernode_count_status(u4 count);
 void store_node_data(DH_Location_Structure dls, QVariant value);
 void store_node_data(DH_Location_Structure dls, const QByteArray& value);
 void store_node_data(DH_Location_Structure dls, void* value);

 void fetch_node_data(DH_Location_Structure dls, QVariant& result);
 void fetch_node_data(DH_Location_Structure dls, QByteArray& result);
 void fetch_node_data(DH_Location_Structure dls, void*& result);

 void* get_wdb_record_from_block(char* block);
 QString get_string_from_wdb_record(void* rec, u2 field_number = 1);

 key_t ftok_key(QString which);

 DgDb_Hypernode* get_hypernode_from_block_record(DH_Type* dht, void* rec);

 template<DH_Subvalue_Field::Write_Mode WM>
 void write_key_value(DgDb_Hypernode* dh, DH_Subvalue_Field* sf, char* mem);

};

_KANS(DGDB)

#endif // DGDB_DATABASE_INSTANCE__H


