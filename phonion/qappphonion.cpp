
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

enum LaunchOption { Phone = 0,
                    Message,
                    Browser,
                    Email,
                    Wallet,
                    Settings };

const QString QAppPhonion::launch(int index)
{
    switch (index) {
    case Phone:
        qDebug() << Q_FUNC_INFO << "Phone";
        return "qrc:/qml/Phone.qml";
    case Message:
        qDebug() << Q_FUNC_INFO << "Message";
        return "qrc:/qml/Messages.qml";
    case Browser:
        qDebug() << Q_FUNC_INFO << "Browser";
        return "qrc:/qml/Browser.qml";
    case Email:
        qDebug() << Q_FUNC_INFO << "Email";
        return "qrc:/qml/Email.qml";
    case Wallet:
        qDebug() << Q_FUNC_INFO << "Wallet";
        return "qrc:/qml/Wallet.qml";
    case Settings:
        qDebug() << Q_FUNC_INFO << "Settings";
        return "qrc:/qml/Settings.qml";
    default:
        qDebug() << Q_FUNC_INFO << "Unknown launch option. Going home.";
        return "qrc:/qml/Home.qml";
    }
}
