#ifndef PP_EVENTLOOP_H
#define PP_EVENTLOOP_H

#include <assert.h>
#include <memory>
#include "Noncopyable.h"
#include "CurrentThread.h"

typedef std::shared_ptr<Channel> Channelptr;
typedef std::vector<Channelptr> ChannelList;
class Epoll;
class Channel;
class Eventloop : noncopyable {
public:
    Eventloop();
    ~Eventloop();
    
    void quit();
    void loop();
    
    void assertInLoopThread() {
        assert(isInLoopThread());
    }
    bool isInLoopThread() const { return thread_ID == CurrentThread::tid(); }
    static Eventloop* GetEventLoopOfCurrentThread();
private:
    //void abortNotInLoopThread();
    bool looping_;
    const pid_t thread_ID;
    bool quit_;
    std::shared_ptr<Epoll> Epoller_;
    ChannelList activeChannels_;
};


#endif