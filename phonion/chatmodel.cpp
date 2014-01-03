
#include <QByteArray>
#include <QHash>
#include <QModelIndex>
#include <QVariant>

#include <QDebug>

#include "chatmodel.h"

void ChatModel::newMessage(const QString& buddy, const QString& msg)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());

    qDebug() << " ON CHAT MESSAGE :" << buddy << ": " << msg;
    if (!_chats.keys().contains(buddy))
        _chats[buddy] = QStringList();
    _chats[buddy].append(msg);

    endInsertRows();
}

void ChatModel::setCurrentBuddy(const QString& buddy)
{
    if (!_chats.keys().contains(buddy))
        _chats[buddy] = QStringList();
    _currentBuddy = buddy;
}

QString ChatModel::currentBuddy()
{
    return _currentBuddy;
}

QVariant ChatModel::data(const QModelIndex& index, int role) const
{
    if (role == MsgRole)
        return QVariant(_chats[_currentBuddy].at(index.row()));

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
    if (_chats.empty())
        return 0;
    return _chats[_currentBuddy].size();
}
