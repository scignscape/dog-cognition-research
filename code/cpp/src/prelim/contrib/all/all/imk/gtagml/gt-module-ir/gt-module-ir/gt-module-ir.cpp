
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "gt-module-ir.h"

#include "gtagml-dgh-module.h"

#include <QDebug>

#include "textio.h"

USING_KANS(TextIO)

USING_KANS(DGH)


GT_Module_IR::GT_Module_IR()
  :  line_translate_fn_(nullptr),
     cmd_translate_fn_(nullptr)
{
 gtagml_module_ = new GTagML_DGH_Module;
}


QString GT_Module_IR::first_non_flag_arg(const QStringList& qsl, QVector<QChar>& firsts,
  QMap<QString, u1>* flagset, QMap<QString, QString>* flagpairs)
{
 u1 pos = 0;
 QString result;
 bool have_result = false;
 QString held_flag;
 for(QString qs : qsl)
 {
  if(qs.isEmpty())
    continue;

  ++pos;
  int which = 0;
  int count = 0;

  for(QChar qc : firsts)
  {
   ++count;
   if(qs.at(0) == qc)
   {
    which = count;
    break;
   }
  }
  if(which)
  {
   if(flagset)
   {
    if(have_result)
    {
      // // have_result will only be true if flagpairs is non-null
     if(!held_flag.isEmpty())
       (*flagpairs)[held_flag] = QString{};
     held_flag = qs;
    }
    else
      (*flagset)[qs] = pos;
   }
   continue;
  }
  if(flagpairs)
  {
   if(have_result)
   {
    if(flagpairs->contains(held_flag))
      (*flagpairs)[held_flag] += "$$";
    (*flagpairs)[held_flag] += qs;
   }
   else
   {
    have_result = true;
    result = qs;
   }
  }
  else
    return qs;
 }
 return result;
}


QString GT_Module_IR::first_non_flag_arg(const QStringList& qsl, QString firsts,
  QMap<QString, u1>* flagset, QMap<QString, QString>* flagpairs)
{
 if(firsts.isEmpty())
   return {};
 QVector<QChar> qchars;
 qchars.resize(firsts.length());
// for(QChar qc : firsts)
//   qchars << qc;
 std::copy(firsts.begin(), firsts.end(), qchars.begin());
 return first_non_flag_arg(qsl, qchars, flagset, flagpairs);
}

QString GT_Module_IR::first_non_flag_arg(const QStringList& qsl,
  QMap<QString, u1>* flagset, QMap<QString, QString>* flagpairs)
{
 return first_non_flag_arg(qsl, ":-", flagset, flagpairs);
}


void GT_Module_IR::check_translate_line(QString& l)
{
 if(line_translate_fn_)
   line_translate_fn_(l);
 else
   l = l.simplified();
}

void GT_Module_IR::check_translate_cmd(QString& c)
{
 if(cmd_translate_fn_)
   cmd_translate_fn_(c);
 else
   c.replace('-', '_');
}


void GT_Module_IR::run_lines(QString proc_name)
{
 auto it = line_ops_.find(proc_name);
 if(it == line_ops_.end())
   return;

 const QList<line_op_info>& lines = it.value();
 for(auto& line: lines)
 {
  if(line.cmd)
  {
   auto ff = (void(GTagML_DGH_Module::*)(QString)) line.fn.fn1;
   (gtagml_module_->*(ff))(*line.cmd);
  }
  else
  {
   auto ff = (void(GTagML_DGH_Module::*)()) line.fn.fn0;
   (gtagml_module_->*(ff))();
  }
 }
}

void GT_Module_IR::read_lines(QString lines)
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

  check_translate_line(l);

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
   check_translate_cmd(l1);
   QString l2 = l.mid(mp + 2, np - mp - 2).trimmed();
//?
//   if(reread)
//     reread_substitute(l2);
   read_line(l1, l2);
  }
  else
  {
   read_line(l);
  }
  pos = np + 3;
 }

}

void GT_Module_IR::read_line(QString inst, QString arg)
{
 static QMap<QString, QPair<void*, fn1_t>> static_map {{

  { "gt_compile_file",
    { gtagml_module_, (fn1_t) &GTagML_DGH_Module::compile_gt_file} },

  { "gt_compile_folder",
    { gtagml_module_, (fn1_t) &GTagML_DGH_Module::compile_gt_folder} },

  { "gt_compile_manuscript",
    { gtagml_module_, (fn1_t) &GTagML_DGH_Module::compile_gt_manuscript} },


 }};

 auto it = static_map.find(inst);
 if(it != static_map.end())
 {
  QString* a = new QString(arg);
  line_ops_[current_proc_name_]
    .push_back({it.value().first, a, fn_u{.fn1=it.value().second}});
 }
}


void GT_Module_IR::read_line(QString inst)
{
 static QMap<QString, QPair<void*, fn0_t>> static_map {{

 }};

 auto it = static_map.find(inst);
 if(it != static_map.end())
 {
  line_ops_[current_proc_name_]
    .push_back({it.value().first, nullptr, fn_u{.fn0=it.value().second}});
 }

}


void GT_Module_IR::parse_fn_line(QString line)
{
// if(line[3] == 'p')
// {
//  ++source_fn_anon_count_;
//  source_fn_names_.push(current_source_fn_name_);
//  current_source_fn_name_ = QString::number(source_fn_anon_count_).prepend(';');
// }
// else if(line[3] == 'e')
// {
//  last_source_fn_name_ = current_source_fn_name_;
//  current_source_fn_name_ = source_fn_names_.pop();
// }
// else
// {
  QString fn = line.mid(3).simplified();
// }
}


//void PhaonIR::read_local_program(QString path)
//{
// QString lines;
// load_file(path, lines);

// int pos = 0;
// int end = lines.length();

// while(pos < end)
// {
//  int np = lines.indexOf(";.\n", pos);
//  if(np == -1)
//    np = lines.indexOf("\n.\n", pos);
//  if(np == -1)
//    break;
//  QString l = lines.mid(pos, np - pos).trimmed();
//  if(l.startsWith(".;"))
//  {
//   pos = np + 3;
//   continue;
//  }
//  if(l.startsWith("@fn"))
//  {
//   parse_fn_line(l);
//   pos = np + 3;
//   continue;
//  }

//  bool reread = false;
//  int mp = l.indexOf(" $");
//  if(mp == -1)
//  {
//   mp = l.indexOf(" @");
//   reread = true;
//  }
//  if(mp != -1)
//  {
//   QString l1 = l.mid(0, mp).trimmed();
//   QString l2 = l.mid(mp + 2, np - mp - 2).trimmed();
//   if(reread)
//     reread_substitute(l2);
//   read_line(l1, l2);
//  }
//  else
//  {
//   read_line(l.trimmed());
//  }
//  pos = np + 3;
// }
// run_lines(starting_source_fn_name_);
//}
