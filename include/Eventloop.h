#ifndef PP_EVENTLOOP_H
#define PP_EVENTLOOP_H

#include <assert.h>
#include <memory>
#include <vector>
#include "Noncopyable.h"
#include "CurrentThread.h"

#define ADD 1
#define MOD 2
#define DEL 3

class Epoll;
class Channel;

typedef std::shared_ptr<Channel> Channelptr;
typedef std::vector<Channelptr> ChannelList;

class Eventloop : noncopyable {
public:
    Eventloop();
    ~Eventloop();
    
    void quit();
    void loop();

    void updateChannelFromOutside(Channelptr ch, int flag);
    
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