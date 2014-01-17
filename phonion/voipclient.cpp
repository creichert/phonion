
#include <QObject>
#include <QAbstractSocket>
#include <QDebug>
#include <QThread>

#include "ServerHandler.h"
#include "Global.h"
#include "Log.h"

#include "voipclient.h"

static void recreateServerHandler() {
    ServerHandlerPtr sh = g.sh;
    if (sh && sh->isRunning()) {
        sh->disconnect();
        sh->wait();
        QCoreApplication::instance()->processEvents();
    }

    g.sh.reset();
    while (sh && ! sh.unique())
        QThread::yieldCurrentThread();
    sh.reset();

    sh = ServerHandlerPtr(new ServerHandler());
    sh->moveToThread(sh.get());
    g.sh = sh;
}

VoipClient::VoipClient(QObject* parent)
  : QObject(parent)
  , _serverHandler()
{
    QFile f("./phonion/torchat/src/Tor/hidden_service/hostname");
    if(!f.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning("Hidden service not found");
        return;
    }

    _myonion = f.read(16);
    qDebug() << "Registering as user: " << _myonion;
}

void VoipClient::call(const QString& onion)
{
    recreateServerHandler();
    _serverHandler = g.sh.get();
    connect(_serverHandler, SIGNAL(connected()), SLOT(serverConnected()));
    connect(_serverHandler, SIGNAL(disconnected(QAbstractSocket::SocketError, QString)),
            SLOT(serverDisconnected(QAbstractSocket::SocketError, QString)));

    const QString host = onion + ".onion";
    const short unsigned int port = 64738;
    const QString user =  _myonion; // AppLauncher.onion (nick)
    const QString pass = "phonion";

    qDebug() << "Placing call to " << host;
    _serverHandler->setConnectionInfo(host, port, user, pass);
    _serverHandler->start();

}

void VoipClient::end()
{
    _serverHandler->disconnect();
}

void VoipClient::serverConnected()
{
    qDebug() << "Server Connected";
}

void VoipClient::serverDisconnected(QAbstractSocket::SocketError err, QString reason)
{
    qDebug() << "Server disconnected: " << err << " : " << reason;
}

