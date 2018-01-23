#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "cscsh_readline.h"

#define DELIMITER " \t"

int cscsh_readline(char **buffer, unsigned INPUT_BUFFSIZE){
    unsigned buffsize = INPUT_BUFFSIZE;
    unsigned i = 0;
    char c;

    do{
        c = getchar();

        if(c == EOF || c == '\0' || c == '\n'){
            (*buffer)[i] = '\0';
            break;
        }

        (*buffer)[i] = c;
        ++i;

        if(i >= buffsize){
            buffsize += INPUT_BUFFSIZE;
            *buffer = (char *) realloc(*buffer, buffsize * sizeof(char));

            if(!(*buffer))
                exit(EXIT_FAILURE);
        }
    }while(1);
    
    return buffsize;
}

int cscsh_tokenize(char *** tokens, unsigned ARGS_BUFFSIZE, char * string){
    unsigned buffsize = ARGS_BUFFSIZE;
    unsigned i = 0;
    char * token = strtok(string, DELIMITER);

    while(token){
        (*tokens)[i] = token;
        ++i;

        if(i >= buffsize){
            buffsize += ARGS_BUFFSIZE;
            *tokens = (char **) realloc(*tokens, buffsize);
            if(!(*tokens))
                exit(EXIT_FAILURE);
        }

        token = strtok(NULL, DELIMITER);
    }

    (*tokens)[i] = NULL;
    return buffsize;   
}
