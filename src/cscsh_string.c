#include <stdlib.h>
#include <string.h>
#include "cscsh_string.h"

#define DELIMITER " \t"

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

char * deep_copy(char * buffer, unsigned INPUT_BUFFSIZE){
    unsigned buffsize = INPUT_BUFFSIZE;
    char * copy = (char *) malloc(sizeof(char) * buffsize);

    if(!copy)
        exit(EXIT_FAILURE);

    unsigned i = 0;
    while(buffer[i] != '\0'){
        copy[i] = buffer[i];
        ++i;
        if(i >= buffsize){
            buffsize += INPUT_BUFFSIZE;
            copy = (char *) realloc(buffer, buffsize * sizeof(char));

            if(!copy)
                exit(EXIT_FAILURE);
        }
    }

    copy[i] = '\0';

    return copy;
}
