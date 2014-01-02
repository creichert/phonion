
#include <QObject>
#include <QThread>

#include <boost/python.hpp>

class QString;

class MessageApp : public QObject
{
    Q_OBJECT
public:
    MessageApp();
    ~MessageApp();

    Q_INVOKABLE void sendChatMessage(const QString& msg);

private slots:
    void updateInterpreter();
    void onChatMessage(const QString& msg);

private:
    std::string parse_python_exception();

    boost::python::object _buddyList;
};
