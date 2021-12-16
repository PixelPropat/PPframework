
#include <stdio.h>
#include "Eventloop.h"

__thread Eventloop* t_loopInThisThread = 0;

Eventloop* Eventloop::GetEventLoopOfCurrentThread() {
	return t_loopInThisThread;
}

Eventloop::Eventloop()
    : looping_(false),
      thread_ID(CurrentThread::tid()) {   
	printf("loop construct\n");   
  	if (t_loopInThisThread) {
    	printf("Another eventloop exist!\n");
		assert(!t_loopInThisThread);
  	}
  	else t_loopInThisThread = this;
}

Eventloop::~Eventloop() {
	printf("loop destruct\n");
	assert(!looping_);
	t_loopInThisThread = 0;
}

void Eventloop::loop() {
	assert(!looping_);
	assertInLoopThread();
	looping_ = true;
	printf("looping!, threadID is %d\n", thread_ID);
	sleep(5);
	looping_ = false;
}