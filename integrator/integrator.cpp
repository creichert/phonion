
#include <iostream>
#include <boost/python.hpp>

#include <QDebug>

#include "integrator.h"

using namespace std;
using namespace boost::python;


enum { CB_TYPE_CHAT = 1
     , CB_TYPE_FILE = 2
     , CB_TYPE_OFFLINE_SENT = 3
     , CB_TYPE_STATUS = 4
     , CB_TYPE_LIST_CHANGED = 5
     , CB_TYPE_AVATAR = 6
     , CB_TYPE_PROFILE = 7
     , CB_TYPE_REMOVE = 8
};

void Integrator::callback(int type, PyObject* data)
{
    PyObject* objectsRepresentation = PyObject_Repr(data);
    QString str = PyString_AsString(objectsRepresentation);
    qDebug() << "CALLBACK TYPE: " << type;
    qDebug() << "CALLBACK DATA: " << str;
    switch (type) {

    case CB_TYPE_CHAT: {

        PyObject* budobj = PySequence_GetItem(data, 0);
        PyObject* add = PyObject_GetAttrString(budobj, "address");
        QString address(PyString_AsString(add));

        PyObject* strobj = PySequence_GetItem(data, 1);
        str = PyString_AsString(strobj);

        emit onChatMessage(address, str);
        break;
    } // CB_TYPE_CHAT

    case CB_TYPE_STATUS: {

        PyObject* add = PyObject_GetAttrString(data, "address");
        QString address(PyString_AsString(add));

        emit statusChanged(address);
        break;
    } // CB_TYPE_STATUS
    }
}

BOOST_PYTHON_MODULE(libintegrator)
{
    // Expose class instead.
    class_<Integrator, boost::noncopyable>("Integrator")
        .def("callback", &Integrator::callback);
}
