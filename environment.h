#ifndef ENV_H
#define ENV_H

#include "history.h"

typedef struct _environment environment;

struct _environment {
    char * prompt;
    history * event_history;
};

environment * create_environment(void);
void print_prompt(environment *);

#endif
