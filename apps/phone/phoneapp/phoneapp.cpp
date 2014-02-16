
#include <QApplication>
#include <QIcon>
#include <QQmlContext>
#include <QString>

#include "phoneapp.h"
#include "notifier.h"
#include "voipclient.h"

#include "SetupMumble.h"

void PhoneApp::start(QQmlContext* context, const QString& onion, Notifier* notifier)
{
    App::start(context, onion, notifier);
#ifdef VOIP

    _voipClient = new VoipClient(onion, this);
    // Use this as parent to manage mumble resources:
    // setupMumble(*qApp, _voipClient, 0, NULL);
    setupMumble(*qApp, 0, NULL);
    context->setContextProperty("voipclient", _voipClient);
#endif
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
