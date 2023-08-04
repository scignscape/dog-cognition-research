/*
 * SPDX-FileCopyrightText: (C) 2013-2022 Daniel Nicoletti <dantti12@gmail.com>
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef GAINTLEE_VIEW_P_H
#define GAINTLEE_VIEW_P_H

#include "gaintleeview.h"
#include "view_p.h"

#include <gaintlee/cachingloaderdecorator.h>
#include <gaintlee/engine.h>
#include <gaintlee/templateloader.h>

namespace Cutelyst {

class GaintleeViewPrivate : public ViewPrivate
{
public:
    virtual ~GaintleeViewPrivate() override = default;

    QStringList includePaths;
    QString extension = QStringLiteral(".html");
    QString wrapper;
    QString cutelystVar;
    Gaintlee::Engine *engine;
    QSharedPointer<Gaintlee::FileSystemTemplateLoader> loader;
    QSharedPointer<Gaintlee::CachingLoaderDecorator> cache;
    QHash<QLocale, QTranslator *> translators;
    QHash<QString, QString> translationCatalogs;
};

} // namespace Cutelyst

#endif // GAINTLEE_VIEW_P_H
