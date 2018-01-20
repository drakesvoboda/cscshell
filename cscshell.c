#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "builtin.h"
#include "cscsh_readline.h"

int COMMAND_NOT_FOUND(char *command){
    printf("The %s command was not found\n", command);
    return 0;
}

int PRINT_URL(){
    puts("test");
    return 0;
}

int EXIT(){
    puts("Goodbye");
    return 1;
}

int HELP();

const builtin builtins[] = {
    {"url", &PRINT_URL},
    {"help", &HELP},
    {"exit", &EXIT},
    {"quit", &EXIT},
};

int HELP(){
    for(int i = 0; i < 3; ++i){
        puts(builtins[i].command);
    }

    return 0;
}

int execute_builtin(char *command){
    for(int i = 0; i < 3; ++i){
        if(strcmp(command,builtins[i].command) == 0){
            return (builtins[i].func)();
        }
    }

    return COMMAND_NOT_FOUND(command);
}

int main(int argc, char **argv)
{
    int exit_code = 0;

    char *buffer;

    do{
        buffer = cscsh_readline();
        exit_code = execute_builtin(buffer);
        free(buffer);
    }while(!exit_code);

    exit(EXIT_SUCCESS);
}
