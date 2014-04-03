
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
#include "incubationcontroller.h"
#include "phonion.h"
#include "notifier.h"

#define PROXY_HOST "127.0.0.1"
#define PROXY_PORT 11109

Phonion::Phonion(int &argc, char **argv)
  : QApplication(argc, argv)
  , _notifier(new Notifier(this))
  , _view(new QQuickView(this->modalWindow()))
  , _appModel(new AppModel(this))
{
    setApplicationName(QLatin1String("Phonion"));
    setOrganizationName(QLatin1String("Phonion"));
    setOrganizationDomain(QLatin1String("phonion.phonion.co"));

    qmlRegisterType<Notifier>("Phonion", 1, 0, "Notifier");
    qmlRegisterType<AppModel>("Phonion", 1, 0, "AppModel");

    QNetworkProxy proxy;
    proxy.setType(QNetworkProxy::Socks5Proxy);
    proxy.setHostName(PROXY_HOST);
    proxy.setPort(PROXY_PORT);
    //proxy.setUser("");
    //proxy.setPassword("");
    QNetworkProxy::setApplicationProxy(proxy);

    /* Use QFileInfo and also check against security key. */
    QFile f("./apps/message/torchat/torchat/src/Tor/hidden_service/hostname");
    if(!f.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning("Hidden service not found");
    } else {
        _onion = f.read(16);
        qDebug() << "Identified hidden service: " << _onion;
    }

    // set the engines qqmlnetworkaccessmanager here. pass in our phonionnetworkproxy.
    // and return it when create() is called.

    _view->engine()->setIncubationController(new PhonionIncubationController(_view->engine()));
    /* Phonion is the context of the root object. */
    _view->rootContext()->setContextObject(this);
    _view->rootContext()->setContextProperty("Phonion", this);
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
    _currentAppItem.clear();
}

void Phonion::launch(int index)
{
    App* app = _appModel->app(index);

    QQmlContext* context = app->context();
    if (!context) {
        context = new QQmlContext(_view->engine(), app);
    }

    app->launch(context, onion(), _notifier);

    /* Get the area which contains the app. */
    QObject* apparea = _view->rootObject()->findChild<QObject*>("apparea");

    /* Use an AppIncubator to prepare component to be injected into apparea.
     *
     * A new component is created each time the app is launched but the
     * context for the app is persistent.
     */
    AppIncubator incubator(qobject_cast<QQuickItem*>(apparea));

    QQmlComponent component(_view->engine(), QUrl(app->source()));
    component.create(incubator, context);

    _currentAppItem = QSharedPointer<QQuickItem>(qobject_cast<QQuickItem*>(incubator.object()));
}

void Phonion::loadApps()
{
    QDir appdir("./apps");
    QStringList apps = QDir("./apps").entryList(QStringList() << "*.so", QDir:: Files | QDir::NoSymLinks);
    foreach(const QString& appname, apps) {
        QPluginLoader loader(appdir.absoluteFilePath(appname));
        QObject* plugin = loader.instance();
        if (plugin) {
            App* app = qobject_cast<App*>(plugin);
            if (app) {
                _appModel->addApp(app);
            }
        }
    }
}
