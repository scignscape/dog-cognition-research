
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef RZ_TYPEDEFS__H
#define RZ_TYPEDEFS__H

class QString;
class QTextStream;
class RZ_Core_Rule;

typedef QString tString;
typedef QTextStream tStringStream;
typedef unsigned short tMid;
typedef int tInt;
typedef char tChar;

typedef tInt tyId;


typedef tInt Flag_or_Depth;
typedef tString tNodeLabel;
typedef RZ_Core_Rule tRule;

#include <QString>
#include <fstream>

struct RZ_Utilities
{
 static void Load_File(QString file_path, QString& contents)
 {
  std::string c;
  std::ifstream ifs (file_path.toStdString());
  if(! ifs.is_open() )
   contents = "";
  std::getline(ifs, c, '\0');
  ifs.close();
  contents = QString::fromStdString(c);
 }
};


typedef RZ_Utilities Utilities_type;

#define tMap QMap
#define tVec QVector


#endif //RZ_TYPEDEFS__H
