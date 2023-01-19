
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef WITHS__H
#define WITHS__H

#include <QtGlobal>
#include <QString>
#include <QMap>
#include <QDir>
#include <QVector>
#include <QTextStream>

#include <functional>

struct brake
{
 std::function<void(brake)> fn;
 static std::function<void(brake)> get_null()
 {
  static std::function<void(brake)> the_null = [](brake){};
  return the_null;
 }
 brake& operator&(brake& rhs)
 {
  rhs(); return *this;
 }
 brake() : fn(brake::get_null())
 {
 }
 brake(std::function<void(brake)> f) : fn(f)
 {
 }
 static std::function<void(brake)> make_break_function(brake& test_brk)
 {
  return [&test_brk](brake b)
  {
   if(b.fn)
   {
    test_brk.fn = b.fn;
    b.fn({});
   }
  };
 }
 void operator()()
 {
  fn({});
 }

 void operator()(brake brk)
 {
  fn(brk);
 }
};

struct with_lines_Package
{
 const QString* const input;
 void operator<<(std::function<void(QString)> fn)
 {
  if(!input)
    return;
  QString qs;
  QTextStream ts(const_cast<QString*>(input), QIODevice::ReadOnly);
  while(ts.readLineInto(&qs))
  {
   fn(qs);
  }
 }
};

static inline with_lines_Package with_lines(const QString& qs)
{
 return {&qs};
}

template<typename KEY_Type, typename VAL_Type>
struct with_map_Package
{
 QMap<KEY_Type, VAL_Type>& qm;
 void operator<<(std::function<void(const KEY_Type&, const VAL_Type&)> fn)
 {
  QMapIterator<KEY_Type, VAL_Type> it(qm);
  while (it.hasNext())
  {
   it.next();
   fn(it.key(), it.value());
  }
 }
};

template<typename KEY_Type, typename VAL_Type>
static inline with_map_Package<KEY_Type, VAL_Type>
  with_map(QMap<KEY_Type, VAL_Type>& qm)
{
 return {qm};
}


struct with_files_Package
{
 QDir qd;
 QStringList filters;
 QDir::Filters qdfilters;
 with_files_Package& filter(QStringList&& qsl)
 {
  filters = qsl;
  return *this;
 }
 with_files_Package& filter(const QStringList& qsl)
 {
  filters = qsl;
  return *this;
 }
 void operator<<(std::function<void(QFileInfo&)> fn)
 {
  QFileInfoList qfil;
  if(filters.isEmpty())
    qfil = qd.entryInfoList(qdfilters);
  else
    qfil = qd.entryInfoList(filters, qdfilters);

  for(QFileInfo qfi :  qfil)
  {
   fn(qfi);
  }
 }
};

static inline with_files_Package with_files(QDir qd)
{
 return {qd, {}, QDir::Files | QDir::NoDotAndDotDot};
}


struct with_range_2_Package
{
 quint32 min;
 quint32 max;

 void operator<<(std::function<void(quint32)> fn)
 {
  for(quint32 i = min; i < max; ++i)
    fn(i);
 }

 void operator<<(std::function<void(quint32, brake brk)> fn)
 {
  brake test_brk = brake(nullptr);
  auto brk = brake::make_break_function(test_brk);
  for(quint32 i = min; i < max; ++i)
  {
   fn(i, {brk});
   if(test_brk.fn)
     break;
  }
 }
};

struct with_range_Package
{
 quint32 min;
 with_range_2_Package operator()(quint32 max)
 {
  return {min, max + 1};
 }
 with_range_2_Package operator[](quint32 max)
 {
  return {min, max};
 }
};

static with_range_Package with_range(quint32 min)
{
 return {min};
}

struct with_multi_range_Package
{
 quint8 dimension;
 QVector<quint32> args;
 QVector<quint32> carried;

 with_multi_range_Package& operator()(quint32 arg)
 {
  args.push_back(arg + 1);
  return *this;
 }
 with_multi_range_Package& operator[](quint32 arg)
 {
  args.push_back(arg);
  return *this;
 }
 void operator<<(std::function<void(QVector<quint32>)> fn)
 {
  quint32 index = 0;
  while(args.size() < (dimension * 2))
  {
   args.insert(index, 0);
   index += 2;
  }
  for(quint32 i = args[0]; i < args[1]; ++i)
  {
   QVector<quint32> c = carried;
   c.push_front(i);
   if(dimension == 1)
   {
    fn(c);
   }
   else
   {
    with_multi_range_Package p1{dimension - 1, args.mid(2), c};
    p1 << fn;
   }

//   for(quint32 j = args[2]; j < args[3]; ++j)
//     fn({i, j});
  }
 }

};

static with_multi_range_Package with_multi_range(quint8 dim)
{
 return {dim, {}, {}};
}


#endif // WITHS__H
