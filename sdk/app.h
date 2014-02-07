#ifndef APP_H
#define APP_H

#include <QObject>
#include <QPointer>
#include <QQmlContext>
#include <QString>

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

    // virtual void launch();
    virtual QString id() = 0;
    virtual QString name() = 0;
    virtual QString icon() = 0;
    virtual QString source() = 0;
};

#define AppInterface_iid "co.phonion.Phonion.AppInterface"
Q_DECLARE_INTERFACE(AppInterface, AppInterface_iid)

/* Abstract class which defines an App type.
 */
class App : public QObject, public AppInterface {
    Q_OBJECT
    Q_INTERFACES(AppInterface)
public:

    /* The standard constructor for each app sets up only the data necessary
     * to display information on the app.
     */
    QQmlContext* context() { return _context; }
    QString onion() { return _onion; }

    /* `startApp` launches the application and initializes data models.
     */
    virtual void startApp(QQmlContext* context, const QString& onion, Notifier* notifier) {
        Q_UNUSED(notifier);
        _context = context;
        _onion = onion;
        _initialized = true;
    }

    bool initialized() { return _initialized; }

private:
    QPointer<QQmlContext> _context;
    QString _onion;
    bool _initialized;
};

#endif // APP_H
