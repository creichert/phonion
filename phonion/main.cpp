
#include <QGuiApplication>
#include <QQuickView>
#include <QQmlContext>
#include <QUrl>

#include "applauncher.h"
#include "chatmodel.h"
#include "messageapp.h"


int main(int argc, char** argv) {

    QGuiApplication a(argc, argv);

    AppLauncher applauncher;
    MessageApp msgApp;
   
    QQuickView v;
    v.setResizeMode(QQuickView::SizeRootObjectToView);
    v.rootContext()->setContextProperty("AppLauncher", &applauncher);
    v.rootContext()->setContextProperty("MessageApp", &msgApp);
    v.rootContext()->setContextProperty("messagemodel", msgApp.chatModel());
    v.setSource(QUrl("qrc:/qml/main.qml"));
    v.showFullScreen();

    return a.exec();
}

