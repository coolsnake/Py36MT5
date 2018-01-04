// Test.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "Python.h"
#include <string>

using namespace std;

PyObject *pModule;
PyObject *pFunc;
PyObject *pArgs;
PyObject *pValue;
PyObject *global_dict;


void LoadScript(const wchar_t* name)
{
	wstring w(name);
	string st(w.begin(), w.end());
	const char * s = st.c_str();
	Py_Initialize();
	FILE* fp;
	fopen_s(&fp, s, "r");
	int rz = 0;
	rz = PyRun_SimpleFile(fp, s);
	pModule = PyImport_AddModule("__ main__");
	global_dict = PyModule_GetDict(pModule);
}

void Finalize()
{
	Py_DECREF(pModule);
	Py_Finalize();
}

void NewArg(int i)
{
	pArgs = PyTuple_New(i);
}

void CallFunc(const wchar_t* name)
{
	wstring w(name);
	string st(w.begin(), w.end());
	const char * s = st.c_str();
	pFunc = PyDict_GetItemString(global_dict, s);
	if (pFunc != NULL)
	{
		pValue = PyObject_CallObject(pFunc, pArgs);
		Py_DECREF(pArgs);
		Py_DECREF(pFunc);
	}
}

long GetRezLong()
{
	long rez = 0;
	if (pValue != NULL)
	{
		rez = PyLong_AsLong(pValue);
		Py_DECREF(pValue);
	}
	return rez;
}

int main()
{
	auto fn = L"C:\\local\\Scripts\\test.py";
	LoadScript(fn);
	NewArg(0);
	auto f = L"TickCount";
	CallFunc(f);
	long r = GetRezLong();
	return 0;
}

