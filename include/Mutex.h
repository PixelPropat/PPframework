#ifndef PP_MUTEX_H
#define PP_MUTEX_H
#include <stdio.h>
#include <pthread.h>
class Mutex {
public:
    inline Mutex() {
        pthread_mutex_init(&ppmutex, NULL);
    }
    ~Mutex() {
        pthread_mutex_destroy(&ppmutex);
    }
    void Lock() {
        pthread_mutex_lock(&ppmutex);
    }
    void Unlock() {
        pthread_mutex_unlock(&ppmutex);
    }
    pthread_mutex_t* GetMutex() {
        return &ppmutex;
    }

private:
    pthread_mutex_t ppmutex;
};

class MutexLock {
public: 
    MutexLock(Mutex& mutex) : mutex_(mutex) {
        mutex_.Lock();
    }
    ~MutexLock() {
        mutex_.Unlock();
    }

private:
/* Must be a reference, if not, it will use copy constructor, different mutex!*/
    Mutex& mutex_;
};


#endif