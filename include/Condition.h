#ifndef PP_CONDITION_H
#define PP_CONDITION_H

#include "Mutex.h"

class Condition : noncopyable
{
private:
    Mutex& mutex_;
    pthread_cond_t ppcond;
public:   
    Condition(Mutex& mutex);
    ~Condition();
    void Wait();
    void Notify();
    void NotifyAll();
};

Condition::Condition(Mutex& mutex) : mutex_(mutex)
{
    pthread_cond_init(&ppcond, NULL);
}

Condition::~Condition()
{
    pthread_cond_destroy(&ppcond);
}

void Condition::Wait()
{
    pthread_cond_wait(&ppcond, mutex_.GetMutex());
}

void Condition::Notify()
{
    pthread_cond_signal(&ppcond);
}

void Condition::NotifyAll()
{
    pthread_cond_broadcast(&ppcond);
}

#endif