
#ifndef CHASM_VIEW__H
#define CHASM_VIEW__H

#include <Cutelyst/View>

#include <QLocale>
#include <QObject>
#include <QStringList>
#include <QVector>

#include "chasm-macros.h"

class QTranslator;


CHASM_NAMESPACE_

class Chasm_ViewPrivate;


class TSI_IMPORT Chasm_View : public Cutelyst::View
{
 Q_OBJECT
 Q_DECLARE_PRIVATE(Chasm_View)


public:

 explicit Chasm_View(QObject *parent = nullptr, const QString &name = QString());

 Q_PROPERTY(QStringList include_paths_ READ include_paths WRITE set_include_paths NOTIFY changed)
 QStringList include_paths() const;

 void set_include_paths(const QStringList &paths);

 QString default_file_extension() const;

 QByteArray render(Cutelyst::Context *c) const;


Q_SIGNALS:
    void changed();
};

_CHASM_NAMESPACE

#endif //CHASM_VIEW__H



// Q_PROPERTY(QString templateExtension READ templateExtension WRITE setTemplateExtension NOTIFY changed)
// QString templateExtension() const;

// void setTemplateExtension(const QString &extension);

// Q_PROPERTY(QString wrapper READ wrapper WRITE setWrapper NOTIFY changed)
// QString wrapper() const;

//    void setWrapper(const QString &name);

//    Q_PROPERTY(bool cache READ isCaching WRITE setCache NOTIFY changed)
//    /*!
//     * Returns true if caching is enabled
//     */
//    bool isCaching() const;

//    /*!
//     * Sets if template caching should be done, this increases
//     * performance at the cost of higher memory usage.
//     */
//    void setCache(bool enable);
