#ifndef BUILTIN_LIB_H
#define BUILTIN_LIB_H

#include "environment.h"

int URL(char **, environment *);
int HOUR(char **, environment *);
int ROOM(char **, environment *);
int DESP(char **, environment *);
int TEXT(char **, environment *);
int REF(char **, environment *);
int PROF(char **, environment *);
int POL(char **, environment *);
int POH(char **, environment *);
int PMA(char **, environment *);
int TA(char **, environment *);
int TOL(char **, environment *);
int TOH(char **, environment *);
int TMA(char **, environment *);
int HISTORY(char **, environment *);
int HELP(char **, environment *);
int EXIT(char **, environment *);
int execute_builtin(char **, environment *);

#endif
