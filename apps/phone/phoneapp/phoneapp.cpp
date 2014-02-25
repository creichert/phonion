
#include <QApplication>
#include <QIcon>
#include <QQmlContext>
#include <QString>

#include "phoneapp.h"
#include "notifier.h"
#include "voipclient.h"

#include "SetupMumble.h"

PhoneApp::PhoneApp(QObject* parent)
    : App(parent)
    , _voipClient(0)
{
    qmlRegisterType<VoipClient>("Phonion", 1, 0, "VoipClient");
}

void PhoneApp::start(QQmlContext* context, const QString& onion, Notifier* notifier)
{
    App::start(context, onion, notifier);

    _voipClient = new VoipClient(onion, this);
    /* TODO: Use this as parent to manage mumble resources:
     *       `setupMumble(*qApp, _voipClient, 0, NULL);`
     */
    setupMumble(*qApp, 0, NULL);
}

QString PhoneApp::id()
{
    return "PhoneApp";
}

QString PhoneApp::name()
{
    return "Phone";
}

QString PhoneApp::icon()
{
    return "qrc:/phone/phone.png";
}

QString PhoneApp::source()
{
    return "qrc:/qml/Phone.qml";
}

VoipClient* PhoneApp::voipClient()
{
    return _voipClient;
}
