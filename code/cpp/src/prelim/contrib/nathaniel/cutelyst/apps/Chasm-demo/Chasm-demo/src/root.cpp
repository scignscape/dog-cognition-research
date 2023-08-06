
#include "root.h"

#include "Cutelyst/tsi/response/tsi-server-response.h"
#include "Cutelyst/tsi/response/raw-file/tsi-raw-file-server-response.h"

using namespace Cutelyst;

Root::Root(QObject *parent) : Controller(parent)
{
}

Root::~Root()
{
}

void Root::index(Context* c)
{
 c->response()->body() = "Welcome to Cutelyst (chasm)";
}

void Root::defaultPage(Context* c)
{
 Request* r = c->request();
 QStringList args = r->args();

 QString controller_key;
 if(args.size() >= 2)
 {
  controller_key = args.takeFirst();
 }

 TSI_Server_Response& tsr = c->get_tsi_server_response();

 QString rc = tsr.resource_code();

 if(rc.isEmpty())
 {
  c->response()->body() = "Page not found!";
  c->response()->setStatus(404);
  return;
 }

 TSI_Raw_File_Server_Response* trsr = tsr.parse_resource_code(controller_key);

 tsr.set_raw_file_response(trsr);
 tsr.set_path_components(args);
}

