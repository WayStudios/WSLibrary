/*******************************************************************************
 * Way Studios Library
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
    DECLARE_SIGNAL(TIMEVAL, Timer, Timeout)
public:
    explicit Timer(Object* OBJ = 0);
    ~Timer();

    BOOLEAN isActive() const;

    TIMEVAL interval() const;

    void start(TIMEVAL V = 0);
    TIMEVAL stop();
protected:
    virtual void processEvent(Event*);
    virtual void processTimeEvent(TimeEvent*);
};

END_WS_NAMESPACE

END_HEADER

#endif
