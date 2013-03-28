/*******************************************************************************
 * Way Studios Library
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

    Timer* timer;
    TIMEVAL begin;
    TIMEVAL end;
    TIMEVAL interval;

    UNCOPYABLE(TimerSpecific)
};

class LOCAL Timer::TimerImplementation {
    UNCOPYABLE(TimerImplementation)
public:
    explicit TimerImplementation(Timer*);
    ~TimerImplementation();

    void start();
    ws_timeval stop();

    TimerSpecific* timerSpecific;
    BOOLEAN active;
};

END_WS_NAMESPACE

END_HEADER

#endif
