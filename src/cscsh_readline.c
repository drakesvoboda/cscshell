#include <stdlib.h>
#include <stdio.h>
#include "cscsh_readline.h"

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
