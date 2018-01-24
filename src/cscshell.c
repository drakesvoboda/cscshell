#include <stdlib.h>
#include "builtin_lib.h"
#include "cscsh_readline.h"
#include "environment.h"
#include "history.h"

#define INPUT_BUFFSIZE 128 
#define ARGS_BUFFSIZE 16

int main(int argc, char **argv)
{
    environment * env = create_environment();
    int exit_code;
    unsigned buffsize;
    char * buffer;
    char ** args;

    do{
        print_prompt(env);

        buffer = (char *) malloc(sizeof(char) * INPUT_BUFFSIZE);
        args = (char **) malloc(sizeof(char *) * ARGS_BUFFSIZE);
        
        if(!buffer || !args)
            exit(EXIT_FAILURE);

        buffsize = cscsh_readline(&buffer, INPUT_BUFFSIZE);
        
        if(buffer[0] != '\0'){
            add_event(env->event_history, buffer, buffsize);

            cscsh_tokenize(&args, ARGS_BUFFSIZE, buffer);

            exit_code = execute_builtin(args, env);            
        }

        free(buffer);
        free(args);
    }while(!exit_code);

    destroy_environment(&env);

    exit(EXIT_SUCCESS);
}
