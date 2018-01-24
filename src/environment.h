#ifndef ENV_H
#define ENV_H

#include "history.h"

typedef struct _environment environment;

struct _environment {
    char prompt[64];
    history * event_history;
};

environment * create_environment(void);
void destroy_environment(environment **);
void set_prompt(environment *, const char *);
void print_prompt(environment *);

#endif
