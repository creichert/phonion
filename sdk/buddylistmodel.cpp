
#include <QAbstractListModel>
#include <QByteArray>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QFileSystemWatcher>
#include <QHash>
#include <QList>
#include <QModelIndex>
#include <QString>
#include <QStringList>
#include <QVariant>

#include "buddy.h"
#include "buddylistmodel.h"

BuddyListModel::BuddyListModel(QObject* parent)
  : QAbstractListModel(parent)
{
    QString blfile = QDir::currentPath() + "/apps/message/torchat/torchat/src/buddy-list.txt";
    QFileSystemWatcher* watcher = new QFileSystemWatcher(this);
    watcher->addPath(blfile);
    connect(watcher, SIGNAL(fileChanged(const QString&)), SLOT(onBuddyListChanged(const QString&)));
    onBuddyListChanged(blfile);
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

void BuddyListModel::onBuddyListChanged(const QString& path)
{
    QFile inputFile(path);
    if (inputFile.open(QIODevice::ReadOnly)) {

        // Completely re-build the buddy list.
        beginRemoveRows(QModelIndex(), 0, rowCount());
        _buddies.clear();
        endRemoveRows();

        QTextStream in(&inputFile);
        while (!in.atEnd()) {
            QString line = in.readLine();
            QString address = line.split(' ').at(0);
            QString name;
            if (line.length() > 0)
                name = line.split(' ').at(1);

            // Test if buddy is already in the list
            if(!buddyFromAddress(address))
                addBuddy(new Buddy(address, name, this));
        }
        inputFile.close();
    } else
        qDebug() << inputFile.errorString();
}

Buddy* BuddyListModel::buddyFromAddress(const QString& address)
{
    foreach(Buddy* buddy, _buddies) {
        if (buddy->onion() == address)
            return buddy;
    }
    return 0;
}
