
#ifndef JS_INTERFACE__H
#define JS_INTERFACE__H

#include <QObject>
#include <QDebug>

class QH_Web_Engine_Page;

#include "qh-web-engine-page.h"

class JsInterface: public QObject
{
    Q_OBJECT

 QH_Web_Engine_Page* wep_;

public:

 JsInterface(QH_Web_Engine_Page* wep) : wep_(wep) {}

    /// Log, for debugging
    Q_INVOKABLE void log(const QString& str) const
    {
        qDebug() << "LOG from JS: " << str;
    }

 Q_INVOKABLE void page_callback(QString key, const QJsonValue& msg) const
 {
  wep_->run_js_interface_callback(key, msg);
 }

};




#endif
