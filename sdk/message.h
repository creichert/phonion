#ifndef MESSAGE_H
#define MESSAGE_H

#include <QObject>
#include <QString>

class Message : public QObject {
    Q_OBJECT
public:
    explicit Message(const QString& buddy, const QString& text, bool fromme=false, QObject* parent=0);

    Q_INVOKABLE QString text() { return _text; }
    Q_INVOKABLE QString buddy() { return _buddy; }
    Q_INVOKABLE bool fromme() { return _fromme; }

private:
    QString _buddy;
    QString _text;
    bool _fromme;
};

#endif // MESSAGE_H
