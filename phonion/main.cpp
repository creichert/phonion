
#include <QApplication>
#include <QFileInfo>
#include <QNetworkProxy>
#include <QProcess>
#include <QString>
#include <QStringList>
#include <QQuickView>
#include <QQmlContext>
#include <QUrl>

#include "applauncher.h"
#include "buddylistmodel.h"
#include "chatmodel.h"
#include "messageapp.h"
#include "voipclient.h"

#include "SetupMumble.h"

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

class QAppPhonion: public QApplication {
public:
    QAppPhonion(int &argc, char **argv) : QApplication(argc, argv) {}
};

int main(int argc, char** argv) {

    QAppPhonion a(argc, argv);
	a.setApplicationName(QLatin1String("Phonion"));
	a.setOrganizationName(QLatin1String("Phonion"));
	a.setOrganizationDomain(QLatin1String("phonion.phonion.co"));
#ifdef VOIP
    setupMumble(a, argc, argv);
    qDebug() << "Mumble initialization complete.";
#endif

    const QString onion = hiddenServiceAddress();
    initializeMumbleServer();
    AppLauncher applauncher(onion);
    MessageApp msgApp;

    // Proxy through TorChat for Mumble.
    QNetworkProxy proxy;
    proxy.setType(QNetworkProxy::Socks5Proxy);
    proxy.setHostName("127.0.0.1");
    proxy.setPort(11109);
    QNetworkProxy::setApplicationProxy(proxy);

    QQuickView v;
    v.setResizeMode(QQuickView::SizeRootObjectToView);
    v.rootContext()->setContextProperty("AppLauncher", &applauncher);
    v.rootContext()->setContextProperty("MessageApp", &msgApp);
    v.rootContext()->setContextProperty("messagemodel", msgApp.chatModel());
    v.rootContext()->setContextProperty("buddylistmodel", msgApp.buddyListModel());
#ifdef VOIP
    VoipClient voip(onion);
    v.rootContext()->setContextProperty("voipclient", &voip);
#endif
    v.setSource(QUrl("qrc:/qml/main.qml"));
    v.show();

    return a.exec();
}
