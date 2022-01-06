
#include <stdio.h>
#include "Eventloop.h"
#include "Epoll.h"
#include "Channel.h"

__thread Eventloop* t_loopInThisThread = 0;

Eventloop* Eventloop::GetEventLoopOfCurrentThread() {
	return t_loopInThisThread;
}

Eventloop::Eventloop()
    : looping_(false),
      thread_ID(CurrentThread::tid()),
	  quit_(false),
	  Epoller_(new Epoll(this)) {   
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

void Eventloop::quit() {
	quit_ = true;
} 

void Eventloop::loop() {
	assert(!looping_);
	assertInLoopThread();
	looping_ = true;
	printf("looping!, threadID is %d\n", thread_ID);
	quit_ = false;
	while (!quit_) {
		activeChannels_.clear();
		Epoller_->Poll(&activeChannels_);
		for (auto& it : activeChannels_) {
			it->HandleEvent();
		}
	}
	
	looping_ = false;
}