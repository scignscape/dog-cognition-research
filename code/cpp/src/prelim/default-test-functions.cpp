
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

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

quint32 test_find(QString instr, QString outstr)
{
 return outstr.indexOf(instr);
}



void test_arg_vec_str(quint64 args_ptr)
{
 QVector<quint64>& args = *(QVector<quint64>*)(args_ptr);

 for(quint64 qui: args)
 {
  QString** qs = (QString**) qui;
  qDebug() << **qs;
 }
}

quint32 test_i_s(QString s1)
{
 qDebug() << "s1 = " << s1;
 qDebug() << "returning: 66";
 return 66;
}

void test_0_ss(QString s1, QString s2)
{
 qDebug() << "s1 = " << s1 << "s2 = " << s2;
}

void test_0_s(QString s1)
{
 qDebug() << "s1 = " << s1;
}

int test_i_ss(QString s1, QString s2)
{
 qDebug() << "s1 = " << s1 << "s2 = " << s2;
 qDebug() << "returning: 66";
 return 66;
}

void fndoc_test_0_S10_s(PHR_Fn_Doc* fnd, QString s1)
{
 qDebug() << "s1 = " << s1;
}

void fndoc_test_0_S10(PHR_Fn_Doc* fnd)
{
 qDebug() << "ok";
}

QString n_to_s(quint32 arg)
{
 return QString::number(arg);
}

QString test_s_s(QString s1)
{
 qDebug() << "s1 = " << s1;
 qDebug() << "returning: s_s";
 return "s_s";
}

QString test_s_ss(QString s1, QString s2)
{
 qDebug() << "s1 = " << s1 << "s2 = " << s2;
 qDebug() << "returning: s_ss";
 return "s_ss";
}

void init_test_functions(PhaonIR& phr, PHR_Code_Model& pcm,
  PHR_Channel_Group_Table& table, PHR_Symbol_Scope& pss)
{
 PHR_Type_System* type_system = pcm.type_system();
 PHR_Channel_System& pcs = *phr.channel_system();

 PHR_Channel_Semantic_Protocol* lambda = pcs["lambda"];
 PHR_Channel_Semantic_Protocol* result = pcs["result"];
 PHR_Channel_Semantic_Protocol* sigma = pcs["sigma"];

 PHR_Channel_Group g1;
 {
  PHR_Type* ty = type_system->get_type_by_name("str");
  PHR_Carrier* phc1 = new PHR_Carrier;
  phc1->set_phr_type(ty);
  PHR_Carrier* phc2 = new PHR_Carrier;
  phc2->set_phr_type(ty);
  g1.init_channel(lambda, 2);
  (*g1[lambda])[0] = phc1;
  (*g1[lambda])[1] = phc2;

  PHR_Type* rty = type_system->get_type_by_name("u4");
  PHR_Carrier* rphc = new PHR_Carrier;
  rphc->set_phr_type(rty);
  g1.init_channel(result, 1);
  (*g1[result])[0] = rphc;

  table.init_phaon_function(g1, pss, "test-i-ss", 700, &test_i_ss);

  g1.clear_all();
 }

 {
  PHR_Type* ty = type_system->get_type_by_name("str");
  PHR_Carrier* phc1 = new PHR_Carrier;
  phc1->set_phr_type(ty);
  g1.init_channel(lambda, 1);
  (*g1[lambda])[0] = phc1;

  PHR_Type* rty = type_system->get_type_by_name("u4");
  PHR_Carrier* rphc = new PHR_Carrier;
  rphc->set_phr_type(rty);
  g1.init_channel(result, 1);
  (*g1[result])[0] = rphc;

  table.init_phaon_function(g1, pss, "test-i-s", 700, &test_i_s);

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

  table.init_phaon_function(g1, pss, "test-0-ss", 700, &test_0_ss);

  g1.clear_all();
 }

 {
  PHR_Type* ty = type_system->get_type_by_name("str");
  PHR_Carrier* phc = new PHR_Carrier;
  phc->set_phr_type(ty);
  g1.init_channel(lambda, 1);
  (*g1[lambda])[0] = phc;

  table.init_phaon_function(g1, pss, "test-0-s", 700, &test_0_s);

  g1.clear_all();
 }

 {
  PHR_Type* ty1 = type_system->get_type_by_name("PHR_Fn_Doc*");
  PHR_Carrier* phc1 = new PHR_Carrier;
  phc1->set_phr_type(ty1);

  g1.init_channel(sigma, 1);
  (*g1[sigma])[0] = phc1;

  table.init_phaon_function(g1, pss, "test-0-S10", 710, &fndoc_test_0_S10);

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

  table.init_phaon_function(g1, pss, "test-0-S10-s", 710, &fndoc_test_0_S10_s);

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

  PHR_Carrier* rphc = new PHR_Carrier;
  rphc->set_phr_type(ty);
  g1.init_channel(result, 1);
  (*g1[result])[0] = rphc;

  table.init_phaon_function(g1, pss, "test-s-ss", 600, &test_s_ss);

  g1.clear_all();
 }

 {
  PHR_Type* ty = type_system->get_type_by_name("str");
  PHR_Carrier* phc1 = new PHR_Carrier;
  phc1->set_phr_type(ty);
  PHR_Carrier* phc2 = new PHR_Carrier;
  phc2->set_phr_type(ty);
  g1.init_channel(lambda, 1);
  (*g1[lambda])[0] = phc1;

  PHR_Carrier* rphc = new PHR_Carrier;
  rphc->set_phr_type(ty);
  g1.init_channel(result, 1);
  (*g1[result])[0] = rphc;

  table.init_phaon_function(g1, pss, "test-s-s", 600, &test_s_s);

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

  PHR_Type* rty = type_system->get_type_by_name("u4");
  PHR_Carrier* rphc = new PHR_Carrier;
  rphc->set_phr_type(rty);
  g1.init_channel(result, 1);
  (*g1[result])[0] = rphc;

  table.init_phaon_function(g1, pss, "test-find", 700, &test_find);

  g1.clear_all();
 }

 {
  PHR_Type* ty = type_system->get_type_by_name("u4");
  PHR_Carrier* phc = new PHR_Carrier;
  phc->set_phr_type(ty);
  g1.init_channel(lambda, 1);
  (*g1[lambda])[0] = phc;

  PHR_Type* rty = type_system->get_type_by_name("str");
  PHR_Carrier* rphc = new PHR_Carrier;
  rphc->set_phr_type(rty);
  g1.init_channel(result, 1);
  (*g1[result])[0] = rphc;

  table.init_phaon_function(g1, pss, "n-to-s", 600, &n_to_s);

  g1.clear_all();
 }

 {
  PHR_Type* ty = type_system->get_type_by_name("argvec");
  PHR_Carrier* phc = new PHR_Carrier;
  phc->set_phr_type(ty);
  g1.init_channel(lambda, 1);
  (*g1[lambda])[0] = phc;

  table.init_phaon_function(g1, pss, "test-arg-vec-str", 700, &test_arg_vec_str);
  table.init_phaon_function(g1, pss, "prss", 700, &test_arg_vec_str);

  g1.clear_all();
 }
}

