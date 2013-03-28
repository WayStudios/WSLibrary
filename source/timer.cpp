/*******************************************************************************
 * Way Studios Library
 * Developer:Xu Waycell
 *******************************************************************************/
#include <timer.hpp>
#include <timerimpl.hpp>
#include <timeevent.hpp>
#include <threadimpl.hpp>
#include <time.hpp>

/*#if defined(API_POSIX)
//#include <time.h>
#include <sys/time.h>
#include <sys/types.h>
#elif defined(API_MSWINDOWS)
#endif*/

BEGIN_SOURCECODE

BEGIN_WS_NAMESPACE

TimerSpecific::TimerSpecific(Timer* P) : timer(P), begin(0), end(0), interval(0) {
    //	EventLoopSpecific::LST_TimerSpecific.Append(this);
}

TimerSpecific::~TimerSpecific() {
    //	EventLoopSpecific::LST_TimerSpecific.Remove(this);
}

//List<TimerSpecific*> TimerSpecific::SpecificList;

/*
ws_timeval TimerSpecific::Now()
{

#if defined(API_POSIX) && !defined(OS_MACOSX)
    timespec c_ts;
    if(clock_gettime(CLOCK_MONOTONIC,&c_ts)==0)
        return c_ts.tv_sec*1000+c_ts.tv_nsec/1000000;
#elif defined(OS_MACOSX)
    timeval tm_v;
    gettimeofday(&tm_v,0);
    return tm_v.tv_sec*1000+tm_v.tv_usec/1000;
#elif defined(API_MSWINDOWS)
    return static_cast<ws_timeval>(GetTickCount());
#endif
    return 0;
}
 */

Timer::TimerImplementation::TimerImplementation(Timer* H) : timerSpecific(0), active(false) {
    timerSpecific = new TimerSpecific(H);
}

Timer::TimerImplementation::~TimerImplementation() {
    if (timerSpecific)
        delete timerSpecific;
}

void Timer::TimerImplementation::start() {
    ThreadSpecific* P_THSPEC = 0;
#if defined(API_POSIX)
    P_THSPEC = reinterpret_cast<ThreadSpecific*> (pthread_getspecific(thread_pthread_key));
#elif defined(API_MSWINDOWS)
    P_THSPEC = reinterpret_cast<ThreadSpecific*> (TlsGetValue(thread_tls()));
#endif
    timerSpecific->end = timerSpecific->begin = Time::now().value;
    if (P_THSPEC)
        P_THSPEC->timerSpecificList.append(timerSpecific);
}

TIMEVAL Timer::TimerImplementation::stop() {
    if (timerSpecific) {
        ThreadSpecific* P_THSPEC = 0;
#if defined(API_POSIX)
        P_THSPEC = reinterpret_cast<ThreadSpecific*> (pthread_getspecific(thread_pthread_key));
#elif defined(API_MSWINDOWS)
        P_THSPEC = reinterpret_cast<ThreadSpecific*> (TlsGetValue(thread_tls()));
#endif
        if (P_THSPEC)
            P_THSPEC->timerSpecificList.remove(timerSpecific);
        timerSpecific->end = Time::now().value;
        return (timerSpecific->end) - (timerSpecific->begin);
    }
    return 0;
}

Timer::Timer(Object* OBJ) : Object(OBJ), implementation(0) {
    implementation = new TimerImplementation(this);
}

Timer::~Timer() {
    stop();
    if (implementation)
        delete implementation;
}

BOOLEAN Timer::isActive() const {
    return implementation->active;
}

TIMEVAL Timer::interval() const {
    if (implementation)
        if (implementation->timerSpecific)
            return implementation->timerSpecific->interval;
    return 0;
}

void Timer::start(TIMEVAL V) {
    if (isActive())
        return;
    if (implementation) {
        if (implementation->timerSpecific) {
            implementation->timerSpecific->interval = V;
            if (V != 0)
                implementation->start();
            else if (V == 0)
                implementation->timerSpecific->begin = Time::now().value;
            implementation->active = true;
        }
    }
}

TIMEVAL Timer::stop() {
    if (isActive()) {
        if (implementation)
            if (implementation->timerSpecific) {
                implementation->active = false;
                if (implementation->timerSpecific->interval != 0)
                    return implementation->stop();
                else if (implementation->timerSpecific->interval == 0) {
                    implementation->timerSpecific->end = Time::now().value;
                    TIMEVAL RET = implementation->timerSpecific->end - implementation->timerSpecific->begin;
                    return RET;
                }
            }
    }
    return 0;
}

void Timer::processEvent(Event* E) {
    if (E)
        if (E->type == WS_TIMEEVENT)
            processTimeEvent(static_cast<TimeEvent*> (E));
}

void Timer::processTimeEvent(TimeEvent* E) {
    if (E)
		if (E->interval >= interval()) {
		}
}

END_WS_NAMESPACE

END_SOURCECODE
