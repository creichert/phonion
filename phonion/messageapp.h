
#include <QObject>

#include <boost/python.hpp>

class QString;

class MessageApp : public QObject
{
    Q_OBJECT
public:
    MessageApp();
    ~MessageApp();

    Q_INVOKABLE void sendMessage(const QString& msg);

private:
    std::string parse_python_exception();

    boost::python::object _buddyList;
};
