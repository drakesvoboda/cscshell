#include <stdlib.h>
#include "builtin_lib.h"
#include "cscsh_readline.h"
#include "environment.h"

environment * env;

int main(int argc, char **argv)
{
    env = create_environment();
    int exit_code;
    char *buffer;

    do{
        print_prompt(env);
        buffer = (char *) malloc(sizeof(char) * 32);
        cscsh_readline(buffer, 32);
        exit_code = execute_builtin(buffer, env);
    }while(!exit_code);

    exit(EXIT_SUCCESS);
}
