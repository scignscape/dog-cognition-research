#ifndef DEMO_TUTORIAL__H
#define DEMO_TUTORIAL__H

#include <Cutelyst/Application>

using namespace Cutelyst;

class demo_tutorial : public Application
{
 Q_OBJECT
 CUTELYST_APPLICATION(IID "demo_tutorial")
public:
 Q_INVOKABLE explicit demo_tutorial(QObject *parent = nullptr);
 ~demo_tutorial();

 bool init();
};

#endif //DEMO_TUTORIAL__H

