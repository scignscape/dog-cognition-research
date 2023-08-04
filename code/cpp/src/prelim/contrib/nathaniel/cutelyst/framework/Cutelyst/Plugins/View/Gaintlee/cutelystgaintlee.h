/*
 * SPDX-FileCopyrightText: (C) 2017-2022 Daniel Nicoletti <dantti12@gmail.com>
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef CUTELYSTGAINTLEE_H
#define CUTELYSTGAINTLEE_H

#ifndef DOXYGEN_SHOULD_SKIP_THIS

#    include <gaintlee/taglibraryinterface.h>

#    if defined(cutelyst_gaintlee_urifor_EXPORTS)
#        define CUTELYST_GAINTLEE_URIFOR_EXPORT Q_DECL_EXPORT
#    else
#        define CUTELYST_GAINTLEE_URIFOR_EXPORT Q_DECL_IMPORT
#    endif

class CutelystGaintlee final : public QObject
    , public Gaintlee::TagLibraryInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.gaintlee.TagLibraryInterface/1.0")
    Q_INTERFACES(Gaintlee::TagLibraryInterface)
public:
    explicit CutelystGaintlee(QObject *parent = nullptr);

    virtual QHash<QString, Gaintlee::AbstractNodeFactory *> nodeFactories(const QString &name = QString()) override;

    virtual QHash<QString, Gaintlee::Filter *> filters(const QString &name = QString()) override;
};

#endif

#endif // CUTELYSTGAINTLEE_H
