#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "builtin_lib.h"
#include "builtin.h"
#include "environment.h"

const builtin builtins[] = {
    {"url", &URL},
    {"hour", &HOUR},
    {"room", &ROOM},
    {"desp", &DESP},
    {"text", &TEXT},
    {"ref", &REF},
    {"prof", &PROF},
    {"pol", &POL},
    {"poh", &POH},
    {"pma", &PMA},
    {"ta", &TA},
    {"tol", &TOL},
    {"toh", &TOH},
    {"tma", &TMA},
    {"history", &HISTORY},
    {"help", &HELP},
    {"exit", &EXIT},
    {"quit", &EXIT},
};

int HELP(environment * env){
    int n = sizeof(builtins) / sizeof(builtin);
    for(int i = 0; i < n; ++i){
        puts(builtins[i].command);
    }

    return 0;
}

int URL(environment * env){
    puts("http://www.cs.wayne.edu/~lihao/Courses/CSC4420");
    return 0;
}

int HOUR(environment * env){
    puts("Mon/Wed 10:00 AM - 11:15 AM");
    return 0;
}

int ROOM(environment * env){
    puts("0125 State Hall");
    return 0;
}
int DESP(environment * env){
    puts("Operating system is an essential software layer to use various various computing devices. This course covers the basic components and design principles of modern operating systems, including process and thread, CPU scheduling, memory management, file system and others. This course also provides hand-on programming experiences of using Linux system calls, and design and implementation of a cloud-based file system.");
    return 0;
}

int TEXT(environment * env){
    puts("Modern Operating Systems, Andrew S. Tanenbaum, 4th Edition, Pearson, 2015");
    return 0;
}

int REF(environment * env){
    puts("Operating System Concepts, 8th Edition, Wiley, 2008.");
    puts("Understanding the Linux Kernel, 3rd Edition, O'Reilly Media, 2005. ");
    puts("Advanced UNIX Programming, 2nd Edition, Pearson, 2004.");
    puts("Advanced Programming in the UNIX Environment, Addison-Wesley, 1992.");
    return 0;
}

int PROF(environment * env){
    puts("Lihao Xu");
    return 0;
}

int POL(environment * env){
    puts("5057 Woodward, Floor 14, Suite 1401.1");
    return 0;
}

int POH(environment * env){
    puts("Mon, Wed, 1:00 PM – 2:00 PM or by appointment");
    return 0;
}

int PMA(environment * env){
    puts("lihao@wayne.edu");
    return 0;
}

int TA(environment * env){
    puts("Sumukhi Chandrashekar");
    return 0;
}

int TOL(environment * env){
    puts("5057 Woodward, Floor 3, Room 3211");
    return 0;
}

int TOH(environment * env){
    puts("Mon, Wed, 11:15AM – 12:15PM");
    return 0;
}

int TMA(environment * env){
    puts("sumukhic@wayne.edu");
    return 0;
}

int EXIT(environment * env){
    puts("Goodbye");
    return 1;
}

int HISTORY(environment * env){
    int i = 0;
    if(env->event_history->events[env->event_history->head] != NULL)
        i = env->event_history->head;

    for(int j = 0; j < env->event_history->size; ++j){
        puts(env->event_history->events[i]);

        ++i;
        if(i >= env->event_history->capacity)
            i = 0;
    }

    return 0;
}

int COMMAND_NOT_FOUND(char *command){
    printf("The %s command was not found\n", command);
    return 0;
}

int execute_builtin(char *command, environment * env){
    int ret;
    int n = sizeof(builtins) / sizeof(builtin);
    for(int i = 0; i < n; ++i){
        if(strcmp(command,builtins[i].command) == 0){
            ret = (builtins[i].func)(env);
            add_event(env->event_history, command);
            return ret;
        }
    }

    return COMMAND_NOT_FOUND(command);
}


