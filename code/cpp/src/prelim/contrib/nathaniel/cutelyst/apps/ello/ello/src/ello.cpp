#include "ello.h"

#include "root.h"

using namespace Cutelyst;

ello::ello(QObject *parent) : Application(parent)
{
}

ello::~ello()
{
}

bool ello::init()
{
    new Root(this);

    return true;
}

