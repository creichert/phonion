#ifndef MESSAGEAPP_H
#define MESSAGEAPP_H

#include <boost/python.hpp>

#include <QObject>

#include "app.h"

class BuddyListModel;
class ChatModel;
class Notifier;
class QQmlContext;
class QString;

class MessageApp : public App
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "co.phonion.Phonion.AppInterface" FILE "messageapp.json")
public:

    ~MessageApp();

    virtual void startApp(QQmlContext* context, const QString& onion, Notifier* notifier);
    virtual QString id();
    virtual QString name();
    virtual QString icon();
    virtual QString source();

    BuddyListModel* buddyListModel();
    ChatModel* chatModel();

    Q_INVOKABLE void addBuddy(const QString& buddy);
    Q_INVOKABLE void sendChatMessage(const QString& msg);

private slots:
    void updateInterpreter();
    void onChatMessage(const QString& buddy, const QString& msg);
    void onStatusChanged(const QString& buddy);

private:
    std::string parse_python_exception();
    boost::python::object _buddyList;

    ChatModel* _chatModel;
    BuddyListModel* _buddyListModel;
};

#endif // MESSAGEAPP_H
