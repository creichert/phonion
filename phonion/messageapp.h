#ifndef MESSAGEAPP_H
#define MESSAGEAPP_H

#include <QObject>
#include <QThread>

#include <boost/python.hpp>

class BuddyListModel;
class ChatModel;
class QString;

class MessageApp : public QObject
{
    Q_OBJECT
public:
    MessageApp(QObject* parent = 0);
    ~MessageApp();

    BuddyListModel* buddyListModel();
    ChatModel* chatModel();

    Q_INVOKABLE void addBuddy(const QString& buddy);
    Q_INVOKABLE void sendChatMessage(const QString& msg);

private slots:
    void updateInterpreter();
    void onChatMessage(const QString& buddy, const QString& msg);

private:
    std::string parse_python_exception();

    boost::python::object _buddyList;

    ChatModel* _chatModel;
    BuddyListModel* _buddyListModel;
};

#endif // MESSAGEAPP_H
