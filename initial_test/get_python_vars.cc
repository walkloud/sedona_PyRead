#include <Python.h>
#include <iostream>
using namespace std;
#include <stdio.h>
#include <string.h>

int
main(int argc, char *argv[])
{
    PyObject *pName, *pModule, *particle_dict;
    int i;

    if (argc < 2) {
        fprintf(stderr,"Usage: call pythonfile funcname [args]\n");
        return 1;
    }


    Py_Initialize();
    /* Add the following 2 lines in order to add cwd to python path */
    PyRun_SimpleString("import sys");
    PyRun_SimpleString("sys.path.append('.')");

    pName = PyString_FromString(argv[1]);
    /* Error checking of pName left out */

    cout << "Loading Python module '" << argv[1] << "'" << endl;

    pModule = PyImport_Import(pName);
    Py_DECREF(pName);

    if (pModule != NULL) {
        particle_dict = PyObject_GetAttrString(pModule, (char *)"particles");
        cout << "particles dictionary loaded" << endl;

        if (particle_dict) {
            //int n_emit;
            PyObject *n_emitPy = PyDict_GetItemString(particle_dict, (char *)"n_emit");
            PyObject *energyPy = PyDict_GetItemString(particle_dict,"energy");
            if (n_emitPy != NULL && energyPy != NULL){
                int n_emit = PyLong_AsLong(n_emitPy);
                cout << "number of particles emmited = " << n_emit << endl;

                double energy = PyFloat_AsDouble(energyPy);
                cout << "Radiation energy = " << energy << endl;
            }
            else {
                Py_DECREF(particle_dict);
                Py_DECREF(pModule);
                Py_DECREF(n_emitPy);
                Py_DECREF(energyPy);
                PyErr_Print();
                fprintf(stderr,"Call failed\n");
                return 1;
            }
        }
        else {
            if (PyErr_Occurred())
                PyErr_Print();
            fprintf(stderr, "Cannot find function \"%s\"\n", argv[2]);
        }
        Py_DECREF(pModule);
        Py_DECREF(particle_dict);
    }
    else {
        PyErr_Print();
        fprintf(stderr, "Failed to load \"%s\"\n", argv[1]);
        return 1;
    }
    Py_Finalize();
    return 0;
}
