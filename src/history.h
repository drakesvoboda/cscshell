#ifndef HISTORY_H
#define HISTORY_H

typedef struct _history history;

struct _history {
    unsigned capacity, head, size, event_number;
    char**events;
};

history * create_history(unsigned);

void add_event(history *, char *, unsigned);

void change_capacity(history **, unsigned);

void increase_capacity(history **, unsigned);

void decrease_capacity(history **, unsigned);

void destroy_history(history **);

void print_history(history *);

#endif
