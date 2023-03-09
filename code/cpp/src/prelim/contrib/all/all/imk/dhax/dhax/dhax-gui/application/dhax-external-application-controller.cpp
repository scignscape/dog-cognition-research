
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "dhax-external-application-controller.h"

#include "main-window/dhax-main-window.h"

#include "rpdf/webgl-view-dialog.h"

#include "dhax-application-controller.h"

#include "dhax-forge-controller.h"

#include "textio.h"

#include "styles.h"

USING_KANS(TextIO)

#include <QMenuBar>

#include <QGuiApplication>
#include <QTimer>
#include <QDebug>
#include <QFile>
#include <QScreen>

#include <QFileDialog>

#include <QProcess>

#include <QProgressDialog>

#include "dhax-video/dhax-video-player-dialog.h"


DHAX_External_Application_Controller::DHAX_External_Application_Controller()
  :  application_main_window_(nullptr),
     application_controller_(nullptr),
     current_wgl_dialog_(nullptr) //, current_video_player_dialog_(nullptr)
{
 save_area_folder_ = ROOT_FOLDER "/../save-area";
}




void DHAX_External_Application_Controller::view_3d()
{
 QString path = qApp->applicationDirPath();
 QDir qd(path);

 QString ap = qd.absoluteFilePath("meshlab-console");

 QProcess cmd;
 cmd.startDetached(ap, {});

}


void DHAX_External_Application_Controller::prepare_video_recorder()
{
 qDebug() << "prepare_video_recorder";

// QString cmd = "";

 QDir qd(SSR_BIN_FOLDER);

 QString ap = qd.absoluteFilePath("simplescreenrecorder");
 qDebug() << "ap = " << ap;

 QProcess cmd;
 cmd.startDetached(ap, {});

 QTimer::singleShot(2000, [this]()
 {
  test_ssr_datagram();
 });
}

void DHAX_External_Application_Controller::test_ssr_datagram()
{
 qDebug() << "test ssr";

 QRect rect;

 if(current_wgl_dialog_)
 {
  rect = current_wgl_dialog_->get_web_view_geometry();
  if(current_wgl_dialog_->first_video_capture_position().isNull())
  {
   current_wgl_dialog_->first_video_capture_position() = rect;
   QObject::connect(current_wgl_dialog_,
     &WebGL_View_Dialog::web_view_geometry_updated,
     [this](QRect r)
   {
    application_controller_->send_ssr_reset(r);
   });
  }

  qDebug() << "rect = " << rect;
  application_controller_->send_ssr_reset(rect);
 }
 else if(DHAX_Video_Player_Dialog* dlg =
   application_controller_->current_video_player_dialog())
 {
  rect = dlg->current_scene_camera_view_geometry();
  if(dlg->first_video_capture_position().isNull())
  {
   dlg->first_video_capture_position() = rect;
   QObject::connect(dlg,
     &DHAX_Video_Player_Dialog::scene_camera_view_geometry_updated,
     [this, dlg]()
   {
    QRect r = dlg->current_scene_camera_view_geometry();
    if(!r.isEmpty())
    {
     qDebug() << "!r = " << r;
     application_controller_->send_ssr_reset(r);
    }
   });
  }

  qDebug() << "rect = " << rect;
  application_controller_->send_ssr_reset(rect);
 }


 else
   application_controller_->send_ssr_reset("--------------");

}

void DHAX_External_Application_Controller::view_360()
{
 if(current_wgl_dialog_)
 {
  current_wgl_dialog_->setWindowState(current_wgl_dialog_->windowState()
    & ~Qt::WindowMinimized | Qt::WindowActive);
  current_wgl_dialog_->reset_tab_selection();
  return;
 }

 current_wgl_dialog_ = new WebGL_View_Dialog(nullptr);

 current_wgl_dialog_->setWindowTitle("360 Mode");

 application_main_window_->connect(current_wgl_dialog_, &WebGL_View_Dialog::youtube_download_requested,
   [this](QString url)
 {
  QString path = YOU_TUBE_DOWNLOAD_CMD_FOLDER;
  qDebug() << "path = " << path;

  QDir qd(path);

  QString ap = qd.absoluteFilePath(YOU_TUBE_DOWNLOAD_EXE);

  auto gd = []()
  {
   qDebug() << "----gd";
   return "--get-duration";
  };

  auto gdu = [url]()
  {
   qDebug() << "----gdu";
   return url;
  };

  QStringList options;
//  options << "--get-duration";
//  options << url;

  options << gd() << gdu();

  qDebug() << " options = " << options;

  QProcess* cmd = new QProcess;

  application_main_window_->connect(cmd,
    QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
    [this, cmd, ap, url](int exit_code, QProcess::ExitStatus exit_status)
  {
   static QSet<QProcess*> aborted_processes;

   QByteArray qba = cmd->readAllStandardOutput();

   if(aborted_processes.contains(cmd))
     return;

   cmd->close();
   aborted_processes.insert(cmd);

   QByteArrayList qbal = qba.split(':');
   u2 duration = qbal.value(0).toUInt() * 60 + qbal.value(1).toUInt();

   QProcess* cmd1 = new QProcess;

   QString summary = QString("Downloading a video of %1 seconds (bar shows seconds ellapsed)").arg(duration);

   QProgressDialog* qpd = new QProgressDialog(summary, "Cancel",
     0, duration);

   qpd->setStyleSheet(qmessagebox_button_style_sheet());


   QTimer *timer = new QTimer(qpd);

   qpd->connect(qpd, &QProgressDialog::canceled, [cmd1, timer, qpd]
   {
    timer->stop();
    timer->deleteLater();
    aborted_processes.insert(cmd1);
    cmd1->close();
    qpd->deleteLater();
   });

   qpd->connect(timer, &QTimer::timeout, [qpd]
   {
    qpd->setValue(qpd->value() + 1);
   });

   timer->start(1000);
   qpd->show();


   QString outfile =
     QDateTime::currentDateTime().toString("/ddMMyyyy-hhmmss").prepend(YOU_TUBE_DOWNLOAD_FOLDER);

   QStringList options1;
   options1 << "-o" << outfile << "--skip-unavailable-fragments"
       << "--no-continue" << "--no-part" << "--no-call-home";
   options1 << url;

   application_main_window_->connect(cmd1,
     QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
     [outfile, this, qpd, cmd1, timer](int exit_code, QProcess::ExitStatus exit_status)
   {
    if(aborted_processes.contains(cmd1))
      return;
    qpd->close();
    timer->stop();
    qpd->deleteLater();
    timer->deleteLater();

    application_controller_->handle_newly_downloaded_video(outfile);
   });

   cmd1->start(ap, options1);


//     qDebug() << " ============== ";
//     qDebug() << "duration: " << duration;
//     qDebug() << " ============== ";

     //?if(exit_status == QProcess::NormalExit)
     //?  application_controller_->handle_newly_downloaded_video(outfile);
    });

    cmd->start(ap, options);


//  QString outfile =
//    QDateTime::currentDateTime().toString("/ddMMyyyy-hhmmss").prepend(YOU_TUBE_DOWNLOAD_FOLDER);

//  QStringList options;
//  options << "-o" << outfile << "--skip-unavailable-fragments"
//    << "--no-continue" << "--no-part" << "--no-call-home";
//  options << url;

//  qDebug() << "cmd = " << ap;

//  QProcess* cmd = new QProcess;

//  application_main_window_->connect(cmd,
//    QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
//    [outfile, this](int exit_code, QProcess::ExitStatus exit_status)
//  {
//   //?if(exit_status == QProcess::NormalExit)
//     application_controller_->handle_newly_downloaded_video(outfile);
//  });

//  cmd->start(ap, options);

 });

 application_main_window_->connect(current_wgl_dialog_, &WebGL_View_Dialog::snapshot_saved,
   [this](QString file_path)
 {
  qDebug() << "loading " << file_path;
  current_wgl_dialog_->setWindowState(current_wgl_dialog_->windowState()
    | Qt::WindowMinimized);


  QString copy_path = copy_binary_file_to_folder(file_path, save_area_folder_);

  if(copy_path.isEmpty())
    application_controller_->load_image(file_path);
  else
    application_controller_->load_image(copy_path);
 });

 current_wgl_dialog_->show();

}

void DHAX_External_Application_Controller::view_cad()
{
 QDir qd(FREECAD_BIN_FOLDER);

 QString ap = qd.absoluteFilePath("FreeCAD");
 qDebug() << "ap = " << ap;

 QProcess cmd;
 cmd.startDetached(ap, {});
}

#ifdef USE_FORGE
void DHAX_External_Application_Controller::run_forge_workflow()
{
 DHAX_Forge_Controller* dfc = application_controller_->check_init_forge_controller();
 dfc->run_workflow();
}
#endif//def USE_FORGE
