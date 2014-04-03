#ifndef NOTIFICATION_H
#define NOTIFICATION_H

#include <QObject>

class Notification : public QObject {
    Q_OBJECT
public:
    explicit Notification(QObject* parent=0);
};

#endif // NOTIFICATION_H
