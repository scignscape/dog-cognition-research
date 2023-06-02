
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "chasm-runtime-eval.h"

#include "chasm-lib/chasm/chasm-runtime.h"
#include "chasm-lib/chasm/chasm-call-package.h"
#include "chasm-lib/chasm/types/chasm-type-object.h"

#include "chasm-procedure-table/chasm-procedure-table.h"

#include "csm-ghost-scope.h"

#include <QString>
#include <QVariant>
#include <QByteArray>

#include <QUrl>

#include <QPoint>

#include <QRegularExpression>


Chasm_Runtime_Eval::Chasm_Runtime_Eval(Chasm_Runtime* csr)
  :  csr_(csr), proctable_(nullptr)
{
 const QVector<Chasm_Type_Object*>& pto = *csr_->pretype_type_objects();

// type_object_ref_ = pto[0];
// type_object_u1_ = pto[1];
// type_object_u2_ = pto[2];
// type_object_QString_ = pto[3];
// type_object_u4_ = pto[4];
// type_object_QByteArray_ = pto[5];
// type_object_r8_ = pto[6];
// type_object_QVariant_ = pto[7];
// type_object_n8_ = pto[8];
// type_object_ptr_ = pto[9];
}


Chasm_Carrier Chasm_Runtime_Eval::_call_s0(QString name)
{
 _call_s0(name, "retvalue", {});
}

Chasm_Carrier Chasm_Runtime_Eval::call_s0(QString name, QString args_rep)
{
 //? return _call_s0(name, "retvalue", args_rep);
}

Chasm_Carrier Chasm_Runtime_Eval::_call_s0(QString name, QString ret_channel_name, QVector<void*> args)
{
 _minimal_fn_s0_type fn = nullptr;
 _minimal_fn_s1_type sfn = nullptr;

 CFC_Pair cfc = proctable_->find_procedure(name, fn, sfn);

 if(cfc.first.invalid())
   return {};

 Chasm_Call_Package* ccp = csr_->new_call_package();

 if(cfc.first.arg_count > 0)
 {
  ccp->add_new_channel("lambda");

  for(u1 a, u = 0; a < cfc.first.arg_count; ++a, u += 2)
  {
   Chasm_Type_Object* cto = (Chasm_Type_Object*) args[u];
   Chasm_Carrier cc = csr_->gen_carrier(cto->get_pretype_code()).take_value(args[u + 1]);
   ccp->add_carrier(cc);
  }
 }

 ccp->add_new_channel(ret_channel_name);
 Chasm_Carrier rcc = csr_->gen_carrier(cfc.first.return_code);
 ccp->add_carrier(rcc);

 if(fn)
 {
  csr_->evaluate(ccp, cfc, fn, &rcc);
 }

 return rcc;
}

// Chasm_Carrier Chasm_Runtime_Eval::_call_s0(QString name, QString ret_channel_name, QString args_rep)

Chasm_Carrier Chasm_Runtime_Eval::_call_s01(QString name, QString ret_channel_name,
  QVector<Chasm_Value_Expression> args)
{
 _minimal_fn_s0_type fn = nullptr;
 _minimal_fn_s1_type sfn = nullptr;

 //Chasm_Function_Code
 CFC_Pair cfc = proctable_->find_procedure(name, fn, sfn);

 if(cfc.first.invalid())
   return {};

 Chasm_Call_Package* ccp = csr_->new_call_package();

 ccp->add_new_channel(ret_channel_name);
 Chasm_Carrier rcc = csr_->gen_carrier(cfc.first.return_code);
 ccp->add_carrier(rcc);

 if(cfc.first.arg_count == 0)
 {
  if(fn)
    csr_->evaluate(ccp, cfc, fn, &rcc);
  else if(sfn)
    csr_->evaluate(ccp, cfc, sfn, &rcc);
  return rcc;
 }

 ccp->add_new_channel("lambda");

 u1 count = qMin<u1>(cfc.first.arg_count, args.size());

 Chasm_Carrier ccs[count];

 for(u1 u = 0; u < count; ++u)
 {
  Chasm_Value_Expression cvx = args[u];
  init_carrier(ccs[u], cvx);
  ccp->add_carrier(ccs[u]);
 }

 if(fn)
 {
  csr_->evaluate(ccp, cfc, fn, &rcc);
 }

 else if(sfn)
 {
  csr_->evaluate(ccp, cfc, sfn, &rcc);
 }

 //ccp->add_carriers({ccs});

 return rcc;
}

void Chasm_Runtime_Eval::init_carrier(Chasm_Carrier& cc, Chasm_Value_Expression cvx)
{
 Chasm_Type_Object* cto = cvx.get_type_object();

 if(cto)
 {
  if(cto->name() == "QStringList&")
  {
   QString* qs = cvx.get_qstring();
   QStringList* qsl = new QStringList( qs->split(":.") );
   for(QString& qs1 : (*qsl))
   {
    qs1.replace(QRegularExpression(":\\$[.](?!=[.])"), ":.");
    qs1.replace(":$.", ":$");
   }
   cc.set_type_flag(0);
   cc.take_value(qsl);
   return;
  }
 }
 u1 pc = cto? cto->get_pretype_code() : cvx.get_hint_pretype_code();

 switch (pc)
 {
 case 1:
  {
   u1 u = cvx.get_u1();
   cc.set_type_flag(1);
   cc.take_value(&u);
  }
  break;

 case 3:
  {
   QString* qs = cvx.get_qstring();
   cc.set_type_flag(3);
   cc.take_value(qs);
  }
  break;
 }
}

Chasm_Carrier Chasm_Runtime_Eval::call_s1(void* obj, QString name)
{
 _minimal_fn_s0_type fn = nullptr;
 _minimal_fn_s1_type sfn = nullptr;

 CFC_Pair cfc = proctable_->find_procedure(name, fn, sfn);

 if(cfc.first.invalid())
   return {};
 //csr

 Chasm_Call_Package* ccp = csr_->new_call_package();
 ccp->add_new_channel("sigma");
 Chasm_Carrier scc = csr_->gen_carrier(9).take_value(&obj);
 ccp->add_carrier(scc);

 ccp->add_new_channel("retvalue");
 Chasm_Carrier rcc = csr_->gen_carrier(cfc.first.return_code);
 ccp->add_carrier(rcc);

 if(sfn)
 {
  csr_->evaluate(ccp, cfc, sfn, &rcc);
 }

 return rcc;
}
