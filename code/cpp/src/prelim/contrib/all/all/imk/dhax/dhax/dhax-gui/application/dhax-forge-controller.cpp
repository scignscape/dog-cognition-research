
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "dhax-forge-controller.h"

#include "textio.h"

USING_KANS(TextIO)

#include <QApplication>

#ifdef USE_Forge
#include "iat-forge/forge-session.h"
#include "iat-forge/forge-runtime.h"
#include "iat-forge/forge-api-workflow.h"
#endif

#include <QFileDialog>

#include <QProcessEnvironment>
#include <QFileDialog>

#define VALUE2(x) value(#x, #x)



DHAX_Forge_Controller::DHAX_Forge_Controller()
  :  forge_session_(nullptr)
{

}


void DHAX_Forge_Controller::init_ssl()
{
 auto envs = QProcessEnvironment::systemEnvironment();
 QString FORGE_CLIENT_ID = envs.VALUE2(FORGE_CLIENT_ID);
 QString FORGE_CLIENT_SECRET = envs.VALUE2(FORGE_CLIENT_SECRET);

 forge_client_id_ = load_file(FORGE_CREDENTIALS_FOLDER "/id").trimmed();
 if(forge_client_id_.isEmpty())
   forge_client_id_ = FORGE_CLIENT_ID;

 forge_client_secret_ = load_file(FORGE_CREDENTIALS_FOLDER "/secret").trimmed();
 if(forge_client_secret_.isEmpty())
   forge_client_secret_ = FORGE_CLIENT_SECRET;

 libcrypto_file_name_ = LIBCRYPTO_FILE_NAME;
 libssl_file_name_ = LIBSSL_FILE_NAME;
}


void DHAX_Forge_Controller::parse_default_workflow(Forge_API_Workflow& fw)
{
 fw.parse_calls(R"(
   .; dowload a file ... ;.
  set-client-id $ %1 ;.
  set-client-secret $ %2 ;.
  load-ssl-libraries $ %3;%4 ;.
  get-access-token ;.
  check-bucket $ b3 ;.
  report-current-bucket ;.
  get-download-file-name ;.
  check-download-file ;.

 )"_q.arg(forge_client_id_).arg(forge_client_secret_)
   .arg(LIBCRYPTO_FILE_NAME).arg(LIBSSL_FILE_NAME));
}

void DHAX_Forge_Controller::run_workflow()
{
 if(forge_session_)
   delete forge_session_;

 forge_session_ = new Forge_Session;
 //Forge_Session fs;
 QPair<Forge_Runtime*, Forge_API_Workflow*> pr = init_forge(*forge_session_);

 pr.second->add_custom_env_value("FORGE_CLIENT_ID", forge_client_id_);
 pr.second->add_custom_env_value("FORGE_CLIENT_SECRET", forge_client_secret_);


 QString path = QFileDialog::getOpenFileName(nullptr, "Select Workflow", DEFAULT_FORGE_UPLOAD_FOLDER);

 if(path.isEmpty())
 {
  qDebug() << "No workflow selected; running default.";
  parse_default_workflow(*pr.second);
 }
 else
   pr.second->parse_calls_from_file(path);

 int& result = pr.second->run_calls([]()
 {
  qDebug() << "Done.";
//?  app.exit();
  return 0;
 });
// app.exec();
// qDebug() << "result: " << result;
// return result;
}

