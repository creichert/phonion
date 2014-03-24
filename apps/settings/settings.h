#ifndef SETTINGS_H
#define SETTINGS_H

#include "app.h"
#include "app.h"

class SettingsApp : public App
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "co.phonion.Phonion.AppInterface" FILE "settingsapp.json")
public:

    SettingsApp(QObject* parent=0);
    ~SettingsApp();

    virtual QString id();
    virtual QString name();
    virtual QString icon();
    virtual QString source();

protected:
    virtual void start(QQmlContext* context, const QString& onion, Notifier* notifier);
};

#endif // SETTINGS_H
