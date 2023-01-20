
//           Copyright Nathaniel Christen 2021.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "dgdb-database-instance.h"

#include <QDir>
#include <QFileInfo>

#include "dh-location-structure.h"

#include "dwb/dwb-instance.h"

//#include "


#include "tkrzw/tkrzw_dbm.h"

#include "types/dh-type.h"

using namespace tkrzw;

#include <string_view>

#include "dh-record-processors.h"

#include "dh-stage-value.h"

#include "conversions.h"

#include "dgdb-hypernode.h"

#include <QDataStream>

//template<DH_Location_Structure::Data_Options OPTS>
//void store_subvalue_(DH_Location_Structure dls, DgDb_Hypernode* dh, DH_Subvalue_Field* sf, DH_Stage_Value& sv, // const QByteArray& value, QString field_name);


void DgDb_Database_Instance::store_subvalue_to_external_record(DH_Subvalue_Field* sf,
   DWB_Instance* dwb, void* rec, char* mem, DH_Stage_Value& sv) //const QByteArray& value)
{
 dwb->write_field(rec, sf->query_column(), sv);

 // //  are we re-encoding this?  Would it be more efficient to get the enc
  //    when the record is extracted?  Or is encoding quick enough that it's
  //    not worth the hassle passing the end around? ...
 QByteArray enc = dwb->encode_record(rec);
 memcpy(mem, enc.data(), enc.size());

}

void DgDb_Database_Instance::store_subvalue_to_external_record(DgDb_Hypernode* dh,
  DH_Subvalue_Field* sf, char* mem, DH_Stage_Value& sv) //const QByteArray& value)
{
 DWB_Instance* dwb = get_query_dwb(dh->dh_type(), sf);
 void* rec = get_wdb_record_from_block(dh->shm_block());

 n8 rid = blocks_dwb_->get_record_id(rec);

 // //  assume always 2 for now ...
 static u1 rec_column = 2;

 u2 qc = sf->query_column();

 //  this is presumably obsolete because the qc is now set to a default ...
 //  if(qc == 0)
 //  {
 //   // //  note: here we're updating sf ...
 //   qc = rec_column + 1;
 //   sf->set_query_column(qc);
 //  }

 u2 max = sf->max_partner_query_column();

 // //  also assume the query columns are the last column (so
 //    we don't need to allocate more fields than that ...)
 max = max? max + 1 : qc + 1;

 // //  assume always 1 for now ...
 static u1 target_id_column = 1;
 n8 qrid = new_record_id(_queries_rec_id_category_floor);

 // //  assume always 0 for now ...
 static u1 rec_id_column = 0;

 // //  these are not currently used but help to clarify db contents when displayed ...
 n8 hypernode_id = dh->id();
 // //  assyme always 3 for now ...
 u2 hypernode_id_column = 3;

 void* qrec = dwb->new_query_record(blocks_dwb_, rec, rid, rec_column,
   hypernode_id, qc, sv, max, Config.flags.avoid_record_pointers);

 QByteArray enc = dwb->encode_record(qrec);
 memcpy(mem, enc.data(), enc.size());

 // //  store the hypernode id for testing/demo -- currently not strictly needed.
 //    The wgdn utility doesn't work well with direct inter-record links
 //    so id's can be used in lieu of rec's to look at db contents temporarily
// dwb->write_u1_field(qrec, target_id_column, dh->id());

 dwb->write_n8_field(qrec, target_id_column, rid);
 dwb->write_n8_field(qrec, rec_id_column, qrid);
 dwb->write_n8_field(qrec, hypernode_id_column, hypernode_id);
}


void DgDb_Database_Instance::store_subvalue_to_record(DH_Subvalue_Field* sf, char* mem,
  DH_Stage_Value& sv) //                                                    const QByteArray& value)
{
 u2 spl = sf->block_offset_record_column_split();

 u2 adj = blocks_dwb_->write_rec_field_via_split((char*)mem, spl, sv); //value);
 QByteArray qba = u2_to_qba(adj? adj : spl);
 memcpy(mem, qba.data(), qba.size());
}

void DgDb_Database_Instance::store_subvalue_to_block(DH_Subvalue_Field* sf,
  char* mem, DH_Stage_Value& sv)
{
 n8 enc = blocks_dwb_->write_encoded_value(sv); //value);
 QByteArray qba = n8_to_qba(enc);
 memcpy(mem, qba.data(), qba.size());
}



template<>
void DgDb_Database_Instance::store_subvalue_<DH_Location_Structure::Data_Options::QVariant>
  (DH_Location_Structure dls, DgDb_Hypernode* dh, DH_Subvalue_Field* sf, DH_Stage_Value& sv, // const QByteArray& value,
   QString field_name)
{
 // store_node_data(dls, value);
}


template<>
void DgDb_Database_Instance::store_subvalue_<DH_Location_Structure::Data_Options::Numeric>
  (DH_Location_Structure dls, DgDb_Hypernode* dh, DH_Subvalue_Field* sf, DH_Stage_Value& sv, // const QByteArray& value,
   QString field_name)
{
 // store_node_data(dls, value);
}


template<>
void DgDb_Database_Instance::store_subvalue_<DH_Location_Structure::Data_Options::QString>
(DH_Location_Structure dls, DgDb_Hypernode* dh, DH_Subvalue_Field* sf, DH_Stage_Value& sv, // const QByteArray& value,
 QString field_name)
{
 // store_node_data(dls, value);
}

template<>
void DgDb_Database_Instance::store_subvalue_<DH_Location_Structure::Data_Options::Raw_Binary>
(DH_Location_Structure dls, DgDb_Hypernode* dh, DH_Subvalue_Field* sf, DH_Stage_Value& sv, // const QByteArray& value,
 QString field_name)
{
 // store_node_data(dls, value);
}

template<>
void DgDb_Database_Instance::store_subvalue_<DH_Location_Structure::Data_Options::Shm_Pointer>
(DH_Location_Structure dls, DgDb_Hypernode* dh, DH_Subvalue_Field* sf, DH_Stage_Value& sv, // const QByteArray& value,
 QString field_name)
{
 void* mem = default_get_shm_field_ptr(dls, dh, dls.get_raw_primary_field_id(), field_name, nullptr, nullptr);

 //DH_Type* dht = dh->dh_type();
 DH_Subvalue_Field::Write_Mode wm = sf->write_mode();
 switch (wm)
 {
 case DH_Subvalue_Field::In_Block:
  {
   QByteArray value;
   sv.to_qba(value);
   memcpy(mem, value.data(), value.size());
  }
  break;

 case DH_Subvalue_Field::Redirect_In_Block:
  break;

 case DH_Subvalue_Field::Redirect_In_Record:
  {
   store_subvalue_to_record(sf, (char*) mem, sv); //value);

  }
  break;

 case DH_Subvalue_Field::Redirect_External:
  {
   store_subvalue_to_external_record(dh, sf, (char*) mem, sv);// value);
//   DWB_Instance* dwb = get_query_dwb(dh->dh_type(), *sf);
//   void* rec = get_wdb_record_from_block(dh->shm_block());

//   // //  assume always 2 for now ...
//   static u1 rec_column = 2;

//   // //  also assume the query column is the last column (so
//    //    we don't need to allocate more fields than that ...)
//   void* qrec = dwb->new_query_record(blocks_dwb_, rec, rec_column, sf->query_column(),
//     value, sf->query_column() + 1);

//   QByteArray enc = dwb->encode_record(qrec);
//   memcpy(mem, enc.data(), enc.size());



  }
  break;

 }


 //ktype_<n8>::set ks(*nodes_dbm_);
 store_node_data(dls, mem);
}

template<>
void DgDb_Database_Instance::store_subvalue_<DH_Location_Structure::Data_Options::Shm_Pointer_With_Path_Code>
(DH_Location_Structure dls, DgDb_Hypernode* dh, DH_Subvalue_Field* sf, DH_Stage_Value& sv, // const QByteArray& value,
 QString field_name)
{
 //?get_shm_field_ptr_(*this, *dh, dls.get_raw_primary_field_id(), field_name, nullptr, nullptr);
 //// store_node_data(dls, value);
}

template<>
void DgDb_Database_Instance::store_subvalue_<DH_Location_Structure::Data_Options::In_Edge>
(DH_Location_Structure dls, DgDb_Hypernode* dh, DH_Subvalue_Field* sf, DH_Stage_Value& sv, // const QByteArray& value,
 QString field_name)
{
 // store_node_data(dls, value);
}

template<>
void DgDb_Database_Instance::store_subvalue_<DH_Location_Structure::Data_Options::Out_Edge>
(DH_Location_Structure dls, DgDb_Hypernode* dh, DH_Subvalue_Field* sf, DH_Stage_Value& sv, // const QByteArray& value,
 QString field_name)
{
 // store_node_data(dls, value);
}

template<>
void DgDb_Database_Instance::store_subvalue_<DH_Location_Structure::Data_Options::Signed_Numeric>
(DH_Location_Structure dls, DgDb_Hypernode* dh, DH_Subvalue_Field* sf, DH_Stage_Value& sv, // const QByteArray& value,
 QString field_name)
{
 // store_node_data(dls, value);
}

template<>
void DgDb_Database_Instance::store_subvalue_<DH_Location_Structure::Data_Options::Typed_Numeric>
(DH_Location_Structure dls, DgDb_Hypernode* dh, DH_Subvalue_Field* sf, DH_Stage_Value& sv, // const QByteArray& value,
 QString field_name)
{
 // store_node_data(dls, value);
}

template<>
void DgDb_Database_Instance::store_subvalue_<DH_Location_Structure::Data_Options::Typed_QString>
(DH_Location_Structure dls, DgDb_Hypernode* dh, DH_Subvalue_Field* sf, DH_Stage_Value& sv, // const QByteArray& value,
 QString field_name)
{
 // store_node_data(dls, value);
}

template<>
void DgDb_Database_Instance::store_subvalue_<DH_Location_Structure::Data_Options::Typed_Raw_Binary>
(DH_Location_Structure dls, DgDb_Hypernode* dh, DH_Subvalue_Field* sf, DH_Stage_Value& sv, // const QByteArray& value,
 QString field_name)
{
 // store_node_data(dls, value);
}

template<>
void DgDb_Database_Instance::store_subvalue_<DH_Location_Structure::Data_Options::Typed_Shm_Pointer>
(DH_Location_Structure dls, DgDb_Hypernode* dh, DH_Subvalue_Field* sf, DH_Stage_Value& sv, // const QByteArray& value,
 QString field_name)
{
 // store_node_data(dls, value);
}

template<>
void DgDb_Database_Instance::store_subvalue_<DH_Location_Structure::Data_Options::Typed_Shm_Pointer_With_Path_Code>
(DH_Location_Structure dls, DgDb_Hypernode* dh, DH_Subvalue_Field* sf, DH_Stage_Value& sv, // const QByteArray& value,
 QString field_name)
{
 // store_node_data(dls, value);
}

template<>
void DgDb_Database_Instance::store_subvalue_<DH_Location_Structure::Data_Options::Typed_In_Edge>
(DH_Location_Structure dls, DgDb_Hypernode* dh, DH_Subvalue_Field* sf, DH_Stage_Value& sv, // const QByteArray& value,
 QString field_name)
{
 // store_node_data(dls, value);
}

template<>
void DgDb_Database_Instance::store_subvalue_<DH_Location_Structure::Data_Options::Typed_Out_Edge>
(DH_Location_Structure dls, DgDb_Hypernode* dh, DH_Subvalue_Field* sf, DH_Stage_Value& sv, // const QByteArray& value,
 QString field_name)
{
 // store_node_data(dls, value);
}


