
#include <boost/python.hpp>

#include <QObject>
#include <QDebug>
#include <QString>

using namespace boost::python;

class Integrator : public QObject
{
  Q_OBJECT

public:
    void callback(int type, PyObject* data);

signals:
    void onChatMessage(const QString&, const QString& msg);
};
