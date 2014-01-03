
#include <QAbstractListModel>
#include <QHash>
#include <QStringList>

class QByteArray;

class ChatModel : public QAbstractListModel
{
    Q_OBJECT
public:

    enum ChatRoles {
        MsgRole = Qt::UserRole + 1
    };

    void newMessage(const QString& buddy, const QString& msg);

    void setCurrentBuddy(const QString& buddy);
    Q_INVOKABLE QString currentBuddy();

    virtual QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
    virtual QHash<int, QByteArray> roleNames() const;
    virtual int rowCount (const QModelIndex& parent = QModelIndex()) const;

private:
    // Don't hold all chats in memory all the time.
    QHash<QString, QStringList> _chats;
    QString _currentBuddy;
};
