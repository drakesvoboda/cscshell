#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "builtin.h"
#include "cscsh_readline.h"
#include "history.h"

history * event_history;
char * prompt;

int COMMAND_NOT_FOUND(char *command){
    printf("The %s command was not found\n", command);
    return 0;
}

int URL();
int HOUR();
int ROOM();
int DESP();
int TEXT();
int REF();
int PROF();
int POL();
int POH();
int PMA();
int TA();
int TOL();
int TOH();
int TMA();
int HISTORY();
int HELP();
int EXIT();

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

int HELP(){
    for(int i = 0; i < 18; ++i){
        puts(builtins[i].command);
    }

    return 0;
}

int URL(){
    puts("http://www.cs.wayne.edu/~lihao/Courses/CSC4420");
    return 0;
}

int HOUR(){
    puts("Mon/Wed 10:00 AM - 11:15 AM");
    return 0;
}
int ROOM(){
    puts("0125 State Hall");
    return 0;
}
int DESP(){
    puts("Operating system is an essential software layer to use various various computing devices. This course covers the basic components and design principles of modern operating systems, including process and thread, CPU scheduling, memory management, file system and others. This course also provides hand-on programming experiences of using Linux system calls, and design and implementation of a cloud-based file system.");
    return 0;
}
int TEXT(){
    puts("Modern Operating Systems, Andrew S. Tanenbaum, 4th Edition, Pearson, 2015");
    return 0;
}
int REF(){
    puts("Operating System Concepts, 8th Edition, Wiley, 2008.");
    puts("Understanding the Linux Kernel, 3rd Edition, O'Reilly Media, 2005. ");
    puts("Advanced UNIX Programming, 2nd Edition, Pearson, 2004.");
    puts("Advanced Programming in the UNIX Environment, Addison-Wesley, 1992.");
    return 0;
}
int PROF(){
    puts("Lihao Xu");
    return 0;
}
int POL(){
    puts("5057 Woodward, Floor 14, Suite 1401.1");
    return 0;
}
int POH(){
    puts("Mon, Wed, 1:00 PM – 2:00 PM or by appointment");
    return 0;
}
int PMA(){
    puts("lihao@wayne.edu");
    return 0;
}
int TA(){
    puts("Sumukhi Chandrashekar");
    return 0;
}
int TOL(){
    puts("5057 Woodward, Floor 3, Room 3211");
    return 0;
}
int TOH(){
    puts("Mon, Wed, 11:15AM – 12:15PM");
    return 0;
}
int TMA(){
    puts("sumukhic@wayne.edu");
    return 0;
}
int EXIT(){
    puts("Goodbye");
    return 1;
}
int HISTORY(){
    int i = 0;
    if(event_history->events[event_history->head] != NULL)
        i = event_history->head;

    for(int j = 0; j < event_history->size; ++j){
        puts(event_history->events[i]);

        ++i;
        if(i >= event_history->capacity)
            i = 0;
    }

    return 0;
}

int execute_builtin(char *command){
    for(int i = 0; i < 18; ++i){
        if(strcmp(command,builtins[i].command) == 0){
            return (builtins[i].func)();
        }
    }

    return COMMAND_NOT_FOUND(command);
}

void print_prompt(char * prompt){
    printf("%s",prompt);
}

int main(int argc, char **argv)
{
    prompt = "--> ";
    int exit_code = 0;
    char *buffer;
    event_history = create_history(4);
    do{
        print_prompt(prompt);
        buffer = cscsh_readline();
        exit_code = execute_builtin(buffer);
        add_event(event_history, buffer);
    }while(!exit_code);

    exit(EXIT_SUCCESS);
}
