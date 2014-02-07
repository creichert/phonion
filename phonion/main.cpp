
#include <QFileInfo>
#include <QProcess>
#include <QNetworkProxy>
#include <QString>
#include <QStringList>
#include <QQuickView>
#include <QQmlContext>
#include <QUrl>

#include "SetupMumble.h"

#include "buddylistmodel.h"
#include "chatmodel.h"
#include "messageapp.h"
#include "qappphonion.h"
#include "voipclient.h"
#include "notifier.h"

#define PROXY_HOST "127.0.0.1"
#define PROXY_PORT 11109

void initializeMumbleServer() {
    //QProcess* process = new QProcess;
    //process->start("murmurd", QStringList() << "-ini" << QFileInfo("mumble-server.ini").absoluteFilePath());
    //qDebug() << "Murmurd Exit Code: " << process->exitCode();
}

const QString hiddenServiceAddress() {

    QString onion;

    // Use QFileInfo and also check against security key.
    QFile f("./phonion/torchat/torchat/src/Tor/hidden_service/hostname");
    if(!f.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning("Hidden service not found");
        return onion;
    }

    onion = f.read(16);
    qDebug() << "Identified hidden service: " << onion;
    return onion;
}

int main(int argc, char** argv) {

    QAppPhonion a(argc, argv);

    const QString onion = hiddenServiceAddress();
    a.setOnion(onion);

#ifdef VOIP
    setupMumble(a, argc, argv);
    initializeMumbleServer();
    qDebug() << "Mumble initialization complete.";
#endif

    MessageApp msgApp;

    QNetworkProxy proxy;
    proxy.setType(QNetworkProxy::Socks5Proxy);
    proxy.setHostName(PROXY_HOST);
    proxy.setPort(PROXY_PORT);
    QNetworkProxy::setApplicationProxy(proxy);

    Notifier notifier;
    QObject::connect(msgApp.chatModel(), SIGNAL(messageNotification(const QString&)), &notifier, SIGNAL(messageNotification(const QString&)));

    QQuickView v;
    v.setResizeMode(QQuickView::SizeRootObjectToView);
    v.rootContext()->setContextProperty("app", &a);
    v.rootContext()->setContextProperty("MessageApp", &msgApp);
    v.rootContext()->setContextProperty("messagemodel", msgApp.chatModel());
    v.rootContext()->setContextProperty("notifier", &notifier);
    v.rootContext()->setContextProperty("buddylistmodel", msgApp.buddyListModel());
#ifdef VOIP
    VoipClient voip(onion);
    v.rootContext()->setContextProperty("voipclient", &voip);
#endif
    v.setSource(QUrl("qrc:/qml/Main.qml"));
    v.show();

    return a.exec();
}
