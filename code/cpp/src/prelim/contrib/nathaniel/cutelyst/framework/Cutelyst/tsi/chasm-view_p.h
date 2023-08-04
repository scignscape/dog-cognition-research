
#ifndef CHASM_VIEW_P__H
#define CHASM_VIEW_P__H

#include <Cutelyst/View>
#include "Cutelyst/view_p.h"

#include <QLocale>
#include <QObject>
#include <QStringList>
#include <QVector>


#include "chasm-macros.h"

CHASM_NAMESPACE_

class Chasm_ViewPrivate : public Cutelyst::ViewPrivate
{
public:

 QStringList include_paths_;

 virtual ~Chasm_ViewPrivate() override = default;
 QString extension = QStringLiteral(".html");
};

_CHASM_NAMESPACE

#endif //CHASM_VIEW_P__H

