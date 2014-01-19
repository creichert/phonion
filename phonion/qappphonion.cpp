
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

namespace {
enum LaunchOption { Message = 0,
                    Call,
                    Browse,
                    Settings };
}

const QString QAppPhonion::launch(int index)
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
