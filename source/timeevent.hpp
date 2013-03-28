/*******************************************************************************
 * Way Studios Library
 * Developer:Xu Waycell
 *******************************************************************************/
#ifndef TIMEEVENT_HEADER
#define	TIMEEVENT_HEADER

#include <event.hpp>

BEGIN_HEADER

#ifndef WS_TIMEEVENT
#define WS_TIMEEVENT 0x12
#endif

BEGIN_WS_NAMESPACE

struct EXPORT TimeEvent : public Event {
    explicit TimeEvent(TIMEVAL);
    ~TimeEvent();

    BOOLEAN operator ==(const TimeEvent&) const;
    BOOLEAN operator !=(const TimeEvent&) const;

    TIMEVAL interval;

    UNCOPYABLE(TimeEvent)
};

END_WS_NAMESPACE

END_HEADER

#endif
