#ifndef BUDDYLISTMODEL_H
#define BUDDYLISTMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include <QList>

class Buddy;

class BuddyListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum BuddyListRoles {
        NameRole = Qt::UserRole + 1,
        StatusRole
    };

    BuddyListModel(const QList<Buddy*>& buddies, QObject* parent=0);

    void addBuddy(Buddy* buddy);
    QList<Buddy*> buddies();

    virtual QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
    virtual QHash<int, QByteArray> roleNames() const;
    virtual int rowCount (const QModelIndex& parent = QModelIndex()) const;

private:
    QList<Buddy*> _buddies;
};

#endif // BUDDYLISTMODEL_H
