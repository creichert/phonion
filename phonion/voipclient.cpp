
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
        //g.mw->on_qaServerDisconnect_triggered();
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
    //g.mw->connect(sh.get(), SIGNAL(connected()), g.mw, SLOT(serverConnected()));
    //g.mw->connect(sh.get(), SIGNAL(disconnected(QAbstractSocket::SocketError, QString)), g.mw, SLOT(serverDisconnected(QAbstractSocket::SocketError, QString)));
}

VoipClient::VoipClient(QObject* parent)
  : QObject(parent)
  , _serverHandler()
{
}

void VoipClient::call(const QString& onion)
{
    qDebug() << "Placing call to onion: " << onion;
    recreateServerHandler();
    _serverHandler = g.sh.get();
    connect(_serverHandler, SIGNAL(connected()), SLOT(serverConnected()));
    connect(_serverHandler, SIGNAL(disconnected(QAbstractSocket::SocketError, QString)),
            SLOT(serverDisconnected(QAbstractSocket::SocketError, QString)));

    const QString host = "ro2jdbdfhj57b5cj.onion";
    const short unsigned int port = 64738;
    const QString user = "phonion___"; // AppLauncher.onion (nick)
    const QString pass = "phonion";

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

