#ifndef NOTIFIER_H
#define NOTIFIER_H

#include <QObject>

class Message;

class Notifier : public QObject {
    Q_OBJECT
public:
    explicit Notifier(QObject* parent=0);

signals:
    void messageNotification(const QString& msg);
};

#endif // NOTIFIER_H
