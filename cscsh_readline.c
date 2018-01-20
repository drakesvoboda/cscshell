#include <stdlib.h>
#include <stdio.h>
#include "cscsh_readline.h"

#define BUFF_SIZE 256

char * csch_readline(void){
    int bufsize = BUFF_SIZE;
    int i = 0;
    char *buffer = malloc(sizeof(char) * bufsize);
    char c;

    if(!buffer){ exit(EXIT_FAILURE); }

    do{
        c = getchar();

        if(c == EOF || c == '\0' || c == '\n'){
            buffer[i] = '\0';
            return buffer;
        }

        buffer[i] = c;
        ++i;
    }while(i < bufsize);

}

