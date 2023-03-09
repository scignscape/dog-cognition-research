

//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include <QString>
#include <QDebug>

#include "global-types.h"

#include "global-macros.h"

#include "textio.h"
USING_KANS(TextIO)


#define _Continue_term return 0
#define _Continue_preterm return 0
#define _Continue_1(x) _Continue_ ## x
#define continue(...) _preproc_CONCAT(_Continue_, _preproc_NUM_ARGS (__VA_ARGS__)) (__VA_ARGS__)


#define _Continue_0 continue;

#define continues return 0;

//#define continue (...) continue ## __VA_ARGS__

//#define continues (...) _preproc_CONCAT(_Continue_, _preproc_NUM_ARGS (__VA_ARGS__)) (__VA_ARGS__)
//#define _Continue_0 return 0;
//#define _Continue_1(x) _Continue_ ## x;

 //continue;

#include <QMessageBox>
#include <QClipboard>
#include <QGuiApplication>
#include <QPushButton>
#include <QDirIterator>

#include <QRegularExpression>

#include <QProcess>


#include <QNetworkAccessManager>
#include <QNetworkReply>

#include <QLibrary>

#include <QApplication>


//  /media/nlevisrael/OS/nc/ar/bunny/youtube




void _get_yts(QStringList* qsl, u2 index, u2 end)
{
// QString working = "/home/nlevisrael/gits/ctg-temp/stella/yt-dlp/temp";
// QString names_file = "/home/nlevisrael/gits/ctg-temp/stella/yt-dlp/names.txt";
//? QString links_file = "/home/nlevisrael/gits/ctg-temp/stella/yt-dlp/stella/tiktok-links.txt";


// QString working = "/home/nlevisrael/gits/ctg-temp/stella/yt-dlp/temp";
// QString names_file = "/home/nlevisrael/gits/ctg-temp/stella/yt-dlp/names.txt";

 QString working = "/home/nlevisrael/gits/ctg-temp/stella/yt-dlp/stella-yts/temp";
 QString names_file = "/home/nlevisrael/gits/ctg-temp/stella/yt-dlp/stella-yts/names.txt";


 QProcess* cmd = new QProcess;

 QString url = qsl->value(index); //"https://www.tiktok.com/@whataboutbunny/video/6832653004005526789";

 if(url.isEmpty())
   return;

 url.prepend("https://www.youtube.com/@hungerforwords/shorts/");

 QStringList options;
 options << "-v";
 options << url;

 cmd->setWorkingDirectory(working);

 QObject::connect(cmd,
   QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
   [working, cmd, qsl, index, end, names_file, url](int exit_code, QProcess::ExitStatus exit_status)
 {
  QDir qd(working);
  QFileInfoList qfil = qd.entryInfoList(QDir::Files);

  qDebug() << qfil.size();

  qDebug() << "\nerr: " << cmd->readAllStandardError();
  qDebug() << "\nout: " << cmd->readAllStandardOutput();

  if(qfil.isEmpty())
  {
   qDebug() << "unexpected empty folder";
   return;
  }

  u2 new_index = index + 1;

  QFileInfo qfi = qfil.first();

  qDebug() << "name: " << qfi.fileName();

  QFile qf(names_file);

  qf.open(QIODevice::WriteOnly | QFile::Append);
  QTextStream out(&qf); // = new QTextStream(qf);
  out << "\n" << new_index << ": " << url << " = " << qfi.fileName() << "\n";

//?  QString pattern = "https://www.tiktok.com/@whataboutbunny/video/";
  QString pattern = "https://www.tiktok.com/@hunger4words/video/";
  QString cut_url = url;
  if(url.startsWith(pattern))
  {
   cut_url = url.mid(pattern.length());
  }

  QString target_file_name = "%1-%2"_qt.arg(new_index).arg(cut_url);

  QString target_folder = "/media/nlevisrael/OS/nc/ar/stella/youtube/shorts";
//  QString target_folder = "/home/nlevisrael/gits/ctg-temp/stella/yt-dlp/stella/tempd";


  copy_binary_file_to_folder_with_rename(qfi.absoluteFilePath(), target_folder, target_file_name,
    qfi.suffix());

//?  QFile::rename(qfi.absoluteFilePath(), qfi.absolutePath() + "/" + target_file_name);
  QFile::remove(qfi.absoluteFilePath());

  cmd->deleteLater();

//  if(index <= end)
//  {
//   _get_yts(qsl, new_index, end);
//  }

 });

 cmd->setProgram("yt-dlp");
 cmd->setArguments(options);
 cmd->start();

}


// /home/nlevisrael/gits/ctg-temp/stella/yt-dlp/stella-yts/playlist

#include <QCollator>

void instagram_temp()
{
 QString folder = "/media/nlevisrael/OS/nc/ar/bunny/youtube";

 QDir qd(folder);

// QFileInfoList qfil = qd.entryInfoList();
 QStringList qfil = qd.entryList(QDir::Files);

 QStringList copy = qfil;

 QCollator collator;
 collator.setNumericMode(true);

 std::sort(qfil.begin(), qfil.end(), collator);

 QMap<QString, QPair<QString, int>> order;

 int c = 0;

 for(QString fn : qfil)
 {
  QRegularExpression qre("-([\\w-]+)\\.(\\w+)");

  QRegularExpressionMatch m = qre.match(fn);

  QString code = m.captured(1);
  QString c2 = m.captured(2);
  order[code] = {c2, c};
  ++c;
 }

 for(QString fn : copy)
 {
  QRegularExpression qre("-([\\w-]+)\\.");

  QString code = qre.match(fn).captured(1);

  QString nfn = "%1-%2.%3"_qt.arg(order[code].second + 1).arg(code).arg(order[code].first);
  qDebug() << fn << " -> " << nfn;

  if(fn == nfn)
    continue;

  QFile::rename(qd.absoluteFilePath(fn), qd.absoluteFilePath(nfn));
 }


// qDebug() << qfil;

}

void instagram_temp22()
{
 QString summary = "/home/nlevisrael/gits/ctg-temp/stella/yt-dlp/stella-yts/summary.txt";
 QString nsummary = "/home/nlevisrael/gits/ctg-temp/stella/yt-dlp/stella-yts/nsummary.txt";

 QString text = load_file(summary);
 QStringList ltext = text.split("\n", QString::SkipEmptyParts);

// QStringList

 QMap<u1, QString> new_lines;

 for(QString line : ltext)
 {
  QStringList parts = line.split(" = ");

  QString fname = parts.value(0);
  QString desc = parts.value(1);

  int index = fname.indexOf('-');

  int count = fname.left(index).toUInt();

  count = 47 - count;

  fname.replace(0, index, QString::number(count));

  new_lines[count] = fname + " = " + desc;
 }

 QString new_text;
 for(int  i = 1; i <= 46; ++i)
 {
  new_text.push_back(new_lines[i] + "\n");
 }

 save_file(nsummary, new_text);

}

void instagram_temp21()
{
 QString rtarget = "/media/nlevisrael/OS/nc/ar/stella/youtube/shorts";
 QDir qd(rtarget);

 QFileInfoList qfil = qd.entryInfoList(QDir::Files);

 for(QFileInfo qfi : qfil)
 {
  QString fn = qfi.absoluteFilePath();
  fn.replace("webm.webm", "webm");

  QFile::rename(qfi.absoluteFilePath(), fn);
 }

}

void instagram_temp20()
{
 QString target = "/home/nlevisrael/gits/ctg-temp/stella/yt-dlp/stella-yts/target";
// QString rtarget = "/home/nlevisrael/gits/ctg-temp/stella/yt-dlp/stella-yts/rtarget";

 QString rtarget = "/media/nlevisrael/OS/nc/ar/stella/youtube/shorts";


 QDir qd(target);

 QFileInfoList qfil = qd.entryInfoList(QDir::Files);

 for(QFileInfo qfi : qfil)
 {
  QString fn = qfi.fileName();

  int index = fn.indexOf('-');

  if(index == -1)
    continue;

  int count = fn.left(index).toUInt();

  count = 47 - count;

  fn.replace(0, index, QString::number(count));

  copy_binary_file_to_folder_with_rename(qfi.absoluteFilePath(), rtarget, fn, qfi.suffix());
 }




}

void instagram_temp19()
{
 QString nfile = "/home/nlevisrael/gits/ctg-temp/stella/yt-dlp/stella-yts/notes.txt";
 QString folder = "/home/nlevisrael/gits/ctg-temp/stella/yt-dlp/stella-yts/playlist";
 QString nfolder = "/home/nlevisrael/gits/ctg-temp/stella/yt-dlp/stella-yts/target";
 QString sfile = "/home/nlevisrael/gits/ctg-temp/stella/yt-dlp/stella-yts/summary.txt";

 QString ntext = load_file(nfile);

 QStringList ns = ntext.split("\n", QString::SkipEmptyParts);

 QMap<QString, QPair<u1, QString>> codes;
 u1 count = 0;
 for(QString line : ns)
 {
  ++count;

  QStringList inner = line.split(" = ");

  codes[inner.value(0)] = {count, inner.value(1)};

 }

 QDir qd(folder);

 QFileInfoList qfil = qd.entryInfoList(QDir::Files);

 QStringList summary;

 for(QFileInfo qfi : qfil)
 {
  QString fn = qfi.fileName();

  QRegularExpression qre("\\[([\\w-]+)\\]");

  QRegularExpressionMatch match =  qre.match(fn);
  if(match.hasMatch())
  {
   QString url_code = match.captured(1);

   QPair<u1, QString> code = codes[url_code];

   qDebug() << code.first << " - " << url_code << " = " << code.second;

   QString file_name = "%1-%2"_qt.arg(code.first).arg(url_code);

   summary.push_back(file_name + " = " + code.second);

   copy_binary_file_to_folder_with_rename(qfi.absoluteFilePath(), nfolder, file_name);
  }



 }

 save_file(sfile, summary.join("\n"));
}



void instagram_temp18()
{
 QString path = "/home/nlevisrael/gits/ctg-temp/stella/yt-dlp/yt.txt";
 QString nfile = "/home/nlevisrael/gits/ctg-temp/stella/yt-dlp/stella-yts/notes.txt";

 QString text = load_file(path);

//?
 QRegularExpression qre("\"videoId\":\"([\\w-]+)\",\"headline\":\\{\"simpleText\":\"([^\"]+)\"");
// QRegularExpression qre("\"videoId\":\"([\\w-]+)\",\"headline\":");

 QRegularExpressionMatchIterator it =  qre.globalMatch(text);

 QStringList refs;

 while(it.hasNext())
 {
  QRegularExpressionMatch qrm = it.next();

  refs.push_back(qrm.captured(1) + " = " + qrm.captured(2));
 }

 QString ntext = refs.join("\n");
 save_file(nfile, ntext);



  // "/shorts/";

}



void instagram_temp17()
{
 //QString links_file = "/home/nlevisrael/gits/ctg-temp/stella/yt-dlp/tiktok-links";
// QString links_file = "/home/nlevisrael/gits/ctg-temp/stella/yt-dlp/stella/tiktok-links.txt";
 QString names_file = "/home/nlevisrael/gits/ctg-temp/stella/yt-dlp/stella-yts/n.txt";

 QString text = load_file(names_file);

 QStringList* links = new QStringList(text.split("\n", QString::SkipEmptyParts));

// qDebug() << "links " << *links;

 // // don't necessarily start at the beginning ...

// _get_yts(links, 0, 6);


}



void instagram_temp16()
{
 QString path = "/home/nlevisrael/gits/ctg-temp/stella/yt-dlp/yt.txt";
 QString nfile = "/home/nlevisrael/gits/ctg-temp/stella/yt-dlp/n.txt";

 QString text = load_file(path);

 QRegularExpression qre("/shorts/([\\w-]+)");

 QRegularExpressionMatchIterator it =  qre.globalMatch(text);

 QStringList refs;

 while(it.hasNext())
 {
  QRegularExpressionMatch qrm = it.next();

  refs.push_back(qrm.captured(1));
 }

 QString ntext = refs.join("\n");
 save_file(nfile, ntext);



  // "/shorts/";

}


void instagram_temp15()
{
 QString folder = "/media/nlevisrael/OS/nc/ar/bunny/youtube";
 QString cfolder = "/media/nlevisrael/OS/nc/ar/bunny/cyoutube";

 QDir qdir(cfolder);

 QDirIterator qd(folder, QDir::Files);

 while(qd.hasNext())
 {
  QString path = qd.next();
  QFileInfo qfi(path);

  QString fn = qfi.fileName();

  int index = fn.indexOf('-');

  if(index == -1)
    continue;

  u2 count = fn.left(index).toUInt();
  count = 135 - count;

  fn = fn.mid(index);
  fn.prepend(QString::number(count));

  qDebug() << qfi.absoluteDir().filePath(fn);

  QString source = qfi.absoluteFilePath();
  QString target = qdir.filePath(fn);

  qDebug() << source << " -> " << target;


  QFile::copy(source, target);

 }


}


void _get_tiktok(QStringList* qsl, u2 index, u2 end)
{
// QString working = "/home/nlevisrael/gits/ctg-temp/stella/yt-dlp/temp";
// QString names_file = "/home/nlevisrael/gits/ctg-temp/stella/yt-dlp/names.txt";
//? QString links_file = "/home/nlevisrael/gits/ctg-temp/stella/yt-dlp/stella/tiktok-links.txt";


// QString working = "/home/nlevisrael/gits/ctg-temp/stella/yt-dlp/temp";
// QString names_file = "/home/nlevisrael/gits/ctg-temp/stella/yt-dlp/names.txt";

 QString working = "/home/nlevisrael/gits/ctg-temp/stella/yt-dlp/stella/temp";
 QString names_file = "/home/nlevisrael/gits/ctg-temp/stella/yt-dlp/stella/names.txt";


 QProcess* cmd = new QProcess;

 QString url = qsl->value(index); //"https://www.tiktok.com/@whataboutbunny/video/6832653004005526789";

 if(url.isEmpty())
   return;

 QStringList options;
 options << "-v";
 options << url;

 cmd->setWorkingDirectory(working);

 QObject::connect(cmd,
   QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
   [working, cmd, qsl, index, end, names_file, url](int exit_code, QProcess::ExitStatus exit_status)
 {
  QDir qd(working);
  QFileInfoList qfil = qd.entryInfoList(QDir::Files);

  qDebug() << qfil.size();

  qDebug() << "\nerr: " << cmd->readAllStandardError();
  qDebug() << "\nout: " << cmd->readAllStandardOutput();

  if(qfil.isEmpty())
  {
   qDebug() << "unexpected empty folder";
   return;
  }

  u2 new_index = index + 1;

  QFileInfo qfi = qfil.first();

  qDebug() << "name: " << qfi.fileName();

  QFile qf(names_file);

  qf.open(QIODevice::WriteOnly | QFile::Append);
  QTextStream out(&qf); // = new QTextStream(qf);
  out << "\n" << new_index << ": " << url << " = " << qfi.fileName() << "\n";

//?  QString pattern = "https://www.tiktok.com/@whataboutbunny/video/";
  QString pattern = "https://www.tiktok.com/@hunger4words/video/";
  QString cut_url = url;
  if(url.startsWith(pattern))
  {
   cut_url = url.mid(pattern.length());
  }

  QString target_file_name = "%1-%2"_qt.arg(new_index).arg(cut_url);

  QString target_folder = "/media/nlevisrael/OS/nc/ar/tiktok/stella/target";
//  QString target_folder = "/home/nlevisrael/gits/ctg-temp/stella/yt-dlp/stella/tempd";


  copy_binary_file_to_folder_with_rename(qfi.absoluteFilePath(), target_folder, target_file_name,
    qfi.suffix());

//?  QFile::rename(qfi.absoluteFilePath(), qfi.absolutePath() + "/" + target_file_name);
  QFile::remove(qfi.absoluteFilePath());

  cmd->deleteLater();

  if(index <= end)
  {
   _get_tiktok(qsl, new_index, end);
  }

 });

 cmd->setProgram("yt-dlp");
 cmd->setArguments(options);
 cmd->start();

}


void instagram_temp13()
{
 //QString links_file = "/home/nlevisrael/gits/ctg-temp/stella/yt-dlp/tiktok-links";
 QString links_file = "/home/nlevisrael/gits/ctg-temp/stella/yt-dlp/stella/tiktok-links.txt";

 QString text = load_file(links_file);

 QStringList* links = new QStringList(text.split("\n", QString::SkipEmptyParts));

// qDebug() << "links " << *links;

 // // don't necessarily start at the beginning ...

 _get_tiktok(links, 28, 28);


}

void instagram_temp14()
{
 QString names_file = "/home/nlevisrael/gits/ctg-temp/stella/yt-dlp/names.txt";

 QString report_file = "/home/nlevisrael/gits/ctg-temp/stella/yt-dlp/report.txt";

 QString links_file = "/home/nlevisrael/gits/ctg-temp/stella/yt-dlp/tiktok-links";

 QString text = load_file(links_file);

 QStringList links = text.split("\n", QString::SkipEmptyParts);


 QMap<u2, QStringList> names;

 load_file(names_file, [&names](QString name)
 {
  if(name.isEmpty())
   return 0;

  u2 index1 = name.indexOf(':');
  u2 index2 = name.indexOf('=');

  u2 number = name.left(index1).toUInt();
//  qDebug() << "number = " << number;

  QString url = name.mid(index1 + 2, index2 - index1 - 3);
//  qDebug() << "url = " << url;

  name = name.mid(index2 + 2).replace('?', '/').toLatin1().replace('?', "").replace('/', '?');

//  qDebug() << "name = " << name;

  names[number].push_back(url);
  names[number].push_back(name);

  return 0;
 });

 QStringList lines;

 for(u2 index = 1; index <= 808; ++index)
 {
  QString line;
  if(names.contains(index))
  {
   line = "%1\n%2\n%3\n\n"_qt.arg(index).arg(names[index].value(0)).arg(names[index].value(1));
  }
  else
  {
   QString link = links.value(index - 1);
   QString line = "?%1: %2"_qt.arg(index).arg(link);
  }
  lines.push_back(line);
 }

 save_file(report_file, lines.join("\n"));
}






void instagram_temp11()
{
 //QString file = "/media/nlevisrael/OS/nc/ar/links";
 QString file = "/home/nlevisrael/gits/ctg-temp/stella/yt-dlp/stella/links.txt";

 load_file(file, [](QString line)
 {
  int index = line.indexOf("?");
  line = line.left(index);
  qDebug() << "line = " << line;
  return 0;
 });


}

void instagram_temp10()
{

// QString file = "/media/nlevisrael/OS/nc/ar/links";
 QString file = "/home/nlevisrael/gits/ctg-temp/stella/yt-dlp/stella/links.txt";

 QFile* qf = new QFile(file);

 qf->open(QIODevice::WriteOnly | QFile::Append);

// QTextStream* out = new QTextStream(qf);

 QClipboard* c = QApplication::clipboard();
 QObject::connect(c, &QClipboard::dataChanged,
  [c, qf]()
 {
  QTextStream out(qf); // = new QTextStream(qf);
  out << c->text() << "\n";
  qDebug() << c->text();
 });
}


void instagram_temp9()
{
 QString file = "/media/nlevisrael/OS/nc/ar/il";

// /media/nlevisrael/OS/nc/ar/il

 QString nfile = "/media/nlevisrael/OS/nc/ar/refs";
 QString text = load_file(file);

// QRegularExpression qre("https://www.tiktok.com/@whataboutbunny/video/\\d+");
// QRegularExpression qre("\\d+");
 QRegularExpression qre("\"(\\d+)\"");

 QRegularExpressionMatchIterator it =  qre.globalMatch(text);

 QStringList refs;

 while(it.hasNext())
 {
  QRegularExpressionMatch qrm = it.next();

  refs.push_back(qrm.captured(1));
 }

 QString ntext = refs.join("\n");
 save_file(nfile, ntext);


}


void instagram_temp8()
{
//? QString dir = "/media/nlevisrael/OS/nc/ar/bunny/youtube";
 QString dir = "/media/nlevisrael/OS/nc/ar/bunny/instagram";

 QDir qd(dir);

 QFileInfoList qfis = qd.entryInfoList(QDir::Files);

 for(QFileInfo qfi : qfis)
 {
  QString name = qfi.fileName();
  name.replace(".mp4.mp4.mp4", ".mp4");
  name.replace(".mkv.mkv.mkv", ".mkv");
  qd.rename(qfi.fileName(), name);
  //renam
//  copy_binary_file_to_folder_with_rename(qfi.absoluteFilePath(), ndir, name);

 }
// for(u1 i = 1; i <= 146; ++i)
// {

// }

}



void instagram_temp7()
{
 QString dir = "/media/nlevisrael/OS/nc/videos";
 QString ndir = "/media/nlevisrael/OS/nc/ar/bunny/youtube";

 QDir qd(dir);

 QFileInfoList qfis = qd.entryInfoList(QDir::Files);

 u1 offset = 0;

 for(QFileInfo qfi : qfis)
 {
  QString name = qfi.fileName();
  u1 count = name.left(3).toUInt();
  if(count == 40 || count == 58 || count == 82 || count == 93
     || count == 132 || count == 139)
  {
   ++offset;
   continue;
  }

  name = name.mid(3);
  count -= offset;
  name.prepend(QString::number(count));
  copy_binary_file_to_folder_with_rename(qfi.absoluteFilePath(), ndir, name);

 }
// for(u1 i = 1; i <= 146; ++i)
// {

// }

}

void instagram_temp6()
{
 QString dir = "/media/nlevisrael/OS/nc/ar/bunny-dbl";
 QString ndir = "/media/nlevisrael/OS/nc/ar/bunny";

 QDir qd(dir);

 QFileInfoList qfis = qd.entryInfoList(QDir::Files);

 u2 size = qfis.size() + 1;

 qDebug() << "size = " << size;

 u2 it = 0;
 for(QFileInfo qfi : qfis)
 {
  ++it;
  //QString src = qfi.absoluteFilePath();
  QString name = qfi.fileName();
  name.replace(".mp4.mp4", ".mp4");
  u1 index = name.indexOf('-');
  u2 count = name.left(index).toUInt();
  count = size - count;

//  qDebug() << "it: " << it << "name: " << name << " " << count;

  name.replace(0, index, QString::number(count));
//  qDebug() << " name: " << name;

  copy_binary_file_to_folder_with_rename(qfi.absoluteFilePath(), ndir, name);

//  videos[count].push_back(name);

 }

// qDebug() << "vsize = " << videos.size();

// for(u2 i = 1; i <= 917; ++i)
// {
//  qDebug() << "i: " << i << " name: " << videos[i];
// }


}








// // borrowed from Forge_Runtime
void _load_ssl_libraries()
{
 QLibrary libcrypto, libssl;
 libcrypto.setFileName(LIBCRYPTO_FILE_NAME); //"/home/nlevisrael/gits/ctg-temp/ssl/install/ldir/libcrypto.so.1.1");
 libssl.setFileName(LIBSSL_FILE_NAME); //"/home/nlevisrael/gits/ctg-temp/ssl/install/ldir/libssl.so.1.1");

 libcrypto.load();
 libssl.load();

 QString qssl = QSslSocket::sslLibraryBuildVersionString();
 qDebug() << "qssl: " << qssl;
}



void _get_url_from_title(QString& title, QVector<QPair<QString, QString>>& urls, QStringList& titles)
{
 u2 count = urls.size();
 title = titles.value(count);
 if(title.isEmpty())
   return;

 QString search = title.replace(' ', '+');
 QString query = "https://www.youtube.com/results?search_query=" + search;//Bunny+interrupts+her+lesson+to+address+more+important+issues

 QNetworkAccessManager* qnam = new QNetworkAccessManager;


 qnam->connect(qnam, &QNetworkAccessManager::finished, [&title, &urls, &titles, qnam, query](QNetworkReply* reply)
 {
  if(reply->error() != QNetworkReply::NoError)
  {
   qDebug() << "error: " << reply->errorString();
   qDebug() << "query: " << query;

   return;
  }

  QString all = QString::fromLatin1(reply->readAll());

  qnam->deleteLater();
  reply->deleteLater();

  QRegularExpression url_regex("watch\\?v=([\\w-]+)");
    //?"url":"/watch?v="

  QRegularExpressionMatch match = url_regex.match(all);
  if(match.hasMatch())
  {
   QString capture = match.captured(1);
   qDebug() << "Url for title %1: %2"_qt.arg(title).arg(capture);
    urls.push_back({capture, title});
  }
  else
    urls.push_back({"?", title});


  if(urls.size() == titles.size())
  {
   QString out;
   QString out_file = "/home/nlevisrael/gits/ctg-temp/dev/documents/i4/stella/bvo";
   for(QPair<QString, QString>& pr : urls)
   {
    out.push_back("%1 == %2\n"_qt.arg(pr.first).arg(pr.second));
   }
   save_file(out_file, out);

   // //  delete title, urls, titles?
  }
  else
    _get_url_from_title(title, urls, titles);

 });

 QNetworkReply* reply = qnam->get(QNetworkRequest(QUrl(query)));

 reply->connect(reply, &QNetworkReply::errorOccurred, [reply, query]()
 {
  QString error = reply->errorString();

  qDebug() << "Caught error: " << error << " = " << reply->error();
 });


}

void instagram_temp00()
{
 _load_ssl_libraries();


 QString list_file = "/home/nlevisrael/gits/ctg-temp/dev/documents/i4/stella/bv";
 QString text;
 load_file(list_file, text);
 QStringList lines = text.split("\n", QString::SplitBehavior::SkipEmptyParts);

 QStringList& titles = *new QStringList;
 QVector<QPair<QString, QString>>& urls = *new QVector<QPair<QString, QString>>;

 bool ready = false;

 for(QString line : lines)
 {
  if(ready)
  {
   ready = false;

   // // actually we should restrict to just "What About Bunny" (maybe without the space),
    //   or "Bunny the talking dog" ...
    //   But for now I just take out the other videos by hand ...
   QStringList parts = line.split('|');
   titles.push_back(parts.value(0).simplified());
  }
  else
    ready = (line == "NOW PLAYING");
 }

 QString& title = *new QString;
 _get_url_from_title(title, urls, titles);

 //manager->get(QNetworkRequest(QUrl("http://qt-project.org")));



}


void instagram_temp1()
{
 //QString new_list_file = "/home/nlevisrael/gits/ctg-temp/stella/yt/t1.txt";
// QString new_list_file = "/home/nlevisrael/gits/ctg-temp/dev/documents/i4/stella/bunny-videos.txt";
 QString new_list_file = "/home/nlevisrael/gits/ctg-temp/dev/documents/i4/stella/bunny-more-videos.txt";

 QString text;
 load_file(new_list_file, text);




 QStringList videos = text.split("\n", QString::SplitBehavior::SkipEmptyParts);

 QVector<QString>& vvideos = *new QVector<QString>(videos.toVector());

 // //  start at?
 u1& count = *new u1(0);

 QString gap(92, ' ');

 QString& next_download = *new QString(vvideos.value(count));

 QMessageBox* mbox = new QMessageBox(QMessageBox::Question,
   "Ready to Download: %1"_qt.arg(next_download),
   "Hit Download to begin" + gap);

// QString& need_copy_path = *new QString;

 QPushButton* download = mbox->addButton("Download", QMessageBox::ActionRole);
 download->disconnect();

 QPushButton* next = mbox->addButton("Next", QMessageBox::ActionRole);
 next->disconnect();
 next->setEnabled(false);

 mbox->connect(download, &QAbstractButton::clicked, [mbox, &count, next, download, &vvideos, &next_download]()
 {
  qDebug() << "download = " << next_download;

  QString path = YOU_TUBE_DOWNLOAD_CMD_FOLDER;
  qDebug() << "path = " << path;

  QDir qd(path);
  QString ap = qd.absoluteFilePath(YOU_TUBE_DOWNLOAD_EXE);

//  qDebug() << "ap = " << ap;

  u4 ix = next_download.indexOf(" == ");
  QStringRef vid = next_download.midRef(0, ix);

  QString outfile = "/home/nlevisrael/gits/ctg-temp/dev/documents/i4/stella/more-videos/%1-%2"_qt
    .arg(count + 1, 3, 10, QChar{'0'}).arg(vid);

  QStringList options;
  options << "-o" << outfile << "--skip-unavailable-fragments"
      << "--no-continue" << "--no-part" << "--no-call-home";

//?  QString url = "https://www.youtube.com/watch?v=" + next_download.mid(4);
  QString url = "https://www.youtube.com/watch?v=" + vid;

  options << url;

  qDebug() << "url = " << url;

  QProcess* cmd = new QProcess;

  mbox->connect(cmd,
    QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
    [cmd, &download, &next_download, &next, &count, &vvideos](int exit_code, QProcess::ExitStatus exit_status)
  {
   qDebug() << "downloaded: " << next_download;

   qDebug() << "std: " << cmd->readAllStandardOutput();
   qDebug() << "err: " << cmd->readAllStandardError();

   download->setEnabled(false);
   next->setEnabled(true);

   cmd->deleteLater();

   bool skip = false;
   do
   {
    ++count;
    if(count == vvideos.size())
    {
     next->setEnabled(false);
     return;
    }
    next_download = vvideos[count];
    if(next_download.endsWith('!'))
      skip = true;
   } while(skip);


  });

  cmd->setProcessChannelMode(QProcess::ForwardedChannels);
  cmd->start(ap, options);


//  if(last_key.isEmpty())

 });


 mbox->connect(next, &QAbstractButton::clicked, [mbox,
   &count, next, download, &vvideos, &next_download]()
 {
  qDebug() << "download = " << next_download;
  download->setEnabled(true);
  next->setEnabled(false);
//  if(last_key.isEmpty())

  mbox->setWindowTitle( "Ready to Download: %1"_qt.arg(next_download) );


 });

 mbox->addButton("Close", QMessageBox::RejectRole);


 mbox->setModal(false);
 mbox->show();


// for(QString v : videos)
// {
//  new_videos.push_back(v.trimmed());
// }

// qDebug() << new_videos;

}


void instagram_temp3()
{
 QString html_file = "/home/nlevisrael/gits/ctg-temp/dev/documents/i4/stella/bunny.txt";
 QString out_file = "/home/nlevisrael/gits/ctg-temp/dev/documents/i4/stella/bunny-videos.txt";

 QString text;
 load_file(html_file, text);

// s4 index = 0, old_index = 0;

 //"text":"Confrontation of Dad Went Poop | What About Bunny"

 QRegularExpression qre("\"title\":\\{\"runs\":\\[\\{\"text\":\"([^\"]+)\"");

 QRegularExpression url_regex("watch\\?v=([\\w-]+)");

 QRegularExpressionMatchIterator it = qre.globalMatch(text);

 QVector<QPair<QString, QString>> videos;

 // //  ranges holds title and start of *next* match;
  //    we look for the video url between the end
  //    of this match and start of the next
 QMap<u4, QPair<QString, u4>> ranges;

 u4 last_end = 0;

 while(it.hasNext())
 {
  QRegularExpressionMatch match = it.next();
  //videos.push_back({match.captured(1), {}});

  QString title = match.captured(1);

//  static QString what_about (" | What About Bunny");
//  if(title.endsWith(what_about))
//    title.chop(what_about.length());
//  else
//    continue;

  ranges[match.capturedEnd()] = {title, 0};

  if(last_end)
    ranges[last_end].second = match.capturedStart();

  last_end = match.capturedEnd();

//  if(videos.contains(match.captured(1)))
//    continue;
//  videos[match.captured(1)] = ++count;

  //index = text.indexOf("| what about ")

 }

 QMapIterator<u4, QPair<QString, u4>> rit(ranges);
 while(rit.hasNext())
 {
  rit.next();

  QRegularExpressionMatch match = url_regex.match(text, rit.key());
  if(match.capturedStart() < rit.value().second)
    videos.push_back({match.captured(1), rit.value().first});
  else
    videos.push_back({"?", rit.value().first});
 }

 QString out_text;

 for(QPair<QString, QString>& pr : videos)
 {
  out_text += "%1 == %2\n"_qt.arg(pr.first).arg(pr.second);
 }

 save_file(out_file, out_text);

// qDebug() << videos;
}

void instagram_temp0()
{
 QString list_file = "/home/nlevisrael/gits/ctg-temp/stella/yt/t1";

 QString new_list_file = "/home/nlevisrael/gits/ctg-temp/stella/yt/t1.txt";

 QString text;
 load_file(list_file, text);

 QRegularExpression qre("watch\\?v=([\\w-]+)");

 QRegularExpressionMatchIterator it = qre.globalMatch(text);

 QMap<QString, u1> videos;
 QVector<QString> vvideos;


 QString out;
 u1 count = 0;

 while(it.hasNext())
 {
  QRegularExpressionMatch match = it.next();
  if(videos.contains(match.captured(1)))
    continue;
  videos[match.captured(1)] = ++count;
 }

 vvideos.resize(videos.size());

 QMapIterator<QString, u1> it1(videos);
 while(it1.hasNext())
 {
  it1.next();
  vvideos[it1.value() - 1] = "%1-%2\n"_qt.arg(it1.value(), 3, 10, QChar{'0'}).arg(it1.key());
 }

 for(QString vvideo : vvideos)
   out += vvideo;



 save_file(new_list_file, out);

 qDebug() << videos.size();

}

void instagram_temp4()
{
//? QString list_folder = "/home/nlevisrael/gits/ctg-temp/dev/documents/i4/stella";
 QString list_folder = "/home/nlevisrael/gits/ctg-temp/dev/documents/i4/stella/bunny";

//? QString ar_folder = "/home/nlevisrael/gits/ctg-temp/ar/dev/dataset/videos/ig";
 QString ar_folder = "/media/nlevisrael/OS/nc/ar/bunny";


 QDir qd(list_folder);

//? for(u1 i = 1; i <= 49; ++i)
 for(u1 i = 1; i <= 230; ++i)
 {
  qd.cd(QString::number(i));

  QFileInfoList qfis = qd.entryInfoList(QDir::Files);

  for(QFileInfo qfi : qfis)
  {
   QString ap = qfi.absoluteFilePath();
//   qDebug() << "ap = " << ap;


   QString fn = qfi.fileName();
   i4 index = fn.indexOf('-');
   u2 count = fn.mid(0, index).toUInt();
   fn = fn.mid(index);
//?   fn.prepend(QString::number(count - 4));
   fn.prepend(QString::number(count));

   qDebug() << "fn = " << fn;

   copy_binary_file_to_folder_with_rename(ap, ar_folder, fn);

  }

  qd.cdUp();
 }

}


void instagram_temp2()
{
 QString list_file = "/home/nlevisrael/gits/ctg-temp/dev/documents/i4/stella/bunny/bunny-links";

 QMap<u1, QList<QPair<QString,QString>>>& files = *new QMap<u1, QList<QPair<QString,QString>>>;
 u1 current_key;

 load_file(list_file, [&files, &current_key](QString line)
 {
//  for(u1 i = 0; i < 10; ++i)
//    continue;

  if(line.isEmpty())
    continue (preterm);
  i4 index = line.lastIndexOf('/');
  if(index == -1)
  {
   current_key = line.trimmed().toUInt();
   continue (preterm);
  }

  QString name = line.mid(index + 1);
  files[current_key].push_back({line, name});
  continue (term);
 });

// qDebug() << files;

 QFileInfo qfi(list_file);

 QDir& qd = *new QDir(qfi.absoluteDir());

// QMapIterator<u1, QList<QPair<QString,QString>>> it(files);

 QString gap(90, ' ');

 QMessageBox* mbox = new QMessageBox(QMessageBox::Question, "Copied: (waiting to start)",
   "Hit Start to begin" + gap);

 QString& last_key = *new QString;
 QString& need_copy_path = *new QString;

 QClipboard* clipboard = QGuiApplication::clipboard();

 QPushButton* go_on = mbox->addButton("Start", QMessageBox::ActionRole);
 go_on->disconnect();

 mbox->addButton("Close", QMessageBox::RejectRole);


 u1 start = 216;
 QPair<u1, u1>& counts = *new QPair<u1, u1>{start, 0};

 // //  in the list file the links are grouped in fours
 u2& last_index = *new u2((start - 1) * 4);


 mbox->connect(mbox, &QMessageBox::rejected, [mbox, &last_key,
   &counts, &qd, &files, &need_copy_path, &last_index]()
 {
  qDebug() << "Ok, closing the message box.";
  delete &last_index;
  delete &files;
  delete &counts;
  delete &qd;
  delete &last_key;
  delete &need_copy_path;
  mbox->deleteLater();
 });

 mbox->connect(go_on, &QAbstractButton::clicked, [mbox, &last_key,
   &counts, go_on, &qd, clipboard, &files, &need_copy_path, &last_index]()
 {
  if(last_key.isEmpty())
  {
   // // just starting
   go_on->setText("Next");

   QString gap(90, ' ');
   mbox->setText("Hit Next to continue" + gap);
  }
  else
  {
   ++last_index;

   QString copy_path = "%1-%2"_qt.arg(last_index).arg(last_key);
   // find a new file

//   QDirIterator qdi(qd);
//   QDirIterator it(folder, QDir::Filter::Dirs | QDir::Filter::NoDotAndDotDot);
   QFileInfoList qfis = qd.entryInfoList(QDir::Files);

   for(QFileInfo qfi : qfis)
   {
    if(qfi.suffix().isEmpty())
      continue;

    qDebug() << "\nFile name: " << qfi.fileName();
    qDebug() << "Copying to: " << "%1/%2"_qt.arg(need_copy_path).arg(last_key);

    copy_binary_file_to_folder_with_rename(qfi.absoluteFilePath(), need_copy_path, copy_path);
    QFile::remove(qfi.absoluteFilePath());
    break;
   }
  }

  QPair<u1, u1> next_counts;

  // //  flag for done
  if(counts.first == 0)
  {
   // //  just have to copy

   go_on->setText("Done");
   go_on->setEnabled(false);
  }
  else
  {
   if(counts.second == 0)
   {
    qd.mkdir(QString::number(counts.first));
    need_copy_path = qd.absoluteFilePath(QString::number(counts.first));
   }

   if(files.contains(counts.first))
   {
    if(files[counts.first].size() > counts.second + 1)
      next_counts = {counts.first, counts.second + 1};
    else if(files.contains(counts.first + 1))
      next_counts = {counts.first + 1, 0};
    else
      next_counts = {0, 0};
   }
   else
   {
    qDebug() << "Unexpected control path reached ... line " << __LINE__;
    next_counts = {0, 0};
   }
  }

  QPair<QString, QString> file_pr = files[counts.first][counts.second];
  clipboard->setText(file_pr.first);
  mbox->setWindowTitle("Copied: "_qt + file_pr.first);
  last_key = file_pr.second;

  qDebug() << "last key: " << last_key;

  counts = next_counts;

 });

 mbox->show();
}


#ifdef HIDE
#include "dhax-video-player-frame.h"
#include "dhax-video-navigation-frame.h"

#include "dhax-video-annotation-set.h"
#include "dhax-video-annotation.h"

#include <QGraphicsVideoItem>

#include <QMenu>
#include <QStyle>
#include <QDir>

#include <QScrollBar>

#include "styles.h"

#include "aforms/rotateable-arrow-annotation.h"

#define INIT_SHOW_HIDE(ty) \
DHAX_Video_Player_Frame::_show_hide* ty##_show_hide \
  = DHAX_Video_Player_Frame::init_show_hide<ty>();


void show_hide_hide(DHAX_Video_Annotation* dva)
{
 DHAX_Video_Player_Frame::_show_hide* sh =
   dva->scene_type_data_as<DHAX_Video_Player_Frame::_show_hide>();
 sh->hide(dva->scene_data());
}

void show_hide_show(DHAX_Video_Annotation* dva)
{
 DHAX_Video_Player_Frame::_show_hide* sh =
   dva->scene_type_data_as<DHAX_Video_Player_Frame::_show_hide>();
 sh->show(dva->scene_data());
}


INIT_SHOW_HIDE(QGraphicsTextItem)
INIT_SHOW_HIDE(QGraphicsEllipseItem)


DHAX_Video_Player_Frame::DHAX_Video_Player_Frame(QWidget* parent)
  :  QFrame(parent), annotation_set_(nullptr),
     full_size_rect_item_(nullptr),
     smaller_size_rect_item_(nullptr),
     replay_count_(0), current_frame_count_(0), graphics_view_(nullptr)
{
// setLayout(new QVBoxLayout);
// layout()->setContentsMargins(0, 0, 0, 0);

//? video_widget_ = new QVideoWidget(this);

 //        btn = new QPushButton(this);
 //        btn->setText("tux.jpeg");
 //        btn->resize(QSize(128, 128));
 //        btn->setIconSize(QSize(128, 128));


 navigation_ = new DHAX_Video_Navigation_Frame;
 navigation_->setFrameStyle(QFrame::Panel | QFrame::Sunken);

 main_layout_ = new QVBoxLayout;

 main_layout_->setContentsMargins(0, 0, 0, 0);
 main_layout_->setMargin(0);

 graphics_view_ = new QGraphicsView(this);
 graphics_scene_ = new QGraphicsScene(this);
 graphics_view_->setScene(graphics_scene_);
 video_item_ = new QGraphicsVideoItem;
 graphics_scene_->addItem(video_item_);

 video_item_->setFlags(QGraphicsItem::ItemIsMovable);

//? graphics_view_->setAlignment(Qt::AlignHCenter | Qt::AlignBaseline);

 frame_number_text_ = nullptr;


 graphics_view_->setContextMenuPolicy(Qt::CustomContextMenu);

 connect(graphics_view_, &QGraphicsView::customContextMenuRequested, [this](const QPoint& pos)
 {
  QMenu* menu = new QMenu(this);
  menu->addAction("Load annotations", this, &DHAX_Video_Player_Frame::load_annotations);
  menu->popup(mapToGlobal(pos));
 });


 connect(video_item_,
   &QGraphicsVideoItem::nativeSizeChanged, [this]()
 {
//?  QSize sz = media_player_->media().canonicalResource().resolution();
//?  QSize sz = media_player_->metaData("Resolution").value<QSize>();
  QSizeF szf = video_item_->nativeSize();

  if(szf == QSize(0,0))
  {
   ++replay_count_;
   current_frame_count_ = 0;
  }
  else if(replay_count_ > 0)
  {
   graphics_view_->centerOn(video_item_);
  }


 });

// main_layout_->addWidget(video_widget_);
 main_layout_->addWidget(graphics_view_);
 main_layout_->addWidget(navigation_);

//  video_frame_grabber_ = new VideoFrameGrabber(this);

 media_player_ = new QMediaPlayer(this);
 media_player_->setVideoOutput(video_item_);
// media_player_->setVideoOutput(video_widget_);
//  media_player_->setVideoOutput(video_frame_grabber_);

// connect(media_player_, &QMediaPlayer::metaDataChanged,
//   []()
// {

// });

 connect(media_player_, &QMediaPlayer::stateChanged, [this](QMediaPlayer::State state)
 {
  if(state == QMediaPlayer::StoppedState)
  {
   qDebug() << "stopped";
//   media_player_->setPosition(0);
//   media_player_->play();
   //video_probe_->
  }
 });

 video_probe_ = new QVideoProbe;

 if(video_probe_->setSource(media_player_))
 {
  qDebug() << "probe ok";
 }
 else
 {
  qDebug() << "probe bad";
 }

 connect_video_probe();


 connect(navigation_, &DHAX_Video_Navigation_Frame::grab_frame_requested, [this]()
 {
  pause();

  qDebug() << "pos: " << media_player_->position();
  QImage frame_image = current_video_frame_.image();
  QLabel* l = new QLabel;
  l->setPixmap(QPixmap::fromImage(frame_image));

  l->setContextMenuPolicy(Qt::CustomContextMenu);

  connect(l, &QLabel::customContextMenuRequested, [this, l](QPoint pos)
  {
   QMenu* m = new QMenu;
   m->addAction("Send video frame to main window", [this, l]()
   {
    handle_send_video_frame_to_main_window(l);
   });
   m->popup(pos + l->pos() + QPoint(0,
     QApplication::style()->pixelMetric(QStyle::PM_TitleBarHeight)));
  });

  l->show();
 });

// connect(navigation_, &DHAX_Video_Navigation_Frame::pause_requested, [this]()
// {
//  pause();
//  //      qDebug()<<"p clicked";
// });

 connect(navigation_, &DHAX_Video_Navigation_Frame::pause_requested, this,
   &DHAX_Video_Player_Frame::pause);

 connect(navigation_, &DHAX_Video_Navigation_Frame::resume_requested, this,
   &DHAX_Video_Player_Frame::resume);

 connect(navigation_, &DHAX_Video_Navigation_Frame::restart_requested, [this]()
 {
//      qDebug()<<"r clicked";
  media_player_->setPosition(0);
  current_frame_count_ = 0;
  update_frame_number_text();
  media_player_->play();
 });

 connect(navigation_, &DHAX_Video_Navigation_Frame::full_size_requested, [this]()
 {
  reset_to_full_size();
//      qDebug()<<"r clicked";
 });

 connect(navigation_, &DHAX_Video_Navigation_Frame::smaller_size_requested, [this]()
 {
  reset_to_smaller_size();
 });

 setLayout(main_layout_);

//  QMediaPlaylist *playList = new QMediaPlaylist(this);
//  playList->addMedia(QUrl::fromLocalFile("/home/nlevisrael/gits/ctg-temp/stella/videos/test.webm"));
//  playList->setPlaybackMode(QMediaPlaylist::Loop);
//  media_player_->setPlaylist(playList);


//  current_path_ = "/home/nlevisrael/gits/ctg-temp/stella/videos/test.mp4";


}

template<typename T>
T* DHAX_Video_Player_Frame::make_or_show_scene_annotation(DHAX_Video_Annotation* dva)
{
 T* result;
 if(dva->scene_data_as(result))
 {
  show_hide_show(dva);
 }
 else
 {
  qDebug() << "inserting annotation for frame " << current_frame_count_;
  qDebug() << *dva;
  result = (T*) make_scene_annotation(dva);
 }
 return result;
}



void DHAX_Video_Player_Frame::handle_video_frame(const QVideoFrame& qvf)
{
 if(need_video_size_)
 {
  --need_video_size_;
  if(media_player_->isMetaDataAvailable())
  {
   video_size_ = media_player_->metaData("Resolution").value<QSize>();
   if(video_size_.isValid())
   {
    need_video_size_ = 0;
    confirm_video_size();
   }
  }
 }

 qint64 st = qvf.startTime();
 qint64 seconds = st/1000;
 qint64 fn = st/40000;


 if(annotation_set_)
 {
  QPair<void*, void*> pr = annotation_set_->get_data_by_end_frame(current_frame_count_);
  if(pr.second)
  {
   ((_show_hide*)pr.first)->hide(pr.second);
  }

  DHAX_Video_Annotation* dva = annotation_set_->get_annotation_by_start_frame(current_frame_count_);
  if(dva)
  {
   QGraphicsItem* qgi;
   if(dva->kind() == "text")
   {
    qgi = make_or_show_scene_annotation<QGraphicsTextItem>(dva);
   }
   else //if(dva->kind() == "arrow")
   {
    qgi = make_or_show_scene_annotation<QGraphicsItem>(dva);
   }
  }
 }

 ++current_frame_count_;

 if((current_frame_count_ & 20) == 0)
 {
  if(frame_number_text_)
    update_frame_number_text();
 }


//  qDebug() << fn;
 current_video_frame_ = qvf;

//    QSize sz = media_player_->media().canonicalResource().resolution();
//    qDebug() << "size = " << sz;
//    QSize sz1 = media_player_->metaData("Resolution").value<QSize>();
//    qDebug() << "size1 = " << sz1;

//   QImage frame_image = qvf.image();

//   QLabel* l = new QLabel;
//   l->setPixmap(QPixmap::fromImage(frame_image));
//   l->show();

}


void* DHAX_Video_Player_Frame::make_scene_text_annotation(DHAX_Video_Annotation* dva)
{
 QGraphicsTextItem* result = graphics_scene_->addText(dva->text());
 result->setParentItem(annotations_rect_item_);
 result->setPos(dva->corner_position());
 result->setHtml(dva->html_text());
 dva->set_scene_data(result);
 dva->set_scene_type_data(QGraphicsTextItem_show_hide);
 annotation_set_->set_end_frame_data(dva->ending_frame_number(),
   //QGraphicsTextItem_show_hide,
   *dva);
 return result;
}

void* DHAX_Video_Player_Frame::make_scene_circled_text_annotation(DHAX_Video_Annotation* dva)
{
 QGraphicsSimpleTextItem* ti = graphics_scene_->addSimpleText(dva->text());
 ti->setPos(dva->corner_position());
 ti->setText(dva->text());

 QRectF qrf(0, 0, annotation_set_->circled_text_default_width(),
   annotation_set_->circled_text_default_width());

 qrf.moveCenter(dva->corner_position());

 QBrush qbr(annotation_set_->circled_text_default_background_color());
 QPen qpen(QBrush(annotation_set_->circled_text_default_outline_color()),
   annotation_set_->circled_text_default_width());

 QGraphicsEllipseItem* result = graphics_scene_->addEllipse(qrf, qpen, qbr);

 ti->setParentItem(result);
 result->setParentItem(annotations_rect_item_);

 dva->set_scene_data(result);
 dva->set_scene_type_data(QGraphicsEllipseItem_show_hide);

 annotation_set_->set_end_frame_data(dva->ending_frame_number(),
   //?QGraphicsEllipseItem_show_hide,
   *dva);

 return result;
}

void* DHAX_Video_Player_Frame::make_scene_arrow_annotation(DHAX_Video_Annotation* dva)
{
 QByteArray qba = QByteArray::fromBase64(dva->data64().trimmed().toLatin1());
 QString kv_text = dva->kv_text();

 Rotateable_Arrow_Annotation raa = kv_text.isEmpty()?
   Rotateable_Arrow_Annotation(qba) : Rotateable_Arrow_Annotation(kv_text);

 const QPolygonF& qpf = raa.rendered_polygon();

 QBrush qbr(raa.fill_color());

 qDebug() << raa.fill_color();
 qDebug() << raa.get_xscale();

 QGraphicsPolygonItem* result = graphics_scene_->addPolygon(qpf, Qt::NoPen, qbr);
// result->setScale(raa.get_scale());
 return result;
}

void* DHAX_Video_Player_Frame::make_scene_annotation(DHAX_Video_Annotation* dva)
{
 if(dva->kind() == "text")
   return make_scene_text_annotation(dva);
 else if(dva->kind() == "circled")
   return make_scene_circled_text_annotation(dva);
 else if(dva->kind() == "Rotateable_Arrow_Annotation")
  return make_scene_arrow_annotation(dva);

 return nullptr;
}

void DHAX_Video_Player_Frame::connect_video_probe()
{
 connect(video_probe_, &QVideoProbe::videoFrameProbed, this,
   &DHAX_Video_Player_Frame::handle_video_frame);
}


void DHAX_Video_Player_Frame::init_annotations()
{
 annotation_set_ = new DHAX_Video_Annotation_Set;
//? annotation_set_->load_sample_annotations();
 qDebug() << "annotation_st" << *annotation_set_;

 annotations_rect_item_ = graphics_scene_->addRect(0,0,0,0,Qt::NoPen, Qt::NoBrush);
 annotations_rect_item_->setZValue(1);

// annotations_rect_item_->setPen(Qt::NoPen);
// annotations_rect_item_->setBrush(Qt::NoBrush);

// annotations_rect_item_->setScale(1.3);
}


void DHAX_Video_Player_Frame::reset_annotation()
{
// //  this would by Qt 6 ...
// for (auto [key, value]: annotation_set_->asKeyValueRange())
// {
//     // ...
// }

 for(DHAX_Video_Annotation& dva : annotation_set_->values())
 {
  show_hide_show(&dva);
 }
}

void DHAX_Video_Player_Frame::load_annotations()
{
 pause();
// init_annotations();
// qDebug( ) << "init_aaa";
 //resume();

 QString annotation_file = QFileDialog::getOpenFileName(this,
   "Select annotation file (.ntxh format)", ROOT_FOLDER "/..",
   "*.ntxh");

//  QString annotation_file = "/home/nlevisrael/gits/ctg-temp/video-annotations/t1.ntxh";

 if(!annotation_file.isEmpty())
 {
  annotation_set_->load_annotation_file(annotation_file);
 }
}

void DHAX_Video_Player_Frame::update_frame_number_text()
{
 QString text = QString::number(current_frame_count_);
//      "%1\n%2"_qt.arg(current_frame_count_).arg(seconds);
 frame_number_text_->setPlainText(text);
}


void DHAX_Video_Player_Frame::pause()
{
 media_player_->pause();
 navigation_->set_play_button_to_resume();
}


void DHAX_Video_Player_Frame::resume()
{
 media_player_->play();
 navigation_->set_play_button_to_play();
}

void DHAX_Video_Player_Frame::handle_send_video_frame_to_main_window(QLabel* l)
{
 QString cnf = class_name_folder(DEFAULT_DHAX_TEMP_FOLDER "/_proc");

 QDir qd(cnf);
 if(!qd.exists())
   qd.mkpath(".");

 cnf += "/temp.png";
 l->pixmap()->save(cnf);

 qDebug() << "saving pixmap: " << cnf;

 Q_EMIT show_video_frame_requested(cnf);
}


void DHAX_Video_Player_Frame::halt()
{
 media_player_->stop();
}


void DHAX_Video_Player_Frame::play_local_video(QString file_path)
{
 init_annotations();

 //current_path_ = file_path;
// current_path_ = "/home/nlevisrael/gits/ctg-temp/stella/videos/test.mkv";
//
 current_path_ = "/home/nlevisrael/gits/ctg-temp/video-annotations/back/bus.mkv";

 current_url_ =  QUrl::fromLocalFile(current_path_);

 QMediaPlaylist* play_list = new QMediaPlaylist();
 media_player_->setPlaylist(play_list);
 play_list->addMedia(QMediaContent(current_url_));
 play_list->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);

// media_player_->setMedia(current_url_);

 // //  give it a bit of time
 need_video_size_ = 10; //

// ?check_adjust_size();

 media_player_->play();



 qDebug() << " SR1: " << graphics_scene_->sceneRect();
 qDebug() << " IBR1: " << graphics_scene_->itemsBoundingRect();

 QSizeF sz = video_item_->size(); //.grownBy(QMargins(5,5,5,5));
 qDebug() << " SZ1: " << sz;


// navigation_->show();
}

QSize DHAX_Video_Player_Frame::get_navigation_size()
{
 return navigation_->size();
}

QRectF DHAX_Video_Player_Frame::graphics_view_visible_rect()
{
    QPointF tl(graphics_view_->horizontalScrollBar()->value(),
      graphics_view_->verticalScrollBar()->value());
    QPointF br = tl + graphics_view_->viewport()->rect().bottomRight();
    QMatrix mat = graphics_view_->matrix().inverted();
    return mat.mapRect(QRectF(tl,br));
}

QRect DHAX_Video_Player_Frame::get_web_view_geometry()
{
 if(!graphics_view_)
   return {};

 r8 vleft = web_view_geometry_.left();
 r8 vtop = web_view_geometry_.top();

 QPointF A = graphics_view_->mapToScene( QPoint(0, 0) );
 QPointF B = graphics_view_->mapToScene( QPoint(
         graphics_view_->viewport()->width(),
         graphics_view_->viewport()->height() ));

 QRectF ab( A, B );

 QRect rr = graphics_view_->viewport()->rect();
 QPoint tl = QPoint(vleft - ab.left(), vtop - ab.top());
 QPoint tl_global =  graphics_view_->mapToGlobal(tl);

 QPoint rr_global =  graphics_view_->mapToGlobal(rr.topLeft());

 QRect tl_rect (tl_global, QSize(web_view_geometry_.width(),
                                 web_view_geometry_.height()));
 QRect rr_rect (rr_global, QSize(rr.width(), rr.height()));

 QRect intersection = tl_rect.intersected(rr_rect);

 return intersection;
}



#ifdef HIDE
void DHAX_Video_Player_Frame::confirm_video_size()
{
 QColor c (200, 100, 10, 100);

// {
//  QBrush qbr(c);
//  QGraphicsEllipseItem* el1 = graphics_scene_->addEllipse(0, 0, 20, 20, QPen(), qbr);
//  el1->setParentItem(annotations_rect_item_);
//  QGraphicsEllipseItem* el2 = graphics_scene_->addEllipse(40, 40, 20, 20, QPen(), qbr);
//  el2->setParentItem(annotations_rect_item_);
//  QGraphicsEllipseItem* el3 = graphics_scene_->addEllipse(80, 80, 20, 20, QPen(), qbr);
//  el3->setParentItem(annotations_rect_item_);
//  QGraphicsEllipseItem* el4 = graphics_scene_->addEllipse(120, 120, 20, 20, QPen(), qbr);
//  el4->setParentItem(annotations_rect_item_);

//  QGraphicsEllipseItem* el5 = graphics_scene_->addEllipse(120, 220, 20, 20, QPen(), qbr);
//  el5->setParentItem(annotations_rect_item_);


// }


 qDebug() << " SR2: " << graphics_scene_->sceneRect();
 qDebug() << " IBR2: " << graphics_scene_->itemsBoundingRect();

 QSizeF sz = video_item_->size(); //.grownBy(QMargins(5,5,5,5));
 qDebug() << " SZ2: " << sz;


 double ratio, new_width, new_height, left, top; // h_center, v_center;

 if(video_size_.width() > video_size_.height())
 {
   ratio = video_size_.height() > video_size_.width();

 }
 else
 {
   ratio  = (double) video_size_.width() / video_size_.height();
   new_height = sz.height();
   new_width = sz.height() * ratio;
   left = (sz.width() / 2) - (new_width / 2);
   top = video_item_->pos().y();
//   h_center = sz.width() / 2;
 }

 annotation_set_->set_smaller_video_size(QSizeF(new_width, new_height));
// annotation_set_->set_smaller_video_size(QSizeF(new_width, sz.height()));
 annotation_set_->set_larger_video_size(video_size_);
 annotation_set_->check_ratios();


 //QRectF
 video_rect_ = QRectF(left, top, new_width, new_height);
 //video_top_left_ = video_rect.topLeft();

 web_view_geometry_ = video_rect_.toRect();

 annotations_rect_item_->setRect(video_rect_.adjusted(2,2,-2,-2));

// smaller_size_rect_item_ = graphics_scene_->addRect(left,
//   video_item_->pos().y(),new_width,sz.height(),QPen(QBrush(c), 4));

 smaller_size_rect_item_ = graphics_scene_->addRect(video_rect_, QPen(QBrush(c), 4),
   Qt::NoBrush);


 smaller_size_rect_item_->setParentItem(video_item_);

 QRectF framed_scene_rect = graphics_scene_->sceneRect();

 QColor text_bkg_color (110, 80, 20, 40);
 QColor text_color (10, 80, 20, 255);

// u1 frame_number_text_background_extra_height = 10;

// frame_number_text_background_ = graphics_scene_->addRect(
//   QRect(smaller_size_rect_item_->rect().bottomRight().toPoint() - QPoint(120, 2),
//   smaller_size_rect_item_->rect().bottomRight().toPoint() + QPoint(-100, frame_number_text_background_extra_height)));

// frame_number_text_background_ = graphics_scene_->addRect(
//   QRect(smaller_size_rect_item_->rect().center().toPoint() - QPoint(20, 2),
//   smaller_size_rect_item_->rect().center().toPoint()));

  frame_number_text_background_ = graphics_scene_->addRect(
    QRect(smaller_size_rect_item_->rect().topLeft().toPoint() + QPoint(-20, 5),
    smaller_size_rect_item_->rect().topLeft().toPoint() + QPoint(3, 20)));

 frame_number_text_background_->setParentItem(smaller_size_rect_item_);

 frame_number_text_background_->setBrush(QBrush(text_bkg_color));
 frame_number_text_background_->setPen(Qt::NoPen);

 frame_number_text_ = graphics_scene_->addText("0000");
 frame_number_text_->setParentItem(frame_number_text_background_);
 frame_number_text_->setPos(frame_number_text_background_->rect().topLeft());

 frame_number_text_->setDefaultTextColor(text_color);
 QFont font = frame_number_text_->font();
 font.setPointSize(5);
 frame_number_text_->setFont(font);

 reset_graphics_scene_rect();

 graphics_scene_->setSceneRect(framed_scene_rect);
 initial_smaller_scene_rect_ = framed_scene_rect;

 reposition_smaller_annotations_rect_item();

 qDebug() << " SR4: " << graphics_scene_->sceneRect();
 qDebug() << " IBR4: " << graphics_scene_->itemsBoundingRect();

// double left_half = h_center - graphics_scene_->sceneRect().left();
// double right_half = h_center - graphics_scene_->sceneRect().right();

// qDebug() << " left half: " << left_half;
// qDebug() << " right half: " << right_half;

 Q_EMIT video_size_established(QSize(new_width, new_height ));


}
#endif






void DHAX_Video_Player_Frame::confirm_video_size()
{
 QColor c (200, 100, 10, 100);

// {
//  QBrush qbr(c);
//  QGraphicsEllipseItem* el1 = graphics_scene_->addEllipse(0, 0, 20, 20, QPen(), qbr);
//  el1->setParentItem(annotations_rect_item_);
//  QGraphicsEllipseItem* el2 = graphics_scene_->addEllipse(40, 40, 20, 20, QPen(), qbr);
//  el2->setParentItem(annotations_rect_item_);
//  QGraphicsEllipseItem* el3 = graphics_scene_->addEllipse(80, 80, 20, 20, QPen(), qbr);
//  el3->setParentItem(annotations_rect_item_);
//  QGraphicsEllipseItem* el4 = graphics_scene_->addEllipse(120, 120, 20, 20, QPen(), qbr);
//  el4->setParentItem(annotations_rect_item_);

//  QGraphicsEllipseItem* el5 = graphics_scene_->addEllipse(120, 220, 20, 20, QPen(), qbr);
//  el5->setParentItem(annotations_rect_item_);


// }


 qDebug() << " SR2: " << graphics_scene_->sceneRect();
 qDebug() << " IBR2: " << graphics_scene_->itemsBoundingRect();

 QSizeF sz = video_item_->size(); //.grownBy(QMargins(5,5,5,5));
 qDebug() << " SZ2: " << sz;


 double ratio;

 if(video_size_.width() > video_size_.height())
 {
   ratio = video_size_.height() > video_size_.width();


 }
 else
   ratio  = (double) video_size_.width() / video_size_.height();

 double new_width = sz.height() * ratio;

 double left = (sz.width() / 2) - (new_width / 2);

 double h_center = sz.width() / 2;

 annotation_set_->set_smaller_video_size(QSizeF(new_width, sz.height()));
 annotation_set_->set_larger_video_size(video_size_);
 annotation_set_->check_ratios();


 //QRectF
 video_rect_ = QRectF(left, video_item_->pos().y(), new_width, sz.height());
 //video_top_left_ = video_rect.topLeft();

 web_view_geometry_ = video_rect_.toRect();

 annotations_rect_item_->setRect(video_rect_.adjusted(2,2,-2,-2));

// smaller_size_rect_item_ = graphics_scene_->addRect(left,
//   video_item_->pos().y(),new_width,sz.height(),QPen(QBrush(c), 4));

 smaller_size_rect_item_ = graphics_scene_->addRect(video_rect_, QPen(QBrush(c), 4),
   Qt::NoBrush);


 smaller_size_rect_item_->setParentItem(video_item_);

 QRectF framed_scene_rect = graphics_scene_->sceneRect();

 QColor text_bkg_color (110, 80, 20, 40);
 QColor text_color (10, 80, 20, 255);

// u1 frame_number_text_background_extra_height = 10;

// frame_number_text_background_ = graphics_scene_->addRect(
//   QRect(smaller_size_rect_item_->rect().bottomRight().toPoint() - QPoint(120, 2),
//   smaller_size_rect_item_->rect().bottomRight().toPoint() + QPoint(-100, frame_number_text_background_extra_height)));

// frame_number_text_background_ = graphics_scene_->addRect(
//   QRect(smaller_size_rect_item_->rect().center().toPoint() - QPoint(20, 2),
//   smaller_size_rect_item_->rect().center().toPoint()));

  frame_number_text_background_ = graphics_scene_->addRect(
    QRect(smaller_size_rect_item_->rect().topLeft().toPoint() + QPoint(-20, 5),
    smaller_size_rect_item_->rect().topLeft().toPoint() + QPoint(3, 20)));

 frame_number_text_background_->setParentItem(smaller_size_rect_item_);

 frame_number_text_background_->setBrush(QBrush(text_bkg_color));
 frame_number_text_background_->setPen(Qt::NoPen);

 frame_number_text_ = graphics_scene_->addText("0000");
 frame_number_text_->setParentItem(frame_number_text_background_);
 frame_number_text_->setPos(frame_number_text_background_->rect().topLeft());

 frame_number_text_->setDefaultTextColor(text_color);
 QFont font = frame_number_text_->font();
 font.setPointSize(5);
 frame_number_text_->setFont(font);

 reset_graphics_scene_rect();

 graphics_scene_->setSceneRect(framed_scene_rect);
 initial_smaller_scene_rect_ = framed_scene_rect;

 reposition_smaller_annotations_rect_item();

 qDebug() << " SR4: " << graphics_scene_->sceneRect();
 qDebug() << " IBR4: " << graphics_scene_->itemsBoundingRect();

 double left_half = h_center - graphics_scene_->sceneRect().left();
 double right_half = h_center - graphics_scene_->sceneRect().right();

 qDebug() << " left half: " << left_half;
 qDebug() << " right half: " << right_half;

 Q_EMIT video_size_established(QSize(new_width, sz.height() ));


}

void DHAX_Video_Player_Frame::reset_graphics_scene_rect()
{
 QRectF rect = graphics_scene_->itemsBoundingRect();
 graphics_scene_->setSceneRect(rect);
}

void DHAX_Video_Player_Frame::reset_to_smaller_size()
{
 annotations_rect_item_->setScale(1);
 reposition_smaller_annotations_rect_item();

 if(full_size_rect_item_)
   graphics_scene_->removeItem(full_size_rect_item_);
 if(smaller_size_rect_item_)
 {
  graphics_scene_->addItem(smaller_size_rect_item_);
  smaller_size_rect_item_->setParentItem(video_item_);
 }

// frame_number_text_background_->show();
// frame_number_text_->show();


 video_item_->setSize(last_smaller_size_);
// web_view_geometry_ = last_smaller_size_;

 web_view_geometry_ = video_rect_.toRect();

 reset_graphics_scene_rect();

 graphics_scene_->setSceneRect(initial_smaller_scene_rect_);

 Q_EMIT smaller_video_size_requested(last_smaller_size_.toSize());
}

void DHAX_Video_Player_Frame::reset_to_full_size()
{
 qDebug() << " ==== " << annotation_set_->sizes_ratio_x()
           << " --- " << annotation_set_->sizes_ratio_y() ;


// annotations_rect_item_->setTransform(annotation_set_->sizes_ratio_y());

// annotations_rect_item_->setScale(annotation_set_->sizes_ratio_y());
 reposition_larger_annotations_rect_item();


// QColor c1 (250, 100, 210, 200);
// {
//  QBrush qbr(c1);
//  QGraphicsEllipseItem* el1 = graphics_scene_->addEllipse(20, 20, 20, 20, QPen(), qbr);
//  el1->setParentItem(annotations_rect_item_);
//  QGraphicsEllipseItem* el2 = graphics_scene_->addEllipse(60, 60, 20, 20, QPen(), qbr);
//  el2->setParentItem(annotations_rect_item_);
//  QGraphicsEllipseItem* el3 = graphics_scene_->addEllipse(100, 100, 20, 20, QPen(), qbr);
//  el3->setParentItem(annotations_rect_item_);
//  QGraphicsEllipseItem* el4 = graphics_scene_->addEllipse(140, 140, 20, 20, QPen(), qbr);
//  el4->setParentItem(annotations_rect_item_);

//  QGraphicsEllipseItem* el5 = graphics_scene_->addEllipse(140, 220, 20, 20, QPen(), qbr);
//  el5->setParentItem(annotations_rect_item_);

//  QGraphicsEllipseItem* el6 = graphics_scene_->addEllipse(160, 1270, 20, 20, QPen(), QBrush(Qt::red));

// }


// annotations_rect_item_->setScale(annotation_set_->sizes_ratio_x());
// qDebug() << " ===== MATRIX =====\n" << annotations_rect_item_->transform();

// qDebug() << "new size: " << video_size_;
// QSize sza = video_size_.grownBy(QMargins(5,5,5,5));
// setMaximumWidth(sza.width());
// setMaximumHeight(sza.height());
// graphics_view_->resize(video_size_);
// graphics_view_->update();

// video_item_->setSize(video_size_);

 QColor c (200, 100, 10, 100);

 if(smaller_size_rect_item_)
   graphics_scene_->removeItem(smaller_size_rect_item_);

 if(full_size_rect_item_)
   graphics_scene_->addItem(full_size_rect_item_);
 else
 {
  QSizeF szs = video_size_.grownBy(QMargins(3,3,3,3));

  full_size_rect_item_ = graphics_scene_->addRect(0, 0, szs.width(), szs.height(),
   QPen(QBrush(c), 10), Qt::NoBrush);
 }

 web_view_geometry_ = QRect(0, 0, video_size_.width(), video_size_.height());

 if(true) //last_larger_video_size_.isEmpty())
 {
//  frame_number_text_background_->hide();
//  frame_number_text_->hide();

  last_smaller_size_ = video_item_->size();

  video_item_->setSize(video_size_);

  QSizeF sza = video_size_.grownBy(QMargins(5,5,5,5));

  last_larger_video_size_ = video_size_;
  last_larger_graphics_view_size_ = sza;

  graphics_view_->resize(sza.toSize());
  QRectF rect = graphics_scene_->itemsBoundingRect();
  graphics_scene_->setSceneRect(rect);

  Q_EMIT full_video_size_requested(sza.toSize());
 }

}

void DHAX_Video_Player_Frame::reposition_smaller_annotations_rect_item()
{
 QTransform tr; tr.scale(1, 1);
 annotations_rect_item_->setTransform(tr);

 annotations_rect_item_->setPos(video_rect_.topLeft() +
   QPoint(annotation_set_->smaller_size_x_translation(),
          annotation_set_->smaller_size_y_translation()));
}

void DHAX_Video_Player_Frame::reposition_larger_annotations_rect_item()
{
 QTransform tr; tr.scale(annotation_set_->sizes_ratio_x() *
   annotation_set_->sizes_ratio_x_adjustment(),
   annotation_set_->sizes_ratio_y() *
   annotation_set_->sizes_ratio_y_adjustment());

 annotations_rect_item_->setTransform(tr);

 annotations_rect_item_->setPos(
   annotation_set_->larger_size_x_translation(), annotation_set_->larger_size_y_translation());
}


void DHAX_Video_Player_Frame::recenter()
{
 graphics_view_->centerOn(video_item_);
}

void DHAX_Video_Player_Frame::resizeEvent(QResizeEvent* event)
{
 graphics_view_->centerOn(video_item_);

//? setMaximumWidth(video_widget_->width() + 12);
//? navigation_->move(p.x(), p.y() - 20);
//? navigation_->move(rect().bottomRight() - navigation_->rect().bottomRight());// + QPoint(-40,-40));
// navigation_->move(video_widget_->rect().bottomRight() - navigation_->rect().bottomRight() + QPoint(0,10));
 QWidget::resizeEvent(event);
}
#endif
