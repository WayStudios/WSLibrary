/*******************************************************************************
 * WayStudio Library
 * Developer:Xu Waycell
 *******************************************************************************/
#ifndef TIMER_HEADER
#define	TIMER_HEADER

#include <object.hpp>

BEGIN_HEADER

BEGIN_WS_NAMESPACE

struct TimeEvent;

class EXPORT Timer : public Object {
    DECLARE_IMPLEMENTATION(Timer)
    UNCOPYABLE(Timer)
    signal :
    DECLARE_SIGNAL(ws_timeval, Timer, Timeout)
public:
    explicit Timer(Object* OBJ = 0);
    ~Timer();

    boolean IsActive() const;

    ws_timeval Interval() const;

    void Start(ws_timeval V = 0);
    ws_timeval Stop();
protected:
    virtual void ProcessEvent(Event*);
    virtual void ProcessTimeEvent(TimeEvent*);
};

END_WS_NAMESPACE

END_HEADER

#endif
