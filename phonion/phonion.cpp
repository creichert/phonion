
#include <QApplication>
#include <QDebug>
#include <QDirIterator>
#include <QFileInfo>
#include <QList>
#include <QNetworkProxy>
#include <QPluginLoader>
#include <QQmlContext>
#include <QQmlEngine>
#include <QQmlProperty>
#include <QQuickItem>
#include <QQuickView>
#include <QString>
#include <QUrl>
#include <QWindow>

#include "app.h"
#include "appmodel.h"
#include "phonion.h"
#include "notifier.h"

#define PROXY_HOST "127.0.0.1"
#define PROXY_PORT 11109

Phonion::Phonion(int &argc, char **argv)
  : QApplication(argc, argv)
  , _notifier(new Notifier(this))
  , _view(new QQuickView(this->modalWindow()))
  , _appModel(new AppModel(this))
  , _currentAppItem(0)
{
    setApplicationName(QLatin1String("Phonion"));
    setOrganizationName(QLatin1String("Phonion"));
    setOrganizationDomain(QLatin1String("phonion.phonion.co"));

    qmlRegisterType<Notifier>("Phonion", 1, 0, "Notifier");
    qmlRegisterType<AppModel>("Phonion", 1, 0, "AppModel");

    /* Use QFileInfo and also check against security key. */
    QFile f("./apps/message/torchat/torchat/src/Tor/hidden_service/hostname");
    if(!f.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning("Hidden service not found");
    } else {
        _onion = f.read(16);
        qDebug() << "Identified hidden service: " << _onion;
    }

    _view->rootContext()->setContextObject(this);
    _view->rootContext()->setContextProperty("phonion", this);
    _view->setResizeMode(QQuickView::SizeRootObjectToView);
    _view->setSource(QUrl("qrc:/qml/Main.qml"));
    _view->show();

    /* TODO: The home screen grid view should read the
     *       info about each app in it's corresponding
     *       JSON file. The app (plugin) should not be
     *       instantiated until use clicks launch.
     */
    loadApps();
}

Notifier* Phonion::notifier()
{
    return _notifier;
}

AppModel* Phonion::appModel()
{
    return _appModel;
}

const QString Phonion::onion()
{
    return _onion;
}

void Phonion::home()
{
    _currentAppItem->setParentItem(0);
    _currentAppItem->deleteLater();
}

void Phonion::launch(int index)
{
    App* app = _appModel->app(index);

    QQmlContext* context = app->context();
    if (!context) {
        context = new QQmlContext(_view->engine(), app);
    }

    app->launch(context, onion(), _notifier);

    /* TODO: (Fix) This has to be called after the Phone (or
     *        any app that uses a QSocket).
     *
     *        Utilitze QNetworkAccessManager to build a network
     *        access layer.
     */
    QNetworkProxy proxy;
    proxy.setType(QNetworkProxy::Socks5Proxy);
    proxy.setHostName(PROXY_HOST);
    proxy.setPort(PROXY_PORT);
    QNetworkProxy::setApplicationProxy(proxy);

    /* Inject component for app into object tree.
     *
     * A new component is created each time the app is launched but the
     * context for the app is persistent.
     */
    QQmlComponent* component = new QQmlComponent(_view->engine(), QUrl(app->source()));

    QObject* root = _view->rootObject();
    QObject* apparea = root->findChild<QObject*>("apparea");

    _currentAppItem = qobject_cast<QQuickItem*>(component->create(context));
    _currentAppItem->setParentItem(qobject_cast<QQuickItem*>(apparea));
    QQmlProperty(_currentAppItem, "anchors.fill").write(QVariant::fromValue(apparea));
}

/* TODO: Move to the app model.
 */
void Phonion::loadApps()
{
    /* TODO: Clean this up once we are copying
     *       all apps to a proper plugins or apps dir.
     */
    QDirIterator it("./apps", QDir::Files | QDir::NoSymLinks, QDirIterator::Subdirectories);
    while (it.hasNext()) {
        QPluginLoader loader(it.next());
        QObject* plugin = loader.instance();
        if (plugin) {
            App* app = qobject_cast<App*>(plugin);
            if (app) {
                _appModel->addApp(app);
            }
        }
    }
}
