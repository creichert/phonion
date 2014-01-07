#ifndef VOIPCLIENT_H
#define VOIPCLIENT_H

#include <QObject>
#include <QAbstractSocket>

class ServerHandler;

class VoipClient : public QObject
{
    Q_OBJECT
public:
    VoipClient(QObject* parent = 0);

private slots:
    void serverConnected();
    void serverDisconnected(QAbstractSocket::SocketError, QString reason);
private:
    ServerHandler* _serverHandler;
};

#endif // VOIPCLIENT_H
