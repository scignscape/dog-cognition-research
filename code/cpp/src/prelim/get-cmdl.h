
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef GET_CMDL__H
#define GET_CMDL__H

#include "kans.h"

#include "global-types.h"

#include <QFile>
#include <QTextStream>

#include <QVector>
#include <QPair>
#include <QtGlobal>

#ifdef USE_CWL
#include "cbicaCmdParser.h"
#endif //def USE_CWL


KANS_(Util)


inline QStringList get_cmdl(int argc, char* argv[])
{
 QStringList result;
 for(int i = 0; i < argc; ++i)
   result.push_back(QString::fromLatin1(argv[i]));
 return result;
}

#ifdef USE_CWL
inline void get_cmdl(cbica::CmdParser& parser,
  const QVector< QPair< QPair<QString*, const QString&>,  const QString&> >& vec)
{
 for(auto prpr : vec)
 {
  std::string sstr;
  parser.getParameterValue(prpr.first.second.toStdString(), sstr);
  if(sstr.size() == 0)
    *prpr.first.first = prpr.second;
  else
    *prpr.first.first = QString::fromStdString(sstr);
 }
}

enum class _typecodes
{
 N_A, _u1, _u2, _u4, _n8, _s1, _s2, _s4, _r8
};

_typecodes parse_typecode(QString key)
{
 static QMap<QString, _typecodes> static_map {{
  { "u1", _typecodes::_u1 },
  { "u2", _typecodes::_u2 },
  { "u4", _typecodes::_u4 },
  { "n8", _typecodes::_n8 },
  { "s1", _typecodes::_s1 },
  { "s2", _typecodes::_s2 },
  { "s4", _typecodes::_s4 },
  { "r8", _typecodes::_r8 },
   }};
 return  static_map.value(key, _typecodes::N_A);
}

inline void get_cmdl(cbica::CmdParser& parser,
  const QVector< QPair< QPair<void*, const QString&>, const QStringList&> >& vec)
{
 for(auto prpr : vec)
 {
  QString param = prpr.first.second;
  QString typec;
  QStringList psplit = param.split(':');
  if(psplit.size() > 1)
  {
   typec = psplit[0];
   param = psplit[1];
  }
   // // for cwl ...
  int position = -1;
  parser.compareParameter(param.toStdString(), position);
  _typecodes tc = typec.isEmpty()? _typecodes::N_A: parse_typecode(typec);
  switch (tc)
  {
  case _typecodes::N_A: // string
   {
    if(position == -1)
    {
     *(QString*)prpr.first.first = prpr.second.value(0);
     continue;
    }
    std::string sstr;
    parser.getParameterValue(param.toStdString(), sstr);
    if(sstr.size() == 0)
      *(QString*)prpr.first.first = prpr.second.value(0);
    else
      *(QString*)prpr.first.first = QString::fromStdString(sstr);

   }
   break;
  case _typecodes::_u1:
   {
    if(position == -1)
    {
     *(u1*)prpr.first.first = prpr.second.value(0).toInt();
     continue;
    }
    int v;
    parser.getParameterValue(param.toStdString(), v);
    *(u1*)prpr.first.first = v;
   }
   break;
  case _typecodes::_u2:
   {
    if(position == -1)
    {
     *(u2*)prpr.first.first = prpr.second.value(0).toInt();
     continue;
    }
    int v;
    parser.getParameterValue(param.toStdString(), v);
    *(u2*)prpr.first.first = v;
   }
   break;
  case _typecodes::_u4:
   {
    if(position == -1)
    {
     *(u4*)prpr.first.first = prpr.second.value(0).toInt();
     continue;
    }
    int v;
    parser.getParameterValue(param.toStdString(), v);
    *(u4*)prpr.first.first = v;
   }
   break;
  case _typecodes::_n8:
   {
    if(position == -1)
    {
     *(n8*)prpr.first.first = prpr.second.value(0).toLongLong();
     continue;
    }
    size_t v;
    parser.getParameterValue(param.toStdString(), v);
    *(n8*)prpr.first.first = v;
   }
   break;

  case _typecodes::_s1:
   {
    if(position == -1)
    {
     *(s1*)prpr.first.first = prpr.second.value(0).toInt();
     continue;
    }
    int v;
    parser.getParameterValue(param.toStdString(), v);
    *(s1*)prpr.first.first = v;
   }
   break;
  case _typecodes::_s2:
   {
    if(position == -1)
    {
     *(s2*)prpr.first.first = prpr.second.value(0).toInt();
     continue;
    }
    int v;
    parser.getParameterValue(param.toStdString(), v);
    *(s2*)prpr.first.first = v;
   }
   break;
  case _typecodes::_s4:
   {
    if(position == -1)
    {
     *(s4*)prpr.first.first = prpr.second.value(0).toInt();
     continue;
    }
    int v;
    parser.getParameterValue(param.toStdString(), v);
    *(s4*)prpr.first.first = v;
   }
   break;

  case _typecodes::_r8:
   {
    if(position == -1)
    {
     *(r8*)prpr.first.first = prpr.second.value(0).toDouble();
     continue;
    }
    float v;
    parser.getParameterValue(param.toStdString(), v);
    *(r8*)prpr.first.first = v;
   }
   break;
  }
 }
}
#endif //def USE_CWL


inline QStringList get_cmdl(int argc, char* argv[], 
  int offset, const QVector< QPair<QString*, const QString&> > vec)
{
 QStringList result;// = get_cmdl(argc, argv);

 int sz = vec.size();// + offset;
// int max = qMax(argc, szo);

// int oi = qMax(argc - offset, 0);

 for(int i = 0; i < argc; ++i)
 {
  QString arg = QString::fromLatin1(argv[i]);
  result.push_back(arg);
  if(i < offset)
    continue;
  *vec[i - offset].first = arg;
  //++oi;
 }

 //if(argc - offset)

 for(int i = qMax(argc - offset, 0); i < sz; ++i)
 {
  *vec[i].first = vec[i].second;
 }
 return result;
}


_KANS(Util)


#endif // GET_CMDL__H

