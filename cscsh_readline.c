#include <stdlib.h>
#include <stdio.h>
#include "cscsh_readline.h"

#define BUFF_SIZE 256

int cscsh_readline(char *buffer, int bufsize){
    int i = 0;
    char c;

    do{
        c = getchar();

        if(c == EOF || c == '\0' || c == '\n'){
            buffer[i] = '\0';
            return 0;
        }

        buffer[i] = c;
        ++i;
    }while(i < bufsize);

    return 0;
}

