#ifndef PP_CHANNEL_H
#define PP_CHANNEL_H

#include <functional>
#include <sys/epoll.h>
#include "Noncopyable.h"

class Eventloop;
class Channel : noncopyable {
public:
    typedef std::function<void()> EventCallBack;

    Channel(Eventloop* loop, int fd);
    ~Channel();

    void HandleEvent();
    void SetReadCallBack(const EventCallBack cb) { readcallback_ = std::move(cb); }
    void SetWriteCallBack(const EventCallBack cb) { writecallback_ = std::move(cb); }
    void SetCloseCallBack(const EventCallBack cb) { closecallback_ = std::move(cb); }
    void SetErrorCallBack(const EventCallBack cb) { errorcallback_ = std::move(cb); }

    int fd() const { return fd_; }

    int events() const {return events_; }
    void setevents(int evnt) { events_ = evnt; }
    void setrevents(int revnt) { revents_ = revnt; }
    void enableReading() { events_ |= EPOLLIN; }
    void enableWriting() { events_ |= EPOLLOUT; }
    void disableReading() { events_ &= ~EPOLLIN; }
    void disableWriting() { events_ &= ~EPOLLOUT; }

    Eventloop* ownerloop() const { return loop_; }
    
private:
    Eventloop* loop_;
    int fd_;
    int events_;
    int revents_;

    EventCallBack readcallback_;
    EventCallBack writecallback_;
    EventCallBack closecallback_;
    EventCallBack errorcallback_;

    bool eventhandling_;
};

#endif