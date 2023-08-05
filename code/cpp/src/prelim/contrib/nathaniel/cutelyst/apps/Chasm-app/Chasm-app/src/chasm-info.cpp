
#include "chasm-info.h"

using namespace Cutelyst;

Chasm_Info::Chasm_Info(QObject *parent) : Controller(parent)
{
}

Chasm_Info::~Chasm_Info()
{
}

void Chasm_Info::index(Context* c)
{
 c->response()->body() = "Matched Controller::chasm_info in chasm_info.";
}

void Chasm_Info::list(Context *c)
{
 // c is the Cutelyst::Context that's used to 'glue together'
 // the various components that make up the application

 c->setStash("chasm_info", "");

 // Set the Grantlee template to use. You will almost always want to do this
 // in your action methods (action methods respond to user input in
 // your controllers).
 c->setStash("template", "chasm-info/list.html");
}
