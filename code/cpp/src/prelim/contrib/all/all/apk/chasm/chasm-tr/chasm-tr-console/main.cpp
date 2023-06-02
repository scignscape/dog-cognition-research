
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
#include "chasm-tr/chvm/eval/channel-package-runner.h"


USING_AQNS(Chasm_TR)

//#include "ch

int main(int argc, char *argv[])
{

 ChTR_Document chrd(ROOT_FOLDER "/../chtr/t1/t1.cr");

 chrd.parse();

 ChVM_Code_Generator ccg(chrd.graph());

 QString chvm;
 ccg.graph_to_chvm(chvm);

 chrd.save_file("..chvm", chvm);

 ChVM_Channel_Package_Runner ccr();


 return 0;

 //?chrd.graph_to_chvm();

}
