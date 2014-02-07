
#include <QAbstractListModel>
#include <QIcon>
#include <QList>
#include <QVariant>
#include <QHash>
#include <QByteArray>

#include "appmodel.h"
#include "app.h"

AppModel::AppModel(QObject* parent)
  : QAbstractListModel(parent)
{
}

void AppModel::addApp(App* app)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());

    _apps.append(app);

    endInsertRows();
}

App* AppModel::app(int index)
{
    return _apps.at(index);
}

QVariant AppModel::data(const QModelIndex& index, int role) const
{
    if (role == NameRole)
        return _apps.at(index.row())->name();
    else if (role == IconRole)
        return _apps.at(index.row())->icon();

    return QVariant();
}

QHash<int, QByteArray> AppModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[IconRole] = "icon";
    return roles;
}

int AppModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)
    return _apps.size();
}
