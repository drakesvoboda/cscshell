#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "cscsh_string.h"
#include "history.h"

int increment_index(history * hist, int index){
    ++index;

    if(index >= hist->capacity)
        index = 0;

    return index;
}

int increment_index_range(history * hist, int index, int distance){
    index += distance;

    if(index >= hist->capacity)
        index = index - hist->capacity;

    return index;
}


history * create_history(unsigned capacity){
    if(capacity < 0)
        exit(EXIT_FAILURE);    

    history * hist = (history *) malloc(sizeof(history));
    hist->events = (char **) malloc(capacity * sizeof(char *));
    hist->capacity = capacity;
    hist->event_number = 1;
    hist->head = 0;
    hist->size = 0;

    return hist;
}

void add_event(history * hist, char * buffer, unsigned INPUT_BUFFSIZE){
    if(hist->size == hist->capacity){
        free(hist->events[hist->head]); 
        hist->events[hist->head] = NULL;
    } else
        ++hist->size;

    hist->events[hist->head] = deep_copy(buffer, INPUT_BUFFSIZE);

    ++hist->event_number;
    
    hist->head = increment_index(hist, hist->head);
}
 
void change_capacity(history ** hist, unsigned capacity){
    if(capacity < 0){
        puts("History capacity must be non-negative");
        return;
    }
    else if(capacity < (*hist)->capacity)
        decrease_capacity(hist, capacity);
    else if(capacity > (*hist)->capacity)
        increase_capacity(hist, capacity);
    else
        return;
}

void increase_capacity(history ** hist, unsigned capacity){
    if((*hist)->capacity >= capacity)
        return;

    history * new_hist = create_history(capacity);

    new_hist->event_number = (*hist)->event_number;
    new_hist->size = (*hist)->size;
    new_hist->head = (*hist)->size;

    int old_inc = (*hist)->head;
    
    if((*hist)->size < (*hist)->capacity)
        old_inc = 0;

    for(int i = 0; i < new_hist->size; ++i){
        new_hist->events[i] = deep_copy((*hist)->events[old_inc], 256); 
        old_inc = increment_index((*hist), old_inc);
    }

    destroy_history(hist);
    *hist = new_hist;
}

void decrease_capacity(history ** hist, unsigned capacity){
    if((*hist)->capacity <= capacity || (*hist)->capacity < 0)
        return;

    history * new_hist = create_history(capacity);

    new_hist->event_number = (*hist)->event_number;

    new_hist->head = 0;
    
    int i = increment_index_range((*hist), (*hist)->head, (*hist)->capacity - new_hist->capacity);
    
    do{
        if(i < (*hist)->size){
            new_hist->events[new_hist->head] = deep_copy((*hist)->events[i], 256);
            new_hist->head = increment_index(new_hist, new_hist->head);
            ++new_hist->size;
        }

        i = increment_index((*hist), i);
    }while(i != (*hist)->head && new_hist->size <= new_hist->capacity);

    destroy_history(hist);
    *hist = new_hist;
}

void print_history(history * hist){
    int i = 0;
    int event_number = hist->event_number - hist->size;
    if(hist->events[hist->head] != NULL)
        i = hist->head;

    for(int j = 0; j < hist->size; ++j){
        printf("%d : %s\n", event_number, hist->events[i]);
        ++event_number;
        i = increment_index(hist, i);
    }
}

void destroy_history(history ** hist){
    int i = 0;
    while((*hist)->events[i] != NULL && i < (*hist)->size){
        free((*hist)->events[i]);
        ++i;
    }
    free((*hist)->events);
    free(*hist); 
    *hist = NULL;
}
