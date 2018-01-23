#include <stdlib.h>
#include <string.h>
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
    int buffsize;
    char * buffer;
    char * copy;
    char ** args;

    do{
        print_prompt(env);

        buffer = (char *) malloc(sizeof(char) * INPUT_BUFFSIZE);
        args = (char **) malloc(sizeof(char *) * ARGS_BUFFSIZE);
        
        if(!buffer || !args)
            exit(EXIT_FAILURE);

        buffsize = cscsh_readline(&buffer, INPUT_BUFFSIZE); //Read line from user into buffer

        copy = (char *) malloc(sizeof(char) * buffsize); //Freed by history

        if(!copy)
            exit(EXIT_FAILURE);

        strcpy(copy, buffer); //Copy buffer before splitting 

        cscsh_tokenize(&args, ARGS_BUFFSIZE, buffer); //Split buffer around arguments

        exit_code = execute_builtin(args, env);            

        add_event(env->event_history, copy); //Add copy to history, history will free the copy

        free(buffer);
        free(args);
    }while(!exit_code);

    exit(EXIT_SUCCESS);
}
