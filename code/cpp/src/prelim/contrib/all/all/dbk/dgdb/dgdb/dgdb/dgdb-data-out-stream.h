
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef DGDB_DATA_OUT_STREAM__H
#define DGDB_DATA_OUT_STREAM__H

#include <functional>

#include <QMap>
#include <QString>
#include <QByteArray>

#include <QDebug>

#include "global-types.h"

//#include "_whitedb/_whitedb.h"

#include "accessors.h"

#include "kans.h"


KANS_(DGDB)


class DH_Type;
class DH_Type_Builder;

class DgDb_Data_Out_Stream
{
 const QByteArray& device_;

 size_t index_;
 size_t current_target_;
 size_t current_start_offset_;

public:


 DgDb_Data_Out_Stream(const QByteArray& device);

 DgDb_Data_Out_Stream& operator / (size_t ct) //std::initializer_list<size_t> svec)
 {
  current_target_ = ct;
//  QVector vec(svec);
//  current_target_ = vec.last();
//  if(vec.size() > 1)
//    current_start_offset_ = vec.first();
//  else
//    current_start_offset_ = 0;
  return *this;
 }

 template<typename T>
 DgDb_Data_Out_Stream& operator / (T& t)
 {
  qDebug() << "this ";
  return *this;
 }


};


//template<>
//DgDb_Data_Out_Stream& DgDb_Data_Out_Stream::operator >> (QVector<size_t>& vec)
//{
// current_target_ = vec.last();
// if(vec.size() > 1)
//   current_start_offset_ = vec.first();
// else
//   current_start_offset_ = 0;
// return *this;
//}

_KANS(DGDB)


#endif // DGDB_DATA_OUT_STREAM__H


