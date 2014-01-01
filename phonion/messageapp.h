
#include <QObject>
#include <QThread>

#include <boost/python.hpp>

class QString;

class OnionChatThread;

class MessageApp : public QObject
{
    Q_OBJECT
public:
    MessageApp();
    ~MessageApp();

    Q_INVOKABLE void sendMessage(const QString& msg);

private:
    OnionChatThread* _t;
    std::string parse_python_exception();

    boost::python::object _buddyList;
};

class OnionChatThread : public QThread
{
    Q_OBJECT
public:
    OnionChatThread(MessageApp* app) {
        _app = app;
    }
private:
    MessageApp* _app;
    void run() {
        //_app->initialize();
    }
};


