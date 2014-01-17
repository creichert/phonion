
#include <QDebug>
#include <QFile>
#include <QIODevice>
#include <QProcess>
#include <QString>
#include <QStringRef>

#include "applauncher.h"

AppLauncher::AppLauncher(const QString& onion, QObject* parent)
  : QObject(parent)
  , _addr(onion)
{
}

QString AppLauncher::prettyOnion()
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

