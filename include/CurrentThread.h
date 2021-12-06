#ifndef PP_CURRENTTHREAD_H
#define PP_CURRENTTHREAD_H

#include <pthread.h>
#include <unistd.h>
#include <syscall.h>

namespace CurrentThread {
    __thread int t_cachedTid = 0;
    pid_t tid() {
        if (t_cachedTid == 0) {
            t_cachedTid = syscall(SYS_gettid);
        }
        return t_cachedTid;
    }
}

#endif