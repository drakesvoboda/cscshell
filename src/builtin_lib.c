#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "builtin_lib.h"
#include "builtin.h"
#include "environment.h"
#include "history.h"

int COMMAND_NOT_FOUND(char ** args){
    printf("The \'%s\' command was not found\n", args[0]);
    return 0;
}

int INVALID_ARGUMENTS(char ** args){
    printf("The argument(s) \"");
    for(int i = 0; args[i] != NULL; ++i){
        if(i == 0) continue;
        else if(i != 1) printf(" ");
        printf("%s", args[i]);
    }
    printf("\" are invalid for the \'%s\' command\n", args[0]);
    return 0;
}

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
    {"set", &SET},
    {"history", &HISTORY},
    {"help", &HELP},
    {"exit", &EXIT},
    {"quit", &EXIT},
};

int HELP(char ** args, environment * env){
    int n = sizeof(builtins) / sizeof(builtin);
    for(int i = 0; i < n; ++i){
        puts(builtins[i].command);
    }

    return 0;
}

int URL(char ** args, environment * env){
    puts("http://www.cs.wayne.edu/~lihao/Courses/CSC4420");
    return 0;
}

int HOUR(char ** args, environment * env){
    puts("Mon/Wed 10:00 AM - 11:15 AM");
    return 0;
}

int ROOM(char ** args, environment * env){
    puts("0125 State Hall");
    return 0;
}
int DESP(char ** args, environment * env){
    puts("Operating system is an essential software layer to use various various computing devices. This course covers the basic components and design principles of modern operating systems, including process and thread, CPU scheduling, memory management, file system and others. This course also provides hand-on programming experiences of using Linux system calls, and design and implementation of a cloud-based file system.");
    return 0;
}

int TEXT(char ** args, environment * env){
    puts("Modern Operating Systems, Andrew S. Tanenbaum, 4th Edition, Pearson, 2015");
    return 0;
}

int REF(char ** args, environment * env){
    puts("Operating System Concepts, 8th Edition, Wiley, 2008.");
    puts("Understanding the Linux Kernel, 3rd Edition, O'Reilly Media, 2005. ");
    puts("Advanced UNIX Programming, 2nd Edition, Pearson, 2004.");
    puts("Advanced Programming in the UNIX Environment, Addison-Wesley, 1992.");
    return 0;
}

int PROF(char ** args, environment * env){
    puts("Lihao Xu");
    return 0;
}

int POL(char ** args, environment * env){
    puts("5057 Woodward, Floor 14, Suite 1401.1");
    return 0;
}

int POH(char ** args, environment * env){
    puts("Mon, Wed, 1:00 PM – 2:00 PM or by appointment");
    return 0;
}

int PMA(char ** args, environment * env){
    puts("lihao@wayne.edu");
    return 0;
}

int TA(char ** args, environment * env){
    puts("Sumukhi Chandrashekar");
    return 0;
}

int TOL(char ** args, environment * env){
    puts("5057 Woodward, Floor 3, Room 3211");
    return 0;
}

int TOH(char ** args, environment * env){
    puts("Mon, Wed, 11:15AM – 12:15PM");
    return 0;
}

int TMA(char ** args, environment * env){
    puts("sumukhic@wayne.edu");
    return 0;
}

int EXIT(char ** args, environment * env){
    puts("Goodbye");
    return 1;
}

int HISTORY(char ** args, environment * env){
    print_history(env->event_history);
    return 0;
}

int SET(char ** args, environment * env){
    if(!args[1] || !args[2])
        return INVALID_ARGUMENTS(args);
    
    if(strcmp(args[1], "prompt") == 0)
        set_prompt(env, args[2]);
    else if(strcmp(args[1], "histlen") == 0){
        int new_cap = strtol(args[2], NULL, 10);
        if(new_cap > 0){
            change_capacity(&(env->event_history), new_cap);
        } else {
            return INVALID_ARGUMENTS(args);
        }
    }
    else
        return INVALID_ARGUMENTS(args);
        
    return 0;

}

int execute_builtin(char ** args, environment * env){
    int n = sizeof(builtins) / sizeof(builtin);
    for(int i = 0; i < n; ++i){
        if(strcmp(args[0],builtins[i].command) == 0){
            return (builtins[i].func)(args, env);
        }
    }

    return COMMAND_NOT_FOUND(args);
}
