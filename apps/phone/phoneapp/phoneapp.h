#ifndef PHONEAPP_H
#define PHONEAPP_H

#include "app.h"

class Notifier;
class QQmlContext;

class PhoneApp : public App
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "co.phonion.Phonion.AppInterface" FILE "phoneapp.json")
public:
    virtual QString id();
    virtual QString name();
    virtual QString icon();
    virtual QString source();

protected:
    virtual void start(QQmlContext* context, const QString& onion, Notifier* notifier);
};

#endif // PHONEAPP_H 
