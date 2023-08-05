#ifndef CHASM_APP__H
#define CHASM_APP__H

#include <Cutelyst/Application>

using namespace Cutelyst;

class Chasm_app : public Application
{
 Q_OBJECT
 CUTELYST_APPLICATION(IID "Chasm_app")
public:
 Q_INVOKABLE explicit Chasm_app(QObject *parent = nullptr);
 ~Chasm_app();

 bool init();
};

#endif //CHASM_APP__H

