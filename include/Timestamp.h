#ifndef PP_TIMESTAMP_H
#define PP_TIMESTAMP_H

#include <stdint.h>

class Timestamp {
public:
    Timestamp();
    explicit Timestamp(int64_t microseconds);

    static Timestamp now();
    int64_t microseconds() const { return microseconds_; }
    bool operator<(const Timestamp rhs) { return microseconds_ < rhs.microseconds_; }
    bool operator==(const Timestamp rhs) { return microseconds_ == rhs.microseconds_; }
    bool isValid() const { return microseconds_ > 0; }

    static const int SecondsToMicro = 1000 * 1000;
private:
    int64_t microseconds_;
};


#endif