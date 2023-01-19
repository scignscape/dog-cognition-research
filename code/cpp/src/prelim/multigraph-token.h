
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef MULTIGRAPH_TOKEN__H
#define MULTIGRAPH_TOKEN__H

#include <QString>
#include <QMap>
#include <QList>

enum class MG_Token_Kind_Groups
{
 N_A, Generic, Raw, String_Literal,
 Arg, Target, Arg_Target, Arg_String_Literal, Macro, Sig
};

enum class MG_Token_Subgroups
{
 N_A, Symbol, Value, Ledger, Known, Generic,
 Channel, Type
};

enum class MG_Token_Kinds
{
 N_A, Generic, Raw_Symbol, Raw_Value, String_Literal,
 Arg_Raw_Symbol, Arg_Raw_Value, Ledger_Target, Known_Target,
 Arg_Ledger_Target, Arg_Known_Target, Arg_String_Literal,
 Macro_TBD, Macro_Name,
 Sig_Channel, Sig_Type, Sig_Symbol, Sig_Symbol_Before_Type
};

inline MG_Token_Kind_Groups MG_Token_Kind_to_group(MG_Token_Kinds k)
{
 switch(k)
 {
 case MG_Token_Kinds::Generic: return MG_Token_Kind_Groups::Generic;

 case MG_Token_Kinds::Raw_Symbol:
 case MG_Token_Kinds::Raw_Value:
  return MG_Token_Kind_Groups::Raw;

 case MG_Token_Kinds::String_Literal: return MG_Token_Kind_Groups::String_Literal;

 case MG_Token_Kinds::Arg_Raw_Symbol:
 case MG_Token_Kinds::Arg_Raw_Value:
  return MG_Token_Kind_Groups::Arg;

 case MG_Token_Kinds::Ledger_Target:
 case MG_Token_Kinds::Known_Target:
  return MG_Token_Kind_Groups::Target;

 case MG_Token_Kinds::Arg_Ledger_Target:
 case MG_Token_Kinds::Arg_Known_Target:
  return MG_Token_Kind_Groups::Arg_Target;

 case MG_Token_Kinds::Macro_TBD:
 case MG_Token_Kinds::Macro_Name:
  return MG_Token_Kind_Groups::Macro;

 case MG_Token_Kinds::Sig_Channel:
 case MG_Token_Kinds::Sig_Type:
 case MG_Token_Kinds::Sig_Symbol:
 case MG_Token_Kinds::Sig_Symbol_Before_Type:
  return MG_Token_Kind_Groups::Sig;

 default: return MG_Token_Kind_Groups::N_A;
 }
}

inline MG_Token_Subgroups MG_Token_Kind_to_subgroup(MG_Token_Kinds k)
{
 switch(k)
 {
 case MG_Token_Kinds::Arg_Raw_Symbol:
  return MG_Token_Subgroups::Symbol;
 case MG_Token_Kinds::Arg_Raw_Value:
  return MG_Token_Subgroups::Value;

 case MG_Token_Kinds::Arg_Ledger_Target:
 case MG_Token_Kinds::Ledger_Target:
  return MG_Token_Subgroups::Ledger;

 case MG_Token_Kinds::Arg_Known_Target:
 case MG_Token_Kinds::Known_Target:
  return MG_Token_Subgroups::Known;

 case MG_Token_Kinds::Generic:
  return MG_Token_Subgroups::Generic;

 case MG_Token_Kinds::Sig_Channel:
  return MG_Token_Subgroups::Channel;
 case MG_Token_Kinds::Sig_Type:
  return MG_Token_Subgroups::Type;
 case MG_Token_Kinds::Sig_Symbol:
  return MG_Token_Subgroups::Symbol;

 default: return MG_Token_Subgroups::N_A;
 }
}

inline QList<MG_Token_Kinds> MG_Token_Kind_Group_to_kinds(MG_Token_Kind_Groups g)
{
 switch(g)
 {
 case MG_Token_Kind_Groups::Generic: return {MG_Token_Kinds::Generic};

 case MG_Token_Kind_Groups::Raw:
  return {MG_Token_Kinds::Raw_Symbol, MG_Token_Kinds::Raw_Value};

 case MG_Token_Kind_Groups::String_Literal: return {MG_Token_Kinds::String_Literal};

 case MG_Token_Kind_Groups::Arg:
  return {MG_Token_Kinds::Arg_Raw_Symbol, MG_Token_Kinds::Arg_Raw_Value};

 case MG_Token_Kind_Groups::Target:
  return {MG_Token_Kinds::Ledger_Target, MG_Token_Kinds::Known_Target};

 case MG_Token_Kind_Groups::Arg_Target:
  return {MG_Token_Kinds::Arg_Ledger_Target, MG_Token_Kinds::Arg_Known_Target};

 case MG_Token_Kind_Groups::Macro:
  return {MG_Token_Kinds::Macro_TBD, MG_Token_Kinds::Macro_Name};

 case MG_Token_Kind_Groups::Sig:
  return {MG_Token_Kinds::Sig_Channel,
    MG_Token_Kinds::Sig_Type, MG_Token_Kinds::Sig_Symbol, MG_Token_Kinds::Sig_Symbol_Before_Type};

 default: return {MG_Token_Kinds::N_A};
 }
}

struct MG_Token
{
 MG_Token_Kinds kind;
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

 QString to_target()
 {
  return raw_text.prepend('$');
 }


 QString to_known_target()
 {
  return raw_text.prepend('!');
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

 MG_Token to_kind(MG_Token_Kinds k)
 {
  return {k, raw_text};
 }

 void clear()
 {
  raw_text.clear();
  kind = MG_Token_Kinds::N_A;
 }

 bool has_text()
 {
  return !raw_text.isEmpty();
 }

 static MG_Token Null()
 {
  return {MG_Token_Kinds::N_A, QString()};
 }

 static MG_Token check_as(MG_Token_Kinds k1, MG_Token_Kinds k2, QString qs)
 {
  return { (k1 == MG_Token_Kinds::N_A?k2:k1), qs};
 }


 static MG_Token decode_symbol(QString str)
 {
  if(str.startsWith(":|"))
    str = str.mid(2);
  if(str.endsWith('|'))
    str.chop(1);
  return decode(str);
 }

 static MG_Token decode(QString str)
 {
  static QMap<QString, MG_Token_Kinds> static_map {{
#define TEMP_MACRO(X, Y) {Y, MG_Token_Kinds::X},

  TEMP_MACRO(Raw_Symbol, "__@")
  TEMP_MACRO(Raw_Value, "__$")
  TEMP_MACRO(Generic, "/--")

  TEMP_MACRO(Arg_Raw_Symbol, ">_@")
  TEMP_MACRO(Arg_Raw_Value, ">_$")

  TEMP_MACRO(Arg_Ledger_Target, "<->")
  TEMP_MACRO(Arg_Known_Target, "<!>")

  TEMP_MACRO(Ledger_Target, "-->")
  TEMP_MACRO(Known_Target, "-!>")

  TEMP_MACRO(Arg_String_Literal, "<$>")

  TEMP_MACRO(Macro_TBD, "...")
  TEMP_MACRO(Macro_Name, "(&)")


  TEMP_MACRO(Sig_Channel, "-&-")
  TEMP_MACRO(Sig_Type, "-%-")
  TEMP_MACRO(Sig_Symbol, "-@-")
  TEMP_MACRO(Sig_Symbol_Before_Type, "-@%")

#undef TEMP_MACRO
  }};

  if(str.startsWith('"'))
  {
   return {MG_Token_Kinds::String_Literal, str};
  }
  else
  {
   QString prefix = str.left(3);
   return {static_map.value(prefix, MG_Token_Kinds::Generic), str.mid(3)};
  }
 }

 QString get_encode_prefix() const
 {
  static QMap<MG_Token_Kinds, QString> static_map {{

#define TEMP_MACRO(X, Y) {MG_Token_Kinds::X, Y},

  TEMP_MACRO(Raw_Symbol, "__@")
  TEMP_MACRO(Raw_Value, "__$")
  TEMP_MACRO(Generic, "/--")

  TEMP_MACRO(Arg_Raw_Symbol, ">_@")
  TEMP_MACRO(Arg_Raw_Value, ">_$")

  TEMP_MACRO(Ledger_Target, "-->")
  TEMP_MACRO(Known_Target, "-!>")

  TEMP_MACRO(Arg_Ledger_Target, "<->")
  TEMP_MACRO(Arg_Known_Target, "<!>")

  TEMP_MACRO(Arg_String_Literal, "<$>")

  TEMP_MACRO(Macro_TBD, "...")
  TEMP_MACRO(Macro_Name, "(&)")

  TEMP_MACRO(Sig_Channel, "-&-")
  TEMP_MACRO(Sig_Type, "-%-")
  TEMP_MACRO(Sig_Symbol, "-@-")
  TEMP_MACRO(Sig_Symbol_Before_Type, "-@%")

#undef TEMP_MACRO
  }};

  return static_map.value(kind);
 }

 QString escaped_raw_text() const
 {
  QString result = raw_text;
  if(result.startsWith(":|"))
  {
   result.insert(1, '\\');
   result.insert(result.size() - 1, '\\');
  }
  return result;
 }

 QString encode() const
 {
  switch(kind)
  {
//  case MG_Token_Kinds::Arg_String_Literal:
//    return QString("$%1").arg(raw_text);
  case MG_Token_Kinds::String_Literal:
    return raw_text;
   //?return QString("\"%1\"").arg(raw_text);

  default:
   return QString(":|%1%2|").arg(get_encode_prefix()).arg(escaped_raw_text());
   //return QString("%1%2").arg(get_encode_prefix()).arg(raw_text);
  }
 }
};


#endif //MULTIGRAPH_TOKEN__H
