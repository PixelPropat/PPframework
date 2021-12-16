#include <stdio.h>
#include "Eventloop.h"
#include "Thread.h"

void threadfunc(Eventloop* loop) {
    printf("threadfunc(), tid is %d\n", CurrentThread::tid());
    loop->loop();
}

int main() {
    printf("main, tid is %d\n", CurrentThread::tid());
    Eventloop loop;
    Thread thread(std::bind(threadfunc, &loop));
    thread.start();
    thread.join();
}