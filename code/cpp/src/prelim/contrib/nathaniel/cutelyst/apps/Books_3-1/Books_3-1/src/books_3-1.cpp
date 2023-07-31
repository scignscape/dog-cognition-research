


#include "books_3-1.h"

#include "books.h"

#include "root.h"

#include "Cutelyst/Plugins/View/Grantlee/grantleeview.h"

using namespace Cutelyst;

Books_3_1::Books_3_1(QObject *parent) : Application(parent)
{
}

Books_3_1::~Books_3_1()
{
}

bool Books_3_1::init()
{
 new Root(this);

 new Books(this);


 auto view = new GrantleeView(this);
 view->setIncludePaths({ pathTo("root/src") });

 return true;
}

