
#include <QByteArray>
#include <QHash>
#include <QModelIndex>
#include <QVariant>

#include <QDebug>

#include "chatmodel.h"
#include "message.h"

ChatModel::ChatModel(QObject* parent)
  : QAbstractListModel(parent)
{
}

void ChatModel::newMessage(Message* msg)
{
    beginInsertRows(QModelIndex(), 0, 0);

    qDebug() << "chat message:" << msg->buddy() << ": " << msg->text();

    if (!_chats.keys().contains(msg->buddy()))
        _chats[msg->buddy()] = QList<Message*>();

    /**
     * First item in the list is the most recent.
     *
     * Using QList allows for the quickest insertion at the beginning.  We
     * should be caching outdated messages and only showing the most recent
     * messages here anyways so there should not be a performance bottleneck
     * even with a sizeable backlog. If the user chooses to view more of the
     * chat history we can then use a database model to handle a larger message
     * set.
     */
    _chats[msg->buddy()].prepend(msg);

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
        return QVariant::fromValue(_chats[_currentBuddy].at(index.row())->text());
    else if (role == FromMeRole) {
        return QVariant::fromValue(_chats[_currentBuddy].at(index.row())->fromme());
    }

    return QVariant();
}

QHash<int, QByteArray> ChatModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[MsgRole] = "msg";
    roles[FromMeRole] = "fromme";
    return roles;
}

int ChatModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)
    if (_chats.empty())
        return 0;
    return _chats[_currentBuddy].size();
}
