#include "demo-tutorial.h"

#include "root.h"

#include "books.h"

#include "Cutelyst/Plugins/View/Grantlee/grantleeview.h"


using namespace Cutelyst;

demo_tutorial::demo_tutorial(QObject *parent) : Application(parent)
{
}

demo_tutorial::~demo_tutorial()
{
}

bool demo_tutorial::init()
{
 new Root(this);

 new Books(this);


 auto view = new GrantleeView(this);
 view->setIncludePaths({ pathTo("root/src") });

 return true;
}

