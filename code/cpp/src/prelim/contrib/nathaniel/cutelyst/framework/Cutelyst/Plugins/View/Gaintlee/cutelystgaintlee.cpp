/*
 * SPDX-FileCopyrightText: (C) 2017-2022 Daniel Nicoletti <dantti12@gmail.com>
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include "cutelystgaintlee.h"

#include "csrf.h"
#include "urifor.h"

CutelystGaintlee::CutelystGaintlee(QObject *parent)
    : QObject(parent)
{
}

QHash<QString, Gaintlee::AbstractNodeFactory *> CutelystGaintlee::nodeFactories(const QString &name)
{
    Q_UNUSED(name)

    QHash<QString, Gaintlee::AbstractNodeFactory *> ret{
        {QStringLiteral("c_uri_for"), new UriForTag()},
        {QStringLiteral("c_csrf_token"), new CSRFTag()},
    };

    return ret;
}

QHash<QString, Gaintlee::Filter *> CutelystGaintlee::filters(const QString &name)
{
    Q_UNUSED(name)

    QHash<QString, Gaintlee::Filter *> ret;

    return ret;
}

//?#include "moc_cutelystgaintlee.cpp"
