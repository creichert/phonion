
#include <QStringListModel>

class BuddyListModel : public QStringListModel
{
    Q_OBJECT
public:
    enum BuddyListRoles {
        NameRole = Qt::UserRole + 1,
        StatusRole
    };

    virtual QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
    virtual QHash<int, QByteArray> roleNames() const;
    //virtual int rowCount (const QModelIndex& parent = QModelIndex()) const;
};
