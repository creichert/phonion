#ifndef APPMODEL_H
#define APPMODEL_H

#include <QAbstractListModel>
#include <QList>
#include <QPointer>

#include "buddy.h"

class App;

class AppModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum AppRoles {
      NameRole = Qt::UserRole + 1
    , IconRole 
    };

    AppModel(QObject* parent=0);

    void addApp(App* app);
    App* app(int index);

    virtual QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
    virtual QHash<int, QByteArray> roleNames() const;
    virtual int rowCount (const QModelIndex& parent = QModelIndex()) const;

private:
    QList< QPointer<App> > _apps;
};

#endif // APPMODEL_H
