
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef MULTISTEP_TOKEN__H
#define MULTISTEP_TOKEN__H

#include <QString>
#include <QMap>

enum class MS_Token_Kinds
{
 N_A, Generic, Scoped_Symbol, Scoped_Symbol_Literal_Init,
 Literal, Instruction_Symbol, String_Literal,
 FGround_Symbol, Raw_Symbol,
 Bridge_Symbol, Sigma_Symbol,
 Internal_String, Skip_Token,
 Type_Symbol, Kernel_Type_Symbol,
 Nested_Forward, Nested_Back,
 Paren_Entry, Paren_Leave,
 Note_Symbol, Proxy_Value_Symbol,
 Skipped_Flag_Symbol,  Assignment_Kind,
 Preempted_Instruction_Symbol,
};

struct MS_Token
{
 MS_Token_Kinds kind;
 QString raw_text;

 QPair<int, int> to_number_pair() const
 {
  int ind = raw_text.indexOf('-');
  if(ind == -1)
  {
   return {0, 0};
  }
  return {raw_text.left(ind).toInt(), raw_text.mid(ind + 1).toInt()};
 }

 static QString get_assignment_kind_name(QString tok)
 {
  static QMap<QString, QString> static_map {{
   { "<<|", "formula" },
   { "<<||", "formula-reinit" },
   }};
  return static_map.value(tok, "generic");
 }

 QString to_number_pair_split_string()
 {
  QString result = raw_text;
  int ind = raw_text.indexOf('-');
  if(ind == -1)
  {
   return QString();
  }
  result[ind] = ' ';
  return result;
 }

 QString first_number_to_string() const
 {
  int ind = raw_text.indexOf('-');
  if(ind == -1)
  {
   return raw_text;
  }
  return raw_text.left(ind);
 }

 int first_number() const
 {
  return first_number_to_string().toInt();
 }

 QString second_number_to_string() const
 {
  int ind = raw_text.indexOf('-');
  if(ind == -1)
  {
   return raw_text;
  }
  return raw_text.mid(ind + 1);
 }

 int second_number() const
 {
  return second_number_to_string().toInt();
 }

 MS_Token to_kind(MS_Token_Kinds k)
 {
  return {k, raw_text};
 }

 void clear()
 {
  raw_text.clear();
  kind = MS_Token_Kinds::N_A;
 }

 bool has_text()
 {
  return !raw_text.isEmpty();
 }

 static MS_Token Null()
 {
  return {MS_Token_Kinds::N_A, QString()};
 }

 static MS_Token check_as(MS_Token_Kinds k1, MS_Token_Kinds k2, QString qs)
 {
  return { (k1 == MS_Token_Kinds::N_A?k2:k1), qs};
 }

 static MS_Token decode(QString str)
 {
  static QMap<QString, MS_Token_Kinds> static_map {{
#define TEMP_MACRO(X, Y) {Y, MS_Token_Kinds::X},

    TEMP_MACRO(Scoped_Symbol, "@#_")
    TEMP_MACRO(String_Literal, "\"\"")
    TEMP_MACRO(Literal, "###")
    TEMP_MACRO(FGround_Symbol, "@%_")
    TEMP_MACRO(Raw_Symbol, "%%_")
    TEMP_MACRO(Bridge_Symbol, "")
    TEMP_MACRO(Sigma_Symbol, "@@_")
    TEMP_MACRO(Internal_String, "##_")
    TEMP_MACRO(Skip_Token, "_#_")
    TEMP_MACRO(Type_Symbol, "@__")
    TEMP_MACRO(Kernel_Type_Symbol, "#__")
    TEMP_MACRO(Nested_Forward, "^->")
    TEMP_MACRO(Nested_Back, "^<-")
    TEMP_MACRO(Paren_Entry, "_%>")
    TEMP_MACRO(Paren_Leave, "_%<")
    TEMP_MACRO(Note_Symbol, "_%_")
    TEMP_MACRO(Proxy_Value_Symbol, "_@_")
    TEMP_MACRO(Assignment_Kind, "_=_")

	
	
#undef TEMP_MACRO
  }};

  if(str.startsWith('"'))
  {
   return {MS_Token_Kinds::String_Literal, str};
  }
  else
  {
   QString prefix = str.left(3);
   return {static_map.value(prefix, MS_Token_Kinds::Generic), str.mid(3)};
  }
 }

 QString get_encode_prefix()
 {
  static QMap<MS_Token_Kinds, QString> static_map {{

#define TEMP_MACRO(X, Y) {MS_Token_Kinds::X, Y},

   TEMP_MACRO(Scoped_Symbol, "@#_")
   TEMP_MACRO(String_Literal, "\"\"")
   TEMP_MACRO(Literal, "###")
   TEMP_MACRO(FGround_Symbol, "@%_")
   TEMP_MACRO(Raw_Symbol, "%%_")
   TEMP_MACRO(Bridge_Symbol, "")
   TEMP_MACRO(Sigma_Symbol, "@@_")
   TEMP_MACRO(Internal_String, "##_")
   TEMP_MACRO(Skip_Token, "_#_")
   TEMP_MACRO(Type_Symbol, "@__")
   TEMP_MACRO(Kernel_Type_Symbol, "#__")
   TEMP_MACRO(Nested_Forward, "^->")
   TEMP_MACRO(Nested_Back, "^<-")
   TEMP_MACRO(Paren_Entry, "_%>")
   TEMP_MACRO(Paren_Leave, "_%<")
   TEMP_MACRO(Note_Symbol, "_%_")
   TEMP_MACRO(Proxy_Value_Symbol, "_@_")
   TEMP_MACRO(Assignment_Kind, "_=_")

#undef TEMP_MACRO
  }};

  return static_map.value(kind);
 }

 QString escaped_raw_text()
 {
  QString result = raw_text;
  if(result.startsWith(":|"))
  {
   result.insert(1, '\\');
   result.insert(result.size() - 1, '\\');
  }
  return result;
 }

 QString encode()
 {
  switch(kind)
  {
  case MS_Token_Kinds::Preempted_Instruction_Symbol:
  case MS_Token_Kinds::String_Literal:
   return QString("\"%1\"").arg(raw_text);

  case MS_Token_Kinds::Instruction_Symbol:
   return raw_text;

  case MS_Token_Kinds::Skipped_Flag_Symbol:
   return raw_text;

  case MS_Token_Kinds::Assignment_Kind:
   return QString(":|%1%2|").arg(get_encode_prefix()).arg(get_assignment_kind_name(raw_text));

  default:
   return QString(":|%1%2|").arg(get_encode_prefix()).arg(escaped_raw_text());
  }
 }
};


#endif //MULTISTEP_TOKEN__H
