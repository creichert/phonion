#ifndef NOTIFIER_H
#define NOTIFIER_H

#include <QObject>

#include "message.h"

class Notifier : public QObject {
    Q_OBJECT
public:
    explicit Notifier(QObject* parent=0);

signals:
    void messageNotification(Message* msg);
};

#endif // NOTIFIER_H
