/*******************************************************************************
 * Way Studios Library
 * Developer:Xu Waycell
 *******************************************************************************/
#ifndef EVENTLOOPIMPLEMENTATION_HEADER
#define	EVENTLOOPIMPLEMENTATION_HEADER

#include <eventloop.hpp>
#if defined(API_POSIX)
#include <unistd.h>
#include <sys/select.h>
#include <fcntl.h>
#elif defined(API_MSWINDOWS)
#include <windows.h>
#endif

BEGIN_HEADER

BEGIN_WS_NAMESPACE

struct LOCAL EventLoopSpecific {
    explicit EventLoopSpecific(EventLoop*);
    ~EventLoopSpecific();

    EventLoop* eventLoop;
    EventQueue* eventQueue;
    EventDispatcher* eventDispatcher;
    boolean waiting;

#if defined(API_POSIX)
    static integer FD_MAX;
    integer FD_Pipe[2];
    boolean B_Pipe;
#elif defined(API_MSWINDOWS)
    HANDLE hEvent;
#endif

    UNCOPYABLE(EventLoopSpecific)
};

class LOCAL EventLoop::EventLoopImplementation {
    UNCOPYABLE(EventLoopImplementation)
public:
    EventLoopImplementation();
    ~EventLoopImplementation();

    TIMEVAL interval();
    void wait(TIMEVAL);
    void awake();
#if defined(API_POSIX)
    void openPipe();
    void closePipe();
    void readPipe(void*, SIZE);
    void writePipe(void*, SIZE);
#elif defined(API_MSWINDOWS)
    void openMSEvent();
    void closeMSEvent();
    void setMSEvent();
    void resetMSEvent();
#endif

    BOOLEAN active;
    EventLoopSpecific* eventLoopSpecific;
};

END_WS_NAMESPACE

END_HEADER

#endif
