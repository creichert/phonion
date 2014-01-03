
#include <iostream>
#include <boost/python.hpp>

#include <QString>
#include <QDebug>
#include <QTimer>

#include "buddylistmodel.h"
#include "chatmodel.h"
#include "integrator.h"
#include "messageapp.h"

using namespace std;
namespace py = boost::python;

MessageApp::MessageApp(QObject* parent)
  : QObject(parent)
  , _chatModel(new ChatModel())
  , _buddyListModel(0)
{
    _chatModel->setCurrentBuddy("k4hzlexjprajz5ew");
    Py_Initialize();
    try {

        py::object mm = py::import("__main__");
        py::object mn = mm.attr("__dict__");
        py::exec("import tc_client", mn);
        py::exec("import libintegrator", mn);

        // Fix this ugliness.
        py::exec("i = libintegrator.Integrator()", mn);

        //py::exec("socket = tc_client.tryBindPort(\"127.0.0.1\", 11009)", mn);
        _buddyList = py::eval("tc_client.BuddyList(i.callback)", mn);
        py::list buddies = py::extract<py::list>(_buddyList.attr("list"));
        QStringList bs;
        int len = py::len(buddies);
        for (int i=0; i<len; ++i) {
            const char* p = py::extract<const char*>(py::str(buddies[i].attr("address")).encode("utf-8"));
            bs.append(QString(p));
        }
        qDebug() << "Buddy List: " << bs.join(", ");
        _buddyListModel = new BuddyListModel;
        _buddyListModel->setStringList(bs);

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
    // Not needed using boost::python apparently.
    //Py_Finalize();
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
    _chatModel->newMessage(buddy, msg);
}

void MessageApp::sendChatMessage(const QString& msg)
{
    if (msg.isEmpty())
        return;

    _chatModel->newMessage(_chatModel->currentBuddy(), msg);
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
