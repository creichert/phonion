#ifndef VOIPCLIENT_H
#define VOIPCLIENT_H

#include <QObject>
#include <QAbstractSocket>

class ServerHandler;

class VoipClient : public QObject
{
    Q_OBJECT
public:
    explicit VoipClient(const QString& onion, QObject* parent = 0);

    Q_INVOKABLE void call(const QString& onion);
    Q_INVOKABLE void end();
    Q_INVOKABLE QString latency();

private slots:
    void serverConnected();
    void serverDisconnected(QAbstractSocket::SocketError, QString reason);

private:
    ServerHandler* _serverHandler;
    QString _myonion;
};

#endif // VOIPCLIENT_H
