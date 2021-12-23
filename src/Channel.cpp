#include <assert.h>
#include "Channel.h"

Channel::Channel(Eventloop* loop, int fd)
    : ownerloop_(loop),
      fd_(fd),
      events_(0),
      revents_(0),
      eventhandling_(false) { }

Channel::~Channel() {
    assert(!eventhandling_);
}

void Channel::HandleEvent() {
    eventhandling_ = true;
    if ((revents_ & EPOLLHUP) && !(revents_ & EPOLLIN)) {
        if (closecallback_) closecallback_();
    }
    else if (revents_ & EPOLLERR) {
        if (errorcallback_) errorcallback_();
    }
    else if (revents_ & (EPOLLIN | EPOLLPRI | EPOLLRDHUP)) {
        if (readcallback_) readcallback_();
    }
    else if (revents_ & EPOLLOUT) {
        if (writecallback_) writecallback_();
    }
    eventhandling_ = false;
}