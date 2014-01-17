
#include <QApplication>
#include <QFileInfo>
#include <QProcess>
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
    QProcess process;
    process.start("murmurd", QStringList() << "-ini" << QFileInfo("mumble-server.ini").absoluteFilePath());
}

int main(int argc, char** argv) {

#ifdef VOIP
    QAppMumble a(argc, argv);
	a.setApplicationName(QLatin1String("Phonion"));
	a.setOrganizationName(QLatin1String("Phonion"));
	a.setOrganizationDomain(QLatin1String("phonion.phonion.co"));

    setupMumble(a, argc, argv);
    qDebug() << "Mumble initialization complete.";
    VoipClient voip;
#else
    QGuiApplication a(argc, argv);
#endif

    //initializeMumbleServer();
    AppLauncher applauncher;
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
    v.rootContext()->setContextProperty("voipclient", &voip);
#endif
    v.setSource(QUrl("qrc:/qml/main.qml"));
    v.show();

    return a.exec();
}

