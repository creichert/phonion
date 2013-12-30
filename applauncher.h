
#include <QDebug>
#include <QObject>
#include <QPointer>
#include <QProcess>
#include <QString>

class AppLauncher : public QObject
{
    Q_OBJECT

    enum LaunchOptions {
        Message = 0,
        Call,
        Browse
    };

public:
    AppLauncher();

    Q_INVOKABLE QString onion();

public slots:
    void launch(int index);

private:
    void launchMessage();
    void launchCall();
    void launchBrowse();

    QString _addr;
    QPointer<QProcess> _proc;
};

