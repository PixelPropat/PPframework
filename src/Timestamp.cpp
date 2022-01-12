#include <sys/time.h>
#include <stdio.h>
#include "Timestamp.h"

Timestamp::Timestamp() : microseconds_(0) { }

Timestamp::Timestamp(int64_t microseconds) : microseconds_(microseconds) {}

Timestamp Timestamp::now() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    int64_t seconds = tv.tv_sec;
    return Timestamp(seconds * SecondsToMicro + tv.tv_usec);
}