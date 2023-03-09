
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include <QDebug>

#include <QDirIterator>

#include "textio.h"
USING_KANS(TextIO)


QStringList returns{{"void", "u1", "u2", "QString", "u4", "QByteArray", "r8", "QVariant", "n8", "void*"}};

QString generate_function_code(u1 retc, u2 key, QString sc, u1 ac)
{
 QString ret = returns[retc];
 QString retv;
 if(retc > 0) retv = ret + "& retv, ";

 QString more_args;

 if(ac > 0)
 {
  for(u1 aa = 1; aa <= ac; ++aa)
  {
   more_args += QString("n8 arg%1, ").arg(aa);
  }
 }
//   more_args += "n8 arg1, ";
// if(ac > 1)
//   more_args += "n8 arg2, ";
// if(ac > 2)
//   more_args += "n8 arg3, ";



 QString result = (ac > 0)? QString("void _f_%1%2_(%3%4minimal_fn_%5_re%1_type fn){\n  ")
   .arg(retc).arg(key, ac, 10, QLatin1Char('0')).arg(retv).arg(more_args).arg(sc)
   :  QString("void _f_%1_(%2%3minimal_fn_%4_re%1_type fn){\n  ")
                            .arg(retc).arg(retv).arg(more_args).arg(sc);

 u1 akey = 0;

 // types[0] is return ...  less than 3 others might be used (if ac < 3)
 static QString types [4] = {ret,{},{},{}};

 if(ac > 0)
 {
  static u2 exps[3] {1, 10, 100};
  u2 f = exps[ac - 1];
  for(u1 i = 1, factor = f; i <= ac; ++i, factor /= 10)
  {
   akey = key/factor;
   key -= akey*factor;
   switch(akey)
   {
   case 0: // ref
    types[i] = "n8&";
    result += QString("n8& a%1=*(n8*)arg%1;").arg(i);
    break;

    // // for now treat 5 and 9 like a n8
   case 9: akey = 8; // fallthrough
   case 1: case 2: case 4: case 8:
    types[i] = QString("%1%2").arg(akey == 8?'n':'u').arg(akey);
    result += QString("%1 a%2=*(%1*)arg%2;").arg(types[i]).arg(i);
    break;

   case 3: // QString
    types[i] = "QString";
    result += QString("QString a%1=*(QString*)arg%1;").arg(i);
    break;

   case 5: // QByteArray
    types[i] = "QByteArray";
    result += QString("QByteArray a%1=*(QByteArray*)arg%1;").arg(i);
    break;

   case 6: // double
    types[i] = "r8";
    result += QString("r8 a%1=*(r8*)arg%1;").arg(i);
    break;

   case 7: // QVariant
    types[i] = "QVariant";
    result += QString("QVariant a%1 = *(QVariant*)arg%1;").arg(i);
    break;

   }
  }
 }

 if(retc > 0) result += "retv=";

 switch(ac)
 {
 case 0: result += QString("((%1(*)()) fn)();}\n\n")
    .arg(ret); break;

 case 1: result += QString("((%1(*)(%2)) fn)(a1);}\n\n")
    .arg(ret).arg(types[1]); break;

 case 2: result += QString("((%1(*)(%2,%3)) fn)(a1,a2);}\n\n")
    .arg(ret).arg(types[1]).arg(types[2]); break;

 case 3: result += QString("((%1(*)(%2,%3,%4)) fn)(a1,a2,a3);}\n\n")
    .arg(ret).arg(types[1]).arg(types[2]).arg(types[3]); break;
 }


 return result;
}

int main(int argc, char *argv[])
{
 /*
 0 = ref
 1 = u1
 2 = u2
 3 = QString
 4 = u4
 5 = QByteArray
 6 = dbl
 7 = QVariant
 8 = n8
 9 = pointer
 */

// u1 ac = 3;

 for(u1 ac = 0; ac <= 3; ++ac)
 {
  static u2 exps[4] {1, 10, 100, 1000};

  u2 arsize = exps[ac];

  for(u1 i = 0; i < 10; ++i)
  {
   QString ret = returns[i];
   QString retv, rsym;

   // //  concisely initialize two strings.  A bit cute.
   if(i > 0)
     retv = QString("%1& %2").arg(ret).arg(rsym = "retv, ");


   QString s0_X_reX_ch_eval_file = QString(ROOT_FOLDER "/dev/consoles/fns/s0/a%1/ch-eval-s0_%1_re%2.cpp").arg(ac).arg(i);
   QString s0_X_reX_ch_eval_text = (ac == 0)? "" : R"(

Chasm_Channel* lambda = ccp->channel("lambda");
if(!lambda)
  return;
)";

   if(i > 0)
     s0_X_reX_ch_eval_text += R"(
Chasm_Channel* resultch = ccp->channel("result");
if(!resultch)
  return;
)";

   QString pasn8s;
   if(ac > 0)
   {
    for(int aa = 1; aa <= ac; ++aa)
      pasn8s += QString(", lambda->pasn8(%1)").arg(aa);
   }

   if(i == 0)
   {
    s0_X_reX_ch_eval_text += QString(R"(
run_s0_%1_re0(fncode, (minimal_fn_s0_re0_type) fn%2);
)").arg(ac).arg(pasn8s);
   }
   else
   {
    s0_X_reX_ch_eval_text += QString(R"(
Chasm_Carrier cc = resultch->first_carrier();

%1%2 rr = %3cc.value%4<%1>();
run_s0_%5_re%6(fncode, (minimal_fn_s0_re%6_type) fn,
  rr%7);

if(rcar)
  rcar->set_value%8(rr);
)").arg(ret).arg( (i == 3 || i == 5 || i == 7)?"&":"")
   .arg("")  //.arg((i == 3 || i == 5 || i == 7)?"*("+ret+"*)":"")
   .arg((i == 3 || i == 5 || i == 7)?"_as":"")
   .arg(ac)
   .arg(i).arg(pasn8s)
   .arg((i == 3 || i == 5 || i == 7)?"_as<"+ret+">":
     //(i==9)?"":(i==0)?"*":
     ""

    )
    ;
   }
   save_file(s0_X_reX_ch_eval_file, s0_X_reX_ch_eval_text);

   QString s0_X_reX_file = QString(ROOT_FOLDER "/dev/consoles/fns/s0/a%1/run-s0_%1_re%2.cpp").arg(ac).arg(i);
   QString fn_array_reX_file = QString(ROOT_FOLDER "/dev/consoles/fns/s0/a%1/fn-array-s0_%1_re%2.cpp").arg(ac).arg(i);

   QString fn_array_reX_text;

   QString n8argtext;
   if(ac > 0)
   {
    for(u1 aa = 1; aa <= ac; ++aa)
    {
     n8argtext += QString("n8 arg%1, ").arg(aa);
    }
   }

   QString s0_X_reX_text = QString(R"(


#ifndef SEEN_DEFS_S0_%4_RE%2
#define SEEN_DEFS_S0_%4_RE%2

typedef %1(*minimal_fn_s0_re%2_type)();
typedef void(*run_s0_%4_re%2_type)(%3%6minimal_fn_s0_re%2_type fn);
typedef run_s0_%4_re%2_type s0_%4_re%2_dispatch_array [%5];

#endif //  SEEN_DEFS_S0_%4_RE%2

#ifdef FULL_INCLUDE

#include "fn-array-s0_%4_re%2.cpp"

s0_%4_re%2_dispatch_array* init_s0_%4_re%2_dispatch_array()
{
 s0_%4_re%2_dispatch_array* result = (s0_%4_re%2_dispatch_array*) new run_s0_%4_re%2_type[%5];
 )").arg(ret).arg(i).arg(retv).arg(ac).arg(arsize).arg(n8argtext);

   for(u2 j = 0; j < arsize; ++j)
   {
    if(ac > 0)
      s0_X_reX_text += QString("\n (*result)[%1] = &_f_%2%3_;").arg(j).arg(i).arg(j, ac, 10, QLatin1Char('0'));
    else
      s0_X_reX_text += QString("\n (*result)[%1] = &_f_%2_;").arg(j).arg(i);
   }

   QString atext;
   QString natext;
   if(ac > 0)
   {
    for(u1 aa = 1; aa <= ac; ++aa)
    {
     natext += QString("n8 a%1%2").arg(aa).arg(aa < ac? ", " : "");
     atext += QString("a%1,").arg(aa);
    }
   }

   if( (ac > 0) )
     s0_X_reX_text += QString(R"(
}

void run_s0_%1_re%2(u4 code, minimal_fn_s0_re%2_type fn, %3%4))")
   .arg(ac).arg(i).arg(retv).arg(natext);

   else if( (i > 0) )
     s0_X_reX_text += QString(R"(
}

void run_s0_%1_re%2(u4 code, minimal_fn_s0_re%2_type fn, %3))")
   .arg(ac).arg(i).arg(retv.left(retv.size() - 2));

   else
    s0_X_reX_text += QString(R"(
}

void run_s0_%1_re%2(u4 code, minimal_fn_s0_re%2_type fn))")
  .arg(ac).arg(i); // // here ac = 0 and i = 0 always but keep the substitutions for clarity ...

   s0_X_reX_text += QString(R"(
{
 code %= %1;
 static s0_%2_re%3_dispatch_array* dispatch_array = init_s0_%2_re%3_dispatch_array();
 run_s0_%2_re%3_type f = (*dispatch_array)[code];
 f(%4%5fn);
}

#endif //def FULL_INCLUDE
)").arg(arsize).arg(ac).arg(i).arg(rsym).arg(atext); // .arg(ac).arg(arsize * 10).arg(atext);

   save_file(s0_X_reX_file, s0_X_reX_text);

   for(int j = 0; j < arsize; ++j)
     fn_array_reX_text += generate_function_code(i, j, "s0", ac);
   save_file(fn_array_reX_file, fn_array_reX_text);
  }

 }
 return 0;
}
