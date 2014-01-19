
#include <QApplication>
#include <QObject>

class QAppPhonion: public QApplication {
    Q_OBJECT
public:
    QAppPhonion(int &argc, char **argv)
      : QApplication(argc, argv) {

	    setApplicationName(QLatin1String("Phonion"));
	    setOrganizationName(QLatin1String("Phonion"));
	    setOrganizationDomain(QLatin1String("phonion.phonion.co"));
    }

    ~QAppPhonion() {}

    Q_INVOKABLE const QString prettyOnion();
    Q_INVOKABLE const QString launch(int index);

public slots:
    void setOnion(const QString& onion) { _onion = onion; }

private:
    QString _onion;
};
