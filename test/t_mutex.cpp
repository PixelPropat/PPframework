#include <iostream>
#include <pthread.h>
#include <errno.h>
#include "Mutex.h"
using namespace std;

int global = 1;
int err;
Mutex ppmutex;

static void* pthread_func(void*) {
    for (int i = 1; i < 10; i++) {
        MutexLock Lock(ppmutex);
        cout << "This is thread 1, the " << i << " time" << endl;
        global++;
        cout << "in thread, global is " << global << endl;
    }
}

int main() {
    int err;
    pthread_t tid;

    err = pthread_create(&tid, NULL, pthread_func, NULL);
    if (err != 0) {
        perror("create thread failed");
    }
    for (int i = 0; i < 5; i++) {
        MutexLock Lock(ppmutex);
        cout << "This is main thread executing!" << endl;
        global++;
        cout << "in main, global is " << global << endl;
    }
    err = pthread_join(tid, NULL);
    if (err != 0) {
        perror("thread join failed");
    }
}