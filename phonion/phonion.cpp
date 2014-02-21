
#include <QApplication>
#include <QDebug>
#include <QDirIterator>
#include <QFileInfo>
#include <QList>
#include <QNetworkProxy>
#include <QPluginLoader>
#include <QQmlContext>
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
{
    setApplicationName(QLatin1String("Phonion"));
    setOrganizationName(QLatin1String("Phonion"));
    setOrganizationDomain(QLatin1String("phonion.phonion.co"));

    _view->setResizeMode(QQuickView::SizeRootObjectToView);

    /* Use QFileInfo and also check against security key. */
    QFile f("./apps/message/torchat/torchat/src/Tor/hidden_service/hostname");
    if(!f.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning("Hidden service not found");
    } else {
        _onion = f.read(16);
        qDebug() << "Identified hidden service: " << _onion;
    }

    /* TODO: Phonion should use rootContext. */
    context()->setContextProperty("app", this);
    context()->setContextProperty("notifier", _notifier);
    context()->setContextProperty("appmodel", _appModel);

    _view->setSource(QUrl("qrc:/qml/Main.qml"));
    _view->show();

    /* TODO: The home screen grid view should read the
     *       info about each app in it;s corresponding
     *       JSON file. The app (plugin) should not be
     *       instantiated until use clicks launch.
     */
    loadApps();
}

QQmlContext* Phonion::context()
{
    return _view->rootContext();
}

const QString Phonion::onion()
{
    return _onion;
}

const QString Phonion::launch(int index)
{
    /* TODO: Callback to current app which
     *       puts all non-critical jobs in
     *       the background.
     *
     *       currentApp->pause();
     */

    App* app = _appModel->app(index);

    /* TODO: Only pass QQmlContext. */
    app->launch(_view->rootContext(), onion(), _notifier);

    /* TODO: Don't use root context. Create a new context per app. */
    _view->rootContext()->setContextObject(app);

    /* TODO: (Fix) This has to be called after the Phone (or
     *        any app that uses a QSocket).
     *
     *        Ideally, our infrastructure is fully worked around
     *        a SOCKS5 Proxy for every future QSocket.
     *
     *        Utilitze QNetworkAccessManager to build a network
     *        access layer.
     */
    QNetworkProxy proxy;
    proxy.setType(QNetworkProxy::Socks5Proxy);
    proxy.setHostName(PROXY_HOST);
    proxy.setPort(PROXY_PORT);
    QNetworkProxy::setApplicationProxy(proxy);

    return app->source();
}

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
            if (app)
                _appModel->addApp(app);
        }
    }
}
