#include "books.h"

using namespace Cutelyst;

Books::Books(QObject *parent) : Controller(parent)
{
}

Books::~Books()
{
}

void Books::index(Context *c)
{
    c->response()->body() = "Matched Controller::Books in Books.";
}

