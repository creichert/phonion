
#include <QApplication>
#include <QQuickView>
#include <QQmlContext>
#include <QUrl>

#include "applauncher.h"
#include "buddylistmodel.h"
#include "chatmodel.h"
#include "messageapp.h"
#include "voipclient.h"

#include "SetupMumble.h"

int main(int argc, char** argv) {

#ifdef VOIP
    QAppMumble a(argc, argv);
    setupMumble(a, argc, argv);
    qDebug() << "Mumble initialization complete.";
    VoipClient voip;
#else
    QGuiApplication a(argc, argv);
#endif

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
    v.showFullScreen();

    return a.exec();
}

