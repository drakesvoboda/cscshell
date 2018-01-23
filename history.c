#include <stdlib.h>
#include <stdio.h>
#include "history.h"

history * create_history(unsigned capacity){
    if(capacity < 0){
        exit(EXIT_FAILURE);    
    }

    history * hist = (history *) malloc(sizeof(history));
    hist->capacity = capacity;
    hist->head = 0;
    hist->event_number = 1;
    hist->size = 0;
    hist->events = (char**) malloc(capacity * sizeof(char *));
    return hist;
}

void add_event(history * hist, char * event){
    if(hist->size == hist->capacity)
        free(hist->events[hist->head]);
    else
        ++hist->size;

    hist->events[hist->head] = event;

    ++hist->head;
    ++hist->event_number;

    if(hist->head >= hist->capacity)
        hist->head = 0;
}
 
history * change_capacity(history * hist, unsigned capacity){
    if(capacity < 0){
        puts("History capacity must be non-negative");
        return hist;
    }
    else if(capacity < hist->capacity)
        return decrease_capacity(hist, capacity);
    else if(capacity > hist->capacity)
        return increase_capacity(hist, capacity);
    else
        return hist;
}

history * increase_capacity(history * hist, unsigned capacity){
    if(hist->capacity >= capacity)
        exit(EXIT_FAILURE);

    history * new_hist = (history *) malloc(sizeof(history));  
    new_hist->events = (char**) malloc(capacity * sizeof(char *));
    new_hist->capacity = capacity;
    new_hist->size = hist->size;
    new_hist->head = hist->size;
    new_hist->event_number = hist->event_number;

    int start = hist->head;
    
    if(hist->events[start] == NULL)
        start = 0;

    for(int i = 0; i < new_hist->size; ++i){
        new_hist->events[i] = hist->events[start]; 

        ++start;
        if(start >= hist->capacity)
            start = 0;
    }

    return new_hist;
}
  
history * decrease_capacity(history * hist, unsigned capacity){
    if(hist->capacity <= capacity || hist->capacity < 0)
        exit(EXIT_FAILURE);

    history * new_hist = (history *) malloc(sizeof(history));  
    new_hist->events = (char**) malloc(capacity * sizeof(char *));
    new_hist->capacity = capacity;
    new_hist->event_number = hist->event_number;
    new_hist->head = 0;
    if(hist->size <= new_hist->capacity){
        new_hist->size = hist->size;
        for(; new_hist->head < new_hist->capacity && new_hist->head < hist->size; ++new_hist->head)
            new_hist->events[new_hist->head] = hist->events[new_hist->head];
        
        if(new_hist->head >= new_hist->capacity) new_hist->head = 0;
    }else{
        new_hist->size = new_hist->capacity;
        for(int i = 0; i < new_hist->capacity; ++i){
            --hist->head;     
            if(hist->head < 0) hist->head = hist->capacity-1;

            new_hist->events[i] = hist->events[hist->head];
        }
    }

    return new_hist;
}

void print_history(history * hist){
    int i = 0;
    int event_number = hist->event_number - hist->size;
    if(hist->events[hist->head] != NULL)
        i = hist->head;

    for(int j = 0; j < hist->size; ++j){
        printf("%d : %s\n", event_number, hist->events[i]);
        ++event_number;
        ++i;
        if(i >= hist->capacity)
            i = 0;
    }
}
