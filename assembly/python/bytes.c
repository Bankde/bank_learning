#include "Python.h"

/**
 * print_python_bytes - prints info about a Python 3 bytes object
 * @p: a pointer to a Python 3 bytes object
 * 
 * Return: Nothing
 */

/**
 * Compile with
 * gcc -Wall -Wextra -pedantic -Werror -std=c99 -shared -Wl,-soname,libPython.so -o libPython.so -fPIC -I/usr/include/python3.5 bytes.c
 * ref: https://blog.holbertonschool.com/hack-the-virtual-memory-python-bytes/
 * Note: python version is important (both compile and running). For example, commpile this program with python3.5 then run with python2 will result in address being shifted (because of different structure, I guess)
 */

void print_python_bytes(PyObject *p)
{
    /* The pointer with the correct type.*/
    PyBytesObject *s;
    
    s = (PyBytesObject *)p;
    if (s && PyBytes_Check(p)) {
        printf("Obj Address: %p\n", (void *)s);
        printf("Size: %ld\n", s->ob_base.ob_size);
        printf("Address of Size: %p\n", (void *) &s->ob_base.ob_size);
        printf("String: %s\n", (char *)s->ob_sval);
        printf("Address of string: %p\n", (void *)s->ob_sval);
        for (int i = 0; i < s->ob_base.ob_size; i++) {
            printf("%02x ", s->ob_sval[i]);
        }
        printf("\n");
    }
    else {
        printf("Not PyBytes Object\n");
    }
}
