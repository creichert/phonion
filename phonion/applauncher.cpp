
#include <QDebug>
#include <QFile>
#include <QIODevice>
#include <QProcess>
#include <QString>
#include <QStringRef>

#include "applauncher.h"

AppLauncher::AppLauncher()
{
    // Use QFileInfo and also check against security key.
    QFile f("./phonion/torchat/src/Tor/hidden_service/hostname");
    if(!f.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning("Hidden service not found");
        return;
    }

    _addr = f.read(16);
    qDebug() << "Identified onion: " << _addr;
}

QString AppLauncher::onion()
{
    return QString("%1 - %2 - %3 - %4").arg(_addr.mid(0,4))
                                 .arg(_addr.mid(4,4))
                                 .arg(_addr.mid(8,4))
                                 .arg(_addr.mid(12,4));
}

enum LaunchOptions { Message = 0,
                     Call,
                     Browse,
                     Settings };

QString AppLauncher::launch(int index)
{
    switch (index) {
    case Message:
        qDebug() << "Message";
        return "qrc:/qml/message.qml";
    case Call:
        qDebug() << "Call";
        return "qrc:/qml/call.qml";
    case Browse:
        qDebug() << "Browse";
        return "qrc:/qml/browse.qml";
    case Settings:
        qDebug() << "Settings";
        return "qrc:/qml/settings.qml";
    default:
        return "qrc:/qml/home.qml";
    }
}

