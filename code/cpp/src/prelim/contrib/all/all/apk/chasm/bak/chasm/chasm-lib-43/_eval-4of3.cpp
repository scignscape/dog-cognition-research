
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "chasm-runtime.h"

#include "chasm-call-package.h"
#include "chasm-channel.h"
#include "types/chasm-type-object.h"

//#include "_eval-4of3.h"

#define FULL_INCLUDE
#include "../dev/consoles/fns/run/run-a4of3/run-s01-4of3-re0.cpp"
#include "../dev/consoles/fns/run/run-a4of3/run-s01-4of3-re1.cpp"
#include "../dev/consoles/fns/run/run-a4of3/run-s01-4of3-re2.cpp"
#include "../dev/consoles/fns/run/run-a4of3/run-s01-4of3-re3.cpp"
#include "../dev/consoles/fns/run/run-a4of3/run-s01-4of3-re4.cpp"
#include "../dev/consoles/fns/run/run-a4of3/run-s01-4of3-re5.cpp"
#include "../dev/consoles/fns/run/run-a4of3/run-s01-4of3-re6.cpp"
#include "../dev/consoles/fns/run/run-a4of3/run-s01-4of3-re7.cpp"
#include "../dev/consoles/fns/run/run-a4of3/run-s01-4of3-re8.cpp"
#include "../dev/consoles/fns/run/run-a4of3/run-s01-4of3-re9.cpp"

#include "chasm-runtime.h"

#define INCLUDE_MAP_CODE
 QMap<u2, u2> pretype_patterns_4of3_map {
  #include "../dev/consoles/fns/pretype-patterns-4of3.cpp"
 };
#undef INCLUDE_MAP_CODE// def INCLUDE_MAP_CODE


void _evaluate_4of3_re0(Chasm_Call_Package* ccp, Chasm_Function_Code fncode,
  minimal_fn_s0_re0_type fn, minimal_fn_s1_re0_type sfn)
{
 #include "../dev/consoles/fns/eval/a4of3/ch-eval-s01_4of3_re0.cpp"
}

void _evaluate_4of3_re1(Chasm_Call_Package* ccp, Chasm_Function_Code fncode,
  minimal_fn_s0_re1_type fn, minimal_fn_s1_re1_type sfn, Chasm_Carrier* rcar)
{
 #include "../dev/consoles/fns/eval/a4of3/ch-eval-s01_4of3_re1.cpp"
}

void _evaluate_4of3_re2(Chasm_Call_Package* ccp, Chasm_Function_Code fncode,
  minimal_fn_s0_re2_type fn, minimal_fn_s1_re2_type sfn, Chasm_Carrier* rcar)
{
 #include "../dev/consoles/fns/eval/a4of3/ch-eval-s01_4of3_re2.cpp"
}

void _evaluate_4of3_re3(Chasm_Call_Package* ccp, Chasm_Function_Code fncode,
  minimal_fn_s0_re3_type fn, minimal_fn_s1_re3_type sfn, Chasm_Carrier* rcar)
{
 #include "../dev/consoles/fns/eval/a4of3/ch-eval-s01_4of3_re3.cpp"
}

void _evaluate_4of3_re4(Chasm_Call_Package* ccp, Chasm_Function_Code fncode,
  minimal_fn_s0_re4_type fn, minimal_fn_s1_re4_type sfn, Chasm_Carrier* rcar)
{
 #include "../dev/consoles/fns/eval/a4of3/ch-eval-s01_4of3_re4.cpp"
}

void _evaluate_4of3_re5(Chasm_Call_Package* ccp, Chasm_Function_Code fncode,
  minimal_fn_s0_re5_type fn, minimal_fn_s1_re5_type sfn, Chasm_Carrier* rcar)
{
 #include "../dev/consoles/fns/eval/a4of3/ch-eval-s01_4of3_re5.cpp"
}

void _evaluate_4of3_re6(Chasm_Call_Package* ccp, Chasm_Function_Code fncode,
  minimal_fn_s0_re6_type fn, minimal_fn_s1_re6_type sfn, Chasm_Carrier* rcar)
{
 #include "../dev/consoles/fns/eval/a4of3/ch-eval-s01_4of3_re6.cpp"
}

void _evaluate_4of3_re7(Chasm_Call_Package* ccp, Chasm_Function_Code fncode,
  minimal_fn_s0_re7_type fn, minimal_fn_s1_re7_type sfn, Chasm_Carrier* rcar)
{
 #include "../dev/consoles/fns/eval/a4of3/ch-eval-s01_4of3_re7.cpp"
}

void _evaluate_4of3_re8(Chasm_Call_Package* ccp, Chasm_Function_Code fncode,
  minimal_fn_s0_re8_type fn, minimal_fn_s1_re8_type sfn, Chasm_Carrier* rcar)
{
 #include "../dev/consoles/fns/eval/a4of3/ch-eval-s01_4of3_re8.cpp"
}

void _evaluate_4of3_re9(Chasm_Call_Package* ccp, Chasm_Function_Code fncode,
  minimal_fn_s0_re9_type fn, minimal_fn_s1_re9_type sfn, Chasm_Carrier* rcar)
{
 #include "../dev/consoles/fns/eval/a4of3/ch-eval-s01_4of3_re9.cpp"
}

//template<typename FN_Type>
//void _evaluate_s0_4of3(Chasm_Call_Package* ccp, Chasm_Function_Code fncode,
//  FN_Type fn, Chasm_Carrier* rcar)
//{
// switch (fncode.return_code)
// {
// case 0: _evaluate_4of3_re0(ccp, fncode, (minimal_fn_s0_re0_type) fn, nullptr); break;
// case 1: _evaluate_4of3_re1(ccp, fncode, (minimal_fn_s0_re1_type) fn, nullptr, rcar); break;
// case 2: _evaluate_4of3_re2(ccp, fncode, (minimal_fn_s0_re2_type) fn, nullptr, rcar); break;
// case 3: _evaluate_4of3_re3(ccp, fncode, (minimal_fn_s0_re3_type) fn, nullptr, rcar); break;
// case 4: _evaluate_4of3_re4(ccp, fncode, (minimal_fn_s0_re4_type) fn, nullptr, rcar); break;
// case 5: _evaluate_4of3_re5(ccp, fncode, (minimal_fn_s0_re5_type) fn, nullptr, rcar); break;
// case 6: _evaluate_4of3_re6(ccp, fncode, (minimal_fn_s0_re6_type) fn, nullptr, rcar); break;
// case 7: _evaluate_4of3_re7(ccp, fncode, (minimal_fn_s0_re7_type) fn, nullptr, rcar); break;
// case 8: _evaluate_4of3_re8(ccp, fncode, (minimal_fn_s0_re8_type) fn, nullptr, rcar); break;
// case 9: _evaluate_4of3_re9(ccp, fncode, (minimal_fn_s0_re9_type) fn, nullptr, rcar); break;
// }

//}


//template<typename FN_Type>
void _evaluate_s01_4of3(Chasm_Call_Package* ccp, Chasm_Function_Code fncode,
  minimal_fn_s0_re0_type fn, minimal_fn_s1_re0_type sfn, Chasm_Carrier* rcar)

//                       FN_Type fn, Chasm_Carrier* rcar)
{
 switch (fncode.return_code)
 {
 case 0: _evaluate_4of3_re0(ccp, fncode, (minimal_fn_s0_re0_type) fn, (minimal_fn_s1_re0_type) sfn); break;
 case 1: _evaluate_4of3_re1(ccp, fncode, (minimal_fn_s0_re1_type) fn, (minimal_fn_s1_re1_type) sfn, rcar); break;
 case 2: _evaluate_4of3_re2(ccp, fncode, (minimal_fn_s0_re2_type) fn, (minimal_fn_s1_re2_type) sfn, rcar); break;
 case 3: _evaluate_4of3_re3(ccp, fncode, (minimal_fn_s0_re3_type) fn, (minimal_fn_s1_re3_type) sfn, rcar); break;
 case 4: _evaluate_4of3_re4(ccp, fncode, (minimal_fn_s0_re4_type) fn, (minimal_fn_s1_re4_type) sfn, rcar); break;
 case 5: _evaluate_4of3_re5(ccp, fncode, (minimal_fn_s0_re5_type) fn, (minimal_fn_s1_re5_type) sfn, rcar); break;
 case 6: _evaluate_4of3_re6(ccp, fncode, (minimal_fn_s0_re6_type) fn, (minimal_fn_s1_re6_type) sfn, rcar); break;
 case 7: _evaluate_4of3_re7(ccp, fncode, (minimal_fn_s0_re7_type) fn, (minimal_fn_s1_re7_type) sfn, rcar); break;
 case 8: _evaluate_4of3_re8(ccp, fncode, (minimal_fn_s0_re8_type) fn, (minimal_fn_s1_re8_type) sfn, rcar); break;
 case 9: _evaluate_4of3_re9(ccp, fncode, (minimal_fn_s0_re9_type) fn, (minimal_fn_s1_re9_type) sfn, rcar); break;
 }

}
