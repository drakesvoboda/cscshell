#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "environment.h"
#include "history.h"

environment * create_environment(void){
    environment * env = (environment *) malloc(sizeof(environment));
    strcpy(env->prompt, "-->"); 
    env->prompt[63] = '\0'; // prompt will always be null-terminated if any of the first 63 characters are replaced 
    env->event_history = create_history(2);
    return env;
}

void print_prompt(environment * env){
    printf("\033[1;32m");
    int isMatching = 0; 
    for(int i = 0; env->prompt[i] != '\0'; ++i){
        if(isMatching){
            switch(env->prompt[i]){
                case 'h':
                    printf("%d", env->event_history->event_number);
                    break;
            }

            isMatching = 0;
        } else if(env->prompt[i] == '%') {
            isMatching = 1;
        } else {
            fputc(env->prompt[i], stdout);
        }
    }

    printf(" \033[0m");
}

void set_prompt(environment * env, const char * new_prompt){
    strncpy(env->prompt, new_prompt, 63); 
}

