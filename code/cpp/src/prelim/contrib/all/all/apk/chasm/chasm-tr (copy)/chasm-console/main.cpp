
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include <QDebug>

#include <QPoint>

#include "chasm-lib/test-class.h"

#include "chasm-lib/unified-runtime-object.h"

#include "chasm-lib/metatype-object.h"

#include "chasm-lib/chasm/types/chasm-type-object.h"


#include "textio.h"
USING_KANS(TextIO)

#include "chasm-lib/chasm/chasm-runtime.h"
#include "chasm-lib/chasm/chasm-call-package.h"



typedef void (*_temp_minimal_fn_s0_r0_type)();

//typedef minimal_fn_s0_re0_type minimal_fn_s0_type;
//typedef minimal_fn_s1_re0_type minimal_fn_s1_type;


void testqvar(QVariant arg1, r8 arg2, u2 arg3)
{
 qDebug() << "arg1 = " << arg1;
 qDebug() << "arg2 = " << arg2;
 qDebug() << "arg3 = " << arg3;
}

void run_testqvar(Chasm_Runtime* csr)
{
 Chasm_Call_Package* ccp = csr->new_call_package();
 ccp->add_new_channel("lambda");

 QVariant a1 = 103;
 r8 a2 = .12345;
 u2 a3 = 12345;

 Chasm_Carrier cc1 = csr->gen_carrier<QVariant>(&a1);
 Chasm_Carrier cc2 = csr->gen_carrier<r8>(&a2);
 Chasm_Carrier cc3 = csr->gen_carrier<u2>(&a3);

 ccp->add_carriers({cc1,cc2,cc3});

 csr->evaluate(ccp, 300762_cfc, &testqvar);
 //csr->evaluate(ccp, 300762_cfc, &testqvar);
}


void testqvarf(QVariant arg1, r8 arg2, float* arg3)
{
 qDebug() << "arg1 = " << arg1;
 qDebug() << "arg2 = " << arg2;
 qDebug() << "arg3 = " << *arg3;
}

void run_testqvarf(Chasm_Runtime* csr)
{
 Chasm_Call_Package* ccp = csr->new_call_package();
 ccp->add_new_channel("lambda");

 QVariant a1 = 103;
 r8 a2 = .12345;
 float* a3 = new float(.12345);

 Chasm_Carrier cc1 = csr->gen_carrier<QVariant>(&a1);
 Chasm_Carrier cc2 = csr->gen_carrier<r8>(&a2);
 Chasm_Carrier cc3 = csr->gen_carrier<void*>(&a3);

 ccp->add_carriers({cc1,cc2,cc3});
 csr->evaluate(ccp, 300769_cfc, &testqvarf);
}




void testfn(s1 arg1, u4 arg2, s2& arg3)
{
 qDebug() << "arg1 = " << arg1;
 qDebug() << "arg2 = " << arg2;
 qDebug() << "arg2 + 1 = " << arg2 + 1;
 qDebug() << "arg3 = " << arg3;
 arg3 = -arg3;
}

void run_testfn(Chasm_Runtime* csr)
{
 Chasm_Call_Package* ccp = csr->new_call_package();
 ccp->add_new_channel("lambda");

 s1 a1 = -103;
 u4 a2 = -1;
 s2 a3 = -211;

 Chasm_Carrier cc1 = csr->gen_carrier<u1>(&a1);
 Chasm_Carrier cc2 = csr->gen_carrier<u4>(&a2);
 Chasm_Carrier cc3 = csr->gen_carrier<n8&>(&a3);

 ccp->add_carriers({cc1,cc2,cc3});
 csr->evaluate(ccp, 300140_cfc, &testfn);
 qDebug() << "a3 = " << a3;
}



s1 testsus(s1 arg1, u4 arg2, s2 arg3)
{
 qDebug() << "arg1 = " << arg1;
 qDebug() << "arg2 = " << arg2;
 qDebug() << "arg3 = " << arg3;

 return -arg1;
}

void run_testsus(Chasm_Runtime* csr)
{
 Chasm_Call_Package* ccp = csr->new_call_package();
 ccp->add_new_channel("lambda");

 bool a1 = "true";
 s2 a2 = -533;
 s2 a3 = -211;

 Chasm_Carrier cc1 = csr->gen_carrier<u1>(&a1);
 Chasm_Carrier cc2 = csr->gen_carrier<u2>(&a2);
 Chasm_Carrier cc3 = csr->gen_carrier<n8&>(&a3);

 ccp->add_carriers({cc1,cc2,cc3});
 csr->evaluate(ccp, 300120_cfc, &testsus);
 qDebug() << "a3 = " << a3;
}


void testqs(QString arg1, u4 arg2, u1 arg3)
{
 qDebug() << "arg1 = " << arg1;
 qDebug() << "arg2 = " << arg2;
 qDebug() << "arg3 = " << arg3;
}

QString testqss(QString arg1, u4 arg2, u1 arg3)
{
 qDebug() << "arg1 = " << arg1;
 qDebug() << "arg2 = " << arg2;
 qDebug() << "arg3 = " << arg3;
 return QString("%1, %2, %3").arg(arg1).arg(arg2).arg(arg3);
}

void run_testqss(Chasm_Runtime* csr)
{
 Chasm_Call_Package* ccp = csr->new_call_package();
 ccp->add_new_channel("lambda");

 bool a1 = "true";
 s2 a2 = -533;
 s2 a3 = -211;

 Chasm_Carrier cc1 = csr->gen_carrier<u1>(&a1);
 Chasm_Carrier cc2 = csr->gen_carrier<u2>(&a2);
 Chasm_Carrier cc3 = csr->gen_carrier<n8&>(&a3);

 ccp->add_carriers({cc1,cc2,cc3});
 csr->evaluate(ccp, 300120_cfc, &testqss);
 qDebug() << "a3 = " << a3;

 // ccp->add_new_channel("retvalue");
 // Chasm_Carrier cc0 = csr->gen_carrier<u1>(csr->Retvalue._u1);
 // ccp->add_carrier(cc0);
 // csr->evaluate(ccp, 71341, (minimal_fn_s0_re1_type) &testqs1, &cc0);
 // u1 result = cc0.value<u1>();
 // qDebug() << "r = " << result;
}


u1 testqs1(QString arg1, float arg2, u1 arg3)
{
 qDebug() << "arg1 = " << arg1;
 qDebug() << "arg2 = " << arg2;
 qDebug() << "arg3 = " << arg3;
 u1 result = arg1.size() + ( (u1)arg2 % 10) + (arg3 % 10);
 return result;
}

void run_testqs1(Chasm_Runtime* csr)
{
 Chasm_Call_Package* ccp = csr->new_call_package();
 ccp->add_new_channel("lambda");

 QString a1 = "A1";
 float a2 = 12345.6789;
 u1 a3 = 135;

 Chasm_Carrier cc1 = csr->gen_carrier<QString>(&a1);
 Chasm_Carrier cc2 = csr->gen_carrier<r8>(&a2);
 Chasm_Carrier cc3 = csr->gen_carrier<u1>(&a3);

 ccp->add_carriers({cc1,cc2,cc3});

 ccp->add_new_channel("retvalue");
 Chasm_Carrier cc0 = csr->gen_carrier<u1>(csr->Retvalue._u1);
 ccp->add_carrier(cc0);

 csr->evaluate(ccp, 301361_cfc, &testqs1, &cc0);
 u1 result = cc0.value<u1>();
 qDebug() << "r = " << result;
}


s1 testqs1n(QString arg1, u4 arg2, u1 arg3)
{
 qDebug() << "arg1 = " << arg1;
 qDebug() << "arg2 = " << arg2;
 qDebug() << "arg3 = " << arg3;
 u1 result = arg1.size() + (arg2 % 10) + (arg3 % 10);
 return -result;
}

void run_testqs1n(Chasm_Runtime* csr)
{
 Chasm_Call_Package* ccp = csr->new_call_package();
 ccp->add_new_channel("lambda");

 QString a1 = "Test";
 u4 a2 = 33;
 u1 a3 = 111;

 Chasm_Carrier cc1 = csr->gen_carrier<QString>(&a1);
 Chasm_Carrier cc2 = csr->gen_carrier<u4>(&a2);
 Chasm_Carrier cc3 = csr->gen_carrier<u1>(&a3);

 ccp->add_carriers({cc1,cc2,cc3});

 ccp->add_new_channel("retvalue");

 Chasm_Carrier cc0 = csr->gen_carrier<u2>(csr->Retvalue._u1);
 ccp->add_carrier(cc0);
 csr->evaluate(ccp, 301341_cfc, &testqs1n, &cc0);
 s1 result = cc0.value<s1>();
 qDebug() << "r = " << result;
}

u2 testqs2(QString arg1, u4 arg2, u1 arg3)
{
 qDebug() << "arg1 = " << arg1;
 qDebug() << "arg2 = " << arg2;
 qDebug() << "arg3 = " << arg3;
 u2 result = arg1.size() + (arg2 % 10) + (arg3 % 10);
 return result * 100;
}

void run_testqs2(Chasm_Runtime* csr)
{
 Chasm_Call_Package* ccp = csr->new_call_package();
 ccp->add_new_channel("lambda");

 QString a1 = "Test";
 u4 a2 = 33;
 u1 a3 = 111;

 Chasm_Carrier cc1 = csr->gen_carrier<QString>(&a1);
 Chasm_Carrier cc2 = csr->gen_carrier<u4>(&a2);
 Chasm_Carrier cc3 = csr->gen_carrier<u1>(&a3);

 ccp->add_carriers({cc1,cc2,cc3});

 ccp->add_new_channel("retvalue");

 Chasm_Carrier cc0 = csr->gen_carrier<u2>(csr->Retvalue._u2);
 ccp->add_carrier(cc0);
 csr->evaluate(ccp, 302341_cfc, &testqs2, &cc0);
 u2 result = cc0.value<u2>();
 qDebug() << "r = " << result;
}


s2 testqs2n(QString arg1, u4 arg2, u1 arg3)
{
 qDebug() << "arg1 = " << arg1;
 qDebug() << "arg2 = " << arg2;
 qDebug() << "arg3 = " << arg3;
 s2 result = arg1.size() + (arg2 % 10) + (arg3 % 10);
 return -result * 100;
}

void run_testqs2n(Chasm_Runtime* csr)
{
 Chasm_Call_Package* ccp = csr->new_call_package();
 ccp->add_new_channel("lambda");

 QString a1 = "Test";
 u4 a2 = 33;
 u1 a3 = 111;

 Chasm_Carrier cc1 = csr->gen_carrier<QString>(&a1);
 Chasm_Carrier cc2 = csr->gen_carrier<u4>(&a2);
 Chasm_Carrier cc3 = csr->gen_carrier<u1>(&a3);

 ccp->add_carriers({cc1,cc2,cc3});

 ccp->add_new_channel("retvalue");

 Chasm_Carrier cc0 = csr->gen_carrier<u2>(csr->Retvalue._u2);
 ccp->add_carrier(cc0);
 csr->evaluate(ccp, 302341_cfc, &testqs2n, &cc0);
 s2 result = cc0.value<s2>();
 qDebug() << "r = " << result;
}


QString testqsq(QString arg1, u4 arg2, u1 arg3)
{
 qDebug() << "arg1 = " << arg1;
 qDebug() << "arg2 = " << arg2;
 qDebug() << "arg3 = " << arg3;
 QString result = QString("[%1 - %2 - %3]").arg(arg1).arg(arg2).arg(arg3);
 return result;
}

void run_testqsq(Chasm_Runtime* csr)
{
 Chasm_Call_Package* ccp = csr->new_call_package();
 ccp->add_new_channel("lambda");

 QString a1 = "Test";
 u4 a2 = 33;
 u1 a3 = 111;

 Chasm_Carrier cc1 = csr->gen_carrier<QString>(&a1);
 Chasm_Carrier cc2 = csr->gen_carrier<u4>(&a2);
 Chasm_Carrier cc3 = csr->gen_carrier<u1>(&a3);

 ccp->add_carriers({cc1,cc2,cc3});

 ccp->add_new_channel("retvalue");

 Chasm_Carrier cc0 = csr->gen_carrier<QString>(csr->Retvalue._QString);
 ccp->add_carrier(cc0);
 csr->evaluate(ccp, 303341_cfc, &testqsq, &cc0);
 QString result = cc0.value<QString>();
 qDebug() << "r = " << result;
}



u4 testqs4(QString arg1, u4 arg2, u1 arg3)
{
 qDebug() << "arg1 = " << arg1;
 qDebug() << "arg2 = " << arg2;
 qDebug() << "arg3 = " << arg3;
 u4 result = arg1.size() + (arg2 % 10) + (arg3 % 10);
 return result * 10000;
}

void run_testqs4(Chasm_Runtime* csr)
{
 Chasm_Call_Package* ccp = csr->new_call_package();
 ccp->add_new_channel("lambda");

 QString a1 = "Test";
 u4 a2 = 33;
 u1 a3 = 111;

 Chasm_Carrier cc1 = csr->gen_carrier<QString>(&a1);
 Chasm_Carrier cc2 = csr->gen_carrier<u4>(&a2);
 Chasm_Carrier cc3 = csr->gen_carrier<u1>(&a3);

 ccp->add_carriers({cc1,cc2,cc3});

 ccp->add_new_channel("retvalue");

 Chasm_Carrier cc0 = csr->gen_carrier<u4>(csr->Retvalue._u4);
 ccp->add_carrier(cc0);
 csr->evaluate(ccp, 304341_cfc, &testqs4, &cc0);
 u4 result = cc0.value<u4>();
 qDebug() << "r = " << result;
}

s4 testqs4n(QString arg1, u4 arg2, u1 arg3)
{
 qDebug() << "arg1 = " << arg1;
 qDebug() << "arg2 = " << arg2;
 qDebug() << "arg3 = " << arg3;
 s4 result = arg1.size() + (arg2 % 10) + (arg3 % 10);
 return -result * 10000;
}

void run_testqs4n(Chasm_Runtime* csr)
{
 Chasm_Call_Package* ccp = csr->new_call_package();
 ccp->add_new_channel("lambda");

 QString a1 = "Test";
 u4 a2 = 33;
 u1 a3 = 111;

 Chasm_Carrier cc1 = csr->gen_carrier<QString>(&a1);
 Chasm_Carrier cc2 = csr->gen_carrier<u4>(&a2);
 Chasm_Carrier cc3 = csr->gen_carrier<u1>(&a3);

 ccp->add_carriers({cc1,cc2,cc3});

 ccp->add_new_channel("retvalue");

 Chasm_Carrier cc0 = csr->gen_carrier<u4>(csr->Retvalue._u4);
 ccp->add_carrier(cc0);
 csr->evaluate(ccp, 304341_cfc, &testqs4n, &cc0);
 s4 result = cc0.value<s4>();
 qDebug() << "r = " << result;
}


QByteArray testqs5(QString arg1, u4 arg2, u1 arg3)
{
 qDebug() << "arg1 = " << arg1;
 qDebug() << "arg2 = " << arg2;
 qDebug() << "arg3 = " << arg3;
 QByteArray result = QString("%1, %2, %3").arg(arg1).arg(arg2).arg(arg3).toLatin1();
 return result;
}

void run_testqs5(Chasm_Runtime* csr)
{
 Chasm_Call_Package* ccp = csr->new_call_package();
 ccp->add_new_channel("lambda");

 QString a1 = "Test";
 u4 a2 = 33;
 u1 a3 = 111;

 Chasm_Carrier cc1 = csr->gen_carrier<QString>(&a1);
 Chasm_Carrier cc2 = csr->gen_carrier<u4>(&a2);
 Chasm_Carrier cc3 = csr->gen_carrier<u1>(&a3);

 ccp->add_carriers({cc1,cc2,cc3});

 ccp->add_new_channel("retvalue");

 Chasm_Carrier cc0 = csr->gen_carrier<QByteArray>(csr->Retvalue._QByteArray);
 ccp->add_carrier(cc0);
 csr->evaluate(ccp, 305341_cfc, &testqs5, &cc0);
 QByteArray result = cc0.value<QByteArray>();
 qDebug() << "r = " << result;
}



float testqs6(QString arg1, u4 arg2, u1 arg3)
{
 qDebug() << "arg1 = " << arg1;
 qDebug() << "arg2 = " << arg2;
 qDebug() << "arg3 = " << arg3;
 float result = ((float) arg1.size()) / (arg1.size() + arg2 + arg3);
 return result;
}

void run_testqs6(Chasm_Runtime* csr)
{
 Chasm_Call_Package* ccp = csr->new_call_package();
 ccp->add_new_channel("lambda");

 QString a1 = "Test";
 u4 a2 = 33;
 u1 a3 = 111;

 Chasm_Carrier cc1 = csr->gen_carrier<QString>(&a1);
 Chasm_Carrier cc2 = csr->gen_carrier<u4>(&a2);
 Chasm_Carrier cc3 = csr->gen_carrier<u1>(&a3);

 ccp->add_carriers({cc1,cc2,cc3});

 ccp->add_new_channel("retvalue");

 Chasm_Carrier cc0 = csr->gen_carrier<r8>(csr->Retvalue._r8);
 ccp->add_carrier(cc0);
 csr->evaluate(ccp, 306341_cfc, &testqs6, &cc0);
 QVariant result = cc0.value<float>();
 qDebug() << "r = " << result;
}


r8 testqs6n(QString arg1, u4 arg2, u1 arg3)
{
 qDebug() << "arg1 = " << arg1;
 qDebug() << "arg2 = " << arg2;
 qDebug() << "arg3 = " << arg3;
 r8 result = ((r8) arg1.size()) / (arg1.size() + arg2 + arg3);
 return -result;
}

void run_testqs6n(Chasm_Runtime* csr)
{
 Chasm_Call_Package* ccp = csr->new_call_package();
 ccp->add_new_channel("lambda");

 QString a1 = "Test";
 u4 a2 = 33;
 u1 a3 = 111;

 Chasm_Carrier cc1 = csr->gen_carrier<QString>(&a1);
 Chasm_Carrier cc2 = csr->gen_carrier<u4>(&a2);
 Chasm_Carrier cc3 = csr->gen_carrier<u1>(&a3);

 ccp->add_carriers({cc1,cc2,cc3});

 ccp->add_new_channel("retvalue");

 Chasm_Carrier cc0 = csr->gen_carrier<r8>(csr->Retvalue._r8);
 ccp->add_carrier(cc0);
 csr->evaluate(ccp, 306341_cfc, &testqs6n, &cc0);
 QVariant result = cc0.value<r8>();
 qDebug() << "r = " << result;
}

QVariant testqsv(QString arg1, u4 arg2, u1 arg3)
{
 qDebug() << "arg1 = " << arg1;
 qDebug() << "arg2 = " << arg2;
 qDebug() << "arg3 = " << arg3;
 QString result = QString("%1, %2, %3").arg(arg1).arg(arg2).arg(arg3).toLatin1();
 return QVariant::fromValue(result);
}

void run_testqsv(Chasm_Runtime* csr)
{
 Chasm_Call_Package* ccp = csr->new_call_package();
 ccp->add_new_channel("lambda");

 QString a1 = "Test";
 u4 a2 = 33;
 u1 a3 = 111;

 Chasm_Carrier cc1 = csr->gen_carrier<QString>(&a1);
 Chasm_Carrier cc2 = csr->gen_carrier<u4>(&a2);
 Chasm_Carrier cc3 = csr->gen_carrier<u1>(&a3);

 ccp->add_carriers({cc1,cc2,cc3});

 ccp->add_new_channel("retvalue");

 Chasm_Carrier cc0 = csr->gen_carrier<QVariant>(csr->Retvalue._QVariant);
 ccp->add_carrier(cc0);
 csr->evaluate(ccp, 307341_cfc, &testqsv, &cc0);
 QVariant result = cc0.value<QVariant>();
 qDebug() << "r = " << result;
}



n8 testqs8(QString arg1, u4 arg2, u1 arg3)
{
 qDebug() << "arg1 = " << arg1;
 qDebug() << "arg2 = " << arg2;
 qDebug() << "arg3 = " << arg3;
 n8 result = arg1.size() + (arg2 % 10) + (arg3 % 10);
 return result * 10000000;
}

void run_testqs8(Chasm_Runtime* csr)
{
 Chasm_Call_Package* ccp = csr->new_call_package();
 ccp->add_new_channel("lambda");

 QString a1 = "Test";
 u4 a2 = 33;
 u1 a3 = 111;

 Chasm_Carrier cc1 = csr->gen_carrier<QString>(&a1);
 Chasm_Carrier cc2 = csr->gen_carrier<u4>(&a2);
 Chasm_Carrier cc3 = csr->gen_carrier<u1>(&a3);

 ccp->add_carriers({cc1,cc2,cc3});

 ccp->add_new_channel("retvalue");

 Chasm_Carrier cc0 = csr->gen_carrier<n8>(csr->Retvalue._n8);
 ccp->add_carrier(cc0);
 csr->evaluate(ccp, 308341_cfc, &testqs8, &cc0);
 n8 result = cc0.value<n8>();
 qDebug() << "r = " << result;
}




QString* testqsp(QString arg1, u4 arg2, u1 arg3)
{
 qDebug() << "arg1 = " << arg1;
 qDebug() << "arg2 = " << arg2;
 qDebug() << "arg3 = " << arg3;
 QString result = QString("%1, %2, %3").arg(arg1).arg(arg2).arg(arg3).toLatin1();
 return new QString(result);
}

void run_testqsp(Chasm_Runtime* csr)
{
 Chasm_Call_Package* ccp = csr->new_call_package();
 ccp->add_new_channel("lambda");

 QString a1 = "Test";
 u4 a2 = 33;
 u1 a3 = 111;

 Chasm_Carrier cc1 = csr->gen_carrier<QString>(&a1);
 Chasm_Carrier cc2 = csr->gen_carrier<u4>(&a2);
 Chasm_Carrier cc3 = csr->gen_carrier<u1>(&a3);

 ccp->add_carriers({cc1,cc2,cc3});

 ccp->add_new_channel("retvalue");

 Chasm_Carrier cc0 = csr->gen_carrier<void*>();
 ccp->add_carrier(cc0);
 csr->evaluate(ccp, 309341_cfc, &testqsp, &cc0);
 QString* result = (QString*) cc0.value<void*>();
 qDebug() << "r = " << *result;
}




QString* testqsb(QString arg1, bool arg2, bool& arg3)
{
 qDebug() << "arg1 = " << arg1;
 qDebug() << "arg2 = " << arg2;
 qDebug() << "arg3 = " << arg3;
 QString result = QString("%1, %2, %3").arg(arg1).arg(arg2).arg(arg3).toLatin1();
 arg3 = !arg3;
 return new QString(result);
}

void run_testqsb(Chasm_Runtime* csr)
{
 Chasm_Call_Package* ccp = csr->new_call_package();
 ccp->add_new_channel("lambda");

 QString a1 = "A1";
 bool a2 = true;
 bool a3 = false;

 Chasm_Carrier cc1 = csr->gen_carrier<QString>(&a1);
 Chasm_Carrier cc2 = csr->gen_carrier<u1>(&a2);
 Chasm_Carrier cc3 = csr->gen_carrier<n8&>(&a3);

 ccp->add_carriers({cc1,cc2,cc3});

 ccp->add_new_channel("retvalue");
 Chasm_Carrier cc0 = csr->gen_carrier<void*>(csr->Retvalue._ptr);
 ccp->add_carrier(cc0);

 csr->evaluate(ccp, 309310_cfc, &testqsb, &cc0);
 qDebug() << "a3 = " << a3;
 QString result = cc0.value<QString>();
 qDebug() << "r = " << result;
}


enum class test_enum { E1, E2, E3 };

void teste(QStringList* arg1, u4* arg2, test_enum arg3)
{
 qDebug() << "arg1 = " << *arg1;
 qDebug() << "arg2 = " << *arg2;
 qDebug() << "arg3 = " << (u1) arg3;
 ++*arg2;
}

void run_teste(Chasm_Runtime* csr)
{
 Chasm_Call_Package* ccp = csr->new_call_package();
 ccp->add_new_channel("lambda");

 QStringList* a1 = new QStringList({"Ptr", "A2"});
 u4* a2 = new u4(92300);
 test_enum a3 = test_enum::E3;

 Chasm_Carrier cc1 = csr->gen_carrier<void*>(&a1);
 Chasm_Carrier cc2 = csr->gen_carrier<void*>(&a2);
 Chasm_Carrier cc3 = csr->gen_carrier<u1>(&a3);


 ccp->add_carriers({cc1,cc2,cc3});
 csr->evaluate(ccp, 300991_cfc, &teste);
 qDebug() << "a2 = " << *a2;
}


void testf(QStringList& arg1, test_enum& arg2, double& arg3)
{
 qDebug() << "arg1 = " << arg1;
 qDebug() << "arg2 = " << (u1) arg2;
 qDebug() << "arg3 = " << arg3;
 arg1.first().prepend("(");
 arg1.first().append(")");

 arg1.append("OK");

 arg2 = test_enum::E2;

 arg3 = 0.12345;
}


void run_testf(Chasm_Runtime* csr)
{
 Chasm_Call_Package* ccp = csr->new_call_package();
 ccp->add_new_channel("lambda");

 QStringList a1 {"Ptr", "A2"};
 test_enum a2 = test_enum::E3;
 double a3 = 0.98765;

 Chasm_Carrier cc1 = csr->gen_carrier<n8&>(&a1);
 Chasm_Carrier cc2 = csr->gen_carrier<n8&>(&a2);
 Chasm_Carrier cc3 = csr->gen_carrier<n8&>(&a3);

 ccp->add_carriers({cc1,cc2,cc3});
 csr->evaluate(ccp, 3000_cfc, &testf);
 qDebug() << "a1 = " << a1;
 qDebug() << "a2 = " << (u1) a2;
 qDebug() << "a3 = " << a3;
}


void testf4(QString arg1, QString arg2, QString arg3, QString arg4)
{
 qDebug() << "arg1 = " << arg1;
 qDebug() << "arg2 = " << arg2;
 qDebug() << "arg3 = " << arg3;
 qDebug() << "arg4 = " << arg4;
}


void run_testf4(Chasm_Runtime* csr)
{
 Chasm_Call_Package* ccp = csr->new_call_package();
 ccp->add_new_channel("lambda");

 QString a1 = "A1";
 QString a2 = "A2";
 QString a3 = "A3";
 QString a4 = "A4";

 Chasm_Carrier cc1 = csr->gen_carrier<QString>(&a1);
 Chasm_Carrier cc2 = csr->gen_carrier<QString>(&a2);
 Chasm_Carrier cc3 = csr->gen_carrier<QString>(&a3);
 Chasm_Carrier cc4 = csr->gen_carrier<QString>(&a4);

 ccp->add_carriers({cc1,cc2,cc3,cc4});
 csr->evaluate(ccp, 4003_cfc, &testf4);
}

void testf5(u1 arg1, u1 arg2, u1 arg3, u1 arg4, u1 arg5)
{
 qDebug() << "arg1 = " << arg1;
 qDebug() << "arg2 = " << arg2;
 qDebug() << "arg3 = " << arg3;
 qDebug() << "arg4 = " << arg4;
 qDebug() << "arg5 = " << arg5;
}


void run_testf5(Chasm_Runtime* csr)
{
 Chasm_Call_Package* ccp = csr->new_call_package();
 ccp->add_new_channel("lambda");

 u1 a1 = 11;
 u1 a2 = 12;
 u1 a3 = 13;
 u1 a4 = 14;
 u1 a5 = 15;

 Chasm_Carrier cc1 = csr->gen_carrier<u1>(&a1);
 Chasm_Carrier cc2 = csr->gen_carrier<u1>(&a2);
 Chasm_Carrier cc3 = csr->gen_carrier<u1>(&a3);
 Chasm_Carrier cc4 = csr->gen_carrier<u1>(&a4);
 Chasm_Carrier cc5 = csr->gen_carrier<u1>(&a5);

 ccp->add_carriers({cc1,cc2,cc3,cc4,cc5});
 csr->evaluate(ccp, 5001_cfc, &testf5);
}



void test2(bool arg1, s2 arg2, s2& arg3)
{
 qDebug() << "arg1 = " << arg1;
 qDebug() << "arg2 = " << arg2;
 qDebug() << "arg3 = " << arg3;
 --arg3;
}

void run_test2(Chasm_Runtime* csr)
{
 Chasm_Call_Package* ccp = csr->new_call_package();
 ccp->add_new_channel("lambda");

 bool a1 = "true";
 s2 a2 = -533;
 s2 a3 = -211;

 Chasm_Carrier cc1 = csr->gen_carrier<u1>(&a1);
 Chasm_Carrier cc2 = csr->gen_carrier<u2>(&a2);
 Chasm_Carrier cc3 = csr->gen_carrier<n8&>(&a3);

 ccp->add_carriers({cc1,cc2,cc3});
 csr->evaluate(ccp, 300120_cfc, &test2);
 qDebug() << "a3 = " << a3;
}



//#define run_s0_3_r0(a,b,c,d,e)


struct test_qpr
{
 QString qs;
 u4 uu;
 ~test_qpr()
 {
  qDebug() << "~test qpr";
 }

 QPair<QString, u4> to_pr() { return {qs, uu}; }
};



QPoint* test_smart(test_qpr& arg1, //QPair<QString, u4>& arg1,  //test_qpr& arg1,
                   QPoint& arg2, QStringList* arg3)
{
 qDebug() << "arg1 = " << arg1.to_pr();
 qDebug() << "arg2 = " << arg2;
 qDebug() << "arg3 = " << *arg3;
 return new QPoint(600,601);
}


void pre_run_smart(Chasm_Runtime* csr, QVector<Chasm_Typed_Value_Representation>& args)
{
 Chasm_Type_Object* ref_type_shared = csr->type_system().get_type_object_by_name("n8&!");
 Chasm_Type_Object* pVoid_type = csr->type_system().get_type_object_by_name("void*");
 Chasm_Type_Object* ref_type = csr->type_system().get_type_object_by_name("n8&");

 QString a11 = "Test";
 u4 a12 = 33;

 test_qpr* a1 = new test_qpr{a11, a12};
 args.push_back( ref_type_shared->make_instance(a1) );
 // args.push_back( ref_type_shared->with_instance(_a1) );

 QPoint* a2 = new QPoint(500,501);
 args.push_back( ref_type_shared->make_instance(a2) );


 QStringList* qsl = new QStringList{"qsl1", "qsl2"};

 args.push_back( pVoid_type->with_instance(qsl) );

}

void run_smart(Chasm_Runtime* csr, QVector<Chasm_Typed_Value_Representation>& args)
{
 Chasm_Call_Package* ccp = csr->new_call_package();
 ccp->add_new_channel("lambda");


 Chasm_Carrier cc1 = csr->gen_carrier(args[0]);
 Chasm_Carrier cc2 = csr->gen_carrier(args[1]);
 Chasm_Carrier cc3 = csr->gen_carrier(args[2]);

 ccp->add_carriers({cc1,cc2,cc3});

 ccp->add_new_channel("retvalue");

 Chasm_Carrier cc0 = csr->gen_carrier<u4>(csr->Retvalue._ptr);
 ccp->add_carrier(cc0);
 csr->evaluate(ccp, 309009_cfc, &test_smart, &cc0);
 QPoint* result = cc0.value<QPoint*>();
 qDebug() << "r = " << *result;

 csr->release(ccp);
}


void run_smart(Chasm_Runtime* csr)
{
 Chasm_Call_Package* ccp = csr->new_call_package();
 ccp->add_new_channel("lambda");

 QString a11 = "Test";
 u4 a12 = 33;
 test_qpr* a1 = new test_qpr{a11, a12};

 QPoint* a2 = new QPoint(500,501);
 QStringList* qsl = new QStringList{"qsl1", "qsl2"};


 Chasm_Carrier cc1 = csr->gen_carrier<n8&>(a1);
 Chasm_Carrier cc2 = csr->gen_carrier<n8&>(a2);
 Chasm_Carrier cc3 = csr->gen_carrier<void*>(&qsl);

 ccp->add_carriers({cc1,cc2,cc3});

 ccp->add_new_channel("retvalue");

 Chasm_Carrier cc0 = csr->gen_carrier<void*>(csr->Retvalue._ptr);
 ccp->add_carrier(cc0);
 csr->evaluate(ccp, 309009_cfc, &test_smart, &cc0);
 QPoint* result = cc0.value<QPoint*>();
 qDebug() << "r = " << *result;

 csr->release(ccp);
}



void test2arg(bool arg1, s2& arg2)
{
 qDebug() << "arg1 = " << arg1;
 qDebug() << "arg2 = " << arg2;
 --arg2;
}

void run_test2arg(Chasm_Runtime* csr)
{
 Chasm_Call_Package* ccp = csr->new_call_package();
 ccp->add_new_channel("lambda");

 bool a1 = "true";
 s2 a2 = -533;

 Chasm_Carrier cc1 = csr->gen_carrier<u1>(&a1);
 Chasm_Carrier cc2 = csr->gen_carrier<n8&>(&a2);

 ccp->add_carriers({cc1,cc2});
 csr->evaluate(ccp, 20010_cfc, &test2arg);
 qDebug() << "a2 = " << a2;
}


void test1arg(s2& arg1)
{
 qDebug() << "arg1 = " << arg1;
 --arg1;
}

void run_test1arg(Chasm_Runtime* csr)
{
 Chasm_Call_Package* ccp = csr->new_call_package();
 ccp->add_new_channel("lambda");

 s2 a1 = -533;

 Chasm_Carrier cc1 = csr->gen_carrier<n8&>(&a1);

 ccp->add_carriers({cc1});
 csr->evaluate(ccp, 1000_cfc, &test1arg);
 qDebug() << "a1 = " << a1;
}


void test0arg()
{
 qDebug() << "0 arg";
}

void run_test0arg(Chasm_Runtime* csr)
{
 Chasm_Call_Package* ccp = csr->new_call_package();
 csr->evaluate(ccp, 0_cfc, &test0arg);
}


QStringList* test0r9()
{
 QStringList* result = new QStringList;
 (*result) << "qsl1" << "qsl2";
 return result;
}

void run_test0r9(Chasm_Runtime* csr)
{
 Chasm_Call_Package* ccp = csr->new_call_package();

 ccp->add_new_channel("retvalue");
 Chasm_Carrier cc0 = csr->gen_carrier<void*>(csr->Retvalue._ptr);
 ccp->add_carrier(cc0);

 csr->evaluate(ccp, 9_cfc, &test0r9, &cc0);
 QStringList* result = cc0.value<QStringList*>();
 qDebug() << "r = " << *result;

}


struct test0s1
{
 QStringList qsl;

 void test()
 {
  QStringList* result = new QStringList(qsl);
  (*result) << "_qsl1" << "_qsl2";
  qDebug() << "new string list: " << *result;
 }

 QStringList* testr()
 {
  QStringList* result = new QStringList(qsl);
  (*result) << "_qsl1" << "_qsl2";
  return result;
 }

 void test1(n8 arg)
 {
  QStringList* result = new QStringList(qsl);
  (*result) << "_qsl1" << "_qsl2" << QString::number(arg);
  qDebug() << "new string list: " << *result;
 }

 u1 test1r(n8 arg)
 {
  QStringList* result = new QStringList(qsl);
  (*result) << "_qsl1" << "_qsl2" << QString::number(arg);
  qDebug() << "new string list: " << *result;
  return 123;
 }

 void test2(u4 a1, u1 a2)
 {
  qDebug() << QString("Ratio: %1").arg(a1 / (a2 + 1));
 }

 r8 test2r(u4 a1, n8 a2)
 {
  return (r8) a1 / (a2 + 1);
 }

 void test3(QString a1, u2 a2, QVariant a3)
 {
  qDebug() << QString("%1: %2").arg(a1).arg( (r8) a2 / (a3.toInt() + 1) );
 }

 r8* test3r(u4 a1, u2 a2, bool a3)
 {
  if(a3)
    return new r8( (r8) a1 / a2);
  return nullptr;
 }

 void test4(n8 a1, QString a2, n8 a3, u2& a4)
 {
  qDebug() << QString("%1 %2").arg(a2).arg(a1 + a3);
  a4 = a1 - a3;
 }

 u1 test4r(QString a1, QByteArray a2, QVariant a3, QString a4)
 {
  qDebug() << a1 << "," << a2 << a3.toStringList() << a4;
  return true;
 }

 void test62(r8 a1, r8 a2, u1 a3, u1 a4, u1 a5, u1 a6)
 {
  QString result = QString("%1, %2, %3, %4, %5, %6")
    .arg(a1).arg(a2).arg(a3).arg(a4).arg(a5).arg(a6);
  qDebug() << "result = " << result;
 }

 QByteArray test62r(const r8& a1, r8& a2, u1 a3, u1 a4, u1 a5, u1 a6)
 {
  QString result = QString("%1, %2, %3, %4, %5, %6")
    .arg(a1).arg(a2).arg(a3).arg(a4).arg(a5).arg(a6);
  a2 *= 4;
  qDebug() << "result = " << result;
  QByteArray r = result.toLatin1();
  return r;
 }

};

void run_test0s1(Chasm_Runtime* csr)
{
 Chasm_Call_Package* ccp = csr->new_call_package();

// ccp->add_new_channel("retvalue");

 ccp->add_new_channel("sigma");
 test0s1 ts1{{"q1", "q2"}};

 test0s1* arg1 = &ts1;

 Chasm_Carrier cc0 = csr->gen_carrier<void*>(&arg1);
 ccp->add_carrier(cc0);

 //csr->evaluate(ccp, 80, (minimal_fn_s1_type) &test0s1::test);

 csr->evaluate(ccp, 10_cfc, //(minimal_fn_s1_type)
   &test0s1::test);


 //QStringList* result = cc0.value<QStringList*>();
 //qDebug() << "r = " << *result;

}


void run_test0s1r(Chasm_Runtime* csr)
{
 Chasm_Call_Package* ccp = csr->new_call_package();


 ccp->add_new_channel("sigma");
 test0s1 ts1{{"q1", "q2"}};

 test0s1* arg1 = &ts1;

 Chasm_Carrier cc_this = csr->gen_carrier<void*>(&arg1);
 ccp->add_carrier(cc_this);

 ccp->add_new_channel("retvalue");
 Chasm_Carrier cc0 = csr->gen_carrier<void*>(csr->Retvalue._ptr);
 ccp->add_carrier(cc0);

 csr->evaluate(ccp, 19_cfc, //(minimal_fn_s1_type)
               &test0s1::testr, &cc0);

// csr->evaluate_s1(ccp, 89, (minimal_fn_s1_type) &test0s1::testr, &cc0);

// csr->evaluate_s01(ccp, 89, (minimal_fn_s1_type) &test0s1::testr, &cc0);

 QStringList* result = cc0.value<QStringList*>();
 qDebug() << "r = " << *result;
}




QStringList* teste4(QString start, QVector<u4>& nums, u2 c1, QChar c2)
{
 QStringList* result = new QStringList(start);
 u2 i = 0;
 for(u4 n: nums)
 {
  ++i;
  (*result) << QString("%1=%2").arg(i).arg(n, c1, 10, QChar(c2) );
 }
 return result;
}

void run_teste4(Chasm_Runtime* csr)
{
 Chasm_Call_Package* ccp = csr->new_call_package();


 ccp->add_new_channel("lambda");

 QString a1 = "true";
 QVector<u4> nums {12, 144, 542, 5578};
 u2 fw = 10;
 u2 ch = '*';

 Chasm_Carrier cc1 = csr->gen_carrier<QString>(&a1);
 Chasm_Carrier cc2 = csr->gen_carrier<n8&>(&nums);
 Chasm_Carrier cc3 = csr->gen_carrier<u2>(&fw);
 Chasm_Carrier cc4 = csr->gen_carrier<u2>(&ch);

 ccp->add_carriers({cc1,cc2,cc3,cc4});

 ccp->add_new_channel("retvalue");

 Chasm_Carrier cc0 = csr->gen_carrier<void*>(csr->Retvalue._ptr);
 ccp->add_carrier(cc0);

 csr->evaluate(ccp, 4093022_cfc, //(minimal_fn_s0_re4_type)
         &teste4, &cc0);

 QStringList* result = cc0.value<QStringList*>();
 qDebug() << "r = " << *result;
}



QStringList* teste3(QString start, QVector<u4>& nums, u2 c1)
{
 QStringList* result = new QStringList(start);
 u2 i = 0;
 for(u4 n: nums)
 {
  ++i;
  (*result) << QString("%1=%2").arg(i).arg(n, c1, 10, QLatin1Char('@') );
 }
 return result;
}

void run_teste3(Chasm_Runtime* csr)
{
 Chasm_Call_Package* ccp = csr->new_call_package();


 ccp->add_new_channel("lambda");

 QString a1 = "true";
 QVector<u4> nums {12, 144, 542, 5578};
 u2 fw = 10;

 Chasm_Carrier cc1 = csr->gen_carrier<QString>(&a1);
 Chasm_Carrier cc2 = csr->gen_carrier<n8&>(&nums);
 Chasm_Carrier cc3 = csr->gen_carrier<u2>(&fw);

 ccp->add_carriers({cc1,cc2,cc3});

 ccp->add_new_channel("retvalue");

 Chasm_Carrier cc0 = csr->gen_carrier<void*>(csr->Retvalue._ptr);
 ccp->add_carrier(cc0);

 csr->evaluate(ccp, 309302_cfc, //(minimal_fn_s0_re4_type)
         &teste3, &cc0);

 QStringList* result = cc0.value<QStringList*>();
 qDebug() << "r = " << *result;
}




QStringList* teste4of1(QString start, QString start1, QString start2, QString start3)
{
 QStringList* result = new QStringList({start, start1, start2, start3});
 return result;
}

void run_teste4of1(Chasm_Runtime* csr)
{
 Chasm_Call_Package* ccp = csr->new_call_package();


 ccp->add_new_channel("lambda");

 QString a1 = "true";
 QString a2 = "false";
 QString a3 = "maybe";
 QString a4 = "unknown";

 Chasm_Carrier cc1 = csr->gen_carrier<QString>(&a1);
 Chasm_Carrier cc2 = csr->gen_carrier<QString>(&a2);
 Chasm_Carrier cc3 = csr->gen_carrier<QString>(&a3);
 Chasm_Carrier cc4 = csr->gen_carrier<QString>(&a4);

 ccp->add_carriers({cc1,cc2,cc3,cc4});

 ccp->add_new_channel("retvalue");

 Chasm_Carrier cc0 = csr->gen_carrier<void*>(csr->Retvalue._ptr);
 ccp->add_carrier(cc0);

 csr->evaluate(ccp, 4093_cfc, //(minimal_fn_s0_re4_type)
         &teste4of1, &cc0);


 QStringList* result = cc0.value<QStringList*>();
 qDebug() << "r = " << *result;
}


QVector<r8>* teste4of2(u1 a11, u2 a12, u1 a21, u2 a22)
{
 QVector<r8>* result = new QVector<r8>({(r8)a11/a12, (r8)a21/a22});
 return result;
}

void run_teste4of2(Chasm_Runtime* csr)
{
 Chasm_Call_Package* ccp = csr->new_call_package();


 ccp->add_new_channel("lambda");

 u1 a1 = 200;
 u2 a2 = 400;
 u1 a3 = 250;
 u2 a4 = 1000;

 Chasm_Carrier cc1 = csr->gen_carrier<u1>(&a1);
 Chasm_Carrier cc2 = csr->gen_carrier<u2>(&a2);
 Chasm_Carrier cc3 = csr->gen_carrier<u1>(&a3);
 Chasm_Carrier cc4 = csr->gen_carrier<u2>(&a4);

 ccp->add_carriers({cc1,cc2,cc3,cc4});

 ccp->add_new_channel("retvalue");

 Chasm_Carrier cc0 = csr->gen_carrier<void*>(csr->Retvalue._ptr);
 ccp->add_carrier(cc0);

 csr->evaluate(ccp, 4091212_cfc, &teste4of2, &cc0);

 QVector<r8>* result = cc0.value<QVector<r8>*>();
 qDebug() << "r = " << *result;
}




QStringList* teste5of2(QString start, u4 xx, QString start1, QString start2, u4 yy)
{
 QStringList* result = new QStringList({start, start1, start2, QString::number(xx + yy)});
 return result;
}

void run_teste5of2(Chasm_Runtime* csr)
{
 Chasm_Call_Package* ccp = csr->new_call_package();


 ccp->add_new_channel("lambda");

 QString a1 = "true";
 u4 a2 = 123456789;
 QString a3 = "maybe";
 QString a4 = "unknown";
 u4 a5 = 345678912;

 Chasm_Carrier cc1 = csr->gen_carrier<QString>(&a1);
 Chasm_Carrier cc2 = csr->gen_carrier<u4>(&a2);
 Chasm_Carrier cc3 = csr->gen_carrier<QString>(&a3);
 Chasm_Carrier cc4 = csr->gen_carrier<QString>(&a4);
 Chasm_Carrier cc5 = csr->gen_carrier<u4>(&a5);

 ccp->add_carriers({cc1,cc2,cc3,cc4,cc5});

 ccp->add_new_channel("retvalue");

 Chasm_Carrier cc0 = csr->gen_carrier<void*>(csr->Retvalue._ptr);
 ccp->add_carrier(cc0);

 csr->evaluate(ccp, 50934334_cfc, //(minimal_fn_s0_re4_type)
         &teste5of2, &cc0);

 QStringList* result = cc0.value<QStringList*>();
 qDebug() << "r = " << *result;
}


QStringList* test0()
{
 QStringList* result = new QStringList({"start", "start1", "start2"});
 return result;
}

void run_test0(Chasm_Runtime* csr)
{
 Chasm_Call_Package* ccp = csr->new_call_package();

 ccp->add_new_channel("retvalue");

 Chasm_Carrier cc0 = csr->gen_carrier<void*>(csr->Retvalue._ptr);
 ccp->add_carrier(cc0);

 csr->evaluate(ccp, 9_cfc, //(minimal_fn_s0_re4_type)
         &test0, &cc0);

 QStringList* result = cc0.value<QStringList*>();
 qDebug() << "r = " << *result;
}


void test00()
{
 qDebug() << "In test00 ...";
}

void run_test00(Chasm_Runtime* csr)
{
 Chasm_Call_Package* ccp = csr->new_call_package();

 csr->evaluate(ccp, 0_cfc, &test00);
}


r8 teste2of2(u1 x, n8 y)
{
 return ((r8) x) / y;
}

r8 teste2of2rev(n8 x, u1 y)
{
 return ((r8) x) / y;
}


void run_teste2of2(Chasm_Runtime* csr)
{
 Chasm_Call_Package* ccp = csr->new_call_package();

 ccp->add_new_channel("lambda");

 u1 a1 = 12;
 n8 a2 = 1200000000000;

 Chasm_Carrier cc1 = csr->gen_carrier<u1>(&a1);
 Chasm_Carrier cc2 = csr->gen_carrier<n8>(&a2);

 ccp->add_carriers({cc1,cc2});

 ccp->add_new_channel("retvalue");

 Chasm_Carrier cc0 = csr->gen_carrier<r8>(csr->Retvalue._r8);
 ccp->add_carrier(cc0);

 csr->evaluate(ccp, 20618_cfc, &teste2of2, &cc0);

 r8 result = cc0.value<r8>();
 qDebug() << "r = " << result;
}

void run_teste2of2rev(Chasm_Runtime* csr)
{
 Chasm_Call_Package* ccp = csr->new_call_package();

 ccp->add_new_channel("lambda");

 n8 a1 = 1200000000000;
 u1 a2 = 12;

 Chasm_Carrier cc1 = csr->gen_carrier<n8>(&a1);
 Chasm_Carrier cc2 = csr->gen_carrier<u1>(&a2);

 ccp->add_carriers({cc1,cc2});

 ccp->add_new_channel("retvalue");

 Chasm_Carrier cc0 = csr->gen_carrier<r8>(csr->Retvalue._r8);
 ccp->add_carrier(cc0);

 csr->evaluate(ccp, 20681_cfc, //(minimal_fn_s0_re4_type)
         &teste2of2rev, &cc0);

 r8 result = cc0.value<r8>();
 qDebug() << "r = " << result;
}



void run_test1s1(Chasm_Runtime* csr)
{
 Chasm_Call_Package* ccp = csr->new_call_package();

 ccp->add_new_channel("sigma");
 test0s1 ts1{{"q1", "q2"}};

 test0s1* arg = &ts1;
 Chasm_Carrier cc0 = csr->gen_carrier<void*>(&arg);
 ccp->add_carrier(cc0);

 ccp->add_new_channel("lambda");
 n8 a1 = 12000;
 Chasm_Carrier cc1 = csr->gen_carrier<n8>(&a1);
 ccp->add_carrier(cc1);

 csr->evaluate(ccp, 1108_cfc, //(minimal_fn_s1_type)
   &test0s1::test1);

}


void run_test1s1r(Chasm_Runtime* csr)
{
 Chasm_Call_Package* ccp = csr->new_call_package();

 ccp->add_new_channel("sigma");
 test0s1 ts1{{"q1", "q2"}};

 test0s1* arg = &ts1;
 Chasm_Carrier cc0 = csr->gen_carrier<void*>(&arg);
 ccp->add_carrier(cc0);


 ccp->add_new_channel("lambda");
 n8 a1 = 1200;
 //n8* arg1 = &a1;
 Chasm_Carrier cc1 = csr->gen_carrier<n8>(&a1);
 ccp->add_carrier(cc1);


 ccp->add_new_channel("retvalue");
 Chasm_Carrier ccr = csr->gen_carrier<void*>(csr->Retvalue._ptr);
 ccp->add_carrier(ccr);

 csr->evaluate(ccp, 1118_cfc, //(minimal_fn_s1_type)
               &test0s1::test1r, &cc0);

 u1 result = cc0.value<u1>();
 qDebug() << "r = " << result;
}


void run_test2s1(Chasm_Runtime* csr)
{
 Chasm_Call_Package* ccp = csr->new_call_package();

 ccp->add_new_channel("sigma");
 test0s1 ts1{{"q1", "q2"}};

 test0s1* arg = &ts1;

 Chasm_Carrier cc0 = csr->gen_carrier<void*>(&arg);
 ccp->add_carrier(cc0);

 ccp->add_new_channel("lambda");
 u4 a1 = 87000;
 u1 a2 = 201;


 Chasm_Carrier cc1 = csr->gen_carrier<u4>(&a1);
 Chasm_Carrier cc2 = csr->gen_carrier<u1>(&a2);


 ccp->add_carriers({cc1,cc2});

 csr->evaluate(ccp, 21042_cfc, //(minimal_fn_s1_type)
   &test0s1::test2);
}


void run_test2s1r(Chasm_Runtime* csr)
{
 Chasm_Call_Package* ccp = csr->new_call_package();

 ccp->add_new_channel("sigma");
 test0s1 ts1{{"q1", "q2"}};

 test0s1* arg = &ts1;
 Chasm_Carrier cc0 = csr->gen_carrier<void*>(&arg);
 ccp->add_carrier(cc0);

 ccp->add_new_channel("lambda");
 u4 a1 = 88002;
 n8 a2 = 44000;


 Chasm_Carrier cc1 = csr->gen_carrier<u4>(&a1);
 Chasm_Carrier cc2 = csr->gen_carrier<n8>(&a2);

 ccp->add_carriers({cc1,cc2});


 ccp->add_new_channel("retvalue");
 Chasm_Carrier ccr = csr->gen_carrier<r8>(csr->Retvalue._r8);
 ccp->add_carrier(ccr);

 csr->evaluate(ccp, 21648_cfc, //(minimal_fn_s1_type)
               &test0s1::test2r, &ccr);

 r8 result = ccr.value<r8>();
 qDebug() << "r = " << result;
}



void run_test3s1(Chasm_Runtime* csr)
{
 Chasm_Call_Package* ccp = csr->new_call_package();

 ccp->add_new_channel("sigma");
 test0s1 ts1{{"q1", "q2"}};

 test0s1* arg = &ts1;

 Chasm_Carrier cc0 = csr->gen_carrier<void*>(&arg);
 ccp->add_carrier(cc0);

 ccp->add_new_channel("lambda");
 QString a1 = "qs";
 u2 a2 = 32;
 QVariant a3 = QVariant::fromValue(63);


 Chasm_Carrier cc1 = csr->gen_carrier<QString>(&a1);
 Chasm_Carrier cc2 = csr->gen_carrier<u2>(&a2);
 Chasm_Carrier cc3 = csr->gen_carrier<QVariant>(&a3);


 ccp->add_carriers({cc1,cc2,cc3});

 csr->evaluate(ccp, 310327_cfc, //(minimal_fn_s1_type)
   &test0s1::test3);
}


void run_test3s1r(Chasm_Runtime* csr)
{
 Chasm_Call_Package* ccp = csr->new_call_package();

 ccp->add_new_channel("sigma");
 test0s1 ts1{{"q1", "q2"}};

 test0s1* arg = &ts1;

 Chasm_Carrier cc0 = csr->gen_carrier<void*>(&arg);
 ccp->add_carrier(cc0);

 ccp->add_new_channel("lambda");

 //r8* test3r(u4 a1, u2 a2, bool a3

 u4 a1 = 11;
 u2 a2 = 33;
 bool a3 = true;


 Chasm_Carrier cc1 = csr->gen_carrier<u4>(&a1);
 Chasm_Carrier cc2 = csr->gen_carrier<u2>(&a2);
 Chasm_Carrier cc3 = csr->gen_carrier<u1>(&a3);


 ccp->add_carriers({cc1,cc2,cc3});


 ccp->add_new_channel("retvalue");
 Chasm_Carrier ccr = csr->gen_carrier<void*>(csr->Retvalue._ptr);
 ccp->add_carrier(ccr);

 csr->evaluate(ccp, 319421_cfc, &test0s1::test3r, &ccr);

 r8* result = ccr.value<r8*>();
 qDebug() << "r = " << *result;
}


void run_test4s1(Chasm_Runtime* csr)
{
 Chasm_Call_Package* ccp = csr->new_call_package();

 ccp->add_new_channel("sigma");
 test0s1 ts1{{"q1", "q2"}};

 test0s1* arg = &ts1;

 Chasm_Carrier cc0 = csr->gen_carrier<void*>(&arg);
 ccp->add_carrier(cc0);

 ccp->add_new_channel("lambda");
 n8 a1 = 222;
 QString a2 = "sum:";
 n8 a3 = 200;
 u2 a4;

 Chasm_Carrier cc1 = csr->gen_carrier<n8>(&a1);
 Chasm_Carrier cc2 = csr->gen_carrier<QString>(&a2);
 Chasm_Carrier cc3 = csr->gen_carrier<n8>(&a3);
 Chasm_Carrier cc4 = csr->gen_carrier<n8&>(&a4);


 ccp->add_carriers({cc1,cc2,cc3,cc4});

 csr->evaluate(ccp, 4108380_cfc, //(minimal_fn_s1_type)
   &test0s1::test4);

 qDebug() << "a4 = " << a4;
}


void run_test4s1r(Chasm_Runtime* csr)
{
 Chasm_Call_Package* ccp = csr->new_call_package();

 ccp->add_new_channel("sigma");
 test0s1 ts1{{"q1", "q2"}};

 test0s1* arg = &ts1;

 Chasm_Carrier cc0 = csr->gen_carrier<void*>(&arg);
 ccp->add_carrier(cc0);

 ccp->add_new_channel("lambda");

// u1 test4r(QString a1, QByteArray a2, QVariant a3, QString a4)

 QString a1 = "a1 (string): ";
 QByteArray a2 = "a2 (byte array): ";
 QStringList _a3{"string list 1", "string list 2"};
 QVariant a3 = _a3; //{"string list 1", "string list 2"};
 QString a4 = "a4 (string)";

 Chasm_Carrier cc1 = csr->gen_carrier<QString>(&a1);
 Chasm_Carrier cc2 = csr->gen_carrier<QByteArray>(&a2);
 Chasm_Carrier cc3 = csr->gen_carrier<QVariant>(&a3);
 Chasm_Carrier cc4 = csr->gen_carrier<QString>(&a4);

 ccp->add_carriers({cc1,cc2,cc3,cc4});

 ccp->add_new_channel("retvalue");
 Chasm_Carrier ccr = csr->gen_carrier<void*>(csr->Retvalue._ptr);
 ccp->add_carrier(ccr);

 csr->evaluate(ccp, 4113573_cfc, //(minimal_fn_s1_type)
               &test0s1::test4r, &ccr);

 bool result = ccr._value<u1>();
 qDebug() << "r = " << result;
}


void run_test62s1(Chasm_Runtime* csr)
{
 Chasm_Call_Package* ccp = csr->new_call_package();

 ccp->add_new_channel("sigma");
 test0s1 ts1{{"q1", "q2"}};

 test0s1* arg = &ts1;

 Chasm_Carrier cc0 = csr->gen_carrier<void*>(&arg);
 ccp->add_carrier(cc0);

 ccp->add_new_channel("lambda");
 r8 a1 = 100.5;
 r8 a2 = 200.;
 u1 a3 = 203;
 u1 a4 = 204;
 u1 a5 = 205;
 u1 a6 = 206;


 Chasm_Carrier cc1 = csr->gen_carrier<r8>(&a1);
 Chasm_Carrier cc2 = csr->gen_carrier<r8>(&a2);
 Chasm_Carrier cc3 = csr->gen_carrier<u1>(&a3);
 Chasm_Carrier cc4 = csr->gen_carrier<u1>(&a4);
 Chasm_Carrier cc5 = csr->gen_carrier<u1>(&a5);
 Chasm_Carrier cc6 = csr->gen_carrier<u1>(&a6);


 ccp->add_carriers({cc1,cc2,cc3,cc4,cc5,cc6});

 csr->evaluate(ccp, 610661111_cfc, //(minimal_fn_s1_type)
   &test0s1::test62);
}


void run_test62s1r(Chasm_Runtime* csr)
{
 Chasm_Call_Package* ccp = csr->new_call_package();

 ccp->add_new_channel("sigma");
 test0s1 ts1{{"q1", "q2"}};

 test0s1* arg = &ts1;

 Chasm_Carrier cc0 = csr->gen_carrier<void*>(&arg);
 ccp->add_carrier(cc0);

 ccp->add_new_channel("lambda");
 r8 a1 = 100.5;
 r8 a2 = 200.;
 u1 a3 = 203;
 u1 a4 = 204;
 u1 a5 = 205;
 u1 a6 = 206;


 Chasm_Carrier cc1 = csr->gen_carrier<n8&>(&a1);
 Chasm_Carrier cc2 = csr->gen_carrier<n8&>(&a2);
 Chasm_Carrier cc3 = csr->gen_carrier<u1>(&a3);
 Chasm_Carrier cc4 = csr->gen_carrier<u1>(&a4);
 Chasm_Carrier cc5 = csr->gen_carrier<u1>(&a5);
 Chasm_Carrier cc6 = csr->gen_carrier<u1>(&a6);

 ccp->add_carriers({cc1,cc2,cc3,cc4,cc5,cc6});

 ccp->add_new_channel("retvalue");
 Chasm_Carrier ccr = csr->gen_carrier<QByteArray>(csr->Retvalue._QByteArray);
 ccp->add_carrier(ccr);

 csr->evaluate(ccp, 615001111_cfc, &test0s1::test62r);

 qDebug() << "a2 = " << a2;

 QByteArray result = ccr.value<QByteArray>();
 qDebug() << "r = " << result;
}

s1 test4rr(s2 a1, QByteArray a2, u2 a3, QVariant a4)
{
 qDebug() << a1 << a2 << a3 << a4.toStringList();
 return -2;
}

void run_test4rr(Chasm_Runtime* csr)
{
 Chasm_Call_Package* ccp = csr->new_call_package();

 ccp->add_new_channel("lambda");

 s2 a1 = -33;
 QByteArray a2 = "a2 (byte array)";
 u2 a3 = 34;
 QStringList _a4{"string list 1", "string list 2"};
 QVariant a4 = _a4; //{"string list 1", "string list 2"};

 Chasm_Carrier cc1 = csr->gen_carrier<u2>(&a1);
 Chasm_Carrier cc2 = csr->gen_carrier<QByteArray>(&a2);
 Chasm_Carrier cc3 = csr->gen_carrier<u2>(&a3);
 Chasm_Carrier cc4 = csr->gen_carrier<QVariant>(&a4);

 ccp->add_carriers({cc1,cc2,cc3,cc4});

 ccp->add_new_channel("retvalue");
 Chasm_Carrier ccr = csr->gen_carrier<void*>(csr->Retvalue._u1);
 ccp->add_carrier(ccr);

 csr->evaluate(ccp, 4012527_cfc, //(minimal_fn_s1_type)
               &test4rr, &ccr);

 s2 result = ccr._value<s2>();
 qDebug() << "r = " << result;
}



int main(int argc, char *argv[])
{
 Chasm_Runtime* csr = new Chasm_Runtime;
 csr->init_no_file_session();

 qDebug() << "\n----\n";

// //  temporarily move these around if desired to
 //    debug a specific test ...
// #ifdef HIDE
// #endif //def HIDE

 // //  48 tests ...

 run_test0(csr);
 qDebug() << "\n===\n";

 run_test00(csr);
 qDebug() << "\n===\n";

 run_test0s1(csr);
 qDebug() << "\n===\n";

 run_test0s1r(csr);
 qDebug() << "\n===\n";

 run_test1s1(csr);
 qDebug() << "\n===\n";

 run_test1s1r(csr);
 qDebug() << "\n===\n";

 run_test2s1(csr);
 qDebug() << "\n===\n";

 run_test2s1r(csr);
 qDebug() << "\n===\n";

 run_test3s1(csr);
 qDebug() << "\n===\n";

 run_test3s1r(csr);
 qDebug() << "\n===\n";

 run_test4s1(csr);
 qDebug() << "\n===\n";

 run_test4s1r(csr);
 qDebug() << "\n===\n";


 run_test62s1(csr);
 qDebug() << "\n===\n";

 run_test62s1r(csr);
 qDebug() << "\n===\n";

 run_teste4(csr);
 qDebug() << "\n===\n";

 run_teste3(csr);
 qDebug() << "\n===\n";

 run_teste4of1(csr);
 qDebug() << "\n===\n";

 run_teste4of2(csr);
 qDebug() << "\n===\n";

 run_teste5of2(csr);
 qDebug() << "\n===\n";

 run_teste2of2(csr);
 qDebug() << "\n===\n";

  run_teste2of2rev(csr);
 qDebug() << "\n===\n";

 run_test0arg(csr);
 qDebug() << "\n===\n";

 run_test0r9(csr);
 qDebug() << "\n===\n";

 run_test1arg(csr);
 qDebug() << "\n===\n";

 run_test2arg(csr);
 qDebug() << "\n===\n";


#ifndef __clang__
 // //  so far have trouble with this on Clang ...
 QVector<Chasm_Typed_Value_Representation> rs_args;
 pre_run_smart(csr, rs_args);
 run_smart(csr, rs_args);
 qDebug() << "\n===\n";
#endif

 run_testqvar(csr);
 qDebug() << "\n===\n";

 run_testqvarf(csr);
 qDebug() << "\n===\n";

 run_testfn(csr);
 qDebug() << "\n===\n";

 run_test4rr(csr);
 qDebug() << "\n===\n";

 run_test2(csr);
 qDebug() << "\n===\n";

 run_teste(csr);
 qDebug() << "\n===\n";

 run_testf(csr);
 qDebug() << "\n===\n";

 run_testf4(csr);
 qDebug() << "\n===\n";

 run_testf5(csr);
 qDebug() << "\n===\n";

 run_testqs1(csr);
 qDebug() << "\n===\n";

 run_testqs1n(csr);
 qDebug() << "\n===\n";

 run_testqs2(csr);
 qDebug() << "\n===\n";

 run_testqs2n(csr);
 qDebug() << "\n===\n";

 run_testqsq(csr);
 qDebug() << "\n===\n";

 run_testqs4(csr);
 qDebug() << "\n===\n";

 run_testqs4n(csr);
 qDebug() << "\n===\n";

 run_testqs5(csr);
 qDebug() << "\n===\n";

 run_testqs6(csr);
 qDebug() << "\n===\n";

 run_testqs6n(csr);
 qDebug() << "\n===\n";

 run_testqsv(csr);
 qDebug() << "\n===\n";

 run_testqs8(csr);
 qDebug() << "\n===\n";

 run_testqsp(csr);
 qDebug() << "\n===\n";

 run_testqsb(csr);
//#endif

 qDebug() << "\n_____\n";

}



int main2(int argc, char *argv[])
{
 Unified_Runtime_Object& uro = *Unified_Runtime_Object::instance();
 uro.register_new_metatype_object("Test_Class");

 Test_Class tc("OK");
 qDebug() << tc.text();


 Metatype_Object& mto = *uro.get_metetype_object_by_type_name("Test_Class");

 mto.register_guard_fn("test_method@enter", [](QVector<n8> args) -> n8
 {
  QString& arg0 = *(QString*)args[0];
  u4& arg1 = *(u4*)args[1];
  u4& arg2 = *(u4*)args[2];
  return 0;
 });

// mto

 tc.test_method(ROOT_FOLDER "/dev/extra", 79, 81);
 tc.test_cuo();
 return 0;
}


