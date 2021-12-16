#ifndef PP_NONCOPYABLE
#define PP_NONCOPYABLE

class noncopyable
{
private:
    noncopyable(const noncopyable&) {};
    const noncopyable operator=(const noncopyable&) {};
public:
     noncopyable() {};
    ~ noncopyable() {};
};

#endif