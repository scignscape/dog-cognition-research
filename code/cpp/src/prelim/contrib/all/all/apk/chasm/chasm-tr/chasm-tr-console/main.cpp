
#include "textio.h"

USING_KANS(TextIO)


/*

<! <x>[retval] <\ [proc](pr)  [lambda](<*>[retval] <\ [proc](add) [lambda](5 7) ) !>

.,
load-pst $ /test ;.
,.

,x int

.<x>[r] [p](pr)  [l](<*>[r] [p](add) [l](5 7) )

.[p](unless) [l]($1 $2) = .[p](if) [l](<*>[r] [l](;1) ;2)


[p] = %
[r] = @
[l] = \
[m] = &
[s] =
[e] =
[c] = @.

.<x>@ %(pr) \(<*>@ %(add) \(5 7) )


.&(unless) \($1 $2) = .%(if) \(<*>@ \(;1) ;2)


.<x>@. %(test) \+(this)


.<x>[c]

 */

#include "chasm-tr-parser/chtr-document.h"

#include "chasm-tr/chvm/chvm-code-generator.h"
//?#include "chasm-tr/chvm/eval/channel-package-runner.h"


USING_AQNS(Chasm_TR)

//#include "ch




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

void prn(u1 arg1)
{
 qDebug() << "arg1 = " << arg1;
}


int main(int argc, char *argv[])
{
 Chasm_Runtime csr;
 Chasm_Runtime_Bridge crb(&csr);
 Chasm_Procedure_Table cpt(&csr);
 crb.set_proctable(&cpt);

 cpt.register_s0(testqvar, @300762);
 cpt.register_s0(prn, @1001);

 Chasm_VM csm(&crb);
 csm.gen_source_proc_name();
//? csm.load_program(DEMO_CVM_FOLDER "/t1/t1.cvm");
 csm.load_program(DEMO_CVM_FOLDER "/t1/t1.cr.chvm");
 csm.run_current_source_proc_name();
}



int main1(int argc, char *argv[])
{

 ChTR_Document chrd(ROOT_FOLDER "/../chtr/t1/t1.cr");

 chrd.parse();

 ChVM_Code_Generator ccg(chrd.graph());

 QString chvm;
 ccg.graph_to_chvm(chvm);

 chrd.save_file("..chvm", chvm);

//? ChVM_Channel_Package_Runner ccr();


 return 0;

 //?chrd.graph_to_chvm();

}
