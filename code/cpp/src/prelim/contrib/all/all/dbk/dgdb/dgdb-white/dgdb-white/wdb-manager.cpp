
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "wdb-manager.h"

#include "wdb-instance.h"

#include "dw-instance.h"

#include <QDebug>

#include "kans.h"
#include "textio.h"

//?#include "phaong/phaong.h"
//?#include "phaong/phaong-types.h"

//?
#include "ntxh-parser/ntxh-document.h"

USING_KANS(HGDMCore)

//KA::HGDMCore::NTXH_Document::NTXH_Document(QString path)
// : graph_(nullptr), grammar_(nullptr)
//{
//}


USING_KANS(TextIO)

extern "C" {
#include "whitedb/_whitedb.h"
}


USING_KANS(DGDB)


WDB_Manager::WDB_Manager(DW_Instance* dw_instance)
  :  dw_instance_(dw_instance), 
     max_num_code_(1000), default_mem_size_(0), 
     current_white_(0), first_new_white_(nullptr),
     last_new_white_(nullptr)
{


}

struct WDB_Manager::Query_Iterator
{
 WDB_Instance* wdb;
 wg_query* query;
 void* last;
 void* next;
 u4 count; 

 u1 ref_col;

};

// // duplicate from wdb-instance.cpp
extern wg_int _wg_encode_query_param(void* wh, DW_Stage_Value& dwsv);


DW_Record WDB_Manager::resolve_ref(Query_Iterator* qi)
{
 WDB_Instance* wdb = get_current_white();

 void* white = wdb->white();

 wg_int f = wg_get_field(white, qi->next, qi->ref_col);

 void* rec = nullptr;
 if(dw_instance_->Config.flags.avoid_record_pointers)
 {
  u4 refid = wg_decode_int(white, f);
  rec = wg_find_record_int(white, 0, WG_COND_EQUAL, refid, nullptr);
 }
 else
   rec = wg_decode_record(white, f);
 wg_int id = wg_get_field(white, rec, 0);
 return {wg_decode_int(white, id), rec};
}

WDB_Manager::Query_Iterator* WDB_Manager::new_single_index_query_iterator(QString key,
  u4 id_low, u4 id_high, u4 key_col, u4 val_col,
  DW_Stage_Value& dwsv, u4 ref_col, u4 id_col)
{
 WDB_Instance* wdb = get_current_white();

 void* white = wdb->white();

 u1 arglist_size = 4;

 wg_query_arg arglist[arglist_size];

 arglist[0].column = id_col;
 arglist[0].cond = WG_COND_LESSTHAN;
 arglist[0].value = wg_encode_query_param_int(white, id_high);

 arglist[1].column = id_col;
 arglist[1].cond = WG_COND_GREATER;
 arglist[1].value = wg_encode_query_param_int(white, id_low);

 arglist[2].column = key_col;
 arglist[2].cond = WG_COND_EQUAL;
 arglist[2].value = wg_encode_query_param_str(white,
   Q_TO_STD(key), nullptr);


 arglist[3].column = val_col;
 arglist[3].cond = WG_COND_EQUAL;
 arglist[3].value = _wg_encode_query_param(white, dwsv);

 wg_query* query = wg_make_query(white, nullptr, 0, arglist, arglist_size);
 return new Query_Iterator {wdb, query, nullptr, nullptr, 0,
   (u1) ref_col};

}


WDB_Manager::Query_Iterator* WDB_Manager::new_free_form_query_iterator(u4 threshold, u4 id_col)
{
 WDB_Instance* wdb = get_current_white();

 void* white = wdb->white();

 u1 arglist_size = 1;

 wg_query_arg arglist[arglist_size];

 arglist[0].column = id_col;
 arglist[0].cond = WG_COND_GTEQUAL;
 arglist[0].value = wg_encode_query_param_int(white, (u4) -threshold);

 wg_query* query = wg_make_query(white, nullptr, 0, arglist, arglist_size);
 return new Query_Iterator {wdb, query, nullptr, nullptr, 0, 0};
}


WDB_Manager::Query_Iterator* WDB_Manager::new_query_iterator(QString criterion, 
  u4 id_low, u4 id_high, u4 col, u4 id_col)
{
 WDB_Instance* wdb = get_current_white(); 

 void* white = wdb->white();

 u1 arglist_size = 3;

 wg_query_arg arglist[arglist_size];

 arglist[0].column = id_col;
 arglist[0].cond = WG_COND_LESSTHAN;
 arglist[0].value = wg_encode_query_param_int(white, id_high);

 arglist[1].column = id_col;
 arglist[1].cond = WG_COND_GREATER;
 arglist[1].value = wg_encode_query_param_int(white, id_low);

 arglist[2].column = col;
 arglist[2].cond = WG_COND_EQUAL;
 arglist[2].value = wg_encode_query_param_str(white, 
   Q_TO_STD(criterion), nullptr);

 wg_query* query = wg_make_query(white, nullptr, 0, arglist, arglist_size);
 return new Query_Iterator {wdb, query, nullptr, nullptr, 0, 0};
}


void WDB_Manager::get_hypernode_payload(Query_Iterator* qi, 
  QByteArray& qba, u4 qba_index)
{
 qi->wdb->get_qba_from_record(qi->next, qba_index, qba);
}


void* WDB_Manager::cycle_query(Query_Iterator* qi)
{
 void* rec = wg_fetch(qi->wdb->white(), qi->query);
 if(rec)
 {
  qi->last = qi->next;
  qi->next = rec;
  ++qi->count;
 }
 return rec;
}


QString WDB_Manager::get_restore_file()
{
 return {}; //?current_white_->get_local_file_name();
}

WDB_Instance* WDB_Manager::get_current_white()
{
 if(!current_white_)
 {
  current_white_ = new_white();
  if(last_new_white_)
    first_new_white_ = last_new_white_;
 }
 return current_white_;
}

void WDB_Manager::update_ntxh()
{
 QString ntxh;
 to_ntxh(ntxh);
 save_file(db_root_folder_ + "/" + "manager.ntxh", ntxh);  
}

void WDB_Manager::to_ntxh(QString& result)
{
 QString dty; 
 QString dr;
 dw_instance_->to_ntxh(dty, dr);

 result = QString(R"(

%1

%2

&/

%3
 )").arg(dty).arg(WDB_Instance::static_to_ntxh()).arg(dr);

 for(WDB_Instance* white : whites_.values())
 {
  QString wr;
  white->to_ntxh(wr);
  result += "\n" + wr + "\n";
 }

 result += "/&\n\n";
}


void WDB_Manager::init_from_ntxh()
{
 NTXH_Document doc(db_root_folder_ + "/" + "manager.ntxh");
 doc.parse();

#ifdef HIDE
 typedef NTXH_Graph::hypernode_type hypernode_type;

 QVector<hypernode_type*>& hns = doc.top_level_hypernodes();

 QVectorIterator<hypernode_type*> it(hns);

 hypernode_type* hn = it.next();
 doc.graph()->get_sfs(hn, {1,2}, 
   [this](QVector<QPair<QString, void*>>& prs)
 {
  QString fld = prs[0].first;
  u1 code = prs[1].first.toInt();
  dw_instance_->init_from_ntxh(fld, code);
 });

 while(it.hasNext())
 {
  hypernode_type* hn = it.next();
  QString name;
  QVector<QDateTime> dts {{},{},{}}; 

  doc.graph()->get_sfsr(hn, {{1,4}}, 
  [&name, &dts, this](QVector<QPair<QString, void*>>& prs)
  {
   name = prs[0].first;
   std::transform(prs.begin() + 1, prs.end(), dts.begin(), 
     [](const QPair<QString, void*>& pr) -> QDateTime
     { 
      if(!pr.first.isEmpty())
        return QDateTime::fromString(pr.first);
     });
  });

  qDebug() << "Database Name: " << name;
  qDebug() << "Database Datetimes: " << dts;
 }
#endif //def HIDE 
}


WDB_Instance* WDB_Manager::check_reinit()
{
 if(current_white_)
 {
  WDB_Instance* old_white = current_white_;
  current_white_ = new_white();
  delete old_white;
  return current_white_;
 }
 return nullptr;
}

WDB_Instance* WDB_Manager::new_white(u2 num_code, n8 mem, QString name)
{
 if( (num_code == 0) && !dw_instance_->Config.flags.local_scratch_mode )
 {
  if(!dw_instance_->Config.flags.temp_reinit)
    max_num_code_ += 100;
  num_code = max_num_code_;
 }
 if(mem == 0)
   mem = default_mem_size_;

 void* db = nullptr;

 WDB_Instance** maybe_new = nullptr;

 if(dw_instance_->Config.flags.local_scratch_mode)
 {
  qDebug() << "Using local database ...";
  db = wg_attach_local_database(mem); 

  if(!db)
    qDebug() << "Failed to attach local database ...";

  maybe_new = &last_new_white_;
 }
 else if(dw_instance_->Config.flags.scratch_mode | dw_instance_->Config.flags.temp_reinit)
 {
  void* _db = wg_attach_existing_database(
    QString::number(num_code).toLatin1().data());
  if(_db)
  {
   qDebug() << "Resetting database ...";
   int ok = wg_delete_database(QString::number(num_code).toLatin1().data());
   if(ok > 0)
   {
    qDebug() << "Failed to delete database: " << num_code;
    // // error ... throw something?
   }
   qDebug() << "After reset attaching database ..." << num_code;
  } 
  else
  { 
   qDebug() << "Attaching new database ..." << num_code;
   maybe_new = &last_new_white_;
  }
  db = wg_attach_database(QString::number(num_code).toLatin1().data(), mem);    
 }
 else
 {
  qDebug() << "Attaching database ..." << num_code;
  db = wg_attach_database(QString::number(num_code).toLatin1().data(), mem);
 }

 if(!db)
   return nullptr;

 WDB_Instance* result = new WDB_Instance(dw_instance_, db, name);
 result->set_creation_datetime();
 result->set_num_code(num_code);

 whites_[num_code] = result;

 if(!name.isEmpty())
 {
  whites_by_name_[name] = result;
 }

 if(maybe_new)
   *maybe_new = result;

 update_ntxh();

 return result; 
}

