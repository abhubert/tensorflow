
#ifndef __LIBPYTHON_HPP__
#define __LIBPYTHON_HPP__

#include <string>

#define _PYTHON_API_VERSION 1013

#if _WIN32 || _WIN64
#if _WIN64
typedef __int64 Py_ssize_t;
#else
typedef int Py_ssize_t;
#endif
#else
typedef long Py_ssize_t;
#endif

typedef struct _object PyObject;

#define METH_VARARGS  0x0001
#define METH_KEYWORDS 0x0002

#define __PyObject_HEAD_EXTRA
#define __PyObject_EXTRA_INIT

/* PyObject_HEAD defines the initial segment of every PyObject. */
#define _PyObject_HEAD                   \
__PyObject_HEAD_EXTRA                    \
  Py_ssize_t ob_refcnt;                 \
struct __typeobject *ob_type;

#define _PyObject_VAR_HEAD               \
_PyObject_HEAD                           \
  Py_ssize_t ob_size; /* Number of items in variable part */

typedef struct __typeobject {
  _PyObject_VAR_HEAD
  const char *tp_name; /* For printing, in format "<module>.<name>" */
Py_ssize_t tp_basicsize, tp_itemsize; /* For allocation */

} _PyTypeObject;

typedef struct __object {
  _PyObject_HEAD
} _PyObject;

typedef struct {
  _PyObject_VAR_HEAD
} _PyVarObject;

typedef _PyObject *(*_PyCFunction)(PyObject *, PyObject *);

struct _PyMethodDef { // Is the same for Python 3.4 and 2.7
  const char	*ml_name;	/* The name of the built-in function/method */
_PyCFunction  ml_meth;	/* The C function that implements it */
int		 ml_flags;	/* Combination of METH_xxx flags, which mostly
describe the args expected by the C func */
const char	*ml_doc;	/* The __doc__ attribute, or NULL */
};
typedef struct _PyMethodDef _PyMethodDef;

// For Python 3 we need different initialization macros
#define _PyObject_HEAD3                   _PyObject ob_base;

#define _PyObject_HEAD_INIT(type)        \
{ __PyObject_EXTRA_INIT                  \
  1, type },

#define _PyModuleDef_HEAD_INIT { \
_PyObject_HEAD_INIT(NULL)        \
  NULL, /* m_init */            \
0,    /* m_index */             \
NULL, /* m_copy */              \
}

typedef int (*_inquiry)(PyObject *);
typedef int (*_visitproc)(PyObject *, void *);
typedef int (*_traverseproc)(PyObject *, _visitproc, void *);
typedef void (*_freefunc)(void *);

typedef struct _PyModuleDef_Base {
  _PyObject_HEAD3
  _PyObject* (*m_init)(void);
  Py_ssize_t m_index;
  _PyObject* m_copy;
} _PyModuleDef_Base;

typedef struct _PyModuleDef{
  _PyModuleDef_Base m_base;
  const char* m_name;
  const char* m_doc;
  Py_ssize_t m_size;
  _PyMethodDef *m_methods;
  _inquiry m_reload;
  _traverseproc m_traverse;
  _inquiry m_clear;
  _freefunc m_free;
} _PyModuleDef;



extern void (*_Py_Initialize)();

extern PyObject* (*_Py_InitModule4)(const char *name, _PyMethodDef *methods,
           const char *doc, PyObject *self,
           int apiver);

extern void (*_Py_IncRef)(PyObject *);
extern void (*_Py_DecRef)(PyObject *);

extern PyObject* (*__PyObject_Str)(PyObject *);

extern PyObject* (*_PyObject_Dir)(PyObject *);

extern PyObject* (*_PyObject_GetAttrString)(PyObject*, const char *);
extern int (*_PyObject_HasAttrString)(PyObject*, const char *);

extern Py_ssize_t (*_PyTuple_Size)(PyObject *);
extern PyObject* (*_PyTuple_GetItem)(PyObject *, Py_ssize_t);

extern PyObject* (*_PyList_New)(Py_ssize_t size);
extern Py_ssize_t (*_PyList_Size)(PyObject *);
extern PyObject* (*_PyList_GetItem)(PyObject *, Py_ssize_t);
extern int (*_PyList_SetItem)(PyObject *, Py_ssize_t, PyObject *);

extern int (*_PyString_AsStringAndSize)(
    register PyObject *obj,	/* string or Unicode object */
    register char **s,		/* pointer to buffer variable */
    register Py_ssize_t *len	/* pointer to length variable or NULL
  (only possible for 0-terminated
  strings) */
);

extern PyObject* (*_PyString_FromString)(const char *);
extern PyObject* (*_PyString_FromStringAndSize)(const char *, Py_ssize_t);


extern void (*_PyErr_Fetch)(PyObject **, PyObject **, PyObject **);
extern PyObject* (*_PyErr_Occurred)(void);
extern void (*_PyErr_NormalizeException)(PyObject**, PyObject**, PyObject**);

extern int (*_PyCallable_Check)(PyObject *);

extern PyObject* (*_PyModule_GetDict)(PyObject *);
extern PyObject* (*_PyImport_AddModule)(const char *);

extern PyObject* (*_PyRun_StringFlags)(const char *, int, PyObject*, PyObject*, void*);
extern int (*_PyRun_SimpleFileExFlags)(FILE *, const char *, int, void *);

extern PyObject* (*_PyObject_GetIter)(PyObject *);
extern PyObject* (*_PyIter_Next)(PyObject *);

extern void (*_PySys_SetArgv)(int, char **);

typedef void (*_PyCapsule_Destructor)(PyObject *);
extern PyObject* (*_PyCapsule_New)(void *pointer, const char *name, _PyCapsule_Destructor destructor);
extern void* (*_PyCapsule_GetPointer)(PyObject *capsule, const char *name);

class LibPython {

public:
  bool load(const std::string& libPath, bool python3, std::string* pError);
  bool unload(std::string* pError);

private:
  friend LibPython& libPython();
  LibPython() : pLib_(NULL) {}
  LibPython(const LibPython&);
  void* pLib_;
};

inline LibPython& libPython() {
  static LibPython instance;
  return instance;
}


#endif

