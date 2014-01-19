
#include <QByteArray>
#include <QHash>
#include <QModelIndex>
#include <QVariant>

#include <QDebug>

#include "chatmodel.h"
#include "message.h"

void ChatModel::newMessage(Message* msg)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());

    qDebug() << "chat message:" << msg->buddy() << ": " << msg->text();

    if (!_chats.keys().contains(msg->buddy()))
        _chats[msg->buddy()] = QList<Message*>();

    _chats[msg->buddy()].append(msg);

    endInsertRows();
}

void ChatModel::setCurrentBuddy(const QString& buddy)
{
    if (!_chats.keys().contains(buddy))
        _chats[buddy] = QList<Message*>();
    _currentBuddy = buddy;
}

QString ChatModel::currentBuddy()
{
    return _currentBuddy;
}

QVariant ChatModel::data(const QModelIndex& index, int role) const
{
    if (role == MsgRole)
        return QVariant::fromValue((_chats[_currentBuddy].at(index.row())));

    return QVariant();
}

QHash<int, QByteArray> ChatModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[MsgRole] = "msg";
    return roles;
}

int ChatModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)
    if (_chats.empty())
        return 0;
    return _chats[_currentBuddy].size();
}
