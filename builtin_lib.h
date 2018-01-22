#ifndef BUILTIN_LIB_H
#define BUILTIN_LIB_H

#include "environment.h"

int URL(environment *);
int HOUR(environment *);
int ROOM(environment *);
int DESP(environment *);
int TEXT(environment *);
int REF(environment *);
int PROF(environment *);
int POL(environment *);
int POH(environment *);
int PMA(environment *);
int TA(environment *);
int TOL(environment *);
int TOH(environment *);
int TMA(environment *);
int HISTORY(environment *);
int HELP(environment *);
int EXIT(environment *);
int execute_builtin(char *, environment *);

#endif
