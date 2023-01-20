
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include <QDebug>
#include <QByteArray>
#include <QDataStream>

#include <QDate>

#include "demo-class.h"

#include "queue-demo-class.h"


#include "dgdb-white/dw-instance.h"
#include "dgdb-white/dw-record.h"

#include "dgdb-white/dw-stage-value.h"
#include "dgdb-white/stage/dw-stage-queue.h"

#include "dgdb-white/dw-frame.h"
#include "dgdb-white/dw-dominion.h"


#include "dgdb-white/wdb-manager.h"
#include "dgdb-white/dgenvironment.h"

#include "dgdb-white/wdb-instance.h"
#include "dgdb-white/types/dw-type-system.h"
#include "dgdb-white/types/dw-type.h"

#include "global-types.h"


USING_KANS(DGDB)


int main1(int argc, char* argv[])
{
 DW_Instance* dw = DGEnvironment(
   DEFAULT_DEV_DGDB_FOLDER "/instances/t1");

 // // local_scratch_mode has no persistence at all.
  //   Scratch mode resets the database whenever it is
  //   opened by DigammaDB, but keeps the database in memory 
  //   in between (so e.g. it can be examined via the wgdb utility). 
// dw->Config.flags.local_scratch_mode = true;

 dw->Config.flags.scratch_mode = true;
 dw->Config.flags.avoid_record_pointers = true;

 dw->init();


 DW_Type_System* dwt = dw->type_system();

//? dwt->REGISTER_TYPE_NAME_RESOLUTION(QString);
 dwt->REGISTER_TYPE_NAME_RESOLUTION(Queue_Demo_Class);

 dwt->REGISTER_TYPE(Queue_Demo_Class)
   .default_object_layout()
   .set_stage_encoder(&Queue_Demo_Class::encode_stage_values)
   .set_stage_queue_initializer(&Queue_Demo_Class::init_stage_queue)
   .set_default_stage_queue_reader(&Queue_Demo_Class::read_stage_queue)
  ;
   //.set_stage_queue_reader(&Queue_Demo_Class::read_stage_queue)

   //.set_stage_queue_reader( default_stage_queue_reader
   //  <Queue_Demo_Class>( &Queue_Demo_Class::read_stage_queue ));


 DW_Type* Queue_Demo_Class_dw_type = dwt->get_type_by_name("Queue_Demo_Class");

 qDebug() << "name: " << Queue_Demo_Class_dw_type->name();
 

 Queue_Demo_Class* qdc = new Queue_Demo_Class;
 qdc->set_author("Immanuel Kant");
 qdc->set_title("Critique of Pure Reason");
 qdc->set_num(777);
 qdc->set_publication_date(QDate(1787, 4, 23));
 qdc->set_test_time(QTime(11,47,22,888));


 DW_Record dwr1 = dw->register_typed_value(qdc);

 DW_Stage_Value dwsv;
 dwsv.set_u2_data(777);
 
 DW_Record dwr2 = dw->query_by_index_record(dwsv, "Book.Pages");
 qDebug() << "dwr2 id: " << dwr2.id();

 DW_Stage_Value dwsv1;
 dwsv1.set_str_data("Critique of Pure Reason"); //new_qstring("Critique of Pure Reason");

 DW_Record dwr3 = dw->query_by_multi_index_record(dwsv1, "Queue_Demo_Class", 3);
 qDebug() << "dwr3 id: " << dwr3.id();

 //Queue_Demo_Class* qdc1 = new Queue_Demo_Class; //;dw->new_typed_value<Queue_Demo_Class>(dwr3);

 Queue_Demo_Class* qdc1 = dw->parse_dw_record<Queue_Demo_Class>(dwr3);


 qDebug() << "author: " << qdc1->author();
 qDebug() << "title: " << qdc1->title();
 qDebug() << "num: " << qdc1->num();
 qDebug() << "test_time: " << qdc1->test_time();
 qDebug() << "publication_date: " << qdc1->publication_date();
 
 return 0;
}


int main6(int argc, char* argv[])
{
 DW_Instance* dw = DGEnvironment(
   DEFAULT_DEV_DGDB_FOLDER "/instances/t1");

 // // local_scratch_mode has no persistence at all.
  //   Scratch mode resets the database whenever it is
  //   opened by DigammaDB, but keeps the database in memory 
  //   in between (so e.g. it can be examined via the wgdb utility). 
 dw->Config.flags.local_scratch_mode = true;

 //dw->Config.flags.scratch_mode = true;
 dw->init();


 DW_Type_System* dwt = dw->type_system();

//? dwt->REGISTER_TYPE_NAME_RESOLUTION(QString);
 dwt->REGISTER_TYPE_NAME_RESOLUTION(Queue_Demo_Class);

 dwt->REGISTER_TYPE(Queue_Demo_Class)
   .default_object_layout()
   .set_stage_encoder(&Queue_Demo_Class::encode_stage_values)
   .set_stage_queue_initializer(&Queue_Demo_Class::init_stage_queue)
;

 DW_Type* Queue_Demo_Class_dw_type = dwt->get_type_by_name("Queue_Demo_Class");

 qDebug() << "name: " << Queue_Demo_Class_dw_type->name();
 

 QMap<u4, DW_Stage_Value> svals;

 DW_Stage_Value::Callback_type cb1 = [dw, &svals](u4 u, QString col, DW_Stage_Value* v)
 {
  qDebug() << "u = " << u;
  
//  svals[u] = *v;
 };


 Queue_Demo_Class* qdc = new Queue_Demo_Class;
 qdc->set_author("Immanuel Kant");
 qdc->set_title("Critique of Pure Reason");
 qdc->set_num(777);
 qdc->set_publication_date(QDate(1787, 4, 23));
 qdc->set_test_time(QTime(11,47,22,888));

 DW_Stage_Value::Callback_type cb = [] //&single_index_vals, &multi_index_vals]
   (u4 u, QString col, DW_Stage_Value* v)
 {
/*
  if(u)
    multi_index_vals[u] = v;
  else
    single_index_vals[col] = v;
*/
  qDebug() << "1 u = " << u << ", col = " << col; 
 };

 DW_Stage_Value::Package pkg;

 dw->test_register_value(qdc, &pkg);

 qDebug() << "pkg qba: " << pkg.qba;
 qDebug() << "pkg si: " << pkg.single_indexed.keys();
 qDebug() << "pkg mi: " << pkg.multi_indexed.keys();

 QByteArray demo_qba;
 dw->test_register_value(qdc, cb, &demo_qba);
 qDebug() << "demo qba: " << demo_qba;
}

int main2(int argc, char* argv[])
{
 DW_Instance* dw = DGEnvironment(
   DEFAULT_DEV_DGDB_FOLDER "/instances/t1");

 // // local_scratch_mode has no persistence at all.
  //   Scratch mode resets the database whenever it is
  //   opened by DigammaDB, but keeps the database in memory 
  //   in between (so e.g. it can be examined via the wgdb utility). 
 //dw->Config.flags.local_scratch_mode = true;

 dw->Config.flags.scratch_mode = true;
 dw->init();




 DW_Stage_Value dwsv1;
 //?
// dwsv1.set_str_data("test", 5);
 //dwsv1.set_u4_data(66);

 dwsv1.set_int_data(5);

 void* rec = dw->add_raw_record(2, {dwsv1});

 qDebug() << "rec = " << rec;


 DW_Stage_Value dwsv0;
 dwsv0.set_str_data("test", 5);
 void* rec0 = dw->add_raw_record(2, {dwsv0});

// DW_Stage_Value dwsv2;
// dwsv2.set_rec_data(rec);
// dw->set_raw_record_fields(rec, 1, {dwsv2});


 DW_Stage_Value dwsv2;
 //dwsv2.set_str_data("rec");
 dwsv2.set_rec_data(rec0);
 dw->set_raw_record_fields(rec, 1, {dwsv2});

// void* v1 = dw->query_leading_str(0); 
//? 
 void* v2 = dw->query_leading_int(0); 
 qDebug() << "v2 = " << v2;

 void* v1 = dw->query_leading_rec(1); 
 qDebug() << "v1 = " << v1;

 void* v3 = dw->query_leading_str(0); 
 qDebug() << "v3 = " << v3;

 
}

int main(int argc, char* argv[])
{
 DW_Instance* dw = DGEnvironment(
   DEFAULT_DEV_DGDB_FOLDER "/instances/t1");

 // // local_scratch_mode has no persistence at all.
  //   Scratch mode resets the database whenever it is
  //   opened by DigammaDB, but keeps the database in memory 
  //   in between (so e.g. it can be examined via the wgdb utility). 
 //dw->Config.flags.local_scratch_mode = true;

 dw->Config.flags.scratch_mode = true;
 dw->Config.flags.avoid_record_pointers = true;

 dw->init();

 DW_Type_System* dwt = dw->type_system();

 dwt->REGISTER_TYPE_NAME_RESOLUTION(Demo_Class);
 dwt->REGISTER_TYPE(Demo_Class)
   .set_default_binary_encoder(&Demo_Class::supply_data)
   .set_default_binary_decoder(&Demo_Class::absorb_data)
  ;
 

 qDebug() << "DB root folder: " << dw->db_root_folder();

 Demo_Class dc1;
 dc1.set_a_string("Test Payload");
 dc1.set_a_number(77);

 QByteArray qba1;
 dc1.supply_data(qba1);

 DW_Record dwr1 = dw->new_binary_hypernode_record(qba1);


 Demo_Class dc2;
 dc2.set_a_string("Test Hyperedge");
 dc2.set_a_number(88);

 QByteArray qba2;
 dc2.supply_data(qba2);

 DW_Record dwr2 = dw->new_binary_hypernode_record(qba2);

 DW_Frame& fr = *dw->new_frame(); // new DW_Frame(dw);
 DW_Dominion* dom = new DW_Dominion();

 DW_Context* ctxt = fr.new_context();


 dwr1 << (fr/dom/ctxt)["Demo.SomeRelation"] >> dwr2;

 DW_Record dwr3 = dw->new_property<QString>("Test Property");

 dwr1 << (fr/dom/ctxt)["Demo.TestProperty"] >> dwr3;

 QPair<u4, u4> pr = fr.commit();
 qDebug() << "pr = " << pr;

 DW_Record dwr4 = dw->find_hyperedge(dwr1, "Demo.SomeRelation"); 

 qDebug() << "dwr4 = " << dwr4.id();

 Demo_Class* dc3 = dw->parse_binary_record<Demo_Class>(dwr4);

 qDebug() << "dc3 string = " << dc3->a_string()
   << "dc3 number = " << dc3->a_number();



 //(fr/dw)

 //dw->new_wg_outedges_record(dwr1 "Demo.SomeRelation" 

//? dw->add_hyperedge(dwr1, "Demo.SomeRelation", dwr2);



 //? dwr1 << (fr/dw)["Demo.SomeRelation"] >> dwr2;   

// DW_Record dwr3 = 
 
}

int main5(int argc, char* argv[])
{
 DW_Instance* dw = DGEnvironment(
   DEFAULT_DEV_DGDB_FOLDER "/instances/t1");

 // // local_scratch_mode has no persistence at all.
  //   Scratch mode resets the database whenever it is
  //   opened by DigammaDB, but keeps the database in memory 
  //   in between (so e.g. it can be examined via the wgdb utility). 
 //dw->Config.flags.local_scratch_mode = true;

// dw->Config.flags.scratch_mode = true;
 dw->init();

 QString rf = dw->get_restore_file();

 qDebug() << "RF = " << rf; 

 if(!rf.isEmpty())
 {
  dw->restore_from_file(rf);
  dw->reinit();
 }


}

int main4(int argc, char* argv[])
{
 DW_Instance* dw = DGEnvironment(
   DEFAULT_DEV_DGDB_FOLDER "/instances/t1");

 // // local_scratch_mode has no persistence at all.
  //   Scratch mode resets the database whenever it is
  //   opened by DigammaDB, but keeps the database in memory 
  //   in between (so e.g. it can be examined via the wgdb utility). 
 //dw->Config.flags.local_scratch_mode = true;

// dw->Config.flags.scratch_mode = true;
 dw->init();

 QString rf = dw->get_restore_file();

 qDebug() << "RF = " << rf; 

 qDebug() << "DB root folder: " << dw->db_root_folder();

 Demo_Class dc;
 dc.set_a_string("Test Payload");
 dc.set_a_number(77);

 QByteArray qba;
 dc.supply_data(qba);

 DW_Record dwr = dw->new_binary_hypernode_record(qba);

 QByteArray qba1;
 dw->get_hypernode_payload(dwr.id(), qba1);

 Demo_Class dc1;
 dc1.absorb_data(qba1);

 qDebug() << "ok: " << dc1.a_string() << dc1.a_number(); 

 DW_Stage_Value dwsv;
 dwsv.set_u4_data(dc.a_number());

 u1 et = dwsv.get_dw_encoding_type();
   
 DW_Record dwr1 = dw->new_wg_index_record(dwr, dwsv);
 
 DW_Stage_Value dwsv1;
 dwsv1.set_u4_data(dc.a_number());
 
 DW_Record dwr2 = dw->query_by_index_record(dwsv1);

 QByteArray qba2;
 dw->get_hypernode_payload(dwr2, qba2);
 
 Demo_Class dc2;
 dc2.absorb_data(qba2);
 qDebug() << "ok: " << dc2.a_string() << dc2.a_number(); 

 dw->save_changes();

}



