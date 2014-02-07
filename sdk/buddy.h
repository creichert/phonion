#ifndef BUDDY_H
#define BUDDY_H

#include <QObject>
#include <QString>

class Buddy : public QObject
{
    Q_OBJECT
public:
    enum Status {
      STATUS_OFFLINE = 0
    , STATUS_HANDSHAKE
    , STATUS_ONLINE
    , STATUS_AWAY
    , STATUS_XA
    };

    explicit Buddy(const QString& onion, const QString& displayName = QString(), QObject* parent = 0);

    QString onion() { return _onion; }
    QString displayName() { return _displayName; }
    Status status() { return _status; }
    void setStatus(Status status) { _status = status; }

private:
    QString _onion;
    QString _displayName;
    Status _status;
};

#endif // BUDDY_H
