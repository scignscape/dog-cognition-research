#ifndef BOOKS1__H
#define BOOKS1__H

#include <Cutelyst/Application>

using namespace Cutelyst;

class books1 : public Application
{
    Q_OBJECT
    CUTELYST_APPLICATION(IID "books1")
public:
    Q_INVOKABLE explicit books1(QObject *parent = nullptr);
    ~books1();

    bool init();
};

#endif //BOOKS1__H

