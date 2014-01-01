
#include <iostream>
#include <boost/python.hpp>

#include "../integrator/integrator.h"

#include <QString>
#include <QDebug>

#include "messageapp.h"

using namespace std;
namespace py = boost::python;

class AcquireGIL 
{
public:
    inline AcquireGIL(){
        state = PyGILState_Ensure();
    }

    inline ~AcquireGIL(){
        PyGILState_Release(state);
    }
private:
    PyGILState_STATE state;
};

MessageApp::MessageApp()
{
    PyEval_InitThreads();
    Py_Initialize();
    AcquireGIL gil;
    try {

        py::object mm = py::import("__main__");
        py::object mn = mm.attr("__dict__");
        py::exec("import tc_client", mn);
        py::exec("import libintegrator", mn);
        py::exec("libintegrator.callback(1, \"s\")", mn);
        py::exec("socket = tc_client.tryBindPort(\"127.0.0.1\", 11009)", mn);
        _buddyList = py::eval("tc_client.BuddyList(libintegrator.callback, socket)", mn);

        // For some reason this call is needed in order to allow the looper thread
        // to be started in the previous call.
        py::exec("print \"start thread 1\"", mn);
        //py::exec("print \"start thread 2\"", mn);

    } catch(py::error_already_set const &){
        string perror_str = parse_python_exception();
        cout << "Error during configuration parsing: " << perror_str << endl;
    }
}

MessageApp::~MessageApp()
{
    // Not needed using boost::python apparently.
    //Py_Finalize();
}

void MessageApp::sendMessage(const QString& msg)
{
    try {
        py::object buddy = _buddyList.attr("getBuddyFromAddress")("k4hzlexjprajz5ew");
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
