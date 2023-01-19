
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "default-basic-functions.h"
#include "default-test-functions.h"

#include "phaon-ir/runtime/phr-callable-value.h"
#include "phaon-ir/runtime/phr-expression-object.h"

#include "phaon-ir/eval/phr-channel-group-evaluator.h"
#include "phaon-ir/types/phr-type-object.h"
#include "phaon-ir/types/phr-type.h"

#include "phaon-ir/table/phr-channel-group-table.h"


#include <QTextStream>

#include <QDebug>

#include <QEventLoop>

#include "phaon-ir/types/phr-type-system.h"
#include "phaon-ir/phr-code-model.h"
#include "phaon-ir/channel/phr-channel-group.h"
#include "phaon-ir/table/phr-channel-group-table.h"

#include "phaon-ir/channel/phr-channel-system.h"
#include "phaon-ir/channel/phr-carrier.h"
#include "phaon-ir/phaon-ir.h"

#include "phr-fn-doc/phr-fn-doc.h"

USING_KANS(Phaon)

void fndoc_read(PHR_Fn_Doc* fnd, QString fn)
{
 qDebug() << "Reading " << fn << " ...";
 fnd->read(fn);
}

QString fndoc_test_summary(PHR_Fn_Doc* fnd)
{
 QString summ = fnd->test_summary();
 return summ;
}


void* insert_envv(void* kind, void* test)
{
 static QMap<QString, void*> hold;
 QString* k = reinterpret_cast<QString*>(kind);
 if(test)
 {
  hold[*k] = test;
 }
 return hold.value(*k);
}

void* envv(void* kind)
{
 if(kind)
 {
  qDebug() << "Kind: " << *(QString*)kind;
  return insert_envv(kind, nullptr);
 }
 else
 {
  qDebug() << "In envv: Return kind could not be determined.";
  return nullptr;
 }
}

quint64 let_num(quint64 num)
{
 return num;
}

void prs(QString arg)
{
 qDebug() << arg;
}

void prn(qint32 arg)
{
 qDebug() << arg;
}

void prnn(qint32 arg1, qint32 arg2)
{
 qDebug() << arg1;
 qDebug() << arg2;
}

void prdn(quint64 num, quint64 n1)
{
 qDebug() << num << ", " << n1;
}

void test_dfr(quint64 arg1, quint64 arg2)
{
 PHR_Expression_Object* px1 = (PHR_Expression_Object*) arg1;
 PHR_Channel_Group_Evaluator* ev1 = px1->run();
 quint32 r1 = ev1->get_result_value_as<quint32>();

 PHR_Expression_Object* px2 = (PHR_Expression_Object*) arg2;
 PHR_Channel_Group_Evaluator* ev2 = px2->run();
 quint32 r2 = ev2->get_result_value_as<quint32>();

 qDebug() << r1;
 qDebug() << r2;
}

void test_if_then_else(quint64 args_ptr)
{
 QVector<quint64>& args = *(QVector<quint64>*)(args_ptr);

 int i = 0;
 bool test = false;
 for(quint64 qui: args)
 {
  if(i % 2)
  {
   if(test)
   {
    PHR_Callable_Value** pcv = (PHR_Callable_Value**) qui;
    (*pcv)->run();
    return;
   }
  }
  else
  {
   PHR_Expression_Object** pxo = (PHR_Expression_Object**) qui;

   PHR_Channel_Group_Evaluator* ev = (*pxo)->run();
   qint32 i1 = ev->get_result_value_as<qint32>();
   test = (bool) i1;
  }
  ++i;
 }
}

void test_prss(QString str1, QString str2)
{
 qDebug() << str1;
 qDebug() << str2;
}

void test_arg_vec_calls(quint64 args_ptr)
{
 QVector<quint64>& args = *(QVector<quint64>*)(args_ptr);

 for(quint64 qui: args)
 {
  PHR_Callable_Value** pcv = (PHR_Callable_Value**) qui;
  (*pcv)->run();
 }
}


void if_t_e(quint64 args_ptr)
{
 test_if_then_else(args_ptr);
}

void test_calls(PHR_Callable_Value* pcv1, PHR_Callable_Value* pcv2)
{
 pcv1->run();
 pcv2->run();
}

void test_call(PHR_Callable_Value* pcv)
{
 pcv->run();
}

void test_pass_call(PHR_Callable_Value* pcv)
{
 pcv->run([](QString chn, QString& sym,
   PHR_Type_Object* pto, PHR_Carrier& phc,
   PHR_Scope_Value*& psv, PHR_Runtime_Scope::Storage_Options& so)
 {
  if(sym == "x")
  {
   psv = new PHR_Scope_Value(pto->ty(), 79);
   so = PHR_Runtime_Scope::Storage_Options::Direct;
  }
 });
}

void test_def(QString fn, PHR_Callable_Value* pcv)
{
 qDebug() << fn;
 pcv->register_with_name(fn);
}

void test_dfr_call(quint64 arg, PHR_Callable_Value* pcv)
{
 PHR_Expression_Object* pxo = (PHR_Expression_Object*) arg;
 PHR_Channel_Group_Evaluator* ev1 = pxo->run();
 qint32 r1 = ev1->get_result_value_as<qint32>();
 qDebug() << r1;

 pcv->run();
}

void test_tok_call(quint32 arg, PHR_Callable_Value* pcv)
{
 qDebug() << arg;
 pcv->run();
}

void test_call_tok(PHR_Callable_Value* pcv, quint32 arg)
{
 qDebug() << arg;
 pcv->run();
}

void test_void()
{
 qDebug() << "OK";
}

void init_basic_functions(PhaonIR& phr, PHR_Code_Model& pcm,
  PHR_Channel_Group_Table& table, PHR_Symbol_Scope& pss)
{
 init_test_functions(phr, pcm, table, pss);

 PHR_Type_System* type_system = pcm.type_system();
 PHR_Channel_System& pcs = *phr.channel_system();

 PHR_Channel_Semantic_Protocol* lambda = pcs["lambda"];
 PHR_Channel_Semantic_Protocol* result = pcs["result"];
 PHR_Channel_Semantic_Protocol* sigma = pcs["sigma"];

 PHR_Channel_Group g1;
 {
  PHR_Type* ty = type_system->get_type_by_name("u4");
  PHR_Carrier* phc = new PHR_Carrier;
  phc->set_phr_type(ty);
  g1.init_channel(lambda, 1);
  (*g1[lambda])[0] = phc;

  table.init_phaon_function(g1, pss, "prn", 700, &prn);

  g1.clear_all();
 }

 {
  PHR_Type* ty = type_system->get_type_by_name("str");
  PHR_Carrier* phc1 = new PHR_Carrier;
  phc1->set_phr_type(ty);
  PHR_Carrier* phc2 = new PHR_Carrier;
  phc2->set_phr_type(ty);
  g1.init_channel(lambda, 2);
  (*g1[lambda])[0] = phc1;
  (*g1[lambda])[1] = phc2;

  table.init_phaon_function(g1, pss, "test-prss", 700, &test_prss);

  g1.clear_all();
 }

 {
  table.init_phaon_function(g1, pss, "test-void", 700, &test_void);
  g1.clear_all();
 }

 {
  PHR_Type* ty = type_system->get_type_by_name("u4");
  PHR_Carrier* phc1 = new PHR_Carrier;
  phc1->set_phr_type(ty);
  PHR_Carrier* phc2 = new PHR_Carrier;
  phc2->set_phr_type(ty);
  g1.init_channel(lambda, 2);
  (*g1[lambda])[0] = phc1;
  (*g1[lambda])[1] = phc2;
  table.init_phaon_function(g1, pss, "prnn", 700, &prnn);
  g1.clear_all();
 }

 {
  PHR_Type* ty = type_system->get_type_by_name("u8");
  PHR_Carrier* phc1 = new PHR_Carrier;
  phc1->set_phr_type(ty);
  PHR_Carrier* phc2 = new PHR_Carrier;
  phc2->set_phr_type(ty);
  g1.init_channel(lambda, 2);
  (*g1[lambda])[0] = phc1;
  (*g1[lambda])[1] = phc2;
  table.init_phaon_function(g1, pss, "prdn", 700, &prdn);
  g1.clear_all();
 }


 {
  PHR_Type* ty = type_system->get_type_by_name("u8");
  PHR_Carrier* phc1 = new PHR_Carrier;
  phc1->set_phr_type(ty);
  PHR_Carrier* phc2 = new PHR_Carrier;
  phc2->set_phr_type(ty);
  g1.init_channel(lambda, 1);
  g1.init_channel(result, 1);
  (*g1[lambda])[0] = phc1;
  (*g1[result])[0] = phc2;
  table.init_phaon_function(g1, pss, "let_num", 700, &let_num);
  g1.clear_all();
 }

 {
  PHR_Type* ty = type_system->get_type_by_name("u8");
  PHR_Carrier* phc1 = new PHR_Carrier;
  phc1->set_phr_type(ty);
  PHR_Carrier* phc2 = new PHR_Carrier;
  phc2->set_phr_type(ty);
  g1.init_channel(lambda, 2);
  (*g1[lambda])[0] = phc1;
  (*g1[lambda])[1] = phc2;
  table.init_phaon_function(g1, pss, "test-dfr", 700, &test_dfr);
  g1.clear_all();
 }

 {
  PHR_Type* ty1 = type_system->get_type_by_name("PHR_Fn_Doc*");
  PHR_Carrier* phc1 = new PHR_Carrier;
  phc1->set_phr_type(ty1);

  PHR_Type* ty2 = type_system->get_type_by_name("str");
  PHR_Carrier* phc2 = new PHR_Carrier;
  phc2->set_phr_type(ty2);

  g1.init_channel(sigma, 1);
  (*g1[sigma])[0] = phc1;

  g1.init_channel(lambda, 1);
  (*g1[lambda])[0] = phc2;

  table.init_phaon_function(g1, pss, "read-f", 710, &fndoc_read);
  g1.clear_all();
 }

 {
  PHR_Type* ty1 = type_system->get_type_by_name("PHR_Fn_Doc*");
  PHR_Carrier* phc1 = new PHR_Carrier;
  phc1->set_phr_type(ty1);

  PHR_Type* ty2 = type_system->get_type_by_name("str");
  PHR_Carrier* phc2 = new PHR_Carrier;
  phc2->set_phr_type(ty2);

  g1.init_channel(sigma, 1);
  (*g1[sigma])[0] = phc1;

  g1.init_channel(result, 1);
  (*g1[result])[0] = phc2;

  table.init_phaon_function(g1, pss, "test-summary", 610, &fndoc_test_summary);
  g1.clear_all();
 }


 {
  PHR_Type* ty = type_system->get_type_by_name("argvec");
  PHR_Carrier* phc = new PHR_Carrier;
  phc->set_phr_type(ty);
  g1.init_channel(lambda, 1);
  (*g1[lambda])[0] = phc;

  table.init_phaon_function(g1, pss, "if-t-e", 700, &if_t_e);
  table.init_phaon_function(g1, pss, "test-if-then-else", 700, &test_if_then_else);


  g1.clear_all();
 }

 {
  PHR_Type* ty = type_system->get_type_by_name("pcv");
  PHR_Carrier* phc1 = new PHR_Carrier;
  phc1->set_phr_type(ty);
  PHR_Carrier* phc2 = new PHR_Carrier;
  phc2->set_phr_type(ty);
  g1.init_channel(lambda, 2);
  (*g1[lambda])[0] = phc1;
  (*g1[lambda])[1] = phc2;

  table.init_phaon_function(g1, pss, "test-calls", 700, &test_calls);

  g1.clear_all();
 }

 {
  PHR_Type* ty1 = type_system->get_type_by_name("u8");
  PHR_Carrier* phc1 = new PHR_Carrier;
  phc1->set_phr_type(ty1);

  PHR_Type* ty2 = type_system->get_type_by_name("pcv");
  PHR_Carrier* phc2 = new PHR_Carrier;
  phc2->set_phr_type(ty2);
  g1.init_channel(lambda, 2);
  (*g1[lambda])[0] = phc1;
  (*g1[lambda])[1] = phc2;
  table.init_phaon_function(g1, pss, "test-dfr-call", 700, &test_dfr_call);
  g1.clear_all();
 }

 {
  PHR_Type* ty = type_system->get_type_by_name("pcv");
  PHR_Carrier* phc = new PHR_Carrier;
  phc->set_phr_type(ty);
  g1.init_channel(lambda, 1);
  (*g1[lambda])[0] = phc;

  table.init_phaon_function(g1, pss, "test-call", 700, &test_call);

  g1.clear_all();
 }

 {
  PHR_Type* ty = type_system->get_type_by_name("pcv");
  PHR_Carrier* phc = new PHR_Carrier;
  phc->set_phr_type(ty);
  g1.init_channel(lambda, 1);
  (*g1[lambda])[0] = phc;

  table.init_phaon_function(g1, pss, "test-pass-call", 700, &test_pass_call);

  g1.clear_all();
 }

 {
  PHR_Type* ty1 = type_system->get_type_by_name("str");
  PHR_Carrier* phc1 = new PHR_Carrier;
  phc1->set_phr_type(ty1);

  PHR_Type* ty2 = type_system->get_type_by_name("pcv");
  PHR_Carrier* phc2 = new PHR_Carrier;
  phc2->set_phr_type(ty2);
  g1.init_channel(lambda, 2);
  (*g1[lambda])[0] = phc1;
  (*g1[lambda])[1] = phc2;

  table.init_phaon_function(g1, pss, "test-def", 700, &test_def);

  g1.clear_all();
 }

 {
  PHR_Type* ty = type_system->get_type_by_name("str");
  PHR_Carrier* phc1 = new PHR_Carrier;
  phc1->set_phr_type(ty);
  g1.init_channel(lambda, 1);
  (*g1[lambda])[0] = phc1;
  table.init_phaon_function(g1, pss, "prs", 700, &prs);
  g1.clear_all();
 }

 {
  PHR_Type* ty = type_system->get_type_by_name("argvec");
  PHR_Carrier* phc = new PHR_Carrier;
  phc->set_phr_type(ty);
  g1.init_channel(lambda, 1);
  (*g1[lambda])[0] = phc;

  table.init_phaon_function(g1, pss, "test-arg-vec-calls", 700, &test_arg_vec_calls);

  g1.clear_all();
 }

 {
  PHR_Type* ty1 = type_system->get_type_by_name("u4");
  PHR_Carrier* phc1 = new PHR_Carrier;
  phc1->set_phr_type(ty1);

  PHR_Type* ty2 = type_system->get_type_by_name("pcv");
  PHR_Carrier* phc2 = new PHR_Carrier;
  phc2->set_phr_type(ty2);

  g1.init_channel(lambda, 2);
  (*g1[lambda])[0] = phc1;
  (*g1[lambda])[1] = phc2;

  table.init_phaon_function(g1, pss, "test-tok-call", 700, &test_tok_call);

  g1.clear_all();
 }


 {
  PHR_Type* ty1 = type_system->get_type_by_name("pcv");
  PHR_Carrier* phc1 = new PHR_Carrier;
  phc1->set_phr_type(ty1);

  PHR_Type* ty2 = type_system->get_type_by_name("u4");
  PHR_Carrier* phc2 = new PHR_Carrier;
  phc2->set_phr_type(ty2);

  g1.init_channel(lambda, 2);
  (*g1[lambda])[0] = phc1;
  (*g1[lambda])[1] = phc2;

  table.init_phaon_function(g1, pss, "test-call-tok", 700, &test_call_tok);

  g1.clear_all();
 }

 {
  PHR_Type* ty1 = type_system->get_type_by_name("str");
  PHR_Carrier* phc1 = new PHR_Carrier;
  phc1->set_phr_type(ty1);

  PHR_Type* ty2 = type_system->get_type_by_name("u8");
  PHR_Carrier* phc2 = new PHR_Carrier;
  phc2->set_phr_type(ty2);

  g1.init_channel(lambda, 1);
  (*g1[lambda])[0] = phc1;

  g1.init_channel(result, 1);
  (*g1[result])[0] = phc2;

  table.init_phaon_function(g1, pss, "envv", 700, &envv);

  g1.clear_all();
 }
}

