
#include "chasm-demo.h"

#include "chasm-info.h"

#include "test-controller.h"

#include "root.h"

#include "Cutelyst/Plugins/View/Grantlee/grantleeview.h"
#include "Cutelyst/tsi/chasm-view.h"

USING_CHASM_NAMESPACE


using namespace Cutelyst;

Chasm_demo::Chasm_demo(QObject *parent) : Application(parent),
  chasm_view_(nullptr), grantlee_view_(nullptr)
{
}

Chasm_demo::~Chasm_demo()
{
}

bool Chasm_demo::init()
{
 new Root(this);
 new Chasm_Info(this);
 new Test_Controller(this);

 chasm_view_ = new Chasm_View(this);
 chasm_view_->set_include_paths({ pathTo("root/src") });

 // //  note: no controllers depending on this view will
  //    be found by default, because it is not the first
  //    view created; instead, explicitly invoke this
  //    view when other views are not suitable for a
  //    particular path or controller ...
 grantlee_view_ = new GrantleeView(this);
 grantlee_view_->setIncludePaths({ pathTo("root/src") });

 return true;
}

