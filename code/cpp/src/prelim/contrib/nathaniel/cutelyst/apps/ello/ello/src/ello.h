#ifndef ELLO__H
#define ELLO__H

#include <Cutelyst/Application>

using namespace Cutelyst;

class ello : public Application
{
    Q_OBJECT
    CUTELYST_APPLICATION(IID "ello")
public:
    Q_INVOKABLE explicit ello(QObject *parent = nullptr);
    ~ello();

    bool init();
};

#endif //ELLO__H

