
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include <QDebug>

#include "textio.h"
USING_KANS(TextIO)


#include "chasm-lib/chasm/chasm-runtime.h"
//#include "chasm-lib/chasm/chasm-call-package.h"

#include "chasm-vm/chasm-vm.h"
#include "chasm-runtime-bridge/chasm-runtime-bridge.h"
#include "chasm-procedure-table/chasm-procedure-table.h"


void testqvar(QVariant arg1, r8 arg2, u2 arg3)
{
 qDebug() << "arg1 = " << arg1;
 qDebug() << "arg2 = " << arg2;
 qDebug() << "arg3 = " << arg3;
}

void prn(u1 arg)
{
 qDebug() << "arg = " << arg;
}

//u4 add(u4 arg1, u4 arg2)
//{
// return arg1 + arg2;
//}

void prn2(u1 arg1, u1 arg2)
{
 qDebug() << "arg1 = " << arg1;
 qDebug() << "arg2 = " << arg2;
}

u4 add(u4 arg1, u4 arg2)
{
 qDebug() << "arg1 = " << arg1;
 qDebug() << "arg2 = " << arg2;
 qDebug() << "arg1 + arg2 = " << arg1 + arg2;
 return arg1 + arg2;
}


int main(int argc, char *argv[])
{
 Chasm_Runtime csr;
 Chasm_Runtime_Bridge crb(&csr);
 Chasm_Procedure_Table cpt(&csr);
 crb.set_proctable(&cpt);

// cpt.register_s0(testqvar, @300762);
 cpt.register_s0(prn, @1001);
 cpt.register_s0(prn2, @20044);

// cpt.register_procedure_s0_r1("+",
//   (_minimal_fn_s0_r1_type) &add, "@20444");

 cpt.register_procedure_s0("+",
   (_minimal_fn_s0_type) &add, "@20444");

//  cpt.register_procedure_s0("+",
//    (_minimal_fn_s0_type) &prn2, "@20044");

 Chasm_VM csvm(&crb);

//? csvm.gen_source_proc_name();

// csvm.load_program(DEMO_CVM_FOLDER "/t1/t1.cvm");
 csvm.load_program(DEMO_CVM_FOLDER "/t1/t1.cr.chvm");

//?
 csvm.run_current_source_proc_name();
}


int main1(int argc, char *argv[])
{
 Chasm_Runtime csr;
 Chasm_Runtime_Bridge crb(&csr);
 Chasm_Procedure_Table cpt(&csr);
 crb.set_proctable(&cpt);

 cpt.register_s0(testqvar, @300762);

 Chasm_VM csm(&crb);
 csm.gen_source_proc_name();
 csm.load_program(DEMO_CVM_FOLDER "/t1/t1.cvm");
 csm.run_current_source_proc_name();
}

