
#include <QObject>
#include <QAbstractSocket>
#include <QDebug>
#include <QThread>

#include "ServerHandler.h"
#include "Global.h"
#include "Log.h"

#include "voipclient.h"

static void recreateServerHandler() {
    /**
     * g is a global data structure created in Mumble libs.
     */
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

    // ServerHandlerPtr is QSharedPointer.
    sh = ServerHandlerPtr(new ServerHandler());
    sh->moveToThread(sh.get());
    g.sh = sh;
}

VoipClient::VoipClient(const QString& onion, QObject* parent)
  : QObject(parent)
  , _serverHandler()
  , _myonion(onion)
{
    qDebug() << Q_FUNC_INFO << "Registering VOIP Client As User: " << _myonion;
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
    const QString user =  _myonion;
    const QString pass = "phonion";

    qDebug() << Q_FUNC_INFO << "Placing call to " << host;
    _serverHandler->setConnectionInfo(host, port, user, pass);
    _serverHandler->start();
}

void VoipClient::end()
{
    _serverHandler->disconnect();
}

QString VoipClient::latency()
{
	return QString::fromLatin1("%1").arg(sqrt(boost::accumulators::variance(_serverHandler->accTCP)),0,'f',2);
}

void VoipClient::serverConnected()
{
    qDebug() << Q_FUNC_INFO << "Server Connected " << _serverHandler;
}

void VoipClient::serverDisconnected(QAbstractSocket::SocketError err, QString reason)
{
    qDebug() << Q_FUNC_INFO << "Server disconnected: " << err << " : " << reason;
}
