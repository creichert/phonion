
#include <QAbstractListModel>
#include <QList>
#include <QVariant>
#include <QHash>
#include <QByteArray>
#include <QModelIndex>

#include "buddylistmodel.h"
#include "buddy.h"

BuddyListModel::BuddyListModel(const QList<Buddy*>& buddies, QObject* parent)
  : QAbstractListModel(parent)
  , _buddies(buddies)
{
}

QVariant BuddyListModel::data(const QModelIndex& index, int role) const
{
    if (role == NameRole)
        return _buddies.at(index.row())->onion();
    else if (role == DisplayNameRole)
        return _buddies.at(index.row())->displayName();
    else if (role == StatusRole)
        return QVariant(_buddies.at(index.row())->status());

    return QVariant();
}

QHash<int, QByteArray> BuddyListModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[DisplayNameRole] = "displayName";
    roles[StatusRole] = "status";
    return roles;
}

int BuddyListModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)
    return _buddies.size();
}

void BuddyListModel::addBuddy(Buddy* buddy)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());

    _buddies.append(buddy);

    endInsertRows();
}

QList<Buddy*> BuddyListModel::buddies()
{
    return _buddies;
}

void BuddyListModel::updateStatus(const QString& buddy, Buddy::Status status)
{
    QModelIndex idx;
    for (int i = 0; i < _buddies.size(); ++i) {
        if (_buddies.at(i)->onion() == buddy) {
            idx = index(i);
            _buddies.at(i)->setStatus(status);
        }
    }
    emit dataChanged(idx, idx);
}
