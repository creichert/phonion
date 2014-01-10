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

    Q_INVOKABLE void call(const QString& onion);
    Q_INVOKABLE void end();

private slots:
    void serverConnected();
    void serverDisconnected(QAbstractSocket::SocketError, QString reason);

private:
    ServerHandler* _serverHandler;
};

#endif // VOIPCLIENT_H
