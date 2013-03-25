/*******************************************************************************
 * WayStudio Library
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

    EventLoop* H_EventLoop;
    EventQueue* H_EventQueue;
    EventDispatcher* H_EventDispatcher;
    boolean B_Waiting;

#if defined(API_POSIX)
    static integer FD_MAX;
    integer FD_Pipe[2];
    boolean B_Pipe;
#elif defined(API_MSWINDOWS)
    HANDLE H_MSEvent;
    boolean B_MSEvent;
#endif

    UNCOPYABLE(EventLoopSpecific)
};

class LOCAL EventLoop::EventLoopImplementation {
    UNCOPYABLE(EventLoopImplementation)
public:
    EventLoopImplementation();
    ~EventLoopImplementation();

    ws_timeval Interval();
    void Wait(ws_timeval);
    void Awake();
#if defined(API_POSIX)
    void OpenPipe();
    void ClosePipe();
    void ReadPipe(void*, size);
    void WritePipe(void*, size);
#elif defined(API_MSWINDOWS)
    void OpenMSEvent();
    void CloseMSEvent();
    void SetMSEvent();
    void ResetMSEvent();
#endif

    boolean B_EventLoop;
    EventLoopSpecific* H_Specific;
};

END_WS_NAMESPACE

END_HEADER

#endif
