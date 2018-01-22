#ifndef HISTORY_H
#define HISTORY_H

typedef struct _history history;

struct _history {
    unsigned capacity;
    int head, size, event_number;
    char**events;
};

history * create_history(unsigned);

void add_event(history *, char *);

history * change_capacity(history *, int);

history * increase_capacity(history *, int);

history * decrease_capacity(history *, int);

#endif
