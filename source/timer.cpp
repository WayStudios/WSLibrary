/*******************************************************************************
 * WayStudio Library
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

USING_WS_NAMESPACE

TimerSpecific::TimerSpecific(Timer* P) : H_Timer(P), Begin(0), End(0), Interval(0) {
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

Timer::TimerImplementation::TimerImplementation(Timer* H) : H_Specific(0), B_Active(false) {
    H_Specific = new TimerSpecific(H);
}

Timer::TimerImplementation::~TimerImplementation() {
    if (H_Specific)
        delete H_Specific;
}

void Timer::TimerImplementation::Start() {
    ThreadSpecific* P_THSPEC = 0;
#if defined(API_POSIX)
    P_THSPEC = reinterpret_cast<ThreadSpecific*> (pthread_getspecific(thread_pthread_key));
#elif defined(API_MSWINDOWS)
    P_THSPEC = reinterpret_cast<ThreadSpecific*> (TlsGetValue(thread_tls()));
#endif
    H_Specific->End = H_Specific->Begin = Time::Now().Value;
    if (P_THSPEC)
        P_THSPEC->LST_TimerSpecific.Append(H_Specific);
}

ws_timeval Timer::TimerImplementation::Stop() {
    if (H_Specific) {
        ThreadSpecific* P_THSPEC = 0;
#if defined(API_POSIX)
        P_THSPEC = reinterpret_cast<ThreadSpecific*> (pthread_getspecific(thread_pthread_key));
#elif defined(API_MSWINDOWS)
        P_THSPEC = reinterpret_cast<ThreadSpecific*> (TlsGetValue(thread_tls()));
#endif
        if (P_THSPEC)
            P_THSPEC->LST_TimerSpecific.Remove(H_Specific);
        H_Specific->End = Time::Now().Value;
        return (H_Specific->End) - (H_Specific->Begin);
    }
    return 0;
}

Timer::Timer(Object* OBJ) : Object(OBJ), Implementation(0) {
    Implementation = new TimerImplementation(this);
}

Timer::~Timer() {
    Stop();
    if (Implementation)
        delete Implementation;
}

boolean Timer::IsActive() const {
    return Implementation->B_Active;
}

ws_timeval Timer::Interval() const {
    if (Implementation)
        if (Implementation->H_Specific)
            return Implementation->H_Specific->Interval;
    return 0;
}

void Timer::Start(ws_timeval V) {
    if (IsActive())
        return;
    if (Implementation) {
        if (Implementation->H_Specific) {
            Implementation->H_Specific->Interval = V;
            if (V != 0)
                Implementation->Start();
            else if (V == 0)
                Implementation->H_Specific->Begin = Time::Now().Value;
            Implementation->B_Active = true;
        }
    }
}

ws_timeval Timer::Stop() {
    if (IsActive()) {
        if (Implementation)
            if (Implementation->H_Specific) {
                Implementation->B_Active = false;
                if (Implementation->H_Specific->Interval != 0)
                    return Implementation->Stop();
                else if (Implementation->H_Specific->Interval == 0) {
                    Implementation->H_Specific->End = Time::Now().Value;
                    ws_timeval RET = Implementation->H_Specific->End - Implementation->H_Specific->Begin;
                    return RET;
                }
            }
    }
    return 0;
}

void Timer::ProcessEvent(Event* E) {
    if (E)
        if (E->Type == WS_TIMEEVENT)
            ProcessTimeEvent(static_cast<TimeEvent*> (E));
}

void Timer::ProcessTimeEvent(TimeEvent* E) {
    if (E)
        if (E->Interval >= Interval());
}

END_SOURCECODE
