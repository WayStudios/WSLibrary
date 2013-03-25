/*******************************************************************************
 * WayStudio Library
 * Developer:Xu Waycell
 *******************************************************************************/
#include <eventloop.hpp>
#include <eventloopimpl.hpp>
#include <eventdispatcher.hpp>
#include <threadimpl.hpp>
#include <timerimpl.hpp>
#include <event.hpp>
#include <timeevent.hpp>
#include <time.hpp>

BEGIN_SOURCECODE

BEGIN_WS_NAMESPACE

EventLoopSpecific::EventLoopSpecific(EventLoop* P_EL) : H_EventLoop(P_EL), H_EventQueue(0), H_EventDispatcher(0), B_Waiting(false)
#if defined(API_POSIX)
, B_Pipe(false)
#elif defined(API_MSWINDOWS)
, B_MSEvent(false)
#endif
{
}

EventLoopSpecific::~EventLoopSpecific() {
}

EventLoop::EventLoopImplementation::EventLoopImplementation() : B_EventLoop(false), H_Specific(0) {
}

EventLoop::EventLoopImplementation::~EventLoopImplementation() {
}

ws_timeval EventLoop::EventLoopImplementation::Interval() {
    ws_timeval RET = 0;
    ThreadSpecific* P_THSPEC = 0;
#if defined(API_POSIX)
    P_THSPEC = reinterpret_cast<ThreadSpecific*> (pthread_getspecific(thread_pthread_key));
#elif defined(API_MSWINDOWS)
    P_THSPEC = reinterpret_cast<ThreadSpecific*> (TlsGetValue(thread_tls()));
#endif
    if (P_THSPEC) {
        if (!P_THSPEC->LST_TimerSpecific.Empty()) {
            ws_timeval NOW = Time::Now().Value;
            RET = NOW;
            for (List<TimerSpecific*>::Iterator ITER = P_THSPEC->LST_TimerSpecific.Begin(); ITER != P_THSPEC->LST_TimerSpecific.End(); ++ITER) {
                if ((*ITER)->Begin == (*ITER)->End) {
                    if ((NOW - (*ITER)->Begin) >= (*ITER)->Interval) {
                        (*ITER)->End = NOW;
                        H_Specific->H_EventQueue->Append(static_cast<Event*> (new TimeEvent(NOW - (*ITER)->Begin)), (*ITER)->H_Timer, (*ITER)->H_Timer);
                    } else
                        if (RET > ((*ITER)->Interval - (NOW - (*ITER)->Begin)))
                        RET = ((*ITER)->Interval - (NOW - (*ITER)->Begin));
                }
            }
        }
    }
    return RET;
}

void EventLoop::EventLoopImplementation::Wait(ws_timeval TV_TIMEOUT) {
    if (H_Specific)
        if (!(H_Specific->B_Waiting)) {
#if defined(API_POSIX)
            if (H_Specific->B_Pipe) {
                timeval timeout;
                timeout.tv_sec = TV_TIMEOUT;
                timeout.tv_usec = 0;
                fd_set r_set;
                FD_ZERO(&r_set);
                FD_SET(H_Specific->FD_Pipe[0], &r_set);
                integer nfds = 0;
                if (H_Specific->FD_Pipe[0] > H_Specific->FD_Pipe[1])
                    nfds = H_Specific->FD_Pipe[0] + 1;
                else
                    nfds = H_Specific->FD_Pipe[1] + 1;
                H_Specific->B_Waiting = true;
                select(nfds, &r_set, 0, 0, &timeout);
                H_Specific->B_Waiting = false;
                if (timeout.tv_sec != 0) {
                    byte MSG_Pipe;
                    ReadPipe(&MSG_Pipe, 1);
                }
            }
#elif defined(API_MSWINDOWS)
            if (H_Specific->B_MSEvent) {
                H_Specific->B_Waiting = true;
                if (TV_TIMEOUT != 0)
                    MsgWaitForMultipleObjects(1, &(H_Specific->H_MSEvent), false, TV_TIMEOUT, QS_ALLEVENTS);
                else
                    MsgWaitForMultipleObjects(1, &(H_Specific->H_MSEvent), false, INFINITE, QS_ALLEVENTS);
                ResetMSEvent();
                MSG msg;
                if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
                    TranslateMessage(&msg);
                    DispatchMessage(&msg);
                }
                H_Specific->B_Waiting = false;
            }
#endif
        }
}

void EventLoop::EventLoopImplementation::Awake() {
    if (H_Specific)
        if (H_Specific->B_Waiting) {
#if defined(API_POSIX)
            byte MSG = 0xff;
            WritePipe(&MSG, 1);
#elif defined(API_MSWINDOWS)
            SetMSEvent();
#endif
        }
}

#if defined(API_POSIX)

void EventLoop::EventLoopImplementation::OpenPipe() {
    if (H_Specific)
        if (!(H_Specific->B_Pipe))
            if (pipe(H_Specific->FD_Pipe) == 0) {
                integer rflag = fcntl(H_Specific->FD_Pipe[0], F_GETFL);
                integer wflag = fcntl(H_Specific->FD_Pipe[1], F_GETFL);
                rflag |= O_NONBLOCK;
                wflag |= O_NONBLOCK;
                fcntl(H_Specific->FD_Pipe[0], F_SETFL, rflag);
                fcntl(H_Specific->FD_Pipe[1], F_SETFL, wflag);
                H_Specific->B_Pipe = true;
            }
}

void EventLoop::EventLoopImplementation::ClosePipe() {
    if (H_Specific)
        if (H_Specific->B_Pipe) {
            close(H_Specific->FD_Pipe[0]);
            close(H_Specific->FD_Pipe[1]);
            H_Specific->B_Pipe = false;
        }
}

void EventLoop::EventLoopImplementation::ReadPipe(void* P_BYTE, size SZ) {
    if (H_Specific)
        if (H_Specific->B_Pipe)
            read(H_Specific->FD_Pipe[0], P_BYTE, SZ);
}

void EventLoop::EventLoopImplementation::WritePipe(void* P_BYTE, size SZ) {
    if (H_Specific)
        if (H_Specific->B_Pipe)
            write(H_Specific->FD_Pipe[1], P_BYTE, SZ);
}
#elif defined(API_MSWINDOWS)

void EventLoop::EventLoopImplementation::OpenMSEvent() {
    if (H_Specific)
        if (!(H_Specific->B_MSEvent)) {
            H_Specific->H_MSEvent = CreateEvent(0, true, false, 0);
            if (H_Specific->H_MSEvent)
                H_Specific->B_MSEvent = true;
        }
}

void EventLoop::EventLoopImplementation::CloseMSEvent() {
    if (H_Specific)
        if (H_Specific->B_MSEvent) {
            CloseHandle(H_Specific->H_MSEvent);
            H_Specific->B_MSEvent = false;
        }
}

void EventLoop::EventLoopImplementation::SetMSEvent() {
    if (H_Specific)
        if (H_Specific->B_MSEvent)
            SetEvent(H_Specific->H_MSEvent);
}

void EventLoop::EventLoopImplementation::ResetMSEvent() {
    if (H_Specific)
        if (H_Specific->B_MSEvent)
            ResetEvent(H_Specific->H_MSEvent);
}
#endif

EventLoop::EventLoop(EventQueue* P_EQ, EventDispatcher* P_ED, Object* OBJ) : Object(OBJ), Implementation(0) {
    Implementation = new EventLoopImplementation;
    if (Implementation) {
        Implementation->H_Specific = new EventLoopSpecific(this);
        Implementation->H_Specific->H_EventQueue = P_EQ;
        Implementation->H_Specific->H_EventDispatcher = P_ED;
    }
}

EventLoop::~EventLoop() {
    if (Implementation) {
        if (Implementation->H_Specific)
            delete Implementation->H_Specific;
        delete Implementation;
    }
}

boolean EventLoop::PostEvent(Event* E, Object* R, Object* S) {
    EventQueue* P_EQ = GetEventQueue();
    if (P_EQ) {
        P_EQ->Append(E, R, S);
        return true;
    }
    return false;
}

boolean EventLoop::IsActive() const {
    if (Implementation)
        return Implementation->B_EventLoop;
    return false;
}

void EventLoop::Enter() {
    if (Implementation) {
        ThreadSpecific* P_THSPEC = 0;
#if defined(API_POSIX)
        P_THSPEC = reinterpret_cast<ThreadSpecific*> (pthread_getspecific(thread_pthread_key));
#elif defined(API_MSWINDOWS)
        P_THSPEC = reinterpret_cast<ThreadSpecific*> (TlsGetValue(thread_tls()));
#endif
        if (P_THSPEC)
            if (!(P_THSPEC->H_EventLoopSpecific))
                P_THSPEC->H_EventLoopSpecific = Implementation->H_Specific;
#if defined(API_POSIX)
        Implementation->OpenPipe();
#elif defined(API_MSWINDOWS)
        Implementation->OpenMSEvent();
#endif
        Implementation->B_EventLoop = true;
        while (Implementation->B_EventLoop) {
            if (Implementation->H_Specific->H_EventQueue)
                if (Implementation->H_Specific->H_EventQueue->Empty())
                    Implementation->Wait(Implementation->Interval());
            Iteration();
        }
#if defined(API_POSIX)
        Implementation->ClosePipe();
#elif defined(API_MSWINDOWS)
        Implementation->CloseMSEvent();
#endif
        if (P_THSPEC)
            if (P_THSPEC->H_EventLoopSpecific == Implementation->H_Specific)
                P_THSPEC->H_EventLoopSpecific = 0;
    }
}

void EventLoop::Exit() {
    if (Implementation) {
        if (Implementation->B_EventLoop) {
            Implementation->B_EventLoop = false;
            Implementation->Awake();
        }
    }
}

EventQueue* EventLoop::GetEventQueue() const {
    if (Implementation)
        if (Implementation->H_Specific)
            return Implementation->H_Specific->H_EventQueue;
    return 0;
}

void EventLoop::SetEventQueue(EventQueue* P_EQ) {
    if (Implementation)
        if (Implementation->H_Specific)
            Implementation->H_Specific->H_EventQueue = P_EQ;
}

EventDispatcher* EventLoop::GetEventDispatcher() const {
    if (Implementation)
        if (Implementation->H_Specific)
            return Implementation->H_Specific->H_EventDispatcher;
    return 0;
}

void EventLoop::SetEventDispatcher(EventDispatcher* P_ED) {
    if (Implementation)
        if (Implementation->H_Specific)
            Implementation->H_Specific->H_EventDispatcher = P_ED;
}

void EventLoop::Iteration() {
    EventQueue* P_EQ = GetEventQueue();
    EventDispatcher* P_ED = GetEventDispatcher();
    if (P_EQ && P_ED)
        if (!P_EQ->Empty()) {
            P_ED->Dispatch(P_EQ->Top());
            delete P_EQ->Top().Content;
            P_EQ->Pop();
        }
}

END_WS_NAMESPACE

END_SOURCECODE
