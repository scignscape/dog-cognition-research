
#ifndef CHASM_INFO__H
#define CHASM_INFO__H

#include <Cutelyst/Controller>

using namespace Cutelyst;

class Chasm_Info : public Controller
{
 Q_OBJECT
public:
 explicit Chasm_Info(QObject *parent = nullptr);
 ~Chasm_Info();

 C_ATTR(index, :Path :AutoArgs)
 void index(Context* c);

 C_ATTR(list, :Local)
 void list(Context *c);
};

#endif //CHASM_INFO__H

