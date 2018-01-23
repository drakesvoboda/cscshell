#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "cscsh_readline.h"

#define DELIMITER " "

int cscsh_readline(char *buffer, unsigned INPUT_BUFFSIZE){
    int buffsize = INPUT_BUFFSIZE;
    int i = 0;
    char c;

    do{
        c = getchar();

        if(c == EOF || c == '\0' || c == '\n'){
            buffer[i] = '\0';
            return buffsize;
        }

        if(i >= buffsize){
            buffsize += INPUT_BUFFSIZE;
            buffer = realloc(buffer, buffsize * sizeof(char));
            
            if(!buffer)
                exit(EXIT_FAILURE);
        }

        buffer[i] = c;
        ++i;
    }while(1);
    
    exit(EXIT_FAILURE);
}

int cscsh_tokenize(char ** tokens, unsigned ARGS_BUFFSIZE, char * string){
    int buffsize = ARGS_BUFFSIZE;
    int i = 0;
    char * token = strtok(string, DELIMITER);

    while(token){
        tokens[i] = token;
        ++i;

        if(i >= buffsize){
            buffsize += ARGS_BUFFSIZE;
            tokens = realloc(tokens, buffsize * sizeof(char *));
            
            if(!tokens)
                exit(EXIT_FAILURE);
        }

        token = strtok(NULL, DELIMITER);
    }

    tokens[i] = NULL;
    
    return buffsize;
}
