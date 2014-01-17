
#include <QApplication>
#include <QFileInfo>
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
    QFile f("./phonion/torchat/src/Tor/hidden_service/hostname");
    if(!f.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning("Hidden service not found");
        return onion;
    }

    onion = f.read(16);
    qDebug() << "Identified hidden service: " << onion;
    return onion;
}

int main(int argc, char** argv) {

#ifdef VOIP
    QAppMumble a(argc, argv);
	a.setApplicationName(QLatin1String("Phonion"));
	a.setOrganizationName(QLatin1String("Phonion"));
	a.setOrganizationDomain(QLatin1String("phonion.phonion.co"));
    setupMumble(a, argc, argv);
    qDebug() << "Mumble initialization complete.";
#else
    QGuiApplication a(argc, argv);
#endif


    const QString onion = hiddenServiceAddress();
    initializeMumbleServer();
    AppLauncher applauncher(onion);
    MessageApp msgApp;

    // Proxy for WebView
    //QNetworkProxy proxy;
    //proxy.setType(QNetworkProxy::HttpProxy);
    //proxy.setHostName("127.0.0.1");
    //proxy.setPort(9051);
    //QNetworkProxy::setApplicationProxy(proxy);

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
