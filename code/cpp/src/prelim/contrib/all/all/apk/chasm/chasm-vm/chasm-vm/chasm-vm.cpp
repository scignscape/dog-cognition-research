
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "chasm-vm.h"

#include "chasm/chasm-runtime.h"

#include "chasm-runtime-bridge/chasm-runtime-bridge.h"

#include "textio.h"
USING_KANS(TextIO)

#include <QString>
#include <QVariant>
#include <QByteArray>

#include <QUrl>

#include <QPoint>

Chasm_VM::Chasm_VM(Chasm_Runtime_Bridge* crb)
  :  crb_(crb), gen_source_proc_name_count_(0)
{

}

QString Chasm_VM::_gen_source_proc_name()
{
 ++gen_source_proc_name_count_;
 return QString("<_%1>").arg(gen_source_proc_name_count_);
}

QString Chasm_VM::gen_source_proc_name()
{
 current_source_proc_name_ = _gen_source_proc_name();
 return current_source_proc_name_;
}

void Chasm_VM::load_program(QString path)
{
 QString lines;
 load_file(path, lines);
 read_local_program(lines);
}

void Chasm_VM::reread_substitute(QString& key)
{
 static QMap<QString, QString(Chasm_VM::*)() const> static_map {{
   { "last_source_proc_name", &Chasm_VM::last_source_proc_name },
 }};

 auto it = static_map.find(key);
 if(it != static_map.end())
 {
  key = (this->**it)();
 }
}

void Chasm_VM::parse_fn_line(QString line)
{
// if(line[3] == 'p')
// {
//  ++source_fn_anon_count_;
//  source_proc_names_.push(current_source_proc_name_);
//  current_source_proc_name_ = QString::number(source_fn_anon_count_).prepend(';');
// }
// else if(line[3] == 'e')
// {
//  last_source_proc_name_ = current_source_proc_name_;
//  current_source_proc_name_ = source_proc_names_.pop();
// }
// else
// {
//  QString fn = line.mid(3).simplified();
// }
}


void Chasm_VM::read_local_program(QString lines)
{
 int pos = 0;
 int end = lines.length();

 while(pos < end)
 {
  int np = lines.indexOf(";.\n", pos);
  if(np == -1)
    np = lines.indexOf("\n.\n", pos);
  if(np == -1)
    break;
  QString l = lines.mid(pos, np - pos).trimmed();
  if(l.startsWith(".;"))
  {
   pos = np + 3;
   continue;
  }
  if(l.startsWith("@fn"))
  {
   parse_fn_line(l);
   pos = np + 3;
   continue;
  }

  bool reread = false;
  int mp = l.indexOf(" $");
  if(mp == -1)
  {
   mp = l.indexOf(" @");
   reread = true;
  }
  if(mp != -1)
  {
   QString l1 = l.mid(0, mp).trimmed();
   QString l2 = l.mid(mp + 2, np - mp - 2).trimmed();
   if(reread)
     reread_substitute(l2);
   read_line(l1, l2);
  }
  else
  {
   read_line(l.trimmed());
  }
  pos = np + 3;
 }
 //run_lines(starting_source_proc_name_);
}

void Chasm_VM::run_current_source_proc_name()
{
 run_lines(current_source_proc_name_);
}

void Chasm_VM::read_line(QString inst)
{
 static QMap<QString, void(Chasm_Runtime_Bridge::*)()> static_map {{
  { "new_call_package", &Chasm_Runtime_Bridge::new_call_package },
  { "load_type_ref", &Chasm_Runtime_Bridge::load_type_ref },
  { "load_type_u1", &Chasm_Runtime_Bridge::load_type_u1 },
  { "load_type_u2", &Chasm_Runtime_Bridge::load_type_u2 },
  { "load_type_QString", &Chasm_Runtime_Bridge::load_type_QString },
  { "load_type_u4", &Chasm_Runtime_Bridge::load_type_u4 },
  { "load_type_QByteArray", &Chasm_Runtime_Bridge::load_type_QByteArray },
  { "load_type_r8", &Chasm_Runtime_Bridge::load_type_r8 },
  { "load_type_QVariant", &Chasm_Runtime_Bridge::load_type_QVariant },
  { "load_type_n8", &Chasm_Runtime_Bridge::load_type_n8 },
  { "load_type_ptr", &Chasm_Runtime_Bridge::load_type_ptr },

  { "push_carrier_deque", &Chasm_Runtime_Bridge::push_carrier_deque },
  { "gen_carrier", &Chasm_Runtime_Bridge::gen_carrier},
  { "reset_loaded_raw_value", &Chasm_Runtime_Bridge::reset_loaded_raw_value },
  { "reset_type_object", &Chasm_Runtime_Bridge::reset_type_object },
  { "add_carriers", &Chasm_Runtime_Bridge::add_carriers },
  { "reset_carrier_deque", &Chasm_Runtime_Bridge::reset_carrier_deque },
  { "init_new_ghost_scope", &Chasm_Runtime_Bridge::init_new_ghost_scope },
  { "clear_current_ghost_scope", &Chasm_Runtime_Bridge::clear_current_ghost_scope },
 }};

 auto it = static_map.find(inst);
 if(it != static_map.end())
 {
  line_ops_[current_source_proc_name_].push_back({nullptr, fn_u{.fn0 = it.value()}});
 }
}

void Chasm_VM::read_line(QString inst, QString arg)
{
 static QMap<QString, void(Chasm_Runtime_Bridge::*)(QString)> static_map {{
  { "add_new_channel", &Chasm_Runtime_Bridge::add_new_channel },
  { "gen_carrier_tvr", &Chasm_Runtime_Bridge::gen_carrier_tvr },
  { "run_eval", &Chasm_Runtime_Bridge::run_eval },
 }};

 auto it = static_map.find(inst);
 if(it != static_map.end())
 {
  QString* a = new QString(arg);
  line_ops_[current_source_proc_name_].push_back({a, fn_u{.fn1=it.value()}});
 }
}

void Chasm_VM::run_lines(QString source_proc_name)
{
 auto it = line_ops_.find(source_proc_name);
 if(it == line_ops_.end())
   return;
 const QVector<QPair<QString*, fn_u>>& lines = it.value();
 for(auto& pr: lines)
 {
  if(pr.first)
    (crb_->*(pr.second.fn1))(*pr.first);
  else
    (crb_->*(pr.second.fn0))();
 }
}

