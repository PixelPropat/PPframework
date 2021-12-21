#include <iostream>
#include <pthread.h>
#include <errno.h>
#include <deque>
#include "Condition.h"
#include "Thread.h"

Mutex ppmutex;
int err = 0;
Condition ppcond(ppmutex);
std::deque<int> queue;

void* ThreadEnqueue(void* num) {
    MutexLock Lock(ppmutex);
    queue.push_back(*(int*)num);
    std::cout << "push back the number" << *(int*)num << std::endl;
    ppcond.Notify();
}

void* ThreadDequeue(void*) {
    MutexLock Lock(ppmutex);
    while (queue.empty()) {
        std::cout << "waiting" << std::endl;
        ppcond.Wait();
    }
    int get = queue.front();
    queue.pop_front();
    std::cout << "Get the number" << get << " " << std::endl;
}

int main() {
    pthread_t tid1, tid2;
    for (int i = 0; i < 10; ++i) {
        err = pthread_create(&tid1, NULL, ThreadDequeue, NULL);
        if (err != 0) {
            perror("ThreadDequeue failed");
        }
        err = pthread_create(&tid2, NULL, ThreadEnqueue, (void*)&i);
        if (err != 0) {
            perror("ThreadEnqueue failed");
        }
        pthread_join(tid1, NULL);
        pthread_join(tid2, NULL);
    }
}