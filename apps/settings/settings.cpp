
#include <QObject>
#include <QQmlContext>
#include <QString>

#include "app.h"
#include "notifier.h"
#include "settings.h"

SettingsApp::SettingsApp(QObject* parent)
    : App(parent)
{
}

SettingsApp::~SettingsApp()
{
}

void SettingsApp::start(QQmlContext* context, const QString& onion, Notifier* notifier)
{
    App::start(context, onion, notifier);
}

QString SettingsApp::id()
{
    return "SettingsApp";
}

QString SettingsApp::name()
{
    return "Settings";
}

QString SettingsApp::icon()
{
    return "qrc:/settings/settings.png";
}

QString SettingsApp::source()
{
    return "qrc:/qml/Settings.qml";
}
