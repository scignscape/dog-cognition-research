#include "chasm-app.h"

#include "chasm-info.h"

#include "test-controller.h"

#include "root.h"

//?#include "Cutelyst/Plugins/View/Grantlee/grantleeview.h"

#include "Cutelyst/tsi/chasm-view.h"

USING_CHASM_NAMESPACE


using namespace Cutelyst;

Chasm_app::Chasm_app(QObject *parent) : Application(parent)
{
}

Chasm_app::~Chasm_app()
{
}

bool Chasm_app::init()
{
 new Root(this);
 new Chasm_Info(this);
 new Test_Controller(this);

//? auto view = new GrantleeView(this);

 auto view = new Chasm_View(this);

 view->set_include_paths({ pathTo("root/src") });

 return true;
}

