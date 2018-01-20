#ifndef BUILTIN_H
#define BUILTIN_H

typedef struct _builtin builtin;

struct _builtin {
    const char *command;
    int (*const func)();
};  

#endif
