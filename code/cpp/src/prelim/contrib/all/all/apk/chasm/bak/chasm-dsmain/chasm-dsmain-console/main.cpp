
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include <QDebug>

#include "textio.h"
USING_KANS(TextIO)


#include "chasm/chasm-runtime.h"
//#include "chasm-lib/chasm/chasm-call-package.h"

#include "chasm-vm/chasm-vm.h"
#include "chasm-runtime-bridge/chasm-runtime-bridge.h"
#include "chasm-runtime-bridge/chasm-runtime-eval.h"


#include "chasm-dsmain/chasm-dsmain.h"
#include "chasm-dsmain-model/chasm-dsmain-model.h"

#include "dsmain/dataset-environment.h"
USING_KANS(DSM)

#include "get-cmdl.h"
USING_KANS(Util)


int main(int argc, char *argv[])
{
 QStringList cmds = get_cmdl(argc, argv);

 Chasm_Runtime csr;
 Chasm_Runtime_Bridge crb(&csr);
 Chasm_Runtime_Eval cre(&csr);
 Chasm_Procedure_Table cpt(&csr);

 crb.set_proctable(&cpt);
 cre.set_proctable(&cpt);

 Chasm_DSMain_Model cdm(&cpt);
 cdm.register_procedures();

// Dataset_Environment dsenv({});

 Dataset_Environment* dsenv;

 {
  //QVector<Chasm_Value_Expression> cvxs = ".qsl/;.u4/45;$.23;;;a $$;string;"_cvx;
  QVector<Chasm_Value_Expression> cvxs =
    cpt.parse_expressions(QString(".qsl/%1;.&/ctg;.u1/%2;").arg(cmds.join(":.")).arg(argc));

  Chasm_Carrier cc = cre.call_s0("coco:retvalue")("Dataset_Environment::_new",
    cvxs);


//  Chasm_Value_Expression cvx(".u4/789");

//  Chasm_Carrier cc = cre.call_s0("coco:retvalue")("Dataset_Environment::_new",
//    cpt.type_object_ref(), &qsl);

//  QStringList qsl;

//  Chasm_Carrier cc = cre.call_s0("Dataset_Environment::_new",
//    cpt.type_object_ref(), &qsl);

  dsenv = cc.value<Dataset_Environment*>();


 }

 Chasm_Carrier cc = cre.call_s1(dsenv, "Dataset_Environment::check_setup_only");

 // bool b = cc.value<bool>();

 qDebug() << cc.value<bool>();

// crb.push_carrier_deque();


//// Chasm_VM cvm(&crb);

// void* holder = &dsenv;


// crb.new_call_package();

// crb.add_new_channel("sigma");
// crb.load_type_ptr();
// crb.gen_carrier(&holder);
// crb.add_carriers();
// crb.reset_carrier_deque();
// crb.add_new_channel("retvalue");
// crb.load_type_u1();
// crb.gen_carrier_tvr("0");
// crb.add_carriers();
// crb.run_eval("Dataset_Environment::check_setup_only");
// Chasm_Carrier cc = crb.last_carrier();
// bool b = cc.value<bool>();

// qDebug() << b;
// crb.
// Chasm_DSMain cdsm;
// csm.gen_source_proc_name();
// csm.load_program(DEMO_CSM_FOLDER "/demo/t1.csm");
// csm.run_current_source_proc_name();

 return 0;
}


