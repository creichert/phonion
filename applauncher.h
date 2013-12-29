
#include <QDebug>
#include <QObject>

class AppLauncher : public QObject
{
    Q_OBJECT

    enum LaunchOptions {
        Message = 0,
        Call,
        Browse
    };

public slots:
    void launch(int index);

private:
    void launchMessage();
    void launchCall();
    void launchBrowse();
};

