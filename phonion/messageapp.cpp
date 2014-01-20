
#include <iostream>
#include <boost/python.hpp>

#include <QString>
#include <QDebug>
#include <QTimer>

#include "buddy.h"
#include "buddylistmodel.h"
#include "chatmodel.h"
#include "integrator.h"
#include "message.h"
#include "messageapp.h"

using namespace std;
namespace py = boost::python;

MessageApp::MessageApp(QObject* parent)
  : QObject(parent)
  , _chatModel(new ChatModel(this))
{
    Py_Initialize();
    try {

        py::object mm = py::import("__main__");
        py::object mn = mm.attr("__dict__");
        py::exec("import tc_client", mn);
        py::exec("import libintegrator", mn);
        py::exec("i = libintegrator.Integrator()", mn);
        //py::exec("socket = tc_client.tryBindPort(\"127.0.0.1\", 11009)", mn);
        _buddyList = py::eval("tc_client.BuddyList(i.callback)", mn);

        py::list buddies = py::extract<py::list>(_buddyList.attr("list"));
        QList<Buddy*> bs;
        int len = py::len(buddies);
        for (int i=0; i<len; ++i) {
            const char* address = py::extract<const char*>(py::str(buddies[i].attr("address")).encode("utf-8"));
            // const char* display_name
            bs.append(new Buddy(address, "", this));
        }
        _buddyListModel = new BuddyListModel(bs, this);

        Integrator* integrator = py::extract<Integrator*>(mn["i"]);
        connect(integrator, SIGNAL(onChatMessage(const QString&, const QString&)),
                              SLOT(onChatMessage(const QString&, const QString&)));

    } catch(py::error_already_set const &){
        string perror_str = parse_python_exception();
        cout << "Error during configuration parsing: " << perror_str << endl;
    }

    // Needed to keep app up to date.
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateInterpreter()));
    timer->start(1000);
}

void MessageApp::updateInterpreter()
{
    py::exec("print \"updating interpreter\"");
}

MessageApp::~MessageApp()
{
    _buddyList.attr("stopClient");
}

ChatModel* MessageApp::chatModel()
{
    return _chatModel;
}

BuddyListModel* MessageApp::buddyListModel()
{
    return _buddyListModel;
}

void MessageApp::onChatMessage(const QString& buddy, const QString& msg)
{
    _chatModel->newMessage(new Message(buddy, msg, false, _chatModel));
}

void MessageApp::addBuddy(const QString& newbuddy)
{
    if (newbuddy.length() != 16) {
        qDebug() << "[ERROR]: Incorrectly formatted buddy address.";
        return;
    }

    foreach(Buddy* buddy, _buddyListModel->buddies()) {

        if (buddy->onion() == newbuddy) {
            qDebug() << "Buddy already in list.";
            return;
        }
    }

    try {
        py::extract<bool>(_buddyList.attr("addBuddy")(newbuddy.toStdString()));
    } catch(py::error_already_set const &){
        string perror_str = parse_python_exception();
        cout << "Error during configuration parsing: " << perror_str << endl;
    }

    _buddyListModel->addBuddy(new Buddy(newbuddy, "", this));
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
        cout << "Error during configuration parsing: " << perror_str << endl;
    }
}

std::string MessageApp::parse_python_exception() {

    PyObject *type_ptr = NULL, *value_ptr = NULL, *traceback_ptr = NULL;
    PyErr_Fetch(&type_ptr, &value_ptr, &traceback_ptr);

    std::string ret("Unfetchable Python error");

    if(type_ptr != NULL){
        py::handle<> h_type(type_ptr);
        py::str type_pstr(h_type);
        py::extract<std::string> e_type_pstr(type_pstr);
        if(e_type_pstr.check())
            ret = e_type_pstr();
        else
            ret = "Unknown exception type";
    }

    if(value_ptr != NULL){

        py::handle<> h_val(value_ptr);
        py::str a(h_val);
        py::extract<std::string> returned(a);
        if(returned.check())
            ret +=  ": " + returned();
        else
            ret += std::string(": Unparseable Python error: ");
    }

    if(traceback_ptr != NULL){
        py::handle<> h_tb(traceback_ptr);
        py::object tb(py::import("traceback"));
        py::object fmt_tb(tb.attr("format_tb"));
        py::object tb_list(fmt_tb(h_tb));
        py::object tb_str(py::str("\n").join(tb_list));
        py::extract<std::string> returned(tb_str);
        if(returned.check())
            ret += ": " + returned();
        else
            ret += std::string(": Unparseable Python traceback");
    }
    return ret;
}
