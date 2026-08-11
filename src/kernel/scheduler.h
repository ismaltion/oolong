#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "../lib/stddef.h"

enum thread_state {
    DEAD,
    SLEEPING,
    RUNNABLE,
    RUNNING
};

struct thread {
    u64 process_id;
    enum thread_state state;
};

struct process {
    u64 user_id;
    u8 filename[32];
};

#endif