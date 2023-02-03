
//           Copyright Nathaniel Christen 2021.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "dtb-package.h"

#include "tkrzw/tkrzw_dbm.h"
#include "tkrzw/tkrzw_str_util.h"

#include <string_view>

#include "global-types.h"

#include "dh-record-processors.h"

#include <QDebug>

#include "graph/dh-frame.h"

#include "sv-wrapper.h"

USING_KANS(DGDB)


using namespace tkrzw;


DTB_Package::DTB_Package()
 :  info_dbm_(nullptr),
   nodes_dbm_(nullptr), hyperedge_index_(nullptr),
   pinterns_dbm_(nullptr), finterns_dbm_(nullptr),
   pinterns_count_(0), finterns_count_(0)
{
}

void DTB_Package::init_hyperedge_index(QString folder_path)
{
 TreeDBM::TuningParameters hyperedge_index_params;
 hyperedge_index_params.key_comparator = PairDecimalKeyComparator;

 QString path = folder_path + "/_hyperedge-index";

 hyperedge_index_ = new tkrzw::FileIndex;

 Status status = hyperedge_index_->Open(
   path.toStdString(), true, File::OPEN_TRUNCATE, hyperedge_index_params);

 if(status != Status::SUCCESS)
 {
  qDebug() << "index problem: " << status.GetCode();
 }
}

void DTB_Package::check_interns_dbm(QString folder_path)
{
 check_internal_dbm(folder_path, "_pinterns", pinterns_dbm_);
 check_internal_dbm(folder_path, "_finterns", finterns_dbm_);

 dbms_["info"] = (tkrzw::DBM**) &info_dbm_;
 dbms_["nodes"] = (tkrzw::DBM**) &nodes_dbm_;
 dbms_["pinterns"] = (tkrzw::DBM**) &pinterns_dbm_;
 dbms_["finterns"] = (tkrzw::DBM**) &finterns_dbm_;

 //check_internal_dbm(folder_path, "_hyperedge_index", finterns_dbm_);
 //return interns_dbm_;
}

HashDBM* DTB_Package::check_info_dbm(QString folder_path)
{
 check_internal_dbm(folder_path, "_info", info_dbm_);
 return info_dbm_;
}

HashDBM* DTB_Package::check_nodes_dbm(QString folder_path)
{
 check_internal_dbm(folder_path, "_nodes", nodes_dbm_);
 return nodes_dbm_;
}

void DTB_Package::check_internal_dbm(QString folder_path, QString which, tkrzw::HashDBM*& result)
{
 if(result)
 {
  if(!result->IsOpen())
    result->Open( (folder_path + "/" + which).toStdString(), true);
 }
 else
 {
  result = new HashDBM;
  result->Open( (folder_path + "/" + which).toStdString(), true);
 }
}

void DTB_Package::search_hyperedge_index(u4 node_id, QVector<DH_Location_Structure>& matches)
{
 std::string_view key = tkrzw::ToString(node_id);
 std::vector<std::string> vals = hyperedge_index_->GetValues(key);
 matches.resize(vals.size());
 std::transform(vals.begin(), vals.end(), matches.begin(),
   [](std::string val)
 {
  DH_Location_Structure result;
  result.set_raw_code(StrToInt(val));
  return result;
 });
}

void DTB_Package::index_hyperedge(u4 node_id, DH_Location_Structure dls) //const Hyperedge_Data& hd)//, tkrzw::FileIndex* hyperedge_index)
{
 hyperedge_index_->Add(ToString(node_id), ToString(dls.raw_code())); //ToString(hd.hyperedge_id));
}


void DTB_Package::process_info_record( tkrzw::DBM* dbm, QString key,
  create_cb(empty), update_cb(full) ) // void(*full)(Sv_3 svs), void(*empty)(Sv_2 svs))
{
 const std::string& skey = key.toStdString();
 QByteArray rqba;
 struct _rp : public DBM::RecordProcessor
 {
  std::string_view ProcessFull(std::string_view key,
    std::string_view value) override
  {   
   // //  create the qba for devel so we can see the bytes ..
   QByteArray vqba(value.data(), value.size());

   //std::string_view result;

   SV_Wrapper swk {key, nullptr};
   SV_Wrapper swv {value, nullptr};
   SV_Wrapper swr {{}, rqba};
   SV_Wrapper_3 svs{swk, swv, swr};
   _full(svs);

   // //  create the qba for devel so we can see the bytes ..
   QByteArray qba(swr.value.data(), swr.value.size());

   return swr.value;
  }

  std::string_view ProcessEmpty(std::string_view key) override
  {
   //std::string_view result;

   SV_Wrapper swk {key, nullptr};
   SV_Wrapper swr {{}, rqba};
   SV_Wrapper_2 svs{swk, swr};
   _empty(svs);

   // //  create the qba for devel so we can see the bytes ..
   QByteArray qba(swr.value.data(), swr.value.size());

   return swr.value;
  }

  void(*_full)(Sv_3);
  void(*_empty)(Sv_2);
  QByteArray* rqba;
  _rp(create_cb e, update_cb f, QByteArray* r)
    : _full(f), _empty(e), rqba(r) {}
 } rp(empty, full, &rqba);
 dbm->Process(skey, &rp, true).OrDie();
}


//void DTB_Package::process_info_record(tkrzw::DBM* dbm, QString key)
//{

//}


tkrzw::DBM* DTB_Package::find_dbm(QString key)
{
 auto it = dbms_.find(key);
 if(it == dbms_.end())
   return nullptr;
 return **it;
}

//void DTB_Package::index_pair(u4 key, u4 value,
//  tkrzw::DBM* dbm, tkrzw::FileIndex* index)
//{
// struct Updater : public DBM::RecordProcessor
// {
//  const std::string& primary_key = ToString()
//  std::string_view ProcessFull(std::string_view svkey,
//    std::string_view svvalue) override
//  {
//   //u4 uval = StrToInt(svvalue);
//   return NOOP;
//  }
//  std::string_view ProcessEmpty(std::string_view svkey) override
//  {
//   _division_index->Add(ToString(_pr.first), svkey);
//  }

//  QPair<u4, u4> _pr; // _value;
//  FileIndex* _index;
//  std::string _new_value
// } updater({key, value}, index);
// dbm->Process(primary_key, &updater, true).OrDie();
//}


void DTB_Package::store_hypernode_count_status(u4 count)
{
 //HashDBM* dbm =
 //check_info_dbm();

 // //  possibilities for other range checking as well ...
 u4 c = count & 0b0011'1111'1111'1111'1111'1111'1111'1111;

 ktype_<u4>::set ks(*info_dbm_);

 ks(":_hypernode_count", c);
}


s4 DTB_Package::read_hypernode_count_status()
{
 //check_info_dbm();
 ktype_<u4>::get kg;
 info_dbm_->Process(":_hypernode_count", &kg, true);
 return (s4) kg.data();
}

void DTB_Package::read_interns_count_status() //u2& p, u2& f)
{
 //check_info_dbm();
 static u2 kg_default = 0;
 ktype_<u2>::get kg (&kg_default);
 info_dbm_->Process(":_pinterns_count", &kg, true);
 pinterns_count_ = kg.data();
 kg.reset();
 info_dbm_->Process(":_finterns_count", &kg, true);
 finterns_count_ = kg.data();
}


void DTB_Package::store_node_data(DH_Location_Structure dls, void* value)
{
 std::string key(IntToStrBigEndian(dls.raw_code()));
 std::string_view sval((char*)&value, sizeof(void*));
 nodes_dbm_->Set(key, sval, true);
}



void DTB_Package::fetch_node_data(DH_Location_Structure dls, void*& result)
{
 std::string key(IntToStrBigEndian(dls.raw_code()));
 //std::string_view sval((char*)value.data(), value.size());
 //nodes_dbm_->Get(key, sval, true);

 ktype_<void*>::get kg(&result);

 Status st = nodes_dbm_->Process(key, &kg, true);

 result = kg.data();
}

u2 DTB_Package::check_field_id(QString key)
{
 auto it = field_ids_.find(key);
 if(it == field_ids_.end())
 {
  ktype_<u2>::get kg;
  Status st = finterns_dbm_->Process((char*)key.data(), &kg, true);
  if(st == Status::NOT_FOUND_ERROR)
  {

  }
  field_ids_[key] = kg.data();
  return kg.data();
 }
 return *it;
}

u2 DTB_Package::check_property_id(QString key)
{
 auto it = property_ids_.find(key);
 if(it == property_ids_.end())
 {
  ktype_<u2>::get kg;
  std::string_view kview((char*)key.data(), key.size() * 2);
  Status st = pinterns_dbm_->Process(kview, &kg, false);
  if(st == Status::BROKEN_DATA_ERROR)
  {
   ktype_<u2>::set ks(*pinterns_dbm_);
   ++pinterns_count_;
   ks(key, pinterns_count_);
   property_ids_[key] = pinterns_count_;
   return pinterns_count_;
  }
  property_ids_[key] = kg.data();
  return kg.data();
 }
 return *it;
}

void DTB_Package::fetch_node_data(DH_Location_Structure dls, QByteArray& result)
{
 std::string key(IntToStrBigEndian(dls.raw_code()));
 //std::string_view sval((char*)value.data(), value.size());
 //nodes_dbm_->Get(key, sval, true);

 ktype_<QByteArray*>::get kg(&result);

 Status st = nodes_dbm_->Process(key, &kg, true);

}


void DTB_Package::fetch_node_data(DH_Location_Structure dls, QVariant& result)
{
 std::string key(IntToStrBigEndian(dls.raw_code()));
 //std::string_view sval((char*)value.data(), value.size());
 //nodes_dbm_->Get(key, sval, true);

 //std::string value;
 ktype_<QVariant>::get kg;

 //Status st = nodes_dbm_->Get(key, &value);

 Status st = nodes_dbm_->Process(key, &kg, true);

 result = kg.data();

 //result = kg.data();
// QByteArray qba(kg.data(), value.size());
// QDataStream qds(qba);
// qds >> result;
}


void DTB_Package::store_node_data(DH_Location_Structure dls, const QByteArray& value)
{
 std::string key(IntToStrBigEndian(dls.raw_code()));
 std::string_view sval((char*)value.data(), value.size());
 nodes_dbm_->Set(key, sval, true);
// ktype_<n8>::set ks(*nodes_dbm_);
// ks();
}
