#ifndef VOIPCLIENT_H
#define VOIPCLIENT_H

#include <QAbstractSocket>
#include <QObject>
#include <QProcess>

class ServerHandler;

class VoipClient : public QObject
{
    Q_OBJECT
public:
    explicit VoipClient(const QString& onion = QString(), QObject* parent = 0);

    Q_INVOKABLE void call(const QString& onion);
    Q_INVOKABLE void end();
    Q_INVOKABLE QString latency();

private slots:
    void onServerConnected();
    void onServerDisconnected(QAbstractSocket::SocketError, QString reason);
    void onMurmurError(QProcess::ProcessError err);

private:
    ServerHandler* _serverHandler;
    QString _myonion;
};

#endif // VOIPCLIENT_H
