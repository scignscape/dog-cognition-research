#ifndef HELLO__H
#define HELLO__H

#include <Cutelyst/Application>

using namespace Cutelyst;

class hello : public Application
{
    Q_OBJECT
    CUTELYST_APPLICATION(IID "hello")
public:
    Q_INVOKABLE explicit hello(QObject *parent = nullptr);
    ~hello();

    bool init();
};

#endif //HELLO__H

