#include "hello.h"

#include "root.h"

using namespace Cutelyst;

hello::hello(QObject *parent) : Application(parent)
{
}

hello::~hello()
{
}

bool hello::init()
{
    new Root(this);

    return true;
}

