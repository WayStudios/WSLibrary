/*******************************************************************************
 * Way Studios Library
 * Developer:Xu Waycell
 *******************************************************************************/
#include <timeevent.hpp>

BEGIN_SOURCECODE

USING_WS_NAMESPACE

TimeEvent::TimeEvent(TIMEVAL V) : Event(WS_TIMEEVENT), interval(V) {
}

TimeEvent::~TimeEvent() {
}

BOOLEAN TimeEvent::operator ==(const TimeEvent& REF) const {
    return interval == REF.interval;
}

BOOLEAN TimeEvent::operator !=(const TimeEvent& REF) const {
    return interval != REF.interval;
}

END_SOURCECODE
