
#include <QDebug>
#include <QVariant>
#include <QHash>
#include <QByteArray>
#include <QModelIndex>

#include "buddylistmodel.h"

QVariant BuddyListModel::data(const QModelIndex& index, int role) const
{
    if (role == NameRole)
        return stringList()[index.row()];

    return QVariant();
}

QHash<int, QByteArray> BuddyListModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[StatusRole] = "status";
    return roles;
}
