
#include <QApplication>
#include <QNetworkProxy>
#include <QObject>

#define PROXY_HOST "127.0.0.1"
#define PROXY_PORT 11109

class QAppPhonion: public QApplication {
    Q_OBJECT
public:
    QAppPhonion(int &argc, char **argv)
      : QApplication(argc, argv) {

	    setApplicationName(QLatin1String("Phonion"));
	    setOrganizationName(QLatin1String("Phonion"));
	    setOrganizationDomain(QLatin1String("phonion.phonion.co"));

        QNetworkProxy proxy;
        proxy.setType(QNetworkProxy::Socks5Proxy);
        proxy.setHostName(PROXY_HOST);
        proxy.setPort(PROXY_PORT);
        QNetworkProxy::setApplicationProxy(proxy);
    }

    ~QAppPhonion() {}

    Q_INVOKABLE const QString prettyOnion();
    Q_INVOKABLE const QString launch(int index);

public slots:
    void setOnion(const QString& onion) { _onion = onion; }

private:
    QString _onion;
};
