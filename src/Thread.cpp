#include "Thread.h"
#include "CurrentThread.h"

#include <assert.h>

namespace CurrentThread {
    __thread int t_cachedTid = 0;
}

ThreadData::ThreadData(ThreadFunc func, pid_t* tid, CountDownLatch* latch)
    : func_(std::move(func)),
      tid_(tid),
      latch_(latch) { }

void ThreadData::RunInThread() {
    *tid_ = CurrentThread::tid();
    printf("ready to call the thread function, thread id is %d\n", *tid_);
    tid_ = NULL;
    latch_->CountDown();
    latch_ = NULL;
    func_();
}

Thread::Thread(const ThreadFunc func)
    : func_(std::move(func)),
      started_(false),
      joined_(false),
      pthread_Id_(0),
      tid_(0),
      latch_(1) {
    printf("Thread constructor\n"); 
}

Thread::~Thread() {
    if (started_ && !joined_) {
        pthread_detach(pthread_Id_);
    }
}

static void* ThreadCaller(void* arg) {
    ThreadData* data = static_cast<ThreadData*>(arg);
    data->RunInThread();
    delete data;
}

void Thread::start() {
    assert(!started_);
    started_ = true;
    ThreadData* Funcpasser = new ThreadData(func_, &tid_, &latch_);
    if (pthread_create(&pthread_Id_, NULL, ThreadCaller, Funcpasser)) {
        started_ = false;
        delete Funcpasser;
    }
    else {
        latch_.Wait();
        assert(tid_ > 0);
    }
}

int Thread::join() {
    int err = 0;
    assert(started_ && !joined_);
    joined_ = true;
    err = pthread_join(pthread_Id_, NULL);
    printf("Thread join\n");
    return err;
}