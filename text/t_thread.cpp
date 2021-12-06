#include "Thread.h"
#include "CurrentThread.h"

static void Func() {
    printf("tid=%d\n", CurrentThread::tid());
}

static void Func2(int x) {
    printf("tid=%d, x=%d\n", CurrentThread::tid(), x);
}

int main() {
    printf("Currenttid is %d", CurrentThread::tid());

    Thread t1(Func);
    t1.start();
    printf("t1's tid=%d\n", t1.tid());
    t1.join();

    Thread t2(std::bind(Func2, 10));
    t2.start();
    printf("t2's tid=%d\n", t2.tid());
    t2.join();
}