
#include <QDebug>
#include <QString>

#include "qappphonion.h"

const QString QAppPhonion::prettyOnion()
{
    return QString("%1 - %2 - %3 - %4").arg(_onion.mid(0,4))
                                       .arg(_onion.mid(4,4))
                                       .arg(_onion.mid(8,4))
                                       .arg(_onion.mid(12,4));
}

enum LaunchOption { Message = 0,
                    Call,
                    Browse,
                    Settings };

const QString QAppPhonion::launch(int index)
{
    switch (index) {
    case Message:
        qDebug() << Q_FUNC_INFO << "Message";
        return "qrc:/qml/Message.qml";
    case Call:
        qDebug() << Q_FUNC_INFO << "Call";
        return "qrc:/qml/Call.qml";
    case Browse:
        qDebug() << Q_FUNC_INFO << "Browse";
        return "qrc:/qml/Browse.qml";
    case Settings:
        qDebug() << Q_FUNC_INFO << "Settings";
        return "qrc:/qml/Settings.qml";
    default:
        qDebug() << Q_FUNC_INFO << "Unknown launch option. Going home.";
        return "qrc:/qml/Home.qml";
    }
}
