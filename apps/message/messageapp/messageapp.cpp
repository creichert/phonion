
#include <boost/python.hpp>
#include <iostream>

#include <QDebug>
#include <QIcon>
#include <QQmlContext>
#include <QString>
#include <QTimer>

#include "app.h"
#include "buddy.h"
#include "buddylistmodel.h"
#include "chatmodel.h"
#include "integrator.h"
#include "message.h"
#include "messageapp.h"
#include "notifier.h"

using namespace std;
namespace py = boost::python;

MessageApp::MessageApp(QObject* parent)
    : App(parent)
    , _chatModel(0)
    , _buddyListModel(0)
{
    qmlRegisterType<ChatModel>("Phonion", 1, 0, "ChatModel");
}

MessageApp::~MessageApp()
{
    _buddyList.attr("stopClient");
}

// TODO: Find a way to parameterize the input here as it will almost certainly grow.
void MessageApp::start(QQmlContext* context, const QString& onion, Notifier* notifier)
{
    App::start(context, onion, notifier);

    _chatModel = new ChatModel(this);
    _buddyListModel = new BuddyListModel(this);

    Py_Initialize();
    try {

        py::object mm = py::import("__main__");
        py::object mn = mm.attr("__dict__");
        py::exec("import tc_client", mn);
        py::exec("import libintegrator", mn);
        py::exec("i = libintegrator.Integrator()", mn);
        //py::exec("socket = tc_client.tryBindPort(\"127.0.0.1\", 11009)", mn);
        _buddyList = py::eval("tc_client.BuddyList(i.callback)", mn);

        // (boost::python) Who manages the memory of Integrator now.
        Integrator* integrator = py::extract<Integrator*>(mn["i"]);
        connect(integrator, SIGNAL(onChatMessage(const QString&, const QString&)),
                              SLOT(onChatMessage(const QString&, const QString&)));
        connect(integrator, SIGNAL(statusChanged(const QString&)),
                              SLOT(onStatusChanged(const QString&)));

    } catch(py::error_already_set const &){
        string perror_str = parse_python_exception();
        cout << "Error during configuration parsing: " << perror_str << endl;
    }

    /* TODO: Remove this monstrosity when the Tor and BuddyList handling
     *       are decoupled from TorChat
     */
    context->setContextProperty("MessageApp", this);

    connect(_chatModel, SIGNAL(message(Message*)),
            notifier, SIGNAL(messageNotification(Message*)));

    // Needed to keep app up to date.
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(onUpdateInterpreter()));
    timer->start(1000);
}

QString MessageApp::id()
{
    return "MessageApp";
}

QString MessageApp::name()
{
    return "Message";
}

QString MessageApp::icon()
{
    return "qrc:/message/message.png";
}

QString MessageApp::source()
{
    return "qrc:/qml/Messages.qml";
}

ChatModel* MessageApp::chatModel()
{
    return _chatModel;
}

BuddyListModel* MessageApp::buddyListModel()
{
    return _buddyListModel;
}

void MessageApp::addBuddy(const QString& buddy)
{
    if (buddy.length() != 16) {
        qDebug() << "[ERROR]: Incorrectly formatted buddy address.";
        return;
    }

    try {
        py::extract<bool>(_buddyList.attr("addBuddy")(buddy.toStdString()));
    } catch(py::error_already_set const &){
        string perror_str = parse_python_exception();
        cout << Q_FUNC_INFO << perror_str << endl;
    }
}

void MessageApp::sendChatMessage(const QString& msg)
{
    if (msg.isEmpty())
        return;

    _chatModel->newMessage(new Message(_chatModel->currentBuddy(), msg, true, _chatModel));
    try {
        const char* bdy = _chatModel->currentBuddy().toStdString().c_str();
        py::object buddy = _buddyList.attr("getBuddyFromAddress")(bdy);
        buddy.attr("sendChatMessage")(msg.toStdString().c_str());
    } catch(py::error_already_set const &){
        string perror_str = parse_python_exception();
        cout << Q_FUNC_INFO << perror_str << endl;
    }
}

void MessageApp::onUpdateInterpreter()
{
    py::exec("print \"updating interpreter\"");
}

void MessageApp::onChatMessage(const QString& buddy, const QString& msg)
{
    _chatModel->newMessage(new Message(buddy, msg, false, _chatModel));
}

void MessageApp::onStatusChanged(const QString& newbuddy)
{
    Buddy::Status status = Buddy::STATUS_OFFLINE;
    try {
        const char* bdy = newbuddy.toStdString().c_str();
        py::object buddy = _buddyList.attr("getBuddyFromAddress")(bdy);
        int stat = py::extract<int>(buddy.attr("status"));
        status = static_cast<Buddy::Status>(stat);
    } catch(py::error_already_set const &){
        string perror_str = parse_python_exception();
        cout << Q_FUNC_INFO << perror_str << endl;
    }

    _buddyListModel->updateStatus(newbuddy, status);
}

std::string MessageApp::parse_python_exception() {

    PyObject *type_ptr = NULL, *value_ptr = NULL, *traceback_ptr = NULL;
    PyErr_Fetch(&type_ptr, &value_ptr, &traceback_ptr);

    std::string ret("Unfetchable Python error");

    if (type_ptr != NULL) {
        py::handle<> h_type(type_ptr);
        py::str type_pstr(h_type);
        py::extract<std::string> e_type_pstr(type_pstr);
        if (e_type_pstr.check())
            ret = e_type_pstr();
        else
            ret = "Unknown exception type";
    }

    if (value_ptr != NULL) {

        py::handle<> h_val(value_ptr);
        py::str a(h_val);
        py::extract<std::string> returned(a);
        if (returned.check())
            ret +=  ": " + returned();
        else
            ret += std::string(": Unparseable Python error: ");
    }

    if (traceback_ptr != NULL) {
        py::handle<> h_tb(traceback_ptr);
        py::object tb(py::import("traceback"));
        py::object fmt_tb(tb.attr("format_tb"));
        py::object tb_list(fmt_tb(h_tb));
        py::object tb_str(py::str("\n").join(tb_list));
        py::extract<std::string> returned(tb_str);
        if (returned.check())
            ret += ": " + returned();
        else
            ret += std::string(": Unparseable Python traceback");
    }
    return ret;
}
