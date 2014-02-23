#ifndef PHONEAPP_H
#define PHONEAPP_H

#include <QPointer>

#include "app.h"

class Notifier;
class QQmlContext;
class VoipClient;

class PhoneApp : public App
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "co.phonion.Phonion.AppInterface" FILE "phoneapp.json")
    Q_PROPERTY(VoipClient* voipclient READ voipClient CONSTANT)
public:
    explicit PhoneApp(QObject* parent = 0);

    virtual QString id();
    virtual QString name();
    virtual QString icon();
    virtual QString source();

    VoipClient* voipClient();

protected:
    virtual void start(QQmlContext* context, const QString& onion, Notifier* notifier);

private:
    QPointer<VoipClient> _voipClient;
};

#endif // PHONEAPP_H 
