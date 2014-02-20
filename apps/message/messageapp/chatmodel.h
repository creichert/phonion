#ifndef CHATMODEL_H
#define CHATMODEL_H

#include <QAbstractListModel>
#include <QHash>
#include <QList>
#include <QObject>

class QByteArray;
class Message;

class ChatModel : public QAbstractListModel
{
    Q_OBJECT
public:

    enum ChatRoles {
      MsgRole = Qt::UserRole + 1
    , FromMeRole
    };

    ChatModel(QObject* parent = 0);

    void newMessage(Message* msg);

    Q_INVOKABLE void setCurrentBuddy(const QString& buddy);
    Q_INVOKABLE QString currentBuddy();

    virtual QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
    virtual QHash<int, QByteArray> roleNames() const;
    virtual int rowCount (const QModelIndex& parent = QModelIndex()) const;

signals:
    void message(Message*);

private:
    // TODO: Don't hold all chats in memory all the time.
    QHash<QString, QList<Message*> > _chats;
    QString _currentBuddy;
};

#endif // CHATMODEL_H
