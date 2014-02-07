#ifndef BUDDYLISTMODEL_H
#define BUDDYLISTMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include <QList>

#include "buddy.h"

class BuddyListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum BuddyListRoles {
      NameRole = Qt::UserRole + 1
    , DisplayNameRole
    , StatusRole
    };

    BuddyListModel(const QList<Buddy*>& buddies, QObject* parent=0);

    void addBuddy(Buddy* buddy);
    QList<Buddy*> buddies();

    void updateStatus(const QString& buddy, Buddy::Status status);

    virtual QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
    virtual QHash<int, QByteArray> roleNames() const;
    virtual int rowCount (const QModelIndex& parent = QModelIndex()) const;

private:
    QList<Buddy*> _buddies;
};

#endif // BUDDYLISTMODEL_H
