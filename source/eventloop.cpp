/*******************************************************************************
 * Way Studios Library
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

EventLoopSpecific::EventLoopSpecific(EventLoop* P_EL) : eventLoop(P_EL)
													  , eventQueue(0)
													  , eventDispatcher(0)
													  , waiting(false)
#if defined(API_POSIX)
													  , B_Pipe(false)
#endif
{
}

EventLoopSpecific::~EventLoopSpecific() {
}

EventLoop::EventLoopImplementation::EventLoopImplementation() : active(false), eventLoopSpecific(0) {
}

EventLoop::EventLoopImplementation::~EventLoopImplementation() {
}

TIMEVAL EventLoop::EventLoopImplementation::interval() {
    TIMEVAL RET = 0;
    ThreadSpecific* P_THSPEC = 0;
#if defined(API_POSIX)
    P_THSPEC = reinterpret_cast<ThreadSpecific*> (pthread_getspecific(thread_pthread_key));
#elif defined(API_MSWINDOWS)
    P_THSPEC = reinterpret_cast<ThreadSpecific*> (TlsGetValue(thread_tls()));
#endif
    if (P_THSPEC) {
        if (!P_THSPEC->timerSpecificList.empty()) {
            TIMEVAL NOW = Time::now().value;
            RET = NOW;
            for (List<TimerSpecific*>::Iterator ITER = P_THSPEC->timerSpecificList.begin(); ITER != P_THSPEC->timerSpecificList.end(); ++ITER) {
                if ((*ITER)->begin == (*ITER)->end) {
                    if ((NOW - (*ITER)->begin) >= (*ITER)->interval) {
                        (*ITER)->end = NOW;
                        eventLoopSpecific->eventQueue->append(static_cast<Event*> (new TimeEvent(NOW - (*ITER)->begin)), (*ITER)->timer, (*ITER)->timer);
                    } else
                        if (RET > ((*ITER)->interval - (NOW - (*ITER)->begin)))
                        RET = ((*ITER)->interval - (NOW - (*ITER)->begin));
                }
            }
        }
    }
    return RET;
}

void EventLoop::EventLoopImplementation::wait(TIMEVAL TV_TIMEOUT) {
    if (eventLoopSpecific)
        if (!(eventLoopSpecific->waiting)) {
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
            if (eventLoopSpecific->hEvent) {
                eventLoopSpecific->waiting = true;
                if (TV_TIMEOUT != 0)
                    MsgWaitForMultipleObjects(1, &(eventLoopSpecific->hEvent), false, TV_TIMEOUT, QS_ALLEVENTS);
                else
                    MsgWaitForMultipleObjects(1, &(eventLoopSpecific->hEvent), false, INFINITE, QS_ALLEVENTS);
                resetMSEvent();
                MSG msg;
                while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0) {
                    TranslateMessage(&msg);
                    DispatchMessage(&msg);
                }
                eventLoopSpecific->waiting = false;
            }
#endif
        }
}

void EventLoop::EventLoopImplementation::awake() {
    if (eventLoopSpecific)
        if (eventLoopSpecific->waiting) {
#if defined(API_POSIX)
            byte MSG = 0xff;
            WritePipe(&MSG, 1);
#elif defined(API_MSWINDOWS)
            setMSEvent();
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

void EventLoop::EventLoopImplementation::openMSEvent() {
    if (eventLoopSpecific)
        if (!(eventLoopSpecific->hEvent)) {
            eventLoopSpecific->hEvent = CreateEvent(0, true, false, 0);
//            if (eventLoopSpecific->msEvent)
//                eventLoopSpecific->B_MSEvent = true;
        }
}

void EventLoop::EventLoopImplementation::closeMSEvent() {
    if (eventLoopSpecific)
        if (eventLoopSpecific->hEvent) {
            CloseHandle(eventLoopSpecific->hEvent);
            eventLoopSpecific->hEvent = NULL;
        }
}

void EventLoop::EventLoopImplementation::setMSEvent() {
    if (eventLoopSpecific)
        if (eventLoopSpecific->hEvent)
            SetEvent(eventLoopSpecific->hEvent);
}

void EventLoop::EventLoopImplementation::resetMSEvent() {
    if (eventLoopSpecific)
        if (eventLoopSpecific->hEvent)
            ResetEvent(eventLoopSpecific->hEvent);
}
#endif

EventLoop::EventLoop(EventQueue* P_EQ, EventDispatcher* P_ED, Object* OBJ) : Object(OBJ), implementation(0) {
    implementation = new EventLoopImplementation;
    if (implementation) {
        implementation->eventLoopSpecific = new EventLoopSpecific(this);
        implementation->eventLoopSpecific->eventQueue = P_EQ;
        implementation->eventLoopSpecific->eventDispatcher = P_ED;
    }
}

EventLoop::~EventLoop() {
    if (implementation) {
        if (implementation->eventLoopSpecific)
            delete implementation->eventLoopSpecific;
        delete implementation;
    }
}

BOOLEAN EventLoop::postEvent(Event* E, Object* R, Object* S) {
    EventQueue* P_EQ = getEventQueue();
    if (P_EQ) {
        P_EQ->append(E, R, S);
		if(implementation->active)
			iteration();
        return true;
    }
    return false;
}

BOOLEAN EventLoop::sendEvent(Event* E, Object* R, Object* S) {
    EventDispatcher* P_ED = getEventDispatcher();
    if (P_ED) {
		return P_ED->dispatch(E, R, S);
	}
	else
		return Object::sendEvent(E, R, S);
}

BOOLEAN EventLoop::isActive() const {
    if (implementation)
        return implementation->active;
    return false;
}

void EventLoop::enter() {
    if (implementation) {
        ThreadSpecific* P_THSPEC = 0;
#if defined(API_POSIX)
        P_THSPEC = reinterpret_cast<ThreadSpecific*> (pthread_getspecific(thread_pthread_key));
#elif defined(API_MSWINDOWS)
        P_THSPEC = reinterpret_cast<ThreadSpecific*> (TlsGetValue(thread_tls()));
#endif
        if (P_THSPEC)
            if (!(P_THSPEC->eventLoopSpecific))
                P_THSPEC->eventLoopSpecific = implementation->eventLoopSpecific;
#if defined(API_POSIX)
        Implementation->OpenPipe();
#elif defined(API_MSWINDOWS)
        implementation->openMSEvent();
#endif
        implementation->active = true;
        while (implementation->active) {
            if (implementation->eventLoopSpecific->eventQueue)
                if (implementation->eventLoopSpecific->eventQueue->empty())
                    implementation->wait(implementation->interval());
            iteration();
        }
#if defined(API_POSIX)
        Implementation->ClosePipe();
#elif defined(API_MSWINDOWS)
        implementation->closeMSEvent();
#endif
        if (P_THSPEC)
            if (P_THSPEC->eventLoopSpecific == implementation->eventLoopSpecific)
                P_THSPEC->eventLoopSpecific = 0;
    }
}

void EventLoop::exit() {
    if (implementation) {
        if (implementation->active) {
            implementation->active = false;
            implementation->awake();
        }
    }
}

void EventLoop::process() {
	iteration();
}

EventQueue* EventLoop::getEventQueue() const {
    if (implementation)
        if (implementation->eventLoopSpecific)
            return implementation->eventLoopSpecific->eventQueue;
    return 0;
}

void EventLoop::setEventQueue(EventQueue* P_EQ) {
    if (implementation)
        if (implementation->eventLoopSpecific)
            implementation->eventLoopSpecific->eventQueue = P_EQ;
}

EventDispatcher* EventLoop::getEventDispatcher() const {
    if (implementation)
        if (implementation->eventLoopSpecific)
            return implementation->eventLoopSpecific->eventDispatcher;
    return 0;
}

void EventLoop::setEventDispatcher(EventDispatcher* P_ED) {
    if (implementation)
        if (implementation->eventLoopSpecific)
            implementation->eventLoopSpecific->eventDispatcher = P_ED;
}

void EventLoop::iteration() {
    EventQueue* P_EQ = getEventQueue();
    EventDispatcher* P_ED = getEventDispatcher();
    if (P_EQ && P_ED)
		if(!P_EQ->empty())
			while (!P_EQ->empty()) {
				P_ED->dispatch(P_EQ->top());
				delete P_EQ->top().event;
				P_EQ->pop();
	        }
}

END_WS_NAMESPACE

END_SOURCECODE
