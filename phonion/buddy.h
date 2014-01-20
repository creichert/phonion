#ifndef BUDDY_H
#define BUDDY_H

#include <QObject>
#include <QString>

class Buddy : public QObject
{
    Q_OBJECT
public:
    explicit Buddy(const QString& onion, const QString& displayName = QString(), QObject* parent = 0);

    QString onion() { return _onion; }
    QString displayName() { return _displayName; }

private:
    QString _onion;
    QString _displayName;
};

#endif // BUDDY_H
