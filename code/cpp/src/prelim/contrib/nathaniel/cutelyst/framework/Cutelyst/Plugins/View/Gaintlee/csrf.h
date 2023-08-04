/*
 * SPDX-FileCopyrightText: (C) 2017-2022 Matthias Fehring <mf@huessenbergnetz.de>
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef CSRF_H
#define CSRF_H

#ifndef DOXYGEN_SHOULD_SKIP_THIS

#    include <gaintlee/filter.h>
#    include <gaintlee/node.h>
#    include <gaintlee/safestring.h>
#    include <gaintlee/util.h>

class CSRFTag final : public Gaintlee::AbstractNodeFactory
{
    Q_OBJECT
public:
    Gaintlee::Node *getNode(const QString &tagContent, Gaintlee::Parser *p) const override;
};

class CSRF final : public Gaintlee::Node
{
    Q_OBJECT
public:
    explicit CSRF(Gaintlee::Parser *parser = nullptr);

    void render(Gaintlee::OutputStream *stream, Gaintlee::Context *gc) const override;

private:
    mutable QString m_cutelystContext = QStringLiteral("c");
};

#endif // DOXYGEN_SHOULD_SKIP_THIS

#endif // CSRF_H
