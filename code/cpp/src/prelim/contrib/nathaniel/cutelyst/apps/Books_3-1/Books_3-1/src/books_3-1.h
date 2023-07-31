#ifndef BOOKS_3_1__H
#define BOOKS_3_1__H

#include <Cutelyst/Application>

using namespace Cutelyst;

class Books_3_1 : public Application
{
 Q_OBJECT
 CUTELYST_APPLICATION(IID "Books_3_1")
public:
 Q_INVOKABLE explicit Books_3_1(QObject *parent = nullptr);
 ~Books_3_1();

 bool init();
};

#endif //BOOKS_3_1__H

