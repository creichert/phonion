#ifndef QAPPPHONION_H
#define QAPPPHONION_H

#include <QApplication>
#include <QPointer>
#include <QString>

class App;
class AppModel;
class Notifier;
class QObject;
class QQmlContext;
class QQuickItem;
class QQuickView;

class Phonion: public QApplication {
    Q_OBJECT
    Q_PROPERTY(AppModel* appmodel READ appModel CONSTANT)
    Q_PROPERTY(Notifier* notifier READ notifier CONSTANT)
public:
    explicit Phonion(int &argc, char **argv);

    Notifier* notifier();
    AppModel* appModel();

    Q_INVOKABLE void home();
    Q_INVOKABLE void launch(int index);
    Q_INVOKABLE const QString onion();

private:
    void loadApps();

    QPointer<Notifier> _notifier;
    QPointer<QQuickView> _view;
    QPointer<AppModel> _appModel;
    QPointer<QQmlContext> _appContext;
    QPointer<QQuickItem> _currentAppItem;

    QString _onion;
};

#endif // QAPPPHONION_H
