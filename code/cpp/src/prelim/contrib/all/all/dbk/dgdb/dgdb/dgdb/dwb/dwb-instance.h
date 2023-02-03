
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef DWB_INSTANCE__H
#define DWB_INSTANCE__H

#include <QByteArray>

#include <functional>

#include "global-types.h"

#include "accessors.h"

#include "types/stage/dh-stage-code.h"

#include <sys/types.h>

#include "kans.h"

KANS_(DGDB)

class DH_Stage_Value;

class DgDb_Database_Instance;

class DWB_Instance
{
 QString config_path_;
 QString restore_path_;

 void* wdb_instance_;

 key_t ftok_key_;

public:

 DWB_Instance(QString config_path, QString restore_path);


 ACCESSORS(QString ,config_path)

 ACCESSORS__GET(key_t ,ftok_key)

 enum class _DB_Create_Status
 {
  N_A = 0, Attached = 1,
  Created_Via_Restore = 2, Created_New = 4,
  FTOK_Failed = 8, Created_Restore_Failed = 16,
  Create_And_Restore_Failed = 32, Attach_Failed = 64, Reset_Failed = 128
 };

 _DB_Create_Status check_init(DgDb_Database_Instance* origin);

 n8 get_record_id(void* rec, u2 id_column = 0);

 QPair<void*, char*> new_block_record(u2 field_count, size_t block_size, u2 block_column);
 size_t write_record_pointer_bytes(void* rec, char* destination);
 void write_str_field(void* rec, u2 field_number, QString str);
 void write_u1_field(void* rec, u2 field_number, u1 value);
 void write_u2_field(void* rec, u2 field_number, u2 value);
 void write_u4_field(void* rec, u2 field_number, u4 value);
 void write_n8_field(void* rec, u2 field_number, n8 value);
 void* get_record_from_block(char* block);
 QString get_string_from_record(void* rec, u2 field_number);

 void get_qba_from_record(void* rec, u2 field_number,
   QByteArray& result, DH_Stage_Code::Query_Typecode qtc, u1 len, bool is_signed);//DH_Stage_Value& sv); //

 u2 write_rec_field_via_split(char* ptr, u2 spl, DH_Stage_Value& sv); //const QByteArray& text);
 n8 write_encoded_value(DH_Stage_Value& sv); //const QByteArray& text);

 void write_field(void* rec, u2 query_column, DH_Stage_Value& sv);

 //void* get_record_via_split(char* ptr, u2 spl);

 void get_qba_from_encoded_value(n8 enc, DH_Stage_Code::Query_Typecode qtc, QByteArray& result);

 void* get_record_from_qba(const QByteArray& qba);
 void* get_target_record_from_query_record(DWB_Instance* origin_dwb,
   void* qrec, u2 rec_column, QPair<u2, u2> target_id_columns);//, u2 target_id_column, u2 target_id_target_column);

 void* find_query_record(u2 query_column, QString test); // u2 rec_column,
 void* find_query_record(u2 query_column, DH_Stage_Value& sv); // u2 rec_column,

 void* find_record_via_id(n8 id, u2 query_column);

 QPair<void*, QPair<u2, u2>> get_record_via_split(char* ptr, u2 spl);
 QPair<void*, u2> get_record_via_known_split(char* ptr, u2 spl);

 size_t write_max_fixed(u1 max_fixed, char* destination);
 u1 get_max_fixed_from_block(char* block);
 u1 get_max_used_from_block(char* block);
 u1 inc_max_used_from_block(char* block);

 QByteArray encode_record(void* rec);

 void* new_query_record(DWB_Instance* origin_dwb, void* target_record, n8 target_record_id,
   u2 target_column, n8 hypernode_id, u2 value_column, DH_Stage_Value& sv,
   u2 field_count, bool avoid_record_pointers);

 u4 fetch_u4_field(void* rec, u2 dh_id_column);
 QPair<char*, size_t> fetch_blob_field(void* rec, u2 column);

};

_KANS(DGDB)

#endif // DWB_INSTANCE__H


