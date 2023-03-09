
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "gtagml-folder.h"

#include "gtagml-document.h"

//#include "output/gtagml-output-htxn.h"
//#include "output/gtagml-output-latex.h"
//#include "output/gtagml-output-html.h"


#include <QFile>
#include <QFileInfo>
#include <QRegularExpression>
#include <QDir>
#include <QDebug>

#include "kans.h"

USING_KANS(GTagML)


GTagML_Folder::GTagML_Folder(QString local_path)
 : local_path_(local_path)
{

}

GTagML_Folder::GTagML_Folder(QString local_path, QString first_file_path, 
   QString man_path)
  : local_path_(local_path), 
    first_file_path_(first_file_path), man_path_(man_path),
    project_info_(nullptr)
{

}

void GTagML_Folder::read_output_path(QString path)
{
 QFileInfo qfi(path);
 QFile file(path);
 if(file.open(QFile::ReadOnly | QIODevice::Text))
 {
  output_path_ = file.readAll().trimmed();
  local_path_ = qfi.absolutePath();
  input_path_ = path;
 }
}


void GTagML_Folder::convert_to_latex(std::function<void(QString)> fn)
{
 QDir dir;
  
 QStringList qsl;

 if(!first_file_path_.isEmpty())
   qsl.push_back(first_file_path_);

 if(man_path_.isEmpty())
 {
  dir.setCurrent(local_path_);
  dir.setFilter(QDir::Files 
    | QDir::Hidden | QDir::NoSymLinks);
 }
 else if(man_path_.startsWith(';'))
 {
  dir.setCurrent(man_path_.mid(1));
  dir.setFilter(QDir::Dirs | QDir::NoDotAndDotDot);
//  if(!first_file_path_.isEmpty())
//    qsl.push_back(first_file_path_);
 }
 else
 {
  dir.setCurrent(man_path_);
  dir.setFilter(QDir::Files 
    | QDir::Hidden | QDir::NoSymLinks);
//  if(!first_file_path_.isEmpty())
//    qsl.push_back(first_file_path_);
 }

 dir.setSorting(QDir::Size | QDir::Reversed);

 QFileInfoList qfil = dir.entryInfoList();

 QListIterator<QFileInfo> it(qfil);

 QString cabinet;

 while(it.hasNext())
 {
  QFileInfo qfi = it.next();
  if(qfi.isDir())
  {
   if(man_path_.startsWith(';'))
   {
    QDir idir(qfi.absoluteFilePath());
    idir.setFilter(QDir::Dirs | QDir::Files 
      | QDir::Hidden | QDir::NoSymLinks);
    idir.setNameFilters({"*.ngml"});
    QStringList iqsl = idir.entryList();     
    for(QString iqs : iqsl)
      qsl.push_back(qfi.absoluteFilePath() + "/" + iqs);    
   }
  }
  else if(!man_path_.isEmpty())
    ; // //  nothing, because we're only taking 
       //    other files from the man folder ...
  else if(qfi.suffix() == "ngml")
  {
   qsl << qfi.absoluteFilePath();
  }
 }

 QStringListIterator slit(qsl);
 while(slit.hasNext())
 {
  QString path = slit.next();

  fn(path);

//  GTagML_Document doc;
//  doc.load_and_parse(path);

//  doc.set_annotations(&annotations_);

//  GTagML_Output_Latex nol(doc);
//  nol.export_latex();

// doc.write_local_annotations(path + ".an");

 }
// GTagML_Document::write_annotations(local_path_ + "/annotation-summary.html", annotations_);
}

void GTagML_Folder::convert_to_latex()
{
 convert_to_latex([this](QString path)
 {
  GTagML_Document doc;
  doc.load_and_parse(path);

  doc.set_annotations(&annotations_);

//  GTagML_Output_Latex nol(doc);
//  nol.export_latex();
 });
}

#ifdef HIDE
void GTagML_Folder::convert_all_khif_files(QString khif_dir, QString html_dir)
{
 QDir dir(local_path_);
 dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
 dir.setSorting(QDir::Size | QDir::Reversed);

 QFileInfoList qfil = dir.entryInfoList();

 QListIterator<QFileInfo> it(qfil);

 QStringList qsl;
 QString cabinet;

 while(it.hasNext())
 {
  QFileInfo qfi = it.next();
  if(qfi.suffix() == "ngml")
  {
   qsl << qfi.absoluteFilePath();
  }
 }
 QStringListIterator slit(qsl);
 while(slit.hasNext())
 {
  QString path = slit.next();

  QFileInfo qfi(path);

  GTagML_Document ngd;
  ngd.load_and_parse(path);

  GTagML_Output_Khif ngo(ngd);

  QString flo = khif_dir + '/' +
    qfi.completeBaseName() + ".khif";

  QString hlo = html_dir + '/' +
    qfi.completeBaseName() + ".htm";

  file_list_output_[flo] = hlo;

  ngo.export_khif(flo);

  QString s = ngd.khi_info();

  if(s.isEmpty())
  {
   //?
   //QString route = QString("/%1").arg(qfi.completeBaseName());
   //non_partials_codes_[route] = flo;
  }
  else
  {
   QStringList qsl = s.split(QRegularExpression("\\s+"), QString::SkipEmptyParts);
   if(qsl.count() > 1)
   {
    if(qsl[1] == "p")
    {
     partials_codes_[qsl[0]] = flo;
    }
    else if(qsl[1] == "s")
     non_partials_codes_[qsl[0]] = flo;
   }
   else if(qsl.count() == 1)
   {
    non_partials_codes_[qsl[0]] = flo;
   }
   CAON_DEBUG_NOOP
  }
 }
}
#endif //def HIDE

void GTagML_Folder::output_file_list(QString& result, const QMap<QString, QString>& files)
{
 QMapIterator<QString, QString> it(files);
 while(it.hasNext())
 {
  it.next();
  QString k = it.key();
  if(k.startsWith('/'))
   k.remove(0, 1);
  QString v = it.value();
  result += QString(" \"%1\" \n  \"%2\"\n")
    .arg(v).arg(file_list_output_[v]);
 }
}

QString GTagML_Folder::output_file_list()
{
 QString result;

 output_file_list(result, partials_codes_);
 output_file_list(result, non_partials_codes_);
 return result;
}


QString GTagML_Folder::partials_codes_to_lisp()
{
 QString result;
 QMapIterator<QString, QString> it(partials_codes_);
 while(it.hasNext())
 {
  it.next();
  QString k = it.key();
  if(k.startsWith('/'))
   k.remove(0, 1);
  QString v = it.value();
  result += QString("\n (setf (gethash :@@%1 khi-forms::*partials*) \"%2\")").arg(k).arg(v);
 }
 return result;
}

void GTagML_Folder::get_gtagml_files(QStringList& result, QString first_file)
{
 QDir dir(local_path_);
 dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
 dir.setSorting(QDir::Size | QDir::Reversed);

 QFileInfo qfia(first_file);

 QFileInfoList qfil = dir.entryInfoList();

 QListIterator<QFileInfo> it(qfil);

 while(it.hasNext())
 {
  QFileInfo qfi = it.next();
  if(qfi == qfia)
    result.push_front(qfi.absoluteFilePath());
  else if(qfi.suffix() == "gt")
    result << qfi.absoluteFilePath();
  else if(qfi.suffix() == "gtagml")
    result << qfi.absoluteFilePath();

 }
}


void GTagML_Folder::convert_all_files(void(*fn)(QString,
  GTagML_Project_Info*, GTagML_Folder*))
{
 QString first_file;
 if(!first_file_path_.isEmpty())
 {
  QString suffix;
  QFileInfo qfi(first_file_path_);
  if(qfi.suffix().isEmpty())
    suffix = ".gt";
  if(qfi.isAbsolute())
    first_file = qfi.absoluteFilePath() + suffix;
  else
    first_file = QString("%1/%2%3").arg(local_path_).arg(first_file_path_).arg(suffix);
 }
 QStringList files;
 get_gtagml_files(files, first_file);
 //QString setup;
 for(QString f: files)
 {
  fn(f, project_info_, this);
 }
}

void GTagML_Folder::convert_all_files(QString output_path, QString khif_path)
{
 QDir dir(local_path_);
 dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
 dir.setSorting(QDir::Size | QDir::Reversed);

 QFileInfoList qfil = dir.entryInfoList();

 QListIterator<QFileInfo> it(qfil);

 QStringList qsl;
 QString cabinet;

 while(it.hasNext())
 {
  QFileInfo qfi = it.next();
  if(qfi.suffix() == "ngml")
  {
   qDebug() << qfi.absoluteFilePath();
   if(qfi.baseName() == "cabinet")
   {
    cabinet = qfi.absoluteFilePath();
   }
   else
   {
    qsl << qfi.absoluteFilePath();
   }
  }
 }

 if(!cabinet.isEmpty())
 {
  qsl << cabinet;
 }

 QStringListIterator slit(qsl);
 while(slit.hasNext())
 {
  QString path = slit.next();

  QFileInfo qfi(path);

  GTagML_Document ngd;
  ngd.load_and_parse(path);

//  GTagML_Output_Html ngo(ngd);
//  ngo.export_html(output_path + '/' + qfi.completeBaseName() + ".html");

//  // //?
//  GTagML_Output_HTXN noh(ngd, nullptr);
//  noh.export_htxne(output_path + '/' + qfi.completeBaseName() + ".htxne");

//  GTagML_Output_Latex nol(ngd);
//  nol.export_latex(output_path + '/' + qfi.completeBaseName() + ".tex");


//?  if(!khif_path.isEmpty())
//?  {
//?   GTagML_Output_Khif khif(ngd);
//?   khif.export_khif(khif_path + '/' + qfi.completeBaseName() + ".khif");
//?  }

 }
}


void GTagML_Folder::convert_all_files()
{
 convert_all_files(output_path_);
}


void GTagML_Folder::display_user_highlights()
{
 QFile file(input_path_ + ".usrh.txt");
 if(file.open(QFile::WriteOnly | QIODevice::Text))
 {
  QTextStream qts(&file);
   //  QMap<QString, int>& uh = user_highlights_;
  QMapIterator<QString, int> it(user_highlights_);
  while(it.hasNext())
  {
   it.next();
   QString text = it.key();
   int num = it.value();
   qts << text << ' ' << num <<"\n";
  }
  file.close();
 }

}
