
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
    setupMumble(*qApp, 0, NULL);

    VoipClient voip(onion);
    context->setContextProperty("voipclient", &voip);
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
