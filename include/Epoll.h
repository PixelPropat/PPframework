#ifndef PP_EPOLL_H
#define PP_EPOLL_H

#include <vector>
#include <memory>
#include <sys/epoll.h>
#include "Eventloop.h"

#define MAXFDS 100000

class Channel;

typedef struct epoll_event epoll_event;
typedef std::shared_ptr<Channel> Channelptr;
using ChannelList = std::vector<Channelptr>;
//typedef std::vector<epoll_event> epolleventList;


class Epoll : noncopyable {
public:

    Epoll(Eventloop* loop);
    ~Epoll();

    void EpollModChannel(Channelptr req);
    void EpollAddChannel(Channelptr req);
    void EpollRmChannel(Channelptr req);

    int Poll(ChannelList* activeChannels);
    void GetActiveChannel(int events_num, ChannelList* activeChannels);

    int GetEpollFd() const { return epollfd_; }

private:
    ChannelList fd2Channel = std::vector<Channelptr>(MAXFDS);
    Eventloop* ownerloop_;
    int epollfd_;
    epoll_event* events_;
};


#endif