/*******************************************************************************
 * WayStudio Library
 * Developer:Xu Waycell
 *******************************************************************************/
#ifndef TIMERIMPLEMENTATION_HEADER
#define	TIMERIMPLEMENTATION_HEADER

#include <timer.hpp>
#include <list.hpp>

BEGIN_HEADER

BEGIN_WS_NAMESPACE

struct LOCAL TimerSpecific {
    explicit TimerSpecific(Timer*);
    ~TimerSpecific();

    //    static ws_timeval Now();

    Timer* H_Timer;
    ws_timeval Begin;
    ws_timeval End;
    ws_timeval Interval;

    UNCOPYABLE(TimerSpecific)
};

class LOCAL Timer::TimerImplementation {
    UNCOPYABLE(TimerImplementation)
public:
    explicit TimerImplementation(Timer*);
    ~TimerImplementation();

    void Start();
    ws_timeval Stop();

    TimerSpecific* H_Specific;
    boolean B_Active;
};

END_WS_NAMESPACE

END_HEADER

#endif
