

#include "action.h"
#include "application.h"

#include "config.h"



#include "context.h"
#include "response.h"

//#include "view_p.h"

#include <QDirIterator>
#include <QString>
#include <QTranslator>
#include <QtCore/QLoggingCategory>

#include "chasm-view.h"
#include "chasm-view_p.h"

#include "tsi-global-types.h"

#include "tsi/response/raw-file/tsi-raw-file-server-response.h"
#include "tsi/response/tsi-server-response.h"

#include "chasm-textio.h"

// Q_LOGGING_CATEGORY(CUTELYST_GRANTLEE, "cutelyst.grantlee", QtWarningMsg)

USING_CHASM_NAMESPACE

//using namespace Cutelyst;


Chasm_View::Chasm_View(QObject *parent, const QString &name)
    : View(new Chasm_ViewPrivate, parent, name)
{
 Q_D(Chasm_View);


 auto app = qobject_cast<Cutelyst::Application*>(parent);
 if (app)
 {
  set_include_paths({app->config(QStringLiteral("root")).toString()});
 }
 else
 {
        // make sure templates can be found on the current directory
  set_include_paths({QDir::currentPath()});
 }
}

QStringList Chasm_View::include_paths() const
{
 Q_D(const Chasm_View);
   return d->include_paths_;
}

void Chasm_View::set_include_paths(const QStringList &paths)
{
 Q_D(Chasm_View);
 d->include_paths_ = paths;
 Q_EMIT changed();
}

QString Chasm_View::default_file_extension() const
{
 Q_D(const Chasm_View);
 return d->extension;
}


QByteArray Chasm_View::render(Cutelyst::Context* c) const
{
 Q_D(const Chasm_View);

 QByteArray result;

 QString response_file;


 TSI_Server_Response& tsr = c->get_tsi_server_response();

 if(TSI_Raw_File_Server_Response* trsr = tsr.raw_file_response())
 {
  trsr->proceed(c, response_file);
 }
 else
 {
  const QVariantHash stash = c->stash();
  auto it = stash.constFind("response-file"_qt);
  if(it != stash.constEnd())
  {
   response_file = it.value().toString();
  }
 }
 if(response_file.isEmpty())
 {
  result = "Controller failed to provide a response file"; //_qt.arg(response_file).toLatin1();
 }
 else
 {
  QStringList paths = include_paths();
  QString absolute_file;
  for(QString path : paths)
  {
   QFileInfo qfi(path + "/"_qt + response_file);
   if(qfi.exists())
   {
    absolute_file = qfi.absoluteFilePath();
    break;
   }
  }
  if(absolute_file.isEmpty())
    result = "File %1 not found"_qt.arg(response_file).toLatin1();
  else
  {
   qDebug() << "Loading file: " << absolute_file;
   load_file(absolute_file, result);
  }

 }

 return result;



 //?c->response()->body() = "<b>render</b>";

 //return "<b>render ! </b>";
}


#include "moc_chasm-view.cpp"

