#include <stdio.h>
#include <stdlib.h>
#include "environment.h"
#include "history.h"

environment * create_environment(void){
    environment * env = (environment *) malloc(sizeof(environment));
    env->prompt = "--> "; 
    env->event_history = create_history(20);

    return env;
}

void print_prompt(environment * env){
    printf("%s",env->prompt);
}

