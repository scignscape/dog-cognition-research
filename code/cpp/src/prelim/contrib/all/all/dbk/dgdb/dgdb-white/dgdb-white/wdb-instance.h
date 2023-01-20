
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef WDB_INSTANCE__H
#define WDB_INSTANCE__H

#include <QString>
#include <QMap>
#include <QDateTime>

#include "global-types.h"

#include "dw-stage-value.h"
#include "dw-record.h"

#include "accessors.h"

#include "kans.h"

KANS_(DGDB)

class DW_Instance;

class WDB_Instance
{
 DW_Instance* dw_instance_;

 void* white_;
 QString name_;
 u2 num_code_;

 enum DateTime_Codes {
   Recent_Create = 1, Recent_Load_From_File = 2,
   Created = 3, Last_Load_From_File = 4, Recent_Attach = 5
  };

 QMap<u1, QDateTime> datetimes_; 

 void* _new_wg_record(u4 id, QString col1, void* col2,  QString col3, 
   QMap<u4, DW_Stage_Value>& svs);

public:

 WDB_Instance(DW_Instance* dw_instance, void* w, QString n = {}); 

 ACCESSORS(void* ,white)
 ACCESSORS(u2 ,num_code)

 void save_to_local_file(QString folder, QString file_name);
 QString get_local_file_name(QString folder, QString file_name);

 void* query_within_id_range(u4 range_col, u4 low, u4 high, 
   u4 param_column, DW_Stage_Value dwsv, QString label = {}, u4 label_column = 1);

 void* new_wg_record(QMap<u4, DW_Stage_Value>& svs);
 DW_Record new_wg_record(u4 id, QString col1, void* col2, 
   QString col3, QMap<u4, DW_Stage_Value>& svs);

//? void* new_wg_record(u4 id, const QVector<DW_Stage_Value>& svs);

 void decode_wg_record_value(void* rec, u4 index, DW_Stage_Value& dwsv);

 void load_from_file(QString rf);

 DW_Record get_record_from_field(DW_Record dr, u4 col);

 void set_wg_record_field_rec(DW_Record base, u4 col, DW_Record rec);
 void set_wg_record_field_str(DW_Record dr, u4 col, QString str);
 void set_wg_record_field_int(DW_Record dr, u4 col, u4 value);

 void set_str_record_field(void* rec, u4 col, QString str);
 void set_int_record_field(void* rec, u4 col, u4 value);

 void set_wg_encoded_record_field(void* rec, u4 col, n8 value);
 void set_qvariant_record_field(void* rec, u4 col, QVariant value);


 n8 wg_encode_dw_record(DW_Record rec);

 n8 check_wg_encode_dw_record(void* v);

 //void avoid_record_pointers


 void get_qba_from_record(void* rec, u4 field_number, QByteArray& qba);
 void set_qba_record_field(void* rec, u4 field_number, QByteArray& qba);
 void set_qba_record_field(void* rec, u4 field_number, const QByteArray& qba);

 void set_qba_record_field(DW_Record dr, u4 field_number, QByteArray& qba);
 void set_qba_record_field(DW_Record dr, u4 field_number, const QByteArray& qba);

 void set_creation_datetime(QDateTime dtm);
 void set_creation_datetime();

 void* query_leading_rec(u4 col);
 void* query_leading_str(u4 col);
 void* query_leading_int(u4 col);

 void* init_subvalues_record(DW_Record dr, u4 len, u4 col, u4 new_id);

 void read_subvalues_record(DW_Record dr, QStringList& qsl);

 DW_Record match_edges_label(DW_Record dr, QString label, DW_Record& ann, 
   u4 start_col, u4 offset);

 DW_Record get_outedges_record(DW_Record base, u4 col);
 DW_Record get_subvalues_record(DW_Record base, u4 col);
 DW_Record get_multi_index_record(DW_Record base, u4 col);
 DW_Record get_properties_record(DW_Record base, u4 col);
 DW_Record get_subsidiary_record(DW_Record base, u4 col);

 DW_Record find_record_by_string(QString value, u4 col);

 void read_subvalues(DW_Record dr, QStringList& qsl, u4 start_col);
 u4 read_qstrings(DW_Record dr, QStringList& qsl, u4 start_col, u4 offset, 
   QString filter = {}, QString stop_filter = {});

 void* get_record_by_id(u4 id);
 u4 get_record_id(void* rec);
 void* get_index_record_ref_target(void* rec);
 void* get_index_record_ref_target(void* rec, u4 ref_id_column, u4* and_ref_id);

 void set_record_id_field(void* rec, u4 id);
 n8 set_record_field(void* rec, u4 col, DW_Stage_Value& dwsv);


 void* new_wg_record(u4 number_of_columns, u4 col0,
   const QByteArray& col1, u4 qba_field = 1);
 void* new_wg_record(u4 number_of_columns, u4 col0, QString col1);
 void* new_wg_record(u4 number_of_columns);
 void* new_wg_record(u4 number_of_columns, u4 col0);

 DW_Record check_reset_ref_field(DW_Record base, u4 col, u4 new_size); //, u4 (*fn)() );

 void populate_edges_or_property_record(DW_Record new_rec, DW_Record base, 
   QVector<QPair<QPair<QString, DW_Record>, DW_Record>>& targets);

// void set_record_field(void* rec, u4 field_number, const QByteAfrray& qba);

 void set_wg_record_field_property(DW_Record dr, u4 col, DW_Record pseudo_record);

 void set_tag_field(DW_Record dr, u4 col, QString str);
 QString get_tag_field(DW_Record dr, u4 col);

 static QString static_to_ntxh(); 
 void to_ntxh(QString& result);

};


_KANS(DGDB)


#endif // WDB_INSTANCE__H


