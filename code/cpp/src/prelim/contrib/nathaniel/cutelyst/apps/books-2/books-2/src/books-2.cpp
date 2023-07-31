
#include "books-2.h"

#include "books.h"

#include "root.h"

#include "Cutelyst/Plugins/View/Grantlee/grantleeview.h"

using namespace Cutelyst;

books_2::books_2(QObject *parent) : Application(parent)
{
}

books_2::~books_2()
{
}

bool books_2::init()
{
 new Root(this);
 new Books(this);

 auto view = new GrantleeView(this);
 view->setIncludePaths({ pathTo("root/src") });

 return true;
}

