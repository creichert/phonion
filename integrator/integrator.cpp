
#include <iostream>
#include <boost/python.hpp>

#include "integrator.h"

using namespace std;
using namespace boost::python;


static void callback(int type, PyObject* data) {

   cout << "CALLBACK" << endl;
   //cout << "CALLBACK TYPE: " << type << endl;
   // cout << "CALLBACK DATA: " << data << endl;
}

BOOST_PYTHON_MODULE(libintegrator)
{
    def("callback", callback);
}
