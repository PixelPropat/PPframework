#ifndef PP_EVENTLOOP_H
#define PP_EVENTLOOP_H

#include <assert.h>
#include "Noncopyable.h"
#include "CurrentThread.h"

class Eventloop : noncopyable {
public:
    Eventloop();
    ~Eventloop();
    void loop();
    
    void assertInLoopThread() {
        assert(isInLoopThread());
    }
    bool isInLoopThread() const { return thread_ID == CurrentThread::tid(); }
    static Eventloop* GetEventLoopOfCurrentThread();
private:
    //void abortNotInLoopThread();
    bool looping_;
    const pid_t thread_ID;
};


#endif