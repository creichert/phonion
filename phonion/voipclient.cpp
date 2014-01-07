
#include <QObject>
#include <QAbstractSocket>
#include <QDebug>
#include <QThread>

#include "ServerHandler.h"

#include "voipclient.h"

VoipClient::VoipClient(QObject* parent)
  : QObject(parent)
  , _serverHandler(new ServerHandler())
{
    connect(_serverHandler, SIGNAL(connected()), SLOT(serverConnected()));
    connect(_serverHandler, SIGNAL(disconnected(QAbstractSocket::SocketError, QString)),
            SLOT(serverDisconnected(QAbstractSocket::SocketError, QString)));

    const QString host = "127.0.0.1";
    const short unsigned int port = 61473;
    const QString user = "phonion"; // AppLauncher.onion (nick)
    const QString pass = "";
    _serverHandler->setConnectionInfo(host, port, user, pass);
}

void VoipClient::serverConnected()
{
    qDebug() << "Server Connected";
}

void VoipClient::serverDisconnected(QAbstractSocket::SocketError err, QString reason)
{
    qDebug() << "Server disconnected: " << err << " : " << reason;
}
