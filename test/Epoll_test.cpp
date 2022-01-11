#include <sys/timerfd.h>
#include <memory>
#include <string.h>

#include "Eventloop.h"
#include "Epoll.h"
#include "Channel.h"

void readcb(Eventloop* ploop) {
    printf("executing read callback!\n");
    ploop->quit();
    printf("quit!\n");
}

int main() {
    Eventloop loop;
    Eventloop* ploop = &loop;
    int timerfd = timerfd_create(CLOCK_MONOTONIC,TFD_CLOEXEC | TFD_NONBLOCK);
    std::shared_ptr<Channel> ch = std::make_shared<Channel>(ploop, timerfd);
    printf("timerfd is %d\n", ch->fd());
    ch->SetReadCallBack(std::bind(readcb, ploop));
    ch->enableReading();
    loop.updateChannelFromOutside(ch, ADD);

    struct itimerspec howlong;
    memset(&howlong, 0, sizeof(howlong));
    howlong.it_value.tv_sec = 5;
    timerfd_settime(timerfd, 0, &howlong, NULL);

    loop.loop();

    close(timerfd);
}