/*
 * SPDX-FileCopyrightText: (C) 2013-2022 Daniel Nicoletti <dantti12@gmail.com>
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include "action.h"
#include "application.h"
#include "config.h"
#include "context.h"
#include "gaintleeview_p.h"
#include "response.h"

#include <gaintlee/metatype.h>
#include <gaintlee/qtlocalizer.h>

#include <QDirIterator>
#include <QString>
#include <QTranslator>
#include <QtCore/QLoggingCategory>

#define loadByName_debug  loadByName

Q_LOGGING_CATEGORY(CUTELYST_GAINTLEE, "cutelyst.gaintlee", QtWarningMsg)

using namespace Cutelyst;

GAINTLEE_BEGIN_LOOKUP(ParamsMultiMap)
return object.value(property);
GAINTLEE_END_LOOKUP

GAINTLEE_BEGIN_LOOKUP_PTR(Cutelyst::Request)
return object->property(property.toLatin1().constData());
GAINTLEE_END_LOOKUP

GaintleeView::GaintleeView(QObject *parent, const QString &name)
    : View(new GaintleeViewPrivate, parent, name)
{
    Q_D(GaintleeView);

    Gaintlee::registerMetaType<ParamsMultiMap>();
    Gaintlee::registerMetaType<Cutelyst::Request *>(); // To be able to access it's properties

    d->loader = QSharedPointer<Gaintlee::FileSystemTemplateLoader>(new Gaintlee::FileSystemTemplateLoader);

    d->engine = new Gaintlee::Engine(this);
    d->engine->addTemplateLoader(d->loader);

    QString plugins_dir = CUTELYST_PLUGINS_DIR;

    // Set also the paths from CUTELYST_PLUGINS_DIR env variable as plugin paths of gaintlee engine
    const QByteArrayList dirs = QByteArrayList{QByteArrayLiteral(CUTELYST_PLUGINS_DIR)} + qgetenv("CUTELYST_PLUGINS_DIR").split(';');
    for (const QByteArray &dir : dirs) {
        d->engine->addPluginPath(QString::fromLocal8Bit(dir));
    }

//?    d->engine->addDefaultLibrary(QStringLiteral("gaintlee_cutelyst"));
    d->engine->addDefaultLibrary(QStringLiteral("libgaintlee-view"));

    auto app = qobject_cast<Application *>(parent);
    if (app) {
        // make sure templates can be found on the current directory
        setIncludePaths({app->config(QStringLiteral("root")).toString()});

        // If CUTELYST_VAR is set the template might have become
        // {{ Cutelyst.req.base }} instead of {{ c.req.base }}
        d->cutelystVar = app->config(QStringLiteral("CUTELYST_VAR"), QStringLiteral("c")).toString();

        app->loadTranslations(QStringLiteral("plugin_view_gaintlee"));
    } else {
        // make sure templates can be found on the current directory
        setIncludePaths({QDir::currentPath()});
    }
}

QStringList GaintleeView::includePaths() const
{
    Q_D(const GaintleeView);
    return d->includePaths;
}

void GaintleeView::setIncludePaths(const QStringList &paths)
{
    Q_D(GaintleeView);
    d->loader->setTemplateDirs(paths);
    d->includePaths = paths;
    Q_EMIT changed();
}

QString GaintleeView::templateExtension() const
{
    Q_D(const GaintleeView);
    return d->extension;
}

void GaintleeView::setTemplateExtension(const QString &extension)
{
    Q_D(GaintleeView);
    d->extension = extension;
    Q_EMIT changed();
}

QString GaintleeView::wrapper() const
{
    Q_D(const GaintleeView);
    return d->wrapper;
}

void GaintleeView::setWrapper(const QString &name)
{
    Q_D(GaintleeView);
    d->wrapper = name;
    Q_EMIT changed();
}

void GaintleeView::setCache(bool enable)
{
    Q_D(GaintleeView);

    if (enable != d->cache.isNull()) {
        return; // already enabled
    }

    delete d->engine;
    d->engine = new Gaintlee::Engine(this);

    if (enable) {
        d->cache = QSharedPointer<Gaintlee::CachingLoaderDecorator>(new Gaintlee::CachingLoaderDecorator(d->loader));
        d->engine->addTemplateLoader(d->cache);
    } else {
        d->cache.clear();
        d->engine->addTemplateLoader(d->loader);
    }
    Q_EMIT changed();
}

Gaintlee::Engine *GaintleeView::engine() const
{
    Q_D(const GaintleeView);
    return d->engine;
}

void GaintleeView::preloadTemplates()
{
    Q_D(GaintleeView);

    if (!isCaching()) {
        setCache(true);
    }

    const auto includePaths = d->includePaths;
    for (const QString &includePath : includePaths) {
        QDirIterator it(includePath, {QLatin1Char('*') + d->extension}, QDir::Files | QDir::NoDotAndDotDot, QDirIterator::Subdirectories);
        while (it.hasNext()) {
            QString path = it.next();
            path.remove(includePath);
            if (path.startsWith(QLatin1Char('/'))) {
                path.remove(0, 1);
            }

            if (d->cache->canLoadTemplate(path)) {
                d->cache->loadByName_debug(path, d->engine);
            }
        }
    }
}

bool GaintleeView::isCaching() const
{
    Q_D(const GaintleeView);
    return !d->cache.isNull();
}

QByteArray GaintleeView::render(Context *c) const
{
    Q_D(const GaintleeView);

    QByteArray ret;
    c->setStash(d->cutelystVar, QVariant::fromValue(c));
    const QVariantHash stash = c->stash();
    auto it                  = stash.constFind(QStringLiteral("template"));
    QString templateFile;
    if (it != stash.constEnd()) {
        templateFile = it.value().toString();
    } else {
        if (c->action() && !c->action()->reverse().isEmpty()) {
            templateFile = c->action()->reverse() + d->extension;
            if (templateFile.startsWith(QLatin1Char('/'))) {
                templateFile.remove(0, 1);
            }
        }

        if (templateFile.isEmpty()) {
            c->error(QStringLiteral("Cannot render template, template name or template stash key not defined"));
            return ret;
        }
    }

    qCDebug(CUTELYST_GAINTLEE) << "Rendering template" << templateFile;

    Gaintlee::Context gc(stash);

    auto localizer = QSharedPointer<Gaintlee::QtLocalizer>::create(c->locale());

    auto transIt = d->translators.constFind(c->locale());
    if (transIt != d->translators.constEnd()) {
        localizer.data()->installTranslator(transIt.value(), transIt.key().name());
    }

    auto catalogIt = d->translationCatalogs.constBegin();
    while (catalogIt != d->translationCatalogs.constEnd()) {
        localizer.data()->loadCatalog(catalogIt.value(), catalogIt.key());
        ++it;
    }

    gc.setLocalizer(localizer);

    Gaintlee::Template tmpl = d->engine->loadByName_debug(templateFile);
    if (tmpl->error() != Gaintlee::NoError) {
        c->res()->setBody(c->translate("Cutelyst::GaintleeView", "Internal server error."));
        c->error(QLatin1String("Error while rendering template: ") + tmpl->errorString());
        return ret;
    }

    QString content = tmpl->render(&gc);
    if (tmpl->error() != Gaintlee::NoError) {
        c->res()->setBody(c->translate("Cutelyst::GaintleeView", "Internal server error."));
        c->error(QLatin1String("Error while rendering template: ") + tmpl->errorString());
        return ret;
    }

    if (!d->wrapper.isEmpty()) {
        Gaintlee::Template wrapper = d->engine->loadByName_debug(d->wrapper);
        if (tmpl->error() != Gaintlee::NoError) {
            c->res()->setBody(c->translate("Cutelyst::GaintleeView", "Internal server error."));
            c->error(QLatin1String("Error while rendering template: ") + tmpl->errorString());
            return ret;
        }

        Gaintlee::SafeString safeContent(content, true);
        gc.insert(QStringLiteral("content"), safeContent);
        content = wrapper->render(&gc);

        if (wrapper->error() != Gaintlee::NoError) {
            c->res()->setBody(c->translate("Cutelyst::GaintleeView", "Internal server error."));
            c->error(QLatin1String("Error while rendering template: ") + tmpl->errorString());
            return ret;
        }
    }

    ret = content.toUtf8();
    return ret;
}

void GaintleeView::addTranslator(const QLocale &locale, QTranslator *translator)
{
    Q_D(GaintleeView);
    Q_ASSERT_X(translator, "add translator to GaintleeView", "invalid QTranslator object");
    d->translators.insert(locale, translator);
}

void GaintleeView::addTranslator(const QString &locale, QTranslator *translator)
{
    addTranslator(QLocale(locale), translator);
}

void GaintleeView::addTranslationCatalog(const QString &path, const QString &catalog)
{
    Q_D(GaintleeView);
    Q_ASSERT_X(!path.isEmpty(), "add translation catalog to GaintleeView", "empty path");
    Q_ASSERT_X(!catalog.isEmpty(), "add translation catalog to GaintleeView", "empty catalog name");
    d->translationCatalogs.insert(catalog, path);
}

void GaintleeView::addTranslationCatalogs(const QHash<QString, QString> &catalogs)
{
    Q_D(GaintleeView);
    Q_ASSERT_X(!catalogs.empty(), "add translation catalogs to GranteleeView", "empty QHash");
    d->translationCatalogs.unite(catalogs);
}

QVector<QLocale> GaintleeView::loadTranslationsFromDir(const QString &filename, const QString &directory, const QString &prefix, const QString &suffix)
{
    QVector<QLocale> locales;

    if (Q_LIKELY(!filename.isEmpty() && !directory.isEmpty())) {
        const QDir i18nDir(directory);
        if (Q_LIKELY(i18nDir.exists())) {
            const QString _prefix         = prefix.isEmpty() ? QStringLiteral(".") : prefix;
            const QString _suffix         = suffix.isEmpty() ? QStringLiteral(".qm") : suffix;
            const QStringList namesFilter = QStringList({filename + _prefix + QLatin1Char('*') + _suffix});
            const QFileInfoList tsFiles   = i18nDir.entryInfoList(namesFilter, QDir::Files);
            if (Q_LIKELY(!tsFiles.empty())) {
                locales.reserve(tsFiles.size());
                for (const QFileInfo &ts : tsFiles) {
                    const QString fn        = ts.fileName();
                    const int prefIdx       = fn.indexOf(_prefix);
                    const QString locString = fn.mid(prefIdx + _prefix.length(), fn.length() - prefIdx - _suffix.length() - _prefix.length());
                    QLocale loc(locString);
                    if (Q_LIKELY(loc.language() != QLocale::C)) {
                        auto trans = new QTranslator(this);
                        if (Q_LIKELY(trans->load(loc, filename, _prefix, directory))) {
                            addTranslator(loc, trans);
                            locales.append(loc);
                            qCDebug(CUTELYST_GAINTLEE) << "Loaded translations for locale" << loc << "from" << ts.absoluteFilePath();
                        } else {
                            delete trans;
                            qCWarning(CUTELYST_GAINTLEE) << "Can not load translations for locale" << loc;
                        }
                    } else {
                        qCWarning(CUTELYST_GAINTLEE) << "Can not load translations for invalid locale string" << locString;
                    }
                }
                locales.squeeze();
            } else {
                qCWarning(CUTELYST_GAINTLEE) << "Can not find translation files for" << filename << "in directory" << directory;
            }
        } else {
            qCWarning(CUTELYST_GAINTLEE) << "Can not load translations from not existing directory:" << directory;
        }
    } else {
        qCWarning(CUTELYST_GAINTLEE) << "Can not load translations for empty file name or empty path.";
    }

    return locales;
}

//?#include "moc_gaintleeview.cpp"
