#ifndef QAPPPHONION_H
#define QAPPPHONION_H

#include <QApplication>
#include <QPointer>
#include <QString>

class App;
class AppModel;
class Notifier;
class QQmlContext;
class QQuickView;

class Phonion: public QApplication {
    Q_OBJECT
    Q_PROPERTY(AppModel* appmodel READ appModel CONSTANT)
    Q_PROPERTY(Notifier* notifier READ notifier CONSTANT)
public:
    Phonion(int &argc, char **argv);

    Notifier* notifier();
    AppModel* appModel();

    Q_INVOKABLE const QString home();
    Q_INVOKABLE const QString launch(int index);
    Q_INVOKABLE const QString onion();

private:
    void loadApps();

    QPointer<Notifier> _notifier;
    QPointer<QQuickView> _view;
    QPointer<AppModel> _appModel;

    QString _onion;
};

#endif // QAPPPHONION_H
