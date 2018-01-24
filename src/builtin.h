#ifndef BUILTIN_H
#define BUILTIN_H

#include "environment.h"

typedef struct _builtin builtin;

struct _builtin {
    const char *command;
    int (*const func)(char**, environment *);
};  

#endif
