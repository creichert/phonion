#ifndef MESSAGEAPP_H
#define MESSAGEAPP_H

#include <boost/python.hpp>

#include <QObject>
#include <QtQml>

#include "app.h"
#include "buddylistmodel.h"
#include "chatmodel.h"

class Notifier;
class QQmlContext;
class QString;

class MessageApp : public App
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "co.phonion.Phonion.AppInterface" FILE "messageapp.json")
    Q_PROPERTY(ChatModel* messagemodel READ chatModel CONSTANT)
    Q_PROPERTY(BuddyListModel* buddylistmodel READ buddyListModel CONSTANT)
public:

    MessageApp(QObject* parent=0);
    ~MessageApp();

    virtual QString id();
    virtual QString name();
    virtual QString icon();
    virtual QString source();

    ChatModel* chatModel();
    BuddyListModel* buddyListModel();

    Q_INVOKABLE void addBuddy(const QString& buddy);
    Q_INVOKABLE void sendChatMessage(const QString& msg);

protected:
    virtual void start(QQmlContext* context, const QString& onion, Notifier* notifier);

private slots:
    void onUpdateInterpreter();
    void onChatMessage(const QString& buddy, const QString& msg);
    void onStatusChanged(const QString& buddy);

private:
    std::string parse_python_exception();
    boost::python::object _buddyList;

    ChatModel* _chatModel;
    BuddyListModel* _buddyListModel;
};

#endif // MESSAGEAPP_H
