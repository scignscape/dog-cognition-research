
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include <QDebug>

#include <QMap>
#include <QTextStream>
#include <QDataStream>

#include <QDirIterator>

#include "textio.h"
USING_KANS(TextIO)


QStringList returns{{"void", "u1", "u2", "QString", "u4", "QByteArray", "r8", "QVariant", "n8", "void*"}};


u2 condense(u2 pretype_pattern)
{
 u2 result = 0;
 for(u2 pow = 1; pow <= pretype_pattern; pow *= 10)
 {
  u1 d = (pretype_pattern / pow) % 10;
  switch(d)
  {
  case 1: case 2: case 4: case 8: case 9:
    result += 8 * pow; break;
  case 6: result += 6 * pow; break;
  default: break;
  }
 }
 return result;
}

void parse_fn_code(u4 cue)
{
 u4 cc = cue;

 u1 st_code, return_type_code, pattern_digits_run;
 u2 distinct_pretype_pattern, arguments_pretype_pattern;

 if(cue >= 10000000)
 {
  st_code = (cue/10000000) - 1;
  cue %= 10000000;
  return_type_code = cue/1000000;
  cue %= 1000000;
  pattern_digits_run = 6;
 }
 else if(cue >= 1000000)
 {
  st_code = (cue/1000000) - 1;
  cue %= 1000000;
  return_type_code = cue/100000;
  cue %= 10000;
  pattern_digits_run = 5;
 }
 else if(cue >= 100000)
 {
  st_code = (cue/100000) - 1;
  cue %= 100000;
  return_type_code = cue/1000;
  cue %= 1000;
  pattern_digits_run = 4;
 }
 else if(cue >= 10000)
 {
  st_code = (cue/10000) - 1;
  cue %= 10000;
  return_type_code = cue/1000;
  cue %= 1000;
  pattern_digits_run = 3;
 }
 else if(cue >= 1000)
 {
  st_code = (cue/1000) - 1;
  cue %= 1000;
  return_type_code = cue/100;
  cue %= 100;
  pattern_digits_run = 2;
 }
 else
 {
  // only valid range 10-29
  return_type_code = cue % 10;
  st_code = (cue / 10) - 1;
  pattern_digits_run = 0;
 }

// else if(cue >= 100)
// {
//  // error?
////  st_code = (cue/100) - 1;
////  cue %= 100;
////  return_type_code = cue/10;
////  cue %= 10;
////  pattern_digits_run = 1;
// }
// else if(cue >= 10)
// {
//  st_code = (cue/10) - 1;
//  return_type_code = cue % 10;
//  pattern_digits_run = 0;
// }
// else
// {
//  // errer?
// }


 u1 distinct_type_count = (st_code & 6) >> 1;
 bool s1 = st_code & 1;

 u1 arg_count = pattern_digits_run - distinct_type_count;

 u4 st_base = 1;
 for(int i = 0; i < distinct_type_count; ++i) st_base *= 10;

 switch (arg_count)
 {
 case 3: arguments_pretype_pattern = cue % 1000; distinct_pretype_pattern = cue / 1000; break;
 //case 23: arguments_type_pattern = cue % 1000; distinct_pretype_pattern = cue / 1000; break;
 case 2: arguments_pretype_pattern = cue % 100; distinct_pretype_pattern = cue / 100; break;
 case 1: arguments_pretype_pattern = cue % 10; distinct_pretype_pattern = cue / 10; break;
 case 0: arguments_pretype_pattern = distinct_pretype_pattern = 0; break;
 }



 u2 dd = ( (st_code + 1) * st_base) + distinct_pretype_pattern;

 qDebug() << "cue: " << cc << ", D: " << dd << ", A: " << arguments_pretype_pattern;
}


QVector<u2>* generate_4_3()
{
 QVector<u2>* result = new QVector<u2>;
 for(int i = 1; i <= 3; ++i)
 {
  for(int j = 1; j <= 3; ++j)
  {
   for(int k = 1; k <= 3; ++k)
   {
    for(int l = 1; l <= 3; ++l)
    {
     u1 same = 0;
     if(i == j) ++same;
     if(i == k) ++same;
     if(i == l) ++same;
     if(j == k) ++same;
     if(j == l) ++same;
     if(k == l) ++same;
     if(same > 1)
       continue;
     u2 caseval = (1000*i) + (100*j) + (10*k) + l;
     (*result) << caseval;
    }
   }
  }
 }
 return result;
}


QVector<u2>* generate_3_3()
{
 QVector<u2>* result = new QVector<u2>;
 for(int i = 1; i <= 3; ++i)
 {
  for(int j = 1; j <= 3; ++j)
  {
   for(int k = 1; k <= 3; ++k)
   {
    u1 same = 0;
    if(i == j) ++same;
    if(i == k) ++same;
    if(j == k) ++same;
    if(same > 1)
      continue;
    u2 caseval = (100*i) + (10*j) + k;
    (*result) << caseval;
   }
  }
 }
 return result;
}



QString arg_text(u1 pretype_pattern, u1 index, QString& st)
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

 //QString type; // [4] = {{},{},{},{}};

 QString result;

 switch(pretype_pattern)
 {
 case 0: // ref
  // types[i] = "n8&";
  st = "n8&";
  result = QString("n8& a%1=*(n8*)arg%1;").arg(index);
  break;

  // // for now treat 9 like a n8
 case 9: pretype_pattern = 8; // fallthrough
 case 1: case 2: case 4: case 8:
  st = QString("%1%2").arg(pretype_pattern == 8?'n':'u').arg(pretype_pattern);
  // types[i] = QString("%1%2").arg(akey == 8?'n':'u').arg(akey);
  result = QString("%1 a%2=*(%1*)arg%2;").arg(st).arg(index);
  break;

 case 3: // QString
  st = "QString";
  result = QString("QString a%1=*(QString*)arg%1;").arg(index);
  break;

 case 5: // QByteArray
  st = "QByteArray";
  result = QString("QByteArray a%1=*(QByteArray*)arg%1;").arg(index);
  break;

 case 6: // double
  st = "r8";
  result = QString("r8 a%1=*(r8*)arg%1;").arg(index);
  break;

 case 7: // QVariant
  st = "QVariant";
  result = QString("QVariant a%1 = *(QVariant*)arg%1;").arg(index);
  break;
 }

 return result;
}

QString generate_function_code(u2 pretype_pattern, u1 ret, u1 number)
{
 u1 case_len = number;
 u4 clexp = 1;
 for(int i = 0; i < case_len; ++i)
 {
  clexp *= 10;
 }

 static QVector<u2>* vec4 = generate_4_3();
 static QVector<u2>* vec3 = generate_3_3();

 QVector<u2>* vec = number == 3? vec3:vec4;

 u1 pretype_pattern_len = 0;
 u4 tplexp = 1;
 while( (tplexp * 10) < pretype_pattern)
 {
  ++pretype_pattern_len;
  tplexp *= 10;
 }

 u4 distinct_pretype_pattern = pretype_pattern % tplexp;

 u2 len = pretype_pattern / tplexp;

 u2 lenexp = len * tplexp * 10;
// for(u1 i = 0; i < len; ++i)
// {
//  lenexp *= 10;
// }

// u1 t1 = (pretype_pattern % 1000) / 100;
// u1 t2 = (pretype_pattern % 100) / 10;
// u1 t3 = pretype_pattern % 10;
// u1 ts [3] = {t1, t2, t3};

 u1 ts [pretype_pattern_len];

 {
  u4 exp = tplexp;
  for(int i = 0; i < pretype_pattern_len; ++i)
  {
   ts[i] = (distinct_pretype_pattern % exp) / (exp / 10);
   exp /= 10;
  }
 }

 QString sig_args;
 QString call_args;

 if(case_len > 0)
 {
  for(int i = 1; i <= case_len; ++i)
  {
   sig_args += QString("n8 arg%1, ").arg(i);
   call_args += QString("a%1,").arg(i);
  }
  call_args.chop(1);
 }

 QString retfull;
 if(ret > 0)
   retfull = QString("%1& retv, ").arg(returns[ret]);

 QString result = QString("void _f_%1_%2_(u4 pattern, %3%4"
   "minimal_fn_s0_re%2_type fn,\n  minimal_fn_s1_re%2_type sfn, void** _this)"
   "\n{\n switch(pattern)\n {\n")
   .arg(pretype_pattern).arg(ret).arg(retfull).arg(sig_args);

 for(u2 case_val : *vec)
 {
//  u1 c1 = (case_val % 10000) / 1000;
//  u1 c2 = (case_val % 1000) / 100;
//  u1 c3 = (case_val % 100) / 10;
//  u1 c4 = case_val % 10;


  u1 cs[case_len];
  {
   u4 exp = clexp;
   for(int i = 0; i < len; ++i)
   {
    cs[i] = (case_val % exp) / (exp / 10);
    exp /= 10;
   }
  }

  u1 cts[case_len];
  for(u1 i = 0; i < case_len; ++i)
  {
   cts[i] = ts[cs[i] - 1];
  }

  QString case_txt = QString(" case %1:\n  {").arg(case_val); //\n  %2\n  %3\n  %4\n}").arg(cc); //.arg(at1).arg(at2).arg(at3);


  QString sig_type_args;

  if(case_len > 0)
  {
   for(u1 i = 0; i < case_len; ++i)
   {
    QString st;
    QString at = arg_text(cts[i], i + 1, st);
    case_txt += at; // QString("%1").arg(at);
    sig_type_args += st + ",";
   }
   sig_type_args.chop(1);
  }

  QString retv = (ret==0)?"":"retv=";
  QString rettext = returns[ret];

  QString call_args;
  if(case_len > 0)
  {
   for(int i = 1; i <= case_len; ++i)
   {
    call_args += QString("a%1,").arg(i);
   }
   call_args.chop(1);
  }


  case_txt += QString(R"(
   auto _sfn = (%1(_min_::*)(%2))(sfn);
   if(_this) %3((_min_*)*_this->*_sfn)(%4);
   else %3((%5(*)(%2))fn)(%4);
  )").arg(rettext).arg(sig_type_args).arg(retv).arg(call_args).arg(rettext);

  case_txt += "} break;\n";

//  QString at1 = arg_text(ct1, 1);
//  QString at2 = arg_text(ct2, 2);
//  QString at3 = arg_text(ct3, 3);
//  QString at4 = arg_text(ct4, 4);


  result += case_txt;
  //QString("case %1: ")

 }

 result += "  //end of switch\n }\n}\n";

 return result;
}


QString gen_dispatch_array(u1 ret, u1 ac, u1 distinct_type_count, u2 arsize,
  QMap<u2, u2>& pretype_patterns_map )
{
 u4 distinct_type_exp = 1;
 for(u1 i = 0; i < distinct_type_count; ++i)
   distinct_type_exp *= 10;

 //u1 ret =
 QString rettext = returns[ret];
 //QString retv = (ret==0)?"":"retv";
 QString retv, rsym, retfull;

 // //  concisely initialize three strings.  A bit cute.
 if(ret > 0)
   retfull = QString("%1& %2").arg(rettext)
   .arg(rsym = QString("%1, ").arg(retv = "retv"));

 QString n8argtext;
 QString argtext;
 for(int i = 1; i <= ac; ++i)
 {
  n8argtext += QString("n8 arg%1, ").arg(i);
  argtext += QString("arg%1, ").arg(i);
 }

 QString result = QString(R"(
#ifndef SEEN_DEFS_S01_%1of%2_RE%3
#define SEEN_DEFS_S01_%1of%2_RE%3

typedef %4(*minimal_fn_s0_re%3_type)();
typedef %4(_min_::*minimal_fn_s1_re%3_type)();
typedef void(*run_s01_%1of%2_re%3_type)(u4 pattern, %5%6minimal_fn_s0_re%3_type fn,
  minimal_fn_s1_re%3_type sfn, void** _this);
typedef run_s01_%1of%2_re%3_type s01_%1of%2_re%3_dispatch_array [%7];

#endif //  SEEN_DEFS_S01_%1of%2_RE%3

#ifdef FULL_INCLUDE

 )").arg(ac).arg(distinct_type_count).arg(ret).arg(rettext).arg(retfull)
   .arg(n8argtext).arg(arsize);


 QMapIterator<u2, u2> it(pretype_patterns_map);

 while(it.hasNext())
 {
  it.next();
  u2 pretype_pattern = it.key();

//  pretype_pattern %= distinct_type_exp;
//  pretype_pattern += (distinct_type_exp * ac);

  u2 index = it.value();

#ifdef CONDENSED_ONLY
  u2 pp = pretype_pattern % distinct_type_exp;
  u2 cp = condense(pp);
  if(cp == pp)
  {
   result += QString("\n#include \"../dev/consoles/fns/a%1of%2/a%1of%2-re%3/fn%4.cpp\" // #%5")
     .arg(ac).arg(distinct_type_count).arg(ret).arg(pretype_pattern).arg(index);
  }
  else
    result += QString("\n// fn%1.cpp (#%2) skipped").arg(pretype_pattern).arg(index);
#else
  result += QString("\n#include \"../dev/consoles/fns/a%1of%2/a%1of%2-re%3/fn%4.cpp\" // #%5")
    .arg(ac).arg(distinct_type_count).arg(ret).arg(pretype_pattern).arg(index);
#endif
 }



 result += QString(R"(

s01_%1of%2_re%3_dispatch_array* init_s01_%1of%2_re%3_dispatch_array()
{
 s01_%1of%2_re%3_dispatch_array* result = (s01_%1of%2_re%3_dispatch_array*) new run_s01_%1of%2_re%3_type[%4];
 )").arg(ac).arg(distinct_type_count).arg(ret).arg(arsize);


 it.toFront();

 while(it.hasNext())
 {
  it.next();
  u2 pretype_pattern = it.key();

//  pretype_pattern %= distinct_type_exp;
//  pretype_pattern += (distinct_type_exp * ac);

  u2 index = it.value();

#ifdef CONDENSED_ONLY
  u2 pp = pretype_pattern % distinct_type_exp;
  u2 cp = condense(pp);
  if(cp == pp)
    result += QString("\n (*result)[%1] = &_f_%2_%3_;")
      .arg(index).arg(pretype_pattern).arg(ret);
  //cp += (distinct_type_exp * ac);
  else
    result += QString("\n (*result)[%1] = nullptr;")
      .arg(index);
#else
  result += QString("\n (*result)[%1] = &_f_%2_%3_;")
    .arg(index).arg(pretype_pattern).arg(ret);
#endif
 }

 result += "\n\n return result;\n}\n";

 result += QString(R"(

void run_s01_%1of%2_re%3(u4 pattern, u4 index, minimal_fn_s0_re%3_type fn,
  minimal_fn_s1_re%3_type sfn, %4%5 void** _this))")
 .arg(ac).arg(distinct_type_count).arg(ret).arg(n8argtext).arg(retfull);

//? u4 code_mask = 99999;

 result += QString(R"(
{
 static s01_%1of%2_re%3_dispatch_array* dispatch_array = init_s01_%1of%2_re%3_dispatch_array();
 run_s01_%1of%2_re%3_type f = (*dispatch_array)[index];
 f(pattern, %4%5fn, sfn, _this);
}

#endif //def FULL_INCLUDE
   )").arg(ac).arg(distinct_type_count).arg(ret).arg(rsym).arg(argtext);


 // u4 pattern = code % 10000;
 //  code %= %1;

//   void run_s01_%1_re%2(u4 code, minimal_fn_s0_re%2_type fn,
//     minimal_fn_s1_re%2_type sfn, void** _this))")
//     .arg(ac).arg(i); // // here ac = 0 and i = 0 always but keep the substitutions for clarity ...

//      s01_X_reX_text += QString(R"(


//code %=
// typedef s01_%1of%8_re%2_dispatch_array s01_%1of%8_re%2_dispatch_arrays [%7];

// for(u2 j = 0; j < arsize; ++j)
// {
// //  if(ac > 0)
// //      s01_X_reX_text += QString("\n (*result)[%1] = &_f_%2%3_;").arg(j).arg(i).arg(j, ac, 10, QLatin1Char('0'));
// //    else
// //      s01_X_reX_text += QString("\n (*result)[%1] = &_f_%2_;").arg(j).arg(i);
// }

 return result;
}

//   QString atext;
//   QString natext;
//   if(ac > 0)
//   {
//    for(u1 aa = 1; aa <= ac; ++aa)
//    {
//     natext += QString("n8 a%1%2").arg(aa).arg(aa < ac? ", " : "");
//     atext += QString("a%1,").arg(aa);
//    }
//   }

//   if( (ac > 0) )
//     s01_X_reX_text += QString(R"(
// return result;
//}

//void run_s01_%1_re%2(u4 code, minimal_fn_s0_re%2_type fn,
//   minimal_fn_s1_re%2_type sfn, %3%4, void** _this))")
//   .arg(ac).arg(i).arg(retv).arg(natext);

//   else if( (i > 0) )
//     s01_X_reX_text += QString(R"(
// return result;
//}

//void run_s01_%1_re%2(u4 code, minimal_fn_s0_re%2_type fn,
//   minimal_fn_s1_re%2_type sfn, %3, void** _this))")
//   .arg(ac).arg(i).arg(retv.left(retv.size() - 2));

//   else
//    s01_X_reX_text += QString(R"(
// return result;
//}

//void run_s01_%1_re%2(u4 code, minimal_fn_s0_re%2_type fn,
//  minimal_fn_s1_re%2_type sfn, void** _this))")
//  .arg(ac).arg(i); // // here ac = 0 and i = 0 always but keep the substitutions for clarity ...

//   s01_X_reX_text += QString(R"(
//{
// code %= %1;
// static s01_%2_re%3_dispatch_array* dispatch_array = init_s01_%2_re%3_dispatch_array();
// run_s01_%2_re%3_type f = (*dispatch_array)[code];
// f(%4%5fn, sfn, _this);
//}

//#endif //def FULL_INCLUDE
//)").arg(arsize).arg(ac).arg(i).arg(rsym).arg(atext); // .arg(ac).arg(arsize * 10).arg(atext);


// ""));

// return result;
//}

void generate_4or3_3(QMap<u2, u2>& pretype_patterns_map, u1 number)
{
 QMapIterator<u2, u2> it(pretype_patterns_map);

 while(it.hasNext())
 {
  it.next();
  u2 pretype_pattern = it.key();

//  pretype_pattern %= 1000;
//  pretype_pattern += 4000;


  for(int i = 0; i <= 9; ++i)
  {
   QString folder = QString(ROOT_FOLDER "/../dev/consoles/fns/a%1of3/a%1of3-re%2").arg(number).arg(i);
   QDir qd(folder);
   if(!qd.exists())
    qd.mkpath(".");


   QString fn_file = QString(ROOT_FOLDER "/../dev/consoles/fns/a%1of3/a%1of3-re%2/fn%3.cpp")
     .arg(number).arg(i).arg(pretype_pattern);
   QString fn_text;

   //   for(int j = 0; j < 120; ++j)
   //   {
   fn_text += generate_function_code(pretype_pattern, i, number) + "\n";
   //   }
   save_file(fn_file, fn_text);
  }
 }
}


QString arg_text_from_args(u1 pretype, u1 index, QString& st)
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

 //QString type; // [4] = {{},{},{},{}};

 QString result;

 switch(pretype)
 {
 case 0: // ref
  // types[i] = "n8&";
  st = "n8&";
  result = QString("n8& a%1=*(n8*)args[%2];").arg(index).arg(index - 1);
  break;

  // // for now treat 9 like a n8
 case 9: pretype = 8; // fallthrough
 case 1: case 2: case 4: case 8:
  st = QString("%1%2").arg(pretype == 8?'n':'u').arg(pretype);
  // types[i] = QString("%1%2").arg(akey == 8?'n':'u').arg(akey);
  result = QString("%1 a%2=*(%1*)args[%3];").arg(st).arg(index).arg(index - 1);
  break;

 case 3: // QString
  st = "QString";
  result = QString("QString a%1=*(QString*)args[%2];").arg(index).arg(index - 1);
  break;

 case 5: // QByteArray
  st = "QByteArray";
  result = QString("QByteArray a%1=*(QByteArray*)args[%2];").arg(index).arg(index - 1);
  break;

 case 6: // double
  st = "r8";
  result = QString("r8 a%1=*(r8*)args[%2];").arg(index).arg(index - 1);
  break;

 case 7: // QVariant
  st = "QVariant";
  result = QString("QVariant a%1 = *(QVariant*)args[%2];").arg(index).arg(index - 1);
  break;
 }

 return result;
}

void generate_X_1()
{
 for(u1 i = 0; i <= 9; ++i)
 {
  QString folder = QString(ROOT_FOLDER "/../dev/consoles/fns/aXof1/aXof1-re%1").arg(i);
  QDir qd(folder);
  if(!qd.exists())
    qd.mkpath(".");

  QString rettext = returns[i];
  //QString retv = (ret==0)?"":"retv";
  QString retv, rsym, retfull;

  // //  concisely initialize three strings.  A bit cute.
  if(i > 0)
    retfull = QString("%1& %2").arg(rettext)
    .arg(rsym = QString("%1, ").arg((retv = "retv=").left(4)));

  for(u1 j = 0; j < 10; ++j)
  {
   QString fn_file = QString(ROOT_FOLDER "/../dev/consoles/fns/aXof1/aXof1-re%1/fn_%2.cpp").arg(i).arg(j);
   QString fn_text = QString(R"(

void _f_X%1_%2_(u1 ac, %3 QVector<n8>& args, minimal_fn_s0_re%2_type fn,
  minimal_fn_s1_re%2_type sfn, void** _this)
{
 switch(ac)
 {
)").arg(j).arg(i).arg(retfull);

   for(u1 k = 1; k < 9; ++k)
   {
    QString at;
    QString st;
    QString aat;
    for(u1 l = 1; l <= k; ++l)
    {
     aat += QString("a%1,").arg(l);
     QString _st;
     at += arg_text_from_args(j, l, _st);
     st += _st + ",";
    }
    aat.chop(1);
    st.chop(1);
    fn_text += QString(R"(
 case %1:
  {%2
   auto _sfn = (%3(_min_::*)(%4))(sfn);
   if(_this) %5((_min_*)*_this->*_sfn)(%6);
   else %5((%3(*)(%4))fn)(%6);
  } break;
)").arg(k).arg(at).arg(rettext).arg(st).arg(retv).arg(aat);
   }

  fn_text += "\n }\n}";
   save_file(fn_file, fn_text);
  }
 }
}


void generate_X_2(const QMap<u2, u2>& pretype_patterns_map)
{
 for(u1 i = 0; i <= 9; ++i)
 {
  QString folder = QString(ROOT_FOLDER "/../dev/consoles/fns/aXof2/aXof2-re%1").arg(i);
  QDir qd(folder);
  if(!qd.exists())
    qd.mkpath(".");

  QString rettext = returns[i];
  //QString retv = (ret==0)?"":"retv";
  QString retv, rsym, retfull;

  // //  concisely initialize three strings.  A bit cute.
  if(i > 0)
    retfull = QString("%1& %2").arg(rettext)
    .arg(rsym = QString("%1, ").arg((retv = "retv=").left(4)));

  QMapIterator<u2, u2> it(pretype_patterns_map);
  while(it.hasNext())
  {
   it.next();
   u2 pretype_pattern = it.key();
   pretype_pattern %= 100;
   u2 index = it.value();

   QString fn_file = QString(ROOT_FOLDER "/../dev/consoles/fns/aXof2/aXof2-re%1/fn_%2.cpp").arg(i)
     .arg(pretype_pattern, 2, 10, QLatin1Char('0'));
   QString fn_text = QString(R"(

void _f_X%1_%2_(u1 ac_pattern, %3 QVector<n8>& args, minimal_fn_s0_re%2_type fn,
  minimal_fn_s1_re%2_type sfn, void** _this) // # %4
{
 switch(ac_pattern)
 {
)").arg(pretype_pattern, 2, 10, QLatin1Char('0')).arg(i).arg(retfull).arg(index);

   {
    QString st1, st2;
    QString argstext = arg_text_from_args(pretype_pattern / 10, 1, st1)
      + arg_text_from_args(pretype_pattern % 10, 2, st2);
    QString sigatext = st1 + "," + st2;
    fn_text += QString(R"(
 case 0: // 2 args, lower-number pretype first
 {%1
  auto _sfn = (%2(_min_::*)(%3))(sfn);
  if(_this) %4((_min_*)*_this->*_sfn)(a1,a2);
  else %4((%2(*)(%3))fn)(a1,a2);
 } break;
)").arg(argstext).arg(rettext).arg(sigatext).arg(retv);
   }

   {
    QString st1, st2;
    QString argstext = arg_text_from_args(pretype_pattern % 10, 1, st1)
      + arg_text_from_args(pretype_pattern / 10, 2, st2);
    QString sigatext = st1 + "," + st2;
    fn_text += QString(R"(
 case 255: // 2 args, higher-number pretype first
 {%1
  auto _sfn = (%2(_min_::*)(%3))(sfn);
  if(_this) %4((_min_*)*_this->*_sfn)(a1,a2);
  else %4((%2(*)(%3))fn)(a1,a2);
 } break;
)").arg(argstext).arg(rettext).arg(sigatext).arg(retv);
   }

   // k + 3 is arg count ...
   for(u1 k = 0; k < 4; ++k)
   {
    // // don't need the all-0 or all-1 cases
     //   because we have two different pretypes ...
    for(u1 l = 1; l < (1 << (k + 3)) - 1; ++l)
    {
     fn_text += QString(R"(
  case %1 + 0b%2:)").arg(k << 6).arg(l, k + 3, 2, QLatin1Char('0'));

     QString argstext, atext, sigatext;
     for(u1 m = 1, pos = 1 << (k + 2); m <= k + 3; ++m, pos >>= 1)
     {
      QString st;

      // get the pretype
      u1 pretype = (l & pos)? (pretype_pattern % 10) : (pretype_pattern / 10);

      argstext += arg_text_from_args(pretype, m, st);
      sigatext += st + ",";
      atext += QString("a%1,").arg(m);
     }
     sigatext.chop(1);
     atext.chop(1);
     fn_text += QString(R"(
  {%1
   auto _sfn = (%2(_min_::*)(%3))(sfn);
   if(_this) %4((_min_*)*_this->*_sfn)(%5);
   else %4((%2(*)(%3))fn)(%5);
  } break;
)").arg(argstext).arg(rettext).arg(sigatext).arg(retv).arg(atext);
    }
//    fn_text += QString(R"(
// case %1:
//  {%2
//   auto _sfn = (%3(_min_::*)(%4))(sfn);
//   if(_this) %5((_min_*)*_this->*_sfn)(%6);
//   else %5((%3(*)(%4))fn)(%6);
//  } break;
//)").arg(k).arg(at).arg(rettext).arg(st).arg(retv).arg(aat);
   }
   fn_text += "\n }\n}";
   save_file(fn_file, fn_text);
  }
 }
}



void generate_pretype_patterns_maps()
{
 QString fns_folder = ROOT_FOLDER "/../dev/consoles/fns";

 QDir fns(fns_folder);
 if(!fns.exists())
   fns.mkpath(".");

 QString pretype_patterns_pri_file = ROOT_FOLDER "/../dev/consoles/fns/pretype-patterns.pri";

 QString pretype_pattern_3_file = ROOT_FOLDER "/../dev/consoles/fns/pretype-patterns-3.cpp";
 QString pretype_pattern_3_text = "#ifdef INCLUDE_ARRAY_CODE\n{";

 QString pretype_pattern_4of3_file = ROOT_FOLDER "/../dev/consoles/fns/pretype-patterns-4of3.cpp";
 QString pretype_pattern_4of3_text = "#ifdef INCLUDE_ARRAY_CODE\n{";

 QString pretype_pattern_2_file = ROOT_FOLDER "/../dev/consoles/fns/pretype-patterns-2.cpp";
 QString pretype_pattern_2_text = "#ifdef INCLUDE_ARRAY_CODE\n{";

 int col3 = 0;
 int col2 = 0;

 int row3 = 0;

 QMap<u2, u2> pretype_pattern_4of3_map;
 QMap<u2, u2> pretype_pattern_3_map;
 QMap<u2, u2> pretype_pattern_2_map;

 int count2 = 0;
 int count3 = 0;

 for(int i = 0; i <= 8; ++i)
 {
  for(int j = i + 1; j <= 9; ++j)
  {
   u2 val2 = 200 + (i*10) + j;
   pretype_pattern_2_map[val2] = count2;
   ++count2;

   ++col2;
   if(col2 == 10)
     col2 = 1;

   if(col2 == 1)
     pretype_pattern_2_text += "\n";
   else if(col2 == 4 || col2 == 7)
     pretype_pattern_2_text += "  ";


   pretype_pattern_2_text += QString(" %1,").arg(val2);

   if(j == 9)
     continue;
   if(i == 8)
     continue;

   for(int k = j + 1; k <= 9; ++k)
   {
    u2 val3 = 3000 + (i*100) + (j*10) + k;
    u2 val4of3 = 4000 + (i*100) + (j*10) + k;
    pretype_pattern_3_map[val3] = count3;
    pretype_pattern_4of3_map[val4of3] = count3;
    ++count3;

    ++col3;
    if(col3 == 13)
    {
     col3 = 1;
     ++row3;
     if(row3 == 5)
     {
      pretype_pattern_3_text += "\n";
      pretype_pattern_4of3_text += "\n";
     }
    }

    if(col3 == 1)
    {
     pretype_pattern_3_text += "\n";
     pretype_pattern_4of3_text += "\n";
    }
    else if(col3 == 4 || col3 == 7 || col3 == 10)
    {
     pretype_pattern_3_text += "  ";
     pretype_pattern_4of3_text += "  ";
    }

    pretype_pattern_3_text += QString(" %1,").arg(val3);
    pretype_pattern_4of3_text += QString(" %1,").arg(val4of3);

   }
  }
 }

 pretype_pattern_3_text.chop(1);
 pretype_pattern_3_text += "\n}\n#endif //def INCLUDE_ARRAY_CODE\n";

 pretype_pattern_4of3_text.chop(1);
 pretype_pattern_4of3_text += "\n}\n#endif //def INCLUDE_ARRAY_CODE\n";

 pretype_pattern_2_text.chop(1);
 pretype_pattern_2_text += "\n}\n#endif // def INCLUDE_ARRAY_CODE\n";

// QTextStream qts3(&pretype_pattern_3_text);

 pretype_pattern_3_text += "\n\n#ifdef INCLUDE_MAP_CODE\n{\n";
 QMapIterator<u2, u2> it3(pretype_pattern_3_map);
 while(it3.hasNext())
 {
  it3.next();
  pretype_pattern_3_text += QString(" {%1,%2},").arg(it3.key()).arg(it3.value());
  if( (it3.value() % 6) == 5 )
    pretype_pattern_3_text += "\n";
 }
 pretype_pattern_3_text.chop(2);
 pretype_pattern_3_text += "\n}\n#endif // INCLUDE_MAP_CODE\n";

 pretype_pattern_4of3_text += "\n\n#ifdef INCLUDE_MAP_CODE\n{\n";
 QMapIterator<u2, u2> it4of3(pretype_pattern_4of3_map);
 while(it4of3.hasNext())
 {
  it4of3.next();
  pretype_pattern_4of3_text += QString(" {%1,%2},").arg(it4of3.key()).arg(it4of3.value());
  if( (it4of3.value() % 6) == 5 )
    pretype_pattern_4of3_text += "\n";
 }
 pretype_pattern_4of3_text.chop(2);
 pretype_pattern_4of3_text += "\n}\n#endif // INCLUDE_MAP_CODE\n";


// QTextStream qts2(&pretype_pattern_2_text);

 pretype_pattern_2_text += "\n\n#ifdef INCLUDE_MAP_CODE\n{\n";
 QMapIterator<u2, u2> it2(pretype_pattern_2_map);
 while(it2.hasNext())
 {
  it2.next();
  pretype_pattern_2_text += QString(" {%1,%2},").arg(it2.key()).arg(it2.value());
  if( (it2.value() % 5) == 4 )
    pretype_pattern_2_text += "\n";
 }
 pretype_pattern_2_text.chop(2);
 pretype_pattern_2_text += "\n}\n#endif // INCLUDE_MAP_CODE\n";

 save_file(pretype_pattern_4of3_file, pretype_pattern_4of3_text);
 save_file(pretype_pattern_3_file, pretype_pattern_3_text);
 save_file(pretype_pattern_2_file, pretype_pattern_2_text);


 QString pretype_patterns_pri_text = "# this file is created to signal for qmake "
   "that the pretype patterns files have been generated";

 save_file(pretype_patterns_pri_file, pretype_patterns_pri_text);
}

void gen_dispatch_arrays(QMap<u2, u2>& pretype_patterns_map, QString xofy, u1 number)
{
 QString run_folder = QString(ROOT_FOLDER "/../dev/consoles/fns/run/run-a%1")
   .arg(xofy);

 QDir qd(run_folder);
 if(!qd.exists())
   qd.mkpath(".");

 for(int i = 0; i <= 9; ++i)
 {
  QString disp = gen_dispatch_array(i, number, 3, 120, pretype_patterns_map);
  //fn_text += generate_function_code(pretype_pattern, i) + "\n";

  QString run_file = QString(ROOT_FOLDER "/../dev/consoles/fns/run/run-a%1/run-s01-%1-re%2.cpp")
    .arg(xofy).arg(i);

  save_file(run_file, disp);
 }
}

QString gen_dispatch_array_Xof1(u1 ret)
{
 QString rettext = returns[ret];
 //QString retv = (ret==0)?"":"retv";
 QString retv, rsym, retfull;

 // //  concisely initialize three strings.  A bit cute.
 if(ret > 0)
   retfull = QString("%1& %2").arg(rettext)
   .arg(rsym = QString("%1, ").arg(retv = "retv"));

 QString result = QString(R"(
#ifndef SEEN_DEFS_S01_Xof1_RE%1
#define SEEN_DEFS_S01_Xof1_RE%1

typedef %2(*minimal_fn_s0_re%1_type)();
typedef %2(_min_::*minimal_fn_s1_re%1_type)();
typedef void(*run_s01_Xof1_re%1_type)(u1 ac, %3 QVector<n8>& args,
  minimal_fn_s0_re%1_type fn, minimal_fn_s1_re%1_type sfn, void** _this);
typedef run_s01_Xof1_re%1_type s01_Xof1_re%1_dispatch_array [10];

#endif //  SEEN_DEFS_S01_Xof1_RE%1

#ifdef FULL_INCLUDE

 )").arg(ret).arg(rettext).arg(retfull);

 for(u1 i = 0; i < 10; ++i)
 {
#ifdef CONDENSED_ONLY
  if( (i == 0) || (i == 6) || (i == 8) )
    result += QString(R"(
 #include "../dev/consoles/fns/aXof1/aXof1-re%1/fn_%2.cpp" // #%2)").arg(ret).arg(i);
  else
    result += QString("\n // fn_%1.cpp (#%1) skipped").arg(i);
#else
  result += QString(R"(
#include "../dev/consoles/fns/aXof1/aXof1-re%1/fn_%2.cpp" // #%2)").arg(ret).arg(i);
#endif
 }

 result += QString(R"(


s01_Xof1_re%1_dispatch_array* init_s01_Xof1_re%1_dispatch_array()
{
 s01_Xof1_re%1_dispatch_array* result = (s01_Xof1_re%1_dispatch_array*) new run_s01_Xof1_re%1_type[10];
 )").arg(ret);

 for(u1 i = 0; i < 10; ++i)
 {
#ifdef CONDENSED_ONLY
  if( (i == 0) || (i == 6) || (i == 8) )
    result += QString(R"(
 (*result)[%1] = &_f_X%1_%2_;)").arg(i).arg(ret);
  else
    result += QString(R"(
 (*result)[%1] = nullptr;)").arg(i);
#else
  result += QString(R"(
 (*result)[%1] = &_f_X%1_%2_;)").arg(i).arg(ret);
#endif
 }

 result += "\n\n return result;\n}\n";

 result += QString(R"(

void run_s01_Xof1_re%1(u1 ac, u1 index, minimal_fn_s0_re%1_type fn,
  minimal_fn_s1_re%1_type sfn, QVector<n8>& args, %2 void** _this))")
 .arg(ret).arg(retfull);

 result += QString(R"(
{
 static s01_Xof1_re%1_dispatch_array* dispatch_array = init_s01_Xof1_re%1_dispatch_array();
 run_s01_Xof1_re%1_type f = (*dispatch_array)[index];
 f(ac, %2args, fn, sfn, _this);
}

#endif //def FULL_INCLUDE
   )").arg(ret).arg(rsym);

 return result;
}


void gen_dispatch_arrays_Xof1()
{
 for(int i = 0; i <= 9; ++i)
 {
  QString disp = gen_dispatch_array_Xof1(i);
  //fn_text += generate_function_code(pretype_pattern, i) + "\n";

  QString run_folder = ROOT_FOLDER "/../dev/consoles/fns/run/run-aXof1";
  QDir qd(run_folder);
  if(!qd.exists())
    qd.mkpath(".");


  QString run_file = QString(ROOT_FOLDER "/../dev/consoles/fns/run/run-aXof1/run-s01-Xof1-re%1.cpp")
     .arg(i);

  save_file(run_file, disp);
 }
}



QString gen_dispatch_array_Xof2(QMap<u2, u2>& pretype_patterns_map, u1 ret)
{
 QString rettext = returns[ret];
 //QString retv = (ret==0)?"":"retv";
 QString retv, rsym, retfull;

 // //  concisely initialize three strings.  A bit cute.
 if(ret > 0)
   retfull = QString("%1& %2").arg(rettext)
   .arg(rsym = QString("%1, ").arg(retv = "retv"));

 QString result = QString(R"(
#ifndef SEEN_DEFS_S01_Xof2_RE%1
#define SEEN_DEFS_S01_Xof2_RE%1

typedef %2(*minimal_fn_s0_re%1_type)();
typedef %2(_min_::*minimal_fn_s1_re%1_type)();
typedef void(*run_s01_Xof2_re%1_type)(u1 ac, %3 QVector<n8>& args,
  minimal_fn_s0_re%1_type fn, minimal_fn_s1_re%1_type sfn, void** _this);
typedef run_s01_Xof2_re%1_type s01_Xof2_re%1_dispatch_array [10];

#endif //  SEEN_DEFS_S01_Xof2_RE%1

#ifdef FULL_INCLUDE

 )").arg(ret).arg(rettext).arg(retfull);

 QMapIterator<u2, u2> it(pretype_patterns_map);
 while(it.hasNext())
 {
  it.next();
  u2 pretype_pattern = it.key();
  pretype_pattern %= 100;
  u2 index = it.value();

#ifdef CONDENSED_ONLY
  u2 condensed = condense(pretype_pattern);
  if(condensed == pretype_pattern)
    result += QString("\n#include \"../dev/consoles/fns/aXof2/aXof2-re%1/fn_%2.cpp\" // #%3")
      .arg(ret).arg(pretype_pattern, 2, 10, QLatin1Char('0')).arg(index);
  else
    result += QString("\n // fn_%1.cpp (#%2) skipped")
      .arg(pretype_pattern, 2, 10, QLatin1Char('0')).arg(index);
#else
  result += QString("\n#include \"../dev/consoles/fns/aXof2/aXof2-re%1/fn_%2.cpp\" // #%3")
    .arg(ret).arg(pretype_pattern, 2, 10, QLatin1Char('0')).arg(index);
#endif
 }

 result += QString(R"(

s01_Xof2_re%1_dispatch_array* init_s01_Xof2_re%1_dispatch_array()
{
 s01_Xof2_re%1_dispatch_array* result = (s01_Xof2_re%1_dispatch_array*) new run_s01_Xof2_re%1_type[45];
 )").arg(ret);

 it.toFront();
 while(it.hasNext())
 {
  it.next();
  u2 pretype_pattern = it.key();
  pretype_pattern %= 100;
  u2 index = it.value();
#ifdef CONDENSED_ONLY
  u2 condensed = condense(pretype_pattern);
  if(condensed != pretype_pattern)
    result += QString(R"(
 (*result)[%1] = nullptr;)").arg(index);
  else
    result += QString(R"(
 (*result)[%1] = &_f_X%2_%3_;)").arg(index).arg(condensed, 2, 10, QLatin1Char('0')).arg(ret);
#else
  result += QString(R"(
  (*result)[%1] = &_f_X%2_%3_;)").arg(index).arg(pretype_pattern, 2, 10, QLatin1Char('0')).arg(ret);
#endif
 }

 result += "\n\n return result;\n}\n";

 result += QString(R"(

void run_s01_Xof2_re%1(u1 ac_pattern, u1 index, minimal_fn_s0_re%1_type fn,
  minimal_fn_s1_re%1_type sfn, QVector<n8>& args, %2 void** _this))")
 .arg(ret).arg(retfull);

 result += QString(R"(
{
 static s01_Xof2_re%1_dispatch_array* dispatch_array = init_s01_Xof2_re%1_dispatch_array();
 run_s01_Xof2_re%1_type f = (*dispatch_array)[index];
 f(ac_pattern, %2args, fn, sfn, _this);
}

#endif //def FULL_INCLUDE
   )").arg(ret).arg(rsym);

 return result;
}


void gen_dispatch_arrays_Xof2(QMap<u2, u2>& pretype_patterns_map)
{
 QString run_folder = ROOT_FOLDER "/../dev/consoles/fns/run/run-aXof2";
 QDir qd(run_folder);
 if(!qd.exists())
   qd.mkpath(".");

 for(int i = 0; i <= 9; ++i)
 {
  QString disp = gen_dispatch_array_Xof2(pretype_patterns_map, i);
  //fn_text += generate_function_code(pretype_pattern, i) + "\n";


  QString run_file = QString(ROOT_FOLDER "/../dev/consoles/fns/run/run-aXof2/run-s01-Xof2-re%1.cpp")
     .arg(i);

  save_file(run_file, disp);
 }
}


void gen_fn_files(QMap<u2, u2>& pretype_patterns_map, QString xofy, u1 number)
{
 QMapIterator<u2, u2> it(pretype_patterns_map);

 while(it.hasNext())
 {
  it.next();

  u2 pretype_pattern = it.key();

  for(int i = 0; i <= 9; ++i)
  {
   QString folder = QString(ROOT_FOLDER "/../dev/consoles/fns/a%1/a%1-re%2").arg(xofy).arg(i);
   QDir qd(folder);
   if(!qd.exists())
    qd.mkpath(".");

   QString fn_file = QString(ROOT_FOLDER "/../dev/consoles/fns/a%1/a%1-re%2/fn%3.cpp").arg(xofy).arg(i).arg(pretype_pattern);
   QString fn_text;

   //   for(int j = 0; j < 120; ++j)
   //   {
   fn_text += generate_function_code(pretype_pattern, i, number) + "\n";
   //   }
   save_file(fn_file, fn_text);
  }
 }
}


//void generate_function_code()
//{
//}

void gen_eval_files(//QMap<u2, u2>& pretype_patterns_map,
  u1 arg_count, u1 distinct_types_count)
{
 //static u2 exps[4] {1, 10, 100, 1000};

 u4 arsize = 1;
 for(u1 i = 0; i < arg_count; ++i)
 {
  arsize *= 10;
 }

 for(u1 i = 0; i < 10; ++i)
 {
  QString ret = returns[i];
  QString retv, rsym;

  // //  concisely initialize two strings.  A bit cute.
  if(i > 0)
    retv = QString("%1& %2").arg(ret).arg(rsym = "retv, ");

  QString folder = QString(ROOT_FOLDER "/../dev/consoles/fns/eval/a%1of%2").arg(arg_count)
    .arg(distinct_types_count);
  QDir qd(folder);
  if(!qd.exists())
   qd.mkpath(".");

  QString s01_X_reX_ch_eval_file = QString(ROOT_FOLDER "/../dev/consoles/fns/eval/a%1of%2/ch-eval-s01_%1of%2_re%3.cpp")
    .arg(arg_count).arg(distinct_types_count).arg(i);
  QString s01_X_reX_ch_eval_text = (arg_count == 0)? "" : R"(

Chasm_Channel* lambda = ccp->channel("lambda");
if(!lambda)
 return;
)";

  if(i > 0)
    s01_X_reX_ch_eval_text += R"(
Chasm_Channel* retvalue = ccp->channel("retvalue");
if(!retvalue)
 return;
)";


  s01_X_reX_ch_eval_text += R"(
Chasm_Channel* sigma = ccp->channel("sigma");
void** _this; void* _this_;
if(sigma)
{
 _this_ = sigma->first_carrier().value<void*>();
 _this = &_this_;
}
else { _this = nullptr; _this_ = nullptr; }
)";

  QString pasn8s;
  if(arg_count > 0)
  {
   for(int aa = 1; aa <= arg_count; ++aa)
     pasn8s += QString(", lambda->pasn8(%1)").arg(aa);
  }

  if(i == 0)
  {
   s01_X_reX_ch_eval_text += QString(R"(
u2 index = pretype_patterns_%1of%2_map.value(fncode.distinct_pretype_pattern);
run_s01_%1of%2_re0(fncode.pretype_pattern, index, (minimal_fn_s0_re0_type) fn,
 (minimal_fn_s1_re0_type) sfn%3, _this);
)").arg(arg_count).arg(distinct_types_count).arg(pasn8s);
  }
  else
  {
   s01_X_reX_ch_eval_text += QString(R"(
Chasm_Carrier cc = retvalue->first_carrier();

%1%2 rr = %3cc.value%4<%1>();

u2 index = pretype_patterns_%5of%6_map.value(fncode.distinct_pretype_pattern);
run_s01_%5of%6_re%7(fncode.pretype_pattern, index, (minimal_fn_s0_re%7_type) fn,
  (minimal_fn_s1_re%7_type) sfn%8, rr, _this);

if(rcar)
  rcar->set_value%9(rr);
)").arg(ret).arg( (i == 3 || i == 5 || i == 7)?"&":"")
  .arg("")  //.arg((i == 3 || i == 5 || i == 7)?"*("+ret+"*)":"")
  .arg((i == 3 || i == 5 || i == 7)?"_as":"")
  .arg(arg_count).arg(distinct_types_count)
  .arg(i).arg(pasn8s)
  .arg((i == 3 || i == 5 || i == 7)?"_as<"+ret+">":
    //(i==9)?"":(i==0)?"*":
    ""

   )
   ;
  }
  save_file(s01_X_reX_ch_eval_file, s01_X_reX_ch_eval_text);
 }
}


void gen_eval_file_Xof1or2_r(u1 ret, u1 number)
{
 QString rettext = returns[ret];
 QString retfull, retv, rsym;

   // //  concisely initialize three strings.  A bit cute.
 if(ret > 0)
   retfull = QString("%1& %2").arg(ret).arg(rsym = QString("%1, ").arg(retv = "retv"));

 QString folder = QString(ROOT_FOLDER "/../dev/consoles/fns/eval/aXof%1").arg(number);
 QDir qd(folder);
 if(!qd.exists())
   qd.mkpath(".");

 QString s01_aXof1or2_reX_ch_eval_file = QString(
    ROOT_FOLDER "/../dev/consoles/fns/eval/aXof%1/ch-eval-s01_Xof%1_re%2.cpp")
    .arg(number).arg(ret);
 QString s01_aXof1or2_reX_ch_eval_text = R"(

Chasm_Channel* lambda = ccp->channel("lambda");
if(!lambda)
  return;
)";

 if(ret > 0)
   s01_aXof1or2_reX_ch_eval_text += R"(
Chasm_Channel* retvalue = ccp->channel("retvalue");
if(!retvalue)
  return;
)";

 s01_aXof1or2_reX_ch_eval_text += R"(

QVector<n8> args;
lambda->pasn8vector(args, fncode.arg_count);

Chasm_Channel* sigma = ccp->channel("sigma");
void** _this; void* _this_;
if(sigma)
{
 _this_ = sigma->first_carrier().value<void*>();
 _this = &_this_;
}
else { _this = nullptr; _this_ = nullptr; }
)";

if(ret > 0)
  s01_aXof1or2_reX_ch_eval_text += QString(R"(
Chasm_Carrier cc = retvalue->first_carrier();
%1%2 rr = cc.value%3<%1>();
)").arg(rettext).arg( (ret == 3 || ret == 5 || ret == 7)?"&":"")
   .arg((ret == 3 || ret == 5 || ret == 7)?"_as":"");

if(number == 2)
  s01_aXof1or2_reX_ch_eval_text += R"(

u1 ac_pattern = (fncode.arg_count == 2)?
  ( (fncode.pretype_pattern_binary == 2)? 255: 0):
  ( ((fncode.arg_count - 3) << 6)
    | (fncode.pretype_pattern_binary &
        ((1 << fncode.arg_count) - 1) ) );

u1 index = pretype_patterns_2_map.value((fncode.distinct_pretype_pattern % 100) + 200);
)";

QString rr = (ret == 0)? "": "rr, ";

if(number == 2)
  s01_aXof1or2_reX_ch_eval_text += QString(R"(
run_s01_Xof%1_re%2(ac_pattern, index,
  (minimal_fn_s0_re%2_type) fn,
  (minimal_fn_s1_re%2_type) sfn, args, %3_this);
)").arg(number).arg(ret).arg(rr);

else
  s01_aXof1or2_reX_ch_eval_text += QString(R"(
run_s01_Xof%1_re%2(fncode.arg_count, fncode.distinct_pretype_pattern,
   (minimal_fn_s0_re%2_type) fn,
   (minimal_fn_s1_re%2_type) sfn, args, %3_this);
)").arg(number).arg(ret).arg(rr);


if(ret > 0)
  s01_aXof1or2_reX_ch_eval_text += QString(R"(
if(rcar)
  rcar->set_value%1(rr);
)").arg((ret == 3 || ret == 5 || ret == 7)?"_as<"+rettext+">":"");

 save_file(s01_aXof1or2_reX_ch_eval_file, s01_aXof1or2_reX_ch_eval_text);
}

//u1 ac_pattern = (fncode.arg_count == 2)?
//  ( (fncode.pretype_pattern_binary == 1)? 255: 0):
//  ( ((fncode.arg_count - 2) << 6)
//    | (fncode.pretype_pattern_binary &
//        ((1 << fncode.arg_count) - 1) ) );


void gen_eval_files_Xof1or2()
{
 for(u1 i = 0; i < 10; ++i)
 {
  gen_eval_file_Xof1or2_r(i, 1);
  gen_eval_file_Xof1or2_r(i, 2);
 }
}

int main(int argc, char *argv[])
{
#ifndef HAVE_PRETYPE_PATTERNS
 generate_pretype_patterns_maps();
#endif

#ifdef HAVE_PRETYPE_PATTERNS

#define INCLUDE_MAP_CODE
 QMap<u2, u2> pretype_patterns_3_map {
  #include "../dev/consoles/fns/pretype-patterns-3.cpp"
 };
#undef INCLUDE_MAP_CODE// def INCLUDE_MAP_CODE

#define INCLUDE_MAP_CODE
 QMap<u2, u2> pretype_patterns_2_map {
  #include "../dev/consoles/fns/pretype-patterns-2.cpp"
 };
#undef INCLUDE_MAP_CODE// def INCLUDE_MAP_CODE

#define INCLUDE_MAP_CODE
 QMap<u2, u2> pretype_patterns_4of3_map {
  #include "../dev/consoles/fns/pretype-patterns-4of3.cpp"
 };
#undef INCLUDE_MAP_CODE// def INCLUDE_MAP_CODE

 generate_X_1();
 generate_X_2(pretype_patterns_2_map);

 gen_dispatch_arrays_Xof1();
 gen_dispatch_arrays_Xof2(pretype_patterns_2_map);

 gen_eval_files_Xof1or2();

 gen_dispatch_arrays(pretype_patterns_4of3_map, "4of3", 4);
 gen_fn_files(pretype_patterns_4of3_map, "4of3", 4);
 gen_eval_files(4, 3);

 gen_dispatch_arrays(pretype_patterns_3_map, "3of3", 3);
 gen_fn_files(pretype_patterns_3_map, "3of3", 3);
 gen_eval_files(3, 3);
#endif // def HAVE_PRETYPE_PATTERNS
}


int main5(int argc, char *argv[])
{
 QString case_text_4_file = QString(ROOT_FOLDER "/../dev/consoles/fns/case-text-4.cpp");

 QString case_text_4;

 for(int i = 1; i <= 3; ++i)
 {
  for(int j = 1; j <= 3; ++j)
  {
   for(int k = 1; k <= 3; ++k)
   {
    for(int l = 1; l <= 3; ++l)
    {
     u4 same = 0;
     if(i == j) ++same;
     if(i == k) ++same;
     if(i == l) ++same;
     if(j == k) ++same;
     if(j == l) ++same;
     if(k == l) ++same;
     if(same > 1)
       continue;
     u2 caseval = (1000*i) + (100*j) + (10*k) + l;
     case_text_4 += QString("\ncase %1: ").arg(caseval);
    }
   }
  }
 }
 save_file(case_text_4_file, case_text_4);


 QString case_text_5_file = QString(ROOT_FOLDER "/../dev/consoles/fns/case-text-5.cpp");
 QString case_text_5a_file = QString(ROOT_FOLDER "/../dev/consoles/fns/case-text-5a.cpp");
 QString case_text_5b_file = QString(ROOT_FOLDER "/../dev/consoles/fns/case-text-5b.cpp");

 QString case_text_5;
 QString case_text_5a;
 QString case_text_5b;

 for(int i = 1; i <= 3; ++i)
 {
  for(int j = 1; j <= 3; ++j)
  {
   for(int k = 1; k <= 3; ++k)
   {
    for(int l = 1; l <= 3; ++l)
    {
     for(int m = 1; m <= 3; ++m)
     {
      u4 same = 0;
      if(i == j) ++same;
      if(i == k) ++same;
      if(i == l) ++same;
      if(i == m) ++same;
      if(j == k) ++same;
      if(j == l) ++same;
      if(j == m) ++same;
      if(k == l) ++same;
      if(k == m) ++same;
      if(l == m) ++same;
      if(same > 3)
        continue;
      u2 caseval = (10000*i) + (1000*j) + (100*k) + (10*l) + m;
      case_text_5 += QString("\ncase %1: ").arg(caseval);

      if(same == 2)
        case_text_5a += QString("\ncase %1: ").arg(caseval);
      if(same == 3)
        case_text_5b += QString("\ncase %1: ").arg(caseval);
     }
    }
   }
  }
 }
 save_file(case_text_5_file, case_text_5);
 save_file(case_text_5a_file, case_text_5a);
 save_file(case_text_5b_file, case_text_5b);

}



int main4(int argc, char *argv[])
{
 QString case_text_file = QString(ROOT_FOLDER "/../dev/consoles/fns/case-text.cpp");

 QString case_text;

 for(int i = 1; i <= 3; ++i)
 {
  for(int j = 1; j <= 3; ++j)
  {
   if(j == i)
     continue;
   for(int k = 1; k <= 3; ++k)
   {
    if(k == i)
      continue;
    if(k == j)
      continue;

    u2 caseval = (100*i) + (10*j) + k;
    case_text += QString("\ncase %1: ").arg(caseval);
   }
  }
 }

 case_text += "\n";

 for(u1 i = 1; i < 63; ++i)
 {
  case_text += QString("\ncase 0b%1: ").arg(i, 6, 2, QLatin1Char('0'));
 }

 case_text += "\n";

// for(int i = 1; i <= 3; ++i)
// {
//  for(int j = 1; j <= 3; ++j)
//  {

//  }
// }

 save_file(case_text_file, case_text);

}



int main2(int argc, char *argv[])
{
//#define INCLUDE_MAP_CODE
// QMap<u2, u2> pretype_patterns_3_map {
//  #include "../dev/consoles/fns/pretype-patterns-3.cpp"
// };

// QMap<u2, u2> pretype_patterns_2_map {
//  #include "../dev/consoles/fns/pretype-patterns-2.cpp"
// };

// QMap<u2, u2> pretype_patterns_1_map {
//  #include "../dev/consoles/fns/pretype-patterns-1.cpp"
// };

 return 0;
}


int main1(int argc, char *argv[])
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


// parse_fn_code(84049123);
// parse_fn_code(74049123);

// parse_fn_code(6409121);
// parse_fn_code(5409121);

// parse_fn_code(440111);
// parse_fn_code(340111);

// parse_fn_code(44011);
// parse_fn_code(34011);

// parse_fn_code(4401);
// parse_fn_code(3401);


// parse_fn_code(29);
// parse_fn_code(19);

}





#ifdef HIDE

QString generate_function_code(u1 retc, u2 key, QString sc0, QString sc1, u1 ac)
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



 QString result = (ac > 0)? QString(
   "void _f_%1%2_(%3%4minimal_fn_%5_re%1_type fn, "
   "minimal_fn_%6_re%1_type sfn, void* _this)\n{\n ")
     .arg(retc).arg(key, ac, 10, QLatin1Char('0'))
     .arg(retv).arg(more_args).arg(sc0).arg(sc1)
   :
   QString("void _f_%1_(%2%3minimal_fn_%4_re%1_type fn, "
     "minimal_fn_%5_re%1_type sfn, void* _this)\n{\n ")
     .arg(retc).arg(retv).arg(more_args).arg(sc0).arg(sc1);

 u1 akey = 0;

 // types[0] is return ...  less than 3 others might be used (if ac < 3)
 QString types [4] = {ret,{},{},{}};

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
  result += "\n ";
 }

 QString sfn_line;
 QString if_this;
 if(retc > 0) if_this = "retv=";

 QString if_this_else = if_this;
 if_this.prepend(" if(_this) ");
 if_this_else.prepend("\n else ");


 switch(ac)
 {
 case 0:
  sfn_line += QString("auto _sfn = (%1(_min_::*)())(sfn);\n").arg(ret);
  if_this += "((_min_*)*_this->*_sfn)();\n";//.arg(ret);
  if_this_else += QString("((%1(*)()) fn)();\n}\n").arg(ret);
  break;

 case 1:  //(%2))
  sfn_line += QString("auto _sfn = (%1(_min_::*)(%2))(sfn);\n").arg(ret).arg(types[1]);
  if_this += " ((_min_*)*_this->*_sfn)(a1);"; // //(%2))\n"; //.arg(ret).arg(types[1]);
  if_this_else += QString("((%1(*)(%2)) fn)(a1);\n}\n").arg(ret).arg(types[1]);
  break;

 case 2: //(%2,%3))
  sfn_line += QString("auto _sfn = (%1(_min_::*)(%2,%3))(sfn);\n").arg(ret)
    .arg(types[1]).arg(types[2]);
  if_this += " ((_min_*)*_this->*_sfn)(a1,a2);"; // //(2,3))\n")
    //.arg(types[1]).arg(types[2]);
  if_this_else += QString("((%1(*)(%2,%3)) fn)(a1,a2);\n}\n")
    .arg(ret).arg(types[1]).arg(types[2]);
  break;

 case 3: //(%2,%3,%4))
  sfn_line += QString("auto _sfn = (%1(_min_::*)(%2,%3,%4))(sfn);\n")
    .arg(ret).arg(types[1]).arg(types[2]).arg(types[3]);
  if_this += " ((_min_*)*_this->*_sfn)(a1,a2,a3);"; //(%2,%3,%4))\n"
    //.arg(ret).arg(types[1]).arg(types[2]).arg(types[3]);
  if_this_else += QString("((%1(*)(%2,%3,%4))fn)(a1,a2,a3);\n}\n")
    .arg(ret).arg(types[1]).arg(types[2]).arg(types[3]);
  break;
 }

 result += sfn_line + if_this + if_this_else;

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


   QString s01_X_reX_ch_eval_file = QString(ROOT_FOLDER "/../dev/consoles/fns/s01/a%1/ch-eval-s01_%1_re%2.cpp").arg(ac).arg(i);
   QString s01_X_reX_ch_eval_text = (ac == 0)? "" : R"(

Chasm_Channel* lambda = ccp->channel("lambda");
if(!lambda)
  return;
)";

   if(i > 0)
     s01_X_reX_ch_eval_text += R"(
Chasm_Channel* retvalue = ccp->channel("retvalue");
if(!retvalue)
  return;
)";


   s01_X_reX_ch_eval_text += R"(
Chasm_Channel* sigma = ccp->channel("sigma");
void* _this;
if(sigma)
  _this = sigma->first_carrier().value<void*>();
else
  _this = nullptr;
)";

   QString pasn8s;
   if(ac > 0)
   {
    for(int aa = 1; aa <= ac; ++aa)
      pasn8s += QString(", lambda->pasn8(%1)").arg(aa);
   }

   if(i == 0)
   {
    s01_X_reX_ch_eval_text += QString(R"(
run_s01_%1_re0(fncode, (minimal_fn_s0_re0_type) fn,
  (minimal_fn_s1_re0_type) sfn%2, _this);
)").arg(ac).arg(pasn8s);
   }
   else
   {
    s01_X_reX_ch_eval_text += QString(R"(
Chasm_Carrier cc = retvalue->first_carrier();

%1%2 rr = %3cc.value%4<%1>();
run_s01_%5_re%6(fncode, (minimal_fn_s0_re%6_type) fn,
  (minimal_fn_s1_re%6_type) sfn, rr%7, _this);

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
   save_file(s01_X_reX_ch_eval_file, s01_X_reX_ch_eval_text);

   QString s01_X_reX_file = QString(ROOT_FOLDER "/../dev/consoles/fns/s01/a%1/run-s01_%1_re%2.cpp").arg(ac).arg(i);
   QString fn_array_reX_file = QString(ROOT_FOLDER "/../dev/consoles/fns/s01/a%1/fn-array-s01_%1_re%2.cpp").arg(ac).arg(i);

   QString fn_array_reX_text;

   QString n8argtext;
   if(ac > 0)
   {
    for(u1 aa = 1; aa <= ac; ++aa)
    {
     n8argtext += QString("n8 arg%1, ").arg(aa);
    }
   }

   QString s01_X_reX_text = QString(R"(


#ifndef SEEN_DEFS_S01_%4_RE%2
#define SEEN_DEFS_S01_%4_RE%2

typedef %1(*minimal_fn_s0_re%2_type)();
typedef %1(_min_::*minimal_fn_s1_re%2_type)();
typedef void(*run_s01_%4_re%2_type)(%3%6minimal_fn_s0_re%2_type fn,
  minimal_fn_s1_re%2_type sfn, void* _this);
typedef run_s01_%4_re%2_type s01_%4_re%2_dispatch_array [%5];

#endif //  SEEN_DEFS_S01_%4_RE%2

#ifdef FULL_INCLUDE

#include "fn-array-s01_%4_re%2.cpp"

s01_%4_re%2_dispatch_array* init_s01_%4_re%2_dispatch_array()
{
 s01_%4_re%2_dispatch_array* result = (s01_%4_re%2_dispatch_array*) new run_s01_%4_re%2_type[%5];
 )").arg(ret).arg(i).arg(retv).arg(ac).arg(arsize).arg(n8argtext);

   for(u2 j = 0; j < arsize; ++j)
   {
    if(ac > 0)
      s01_X_reX_text += QString("\n (*result)[%1] = &_f_%2%3_;").arg(j).arg(i).arg(j, ac, 10, QLatin1Char('0'));
    else
      s01_X_reX_text += QString("\n (*result)[%1] = &_f_%2_;").arg(j).arg(i);
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
     s01_X_reX_text += QString(R"(
 return result;
}

void run_s01_%1_re%2(u4 code, minimal_fn_s0_re%2_type fn,
   minimal_fn_s1_re%2_type sfn, %3%4, void* _this))")
   .arg(ac).arg(i).arg(retv).arg(natext);

   else if( (i > 0) )
     s01_X_reX_text += QString(R"(
 return result;
}

void run_s01_%1_re%2(u4 code, minimal_fn_s0_re%2_type fn,
   minimal_fn_s1_re%2_type sfn, %3, void* _this))")
   .arg(ac).arg(i).arg(retv.left(retv.size() - 2));

   else
    s01_X_reX_text += QString(R"(
 return result;
}

void run_s01_%1_re%2(u4 code, minimal_fn_s0_re%2_type fn,
  minimal_fn_s1_re%2_type sfn, void* _this))")
  .arg(ac).arg(i); // // here ac = 0 and i = 0 always but keep the substitutions for clarity ...

   s01_X_reX_text += QString(R"(
{
 code %= %1;
 static s01_%2_re%3_dispatch_array* dispatch_array = init_s01_%2_re%3_dispatch_array();
 run_s01_%2_re%3_type f = (*dispatch_array)[code];
 f(%4%5fn, sfn, _this);
}

#endif //def FULL_INCLUDE
)").arg(arsize).arg(ac).arg(i).arg(rsym).arg(atext); // .arg(ac).arg(arsize * 10).arg(atext);

   save_file(s01_X_reX_file, s01_X_reX_text);

   for(int j = 0; j < arsize; ++j)
     fn_array_reX_text += generate_function_code(i, j, "s0", "s1", ac);
   save_file(fn_array_reX_file, fn_array_reX_text);
  }

 }
 return 0;
}

#endif //def HIDE
