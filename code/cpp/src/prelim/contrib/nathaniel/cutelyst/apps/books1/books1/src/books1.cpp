
#include "Cutelyst/Plugins/View/Grantlee/grantleeview.h"

#include "books1.h"

#include "root.h"

#include "books.h"

using namespace Cutelyst;


books1::books1(QObject *parent) : Application(parent)
{
}

books1::~books1()
{
}

bool books1::init()
{
 new Root(this);

 new Books(this);


 auto view = new GrantleeView(this);
 view->setIncludePaths({ pathTo("root/src") });
 return true;
}

