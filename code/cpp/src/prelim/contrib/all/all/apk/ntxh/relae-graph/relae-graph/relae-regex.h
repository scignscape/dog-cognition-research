
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef RELAE_REGEX__H
#define RELAE_REGEX__H

#include "rz-typedefs.h"
#include "flags.h"

#include <QRegularExpression>
#include <QDebug>
#include <QStringList>
#include <functional>

#include "relae-caon-ptr.h"

#ifndef RZ_MATCH_CALLBACK
#define RZ_MATCH_CALLBACK std::function<void()>
#endif

#ifndef RZ_PERSISTENT_POINTER
#define RZ_PERSISTENT_POINTER(type_name, var_name) \
 type_name*& var_name = *(new type_name*)
#endif

struct RZ_Core_Rule
{
 QRegularExpression* rexpr;
 int context_index;
 tString name;
 tString expr;

 Flag_or_Depth* condition;
 Flag_or_Depth* negative_condition;

 int condition_length;
 int negative_condition_length;

 QRegularExpression::MatchOptions match_options;

 RZ_Flag_Test* flag_test;

 // Emulate named captures with a name-to-index map.
 // Assume that all captures are named!
 QMap<tString, int> capture_name_map;

 RZ_MATCH_CALLBACK callback;

 RZ_Core_Rule(tString n, tString e, RZ_MATCH_CALLBACK c):name(n),expr(e),
   callback(c), context_index(0), condition(0), negative_condition(0),
  condition_length(0), negative_condition_length(0), flag_test(0)
 {
  // //  Check if we want an achor at the carat, like
  //     RegExp::CaretAtOffset -- but QRegularExpression
  //     doesn't use the carat as such.  Analogous to perl \\D...
  bool anchored = false;
  if(e.startsWith('^'))
  {
   anchored = true;
   e.remove(0, 1);
   expr = e;
  }
  if(anchored)
   match_options = QRegularExpression::AnchoredMatchOption;
  else
   match_options = QRegularExpression::NoMatchOption;

  rexpr = new QRegularExpression(e, QRegularExpression::DotMatchesEverythingOption);
 }
};

struct RZ_Match_Data_Base
{
 virtual operator bool() = 0;
 virtual bool end_of_file(){ return false; }
 virtual char* original_rule_type()
 {
  return "unknown";
 }
 virtual void clean_up() {}

 virtual void reset_position(int& pos) = 0;
 virtual tString text() = 0;
 virtual tString text(tString capture_name)
 {
  return "";
 }
 virtual tString text(int capture_number)
 {
  return "";
 }

};

struct RZ_Match_Data_False : RZ_Match_Data_Base
{
 void reset_position(int& pos){}
 operator bool()
 {
  return false;
 }
 tString text()
 {
  return "";
 }
};

struct RZ_Match_Data_Qt : RZ_Match_Data_Base
{
 int position;
 QRegularExpression* rexpr;
 QStringList captures;
 QMap<tString, int> capture_name_map;
 RZ_Match_Data_Qt(int p, QStringList s, QMap<QString, int>& m):position(p + 1),
   captures(s),capture_name_map(m){}
 operator bool()
 {
  return position > 0;
 }
 char* original_rule_type()
 {
  return "QRegularExpression";
 }
 void clean_up()
 {
 }
 void reset_position(int& pos)
 {
  pos = position - 1;
 }
 tString text()
 {
  return captures[0];
 }
 tString text(tString capture_name)
 {
  if(capture_name_map.contains(capture_name))
  {
   int capture_index = capture_name_map[capture_name];
   if(capture_index >= captures.size())
    return tString();
   return captures[capture_name_map[capture_name]];
  }
  return tString();
 }
 tString text(int capture_number)
 {
  return captures[capture_number];
 }

};

inline RZ_Match_Data_Base* RZ_Match_Fail()
{
 static RZ_Match_Data_False result = RZ_Match_Data_False();
 return &result;
}


#endif //RELAE_REGEX__H
