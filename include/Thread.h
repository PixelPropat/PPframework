#ifndef PP_THREAD_H
#define PP_THREAD_H

#include <pthread.h>
#include <functional>

class Thread {
public:
    typedef std::function<void()> ThreadFunc;
    Thread(const ThreadFunc func);
    ~Thread();
    void start();
    pid_t tid() const { return tid_; };
    bool isstarted() const { return started_; };
    int join();
private:
    pthread_t pthread_Id_;
    pid_t tid_;
    bool started_;
    bool joined_;
    ThreadFunc func_;
};

struct ThreadData {
    typedef Thread::ThreadFunc ThreadFunc;
    ThreadFunc func_;
    pid_t* tid_;

    ThreadData(ThreadFunc func, pid_t* tid);
    void RunInThread();
};

#endif