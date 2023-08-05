#ifndef ROOT__H
#define ROOT__H

#include <Cutelyst/Controller>

using namespace Cutelyst;

class Root : public Controller
{
 Q_OBJECT
 C_NAMESPACE("")
public:
 explicit Root(QObject *parent = nullptr);
 ~Root();

 C_ATTR(index, :Path :AutoArgs)
 void index(Context* c);

 C_ATTR(defaultPage, :Path)
 void defaultPage(Context* c);

private:
 C_ATTR(End, :ActionClass("RenderView"))
 void End(Context* c) { Q_UNUSED(c); }
};

#endif //ROOT__H

