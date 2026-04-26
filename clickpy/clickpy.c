#ifndef CLICKPY
#define CLICKPY
#ifdef __cplusplus
extern "C" {
#endif
#ifdef _WIN32
#include "Python.h"
#include <Windows.h>
void click(int atPos, int useStartKey, int useStopKey, DWORD msDelay, LONG total, UINT keyStop, UINT keyStart, UINT stopModifier, UINT startModifier, LONG x, LONG y) {
    MSG msg = {0};
    if (useStartKey) {
        RegisterHotKey(NULL, 1, startModifier, keyStart);
        while (1) {
            if (GetMessage(&msg, NULL, WM_HOTKEY, WM_HOTKEY) >= 0)
                if (msg.message == WM_HOTKEY) break;
            else return;
        } 
        UnregisterHotKey(NULL, 1);
    }
    if (useStopKey) RegisterHotKey(NULL, 1, stopModifier, keyStop);
    for (unsigned long i = 0; !total || (i != total); i++) {
        INPUT input = {0};
        input.type = INPUT_MOUSE;
        input.mi.dx = atPos ? x : 0;
        input.mi.dy = atPos ? y : 0;
        input.mi.mouseData = 0;
        input.mi.time = 0;
        input.mi.dwExtraInfo = 0;
        input.mi.dwFlags = (atPos ? (MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_VIRTUALDESK) : 0) | MOUSEEVENTF_LEFTDOWN;
        SendInput(1, &input,  sizeof(INPUT));
        input.mi.dwFlags = (atPos ? (MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_VIRTUALDESK) : 0) | MOUSEEVENTF_LEFTUP;
        SendInput(1, &input,  sizeof(INPUT));
        Sleep(msDelay);
        if (useStopKey && PeekMessageA(&msg, NULL, WM_HOTKEY, WM_HOTKEY, PM_REMOVE))
            if (msg.message == WM_HOTKEY) break;
    } 
    if (useStopKey) UnregisterHotKey(NULL, 1);
}
static int validCoords(PyObject *args) {
    if (!PyTuple_Check(args)) {
        PyErr_SetString(PyExc_TypeError, "Argument must be a tuple.");
        return 0;
    }
    if (!PyTuple_Size(args) != 2) {
        PyErr_SetString(PyExc_TypeError, "Tuple must have 2 elements.");
        return 0;
    }
    if (!PyLong_Check(PyTuple_GetItem(args, 0))) {
        PyErr_SetString(PyExc_TypeError, "First element must be a long.");
        return 0;
    }
    if (!PyLong_Check(PyTuple_GetItem(args, 1))) {
        PyErr_SetString(PyExc_TypeError, "Second element must be a long.");
        return 0;
    }
    return 1;
}
static PyObject *click_py(PyObject *self, PyObject *_) {
    click(0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0);
    Py_RETURN_NONE;
}
static PyObject *click_at_py(PyObject *self, PyObject *args) {
    if (!validCoords(args)) return NULL;
    click(1, 0, 0, 0, 1, 0, 0, 0, 0, PyLong_AsLong(PyTuple_GetItem(args, 0)), PyLong_AsLong(PyTuple_GetItem(args, 1)));
    Py_RETURN_NONE;
}
static PyObject *clicks_py(PyObject *self, PyObject *args, PyObject *kwargs) {
    static char* keywords[] = {"ms_delay", "key_stop", "key_start", "total_clicks", "stop_modifier", "start_modifier", NULL};
    unsigned int msDelay = 0, keyStop = 0, keyStart = 0, stopModifier = 0, startModifier = 0;
    unsigned long total = 0;
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "|$IIIkII", keywords, &msDelay, &keyStop, &keyStart, &total, &stopModifier, &startModifier))
        return NULL;
    click(0, keyStart, keyStop, msDelay, total, keyStop, keyStart, stopModifier, startModifier, 0, 0);
    Py_RETURN_NONE;
}
static PyObject *clicks_at_py(PyObject *self, PyObject *args, PyObject *kwargs) {
    // ms_delay/0, key_stop/None, key_start/None, total_clicks/0
    static char* keywords[] = {"position", "ms_delay", "key_stop", "key_start", "total_clicks", "stop_modifier", "start_modifier", NULL};
    unsigned int msDelay = 0, keyStop = 0, keyStart = 0, stopModifier = 0, startModifier = 0;
    unsigned long total = 0;
    PyObject *position;
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "O|$IIIkII", keywords, &position, &msDelay, &keyStop, &keyStart, &total, &stopModifier, &startModifier))
        return NULL;
    if (!validCoords(position)) return NULL;
    click(1, keyStart, keyStop, msDelay, total, keyStop, keyStart, stopModifier, startModifier, PyLong_AsLong(PyTuple_GetItem(position, 0)), PyLong_AsLong(PyTuple_GetItem(position, 1)));
    Py_RETURN_NONE;
}
static PyMethodDef clickpy_methods[] = {
    {"click_here", click_py, METH_NOARGS, "click here"},
    {"click_at", click_at_py, METH_O, "click at a specific location"},
    {"clicks_here", (PyCFunction)clicks_py, METH_VARARGS | METH_KEYWORDS, "multiple clicks at the current location"},
    {"clicks_at", (PyCFunction)clicks_at_py, METH_VARARGS | METH_KEYWORDS, "multiple clicks at the spcified location"},
    {NULL, NULL, 0, NULL}
};
static struct PyModuleDef clickpy_module = {PyModuleDef_HEAD_INIT, "clickpy", NULL, -1, clickpy_methods};
#define STRINGIFY(x) #x
#define add_mod(module, mod_name) PyModule_AddIntConstant(module, STRINGIFY(mod_name), MOD_##mod_name)
PyMODINIT_FUNC PyInit_clickpy(void) {
    PyObject *m = NULL;
    m = PyModule_Create(&clickpy_module);
    add_mod(m, ALT);
    add_mod(m, CONTROL);
    add_mod(m, SHIFT);
    add_mod(m, WIN);
    return m;
}
#else
#error "This file is only for windows."
#endif
#ifdef __cplusplus
}
#endif
#endif