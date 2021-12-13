#include <unistd.h>
#include "Eventloop.h"

__thread Eventloop* t_loopInThisThread = 0;

Eventloop::Eventloop()
    : looping_(false),
      thread_ID(CurrentThread::tid()) {
        
    if (t_loopInThisThread) {
      printf("Another eventloop exist!\n");
    }
    else t_loopInThisThread = this;
}