
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "test-class.h"

//#include "qh-package/qh-pack-code.h"
//#include "qh-package/qh-pack-builder.h"

#include <QDebug>

#include <QDataStream>


Test_Class::Test_Class()
 : a_number_(0) //, as_hypernode(nullptr)
{

}


//void Test_Class::supply_pack(Qh_Pack_Builder& qpb)
//{
// // // need node data for the string ...
// qpb.init_node_data();

// qpb.add_sv((u2) a_number_)
//   .add_sv(78)
//   .add_sv(a_string_);

//// qpb.add_structure_value(QVariant::fromValue((u2) a_number_))
////   .add_structure_value(QVariant::fromValue(78))
////   .add_structure_value(QVariant::fromValue(QString("String")));

//}


//void Test_Class::init_pack_code(Qh_Pack_Code& qpc)
//{
// qpc.add_u2().add_u1().add_str();


//}



void Test_Class::supply_data(QByteArray& qba)
{
 QDataStream qds(&qba, QIODevice::WriteOnly);

#define TEMP_MACRO(x) << x##_
 qds _Test_Class_FM(TEMP_MACRO);
#undef TEMP_MACRO


// qds << a_sign_ << a_string_ << a_number_;

}

void Test_Class::absorb_data(const QByteArray& qba)
{
 QDataStream qds(qba);

// u2 an; QString str;
// qds >> an;
// qds >> str;

#define TEMP_MACRO(x) >> x##_
 qds _Test_Class_FM(TEMP_MACRO);
#undef TEMP_MACRO

// qds >> a_sign_ >> a_string_ >> a_number_;

// qDebug() << "a string = " << a_string_;
// qDebug() << "a sign = " << a_sign_;
// qDebug() << "a number = " << a_number_;
}



