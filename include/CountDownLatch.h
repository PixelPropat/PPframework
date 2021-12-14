#ifndef PP_COUNTDOWN_LATCH_H
#define PP_COUNTDOWN_LATCH_H

#include "Condition.h"

class CountDownLatch : noncopyable
{
private:
    mutable Mutex mutex_;
    Condition cond_;
    int count_;
public:
    CountDownLatch(int count);
    ~CountDownLatch();
    void Wait();
    void CountDown();
    int GetCount() const;
};

inline CountDownLatch::CountDownLatch(int count)
    : mutex_(),
      cond_(mutex_),
      count_(count) {}

inline CountDownLatch::~CountDownLatch() {}

inline void CountDownLatch::Wait() {
    MutexLock Lock(mutex_);
    while (count_ > 0) {
        cond_.Wait();
    }
}

inline void CountDownLatch::CountDown() {
    MutexLock Lock(mutex_);
    --count_;
    if (count_ == 0) {
        cond_.NotifyAll();
    }
}

inline int CountDownLatch::GetCount() const {
    MutexLock Lock(mutex_);
    return count_;
}

#endif