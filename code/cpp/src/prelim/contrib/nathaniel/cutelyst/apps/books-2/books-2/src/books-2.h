#ifndef BOOKS_2__H
#define BOOKS_2__H

#include <Cutelyst/Application>

using namespace Cutelyst;

class books_2 : public Application
{
 Q_OBJECT
 CUTELYST_APPLICATION(IID "books_2")
public:
 Q_INVOKABLE explicit books_2(QObject *parent = nullptr);
 ~books_2();

 bool init();
};

#endif //BOOKS_2__H

