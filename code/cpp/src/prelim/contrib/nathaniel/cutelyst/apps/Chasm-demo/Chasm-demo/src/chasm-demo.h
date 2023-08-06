#ifndef CHASM_DEMO__H
#define CHASM_DEMO__H


         #define _including_from_app_
#include <Cutelyst/Application>
         #undef _including_from_app_


using namespace Cutelyst;


namespace_class(Cutelyst ,GrantleeView)
namespace_class(Chasm::TSI ,Chasm_View)


#include "Cutelyst/tsi/chasm-macros.h"
USING_CHASM_NAMESPACE


class Chasm_demo : public Application
{
 Q_OBJECT
 CUTELYST_APPLICATION(IID "Chasm_app")

 Chasm_View* chasm_view_;
 GrantleeView* grantlee_view_;


public:


 Q_INVOKABLE explicit Chasm_demo(QObject *parent = nullptr);
 ~Chasm_demo();

 bool init();
};

#endif //CHASM_DEMO__H

