#include "books1.h"

#include "root.h"

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

    return true;
}

