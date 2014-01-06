#ifndef APPLAUNCHER_H
#define APPLAUNCHER_H

#include <QDebug>
#include <QObject>
#include <QPointer>
#include <QProcess>
#include <QString>

class AppLauncher : public QObject
{
    Q_OBJECT
public:
    AppLauncher();

    Q_INVOKABLE QString onion();
    Q_INVOKABLE QString launch(int index);

private:
    QString _addr;
};

#endif // APPLAUNCHER_H
