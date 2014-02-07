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
public:
    Phonion(int &argc, char **argv);

    QQmlContext* context();

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
