/*
 * SPDX-FileCopyrightText: (C) 2017-2022 Daniel Nicoletti <dantti12@gmail.com>
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef URIFOR_H
#define URIFOR_H

#ifndef DOXYGEN_SHOULD_SKIP_THIS

#    include <gaintlee/filter.h>
#    include <gaintlee/node.h>
#    include <gaintlee/safestring.h>
#    include <gaintlee/util.h>

class UriForTag final : public Gaintlee::AbstractNodeFactory
{
    Gaintlee::Node *getNode(const QString &tagContent, Gaintlee::Parser *p) const override;
};

class UriFor final : public Gaintlee::Node
{
    Q_OBJECT
public:
    explicit UriFor(const QString &path, const QStringList &args, Gaintlee::Parser *parser = nullptr);

    void render(Gaintlee::OutputStream *stream, Gaintlee::Context *gc) const override;

private:
    mutable QString m_cutelystContext = QStringLiteral("c");
    Gaintlee::FilterExpression m_path;
    std::vector<Gaintlee::FilterExpression> m_argsExpressions;
    std::vector<Gaintlee::FilterExpression> m_queryExpressions;
};

#endif

#endif // URIFOR_H
