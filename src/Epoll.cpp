#include "Epoll.h"
#include "Channel.h"
#include <errno.h>

const int EVENTS_NUM = 4096;
const int EPOLLWAITTIME = 10000;

Epoll::Epoll(Eventloop* loop)
    : ownerloop_(loop),
      epollfd_(epoll_create1(EPOLL_CLOEXEC)),
      events_(new epoll_event[EVENTS_NUM])
    {
        assert(epollfd_ > 0);
}

Epoll::~Epoll() {
    close(epollfd_);
}

void Epoll::EpollAddChannel(Channelptr req) {
    int fd = req->fd();
    fd2Channel[fd] = req;
    epoll_event event;
    event.data.fd = fd;
    event.events = req->events();
    if (epoll_ctl(epollfd_, EPOLL_CTL_ADD, fd, &event) < 0) {
        perror("Epoll add error!");
        fd2Channel[fd].reset();
    }
}

void Epoll::EpollModChannel(Channelptr req) {
    int fd = req->fd();
    assert(fd2Channel[fd] == req);
    epoll_event event;
    event.data.fd = fd;
    event.events = req->events();
    if (epoll_ctl(epollfd_, EPOLL_CTL_MOD, fd, &event) < 0) {
        perror("Epoll mod error!");
        fd2Channel[fd].reset();
    }
}

void Epoll::EpollRmChannel(Channelptr req) {
    int fd = req->fd();
    assert(fd2Channel[fd] == req);
    epoll_event event;
    event.data.fd = fd;
    event.events = req->events();
    if (epoll_ctl(epollfd_, EPOLL_CTL_DEL, fd, &event) < 0) {
        perror("Epoll del error!");
        fd2Channel[fd].reset();
    }
}

int Epoll::Poll(ChannelList* activeChannels) {
    while(true) {
        int numevents = epoll_wait(epollfd_, events_, EVENTS_NUM, EPOLLWAITTIME);
        if (numevents == -1) {
            continue;
        }
        GetActiveChannel(numevents, activeChannels);
        if ((*activeChannels).size() > 0) {
            return 0;
        }
    }
}

void Epoll::GetActiveChannel(int events_num, ChannelList* activeChannels) {
    assert(events_num > 0);
    for (int i = 0; i < events_num; ++i) {
        int fd = events_[i].data.fd;
        Channelptr currentreq = fd2Channel[fd];
        if (currentreq) {
            currentreq->setrevents(events_->events);
            activeChannels->push_back(currentreq);
        }
    }
}