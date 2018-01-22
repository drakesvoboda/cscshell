#ifndef HISTORY_H
#define HISTORY_H

typedef struct _history history;

struct _history {
    unsigned capacity,  head, size, event_number;
    char**events;
};

history * create_history(unsigned);

void add_event(history *, char *);

history * change_capacity(history *, unsigned);

history * increase_capacity(history *, unsigned);

history * decrease_capacity(history *, unsigned);

#endif
