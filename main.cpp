
#include <QGuiApplication>
#include <QQuickView>
#include <QQmlContext>
#include <QUrl>

#include "applauncher.h"

int main(int argc, char** argv) {

    QGuiApplication a(argc, argv);

    AppLauncher applauncher;

    QQuickView v;
    v.setResizeMode(QQuickView::SizeRootObjectToView);
    v.rootContext()->setContextProperty("AppLauncher", &applauncher);
    v.setSource(QUrl("qrc:/qml/main.qml"));
    v.showFullScreen();

    return a.exec();
}

