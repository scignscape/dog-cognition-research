
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


void testqvar(QVariant arg1, r8 arg2, u2 arg3)
{
 qDebug() << "arg1 = " << arg1;
 qDebug() << "arg2 = " << arg2;
 qDebug() << "arg3 = " << arg3;
}

#define register_s0(proc ,code) register_procedure_s0(#proc, (void(*)()) &proc, #code)

int main(int argc, char *argv[])
{
 Chasm_Runtime csr;
 Chasm_Runtime_Bridge crb(&csr);
 Chasm_Procedure_Table cpt(&csr);

 crb.set_proctable(&cpt);
// crb.register_(testqvar ,300782);

 cpt.register_s0(testqvar, @300762);

 crb.push_carrier_deque();
// Chasm_VM cvm(&crb);


 crb.new_call_package();
 crb.add_new_channel("lambda");

 crb.load_type_QVariant();
 crb.gen_carrier_tvr("int:103");
 crb.load_type_r8();
 crb.gen_carrier_tvr(".12345");
 crb.load_type_u2();
 crb.gen_carrier_tvr("12345");
 crb.add_carriers();

 crb.run_eval("testqvar");

 crb.reset_carrier_deque();

}


//void testqstr(QString arg1, r8 arg2, u2 arg3)
//{
// qDebug() << "arg1 = " << arg1;
// qDebug() << "arg2 = " << arg2;
// qDebug() << "arg3 = " << arg3;
//}

//#define register_s0(proc ,code) register_procedure_s0(#proc, (void(*)()) &proc, #code)

//int main(int argc, char *argv[])
//{
// Chasm_Runtime csr;
// Chasm_Runtime_Bridge crb(&csr);
//// crb.register_(testqvar ,300782);

// crb.register_s0(testqstr, @300362);

// crb.push_carrier_deque();
//// Chasm_VM cvm(&crb);


// crb.new_call_package();
// crb.add_new_channel("lambda");

// QString a1 = "string";
// r8 a2 = .12345;
// u2 a3 = 12345;

// crb.load_type_QString();
// crb.gen_carrier(&a1);
// crb.load_type_r8();
// crb.gen_carrier(&a2);
// crb.load_type_u2();
// crb.gen_carrier(&a3);
// crb.add_carriers();
// crb.reset_carrier_deque();

// crb.run_eval("testqstr");
//}
