
#include <QFileInfo>
#include <QProcess>
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

void initializeMumbleServer() {
    //QProcess* process = new QProcess;
    //process->start("murmurd", QStringList() << "-ini" << QFileInfo("mumble-server.ini").absoluteFilePath());
    //qDebug() << "Murmurd Exit Code: " << process->exitCode();
}

const QString hiddenServiceAddress() {

    QString onion;

    // Use QFileInfo and also check against security key.
    QFile f("./phonion/torchat/torchat/src/Tor/hidden_service/hostname");
    if(!f.open(QIODevice::ReadOnly)) {
        qWarning("Hidden service not found");
        return onion;
    }

    onion = f.read(16);
    qDebug() << "Identified hidden service: " << onion;
    return onion;
}

int main(int argc, char** argv) {

    QAppPhonion a(argc, argv);

#ifdef VOIP
    setupMumble(a, argc, argv);
    initializeMumbleServer();
    qDebug() << "Mumble initialization complete.";
#endif

    const QString onion = hiddenServiceAddress();
    a.setOnion(onion);

    MessageApp msgApp;

    QQuickView v;
    v.setResizeMode(QQuickView::SizeRootObjectToView);
    v.rootContext()->setContextProperty("app", &a);
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
