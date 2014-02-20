#ifndef APP_H
#define APP_H

#include <QObject>
#include <QPointer>
#include <QQmlContext>
#include <QString>
#include <QtQml>

#include "buddylistmodel.h"

class Notifier;
class QString;
class QQmlContext;

/* Interface which defines the methods and App needs
 * to run in the Phonion client.
 *
 * All functions must be pure.
 */
class AppInterface {

public:
    //virtual ~App();

    virtual QString id() = 0;
    virtual QString name() = 0;
    virtual QString icon() = 0;
    virtual QString source() = 0;

protected:
    virtual void start(QQmlContext* context, const QString& onion, Notifier* notifier) = 0;
};

#define AppInterface_iid "co.phonion.Phonion.AppInterface"
Q_DECLARE_INTERFACE(AppInterface, AppInterface_iid)

/* Abstract class which defines an App type.
 */
class App : public QObject, public AppInterface {
    Q_OBJECT
    Q_INTERFACES(AppInterface)
public:

    App(QObject* parent=0)
        : QObject(parent) {
        qmlRegisterType<BuddyListModel>("Phonion", 1, 0, "BuddyListModel");
    };

    /* The standard constructor for each app sets up only the data necessary
     * to display information on the app.
     */
    QQmlContext* context() { return _context; }
    QString onion() { return _onion; }

    /* TODO: Move all the methods to a cpp file.
     */
    virtual void launch(QQmlContext* context, const QString& onion, Notifier* notifier) {
        Q_UNUSED(notifier);
        _context = context;
        _onion = onion;
        if (!_started) {
            start(context, onion, notifier);
            _started = true;
        }
    }

protected:
    virtual void start(QQmlContext* context, const QString& onion, Notifier* notifier) {
        Q_UNUSED(context);
        Q_UNUSED(onion);
        Q_UNUSED(notifier);
    }

private:
    QPointer<QQmlContext> _context;
    QString _onion;
    bool _started = false;
};

#endif // APP_H
