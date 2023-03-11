
#ifndef JS_INTERFACE__H
#define JS_INTERFACE__H

#include <QObject>
#include <QDebug>

#include "qh-web-engine-page.h"


#include "kans.h"

KANS_(RdSC)

class QH_Web_Engine_Page;

USING_KANS(RdSC)

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

 Q_INVOKABLE void page_callback_str(QString key, QString msg) const
 {
  wep_->run_js_interface_callback(key, msg);
 }

 Q_INVOKABLE void page_callback_jsv(const QJsonValue& key, const QJsonValue& msg) const
 {
  wep_->run_js_interface_callback(key, msg);
 }

};


_KANS(RdSC)



#endif
