
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "ntxh-graph-build.h"

#include "kernel/frame/ntxh-frame.h"

#include "kernel/graph/ntxh-graph.h"

USING_KANS(HGDMCore)


NTXH_Graph_Build::NTXH_Graph_Build(NTXH_Document* d, NTXH_Parser& p, NTXH_Graph& g)
 : Flags(0)
   ,document_(d)
   ,graph_(g)
   ,parser_(p)
   ,fr_(NTXH_Frame::instance())
   ,current_field_number_(0)
   ,current_type_field_index_(0)
   ,current_hypernode_(nullptr)
   ,last_hypernode_(nullptr)
   ,held_current_hypernode_(nullptr)
{

}

void NTXH_Graph_Build::init()
{

}

void NTXH_Graph_Build::end_field()
{
 parse_context_.flags.multiline_field = false;
 parse_context_.flags.expecting_field = false;
 if(flags.discard_acc)
 {
  flags.discard_acc = false;
  return;
 }
 if(flags.define_replacement)
 {
  flags.define_replacement = false;
  replacements_[current_field_name_] = acc_.simplified();
  current_field_name_.clear();
  acc_.clear();
  return;
 }
 if(flags.replace_acc)
 {
  if(acc_.simplified().startsWith('%'))
    acc_ = replacements_.value(acc_.simplified().mid(1));
 }

 if(flags.numeric_acc)
 {
  flags.numeric_acc = false;
  numeric_index_type i = acc_.simplified().toInt();
  add_numeric_read_token(i);
 }
 else if(flags.split_acc)
 {
  flags.split_acc = false;
  QStringList qsl = acc_.simplified().split(' ');
  QStringListIterator qsli(qsl);
  while(qsli.hasNext())
  {
   QString qs = qsli.next();
   add_read_token(qs);
   if(qsli.hasNext())
   {
    if(current_field_name_ != "!#")
    {
     graph_.update_current_field_index(current_type_name_, current_field_name_, current_field_number_);
     current_field_name_ = "!#";
    }
    ++current_field_number_;
   }
  }
  if(current_field_name_ == "!#")
  {
   current_field_name_.clear();
  }
 }
 else
 {
  add_read_token(acc_.trimmed());
 }
 acc_.clear();
}

void NTXH_Graph_Build::read_acc(QString s)
{
 acc_ += s;
}

void NTXH_Graph_Build::read_command(QString prefix, QString cmd, QString suffix)
{
 // // only current command ...
 if(cmd == "s")
 {
  held_current_hypernode_ = current_hypernode_;
  current_hypernode_ = last_hypernode_;
  check_reset_current_type_name();
 }
}

void NTXH_Graph_Build::leave_read_command(QString prefix, QString cmd, QString suffix)
{
 // // only current command ...
 if(cmd == "s")
 {
  current_hypernode_ = held_current_hypernode_;
  held_current_hypernode_ = nullptr;
  check_reset_current_type_name();
 }
}


void NTXH_Graph_Build::prepare_field_read(QString prefix, QString field, QString suffix)
{
 flags.discard_acc = false;
 if(suffix == ".")
   parse_context_.flags.multiline_field = true;
 else if(suffix == "#")
   flags.split_acc = true;
 else if(suffix == ";")
   flags.discard_acc = true;
 else if(suffix == "=")
   flags.numeric_acc = true;
 else if(suffix == "/")
   flags.replace_acc = true;
 else if(suffix == "*")
   flags.wildcard_acc = true;
 else if(suffix == "&")
 {
  flags.wildcard_acc = true;
  parse_context_.flags.multiline_field = true;
 }

 if(prefix == "$$")
 {
  ++current_field_number_;
  current_field_name_.clear();
 }
 else if(prefix == "@@")
 {
  ++current_field_number_;
  current_field_name_.clear();
 }
 else if(prefix.startsWith('$'))
 {
  bool ok;
  current_field_number_ = field.toInt(&ok);
  current_field_name_ = ok? QString() : field;
 }
 else if(prefix.startsWith('@'))
 {
  current_field_number_ = field.toInt();
  current_field_name_.clear();
 }
 else if(prefix.startsWith('%'))
 {
  flags.define_replacement = true;
  current_field_name_ = field;
 }
 flags.array_field = prefix.startsWith('@');

 parse_context_.flags.expecting_field = true;
}

void NTXH_Graph_Build::add_type(QString name, QString length)
{
 QStringList ls = length.mid(1, length.size() - 2).split(';');

 int l = ls[0].toInt();

 signed int cs, offs;

 if(ls.size() > 1)
   offs = ls[1].toInt();
 else
   offs = -1;

 if(ls.size() > 2)
   cs = ls[2].toInt();
 else
   cs = -1;

 if(length.startsWith('{'))
 {
  graph_.add_structure_type(name, l, offs);
 }
 else if(length.startsWith('['))
 {
  graph_.add_array_type(name, l, cs, offs);
 }
 current_type_name_ = name;
 current_type_field_index_ = 0;
 parse_context_.flags.active_type_decl = true;
}

void NTXH_Graph_Build::add_coda_data_line(QString qs)
{

}

void NTXH_Graph_Build::add_numeric_read_token(numeric_index_type val)
{
 if(current_field_name_.isEmpty())
 {
  graph_.add_read_token(current_hypernode_, current_type_name_,
    current_field_number_, {"", (void*)val});
 }
 else
 {
  graph_.add_read_token(current_hypernode_, current_type_name_,
    current_field_name_, {"", (void*)val});
 }
}

void NTXH_Graph_Build::add_read_token(QString text)
{
 if(current_field_name_.isEmpty())
 {
  graph_.add_read_token(current_hypernode_, current_type_name_,
    current_field_number_, {text, nullptr});
 }
 else if(current_field_name_.startsWith('!'))
 {
  graph_.add_read_token(current_hypernode_, current_type_name_,
    current_field_number_, {text, nullptr}, current_field_name_);
 }
 else
 {
  graph_.add_read_token(current_hypernode_, current_type_name_,
    current_field_name_, {text, nullptr});
 }
}

void NTXH_Graph_Build::add_type_field_index(QString name, int code)
{
 if(code == 0)
   ++current_type_field_index_;
 else
   current_type_field_index_ = code;

 graph_.add_type_field_index(current_type_name_, name, code);
}

void NTXH_Graph_Build::start_sample(QString ty)
{
 if(current_hypernode_)
   parent_hypernodes_.push(current_hypernode_);

 current_hypernode_ = graph_.new_hypernode_by_type_name(ty);

 current_type_name_ = ty;

}

void NTXH_Graph_Build::top_level_append()
{
 top_level_hypernodes_.push_back(last_hypernode_);
}

void NTXH_Graph_Build::array_append()
{
 if(current_hypernode_)
 {
  if(last_hypernode_)
    graph_.array_append(current_hypernode_, last_hypernode_);
 }
}

void NTXH_Graph_Build::check_reset_current_type_name()
{
 if(current_hypernode_)
 {
  current_type_name_ = current_hypernode_->type_descriptor().first;
 }
}

void NTXH_Graph_Build::end_sample()
{
 last_hypernode_ = current_hypernode_;

 if(parent_hypernodes_.isEmpty())
   current_hypernode_ = nullptr;
 else
   current_hypernode_ = parent_hypernodes_.pop();

 check_reset_current_type_name();
}
